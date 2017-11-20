#include <stdio.h> // 

int main(int argc, char *argv[])
{
	int i;
	int j;
	puts("P6\n512 512\n255");
	for(i=0;i<512;++i) {
		for(j=0;j<512;++j) {
			int depth;
			for(depth=0;depth<3;++depth) {
				fputc((i+j*depth+50)%256,stdout);
			}
		}
	}
	return 0;
}
