#include<stdio.h>
#include<unistd.h>
#include<math.h>
#include<pthread.h>
#include<stdlib.h>

const double PI =  3.1415926;
void* A1(void* arg){
	struct Variable* ptr=(struct Variable *) arg;
	float* mul=(float*)malloc(sizeof(float));
	float a=ptr->A;
	a=a*PI/180;
	*mul=sin(a);
	return (void *) mul;
}
void* A2(void* arg){
	struct Variable* ptr=(struct Variable *) arg;
	float* mul=(float*)malloc(sizeof(float));
	float a=ptr->B;
	a=a*PI/180;
	*mul=sin(a);
	return (void* ) mul;
}
void* A3(void* arg){
	struct Thread* ptr2=(struct Thread *) arg;
	float* mul=(float*)malloc(sizeof(float));
	float a=ptr2->a;
	float b=ptr2->t1;
	*mul=a*b;
	return (void* ) mul;
}
void* A4(void* arg){
	//struct Variable* ptr=(struct Variable *) arg;
	struct Thread* ptr2=(struct Thread *) arg;
	float* mul=(float*)malloc(sizeof(float));
	float a=ptr2->t3;
	float b=ptr2->t2;
	*mul=a/b;
	return (void*) mul;
}
void* A5(void* arg){
	struct Thread* ptr2=(struct Thread *) arg;
	float* mul=(float*)malloc(sizeof(float));
	float a=ptr2->t2;
	float b=ptr2->b;
	*mul=a/b;
	return (void* ) mul;
}
void* A6(void* arg){
	struct Thread* ptr=(struct Thread *) arg;
	float* mul=(float*)malloc(sizeof(float));
	float a=ptr->t3;
	*mul=asin(a)*180/PI;
	return (void* ) mul;
}