// Licensed to the .NET Foundation under one or more agreements.
// The .NET Foundation licenses this file to you under the MIT license.
// See the LICENSE file in the project root for more information.

#include "GCEvent.h"

#include <pthread.h>
#include <errno.h>
#include <mach/clock.h>
#include <mach/mach_time.h>
#include <assert.h>
#include <memory>

#define HAVE_PTHREAD_CONDATTR_SETCLOCK 1
#define HAVE_MACH_ABSOLUTE_TIME 1

// The number of nanoseconds in a second.
const int tccSecondsToNanoSeconds = 1000000000;

// The number of nanoseconds in a millisecond.
const int tccMilliSecondsToNanoSeconds = 1000000;

#if HAVE_MACH_ABSOLUTE_TIME
static mach_timebase_info_data_t g_TimebaseInfo;
#endif // MACH_ABSOLUTE_TIME

namespace
{

#if HAVE_PTHREAD_CONDATTR_SETCLOCK
void TimeSpecAdd(timespec *time, uint32_t milliseconds)
{
    uint64_t nsec = time->tv_nsec + (uint64_t)milliseconds * tccMilliSecondsToNanoSeconds;
    if (nsec >= tccSecondsToNanoSeconds)
    {
        time->tv_sec += nsec / tccSecondsToNanoSeconds;
        nsec %= tccSecondsToNanoSeconds;
    }

    time->tv_nsec = nsec;
}
#endif // HAVE_PTHREAD_CONDATTR_SETCLOCK

#if HAVE_MACH_ABSOLUTE_TIME
// Convert nanoseconds to the timespec structure
// Parameters:
//  nanoseconds - time in nanoseconds to convert
//  t           - the target timespec structure
void NanosecondsToTimeSpec(uint64_t nanoseconds, timespec *t)
{
    t->tv_sec = nanoseconds / tccSecondsToNanoSeconds;
    t->tv_nsec = nanoseconds % tccSecondsToNanoSeconds;
}
#endif // HAVE_PTHREAD_CONDATTR_SETCLOCK

} // anonymous namespace

class GCEvent::Impl
{
    pthread_cond_t m_condition;
    pthread_mutex_t m_mutex;
    bool m_manualReset;
    bool m_state;
    bool m_isValid;

public:
    Impl(bool manualReset, bool initialState)
        : m_manualReset(manualReset),
          m_state(initialState),
          m_isValid(false)
    {
    }

    bool Initialize()
    {
        pthread_condattr_t attrs;
        int st = pthread_condattr_init(&attrs);
        if (st != 0)
        {
            assert(!"Failed to initialize UnixEvent condition attribute");
            return false;
        }

        // TODO(segilles) implement this for CoreCLR
        //PthreadCondAttrHolder attrsHolder(&attrs);

#if HAVE_PTHREAD_CONDATTR_SETCLOCK && !HAVE_MACH_ABSOLUTE_TIME
        // Ensure that the pthread_cond_timedwait will use CLOCK_MONOTONIC
        st = pthread_condattr_setclock(&attrs, CLOCK_MONOTONIC);
        if (st != 0)
        {
            assert(!"Failed to set UnixEvent condition variable wait clock");
            return false;
        }
#endif // HAVE_PTHREAD_CONDATTR_SETCLOCK && !HAVE_MACH_ABSOLUTE_TIME

        st = pthread_mutex_init(&m_mutex, NULL);
        if (st != 0)
        {
            assert(!"Failed to initialize UnixEvent mutex");
            return false;
        }

        st = pthread_cond_init(&m_condition, &attrs);
        if (st != 0)
        {
            assert(!"Failed to initialize UnixEvent condition variable");

            st = pthread_mutex_destroy(&m_mutex);
            assert(st == 0 && "Failed to destroy UnixEvent mutex");
            return false;
        }

        m_isValid = true;

        return true;
    }

    void CloseEvent()
    {
        if (m_isValid)
        {
            int st = pthread_mutex_destroy(&m_mutex);
            assert(st == 0 && "Failed to destroy UnixEvent mutex");

            st = pthread_cond_destroy(&m_condition);
            assert(st == 0 && "Failed to destroy UnixEvent condition variable");
        }
    }

