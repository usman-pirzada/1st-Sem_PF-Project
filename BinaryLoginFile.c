#include <stdio.h>
#include <string.h>

// Define the structure to hold user data (username and password)
struct User {
    char username[50];
    char password[50];
};

// Function to write a user to a file
void writeUserToFile(const char *filename, struct User user) {
    FILE *file = fopen(filename, "ab");  // Open the file in append binary mode
    if (file == NULL) {
        printf("Unable to open file for writing\n");
        return;
    }
    fwrite(&user, sizeof(struct User), 1, file);  // Write the user structure to the file
    fclose(file);  // Close the file after writing
}

// Function to read all users from a file
int readUsersFromFile(const char *filename, struct User users[]) {
    FILE *file = fopen(filename, "rb");  // Open the file in read binary mode
    if (file == NULL) {
        printf("Unable to open file for reading\n");
        return 0;  // Return 0 if the file can't be opened
    }

    int count = 0;
    // Loop to read users from the file until EOF is encountered
    while (fread(&users[count], sizeof(struct User), 1, file) == 1) {
        count++;  // Increment count for each user read
    }

    fclose(file);  // Close the file after reading
    return count;  // Return the number of users read
}

// Function to validate user login (compare input credentials with stored data)
int validateLogin(struct User users[], int numUsers, const char *username, const char *password) {
    for (int i = 0; i < numUsers; i++) {
        // Compare username and password from the file with the input credentials
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return 1;  // Login is valid if both username and password match
        }
    }
    return 0;  // Return 0 if no match is found
}

void displayMenu() {
    printf("\n========================\n");
    printf("1. Create New User\n");
    printf("2. Login\n");
    printf("3. Exit\n");
    printf("========================\n");
    printf("Enter your choice: ");
}

int main() {
    struct User users[100];  // Array to hold up to 100 users
    const char *filename = "users.dat";  // File to store users

    int numUsers = 0;

    // Infinite loop for menu-driven program
    while (1) {
        displayMenu();  // Show the menu to the user

        int choice;
        scanf("%d", &choice);  // Take user input for menu choice

        switch (choice) {
            case 1: {
                // Create New User
                struct User newUser;
                printf("Enter username: ");
                scanf("%s", newUser.username);
                printf("Enter password: ");
                scanf("%s", newUser.password);

                writeUserToFile(filename, newUser);  // Save the new user to the file
                printf("User created successfully!\n");
                break;
            }
            case 2: {
                // Login
                numUsers = readUsersFromFile(filename, users);  // Read all users from the file

                if (numUsers == 0) {
                    printf("No users found in the system. Please create a new user first.\n");
                    break;
                }

                // Ask for login credentials
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
                break;
            }
            case 3:
                // Exit
                printf("Exiting the program...\n");
                return 0;

            default:
                printf("Invalid choice! Please enter 1, 2, or 3.\n");
        }
    }

    return 0;
}

// ------------will be hlpful for ppre-stored stock----------
// #include <stdio.h>
// #include <string.h>

// // Define the structure to hold user data (username and password)
// struct User {
//     char username[50];
//     char password[50];
// };

// // Function to write a user to a file
// void writeUserToFile(const char *filename, struct User user) {
//     FILE *file = fopen(filename, "ab");  // Open the file in append binary mode
//     if (file == NULL) {
//         printf("Unable to open file for writing\n");
//         return;
//     }
//     fwrite(&user, sizeof(struct User), 1, file);  // Write the user structure to the file
//     fclose(file);  // Close the file after writing
// }

// // Function to read all users from a file
// int readUsersFromFile(const char *filename, struct User users[]) {
//     FILE *file = fopen(filename, "rb");  // Open the file in read binary mode
//     if (file == NULL) {
//         printf("Unable to open file for reading\n");
//         return 0;  // Return 0 if the file can't be opened
//     }

//     int count = 0;
//     // Loop to read users from the file until EOF is encountered
//     while (fread(&users[count], sizeof(struct User), 1, file) == 1) {
//         count++;  // Increment count for each user read
//     }

//     fclose(file);  // Close the file after reading
//     return count;  // Return the number of users read
// }

