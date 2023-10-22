#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include<pthread.h>
#include"CosineRule.h"
#include"SineRule.h"
#include"AreaOfTriangle.h"
char equation[100];
pthread_mutex_t mutex;
char der[6];
void input() {
	printf("Enter the equation (at the end enter comma): ");
	fgets(equation, 100, stdin);
	//printf("%s", equation);
	printf("\nThe derivative of the following equation is\n");

}
char* concats(const char* str, int num) {
	char int_str[50];
	sprintf(int_str, "%d", num);

	size_t len1 = strlen(str);
	size_t len2 = strlen(int_str);

	char* result = malloc(len1 + len2 + 1);
	if (result == NULL) {
		fprintf(stderr, "Error: Failed to allocate memory for result.\n");
		exit(1);
	}

	memcpy(result, str, len1);
	memcpy(result + len1, int_str, len2 + 1);

	return result;
}
char* concat(int num, const char* str) {
	char int_str[50];
	sprintf(int_str, "%d", num);

	size_t len1 = strlen(int_str);
	size_t len2 = strlen(str);

	char* result = malloc(len1 + len2 + 1);
	if (result == NULL) {
		fprintf(stderr, "Error: Failed to allocate memory for result.\n");
		exit(1);
	}

	memcpy(result, int_str, len1);
	memcpy(result + len1, str, len2 + 1);

	return result;
}
char single_derivative(char term[],int out) {
	int coefficient = 0;
	int power = 0;
	int sign = 1;
	int i = 0;
	int t=1;
	char trig[3];
	char* result;
	// Check if the term has a sign
    if (term[i] == '+' || term[i] == '-') {
        if (term[i] == '-') {
            sign = -1;
        }
        i++;
    }

//     Parse the coefficient

	while (term[i] >= '0' && term[i] <= '9') {
		coefficient = coefficient * 10 + (term[i] - '0');
		i++;
	}
	if(coefficient==0)
		coefficient=1;
	// Apply the sign to the coefficient
	coefficient *= sign;

	// Check if the term has a variable
	if (term[i] == 'x') {
		i++;

		// Check if the variable has a power
		if (term[i] == '^') {
			i++;
			// Parse the power
			if(term[i]=='-') {
				t=-1;
				i++;
			}
			power = atoi(term + i);
		} else {
			power = 1;
		}
		power=power*t;
		
		coefficient=coefficient*power;
		power--;
		
		result=concat(coefficient,"x^");
		result=concats(result,power);

	}


	if(term[i]== 's' && term[i+1]=='i' && term[i+2]=='n') {
		trig[0]='c';
		trig[1]='o';
		trig[2]='s';
		trig[3]='x';

		//	printf("%d%sx",coefficient,trig);
		result=concat(coefficient,trig);
	}
	if(term[i]== 'c' && term[i+1]=='o' && term[i+2]=='s') {
		trig[0]='s';
		trig[1]='i';
		trig[2]='n';
		trig[3]='x';
		coefficient=coefficient*-1;
		//	printf("%d%sx",coefficient,trig);
		result=concat(coefficient,trig);
	}
	for(int i=0; i<strlen(result); i++) {
		term[i]=result[i];
		der[i]=result[i];
	}
	if(out==1)
		printf("%s + ",result);
	return result;
}
void* thread_func(void *arg) {
//	pthread_mutex_lock(&mutex);
	pthread_mutex_lock(&mutex);
	int pow,con;
	char a[3],b[3];
	char *term = (char *) arg;
//	printf("hello %s ", term);
//int coefficient = 0;
  
  
	single_derivative(term,1);
	pthread_mutex_unlock(&mutex);
	return NULL;
}

