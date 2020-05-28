#include <stdio.h>
#include <stdlib.h>

#define SIZEL(x) (sizeof(x[0]))

char *argv0;

static void
usage(void)
{
	printf("Usage: %s [scale_file]\n", argv0);
	exit(1);
}

void
main(int argc, char *argv[])
{
	unsigned int i, n1, n2;
	float buf1[BUFSIZ], buf2[BUFSIZ];
	FILE *ampfile;

	argv0 = argv[0] ;

	if(argc<2)
		usage();

	if( !(ampfile = fopen(argv[1], "rb")) ){
		perror("fopen");
		exit(1);
	}

	do{
		n1 = fread(buf1, SIZEL(buf1), BUFSIZ, stdin) ;
		n2 = fread(buf2, SIZEL(buf2), n1, ampfile) ;
		/* Fill with zeroes envelope if its' file is finished. */
		for( i=n2 ; i<BUFSIZ ; ++i )
			buf2[i] = 0 ;
		for( i=0 ; i<n1 ; ++i )
			buf1[i] *= buf2[i] ;
		fwrite(buf1, SIZEL(buf1), n1, stdout);
	}while( n1==BUFSIZ );

	exit(0);
}
