#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>

#define BUFFERSIZE 4096
#define COPYMOCE 0644

void oops(char *, char *);

int main(int argc, char *argv[])
{
    char buf[BUFFERSIZE];
    int in_fd, out_fd, n_chars;
    if(argc != 3)
        oops("Cannot match.", "");
    
    if((in_fd = open(argv[1], O_RDONLY)) < 0)
        oops("Cannot open", "");
    
    if((out_fd = creat(argv[2], COPYMOCE)) == -1)
        oops("Cannot creat.", "");

    while((n_chars = read(in_fd, buf, BUFFERSIZE)) > 0)
        if((n_chars = write(out_fd, buf, n_chars)) != n_chars)
            oops("Write error to", argv[2]);
    
    if(n_chars == -1)
        oops("Read error from", argv[1]);

    if(close(in_fd) == -1 || close(out_fd) == -1)
        oops("Error closing files", "");

    return 0;
}

void oops(char *s1, char *s2)
{
    fprintf(stderr, "Error: %s", s1);
    perror(s2);
    exit(1);
}