#include<pthread.h>
#include<stdio.h>
#include<unistd.h>
#include<math.h>
#include<stdlib.h>
struct Thread{
	float t1;
	float t2;
	float t3;
	float t4;
	float t5;
	float a;
	float b;
}T;

struct Variable{
	float a;
	float b;
	float c;
	float A;
	float B;
}var;


void *S1(void *arg){
	struct Variable *ptr=(struct Variable *) arg;
	float *square=(float*)malloc(sizeof(float));
	float b=ptr->b;
	*square=b*b;
//	printf("%f\n",square);
	return (void*) square;
}
void *S2(void *arg){
	struct Variable *ptr=(struct Variable *) arg;
	float *square=(float*)malloc(sizeof(float));
	float c=ptr->c;
	*square=c*c;
//	printf("%f\n",square);
	return (void*) square;
}
void *S3(void *arg){
	float *mul=(float*)malloc(sizeof(float));
	struct Variable *ptr=(struct Variable *) arg;
	float b=ptr->b;
	float c=ptr->c;
	*mul=2*b*c;
//	printf("%f\n",mul);
	return (void*) mul;
}
void *S4(void *arg){
	struct Thread *ptr=(struct Thread *) arg;
	float *mul=(float*)malloc(sizeof(float));
	float a=ptr->a;
	float b=ptr->t3;
	a=(a*3.142)/180;
	*mul=b*cos(a);
//	printf("%f\n",mul);
	return (void*) mul;
}
void *S5(void *arg){
	struct Thread *ptr=(struct Thread *) arg;
	float *add=(float*)malloc(sizeof(float));
	float a=ptr->t1;
	float b=ptr->t2;
	float c=ptr->t4;
	*add=a+b-c;
//	printf("%f\n",add);
	return (void*) add;
}
void *S6(void *arg){
	struct Thread *ptr=(struct Thread *) arg;
	float a=ptr->t5;
	float *result=(float*)malloc(sizeof(float));
	*result=sqrtf(a);
//	printf("%f\n",result);
	return (void*) result;
}
void *S7(void *arg){
	struct Variable *ptr=(struct Variable *) arg;
	float *mul=(float*)malloc(sizeof(float));
	float a=ptr->a;
	*mul=a*a;
	return (void*) mul; 
}
void *S8(void *arg){
	struct Thread *ptr=(struct Thread *) arg;
	float *result=(float*)malloc(sizeof(float));
	float a=ptr->t1;
	float b=ptr->t2;
	float c=ptr->t3;
	float d=ptr->t4;
	*result=(d-a-b)/-c;
	return (void*) result;
}
void *S9(void *arg){
	struct Thread *ptr=(struct Thread *) arg;
	float *result=(float*)malloc(sizeof(float));
	float a=ptr->t5;
	*result=acos(a)*180/3.142;
	return (void*) result;
}