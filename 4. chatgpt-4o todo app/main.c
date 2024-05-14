#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TASK_NAME_LENGTH 100

// Structure to represent a task
typedef struct Task {
    char name[TASK_NAME_LENGTH];
    struct Task *next;
} Task;

// Function prototypes
void addTask(Task **head, const char *name);
void removeTask(Task **head, int index);
void displayTasks(Task *head);
void saveTasks(Task *head, const char *filename);
void loadTasks(Task **head, const char *filename);
void clearTasks(Task **head);
int getTaskCount(Task *head);
void printMenu();
void clearInputBuffer();

int main() {
    Task *taskList = NULL;
    char taskName[TASK_NAME_LENGTH];
    int choice, taskIndex;
    const char *filename = "tasks.txt";

    loadTasks(&taskList, filename);

    while (1) {
        printMenu();
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            clearInputBuffer();
            printf("Invalid input. Please enter a number.\n");
            continue;
        }
        getchar(); // Consume newline character

        switch (choice) {
            case 1:
                printf("Enter task name (max %d characters): ", TASK_NAME_LENGTH - 1);
                if (fgets(taskName, TASK_NAME_LENGTH, stdin) == NULL) {
                    printf("Failed to read task name.\n");
                    continue;
                }
                if (taskName[strlen(taskName) - 1] != '\n') {
                    clearInputBuffer(); // Discard excess characters
                }
                taskName[strcspn(taskName, "\n")] = 0; // Remove newline character
                addTask(&taskList, taskName);
                break;
            case 2:
                displayTasks(taskList);
                break;
            case 3:
                printf("Enter task index to remove: ");
                if (scanf("%d", &taskIndex) != 1) {
                    clearInputBuffer();
                    printf("Invalid input. Please enter a number.\n");
                    continue;
                }
                removeTask(&taskList, taskIndex);
                break;
            case 4:
                saveTasks(taskList, filename);
                printf("Tasks saved.\n");
                break;
            case 5:
                clearTasks(&taskList);
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

void addTask(Task **head, const char *name) {
    Task *newTask = (Task *)malloc(sizeof(Task));
    if (!newTask) {
        printf("Memory allocation failed.\n");
        return;
    }
    strncpy(newTask->name, name, TASK_NAME_LENGTH - 1);
    newTask->name[TASK_NAME_LENGTH - 1] = '\0'; // Ensure null-termination
    newTask->next = *head;
    *head = newTask;
}

void removeTask(Task **head, int index) {
    if (index < 0 || !*head) {
        printf("Invalid task index.\n");
        return;
    }

    Task *current = *head;
    Task *previous = NULL;

    for (int i = 0; i < index; ++i) {
        if (!current) {
            printf("Invalid task index.\n");
            return;
        }
        previous = current;
        current = current->next;
    }

    if (previous) {
        previous->next = current->next;
    } else {
        *head = current->next;
    }

    free(current);
}

void displayTasks(Task *head) {
    int index = 0;
    for (Task *current = head; current != NULL; current = current->next) {
        printf("%d: %s\n", index++, current->name);
    }
}

void saveTasks(Task *head, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Failed to open file for writing.\n");
        return;
    }

    for (Task *current = head; current != NULL; current = current->next) {
        fprintf(file, "%s\n", current->name);
    }

    fclose(file);
}

void loadTasks(Task **head, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("No existing task file found. Starting fresh.\n");
        return;
    }

    char taskName[TASK_NAME_LENGTH];
    while (fgets(taskName, TASK_NAME_LENGTH, file)) {
        taskName[strcspn(taskName, "\n")] = 0; // Remove newline character
        addTask(head, taskName);
    }

    fclose(file);
}

void clearTasks(Task **head) {
    Task *current = *head;
    while (current) {
        Task *temp = current;
        current = current->next;
        free(temp);
    }
    *head = NULL;
}

void printMenu() {
    printf("\nTODO List Menu:\n");
    printf("1. Add Task\n");
    printf("2. Display Tasks\n");
    printf("3. Remove Task\n");
    printf("4. Save Tasks\n");
    printf("5. Exit\n");
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
