#ifndef __UTMP__
#define __UTMP__

int utmp_open(char *filename);
struct utmp* utmp_next();
void utmp_close();

#endif