int derivative_2(char term[]) {
	int power;
	int sign=1;
	int i=0,j=0;
	int coefficient=0;
	int t=1;
	char u[10],v[10],uu[10],vv[10];
	for(int i=0; i<strlen(u); i++) {
		u[i]="";
		uu[i]="";
	}
	for(int i=0; i<strlen(v); i++) {
		v[i]="";
		vv[i]="";
	}


 if (term[i] == '+' || term[i] == '-') {
        if (term[i] == '-') {
            sign = -1;
        }
        i++;
    }
	while (term[i] >= '0' && term[i] <= '9') {
		coefficient = coefficient * 10 + (term[i] - '0');
		i++;
	}
//		printf("%d",coefficient);
	if(coefficient==0)
		coefficient=1;
//    coefficient *= sign;
	coefficient *= sign;
	if (term[i] == 'x') {
		u[j]=term[i];
		i++;
		j++;
		// Check if the variable has a power
		if (term[i] == '^') {
			u[j]=term[i];
			i++;
			j++;
			// Parse the power
			if(term[i]=='-') {
				u[j]=term[i];
				t=-1;
				i++;
				j++;
			}
			while (term[i] >= '0' && term[i] <= '9') {
				u[j]=term[i];
				//		printf("%c %c",u[i],term[i]);
				power = power * 10 + (term[i] - '0');
				i++;
				j++;
			}
		} else {
			power = 1;
		}

		//      printf("%d",power);
		power=power*t;
		if(term[i]== 's' && term[i+1]=='i' && term[i+2]=='n') {
			v[0]='s';
			v[1]='i';
			v[2]='n';
			v[3]='x';
			//	printf("hello %s \n", v);
		}
		if(term[i]== 'c' && term[i+1]=='o' && term[i+2]=='s') {
			v[0]='c';
			v[1]='o';
			v[2]='s';
			v[3]='x';
			//d=-1;
		}

		for(int i=0; i<strlen(u); i++) {
			uu[i]=u[i];
		}
		for(int i=0; i<strlen(v); i++) {
			vv[i]=v[i];
		}
//	printf("u= %s\n",uu);
//	printf("v= %s\n",vv);
//	char* du=u;
		char dv[10],du[10];
// strcpy(dv,"");
//  strcpy(du,"");
// for(int i=0;i<strlen(du);i++){
//		du[i]="";
//		dv[i]="";
//}
int su=coefficient;
int ssu=power;
int ki=0,kii=0;
	for(int z=0;z<10;z++){
		ki++;
			su=su/10;
			if(su<1){
				break;
			}
		
	}
	for(int z=0;z<10;z++){
		kii++;
			ssu=ssu/10;
			if(ssu<1){
				break;
			}
		
	}
	int size=kii+ki+2;

		single_derivative(u,0);
//	char* dv=v;
		strcpy(du,der);
		single_derivative(v,0);
		strcpy(dv,der);
//	printf("u= %s\n",u);
//	printf("du= %s\n",du);
//	printf("v= %s\n",v);
//	printf("dv= %s\n",dv);
//

		printf("%d((",coefficient);
		for(int i=0; i<strlen(du); i++) {
			printf("%c",du[i]);
		}
		printf(" ");
		for(int i=0; i<4; i++) {
			printf("%c",vv[i]);
		}
		printf(") + (");
		for(int i=0; i<strlen(dv); i++) {
			printf("%c",dv[i]);
		}
		printf(" ");
		for(int i=0; i<size; i++) {
			printf("%c",uu[i]);
		}
		printf(")) + ");


	}
	return 0;

}
void* thread_func_2(void *arg) {

	pthread_mutex_lock(&mutex);
	int pow,con;
	char a[3],b[3];
	char *term = (char *) arg;

	derivative_2(term);
	pthread_mutex_unlock(&mutex);
	return NULL;
}

