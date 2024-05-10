#include <stdio.h>
#include <stdlib.h>

int main() {
	
	int *t1 = malloc(sizeof(int));
	*t1 = 1;

	int *t2 = malloc(sizeof(int));
	*t2 = 2;

	int *t3 = malloc(sizeof(int));
	*t3 = 3;

	int **pArray = malloc(sizeof(int *) * 3);

	pArray[0] = t1;
	pArray[1] = t2;
	pArray[2] = t3;

	return 0;
}