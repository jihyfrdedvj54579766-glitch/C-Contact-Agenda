/*
    Contact Agenda with Persistence & Search
    ----------------------
    A simple contact management program written in C.
    Features: add/delete/show/search contacts, save/load to file.
*/

#include <stdio.h>
#include <string.h>

// Replace hard-coded values with macros for better maintainability
#define MAX_NAME_LEN 100
#define MAX_PHONE_LEN 20
#define MAX_EMAIL_LEN 100
#define MAX_CONTACTS 100
#define DATA_FILE "contacts.txt"

// Define the contact structure
struct contactAgenda {
    char name[MAX_NAME_LEN];
    char phone[MAX_PHONE_LEN];
    char email[MAX_EMAIL_LEN];
};

// Function prototypes
// Implement loadContacts() and saveContacts()
// Load data from file on startup, save to contacts.txt/binary file on exit
// Avoid data loss after program restart
void showContacts(int numContacts, const struct contactAgenda contacts[]);
void addContact(struct contactAgenda contacts[], int* numContacts);
void deleteContact(struct contactAgenda contacts[], int* numContacts);
void searchContact(int numContacts, const struct contactAgenda contacts[]);
void saveContacts(int numContacts, const struct contactAgenda contacts[]);
int loadContacts(struct contactAgenda contacts[]);
void clearInputBuffer();

int main() {
    int numContacts = 0, choice;
    struct contactAgenda contacts[MAX_CONTACTS];

    // Load contacts from file on startup
    numContacts = loadContacts(contacts);
    printf("Loaded %d contacts from %s\n", numContacts, DATA_FILE);

    // Main menu loop
    while (1) {
        printf("\n----- Contact Agenda Menu -----\n");
        printf("1. Show all Contacts\n");
        printf("2. Add a Contact\n");
        printf("3. Delete a Contact\n");
        printf("4. Search Contact\n");
        printf("5. Exit & Save\n");
        printf("Choose an option: ");
        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice) {
            case 1:
                showContacts(numContacts, contacts);
                break;
            case 2:
                addContact(contacts, &numContacts);
                break;
            case 3:
                deleteContact(contacts, &numContacts);
                break;
            case 4:
                searchContact(numContacts, contacts);
                break;
            case 5:
                saveContacts(numContacts, contacts);
                printf("Contacts saved to %s. Exiting.\n", DATA_FILE);
                return 0;
            default:
                printf("Invalid option. Please try again.\n");
                break;
        }
    }
}

// Show all contacts
void showContacts(int numContacts, const struct contactAgenda contacts[]) {
    if (numContacts == 0) {
        printf("No contacts available.\n");
        return;
    }
    for (int i = 0; i < numContacts; i++) {
        printf("Contact %d:\n", i + 1);
        printf("Name: %s\n", contacts[i].name);
        printf("Phone: %s\n", contacts[i].phone);
        printf("Email: %s\n", contacts[i].email);
        printf("-----------------------\n");
    }
}

// Add a new contact
void addContact(struct contactAgenda contacts[], int* numContacts) {
    if (*numContacts >= MAX_CONTACTS) {
        printf("Contact list is full!\n");
        return;
    }

    printf("Enter contact name: ");
    scanf(" %[^\n]", contacts[*numContacts].name);
    clearInputBuffer();

    printf("Enter contact phone: ");
    scanf(" %[^\n]", contacts[*numContacts].phone);
    clearInputBuffer();

    printf("Enter contact email: ");
    scanf(" %[^\n]", contacts[*numContacts].email);
    clearInputBuffer();

    (*numContacts)++;
    printf("Contact added successfully!\n");
}

// Delete a contact by index
void deleteContact(struct contactAgenda contacts[], int* numContacts) {
    int index;
    if (*numContacts == 0) {
        printf("No contacts to delete.\n");
        return;
    }

    printf("Enter contact number to delete (1-%d): ", *numContacts);
    scanf("%d", &index);
    clearInputBuffer();

    if (index < 1 || index > *numContacts) {
        printf("Invalid contact number.\n");
        return;
    }

    // Shift contacts to remove the specified one
    for (int i = index - 1; i < *numContacts - 1; i++) {
        contacts[i] = contacts[i + 1];
    }
    (*numContacts)--;
    printf("Contact deleted successfully!\n");
}

// Search contacts by name, phone, or email
void searchContact(int numContacts, const struct contactAgenda contacts[]) {
    if (numContacts == 0) {
        printf("No contacts available.\n");
        return;
    }

    int choice;
    char keyword[MAX_EMAIL_LEN]; // Sufficient to store email address
    int found = 0;

   // Search method menu
    printf("\n--- Search By ---\n");
    printf("1. Name\n");
    printf("2. Phone\n");
    printf("3. Email\n");
    printf("Choose search type: ");
    scanf("%d", &choice);
    clearInputBuffer();

   // Enter search keyword
    printf("Enter keyword to search: ");
    scanf(" %[^\n]", keyword);
    clearInputBuffer();

    printf("\n=== Search Results ===\n");

    for (int i = 0; i < numContacts; i++) {
        int match = 0;

        switch (choice) {
            case 1: //By name
                if (strstr(contacts[i].name, keyword) != NULL) match = 1;
                break;
            case 2: // By phone number
                if (strstr(contacts[i].phone, keyword) != NULL) match = 1;
                break;
            case 3: // By email
                if (strstr(contacts[i].email, keyword) != NULL) match = 1;
                break;
            default:
                printf("Invalid search type.\n");
                return;
        }

        if (match) {
            printf("Contact %d:\n", i + 1);
            printf("Name: %s\n", contacts[i].name);
            printf("Phone: %s\n", contacts[i].phone);
            printf("Email: %s\n", contacts[i].email);
            printf("-----------------------\n");
            found = 1;
        }
    }

    if (!found) {
        printf("No matching contacts found.\n");
    }
}

// Save contacts to file
void saveContacts(int numContacts, const struct contactAgenda contacts[]) {
    FILE* fp = fopen(DATA_FILE, "w");
    if (fp == NULL) {
        perror("Failed to open file for writing");
        return;
    }

    for (int i = 0; i < numContacts; i++) {
        fprintf(fp, "%s;%s;%s\n", contacts[i].name, contacts[i].phone, contacts[i].email);
    }
    fclose(fp);
}

// Load contacts from file
int loadContacts(struct contactAgenda contacts[]) {
    FILE* fp = fopen(DATA_FILE, "r");
    if (fp == NULL) {
        // File doesn't exist, start with 0 contacts
        return 0;
    }

    int count = 0;
    while (fscanf(fp, "%[^;];%[^;];%[^\n]\n",
                  contacts[count].name,
                  contacts[count].phone,
                  contacts[count].email) == 3 && count < MAX_CONTACTS) {
        count++;
    }
    fclose(fp);
    return count;
}

// Clear input buffer
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
