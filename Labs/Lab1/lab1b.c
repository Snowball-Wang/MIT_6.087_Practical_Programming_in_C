/*
 * lab1b.c
 *
 *  Created on: May 9, 2019
 *      Author: Snowball Wang
 */

/* include helper functions for game */
#include "lifegame.h"

/* add whatever other includes here */
#include <stdio.h>

/* number of generations to evolve the world */
#define NUM_GENERATIONS 50

/* functions to implement -- can copy from Part A */

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

int main(int argc, char ** argv)
{
	int n;
	char * input = NULL;
	char * output = "world.txt";

	/* initialize the world, from file argv[1]
	   if command line argument provided (argc > 1), or
	   using hard-coded pattern (use Part A) otherwise */
	if (argc > 1)
	{
		input = argv[1];
		initialize_world_from_file(input);
	}
	else
	{
		input = "glider.txt";
		initialize_world_from_file(input);
	}

	save_world_to_file(output);
	for (n = 0; n < NUM_GENERATIONS; n++)
		next_generation();

	/* output final world state to console and save
	   world to file "world.txt" in current directory */
	save_world_to_file(output);

	return 0;
}

void next_generation(void) {
	/* for every cell, set the state in the next
	   generation according to the Game of Life rules

	   Hint: use get_next_state(x,y) */
	int i, j;
	int world_width, world_height;
	world_width = get_world_width();
	world_height = get_world_height();
	for (i = 0; i < world_width; i++)
		for (j = 0; j < world_height; j++)
			set_cell_state(i, j, get_next_state(i, j));

	finalize_evolution(); /* called at end to finalize */
}

int get_next_state(int x, int y) {
	/* for the specified cell, compute the state in
	   the next generation using the rules

	   Use num_neighbors(x,y) to compute the number of live
	   neighbors */
	if (get_cell_state(x, y) == DEAD)
		return num_neighbors(x, y) == 3 ? ALIVE : DEAD;
	else
		return (num_neighbors(x, y) == 2 || num_neighbors(x, y) == 3) ? ALIVE : DEAD;

}

int num_neighbors(int x, int y) {
	/* for the specified cell, return the number of
	   neighbors that are ALIVE

	   Use get_cell_state(x,y) */
	int i, j;
	int sum = 0;
	/* remember to exclude value when (i,j) is (x,y) */
	for (i = x-1; i <= x+1; i++)
	{
		for (j = y-1; j <= y+1; j++)
		{
			if (!(i == x && j == y))
				if (get_cell_state(i, j) == ALIVE)
					sum += 1;
		}
	}
	return sum;

}
