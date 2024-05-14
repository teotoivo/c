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

void addTodo(TodoStruct *pTodoStruct, char *newName, char *newDescription)
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
		pTodoStruct->bufferSize *= BUFFER_MULTIPLIER;
		Todo **newArray = realloc(pTodoStruct->arr, (sizeof(Todo*) * pTodoStruct->bufferSize));
		if (newArray == NULL) {
			fprintf(stderr, "Memory reallocation failed\n");
			exit(EXIT_FAILURE);
		}
		pTodoStruct->arr = newArray;

	}

	Todo *pNewTodo = malloc(sizeof(Todo));
	checkIfMallocFailed(pNewTodo);
	strcpy(pNewTodo->name, newName);
	strcpy(pNewTodo->description, newDescription);

	pTodoStruct->arr[pTodoStruct->length] = pNewTodo;
	
	pTodoStruct->length++;
	return;
}

void getAllTodos(TodoStruct *pTodoStruct)
{
	for (int i = 0; i < pTodoStruct->length; i++) {
		printf("\nTodos id: %d\nName: %s\nDescription: %s", i+1, pTodoStruct->arr[i]->name, pTodoStruct->arr[i]->description);
	}

	printf("\nPress enter to continue...");

	if (getchar() != '\n') {
		while(getchar() != '\n');
	}
}

void getTodoById(int *id)
{

}

void initTodos(TodoStruct *todoStruct, size_t initialSize)
{
	todoStruct->arr = malloc(sizeof(Todo*) * initialSize);
	todoStruct->bufferSize = initialSize;
	todoStruct->length = 0;
}

void clear()
{
	printf("\033[2J\033[1;1H");  
}


int main()
{
	printf("Todo app.");

	
	TodoStruct todoStruct;
	initTodos(&todoStruct, INITIAL_BUFFER_SIZE);

	char userAnswer;

	while (userAnswer != 'q')
	{
		printf("\n\nWhat do you want to do?\n");

		printf("a  Get all todos?\n");
		printf("b  Get a todo by its id?\n");
		printf("c  Get a todo by its name?\n");
		printf("d  Add a todo?\n");
		printf("e  Edit a todo?\n");
		printf("f  Delete a todo\n\n");

		printf("q Quit.\n\n");

		printf("Your answer: ");
		char tempChar[2];
		scanf("%1s", tempChar);
		userAnswer = tempChar[0];

		// Clear any extra characters from the terminal if there are any
		while (getchar() != '\n');

		switch (userAnswer)
		{
			case 'a':
				clear();

				getAllTodos(&todoStruct);

				clear();
				break;


			case 'b':
				clear();

				printf("\nEnter todos id: ");
				
				int tempAns;
				scanf("%d", &tempAns);
				
				printf("%d", tempAns);

				// Clear any extra characters from the terminal if there are any
				while (getchar() != '\n');
				
				

				clear();
				break;


			case 'c':
				clear();
				
				clear();
				break;



			case 'd':
				clear();
				char name[MAX_NAME_LENGTH];
				char description[MAX_DESCRIPTION_LENGTH];

				printf("\nEnter the name for the todo: ");
				fgets(name, sizeof(name), stdin);

				//clears extra characters that were left over and if not removes the \n
				if (!strchr(name, '\n')) {
					while(fgetc(stdin)!='\n');
				} else {
					name[strcspn(name, "\n")] = '\0';
				}

				printf("Enter the description for the todo: ");
				fgets(description, sizeof(description), stdin);
				
				//clears extra characters that were left over and if not removes the \n
				if (!strchr(description, '\n')) {
					while(fgetc(stdin)!='\n');
				} else {
					name[strcspn(description, "\n")] = '\0';
				}

				addTodo(&todoStruct, name, description);

				printf("\nTodo created!");

				printf("\nPress enter to continue...");

				if (getchar() != '\n') {
					while(getchar() != '\n');
				}

				clear();
				break;



			case 'e':
				clear();

				clear();
				break;

			case 'f':
				clear();

				clear();
				break;

			case 'q':
				clear();
				

				printf("Bye bye!");

				
				break;

			default:
				clear();
				
				printf("%c is not an option.", userAnswer);

				if (getchar() != '\n') {
					while(getchar() != '\n');
				}
				clear();
				break;

		}


		
	}

	

	return EXIT_SUCCESS;
}


