
/*---------------------------------pt_chmod.c---------------------------------*/

/* 
  Compile this only if your system uses the /dev/ptmx /dev/pts/* master, 
  slave model for ptys, but you don't have /usr/lib/pt_chmod

  Compile with -DAIX if you have AIX and/or /dev/ptc.
*/

/* 
  It needs setuid permission:

  $ ls -l /usr/lib/pt_chmod
  ---s--x--x   1 root     bin         3116 Jul 15  1994 /usr/lib/pt_chmod

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
    fprintf( stderr, "pt_chmod: failed ptsname(%d)\n", fd );
    exit(-1);
  }

  if ( chown( pts, getuid(), getgid() ) )
  {
    fprintf( stderr, 
	"pt_chmod: failed chown ( ptsname(%d)=%s, getuid=%d, getgid=%d)\n",
	fd, pts, getuid(), getgid() );
    exit(-1);
  }

  if ( chmod( pts, 00620))
  {
    fprintf( stderr, 
	"pt_chmod: failed chmod ( ptsname(%d)=%s, 00620)\n",
	fd, pts );
    exit(-1);
  }

  exit( 0);
}

