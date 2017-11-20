#include <arpa/inet.h> // htonl

#include <sys/stat.h> // 

#include <sys/mman.h> // mmap

#include <math.h> // sqrt
#include <stdio.h>
#include <stdint.h>
#include <assert.h>

#define PUTLIT(lit) fwrite(lit,sizeof(lit)-1,1,stdout)

int main(int argc, char *argv[])
{
	PUTLIT("P7\n");

	struct stat info;
	int res = fstat(0,&info);
	assert(res == 0);

	void* mem = mmap(NULL,info.st_size,PROT_READ,MAP_PRIVATE,0,0);
	assert(mem != MAP_FAILED);

	// RGB_ALPHA = 4 bytes per pixel so /4 = /2 /2
	// +4 for the sizeof the nsize
	size_t pixels = (info.st_size+4) / 4;
	int width = sqrt(pixels);
	int height = (pixels) / width + 1;

	width = 4;
	height = 4;
	printf("WIDTH %d\n",width);
	printf("HEIGHT %d\n",height);

	PUTLIT("DEPTH 4\n"
				 "MAXVAL 255\n"
				 "TUPLTYPE RGB_ALPHA\n"
				 "ENDHDR\n");

	size_t i;

	for(i=0;i<4*4*4;++i) {
		fputc(i,stdout);
	}
	return 0;
	
	int32_t nsize = htonl(info.st_size);
	fwrite(&nsize,sizeof(nsize),1,stdout);
	fwrite(mem,1,info.st_size,stdout);
	munmap(mem,info.st_size);

	for(i=0;i<4*width-info.st_size%(4*width);++i) {
		fputc(255,stdout);
	}
		
	return 0;
}
