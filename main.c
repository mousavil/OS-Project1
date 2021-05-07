#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define FIFOFile1 "/tmp/file1"
#define FIFOFile2 "/tmp/file2"
#define FIFOFile3 "/tmp/file3"
#define FIFOFile4 "/tmp/file4"

int main() {

    char *args[] = {"./histogram", "./filtering", NULL};
    char newPhotoAddress[100], oldPhotoAddress[100];
    int histogram1[256],
    int histogram1[256], ;
    int arr2[10];
    int fileDirectory1[2], fileDirectory2[2];

    pipe(fileDirectory1);
    pipe(fileDirectory2);

    if (fork() == 0) {
        execvp(args[0], args);
        exit(0);
    } else if (fork() == 0) {
        execvp(args[1], args);
        exit(0);
    } else if (fork() == 0) {
        int histogram1[256] = {0}, histogram2[256] = {0};
        char address[100], new_address[100];
        int file1, file2, file3, file4, read_byte;

        close(fileDirectory1[1]);
        read(fileDirectory1[0], address, sizeof(address));

        mknod(FIFOFile1, S_IFIFO | 0640, 0);
        mknod(FIFOFile2, S_IFIFO | 0640, 0);
        mknod(FIFOFile3, S_IFIFO | 0640, 0);
        mknod(FIFOFile4, S_IFIFO | 0640, 0);

        file1 = open(FIFOFile1, O_WRONLY);
        file2 = open(FIFOFile2, O_RDONLY);
        file3 = open(FIFOFile3, O_WRONLY);
        file4 = open(FIFOFile4, O_RDONLY);

        write(file1, address, strlen(address));
        write(file3, address, strlen(address));
        printf("Done\n");

        sleep(1);
        read(file2, histogram1, 256 * sizeof(int));

        close(fileDirectory2[0]);
        write(fileDirectory2[1], histogram1, 256 * sizeof(int));

        exit(0);

    }
    printf("Enter Photo Address: ");
    fgets(oldPhotoAddress, sizeof(oldPhotoAddress), stdin);
    int len = strlen(oldPhotoAddress);
    oldPhotoAddress[len - 1] = '\0';

    close(fileDirectory1[0]);
    write(fileDirectory1[1], oldPhotoAddress, sizeof(oldPhotoAddress));

    close(fileDirectory2[1]);
    read(fileDirectory2[0], histogram1, 256 * sizeof(int));

    for (int i = 0; i < 256; i++) {
        printf("%-5d ", histogram1[i]);
        if (i % 15 == 0) {
            printf("\n");
        }
    }
    printf("\nEnd Of Parent Process.\n");
}