    uint32_t Wait(uint32_t milliseconds, bool alertable)
    {
        UNREFERENCED_PARAMETER(alertable);

        timespec endTime;
#if HAVE_MACH_ABSOLUTE_TIME
        uint64_t endMachTime;
        if (milliseconds != INFINITE)
        {
            uint64_t nanoseconds = (uint64_t)milliseconds * tccMilliSecondsToNanoSeconds;
            NanosecondsToTimeSpec(nanoseconds, &endTime);
            endMachTime = mach_absolute_time() + nanoseconds * g_TimebaseInfo.denom / g_TimebaseInfo.numer;
        }
#elif HAVE_PTHREAD_CONDATTR_SETCLOCK
        if (milliseconds != INFINITE)
        {
            clock_gettime(CLOCK_MONOTONIC, &endTime);
            TimeSpecAdd(&endTime, milliseconds);
        }
#else
#error "Don't know how to perform timed wait on this platform"
#endif

        int st = 0;

        pthread_mutex_lock(&m_mutex);
        while (!m_state)
        {
            if (milliseconds == INFINITE)
            {
                st = pthread_cond_wait(&m_condition, &m_mutex);
            }
            else
            {
#if HAVE_MACH_ABSOLUTE_TIME
                // Since OSX doesn't support CLOCK_MONOTONIC, we use relative variant of the
                // timed wait and we need to handle spurious wakeups properly.
                st = pthread_cond_timedwait_relative_np(&m_condition, &m_mutex, &endTime);
                if ((st == 0) && !m_state)
                {
                    uint64_t machTime = mach_absolute_time();
                    if (machTime < endMachTime)
                    {
                        // The wake up was spurious, recalculate the relative endTime
                        uint64_t remainingNanoseconds = (endMachTime - machTime) * g_TimebaseInfo.numer / g_TimebaseInfo.denom;
                        NanosecondsToTimeSpec(remainingNanoseconds, &endTime);
                    }
                    else
                    {
                        // Although the timed wait didn't report a timeout, time calculated from the
                        // mach time shows we have already reached the end time. It can happen if
                        // the wait was spuriously woken up right before the timeout.
                        st = ETIMEDOUT;
                    }
                }
#else  // HAVE_MACH_ABSOLUTE_TIME
                st = pthread_cond_timedwait(&m_condition, &m_mutex, &endTime);
#endif // HAVE_MACH_ABSOLUTE_TIME \
    // Verify that if the wait timed out, the event was not set
                assert((st != ETIMEDOUT) || !m_state);
            }

            if (st != 0)
            {
                // wait failed or timed out
                break;
            }
        }

        if ((st == 0) && !m_manualReset)
        {
            // Clear the state for auto-reset events so that only one waiter gets released
            m_state = false;
        }

        pthread_mutex_unlock(&m_mutex);

        uint32_t waitStatus;

        if (st == 0)
        {
            waitStatus = WAIT_OBJECT_0;
        }
        else if (st == ETIMEDOUT)
        {
            waitStatus = WAIT_TIMEOUT;
        }
        else
        {
            waitStatus = WAIT_FAILED;
        }

        return waitStatus;
    }

    void Set()
    {
        pthread_mutex_lock(&m_mutex);
        m_state = true;
        pthread_mutex_unlock(&m_mutex);

        // Unblock all threads waiting for the condition variable
        pthread_cond_broadcast(&m_condition);
    }

    void Reset()
    {
        pthread_mutex_lock(&m_mutex);
        m_state = false;
        pthread_mutex_unlock(&m_mutex);
    }
};

GCEvent::GCEvent()
    : m_impl(nullptr)
{
}

void GCEvent::CloseEvent()
{
    assert(m_impl != nullptr);
    m_impl->CloseEvent();
}

void GCEvent::Set()
{
    assert(m_impl != nullptr);
    m_impl->Set();
}

void GCEvent::Reset()
{
    assert(m_impl != nullptr);
    m_impl->Reset();
}

uint32_t GCEvent::Wait(uint32_t timeout, bool alertable)
{
    assert(m_impl != nullptr);
    return m_impl->Wait(timeout, alertable);
}

bool GCEvent::CreateAutoEventNoThrow(bool initialState)
{
    // This implementation of GCEvent makes no distinction between
    // host-aware and non-host-aware events (since there will be no host).
    return CreateOSAutoEventNoThrow(initialState);
}

bool GCEvent::CreateManualEventNoThrow(bool initialState)
{
    // This implementation of GCEvent makes no distinction between
    // host-aware and non-host-aware events (since there will be no host).
    return CreateOSManualEventNoThrow(initialState);
}

bool GCEvent::CreateOSAutoEventNoThrow(bool initialState)
{
    assert(m_impl == nullptr);
    std::unique_ptr<GCEvent::Impl> event(new (std::nothrow) GCEvent::Impl(false, initialState));
    if (!event)
    {
        return false;
    }

    if (!event->Initialize())
    {
        return false;
    }

    m_impl = event.release();
    return true;
}

bool GCEvent::CreateOSManualEventNoThrow(bool initialState)
{
    assert(m_impl == nullptr);
    std::unique_ptr<GCEvent::Impl> event(new (std::nothrow) GCEvent::Impl(true, initialState));
    if (!event)
    {
        return false;
    }

    if (!event->Initialize())
    {
        return false;
    }

    m_impl = event.release();
    return true;
}