#include<stdio.h>
#include<stdlib.h>

enum
{
    PAGELEN = 24,
    LINELEN = 512
};

void do_more(FILE *);
int see_more(FILE *);

int main(int argc, char *argv[])
{
    FILE *fp;
    if (argc == 1)
        do_more(stdin);
    else 
    {
        while(--argc)
        {
            if(fp = fopen(*++argv, "r"))
            {
                do_more(fp);
                fclose(fp);
            }
            else
                exit(1);
        }
    }
}

//read and display
void do_more(FILE *fp)
{
    char line[LINELEN];
    int nums_of_lines = 0;
    int ret = 0; //see_more返回值
    FILE *fp_tty = NULL;
    fp_tty = fopen("/dev/tty", "r");
    if(fp_tty == NULL)
        exit(1);
    while (fgets(line, LINELEN, fp))
    {
        if(nums_of_lines == PAGELEN)
        {
            ret = see_more(fp_tty);
            if(!ret)
                break;
            nums_of_lines -= ret;
        }
        if(fputs(line, stdout) == EOF)
            exit(1);
        ++nums_of_lines;
    }
}

int see_more(FILE *fp)
{
    char ch;
    printf("\033[7m more?\033[m");
    while((ch = getc(fp)) != EOF)
    {
        if(ch == 'q')
            return 0;
        if(ch == ' ')
            return PAGELEN;
        if(ch == '\n')
            return 1;
    }
    return 0;
}