#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent an item (product or service)
struct Item {
    char name[50];
    double price;
    int quantity;
    struct Item* next;
};

// Function to create a new item
struct Item* createItem(char name[], double price, int quantity) {
    struct Item* newItem = (struct Item*)malloc(sizeof(struct Item));
    if (newItem == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    strncpy(newItem->name, name, sizeof(newItem->name));
    newItem->price = price;
    newItem->quantity = quantity;
    newItem->next = NULL;
    return newItem;
}

// Function to add an item to the linked list
struct Item* addItem(struct Item* head, char name[], double price, int quantity) {
    struct Item* newItem = createItem(name, price, quantity);

    if (head == NULL) {
        return newItem;
    } else {
        struct Item* current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newItem;
        return head;
    }
}

// Function to delete an item from the linked list
struct Item* deleteItem(struct Item* head, char name[]) {
    if (head == NULL) {
        printf("The list is empty.\n");
        return head;
    }

    struct Item* current = head;
    struct Item* prev = NULL;

    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            if (prev == NULL) {
                head = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            return head;
        }
        prev = current;
        current = current->next;
    }

    printf("Item '%s' not found in the list.\n", name);
    return head;
}

// Function to update the quantity of an item
void updateItem(struct Item* head, char name[], int newQuantity) {
    struct Item* current = head;

    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            current->quantity = newQuantity;
            return;
        }
        current = current->next;
    }

    printf("Item '%s' not found in the list.\n", name);
}

// Function to calculate the total bill
double calculateTotal(struct Item* head) {
    double total = 0.0;
    struct Item* current = head;

    while (current != NULL) {
        total += (current->price * current->quantity);
        current = current->next;
    }

    return total;
}

// Function to calculate the balance to be given to the customer
double calculateBalance(struct Item* head) {
    double total = 0.0;
    double balance = 0.0;
    double cc = 0.0;
    struct Item* current = head;

    printf("Enter the amount and view balance: ");
    scanf("%lf", &cc);  // Use %lf for reading a double.

    while (current != NULL) {
        total += (current->price * current->quantity);
        current = current->next;
    }

    balance = total - cc;

    return balance;
}

// Function to display the bill
void displayBill(struct Item* head) {
    struct Item* current = head;

    printf("************ BILL ************\n");
    printf("%-30s %-10s %-10s\n", "Item", "Price", "Quantity");
    printf("-------------------------------\n");

    while (current != NULL) {
        printf("%-30s RS :%-9.2f %-10d\n", current->name, current->price, current->quantity);
        current = current->next;
    }

    printf("-------------------------------\n");
    printf("Total: RS:%.2f\n", calculateTotal(head));

    printf("-------------------------------\n");
    printf("collect cash from the customer :\n");
    printf("Balance: RS%.2f\n", calculateBalance(head));  // Corrected printf statement.
}

// Function to free the memory allocated for the linked list
void freeList(struct Item* head) {
    struct Item* current = head;
    while (current != NULL) {
        struct Item* temp = current;
        current = current->next;
        free(temp);
    }
}

int main() {
    struct Item* itemList = NULL;
    char name[50];
    double price;
    int quantity;
    char choice;

    do {
        printf("Enter the item name: ");
        scanf("%s", name);

        printf("Enter the item price: ");
        scanf("%lf", &price);

        printf("Enter the quantity: ");
        scanf("%d", &quantity);

        itemList = addItem(itemList, name, price, quantity);//to add the item with the entered information to the itemList

        printf("Do you want to add another item? (y/n): ");
        scanf(" %c", &choice);
    } while (choice == 'y' || choice == 'Y');

    // Display the initial bill
    displayBill(itemList);

    do {
    printf("Do you want to update or delete an item? (u/d/n): ");
    scanf(" %c", &choice);

    if (choice == 'u' || choice == 'U') {
        printf("Enter the name of the item to update: ");
        scanf("%s", name);
        printf("Enter the new quantity: ");
        scanf("%d", &quantity);  // Use %d for reading an integer.
        updateItem(itemList, name, quantity);
    } else if (choice == 'd' || choice == 'D') {
        printf("Enter the name of the item to delete: ");
        scanf("%s", name);
        itemList = deleteItem(itemList, name);
    }
    else{
        break;
    }

    printf("Do you want to update or delete another item? (y/n): ");
    scanf(" %c", &choice);

} while (choice == 'y' || choice == 'Y');


    // Display the final bill
    displayBill(itemList);

    // Free memory
    freeList(itemList);

    return 0;
}
