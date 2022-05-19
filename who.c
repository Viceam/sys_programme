#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<utmp.h>
#include<stdlib.h>
#include<time.h>

# define SHOWHOST

void show_info(struct utmp *utbufd);
void show_time(long timeval);

int main()
{
    struct utmp current_record;
    int utmpfd;
    int reclen = sizeof(struct utmp);
    if((utmpfd = open(UTMP_FILE, O_RDONLY)) == -1)
    {
        perror(UTMP_FILE);
        exit(1);
    }

    while(read(utmpfd, &current_record, reclen) == reclen)
        show_info(&current_record);
    close(utmpfd);

    return 0;
}

void show_info(struct utmp *utbufd)
{
    if(utbufd->ut_type != USER_PROCESS)
        return;
    printf("%-8.8s", utbufd->ut_name);
    printf(" ");
    printf("%-8.8s", utbufd->ut_line);
    printf(" ");
    show_time(utbufd->ut_time);
    printf(" ");
# ifdef SHOWHOST
    if(utbufd->ut_host[0] != '\0')
        printf("(%s)", utbufd->ut_host);
# endif
    printf("\n");
}

void show_time(long timeval)
{
    char *cp;
    cp = ctime(&timeval);

    printf("%24.20s", cp + 4);
}