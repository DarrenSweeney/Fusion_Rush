#if defined(__APPLE__)

#include "TargetConditionals.h"

#if TARGET_IPHONE_SIMULATOR
	#include <stdio.h>
	#include <unistd.h> 
	#include <string.h>
	#include <stdlib.h>
    #include <dirent.h>
    #include <fnmatch.h>
    #include <sys/stat.h>
    #include <fcntl.h>
    #include <sys/socket.h>
    #include <time.h>

    #if !defined(CC_TARGET_OS_IPHONE) // these are already defined in CCImage.c
        FILE *fopen$UNIX2003( const char *filename, const char *mode )
        {
            return fopen(filename, mode);
        }

        size_t fwrite$UNIX2003( const void *a, size_t b, size_t c, FILE *d )
        {
            return fwrite(a, b, c, d);
        }

        char* strerror$UNIX2003(int errornum)
        {
            return strerror(errornum);
        }
    #endif

int fputs$UNIX2003(const char *res1, FILE *res2)
{
    return fputs(res1,res2);
}

DIR * opendir$INODE64$UNIX2003( char * dirName )
{
    return opendir( dirName );
}

DIR * opendir$INODE64( char * dirName )
{
    return opendir( dirName );
}

struct dirent * readdir$INODE64( DIR * dir )
{
    return readdir( dir );
}

int closedir$UNIX2003( DIR * dir )
{
    return closedir( dir );
}

int fnmatch$UNIX2003( const char * pattern, const char * string, int flags )
{
    return fnmatch( pattern, string, flags );
}

int write$UNIX2003(int fd, const void *buf, size_t count)
{
    return write( fd, buf, count);
}

int open$UNIX2003( const char * fname, int mode )
{
    return open( fname, mode );
}

int read$UNIX2003(int fd, void *buf, size_t count)
{
    return read(fd, buf, count);
}

int close$UNIX2003( int fd )
{
    return close(fd );
}

int stat$INODE64( const char * pcc, struct stat * pss )
{
    return stat( pcc, pss );
}

int fcntl$UNIX2003( int fildes, int cmd, int one )
{
    return fcntl( fildes, cmd, one );
}

int fstat$INODE64( int filedes, struct stat * buf )
{
    return fstat( filedes, buf );
}

ssize_t pread$UNIX2003( int fildes, void *buf, size_t nbyte, off_t offset )
{
    return pread( fildes, buf, nbyte, offset );
}

ssize_t send$UNIX2003(int s, const void *msg, size_t len, int flags)
{
    return send ( s, msg, len, flags);
}

ssize_t recv$UNIX2003(int s, void *msg, int len, int flags)
{
    return recv ( s, msg, len, flags);
}

int select$UNIX2003(int  nfds,  fd_set  *readfds,  fd_set  *writefds, fd_set *errorfds, struct timeval *timeout)
{
    return select ( nfds, readfds, writefds, errorfds, timeout);
}

clock_t clock$UNIX2003( void )
{
    return clock ();
}


#endif

#endif /* __APPLE__ */
