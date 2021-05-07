#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define file3 "/tmp/file3"
#define file4 "/tmp/file4"

int main(){
	char oldPhotoAddress[100],newPhotoAddress[100];
	int fileDirectory1 , fileDirectory2,read_bytes;

	fileDirectory1 = open(file3 , O_RDONLY);
	fileDirectory2 = open(file4 , O_WRONLY);
	read_bytes = read(fileDirectory1 , oldPhotoAddress , sizeof(oldPhotoAddress));
	oldPhotoAddress[read_bytes] = '\0';
	printf("Running Filter...\n");
	gaussian_filter(oldPhotoAddress , newPhotoAddress);
	
	write(fileDirectory2 , newPhotoAddress , sizeof(newPhotoAddress));
	
	close(fileDirectory1);
	close(fileDirectory2);
	return 0;
}

void gaussian_filter(char *oldPhotoAddress , char *newPhotoAddress);

