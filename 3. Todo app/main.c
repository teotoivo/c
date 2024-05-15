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

void checkIfMallocFailed(void *ptr) {
    if (ptr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
}

void addTodo(TodoStruct *pTodoStruct, char *newName, char *newDescription) {
    bool isBufferInvalid = pTodoStruct->length > pTodoStruct->bufferSize;
    if (isBufferInvalid) {
        fprintf(stderr, "Buffer is invalid\n");
        exit(EXIT_FAILURE);
    }

    bool todosBufferIsFull = pTodoStruct->length == pTodoStruct->bufferSize;
    if (todosBufferIsFull) {
        pTodoStruct->bufferSize *= BUFFER_MULTIPLIER;
        Todo **newArray = realloc(pTodoStruct->arr, sizeof(Todo*) * pTodoStruct->bufferSize);
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
}

void getAllTodos(TodoStruct *pTodoStruct) {
    for (int i = 0; i < pTodoStruct->length; i++) {
        printf("\nTodo id: %d\nName: %s\nDescription: %s", i + 1, pTodoStruct->arr[i]->name, pTodoStruct->arr[i]->description);
    }

    printf("\nPress enter to continue...");
    if (getchar() != '\n') {
        while (getchar() != '\n');
    }
}

void getTodoById(TodoStruct *pTodoStruct, int id) {
    if (pTodoStruct->length < id || id < 1) {
        printf("\nInvalid index!");
        return;
    }

    printf("\nTodo id: %d\nName: %s\nDescription: %s", id, pTodoStruct->arr[id - 1]->name, pTodoStruct->arr[id - 1]->description);
}

void getTodoByName(TodoStruct *pTodoStruct, char *name) {
    for (int i = 0; i < pTodoStruct->length; i++) {
        if (strstr(pTodoStruct->arr[i]->name, name) != NULL) {
            printf("\nTodo id: %d\nName: %s\nDescription: %s", i + 1, pTodoStruct->arr[i]->name, pTodoStruct->arr[i]->description);
            return;
        }
    }
    printf("No todo containing the name was found!");
}

void initTodos(TodoStruct *todoStruct, size_t initialSize) {
    todoStruct->arr = malloc(sizeof(Todo*) * initialSize);
    checkIfMallocFailed(todoStruct->arr);
    todoStruct->bufferSize = initialSize;
    todoStruct->length = 0;
}

void clear() {
    printf("\033[2J\033[1;1H");  
}

void handleGetAllTodos(TodoStruct *todoStruct) {
    clear();

    getAllTodos(todoStruct);

    clear();
}

void handleGetTodoById(TodoStruct *todoStruct) {
    clear();

    printf("\nEnter todo's id: ");
    int tempAns;
    if (scanf("%d", &tempAns) != 1) {
        printf("\nInvalid Input");
        while (getchar() != '\n');

				printf("\nPress enter to continue...");
    		if (getchar() != '\n') {
    		    while (getchar() != '\n');
    		}
        return;
    }

    // Clear any extra characters from the terminal if there are any
    while (getchar() != '\n');

    getTodoById(todoStruct, tempAns);

    printf("\nPress enter to continue...");
    if (getchar() != '\n') {
        while (getchar() != '\n');
    }

    clear();
}

void handleGetTodoByName(TodoStruct *todoStruct) {
    clear();

    char name[MAX_NAME_LENGTH];

    printf("\nEnter the name of the todo: ");
    fgets(name, sizeof(name), stdin);

    // Clear extra characters that were left over and if not, remove the '\n'
    if (!strchr(name, '\n')) {
        while (fgetc(stdin) != '\n');
    } else {
        name[strcspn(name, "\n")] = '\0';
    }

    getTodoByName(todoStruct, name);


    printf("\nPress enter to continue...");
    if (getchar() != '\n') {
        while (getchar() != '\n');
    }

    clear();
}

void handleAddTodo(TodoStruct *todoStruct) {
    clear();
    char newName[MAX_NAME_LENGTH];
    char newDescription[MAX_DESCRIPTION_LENGTH];
    printf("\nEnter the name for the todo: ");
    fgets(newName, sizeof(newName), stdin);
    // Clear extra characters that were left over and if not, remove the '\n'
    if (!strchr(newName, '\n')) {
        while (fgetc(stdin) != '\n');
    } else {
        newName[strcspn(newName, "\n")] = '\0';
    }
    printf("Enter the description for the todo: ");
    fgets(newDescription, sizeof(newDescription), stdin);
    // Clear extra characters that were left over and if not, remove the '\n'
    if (!strchr(newDescription, '\n')) {
        while (fgetc(stdin) != '\n');
    } else {
        newDescription[strcspn(newDescription, "\n")] = '\0';
    }
    addTodo(todoStruct, newName, newDescription);
    printf("\nTodo created!");
    printf("\nPress enter to continue...");
    if (getchar() != '\n') {
        while (getchar() != '\n');
    }
    clear();
}

void deleteTodo(TodoStruct *pTodoStruct, int id)
{
	if (pTodoStruct->length < id || id < 1) {
    printf("\nInvalid index!");
    return;
  }

	free(pTodoStruct->arr[id-1]);

	for (int i = id-1; i < pTodoStruct->length; i++) {
		pTodoStruct->arr[i] = pTodoStruct->arr[i+1];
	}

	pTodoStruct->length--;
}

void handleDeleteTodo(TodoStruct *todoStruct)
{
	clear();

	printf("\nEnter todo's id: ");
  int tempAns;
  if (scanf("%d", &tempAns) != 1) {
    printf("\nInvalid Input");
    while (getchar() != '\n');

		printf("\nPress enter to continue...");
  	if (getchar() != '\n') {
    	while (getchar() != '\n');
  	}
    return;
  }

  // Clear any extra characters from the terminal if there are any
  while (getchar() != '\n');

  deleteTodo(todoStruct, tempAns);

  printf("\nPress enter to continue...");
  if (getchar() != '\n') {
    while (getchar() != '\n');
  }

	clear();
}

void handleEditTodo(TodoStruct *todoStruct)
{
	clear();

	printf("\nEnter todo's id: ");
  int id;
  if (scanf("%d", &id) != 1) {
    printf("\nInvalid Input");
    while (getchar() != '\n');
    return;
  }
  // Clear any extra characters from the terminal if there are any
  while (getchar() != '\n');

  if (todoStruct->length < id || id < 1) {
    printf("\nInvalid index!");
    return;
  }


	char newName[MAX_NAME_LENGTH];
  char newDescription[MAX_DESCRIPTION_LENGTH];
  printf("\nEnter the name for the todo: ");
  fgets(newName, sizeof(newName), stdin);
  // Clear extra characters that were left over and if not, remove the '\n'
  if (!strchr(newName, '\n')) {
      while (fgetc(stdin) != '\n');
  } else {
		if (newName[0] != '\n')
		{
			strcpy(todoStruct->arr[id-1]->name, newName);
		}
      newName[strcspn(newName, "\n")] = '\0';
  }
  printf("Enter the description for the todo: ");
  fgets(newDescription, sizeof(newDescription), stdin);
  // Clear extra characters that were left over and if not, remove the '\n'
  if (!strchr(newDescription, '\n')) {
      while (fgetc(stdin) != '\n');
  } else {
		if (newDescription[0] != '\n')
		{
			strcpy(todoStruct->arr[id-1]->description, newDescription);
		}
      newDescription[strcspn(newDescription, "\n")] = '\0';
  }




  printf("\nPress enter to continue...");
  if (getchar() != '\n') {
    while (getchar() != '\n');
  }

	clear();
}

int main() {
    printf("Todo app.");

    TodoStruct todoStruct;
    initTodos(&todoStruct, INITIAL_BUFFER_SIZE);

    char userAnswer;

    while (userAnswer != 'q') {
        printf("\n\nWhat do you want to do?\n");
        printf("a  Get all todos?\n");
        printf("b  Get a todo by its id?\n");
        printf("c  Get a todo by its name?\n");
        printf("d  Add a todo?\n");
        printf("e  Edit a todo?\n");
        printf("f  Delete a todo\n\n");
        printf("q  Quit.\n\n");
        printf("Your answer: ");

        char tempChar[2];
        scanf("%1s", tempChar);
        userAnswer = tempChar[0];

        // Clear any extra characters from the terminal if there are any
        while (getchar() != '\n');

        switch (userAnswer) {
            case 'a':
                handleGetAllTodos(&todoStruct);
                break;

            case 'b':
                handleGetTodoById(&todoStruct);
                break;

            case 'c':
                handleGetTodoByName(&todoStruct);
                break;

            case 'd':
                handleAddTodo(&todoStruct);
                break;

            case 'e':
                handleEditTodo(&todoStruct);
                break;

            case 'f':
                handleDeleteTodo(&todoStruct);
                break;

            case 'q':
                clear();
                printf("Bye bye!");
                break;

            default:
                clear();
                printf("%c is not an option.", userAnswer);
                if (getchar() != '\n') {
                    while (getchar() != '\n');
                }
                clear();
                break;
        }
    }

    return EXIT_SUCCESS;
}
