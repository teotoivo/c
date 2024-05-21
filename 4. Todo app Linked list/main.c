#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_NAME_LENGTH 32
#define MAX_DESCRIPTION_LENGTH 64

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

/**
 * @brief Clears the console screen.
 */
void clear();

/**
 * @brief Initializes a Header struct.
 * 
 * @param header Pointer to the Header struct to initialize.
 */
void initHeader(Header* header);

/**
 * @brief Waits for the user to press enter to continue.
 */
void waitForEnter();

/**
 * @brief Prints the menu options to the console.
 * 
 * @return Always returns 0.
 */
int printMenu();

/**
 * @brief Gets the user's menu option selection.
 * 
 * @return The selected option as an integer.
 */
int getOption();

/**
 * @brief Handles printing all todo items in the header.
 * 
 * @param header Pointer to the Header struct containing the todo items.
 */
void handlePrintAll(Header* header);

/**
 * @brief Creates a new todo Node struct.
 * 
 * @param name The name of the todo item.
 * @param description The description of the todo item.
 * @return Pointer to the newly created Node struct.
 */
Node* createTodoStruct(char* name, char* description);

/**
 * @brief Adds a todo Node to the Header at a specified position.
 * 
 * @param header Pointer to the Header struct to add the Node to.
 * @param node Pointer to the Node struct to add.
 * @param position The position to add the Node at (0 for start, -1 for end, or specific index).
 * @return 0 on success, 1 on failure.
 */
int addTodo(Header* header, Node* node, long int position);

/**
 * @brief Handles adding a new todo.
 * 
 * @param header Pointer to the Header struct containing the todo items.
 */
void handleAddTodo(Header* header);

/**
 * @brief Handles getting todo by its Id.
 * 
 * @param header Pointer to the header struct containing the todo items.
*/
void handleGetTodoById(Header* header);


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
                handleGetTodoById(&header);
                break;

            case 3: // add todo
                handleAddTodo(&header);
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
    int option;
    printMenu();
    printf("\n\nSelect an option: ");
    // checks that the input is valid
    while (scanf("%d", &option) != 1) {
        //if input isnt valid clears the terminal and reask for the value
        while (getchar() != '\n');
        clear();
        printf("\nInvalid input!");
        waitForEnter();
        clear();
        printMenu();
        printf("\n\nSelect an option: ");
    }
    //clears the terminal from the '\n' that is left after a scanf
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
	if ((position > header->length || position < 0) && position != -1) {
        printf("Invalid position!");
        free(pNode);
        waitForEnter();
        return 1;
    }

	pNode->next = NULL;
	pNode->previous = NULL;

    if (position == 0) // start
    {
        if (header->first != NULL) {
			pNode->next = header->first;
			header->first->previous = pNode;
		} else {
			header->last = pNode;
		}
		header->first = pNode;

		header->length++;
    } else if (position == -1 || position == header->length) // end
    {
        if (header->last != NULL) {
			pNode->previous = header->last;
			header->last->next = pNode;
		} else {
			header->first = pNode;
		}
		header->last = pNode;

		header->length++;
    } else {
        Node* current = header->first;
        for (int i = 0; i < position; i++) {
            current = current->next;
        }
        pNode->next = current;
        pNode->previous = current->previous;
        current->previous->next = pNode;
        current->previous = pNode;
        header->length++;
    }
    return 0;
}

void handleAddTodo(Header* header)
{
    char name[MAX_NAME_LENGTH] = "";
    char description[MAX_DESCRIPTION_LENGTH] = "";
    printf("Todo name: ");
    if (fgets(name, sizeof(name), stdin) == NULL)
    {
        printf("\nAn error accured!");
        waitForEnter();
        return;
    }
    if (!strchr(name, '\n')) {
        while (fgetc(stdin) != '\n');
        printf("Input too long. It has been cut at %d\n", MAX_NAME_LENGTH-1);
    } else {
        name[strcspn(name, "\n")] = '\0';
    }
    printf("Description name: ");
    if (fgets(description, sizeof(description), stdin) == NULL)
    {
        printf("\nAn error accured!");
        waitForEnter();
        return;
    }
    if (!strchr(description, '\n')) {
        while (fgetc(stdin) != '\n');
        printf("Input too long. It has been cut at %d\n", MAX_DESCRIPTION_LENGTH-1);
    } else {
        description[strcspn(description, "\n")] = '\0';
    }

    if (addTodo(header, createTodoStruct(name, description), -1) == 1)
    {
        return;
    }

    clear();
    printf("Todo added!\n");
    waitForEnter();
}

void handleGetTodoById(Header* header)
{
    size_t todoId;
    
    printf("Give devices id: ");
    
    if (scanf("%d", &todoId) != 1) {
        while (getchar() != '\n');
        clear();
        printf("\nInvalid input!");
        waitForEnter();
        clear();
    }
    while (getchar() != '\n');
}