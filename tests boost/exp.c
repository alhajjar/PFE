#include <math.h>
#include <stdio.h>
#include <stdlib.h>


void main(){

long double theta;

long double alpha2;
long double num;
long double den;
long double petit;
long double grand;
int i;

for(i=0;i<30;i++){
den=coshl(i*i);
num=sinhl(i*i);

printf("%30.60lf\n\n",num/den);
}
}