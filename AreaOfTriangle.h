#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<math.h>
void* F1(void* arg){
	struct Variable *ptr=(struct Variable *) arg;
	float* square=(float*)malloc(sizeof(float));
	float a=ptr->a;
	float b=ptr->b;
	*square=a*b;
	return (void*) square;
}
void* F2(void* arg){
	struct Variable* ptr=(struct Variable *) arg;
	float* mul=(float*)malloc(sizeof(float));
	float c=ptr->c;
	c=c*PI/180;
	*mul=sin(c);
	return (void*) mul;
}
void* F3(void* arg){
	struct Thread* ptr=(struct Thread *) arg;
	float* mul=(float*)malloc(sizeof(float));
	float a=ptr->t1;
	float b=ptr->t2;
	*mul=a*b;
	return (void* ) mul;
}
void* F4(void* arg){
	struct Thread* ptr=(struct Thread *) arg;
	float* mul=(float*)malloc(sizeof(float));
	float a=ptr->t3;
	*mul=0.5*a;
	return (void *) mul;
}