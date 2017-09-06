/*
 * Unit test program for Lib LBR
 * Jun 2015 Tong Zhang <ztong@vt.edu>
 */

#include <lbr.h>

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <sched.h>


#define _USE_CPU_AFFINITY_


#ifdef _USE_CPU_AFFINITY_
void set_cpu_affinity()
{
	cpu_set_t mask;
	CPU_ZERO(&mask);
	CPU_SET(0,&mask);//use cpu 0
	int result = sched_setaffinity(0, sizeof(mask), &mask);
	if(result)
	{
		fprintf(stderr,"set cpu affinity failed, use taskset instead\n");
	}
}
#endif

unsigned long tscs[8];

#define rdtsc(X) \
	unsigned hi, lo; \
	__asm__ __volatile__ ("rdtscp" : "=a"(lo), "=d"(hi));\
	X = ( (unsigned long long)lo)|( ((unsigned long long)hi)<<32 );


/*
 * test functions
 */
void func7()
{
	rdtsc(tscs[7]);
	/*
	 * dump data from LBR
	 */
	lbr_stack lbrstack;
	dump_lbr(0,&lbrstack);
	inteprete_lbr_info(&lbrstack);
	for (int i=0;i<8;i++)
	{
		printf("TSC[%d]=%ld\n",i,tscs[i]);
	}
    printf("-----------\n");
    int j = 0;
	for (int i=1;i<8;i++)
	{
        printf("=%ld\n",tscs[i] - tscs[j]);
        j = i;
	}
}

void func6()
{
	rdtsc(tscs[6]);
	func7();
}
void func5()
{
	rdtsc(tscs[5]);
	func6();
}
void func4()
{
	rdtsc(tscs[4]);
	func5();
}
void func3()
{
	rdtsc(tscs[3]);
	func4();
}
void func2()
{
	rdtsc(tscs[2]);
	func3();
}
void func1()
{
	rdtsc(tscs[1]);
	func2();
}
void func0()
{
	rdtsc(tscs[0]);
	func1();
}

int main()
{
#ifdef _USE_CPU_AFFINITY_
	set_cpu_affinity();
#endif
	if(start_lbr(0))
	{
		return -1;
	}

	func0();
	cleanup_lbr(0);
	return 0;
}


