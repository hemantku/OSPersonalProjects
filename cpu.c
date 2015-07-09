#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <assert.h>

double Gettime(){
    struct timeval t;
    int rc = gettimeofday(&t, NULL);
    assert(rc == 0);
    return (double) t.tv_sec + (double)t.tv_usec/1e6;
}

void Spin(int howlong){
    double t = Gettime();
    while((Gettime() - t) < (double)howlong)
        ;
}

int main(int argc, char *argv[])
{
    if(argc != 2){
        fprintf(stderr, "Usage: CPU <string>\n");
        exit(0);
     }
     char *str = argv[1];
     while(1){
        Spin(1);
        printf("%s\n", str); 
     }
     return 0;
}
