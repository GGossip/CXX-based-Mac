// Licensed to the .NET Foundation under one or more agreements.
// The .NET Foundation licenses this file to you under the MIT license.
// See the LICENSE file in the project root for more information.
// Interface between GC and the OS specific functionality
//

#ifndef _GC_EVENT_H_
#define _GC_EVENT_H_ 1


#include <stdint.h>

// An event is a synchronization object whose state can be set and reset
// indicating that an event has occured. It is used pervasively throughout
// the GC.
//
// Note that GCEvent deliberately leaks its contents by not having a non-trivial destructor.
// This is by design; since all uses of GCEvent have static lifetime, their destructors
// are run on process exit, potentially concurrently with other threads that may still be
// operating on the static event. To avoid these sorts of unsafety, GCEvent chooses to
// not have a destructor at all. The cost of this is leaking a small amount of memory, but
// this is not a problem since a majority of the uses of GCEvent are static. See CoreCLR#11111
// for more details on the hazards of static destructors.
class GCEvent
{
private:
    class Impl;
    Impl *m_impl;

public:
    // Constructs a new uninitialized event.
    GCEvent();

    // Closes the event. Attempting to use the event past calling CloseEvent
    // is a logic error.
    void CloseEvent();

    // "Sets" the event, indicating that a particular event has occured. May
    // wake up other threads waiting on this event. Depending on whether or
    // not this event is an auto-reset event, the state of the event may
    // or may not be automatically reset after Set is called.
    void Set();

    // Resets the event, resetting it back to a non-signalled state. Auto-reset
    // events automatically reset once the event is set, while manual-reset
    // events do not reset until Reset is called. It is a no-op to call Reset
    // on an auto-reset event.
    void Reset();

    // Waits for some period of time for this event to be signalled. The
    // period of time may be infinite (if the timeout argument is INFINITE) or
    // it may be a specified period of time, in milliseconds.
    // Returns:
    //   One of three values, depending on how why this thread was awoken:
    //      WAIT_OBJECT_0 - This event was signalled and woke up this thread.
    //      WAIT_TIMEOUT  - The timeout interval expired without this event being signalled.
    //      WAIT_FAILED   - The wait failed.
    uint32_t Wait(uint32_t timeout, bool alertable);

    // Determines whether or not this event is valid.
    // Returns:
    //  true if this event is invalid (i.e. it has not yet been initialized or
    //  has already been closed), false otherwise
    bool IsValid() const
    {
        return m_impl != nullptr;
    }

    // Initializes this event to be a host-aware manual reset event with the
    // given initial state.
    // Returns:
    //   true if the initialization succeeded, false if it did not
    bool CreateManualEventNoThrow(bool initialState);

    // Initializes this event to be a host-aware auto-resetting event with the
    // given initial state.
    // Returns:
    //   true if the initialization succeeded, false if it did not
    bool CreateAutoEventNoThrow(bool initialState);

    // Initializes this event to be a host-unaware manual reset event with the
    // given initial state.
    // Returns:
    //   true if the initialization succeeded, false if it did not
    bool CreateOSManualEventNoThrow(bool initialState);

    // Initializes this event to be a host-unaware auto-resetting event with the
    // given initial state.
    // Returns:
    //   true if the initialization succeeded, false if it did not
    bool CreateOSAutoEventNoThrow(bool initialState);
};

#endif