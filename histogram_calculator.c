#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define FIFOFile1 "/tmp/file1"
#define FIFOFile2 "/tmp/file2"

int main(){
	
	char photoAddress[100];
	int histogram[256] = {0} ,fileDirectory1 ,fileDirectory2,read_bytes;

	fileDirectory1 = open(FIFOFile1 , O_RDONLY);
	fileDirectory2 = open(FIFOFile2 , O_WRONLY);
	
	read_bytes = read(fileDirectory1 , photoAddress , sizeof(photoAddress));
	photoAddress[read_bytes] = '\0';

	calculate_histogram(photoAddress ,histogram );
	
	write(fileDirectory2 , histogram , 256*sizeof(int));
}


void calculate_histogram(char *photoAddress ,int *histogram ){
	unsigned char header[54],pixel;

    FILE *f = fopen(photoAddress, "rb");
    fread(header, sizeof(unsigned char), 54, f);

    int height = abs(*(int*)&header[22]);
    int width = *(int*)&header[18];

    for (int y = 0; y < height; ++y)
        for (int x = 0; x < width; ++x) {
            fread(&pixel, 1, 1, f);
            histogram[pixel]++;
        };
    fclose(f);
}

void calculate_histogram(char *photoAddress ,int *histogram );