// // Function to validate user login (compare input credentials with stored data)
// int validateLogin(struct User users[], int numUsers, const char *username, const char *password) {
//     for (int i = 0; i < numUsers; i++) {
//         // Compare username and password from the file with the input credentials
//         if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
//             return 1;  // Login is valid if both username and password match
//         }
//     }
//     return 0;  // Return 0 if no match is found
// }

// int main() {
//     struct User users[100];  // Array to hold up to 100 users
//     const char *filename = "users.dat";  // File to store users

//     // Adding some users (for testing)
//     struct User user1 = {"alice", "password123"};
//     struct User user2 = {"bob", "mypassword"};
//     struct User user3 = {"charlie", "password456"};
    
//     // Write users to file
//     writeUserToFile(filename, user1);
//     writeUserToFile(filename, user2);
//     writeUserToFile(filename, user3);

//     // Read users from file
//     int numUsers = readUsersFromFile(filename, users);
//     printf("Number of users read from file: %d\n", numUsers);

//     // User input for login
//     char username[50], password[50];
//     printf("Enter username: ");
//     scanf("%s", username);
//     printf("Enter password: ");
//     scanf("%s", password);

//     // Validate login
//     if (validateLogin(users, numUsers, username, password)) {
//         printf("Login successful!\n");
//     } else {
//         printf("Invalid username or password.\n");
//     }

//     return 0;
// }

// -------------Method-3--------------

// #include <stdio.h>
// #include <string.h>

// struct User {
//     char username[50];
//     char password[50];
// };

// void writeUserToFile(const char *filename, struct User user) {
//     FILE *file = fopen(filename, "ab"); // Open file in append binary mode
//     if (file == NULL) {
//         printf("Unable to open file\n");
//         return;
//     }
//     fwrite(&user, sizeof(struct User), 1, file); // Write the structure to the file
//     fclose(file); // Close the file
// }

// int readUsersFromFile(const char *filename, struct User users[], int maxUsers) {
//     FILE *file = fopen(filename, "rb"); // Open file in binary read mode
//     if (file == NULL) {
//         // File doesn't exist, create it
//         file = fopen(filename, "wb"); // Create the file in write binary mode
//         if (file == NULL) {
//             printf("Unable to create file\n");
//             return 0; // Return 0 if file creation fails
//         }
//         fclose(file); // Close the newly created empty file
//         return 0; // Return 0, no users are in the file yet
//     }

//     int count = 0;
//     while (fread(&users[count], sizeof(struct User), 1, file) == 1) {
//         count++;
//         if (count >= maxUsers) {
//             break;
//         }
//     }

//     fclose(file); // Close the file
//     return count; // Return the number of users read
// }

// int validateLogin(struct User users[], int numUsers, const char *username, const char *password) {
//     for (int i = 0; i < numUsers; i++) {
//         if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
//             return 1; // Valid login
//         }
//     }
//     return 0; // Invalid login
// }

// void createNewUser(const char *filename) {
//     struct User newUser;

//     // Prompt for username and password to create a new user
//     printf("No users found. Please create a new account.\n");
//     printf("Enter new username: ");
//     scanf("%s", newUser.username);
//     printf("Enter new password: ");
//     scanf("%s", newUser.password);

//     // Write the new user to the file
//     writeUserToFile(filename, newUser);
//     printf("Account created successfully!\n");
// }

// int main() {
//     struct User users[100]; // Array to store users, can hold up to 100 users
//     int numUsers = readUsersFromFile("users.dat", users, 100); // Read users from the file

//     if (numUsers == 0) {
//         printf("No users found or file created.\n");
//         createNewUser("users.dat"); // Allow user to create a new account if no users exist
//         numUsers = readUsersFromFile("users.dat", users, 100); // Read the newly added user
//     }

//     // Login functionality
//     char username[50], password[50];
//     printf("Enter username: ");
//     scanf("%s", username);
//     printf("Enter password: ");
//     scanf("%s", password);

//     // Validate login
//     if (validateLogin(users, numUsers, username, password)) {
//         printf("Login successful!\n");
//     } else {
//         printf("Invalid username or password.\n");
//     }

//     return 0;
// }