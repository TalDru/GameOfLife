#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>

#define ALIVE 'O'
#define DEAD '.'

void DisplaySim(int rows, int columns, char* sim);
int CountN(int rows, int columns, int x, int y, char* sim);
char* StepSim(int rows, int columns, char* prevSim);
void BeginSim(int rows, int columns);
double RandD(double min, double max);
char* CreateSim(int rows, int columns);


int main(int argc, char* argv[]) {
	int rows = atoi(argv[1]);
	int columns = atoi(argv[2]);

	if (argc < 2) {
		printf("Format: Game.exe [Rows] [Columns]");
	}if (rows <= 0) {
		printf("The number of rows must be greater than 0; The input was %d\n",rows);
		return -1;
	}
	rows += 2;
	if (columns <= 0) {
		printf("The number of columns must be greater than 0; The input was %d\n", columns);
		return -1;
	}
	columns += 2;

	BeginSim(rows, columns);
}

void DisplaySim(int rows, int columns, char* sim) {

	system("cls");
	//printf("\n\n\n\n\n\n");

	for (int y = 1; y < rows -1; y++)
	{
		for (int x = 1; x < columns -1; x++)
		{
			printf("%c ", *(sim + y*columns + x));
		}
		printf("\n");
	}
}

int CountN(int rows, int columns, int x, int y, char* sim) {
	int count = 0;
	int pivot = y*columns + x;

	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			char c = *(sim + pivot + (i*columns) + j);

			if (c == ALIVE)
				count++;
		}
	}
	return count;
}



char* StepSim(int rows, int columns, char* prevSim) {
	char* nextSim = calloc(rows*columns, sizeof(char));
	if (nextSim == NULL)
		return NULL;
	for (int y = 1; y < rows - 1; y++)
	{
		for (int x = 1; x < columns - 1; x++)
		{
			int live = CountN(rows, columns, x, y, prevSim);
			char cell = *(prevSim + y*columns + x);
			if (cell == ALIVE)
				live--;
			*(nextSim + y*columns + x) = cell;

			//Implement rules

			if (live < 2)
				*(nextSim + y*columns + x) = DEAD; //Any live cell with fewer than two live neighbors dies, as if by underpopulation.
			else if ((live==2 || live==3)&& cell==ALIVE)
				*(nextSim + y*columns + x) = ALIVE; //Any live cell with two or three live neighbors lives on to the next generation.
			else if ((live >3)&& cell == ALIVE)
				*(nextSim + y*columns + x) = DEAD; //Any live cell with more than three live neighbors dies, as if by overpopulation.
			else if (live ==3 && cell == DEAD)
				*(nextSim + y*columns + x) = ALIVE; //Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
		}
	}

	return nextSim;
}

void BeginSim(int rows, int columns) {
	puts("Beginning!");
	char* sim = CreateSim(rows, columns);
	if (sim == NULL)
		return;
	DisplaySim(rows, columns, sim);

	while (1)
	{
		char* newSim = StepSim(rows, columns, sim);
		if (newSim == NULL)
			return;
		free(sim);
		sim = newSim;
		DisplaySim(rows, columns, sim);
		Sleep(1000);
	}
}

double RandD(double min, double max) {
	return ((double)rand() / RAND_MAX)*(max - min) + min;
}

char* CreateSim(int rows, int columns) {

	char* sim = (char*)calloc(rows*columns, sizeof(char));
	
	if (sim == NULL)
		return NULL;

	for (int y = 1; y < rows-1; y++)
	{
		for (int x = 1; x < columns-1; x++)
		{
			if (RandD(0.0, 1.0) <= 0.35) {
				*(sim + y*columns + x) = ALIVE; //Alive
			}
			else {
				*(sim + y*columns + x) = DEAD; //Dead
			}
		}
	}

	return sim;
}


