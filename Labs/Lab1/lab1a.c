/*
 * lab1a.c
 *
 *  Created on: 10/2/2022
 *      Author: Snowball Wang
 */

/* include helper functions for game */
#include "lifegame.h"

/* add whatever other includes here */

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

int main(void)
{
	int n;

	/* initialize the world */
	initialize_world();

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
	int state;
	for(int i = 0; i < get_world_width(); i++){
		for(int j = 0; j < get_world_height(); j++){
			state = get_next_state(i, j);
			set_cell_state(i, j, state);
		}
	}


	finalize_evolution(); /* called at end to finalize */
}

int get_next_state(int x, int y) {
	/* for the specified cell, compute the state in
	   the next generation using the rules

	   Use num_neighbors(x,y) to compute the number of live
	   neighbors */
	int state = get_cell_state(x, y);
	int alive = num_neighbors(x, y);
	/* next alive under two conditions: 
	#1. ALIVE and 2 or 3 live neighbors 
	#2. Dead and 3 live neighbors */
	int next_alive_or_dead = (state && (alive == 2 || alive == 3)) || (!state && (alive == 3));
	if (next_alive_or_dead)
		return ALIVE;
	else
		return DEAD;

}

int num_neighbors(int x, int y) {
	/* for the specified cell, return the number of
	   neighbors that are ALIVE

	   Use get_cell_state(x,y) */
	
	/* Don't forget to exclude (x,y) itself */
	int num_alive = 0;
	for (int i = x - 1; i <= x + 1; i++) {
		for (int j = y - 1; j <= y + 1; j++) {
			if(!(i == x && j == y))
				num_alive += get_cell_state(i, j);
		}
	}

	return num_alive;
}
