#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char** createGrid(int n) {
	
	char** grid = (char**)malloc(n * sizeof(char*));

	if (grid == NULL) {	
		printf("Memory allocation failed!\n");
		exit(1);
	}

	for (int i = 0; i < n; i++) {
		grid[i] = (char *)malloc(n * sizeof(char));
		
		if (grid[i] == NULL) {
			printf("memory allocation failed for row %d!\n", i);
			exit(1);
		}
	}

	return grid;
}

void placeRandomItems(char** grid, int n, char item, char count) {

	srand(time(NULL));

	int already_placed = 0;
	while (already_placed < count) {
		int rand_row = rand() % n;
		int rand_col = rand() % n;

		if (grid[rand_row][rand_col] == '.') {
			grid[rand_row][rand_col] = item;
			already_placed++;
		}
	}
}

void initGrid(char** grid, int n) {

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			grid[i][j] = '.';
		}
	}

	placeRandomItems(grid, n, 'I', 3); // 3 Intel
    placeRandomItems(grid, n, 'L', 2); // 2 Lives
    placeRandomItems(grid, n, 'X', 1); // 1 Extraction Point
    placeRandomItems(grid, n, '#', 4);
}

void freeGrid(char** grid, int n) {

	for (int i = 0; i < n; i++) {
		free(grid[i]);
	}	
	
	free(grid);
}


void displayGrid(char** grid, int n) {

	printf("\n");

	for (int i = 0; i < n; i++) {

		for (int j = 0; j < n; j++) {
			printf("+---");
			if (j == n-1) printf("+");
		}
		printf("\n");

		for (int j = 0; j < n; j++) {
			printf("| %c ", grid[i][j]);
		}
		printf("|\n");
	}

	for (int i = 0; i < n; i++) {
		printf("+---");
	}
	printf("+\n");
}

int main() {
	char** grid = createGrid(5);
	initGrid(grid, 5);
	displayGrid(grid, 5);
	freeGrid(grid, 5);

}
