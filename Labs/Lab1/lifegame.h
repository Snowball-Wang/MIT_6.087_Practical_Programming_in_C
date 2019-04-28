/*
 * lifegame.h
 *
 *  Created on: Jan 7, 2010
 *      Author: Daniel Weller
 */

/* Warning: Do NOT modify the contents of this file.
   All your code should be in lab1a.c. */

#ifndef LIFEGAME_H_
#define LIFEGAME_H_

/* state constants */
#define DEAD 0
#define ALIVE 1

/* initialize_world -- set up world, all cells initialized
   to DEAD or ALIVE; all cells in next generation are
   initialized to DEAD */
void initialize_world(void);

/* returns the width (x) and height (y) of the world */
int get_world_width(void);
int get_world_height(void);

/* returns the state (DEAD or ALIVE) of the cell at (x,y);
   coordinates go from x = 0,...,width-1 and
   y = 0,...,height-1; returns DEAD for cells outside this
   range */
int get_cell_state(int x, int y);

/* sets the state (DEAD or ALIVE) of the cell at (x,y) in
   the next generation; range of coordinates same as in
   get_cell_state(); calls abort() if invalid coordinates
   are specified */
void set_cell_state(int x, int y, int state);

/* updates world state to next generation and resets all
   next generation states to DEAD */
void finalize_evolution(void);

/* outputs the current world state to the console */
void output_world(void);

/* functions to implement for Part B */
void initialize_world_from_file(const char * filename);
void save_world_to_file(const char * filename);

#endif /* LIFEGAME_H_ */
