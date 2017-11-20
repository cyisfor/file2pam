#define _GNU_SOURCE // splice

#include <arpa/inet.h> // htonl

#include <sys/stat.h> // 

#include <sys/mman.h> // mmap

#include <math.h> // sqrt
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <unistd.h> // lseek
#include <fcntl.h> // splice
#include <stdlib.h> // mkstemp

#define PUTLIT(lit) fwrite(lit,sizeof(lit)-1,1,stdout)

int main(int argc, char *argv[])
{
	PUTLIT("P7\n");

	struct stat info;
	void* mem;
	int res = fstat(0,&info);
	if(res == 0 && info.st_size > 0) {
		puts("boop");
		mem = mmap(NULL,info.st_size,PROT_READ,MAP_PRIVATE,0,0);
		assert(mem != MAP_FAILED);
	} else {
		char template[] = ".tmpXXXXXX";
		int out = mkstemp(template);
		unlink(template);
		info.st_size = 0;
		for(;;) {
			ssize_t amt = splice(0, NULL, out, NULL, 0x100000, SPLICE_F_MOVE);
			if(amt == 0) {
				break;
			}
			fprintf(stderr,"reas %d\n",amt);
			assert(amt > 0);
			info.st_size += amt;
		}
		lseek(out, 0, SEEK_SET);
		mem = mmap(NULL,info.st_size,PROT_READ,MAP_PRIVATE,out,0);
		assert(mem != MAP_FAILED);
	}

	fprintf(stderr,"funt length %d\n",info.st_size);

	// RGB_ALPHA = 4 bytes per pixel so /4 = /2 /2
	// +4 for the sizeof the nsize
	size_t pixels = (info.st_size+4) / 3;
	int width = sqrt(pixels);
	int height = (pixels) / width + 1;

	printf("WIDTH %d\n",width);
	printf("HEIGHT %d\n",height);

	PUTLIT("DEPTH 3\n"
				 "MAXVAL 255\n"
				 "TUPLTYPE RGB\n"
				 "ENDHDR\n");

	size_t i;

	
	int32_t nsize = htonl(info.st_size);
	fprintf(stderr,"Um %d %d\n",info.st_size,nsize);
	ssize_t amt = fwrite(&nsize,sizeof(nsize),1,stdout);
	assert(amt == 1);
	fwrite(mem,1,info.st_size,stdout);
	munmap(mem,info.st_size);

	for(i=0;i<3*width-info.st_size%(3*width);++i) {
		fputc(255,stdout);
	}
		
	return 0;
}
