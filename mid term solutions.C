// Question 1. Step count.
#include <stdio.h>
#define DAYS 30

struct Member {
    char name[50];
    int steps[DAYS];
};

void analyzeSteps(struct Member members[], int n) {
    for (int i = 0; i < n; i++) {
        int count = 0;
        int max = members[i].steps[0];

        for (int j = 0; j < DAYS; j++) {
            if (members[i].steps[j] > 10000)
                count++;
            if (members[i].steps[j] > max)
                max = members[i].steps[j];
        }

        printf("\nMember: %s\n", members[i].name);
        printf("Days exceeding 10,000 steps: %d\n", count);
        printf("Maximum step count in the month: %d\n", max);
    }
}

int main() {
    struct Member members[2] = {
        {"Amit", {12000,9000,11000,8000,15000,13000,7000,10000,9500,12500,
                  8700,9100,10500,11300,7200,10200,9700,10050,8900,9200,
                  8700,12300,9900,10400,8700,8800,9100,10100,9400,9800}},
        {"Rahul", {5000,6000,7000,8000,9000,4000,3000,2000,1000,9500,
                   10500,11000,12000,8000,7500,10000,9500,8800,9900,10300,
                   7000,7200,8100,8900,9400,9700,10800,11200,9500,10000}}
    };

    analyzeSteps(members, 2);
    return 0;
}



// Question 2. Swap in the playlist.
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int songID;
    struct Node* next;
};

struct Node* createNode(int id) {
    struct Node* new = (struct Node*)malloc(sizeof(struct Node));
    new->songID = id;
    new->next = NULL;
    return new;
}

void printList(struct Node* head) {
    while (head) {
        printf("%d -> ", head->songID);
        head = head->next;
    }
    printf("NULL\n");
}

struct Node* reverseSegment(struct Node* head, int m, int n) {
    if (!head || m >= n)
        return head;

    struct Node *prev = NULL, *curr = head;
    for (int i = 1; i < m; i++) {
        prev = curr;
        curr = curr->next;
    }

    struct Node* segmentStart = prev;
    struct Node* tail = curr;
    struct Node* next = NULL;

    for (int i = 0; i <= n - m; i++) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    if (segmentStart)
        segmentStart->next = prev;
    else
        head = prev;

    tail->next = curr;
    return head;
}

int main() {
    struct Node* head = createNode(101);
    head->next = createNode(102);
    head->next->next = createNode(103);
    head->next->next->next = createNode(104);
    head->next->next->next->next = createNode(105);
    head->next->next->next->next->next = createNode(106);
    head->next->next->next->next->next->next = createNode(107);

    printf("Original Playlist:\n");
    printList(head);

    head = reverseSegment(head, 2, 5);

    printf("Modified Playlist:\n");
    printList(head);

    return 0;
}



// Lab Question 2. Call queue. 
#include <stdio.h>
#define SIZE 5

int queue[SIZE];
int front = -1;
int rear = -1;

void addCall(int customerID) {
    if ((front == 0 && rear == SIZE - 1) || (rear + 1) % SIZE == front) {
        printf("Queue is full. Please wait.\n");
        return;
    }

    if (front == -1) {
        front = 0;
        rear = 0;
    } else {
        rear = (rear + 1) % SIZE;
    }

    queue[rear] = customerID;
    printf("Call added: %d\n", customerID);
}

void removeCall() {
    if (front == -1) {
        printf("No calls to remove.\n");
        return;
    }

    printf("Removed customer: %d\n", queue[front]);

    if (front == rear) {
        front = -1;
        rear = -1;
    } else {
        front = (front + 1) % SIZE;
    }
}

void displayQueue() {
    if (front == -1) {
        printf("No customers in queue.\n");
        return;
    }

    printf("Customers in queue: ");
    int i = front;
    while (1) {
        printf("%d ", queue[i]);
        if (i == rear)
            break;
        i = (i + 1) % SIZE;
    }
    printf("\n");
}

int main() {
    addCall(101);
    addCall(102);
    addCall(103);
    addCall(104);
    addCall(105);
    displayQueue();

    addCall(106);

    removeCall();
    removeCall();
    displayQueue();

    addCall(106);
    addCall(107);
    displayQueue();

    return 0;
}



// Lab Question 3. Undo and Redo Stack.
#include <stdio.h>
#define MAX 100

int undo[MAX];
int redo[MAX];
int top_Undo = -1;
int top_Redo = -1;

void clearRedo() {
    top_Redo = -1;
}

void performOperation(int op) {
    top_Undo = top_Undo + 1;
    undo[top_Undo] = op;
    clearRedo();
    printf("Performed operation %d\n", op);
}

void undoOperation() {
    if (top_Undo == -1) {
        printf("Nothing to undo!\n");
    } else {
        int op = undo[top_Undo];
        top_Undo = top_Undo - 1;
        top_Redo = top_Redo + 1;
        redo[top_Redo] = op;
        printf("Undo operation %d\n", op);
    }
}

void redoOperation() {
    if (top_Redo == -1) {
        printf("Nothing to redo!\n");
    } else {
        int op = redo[top_Redo];
        top_Redo = top_Redo - 1;
        top_Undo = top_Undo + 1;
        undo[top_Undo] = op;
        printf("Redo operation %d\n", op);
    }
}

void displayStacks() {
    int i;
    printf("\nUndo Stack: ");
    if (top_Undo == -1)
        printf("Empty");
    else
        for (i = 0; i <= top_Undo; i++)
            printf("%d ", undo[i]);

    printf("\nRedo Stack: ");
    if (top_Redo == -1)
        printf("Empty");
    else
        for (i = 0; i <= top_Redo; i++)
            printf("%d ", redo[i]);

    printf("\n");
}

int main() {
    performOperation(10);
    performOperation(20);
    performOperation(30);

    undoOperation();
    redoOperation();

    displayStacks();

    return 0;
}
