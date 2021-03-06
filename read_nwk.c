#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "sir.h"

extern NODE *n;
extern GLOBALS g;

void read_data(FILE *fp) {
	unsigned int i, me, you;

	g.n = 0;

	// scan the system size
	while (2 == fscanf(fp, "%u %u\n", &me, &you)) {
		if (g.n < me) g.n = me;
		if (g.n < you) g.n = you;
	}

	g.n++;

	n = calloc(g.n, sizeof(NODE));

	rewind(fp);

	// scan the degrees
	while (2 == fscanf(fp, "%u %u\n", &me, &you)) {
		n[me].deg++;
		n[you].deg++;
	}

	// initialize agents , and 
	// allocate adjacency lists
	for (i = 0; i < g.n; i++) {
		// initilaize an agent
		n[i].payoff = 0;
		// agent's memory (linked list)
		n[i].head = malloc(sizeof(struct oneMemory));
		n[i].tail = malloc(sizeof(struct oneMemory));
		n[i].head -> next = n[i].tail;
		n[i].storage = malloc(sizeof(struct Storage));
		n[i].storage -> payoff_conforming = 0.0;
		n[i].storage -> payoff_rational= 0.0;
		n[i].storage -> num_conforming = 0;
		n[i].storage -> num_rational = 0;


		// allocate adhacency lists
		n[i].nb = malloc(n[i].deg * sizeof(unsigned int));
		n[i].deg = 0;

		// is initially vaccinated node?
		n[i].immune = get_one_or_zero_randomly(g.coverage);
		if(n[i].immune) n[i].payoff -= g.vac_cost;
	}

	rewind(fp);

	// fill adjacency lists
	while (2 == fscanf(fp, "%u %u\n", &me, &you)) {
		n[me].nb[n[me].deg++] = you;
		n[you].nb[n[you].deg++] = me;
	}
}
