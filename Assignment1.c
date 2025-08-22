#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tab {
    int pageID;
    char url[100];
    struct Tab *prev, *next;
} Tab;

Tab *head = NULL, *current = NULL;
int idCounter = 1;

// Function prototypes
void visitNewPage(char url[]);
void goBack();
void goForward();
void showCurrentTab();
void closeCurrentTab();
void showHistory();

int main() {
    int choice;
    char url[100];

    while (1) {
        printf("\n--- Browser Menu ---\n");
        printf("1. Visit a new page\n");
        printf("2. Go back\n");
        printf("3. Go forward\n");
        printf("4. Show current tab\n");
        printf("5. Close current tab\n");
        printf("6. Show history\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter URL: ");
                scanf("%s", url);
                visitNewPage(url);
                break;
            case 2: goBack(); break;
            case 3: goForward(); break;
            case 4: showCurrentTab(); break;
            case 5: closeCurrentTab(); break;
            case 6: showHistory(); break;
            case 7: exit(0);
            default: printf("Invalid choice!\n");
        }
    }
}

// Function definitions
void visitNewPage(char url[]) {
    Tab newTab = (Tab)malloc(sizeof(Tab));
    newTab->pageID = idCounter++;
    strcpy(newTab->url, url);
    newTab->prev = current;
    newTab->next = NULL;

    if (current) current->next = newTab;
    else head = newTab;

    current = newTab;
    printf("Opened new page [ID: %d, URL: %s]\n", current->pageID, current->url);
}

void goBack() {
    if (current && current->prev) {
        current = current->prev;
        showCurrentTab();
    } else printf("No previous tab!\n");
}

void goForward() {
    if (current && current->next) {
        current = current->next;
        showCurrentTab();
    } else printf("No forward tab!\n");
}

void showCurrentTab() {
    if (current)
        printf("Current tab [ID: %d, URL: %s]\n", current->pageID, current->url);
    else
        printf("No tab open!\n");
}

void closeCurrentTab() {
    if (!current) {
        printf("No tab to close!\n");
        return;
    }
    printf("Closing tab [ID: %d, URL: %s]\n", current->pageID, current->url);

    if (current->prev) current->prev->next = current->next;
    if (current->next) current->next->prev = current->prev;

    Tab *temp = current;
    if (current->next) current = current->next;
    else current = current->prev;

    if (temp == head) head = temp->next;

    free(temp);
}

void showHistory() {
    Tab *temp = head;
    if (!temp) {
        printf("No history!\n");
        return;
    }
    printf("History:\n");
    while (temp) {
        printf("[ID: %d, URL: %s]\n", temp->pageID, temp->url);
        temp = temp->next;
    }
}
