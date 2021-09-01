/*
 * actually the implementation changed not so much due to initially implementation of methods
 * but the benefits of using doubly linked list can be enjoyed later when some other methods is gonna be
 * implemented
 * */
    
#include <stdio.h>
#include <stdlib.h>

typedef struct node Node;

struct node {
    int isTail;
    int isHead;
    int value;
    Node *prevNode;
    Node *nextNode;
};

void printList(Node *linkedList);

void insertNode(Node *linkedList, int value, int index);

void deleteNode(Node *linkedList, int index);

int main() {
    Node list; // declaring the linked list
    list.value = 0;
    list.isHead;
    list.isTail = 1; // initialization of first element
    printList(&list); // printing whole list
    insertNode(&list, 1, 1); // adding integer to arbitrary position in the list
    insertNode(&list, 10, 0);
    insertNode(&list, 2, 2);
    insertNode(&list, 3, 2);
    insertNode(&list, 5, 5);
    printList(&list);
    deleteNode(&list, 3); // removing element from arbitrary position of the list
    printList(&list);
}

void printList(Node *linkedList) {
    Node *current = linkedList;
    for (;;) {
        printf("%d ", current->value);
        if (current->isTail == 0) {
            current = current->nextNode;
        } else {
            break;
        }
    }
    printf("\n");
}

void insertNode(Node *linkedList, int value, int index) {
    if (index == 0) {
        Node *newNode = (Node *) malloc(sizeof(Node));
        newNode->value = linkedList->value;
        newNode->nextNode = linkedList->nextNode;
        newNode->isTail = linkedList->isTail;
        newNode->isHead = 0;
        newNode->prevNode = linkedList;
        linkedList->value = value;
        linkedList->nextNode = newNode;
        linkedList->isTail = 0;
        return;
    }
    Node *current = linkedList;
    for (int i = 0; i < index - 1; ++i) {
        current = current->nextNode;
        if (current->isTail == 1 && (i + 1) < index - 1) {
            printf("ERROR: Index out of range exception.\n");
            return;
        }
    }
    Node *newNode = (Node *) malloc(sizeof(Node));
    newNode->value = value;
    newNode->nextNode = current->nextNode;
    newNode->prevNode = current;
    newNode->isTail = current->isTail;
    newNode->isHead = 0;
    current->isTail = 0;
    current->nextNode = newNode;
}

void deleteNode(Node *linkedList, int index) {
    if (index == 0) {
        Node *toFree = linkedList;
        *linkedList = *linkedList->nextNode;
        linkedList->isHead = 1;
        free(toFree);
        return;
    }
    Node *current = linkedList;
    for (int i = 0; i < index - 1; ++i) {
        current = current->nextNode;
        if (current->isTail == 1 && (i + 1) <= index - 1) {
            printf("ERROR: Index out of range exception.\n");
            return;
        }
    }
    if (current->nextNode->isTail == 1) {
        current->isTail = 1;
        free(current->nextNode);
    } else {
        Node *toFree = current->nextNode;
        current->nextNode = current->nextNode->nextNode;
        current->nextNode->prevNode = current;
        free(toFree);
    }
}