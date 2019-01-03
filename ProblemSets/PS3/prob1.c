#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define NMAX 25
static unsigned int results_buffer[NMAX];

void fibonacci()
{
	/* here are the variables to set as registers */
	unsigned int a = 0;
	unsigned int b = 1;
	unsigned int c;
	int n;

	/* do not edit below this line */
	results_buffer[0] = a;
	results_buffer[1] = b;
	for (n = 2; n < NMAX; n++) {
		c = a + b;
		results_buffer[n] = c; /* store code in results buffer */
		a = b;
		b = c;
	}
}

int main(void) {
	
	int n, ntests = 10000000;
	clock_t tstart, tend;
	double favg;

	/* do profiling */
	tstart = clock();
	
	for (n = 0; n < ntests; n++)
		fibonacci();

	tend = clock();
	/* end profiling */

	/* compute average execution time */
	favg = ((double)(tend - tstart))/CLOCKS_PER_SEC/ntests;

	/* print avg execution time in milliseconds */
	printf("Avg. execution time: %g msec\n",favg*1000);
	return 0;
}
