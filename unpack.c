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
	struct stat info;
	int res = fstat(0,&info);
	assert(res == 0);

	const char* mem = mmap(NULL,info.st_size,PROT_READ,MAP_PRIVATE,0,0);
	const char* cur = memchr(mem,'\n',info.st_size);
	assert(cur);
	cur = memchr(cur+1,'\n',info.st_size-(cur-mem));
	assert(cur);
	cur = memchr(cur+1,'\n',info.st_size-(cur-mem));
	assert(cur);
	++cur;

	int32_t length = ntohl(*((int32_t*)cur));
	cur += 4;
	assert(length <= info.st_size-(cur-mem));
	fwrite(cur,1,length,stdout);
}
