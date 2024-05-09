#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define INITIAL_BUFFER_SIZE 1
#define BUFFER_MULTIPLIER 1.5

#define MAX_NAME_LENGTH 20
#define MAX_DESCRIPTION_LENGTH 50

typedef struct {
	char name[MAX_NAME_LENGTH];
	char description[MAX_DESCRIPTION_LENGTH];
} Todo;

void checkIfMallocFailed(void *ptr)
{
	if (ptr == NULL) {
		fprintf(stderr, "Memory allocation failed\n");
    exit(EXIT_FAILURE);
	}
	return;
}

void freeTodos(Todo **pTodos, size_t noOfTodos)
{
	for (size_t i = 0; i < noOfTodos; i++) {
		free(pTodos[i]);
	}
	free(pTodos);
	return;
}

void removeTodo(Todo **pTodos, size_t *pTodoCount, size_t index)
{
	if (index >= *pTodoCount)
	{
		//invalid index
		return;
	}
}

void addTodo(Todo **pTodos, size_t *pTodoCount, size_t *pTodosBuffer, Todo newTodo)
{
	bool isBufferInvalid = *pTodoCount > *pTodosBuffer;
	if (isBufferInvalid)
	{
		fprintf(stderr, "Buffer is invalid\n");
    exit(EXIT_FAILURE);
	}
	
	
	bool todosBufferIsFull = *pTodoCount == *pTodosBuffer;
	if (todosBufferIsFull)
	{
	    *pTodosBuffer *= BUFFER_MULTIPLIER;

	    *pTodos = realloc(*pTodos, sizeof(Todo) * (*pTodosBuffer));
	    checkIfMallocFailed(pTodos);
	}


	pTodos[0] = malloc(sizeof(Todo));
	strcpy(pTodos[0]->name, newTodo.name);
	strcpy(pTodos[0]->description, newTodo.description);
	
	(*pTodoCount)++;
	return;
}

void getAllTodos(Todo **pTodos, size_t *pTodoCount)
{

	for (int i = 0; i < *pTodoCount; i++)
	{
		Todo todo = (*pTodos)[i];

		printf("Todo\n\nName: %s\nDescription: %s\n", todo.name, todo.description);
	}

	char exitM[2];

	printf("Press any key to return to the menu: ");
	scanf("%1s", exitM);
	printf("\n\n");
	return;
}



int main()
{
	printf("Todo app.\n\n");

	size_t todoCount = 0;
	size_t todosBuffer = INITIAL_BUFFER_SIZE;


	//stores pointers to the structures
	Todo **pTodos = malloc(sizeof(Todo*) * todosBuffer);
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

				Todo tempTodo = {"test", "test ttt"};

				addTodo(pTodos, &todoCount, &todosBuffer, tempTodo);

				break;

			case 'a':

				getAllTodos(pTodos, &todoCount);

				break;

			default:
				printf("%c is not an option.", userAnswer);
				break;

		}


		
	}

	freeTodos(pTodos, todoCount);

	return EXIT_SUCCESS;
}


