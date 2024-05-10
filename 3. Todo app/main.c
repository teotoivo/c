#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


#define INITIAL_BUFFER_SIZE 1
#define BUFFER_MULTIPLIER 2

#define MAX_NAME_LENGTH 32
#define MAX_DESCRIPTION_LENGTH 64




typedef struct {
	char name[MAX_NAME_LENGTH];
	char description[MAX_DESCRIPTION_LENGTH];
} Todo;

typedef struct {
	Todo **todos;
  size_t used;
  size_t size;
} TodosArray;

void checkIfMallocFailed(void *ptr)
{
	if (ptr == NULL) {
		fprintf(stderr, "Memory allocation failed\n");
    exit(EXIT_FAILURE);
	}
	return;
}







int main()
{
	printf("Todo app.\n\n");

	size_t todoCount = 0;
	size_t todosBuffer = INITIAL_BUFFER_SIZE;

	//stores pointers to the structures
	Todo **pTodos = (Todo**)malloc(sizeof(Todo *) * todosBuffer);
	checkIfMallocFailed(pTodos);

	


	char userAnswer;

	while (userAnswer != 'q')
	{
		
		printf("What do you want to do?\n");

		printf("t test\n");

		printf("a  Get all todos?\n");
		printf("b  Get a todo by its id?\n");
		printf("c  Get a todo by its name?\n");
		printf("d  Add a todo?\n");
		printf("e  Delete a todo\n\n");

		printf("q Quit.\n\n");

		printf("Your answer: ");
		char tempChar[2];
		scanf("%1s", tempChar);
		userAnswer = tempChar[0];

		printf("\n\n");

		switch (userAnswer)
		{
			case 't':

				char name[MAX_NAME_LENGTH] = "test";
				char desc[MAX_DESCRIPTION_LENGTH] = "aaaa";

			

				break;

			case 'a':


				break;

			default:
				printf("%c is not an option.", userAnswer);
				break;

		}


		
	}

	freeTodos(pTodos, todoCount);

	return EXIT_SUCCESS;
}


