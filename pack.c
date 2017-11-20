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
#include <stdlib.h> // mkstemp, random

#define PUTLIT(lit) fwrite(lit,sizeof(lit)-1,1,stdout)

int main(int argc, char *argv[])
{
	struct stat info;
	void* mem;
	int res = fstat(0,&info);
	if(res == 0 && info.st_size > 0) {
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
			assert(amt > 0);
			info.st_size += amt;
		}
		lseek(out, 0, SEEK_SET);
		mem = mmap(NULL,info.st_size,PROT_READ,MAP_PRIVATE,out,0);
		close(out);
		assert(mem != MAP_FAILED);
	}

	// RGB = 3 bytes per pixel so /3
	// +4 for the sizeof the nsize
	size_t pixels = (info.st_size+4) / 3 + 1;
	int width = sqrt(pixels);
	int height = (pixels) / width;
	++height;

	fprintf(stderr,"%d pixels\n",pixels);



	PUTLIT("P6\n");

	printf("%d ",width);
	printf("%d\n",height);

	PUTLIT("255\n");

	size_t i;

	
	int32_t nsize = htonl(info.st_size);
	fprintf(stderr,"Um %d %d\n",info.st_size,nsize);
	ssize_t amt = fwrite(&nsize,sizeof(nsize),1,stdout);
	assert(amt == 1);
	amt = fwrite(mem,info.st_size,1,stdout);
	assert(amt == 1);
	munmap(mem,info.st_size);

	// each row is 3*width bytes,
	// bytes left in the row are 3*width-size%(3*width)
	// so if 3*width is 12, and size is 3535, 3535%12 = 7
	// 12-7 = 5, so 3535+5 = 3540, evenly divisible by 12
	fprintf(stderr,"um %d %d\n",pixels,height*width);
	for(i=0;i<3*height*width - (4+info.st_size);++i) {
		fputc(random() % 256,stdout);
	}
		
	return 0;
}