void derivative() {
	int no=0;
	for(int i=0; i<strlen(equation); i++) {
		if(equation[i]=='+' || equation[i]=='-') {
			no++;
		}
	}

//'	pthread_t t[no+1];
	pthread_t t1,t2;
	char a[17];
	int j = 0;
	int flag=0;
	for(int i=0; i<strlen(equation); i++) {
		if(equation[i]=='+' || (equation[i]=='-' && equation[i-1]!='^') || equation[i]==',') {
			a[j] = '\0';
			flag=0;
			int k=0;
			while(1) {
				//		printf(" this %c ",equation[k]);
				if(a[k]=='x') {
					flag++;
				}
				if(k==j) {
					break;
				}
				k++;
			}
			if(flag==2) {
				//		printf(" this is %s  \n",a);
				pthread_create(&t1, NULL, &thread_func_2, a);
				pthread_join(t1, NULL);
			} else {
				//	printf(" this is %s  \n",a);
				//	printf("24\n");
				pthread_create(&t2, NULL, &thread_func, a);
				pthread_join(t2, NULL);
				//	printf("\nout\n");
			}
			a[0]=equation[i];
			j=1;
		} else {
			a[j] = equation[i];
			//	printf("%c  %c ",equation[i],a[j]);
			j++;
		}
	}
	
//	a[j] = '\0';
//	pthread_create(&t[j], NULL, &thread_func, a);
//	pthread_join(t[j], NULL);
}//-----------------------------------------------------------------------
pthread_mutex_t lock;
struct queue {
	double eq1[100];
	double eq2[100];
	double f1;
	double f2;
	int end1;
	int end2;
	char rear[100];
} q ;

struct ThreadData
{
	double c;
	double e;
	double ans;
};


void formfunc(float *a,float *b)
{
	int k=0;
	int g=0;
	if(q.end2==0)
	{
	//	printf("\nError: operator Missing\n");
	}
	while(k!=q.end2)
	{
		int i;
		int j;
			if(q.rear[k]=='+')
			{
				q.eq1[g+1]=q.eq1[g]+q.eq1[g+1];
				q.eq2[g+1]=q.eq2[g]+q.eq2[g+1];
				k=k+1;
				g=g+1;
			}
			else if(q.rear[k]=='-')
			{
				q.eq1[g+1]=q.eq1[g]-q.eq1[g+1];
				q.eq2[g+1]=q.eq2[g]-q.eq2[g+1];
				k=k+1;
				g=g+1;
			}
			else if(q.rear[k]=='*')
			{
				q.eq1[g+1]=q.eq1[g]*q.eq1[g+1];
				q.eq2[g+1]=q.eq2[g]*q.eq2[g+1];
				k=k+1;
				g=g+1;
			}
			else if(q.rear[k]=='/')
			{
				q.eq1[g+1]=q.eq1[g]/q.eq1[g+1];
				q.eq2[g+1]=q.eq2[g]/q.eq2[g+1];
				k=k+1;
				g=g+1;
			}
			else if(q.rear[k]=='^')
			{               
				q.eq1[g+1]=pow(q.eq1[g],q.eq1[g+1]);
				q.eq2[g+1]=pow(q.eq2[g],q.eq2[g+1]);
				g=g+1;
				k=k+1;
			}
			else	
			{
				k=k+1;
	
			}
	}
	q.f1=q.eq1[g];
	q.f2=q.eq2[g];
	printf("f(%.1f)=%f\n",*a,q.f1);
	printf("f(%.1f)=%f\n",*b,q.f2);
}

int *integrate(void *arg)
{
	struct ThreadData *d=(struct ThreadData*)arg;
	pthread_mutex_init(&lock,0);
	
	pthread_mutex_lock(&lock);
	double t1=d->e-d->c;
	pthread_mutex_unlock(&lock);
	
	pthread_mutex_lock(&lock);
	double t2=q.f1+q.f2;
	pthread_mutex_unlock(&lock);
	
	double t3=t1*t2;
	double t4=t3/2;
	
	d->ans=t4;
	
	pthread_mutex_destroy(&lock);
}

