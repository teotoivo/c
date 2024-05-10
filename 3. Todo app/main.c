#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


#define INITIAL_BUFFER_SIZE 1
#define BUFFER_MULTIPLIER 2

#define MAX_NAME_LENGTH 20
#define MAX_DESCRIPTION_LENGTH 50


typedef struct {
	char name[MAX_NAME_LENGTH];
	char description[MAX_DESCRIPTION_LENGTH];
} Todo;

typedef struct {
	size_t length;
	size_t bufferSize;
	Todo **arr;
} TodoStruct;

void checkIfMallocFailed(void *ptr)
{
	if (ptr == NULL) {
		fprintf(stderr, "Memory allocation failed\n");
    exit(EXIT_FAILURE);
	}
	return;
}

void addTodo(TodoStruct *pTodoStruct, Todo *pNewTodo)
{
	bool isBufferInvalid = pTodoStruct->length > pTodoStruct->bufferSize;
	if (isBufferInvalid)
	{
		fprintf(stderr, "Buffer is invalid\n");
    exit(EXIT_FAILURE);
	}

	bool todosBufferIsFull =  pTodoStruct->length == pTodoStruct->bufferSize;;
	if (todosBufferIsFull)
	{
	  Todo **tempArray = pTodoStruct->arr;

		pTodoStruct->bufferSize *= 2;
		pTodoStruct->arr = realloc(pTodoStruct->arr, (sizeof(Todo*) * pTodoStruct->bufferSize));

	}
	pTodoStruct->arr[pTodoStruct->length] = pNewTodo;
	
	pTodoStruct->length++;
	return;
}

void getAllTodos(TodoStruct *pTodoStruct)
{
	for (int i = 0; i < pTodoStruct->length; i++) {
		printf("\nName: %s\nDescription: %s\n", pTodoStruct->arr[i]->name, pTodoStruct->arr[i]->description);
	}
}

void initTodos(TodoStruct *todoStruct, size_t initialSize)
{
	todoStruct->arr = malloc(sizeof(Todo*) * initialSize);
	todoStruct->bufferSize = initialSize;
	todoStruct->length = 0;
}


int main()
{
	printf("Todo app.\n\n");

	
	TodoStruct todoStruct;
	initTodos(&todoStruct, INITIAL_BUFFER_SIZE);

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

				Todo *pPassTodo = malloc(sizeof(Todo));
				*pPassTodo = tempTodo;
				
				addTodo(&todoStruct, pPassTodo);

				break;

			case 'a':

				getAllTodos(&todoStruct);

				break;

			default:
				printf("%c is not an option.", userAnswer);
				break;

		}


		
	}

	

	return EXIT_SUCCESS;
}


