/*
 * prob1d.c
 *
 *  Created on: Jan 20, 2010
 *      Author: dweller
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* functions defined in your code */
int initialize_db (const char * filename);
int locate_movie(char * title );
void dump_sorted_list(const char * filename);
void cleanup(void);

#define NUM_TITLES 10
int main(int argc, char * argv[]) {

	int nresult, n;
	char strtitles[NUM_TITLES][256] = {"Citizen Kane", "Ponderosa", "Gosford Park", "Transformers", "Gone with the Wind", "When Harry Met Sally", "Avatar", "Simpsons Movie, The", "American Pie 2", "Superman Returns"};
	struct s_record * pvalue;

	if (argc < 2) {
		fprintf(stderr,"Error: database name not specified!\n");
		return 1;
	}

	if (argc < 3) {
		fprintf(stderr,"Error: output file name not specified!\n");
		return 1;
	}

	/* initialize B-tree and fill with database */
	if ( (nresult = initialize_db(argv[1])) != 0) {
		cleanup();
		return nresult; /* error during initialization */
	}

	dump_sorted_list(argv[2]);

	for (n = 0; n < NUM_TITLES; n++) {
		if ( (nresult = locate_movie(strtitles[n])) == 0)
			printf("Movie \"%s\" not found!\n", strtitles[n]);

	}

	cleanup();

	return 0;
}

