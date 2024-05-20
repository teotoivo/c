#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_NAME_LENGTH 20
#define MAX_DESCRIPTION_LENGTH 50

struct Node; // Forward declaration

// Define the Node struct
typedef struct Node {
    char name[MAX_NAME_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];
    struct Node* previous;
    struct Node* next;
} Node;

// Define the Header struct
typedef struct {
    size_t length;
    Node* first;
    Node* last;
} Header;

void clear();
void initHeader(Header* header);
void waitForEnter();
int printMenu();
int getOption();
void handlePrintAll(Header* header);
Node* createTodoStruct(char* name, char* description);
int addTodo(Header* header, Node* node, long int position);

int main() {
    Header header;
    initHeader(&header);

    int option;

    while ((option = getOption()) != 0) {
        clear();
        switch (option) {
            case 1: // print all
                handlePrintAll(&header);
                break;

            case 2: // print by id
                
                break;

            case 3: // add todo
                addTodo(&header, createTodoStruct("test1", ""), 0);
                addTodo(&header, createTodoStruct("test0", ""), 0);
                addTodo(&header, createTodoStruct("test2", ""), -1);
								waitForEnter();
                break;

            case 4: // delete todo
                
                break;

            case 5: // edit todo
                
                break;

            default:
                printf("Invalid input!");
                waitForEnter();
                break;
        }
        clear();
    }
		clear();
		printf("Bye bye!");

    return 0;
}

void clear() {
    printf("\033[2J\033[1;1H");  
}

void initHeader(Header* header) {
    header->length = 0;
    header->first = NULL;
    header->last = NULL;
}

void waitForEnter() {
    printf("\nPress enter to continue...");
    if (getchar() != '\n') {
        while (getchar() != '\n');
    }
}

int printMenu() {
    printf("\nChoose an option:");
    printf("\n1. Print all todos");
    printf("\n2. Print todo by id");
    printf("\n3. Add todo");
    printf("\n4. Delete todo");
    printf("\n5. Edit todo");
    printf("\n\n0. quit");

    return 0;
}

int getOption() {
    printMenu();
    
    int option;
    printf("\n\nSelect an option: ");
    
    if (scanf("%d", &option) != 1) {
        while (getchar() != '\n');
        clear();
        printf("\nInvalid input!");
        waitForEnter();
        clear();
        return getOption();
    }
    while (getchar() != '\n');
    return option;
}

void handlePrintAll(Header* header) {
    if (header->first == NULL) {
        printf("No todos to display.");
        waitForEnter();
        return;
    }

    Node* node = header->first;
    for (int i = 0; node != NULL; i++) {
        printf("\nid: %d", i + 1);
        printf("\nname: %s", node->name);
        printf("\ndescription: %s", node->description);
        node = node->next;
    }

    waitForEnter();
}

Node* createTodoStruct(char* name, char* description) {
    Node* todoNode = (Node*)malloc(sizeof(Node));
    if (todoNode == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    todoNode->next = NULL;
    todoNode->previous = NULL;
    strncpy(todoNode->name, name, sizeof(todoNode->name) - 1);
    todoNode->name[sizeof(todoNode->name) - 1] = '\0';
    strncpy(todoNode->description, description, sizeof(todoNode->description) - 1);
    todoNode->description[sizeof(todoNode->description) - 1] = '\0';
    return todoNode;
}
int addTodo(Header* header, Node* pNode, long int position)
{
	printf("\npos: %d", position);
	printf("\nlen: %d", header->length);

	printf("\ncomp: %d", position > header->length);

	printf("\n\n");
	if (position > header->length + 1 || position < -1)
	{
		printf("Invalid position!");
		free(pNode);
		waitForEnter();
		return 1;
	}

	pNode->next = NULL;
	pNode->previous = NULL;

	switch (position)
	{
	case 0:
		if (header->first) {
			pNode->next = header->first;
			header->first->previous = pNode;
		} else {
			header->last = pNode;
		}
		header->first = pNode;

		header->length++;
		break;

	case -1:
		if (header->last) {
			pNode->previous = header->last;
			header->last->next = pNode;
		} else {
			header->first = pNode;
		}
		header->last = pNode;

		header->length++;
		break;
	
	default:
		
		break;
	}

}