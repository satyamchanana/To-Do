#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct ToDo {
    int count;
    char task[100];
    int done;
} todo;
void addtask();
void viewtask();
void taskdone();
void deltask();
int getTaskCount(); 
int main() {
    int chs;
    do {
        printf("\t\t *ToDO* \t\t\n");
        printf("Enter Choice\n");
        printf("1. Add task\n");
        printf("2. View tasks\n");
        printf("3. Mark task done\n");
        printf("4. Delete task\n");
        printf("5. Exit\n");     
        scanf("%d", &chs); 
        getchar(); 
        switch (chs) {
            case 1:
                addtask();
                break;
            case 2:
                viewtask();
                break;
            case 3:
                taskdone();
                break;
            case 4:
                deltask();
                break;
            case 5:
                printf("Exit Initiated\n");
                break;
            default:
                printf("\nError 404: Invalid choice\n");
        }
    } while (chs != 5); 
        return 0;
}

int getTaskCount() {
    FILE *fp = fopen("ToDo.csv", "r");
    if (fp == NULL) {
        return 1; 
    }
    todo task;
    int maxCount = 0;
   while (fscanf(fp, "%d,%[^,],%d", &task.count, task.task, &task.done) != EOF) {
        if (task.count > maxCount) {
            maxCount = task.count;
        }
    }
    fclose(fp);
    return maxCount + 1; 
}
void addtask() 
{
    system("cls");
    FILE *fp = fopen("ToDo.csv", "a");
    if (fp == NULL) {
        printf("Error 404: File not found.\n");
        return;
    }
    todo newtask;
    int taskCount = getTaskCount(); 
   do {
        printf("Type new task or press enter to stop: ");
        fgets(newtask.task, 100, stdin);
        newtask.task[strcspn(newtask.task, "\n")] = 0;
        if (newtask.task[0] == '\0') {
            break;
        }
        newtask.done = 0;
        fprintf(fp, "%d,%s,%d\n", taskCount, newtask.task, newtask.done);
        taskCount++; 
        printf("ToDo added successfully!\n");
    } while (1);
    fclose(fp);
    printf("All tasks have been saved.\n");
}
void viewtask() 
{ system("cls");
    FILE *fp = fopen("ToDo.csv", "r");
    if (fp == NULL) {
        printf("No todo's for today\n");
        return;
    }
    todo task;
    printf("S.no\t\tToDo\t\t\tStatus\n");
    printf("--------------------------------------------\n");
    while (fscanf(fp, "%d,%[^,],%d", &task.count, task.task, &task.done) != EOF) {
        printf("%d\t\t%-30s\t%s\n", task.count, task.task, task.done ? "Done" : "ToDo");
    }
    fclose(fp);
}
void taskdone() 
{
    viewtask();
    FILE *fp = fopen("ToDo.csv", "r");
    if (fp == NULL) {
        printf("Error 404: File not found.\n");
        return;
    }
    FILE *temp = fopen("temp.csv", "w");
    if (temp == NULL) {
        printf("Error creating temporary file.\n");
        fclose(fp);
        return;
    }
    todo task;
    int taskno, found = 0;
    printf("Enter the task number to mark as done: ");
    scanf("%d", &taskno);
    while (fscanf(fp, "%d,%[^,],%d", &task.count, task.task, &task.done) != EOF) {        if (task.count == taskno) {
            found = 1;
            if (task.done == 1)
			 {
                printf("Task %d is already marked as done. Cannot mark it again.\n", taskno);
            } else 
			{
                task.done = 1;
                printf("Task %d marked as done!\n", taskno);
            }
        }
                fprintf(temp, "%d,%s,%d\n", task.count, task.task, task.done);
    }
    if (!found) {
        printf("Task not found.\n");
    }
    fclose(fp);
    fclose(temp);
    remove("ToDo.csv");
    rename("temp.csv", "ToDo.csv");
}


void deltask() 
{
    system("cls");
    viewtask();

    FILE *fp = fopen("ToDo.csv", "r");
    if (fp == NULL) {
        printf("Error 404: File not found.\n");
        return;
    }
    FILE *temp = fopen("temp.csv", "w");
    if (temp == NULL) {
        printf("Error creating temporary file.\n");
        fclose(fp);
        return;
    }
    todo task;
    int taskno, found = 0;
    printf("Enter the task number to delete: ");
    scanf("%d", &taskno);
    while (fscanf(fp, "%d,%[^,],%d", &task.count, task.task, &task.done) != EOF) {
        if (task.count != taskno) {
            fprintf(temp, "%d,%s,%d\n", task.count, task.task, task.done);
        } else {
            found = 1;
            printf("Task %d deleted successfully!\n", taskno);
        }
    }
    if (!found) {
        printf("Task not found.\n");
    }
    fclose(fp);
    fclose(temp);
    remove("ToDo.csv");
    rename("temp.csv", "ToDo.csv");
}

