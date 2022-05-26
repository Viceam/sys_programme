#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<utmp.h>
#include<stdlib.h>
#include<time.h>
#include "utmp.h"

# define SHOWHOST

void show_info(struct utmp *utbufp);
void show_time(long timeval);

int main()
{
    struct utmp* utbufp;
    if(utmp_open(UTMP_FILE) == -1)
    {
        perror(UTMP_FILE);
        exit(1);
    }
    
    while((utbufp = utmp_next()) != (struct utmp*)NULL)
        show_info(utbufp);
        
    utmp_close();
    return 0;
}

void show_info(struct utmp *utbufp)
{
    if(utbufp->ut_type != USER_PROCESS)
        return;
    printf("%-8.8s", utbufp->ut_name);
    printf(" ");
    printf("%-8.8s", utbufp->ut_line);
    printf(" ");
    show_time(utbufp->ut_time);
    printf(" ");
# ifdef SHOWHOST
    if(utbufp->ut_host[0] != '\0')
        printf("(%s)", utbufp->ut_host);
# endif
    printf("\n");
}

void show_time(long timeval)
{
    char *cp;
    cp = ctime(&timeval);

    printf("%24.20s", cp + 4);
}