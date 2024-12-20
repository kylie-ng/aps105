#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "linkedlist.h"

// Node structure and Linked List structure is already defined in linkedlist.h
// file

// Define Resistor structure
typedef struct {
  int value;       // "1. Value of the resistance in Ohms"
  char label[50];  // "2. Label of the resistor"
} Resistor;

// Given function headers
void handleInsert(LinkedList*);
void handleRemove(LinkedList*);
void handleCurrentCal(LinkedList*, int voltage);  // added "voltage"
void handleVoltage(LinkedList*, int voltage);     // added "voltage"
void handlePrint(LinkedList*);
void handleQuit(LinkedList*);

// My added function headers
int getListSize(LinkedList* list);
void insertIntoOrderedList(LinkedList* list, char* label, Resistor* resistor);
bool existResistor(LinkedList* list, char* label);
Resistor* removeFromList(LinkedList* list, char* label);

int main(void) {
  LinkedList circuit;  // declares variable "circuit" of type "LinkedList"
  initList(&circuit);  // in linkedlist.h: the head initially points to NULL
  char command;
  printf("Welcome to our circuit simulator\n");
  // Enter the source voltage!
  printf("What is the source of the voltage?\n");
  int voltage;
  readInputNumber(&voltage);  // already done for me in linkedlist.h

  while (command != 'Q') {
    command = getCommand();

    switch (command) {
      case 'I':
        handleInsert(&circuit);
        break;
      case 'R':
        handleRemove(&circuit);
        break;
      case 'C':
        handleCurrentCal(&circuit, voltage);
        break;
      case 'V':
        handleVoltage(&circuit, voltage);
        break;
      case 'P':
        handlePrint(&circuit);
        break;
      case 'Q':
        handleQuit(&circuit);
        break;
    }
  }
  return 0;
}

// My added Function: Get the size of the linked list
int getListSize(LinkedList* list) {
  int size = 0;
  Node* current =
      list->head;  // Initialize current (of type Node*) to point to the "head"
                   // of the linked list passed as an argument, "list"
  while (current !=
         NULL) {  // while loop that iterates over each node in the linked list
    size++;
    current = current->next;
  }
  return size;
}

// My added Function: Insert nodes into an ordered list
void insertIntoOrderedList(LinkedList* list, char* label, Resistor* resistor) {
  Node* newNode = (Node*)malloc(sizeof(Node));

  newNode->value = (void*)resistor;
  strncpy(newNode->name, label, STRING_MAX);
  newNode->next = NULL;

  // If list is empty or new node should be inserted at the beginning based on
  // lexicographical order of labels
  if (list->head == NULL || strcmp(label, list->head->name) < 0) {
    newNode->next = list->head;  // updates the next pointer of the new node to
                                 // point to the current head of the list
    list->head = newNode;        // assigns the newNode to the head of list
    return;
  }

  Node* current = list->head;
  if (current->next != NULL && strcmp(label, current->next->name) == 0) {
    printf("A resistor with %s label already exists.\n", label);
  }

  // Traverse the list and insert at correct position
  while (current->next != NULL && strcmp(label, current->next->name) >= 0) {
    current = current->next;
  }

  // Insert the new node after the current node
  newNode->next = current->next;
  current->next = newNode;
}

// My added function: see if resistor label name already exists by traversing
// through the linked list
// Traverse the list to find the node with the matching label
bool existResistor(LinkedList* circuit, char* labelName) {
  Node* current;
  current = circuit->head;
  while (current != NULL) {
    if (strcmp(current->name, labelName) == 0) {
      printf("A resistor with %s label already exists.\n", labelName);
      return true;
    } else {
      current = current->next;
    }
  }
  return false;
}

