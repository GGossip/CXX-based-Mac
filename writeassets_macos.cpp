#include "Headers_CXX/Foundation_CXX.h"

#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <string>

#include "Resource-Intermediate-macOS/Shaders.metallib.h"
#include "Resource-Intermediate-macOS/l_hires.h"

void write_assets()
{
    //Write Assets

    int fd_LibraryCaches;
    {
        void *__at_autoreleasepool_obj = objc_autoreleasePoolPush();

        char const *filenameautorelease = NSURL_fileSystemRepresentation(NSArrayNSURL_objectAtIndexedSubscript(NSFileManager_URLsForDirectory(NSFileManager_defaultManager(), NSCachesDirectory, NSUserDomainMask), 0));
        //struct stat stbuf;
        //assert(stat(filenameautorelease, &stbuf) == 0 && S_ISDIR(stbuf.st_mode));

        fd_LibraryCaches = open(filenameautorelease, O_RDONLY, O_DIRECTORY);
        assert(fd_LibraryCaches != -1);

        objc_autoreleasePoolPop(__at_autoreleasepool_obj);
    }

    //Shaders.metallib
    {
        int fd_metallib = openat(fd_LibraryCaches, "Shaders.metallib", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

        ssize_t res1 = write(fd_metallib, Resource_Intermediate_macOS_Shaders_metallib, Resource_Intermediate_macOS_Shaders_metallib_len);
        assert(res1 != -1 && res1 == Resource_Intermediate_macOS_Shaders_metallib_len);

        int res2 = close(fd_metallib);
        assert(res2 == 0);
    }

    //l_hires
    {
        int fd_l_hires = openat(fd_LibraryCaches, "l_hires", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

        ssize_t res1 = write(fd_l_hires, ThirdParty_Assets_Lenna_lena_std_DirectXTex_dds, ThirdParty_Assets_Lenna_lena_std_DirectXTex_dds_len);
        assert(res1 != -1 && res1 == ThirdParty_Assets_Lenna_lena_std_DirectXTex_dds_len);

        int res2 = close(fd_l_hires);
        assert(res2 == 0);
    }

    //LibraryCaches
    {
        int res1 = close(fd_LibraryCaches);
        assert(res1 == 0);
    }
}