void converting(char *exp,float *a,float *b)
{

	int i=0;
	int j=0;
	int z=0;
	while(exp[i]!='~')
	{	
		if(exp[i]=='+'||exp[i]=='-'||exp[i]=='*'||exp[i]=='/')
		{
			q.rear[z]=exp[i];
			z=z+1;
			i=i+1;
		}
		else if(exp[i]=='s')
		{
			q.eq1[j]=sin(*a);
			q.eq2[j]=sin(*b);
			j=j+1;
			i=i+6;
		}
		else if(exp[i]=='c')
		{
			q.eq1[j]=cos(*a);
			q.eq2[j]=cos(*b);
			j=j+1;
			i=i+6;

		}
		else if(exp[i]=='t')
		{
			q.eq1[j]=tan(*a);
			q.eq2[j]=tan(*b);
			j=j+1;
			i=i+6;
		}
		else if(exp[i]=='l')
		{
			q.eq1[j]=log(*a);
			q.eq2[j]=log(*b);
			j=j+1;
			i=i+6;
		}
		else if(exp[i]=='^')
		{
			q.rear[z]=exp[i];
			z=z+1;
			i=i+1;

		}
		else if(exp[i]==' ')
		{
		}		
		else if(exp[i]>='0' && exp[i]<='9')
		{
			switch(exp[i])
			{
				case '1':
					if(exp[i+1]>='0' && exp[i+1]<='9')
					{
						switch(exp[i])
						{
							case '1':
								q.eq1[j]=11;
								q.eq2[j]=11;
								j=j+1;
								i=i+1;	
								break;
							case '0':
								q.eq2[j]=10;
								q.eq1[j]=10;
								j=j+1;
								i=i+1;	
								break;
							case '2':
								q.eq1[j]=12;
								q.eq2[j]=12;
								j=j+1;
								i=i+1;	
								break;
							case '3':
								q.eq2[j]=13;
								q.eq1[j]=13;
								j=j+1;
								i=i+1;	
								break;
							case '4':
								q.eq2[j]=14;
								q.eq1[j]=14;
								j=j+1;
								i=i+1;	
								break;
							case '5':
								q.eq2[j]=15;
								q.eq1[j]=15;
								j=j+1;
								i=i+1;	
								break;
							case '6':
								q.eq2[j]=16;
								q.eq1[j]=16;
								j=j+1;
								i=i+1;	
								break;
							case '7':
								q.eq2[j]=17;
								q.eq1[j]=17;
								j=j+1;
								i=i+1;	
								break;
							case '8':
								q.eq2[j]=18;
								q.eq1[j]=18;
								j=j+1;
								i=i+1;	
								break;
							case '9':
								q.eq2[j]=19;
								q.eq1[j]=19;
								j=j+1;
								i=i+1;
								break;									
						}
					}
					else
					{
					q.eq2[j]=1;
					q.eq1[j]=1;
					j=j+1;
					i=i+1;	
					}
					break;
				case '0':
					q.eq2[j]=0;
					q.eq1[j]=0;
					j=j+1;
					i=i+1;	
					break;
				case '2':
					if(exp[i+1]>='0' && exp[i+1]<='9')
					{
						switch(exp[i])
						{
							case '1':
								q.eq2[j]=21;
								q.eq1[j]=21;
								j=j+1;
								i=i+1;	
								break;
							case '0':
								q.eq2[j]=20;
								q.eq1[j]=20;
								j=j+1;
								i=i+1;	
								break;
							case '2':
								q.eq2[j]=22;
								q.eq1[j]=22;
								j=j+1;
								i=i+1;	
								break;
							case '3':
								q.eq2[j]=23;
								q.eq1[j]=23;
								j=j+1;
								i=i+1;	
								break;
							case '4':
								q.eq2[j]=24;
								q.eq1[j]=24;
								j=j+1;
								i=i+1;	
								break;
							case '5':
								q.eq2[j]=25;
								q.eq1[j]=25;
								j=j+1;
								i=i+1;	
								break;
							case '6':
								q.eq2[j]=26;
								q.eq1[j]=26;
								j=j+1;
								i=i+1;	
								break;
							case '7':
								q.eq2[j]=27;
								q.eq1[j]=27;
								j=j+1;
								i=i+1;	
								break;
							case '8':
								q.eq2[j]=28;
								q.eq1[j]=28;
								j=j+1;
								i=i+1;	
								break;
							case '9':
								q.eq2[j]=29;
								q.eq1[j]=29;
								j=j+1;
								i=i+1;
								break;									
						}
					}
					else
					{
					q.eq2[j]=2;
					q.eq1[j]=2;
					j=j+1;
					i=i+1;	
					}
					break;
				case '3':
					if(exp[i+1]>='0' && exp[i+1]<='9')
					{
						switch(exp[i])
						{
							case '1':
								q.eq2[j]=31;
								q.eq1[j]=31;
								j=j+1;
								i=i+1;	
								break;
							case '0':
								q.eq2[j]=30;
								q.eq1[j]=30;
								j=j+1;
								i=i+1;	
								break;
							case '2':
								q.eq2[j]=32;
								q.eq1[j]=32;
								j=j+1;
								i=i+1;	
								break;
							case '3':
								q.eq2[j]=33;
								q.eq1[j]=33;
								j=j+1;
								i=i+1;	
								break;
							case '4':
								q.eq2[j]=34;
								q.eq1[j]=34;
								j=j+1;
								i=i+1;	
								break;
							case '5':
								q.eq2[j]=35;
								q.eq1[j]=35;
								j=j+1;
								i=i+1;	
								break;
							case '6':
								q.eq2[j]=36;
								q.eq1[j]=36;
								j=j+1;
								i=i+1;	
								break;
							case '7':
								q.eq2[j]=37;
								q.eq1[j]=37;
								j=j+1;
								i=i+1;	
								break;
							case '8':
								q.eq2[j]=38;
								q.eq1[j]=38;
								j=j+1;
								i=i+1;	
								break;
							case '9':
								q.eq2[j]=39;
								q.eq1[j]=39;
								j=j+1;
								i=i+1;
								break;									
						}
					}
					else
					{
					q.eq2[j]=3;
					q.eq1[j]=3;
					j=j+1;
					i=i+1;	
					}	
					break;
				case '4':
					if(exp[i+1]>='0' && exp[i+1]<='9')
					{
						switch(exp[i])
						{
							case '1':
								q.eq2[j]=41;
								q.eq1[j]=41;
								j=j+1;
								i=i+1;	
								break;
							case '0':
								q.eq2[j]=40;
								q.eq1[j]=40;
								j=j+1;
								i=i+1;	
								break;
							case '2':
								q.eq2[j]=42;
								q.eq1[j]=42;
								j=j+1;
								i=i+1;	
								break;
							case '3':
								q.eq2[j]=43;
								q.eq1[j]=43;
								j=j+1;
								i=i+1;	
								break;
							case '4':
								q.eq2[j]=44;
								q.eq1[j]=44;
								j=j+1;
								i=i+1;	
								break;
							case '5':
								q.eq2[j]=45;
								q.eq1[j]=45;
								j=j+1;
								i=i+1;	
								break;
							case '6':
								q.eq2[j]=46;
								q.eq1[j]=46;
								j=j+1;
								i=i+1;	
								break;
							case '7':
								q.eq2[j]=47;
								q.eq1[j]=47;
								j=j+1;
								i=i+1;	
								break;
							case '8':
								q.eq2[j]=48;
								q.eq1[j]=48;
								j=j+1;
								i=i+1;	
								break;
							case '9':
								q.eq2[j]=49;
								q.eq1[j]=49;
								j=j+1;
								i=i+1;
								break;									
						}
					}
					else
					{
					q.eq2[j]=4;
					q.eq1[j]=4;
					j=j+1;
					i=i+1;	
					}
					break;
				case '5':
					if(exp[i+1]>='0' && exp[i+1]<='9')
					{
						switch(exp[i])
						{
							case '1':
								q.eq2[j]=51;
								q.eq1[j]=51;
								j=j+1;
								i=i+1;	
								break;
							case '0':
								q.eq2[j]=50;
								q.eq1[j]=50;
								j=j+1;
								i=i+1;	
								break;
							case '2':
								q.eq2[j]=52;
								q.eq1[j]=52;
								j=j+1;
								i=i+1;	
								break;
							case '3':
								q.eq2[j]=53;
								q.eq1[j]=53;
								j=j+1;
								i=i+1;	
								break;
							case '4':
								q.eq2[j]=54;
								q.eq1[j]=54;
								j=j+1;
								i=i+1;	
								break;
							case '5':
								q.eq2[j]=55;
								q.eq1[j]=55;
								j=j+1;
								i=i+1;	
								break;
							case '6':
								q.eq2[j]=56;
								q.eq1[j]=56;
								j=j+1;
								i=i+1;	
								break;
							case '7':
								q.eq2[j]=57;
								q.eq1[j]=57;
								j=j+1;
								i=i+1;	
								break;
							case '8':
								q.eq2[j]=58;
								q.eq1[j]=58;
								j=j+1;
								i=i+1;	
								break;
							case '9':
								q.eq2[j]=59;
								q.eq1[j]=59;
								j=j+1;
								i=i+1;
								break;									
						}
					}
					else
					{
					q.eq2[j]=5;
					q.eq1[j]=5;
					j=j+1;
					i=i+1;	
					}	
					break;
				case '6':
					if(exp[i+1]>='0' && exp[i+1]<='9')
					{
						switch(exp[i])
						{
							case '1':
								q.eq2[j]=61;
								q.eq1[j]=61;
								j=j+1;
								i=i+1;	
								break;
							case '0':
								q.eq2[j]=60;
								q.eq1[j]=60;
								j=j+1;
								i=i+1;	
								break;
							case '2':
								q.eq2[j]=62;
								q.eq1[j]=62;
								j=j+1;
								i=i+1;	
								break;
							case '3':
								q.eq2[j]=63;
								q.eq1[j]=63;
								j=j+1;
								i=i+1;	
								break;
							case '4':
								q.eq2[j]=64;
								q.eq1[j]=64;
								j=j+1;
								i=i+1;	
								break;
							case '5':
								q.eq2[j]=65;
								q.eq1[j]=65;
								j=j+1;
								i=i+1;	
								break;
							case '6':
								q.eq2[j]=66;
								q.eq1[j]=66;
								j=j+1;
								i=i+1;	
								break;
							case '7':
								q.eq2[j]=67;
								q.eq1[j]=67;
								j=j+1;
								i=i+1;	
								break;
							case '8':
								q.eq2[j]=68;
								q.eq1[j]=68;
								j=j+1;
								i=i+1;	
								break;
							case '9':
								q.eq2[j]=69;
								q.eq1[j]=69;
								j=j+1;
								i=i+1;
								break;									
						}
					}
					else
					{
					q.eq2[j]=6;
					q.eq1[j]=6;
					j=j+1;
					i=i+1;	
					}
					break;
				case '7':
					q.eq2[j]=7;
					q.eq1[j]=7;
					j=j+1;
					i=i+1;	
					break;
				case '8':
					q.eq2[j]=8;
					q.eq1[j]=8;
					j=j+1;
					i=i+1;	
					break;
				case '9':
					q.eq2[j]=9;
					q.eq1[j]=9;
					j=j+1;
					i=i+1;
					break;									
			}
		}
		else if(exp[i]=='x')
		{

			q.eq1[j]=*a;
			q.eq2[j]=*b;
			j=j+1;
			i=i+1;
		}
		else if(exp[i]=='~')
		{
			q.end1=j-1;
			q.end2=z;
		}
		else
		{
			printf("Error: Function can not be recognized\n");
			i=i+1;
			break;
		
		}
	}
	q.end1=j-1;
	q.end2=z;
	float f=*a;
	float g=*b;
	formfunc(&f,&g);

}