// My added function: remove node from list
Resistor* removeFromList(LinkedList* list, char* label) {
  // Check if the list is empty
  if (list->head == NULL) {
    return NULL;
  }

  Node* current = list->head;
  Node* prev = NULL;

  // Traverse the list to find the node with the matching label
  while (current != NULL) {
    if (strcmp(current->name, label) == 0) {
      // If the label matches, remove the node
      if (prev != NULL) {
        prev->next = current->next;  // Update the previous node's next pointer
      } else {
        list->head =
            current
                ->next;  // Update the head pointer if the first node is removed
      }

      Resistor* removedResistor = (Resistor*)current->value;
      free(current);           // Free the memory allocated for the removed node
      return removedResistor;  // Return the removed resistor
    }
    prev = current;
    current = current->next;
  }

  return NULL;  // Return NULL if the label is not found in the list
}

void handleInsert(LinkedList* circuit) {
  int resistance = 0;
  printf("What's the value of the resistor: ");
  readInputNumber(&resistance);
  printf("What's the label of the resistor: ");
  char labelName[STRING_MAX];
  readInputString(labelName, STRING_MAX);
  if (existResistor(circuit, labelName)) {
    return;
  } else {
    // Create a new resistor
    Resistor* newResistor = malloc(sizeof(Resistor));
    if (newResistor == NULL) {
      return;
    }
    newResistor->value = resistance;
    strcpy(newResistor->label, labelName);
    // TODO: Implement the insert into ordered list function
    insertIntoOrderedList(circuit, labelName, newResistor);
  }
}

void handleRemove(LinkedList* circuit) {
  // TODO: Implement the remove function
  char labelName[STRING_MAX];
  printf("What's the label of the resistor you want to remove: ");
  readInputString(labelName, STRING_MAX);
  // Remove from the linked list
  Resistor* removedResistor = removeFromList(circuit, labelName);
  if (removedResistor == NULL) {
    printf("The resistor with %s label does not exist.\n", labelName);
  } else {
    free(removedResistor);
  }
}

void handleCurrentCal(LinkedList* circuit, int voltage) {
  // TODO: Implement the function that prints the value of current in the
  // circuit
  double totalResistance = 0.0;
  Node* current = circuit->head;
  while (current != NULL) {
    Resistor* resistor = (Resistor*)current->value;
    totalResistance += resistor->value;
    current = current->next;
  }
  double currentDouble = voltage / totalResistance;
  printf("The current in the circuit is %.6lfA\n", currentDouble);
}

void handleVoltage(LinkedList* circuit, int voltage) {
  // Copy and pasted from handleCurrent, basically doing it again without having
  // to go through trouble of passing through functions and returning from a
  // void function handleCurrent
  double totalResistance = 0.0;
  Node* current = circuit->head;
  while (current != NULL) {
    Resistor* resistor = (Resistor*)current->value;
    totalResistance += resistor->value;
    current = current->next;
  }
  double currentDouble = voltage / totalResistance;
  // TODO: Implement the function that prints the potential difference across a
  // resistor
  char labelName[STRING_MAX];
  printf(
      "What's the label of the resistor you want to find the voltage across: ");
  readInputString(labelName, STRING_MAX);

  current = circuit->head;
  while (current != NULL) {
    Resistor* resistor = (Resistor*)current->value;
    if (strcmp(resistor->label, labelName) == 0) {
      double voltageAcross = (currentDouble * resistor->value);
      printf("Voltage across resistor is %.6lfV\n", voltageAcross);
      return;
    }
    current = current->next;
  }
  printf("The resistor with %s label does not exist.\n", labelName);
}

void handlePrint(LinkedList* circuit) {
  // TODO: they can implement the print function
  int size = getListSize(circuit);
  Node* current = circuit->head;  // Define current node
  while (current != NULL) {
    Resistor* resistor = (Resistor*)current->value;
    printf("%s  %d Ohms\n", resistor->label, resistor->value);
    current = current->next;
  }
}

void handleQuit(LinkedList* circuit) {
  printf("Removing all resistors in the circuit...\n");
  handlePrint(circuit);
  Node* current = circuit->head;
  while (current !=
         NULL) {  // there are still nodes in the linked list to process
    Node* temp = current;
    current = current->next;
    free(temp);  // deallocates memory previously allocated for the node, thus
                 // removing it from the linked list
  }
  circuit->head = NULL;  // indicates an empty list
}
