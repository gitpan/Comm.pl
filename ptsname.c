
/*---------------------------------ptsname.c---------------------------------*/

/* 
  Compile this only if your system uses the /dev/ptmx /dev/pts/* master, 
  slave model for ptys, but Comm.pl doesn't work for you as it (i.e. the 
  bit hack emulation for ptsname() doesn't work, meaning you're running
  something other than Solaris).

  Compile with -DAIX if you have AIX and/or /dev/ptc.

*/

#ifdef AIX
#define PTSNAME(x) ttyname(fd)
#else
#define PTSNAME(x) ptsname(fd)
#endif

#include <stdio.h>

main( argc, argv )
int argc;
char *argv[];
{
  int fd;
  char *pts, *ptsname();

  fd = atoi(argv[1]);
  if ( ! (pts = PTSNAME(fd) ) )
  {
    fprintf( stderr, "ptsname: failed ptsname(%d)\n", fd );
    exit(-1);
  }
  printf("%s\n", pts );
  exit(0);
}