int main()
{
	char in;
	starting:	
	fflush(stdin);
	ab:
	printf("1)  trignometric functions \n2)  Integration\n3)  Derivative\n4)  Exit\n");
	printf("Option:");
	scanf("%c",&in);
	if(in=='1'){//-----------------------------------
		char num;
	pthread_t p1,p2,p3,p4,p5,p6;
	float *T1,*T2,*T3,*T4,*T5,*T6;
	printf("Welcome to the Advanced Electronic Calculator!\n");
	choose:
	printf("1)Find Area of Triangle\n2)Find Side of Triangle\n3)Find Angle of triangle\n4)Exit\n");
	printf("Option:");
	scanf("%c",&num);
	system("cls");
	if(num=='1'){
	float a,b,c;
	printf("Enter Side 1: ");
	scanf("%f",&a);
	printf("Enter Side 2: ");
	scanf("%f",&b);
	printf("Enter Angle: ");
	scanf("%f",&c);
	var.a=a;
	var.b=b;
	var.c=c;
	pthread_create(&p1,NULL,F1,&var);
	pthread_join(p1,(void**)&T1);
	pthread_create(&p2,NULL,F2,&var);
	pthread_join(p2,(void**)&T2);
	T.t1=*T1;
	T.t2=*T2;
	pthread_create(&p3,NULL,F3,&T);
	pthread_join(p3,(void**)&T3);
	T.t3=*T3;
	pthread_create(&p4,NULL,F4,&T);
	pthread_join(p4,(void**)&T4);
	printf("Area of triangle is: %.2f",*T4);
	}else if(num=='2'){
		printf("To Calculate the side of a triangle you must know either the two other sides and one angle or on side and two angles of the triangle.\n");
		printf("1)2 sides and 1 angle(cosine rule)\n2)1 side and two angles(sine rule)\n");
		printf("Option:");
		char n;
		choice:
		scanf("%c",&n);
		if(n=='1'){
			float a,b,c;
			printf("Enter Angle of the unknown side: ");
			scanf("%f",&a);
			printf("Enter side 1: ");
			scanf("%f",&b);
			printf("Enter side 2: ");
			scanf("%f",&c);	
			var.A=a;
			var.b=b;
			var.c=c;
			T.a=var.A;	
			pthread_create(&p1,NULL,S1,&var);
			pthread_join(p1,(void**) &T1);
//			printf("%f\n",*T1);
			
			pthread_create(&p2,NULL,S2,&var);
			pthread_join(p2,(void**) &T2);
//			printf("%f\n",*T2);
			
			pthread_create(&p3,NULL,S3,&var);
			pthread_join(p3,(void**) &T3);
//			printf("%f\n",*T3);
			
			T.t1= *T1;
			T.t2= *T2;
			T.t3= *T3;
					
			pthread_create(&p4,NULL,S4,&T);
			pthread_join(p4,(void**) &T4);
//			printf("%f\n",*T4);
			
			T.t4= *T4;
			
			pthread_create(&p5,NULL,S5,&T);
			pthread_join(p5,(void**) &T5);
//			printf("%f\n",*T5);
			
			T.t5= *T5;
			
			pthread_create(&p6,NULL,S6,&T);
			pthread_join(p6,(void**) &T6);
			
			printf("Value of side is : %.2f\n", *T6);
		}else if(n=='2'){
			float a,b,c;
			printf("Enter Known Side: ");
			scanf("%f",&a);
			printf("Enter Angle of unknown side(in degrees): ");
			scanf("%f",&b);
			printf("Enter Angle of known side(in degrees): ");
			scanf("%f",&c);
			var.a=a;
			var.A=b;
			var.B=c;
			pthread_create(&p1,NULL,A1,&var);
			pthread_join(p1,(void**)&T1);
			pthread_create(&p2,NULL,A2,&var);
			pthread_join(p2,(void**)&T2);
			T.a=a;
			T.t1=*T1;
			T.t2=*T2;
			pthread_create(&p3,NULL,A3,&T);
			pthread_join(p3,(void**)&T3);
			T.t3=*T3;
			pthread_create(&p4,NULL,A4,&T);
			pthread_join(p4,(void**)&T4);
			printf("Value of remaining side is: %.2f",*T4);
			}else{
				goto choice;
			}
	}else if(num=='3'){
		printf("To find the angle of a triangle, it is important to know at least one angle and 2 sides or 3 sides of the triangle\n");
		printf("1)1 Angle 2 sides(sine rule)\n2)3 sides(cosine rule)");
		char x;
		choice2:
		printf("Option:");
			
		if(x=='1'){
		float a,b,c;
		printf("Enter the Side whos angle u want to calculate: ");
		scanf("%f",&a);
		printf("Enter Side 2: ");
		scanf("%f",&b);
		printf("Enter the known Angle which is the angle belonging to side 2(in degrees): ");
		scanf("%f",&c);
		var.a=a;
		var.b=b;
		var.A=c;
		pthread_create(&p1,NULL,A1,&var);
		pthread_join(p1,(void**)&T1);
		T.a=a;
		T.t1=*T1;
		pthread_create(&p2,NULL,A3,&T);
		pthread_join(p2,(void**)&T2);
		T.b=b;
		T.t2=*T2;
		pthread_create(&p3,NULL,A5,&T);
		pthread_join(p3,(void**)&T3);
		T.t3=*T3;
		pthread_create(&p4,NULL,A6,&T);
		pthread_join(p4,(void**)&T4);
		printf("Value of remaining angle is: %.2f",*T4);
		}else if(x=='2'){
			float a,b,c;
			printf("Enter the side whos angle u want to calculate first: ");
			scanf("%f",&a);
			printf("Enter side 2: ");
			scanf("%f",&b);
			printf("Enter side 3: ");
			scanf("%f",&c);	
			var.a=a;
			var.b=b;
			var.c=c;
			float *T1,*T2,*T3,*T4,*T5,*T6;	
			pthread_create(&p1,NULL,S1,&var);
			pthread_join(p1,(void**) &T1);
//			printf("%f\n",*T1);
			
			pthread_create(&p2,NULL,S2,&var);
			pthread_join(p2,(void**) &T2);
//			printf("%f\n",*T2);
			
			pthread_create(&p3,NULL,S3,&var);
			pthread_join(p3,(void**) &T3);
//			printf("%f\n",*T3);
					
			pthread_create(&p4,NULL,S7,&var);
			pthread_join(p4,(void**) &T4);
//			printf("%f\n",*T4);
			
			T.t1= *T1;
			T.t2= *T2;
			T.t3= *T3;
			T.t4= *T4;
			
			pthread_create(&p5,NULL,S8,&T);
			pthread_join(p5,(void**) &T5);
			
			
			T.t5= *T5;
//			printf("%.2f",*T5);
			
			pthread_create(&p6,NULL,S9,&T);
			pthread_join(p6,(void**) &T6);
			
			printf("Value of side is : %.2f\n", *T6);
		}else{
			goto choice2;
		}
	}
	if(num=='4')
	{
		goto ab;
	}
	else{
		goto choose;
	}
		
		
	}else if(in == '2'){//-----------------------------------
		system("CLS");
		float a,b;
	char exp[100];
	fflush(stdin);
	printf("NOTE:power to be denoted by ^ while sin, cos, tan will be written same\n");
	printf("Note1: write function in order of DMAS rule to reduce error\n");
	printf("Note2: should place ~ to end the equation \n");
	printf("Eg: cos(x)+10*x~\n    5^x=10*x\n\n");
	printf("Enter the equation in form of x:\n");
	fgets(exp,100, stdin);
	printf("Enter the intervals;\n");
	printf("First interval:");
	scanf("%f",&a);
	printf("Second interval:");
	scanf("%f",&b);	

	printf("%s",exp);
	converting(exp,&a,&b);

	int i;
	pthread_t threads[2];
	struct ThreadData d[2];
	for(i=0;i<1;i++)
	{
		d[i].c=a;
		d[i].e=b;
	
	}
	for(i=0;i<1;i++)
	{
		pthread_create(&threads[i],NULL,integrate,&d[i]);
	}
	
	for(i=0;i<1;i++)
	{
		pthread_join(threads[i],NULL);
	}
	
	printf("Integrate: %f",d[0].ans);
	sleep(5);	
	goto ab;	
	}else if(in == '3'){//-----------------------------------
	system("CLS");
			char in;
	start:
		fflush(stdin);
	input();
	derivative();
	printf(" 0");
	printf("\n\nPress 1 to find derivative of another equation\nEnter another character to o back to main menu\n");
	printf("Option:");
	scanf("%c",&in);
	if(in=='1'){
		system("cls");
		goto start;
	}
	else{
		system("CLS");
		goto starting;
		
	}
		
		
	}
	if(in=='4')
	{
		
	}
	else{//-----------------------------------
		system("CLS");
		goto starting;
		
	}
	
	
	
	
	
return 0;
}