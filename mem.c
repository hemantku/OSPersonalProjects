#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <assert.h>

double GetTime()
{
   struct timeval t;
   int rc = gettimeofday(&t, NULL);
   assert(rc == 0);
   return (double) t.tv_sec + (double) t.tv_usec/1e6;

}
void Spin(int howlong)
{
   double t = GetTime();
   while((GetTime() - t) < (double)howlong)
       ;
}
int main(int argc, char *argv[])
{
   int *p = malloc(sizeof(int));
   assert(p != NULL);
   printf("(%d) Memory address of p: %08x\n", getpid(), (unsigned) p);
   *p = 0;
   
   while(1){
      Spin(1);
      *p = *p + 1;
      printf("(%d) p: %d\n", getpid(), *p);
   }
   return 0;
}
