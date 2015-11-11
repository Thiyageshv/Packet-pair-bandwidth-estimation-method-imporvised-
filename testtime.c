#include <time.h>
#include <stdio.h>


int main(void)
{
    time_t mytime;
    mytime = time(NULL);
    strcpy(timedetail,ctime(&mytime));
    int s ;
    s=sizeof(timedetail);
    printf(ctime(&mytime));
    printf("%d",s);

    return 0;
}
