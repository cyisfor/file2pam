#include <arpa/inet.h> // htonl

#include <sys/stat.h> // 

#include <sys/mman.h> // mmap

#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <string.h> // 

#define PUTLIT(lit) fwrite(lit,sizeof(lit)-1,1,stdout)

int main(int argc, char *argv[])
{
	// pngtopam always produces P6
	// then a line, then a line, then data.
	const char* mem;
	struct stat info;
	int res = fstat(0,&info);
	if(res == 0 && info.st_size > 0) {
		mem = mmap(NULL,info.st_size,PROT_READ,MAP_PRIVATE,0,0);
		assert(mem != MAP_FAILED);
	} else {
		char buf[0x100000];
		info.st_size = fread(buf,1,0x100000,stdin);
		mem = buf;
	}
	const char* cur = memchr(mem,'\n',info.st_size);
	assert(cur);
	
	cur = memchr(cur+1,'\n',info.st_size-(cur-mem));
	assert(cur);

	cur = memchr(cur+1,'\n',info.st_size-(cur-mem));
	assert(cur);
	++cur;

	int32_t length = ntohl(*((int32_t*)cur));
	cur += 4;
	fprintf(stderr,"Um %d %d %d %d\n",length,info.st_size,cur-mem,
					length - (info.st_size-(cur-mem)));
	assert(length <= (info.st_size-(cur-mem)));
	fwrite(cur,1,length,stdout);
}
