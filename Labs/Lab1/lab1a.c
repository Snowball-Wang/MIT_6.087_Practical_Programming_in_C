/*
 * lab1a.c
 *
 *  Created on: Apr 28, 2019 
 *      Author: Snowball Wang
 */

/* include helper functions for game */
#include "lifegame.h"

/* add whatever other includes here */
#define WORLDWIDTH  get_world_width()
#define WORLDHEIGHT get_world_height()
/* number of generations to evolve the world */
#define NUM_GENERATIONS 50

/* functions to implement */

/* this function should set the state of all
   the cells in the next generation and call
   finalize_evolution() to update the current
   state of the world to the next generation */
void next_generation(void);

/* this function should return the state of the cell
   at (x,y) in the next generation, according to the
   rules of Conway's Game of Life (see handout) */
int get_next_state(int x, int y);

/* this function should calculate the number of alive
   neighbors of the cell at (x,y) */
int num_neighbors(int x, int y);

static int world[WORLDWIDTH][WORLDHEIGHT];
static int nextstates[WORLDWIDTH][WORLDHEIGHT];

int main(void)
{
	int n;

	/* initialize the world */
    int i, j;

	for (i = 0; i < WORLDWIDTH; i++)
		for (j = 0; j < WORLDHEIGHT; j++)
			world[i][j] = nextstates[i][j] = DEAD;
	/* pattern "glider" */
	world[1][2] = ALIVE;
	world[3][1] = ALIVE;
	world[3][2] = ALIVE;
	world[3][3] = ALIVE;
	world[2][3] = ALIVE;


	for (n = 0; n < NUM_GENERATIONS; n++)
		next_generation();

	/* output final world state */
	output_world();

	return 0;
}

void next_generation(void) {
	/* for every cell, set the state in the next
	   generation according to the Game of Life rules

	   Hint: use get_next_state(x,y) */
	int i, j;
	for (i = 0; i < WORLDWIDTH; i++) {
		for (j = 0; j < WORLDHEIGHT; j++) {
			nextstates[i][j] = get_next_state(i, j);
			world[i][j] = nextstates[i][j];
		}
	}



	finalize_evolution(); /* called at end to finalize */
}

int get_next_state(int x, int y) {
	/* for the specified cell, compute the state in
	   the next generation using the rules

	   Use num_neighbors(x,y) to compute the number of live
	   neighbors */
	if (get_cell_state(x, y) == DEAD)
	{
		if (num_neighbors(x, y) == 3)
			set_cell_state(x, y, ALIVE);
	}
	else
	{
		if (num_neighbors(x, y) == 2 || num_neighbors(x, y) == 3)
		{
			set_cell_state(x, y, ALIVE);
		}
		else
		{
			set_cell_state(x, y, DEAD);
		}
	}

}

int num_neighbors(int x, int y) {
	/* for the specified cell, return the number of
	   neighbors that are ALIVE

	   Use get_cell_state(x,y) */
	int i, j;
	int sum = 0;
	for (i = x-1;i <= x+1; i++)
	{
		for (j = y-1;j <= y+1; j++)
		{
			if (get_cell_state(i, j) == ALIVE)
				sum += 1;
		}
	}
	return sum;


}

