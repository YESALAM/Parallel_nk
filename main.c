#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void printA(int *a,int size){
    for(int i=0;i<size;i++)printf("%d  ",a[i]);
    printf("\n");
}

void prefixSum(int * in,int * out,int n){

    #pragma omp parallel for
    for(int i=1;i<n;i++){
        out[i] = in[i-1] + in[i];
    }

    printA(out,n);

    int k=2;
    int size = n-1;
    while(k<size){
        #pragma omp parallel for
        for(int i=k+1;i<n;i++){
            out[i] = out[i-k]+out[i];
        }

        k = 2*k ;
        printA(out,n);

    }
}



int main()
{
    int n = 7;
    int * a ;
    int * b;
    a = (int *) malloc(sizeof(int)*n);
    b = (int *) malloc(sizeof(int)*n);
    a[0] = 0;
    b[0] = 0;
    for(int i=1;i<n;i++){
        a[i] = i ;
    }

    printA(a,n);
    prefixSum(a,b,n);
    //printA(b,n);



    return 0;
}
