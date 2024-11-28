#include <stdio.h>
#include <string.h>

struct User {
    char username[50];
    char password[50];
};

void writeUserToFile(const char *filename, struct User user) {
    FILE *file = fopen(filename, "ab"); // Open file in append binary mode
    if (file == NULL) {
        printf("Unable to open file\n");
        return;
    }
    fwrite(&user, sizeof(struct User), 1, file); // Write the structure to the file
    fclose(file); // Close the file
}

int readUsersFromFile(const char *filename, struct User users[], int maxUsers) {
    FILE *file = fopen(filename, "rb"); // Open file in binary read mode
    if (file == NULL) {
        // File doesn't exist, create it
        file = fopen(filename, "wb"); // Create the file in write binary mode
        if (file == NULL) {
            printf("Unable to create file\n");
            return 0; // Return 0 if file creation fails
        }
        fclose(file); // Close the newly created empty file
        return 0; // Return 0, no users are in the file yet
    }

    int count = 0;
    while (fread(&users[count], sizeof(struct User), 1, file) == 1) {
        count++;
        if (count >= maxUsers) {
            break;
        }
    }

    fclose(file); // Close the file
    return count; // Return the number of users read
}

int validateLogin(struct User users[], int numUsers, const char *username, const char *password) {
    for (int i = 0; i < numUsers; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1; // Valid login
        }
    }
    return 0; // Invalid login
}

void createNewUser(const char *filename) {
    struct User newUser;

    // Prompt for username and password to create a new user
    printf("No users found. Please create a new account.\n");
    printf("Enter new username: ");
    scanf("%s", newUser.username);
    printf("Enter new password: ");
    scanf("%s", newUser.password);

    // Write the new user to the file
    writeUserToFile(filename, newUser);
    printf("Account created successfully!\n");
}

int main() {
    struct User users[100]; // Array to store users, can hold up to 100 users
    int numUsers = readUsersFromFile("users.dat", users, 100); // Read users from the file

    if (numUsers == 0) {
        printf("No users found or file created.\n");
        createNewUser("users.dat"); // Allow user to create a new account if no users exist
        numUsers = readUsersFromFile("users.dat", users, 100); // Read the newly added user
    }

    // Login functionality
    char username[50], password[50];
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    // Validate login
    if (validateLogin(users, numUsers, username, password)) {
        printf("Login successful!\n");
    } else {
        printf("Invalid username or password.\n");
    }

    return 0;
}