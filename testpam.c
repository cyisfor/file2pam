#include <stdio.h> // 

int main(int argc, char *argv[])
{
	int i;
	int j;
	puts("P6\n512 512\n255");
	for(i=0;i<512;++i) {
		for(j=0;j<512;++j) {
			fputc(i,stdout);
		}
	}
	return 0;
}
