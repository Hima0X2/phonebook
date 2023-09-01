#include <stdio.h>
#include <string.h>

// Define a structure to represent a phonebook entry
struct PhonebookEntry {
    char name[100];
    char address[100];
    char gender[8];
    char gmail[100];
    double phone;
};

// Function to add a new entry to the phonebook
void addEntry() {
    struct PhonebookEntry entry;

    printf("Enter name: ");
    scanf("%s", entry.name);
    printf("Enter address: ");
    scanf("%s", entry.address);
    printf("Enter gender: ");
    scanf("%s", entry.gender);
    printf("Enter Gmail: ");
    scanf("%s", entry.gmail);
    printf("Enter phone number: ");
    scanf("%lf", &entry.phone);

    // Open the file for appending
    FILE* file = fopen("phonebook.txt", "a");
    if (file == NULL) {
        printf("Failed to open file for writing.\n");
        return;
    }

    // Write the entry to the file
    fprintf(file, "%s %s %s %s %.0lf\n", entry.name, entry.address, entry.gender, entry.gmail, entry.phone);

    // Close the file
    fclose(file);

    printf("Entry added successfully.\n");
}

// Function to search for an entry in the phonebook
void searchEntry() {
    char name[100];
    printf("Enter the name to search: ");
    scanf("%s", name);

    FILE* file = fopen("phonebook.txt", "r");
    if (file == NULL) {
        printf("Phonebook is empty or file not found.\n");
        return;
    }

    struct PhonebookEntry entry;
    int found = 0;

    // Search for the entry by name
    while (fscanf(file, "%s %s %s %s %lf\n", entry.name, entry.address, entry.gender, entry.gmail, &entry.phone) != EOF) {
        if (strcmp(entry.name, name) == 0) {
            printf("Entry found:\n");
            printf("Name: %s\n", entry.name);
            printf("Address: %s\n", entry.address);
            printf("Gender: %s\n", entry.gender);
            printf("Gmail: %s\n", entry.gmail);
            printf("Phone Number: %.0lf\n", entry.phone);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Entry not found.\n");
    }

    fclose(file);
}

// Function to list all entries in the phonebook
void listEntries() {
    FILE* file = fopen("phonebook.txt", "r");
    if (file == NULL) {
        printf("Phonebook is empty or file not found.\n");
        return;
    }

    struct PhonebookEntry entry;

    printf("List of Entries:\n");

    while (fscanf(file, "%s %s %s %s %lf\n", entry.name, entry.address, entry.gender, entry.gmail, &entry.phone) != EOF) {
        printf("Name: %s\n", entry.name);
        printf("Address: %s\n", entry.address);
        printf("Gender: %s\n", entry.gender);
        printf("Gmail: %s\n", entry.gmail);
        printf("Phone Number: %.0lf\n", entry.phone);
        printf("------------------------\n");
    }

    fclose(file);
}

void modifyEntry() {
    char name[100];
    printf("Enter the name of the entry to modify: ");
    scanf("%s", name);

    FILE* inputFile = fopen("phonebook.txt", "r");
    FILE* tempFile = fopen("temp.txt", "w");

    if (inputFile == NULL || tempFile == NULL) {
        printf("Error opening files.\n");
        return;
    }

    struct PhonebookEntry entry;
    int found = 0;

    while (fscanf(inputFile, "%s %s %s %s %lf\n", entry.name, entry.address, entry.gender, entry.gmail, &entry.phone) != EOF) {
        if (strcmp(entry.name, name) == 0) {
            printf("Enter new address: ");
            scanf("%s", entry.address);
            printf("Enter new gender: ");
            scanf("%s", entry.gender);
            printf("Enter new Gmail: ");
            scanf("%s", entry.gmail);
            printf("Enter new phone number: ");
            scanf("%lf", &entry.phone);
            found = 1;
        }
        fprintf(tempFile, "%s %s %s %s %.0lf\n", entry.name, entry.address, entry.gender, entry.gmail, entry.phone);
    }

    fclose(inputFile);
    fclose(tempFile);

    if (found) {
        remove("phonebook.txt");
        rename("temp.txt", "phonebook.txt");
        printf("Entry modified successfully.\n");
    } else {
        remove("temp.txt");
        printf("Entry not found.\n");
    }
}

// Function to delete an existing entry from the phonebook
void deleteEntry() {
    char name[100];
    printf("Enter the name of the entry to delete: ");
    scanf("%s", name);

    FILE* inputFile = fopen("phonebook.txt", "r");
    FILE* tempFile = fopen("temp.txt", "w");

    if (inputFile == NULL || tempFile == NULL) {
        printf("Error opening files.\n");
        return;
    }

    struct PhonebookEntry entry;
    int found = 0;

    while (fscanf(inputFile, "%s %s %s %s %lf\n", entry.name, entry.address, entry.gender, entry.gmail, &entry.phone) != EOF) {
        if (strcmp(entry.name, name) == 0) {
            found = 1;
        } else {
            fprintf(tempFile, "%s %s %s %s %.0lf\n", entry.name, entry.address, entry.gender, entry.gmail, entry.phone);
        }
    }

    fclose(inputFile);
    fclose(tempFile);

    if (found) {
        remove("phonebook.txt");
        rename("temp.txt", "phonebook.txt");
        printf("Entry deleted successfully.\n");
    } else {
        remove("temp.txt");
        printf("Entry not found.\n");
    }
}

int main() {
    int choice;

    while (1) {
        printf("\nPhonebook Directory\n");
        printf("1. Add Entry\n");
        printf("2. Search Entry\n");
        printf("3. List Entries\n");
        printf("4. Modify Entry\n");
        printf("5. Delete Entry\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addEntry();
                break;
            case 2:
                searchEntry();
                break;
            case 3:
                listEntries();
                break;
            case 4:
                modifyEntry();
                break;
            case 5:
                deleteEntry();
                break;
            case 6:
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

