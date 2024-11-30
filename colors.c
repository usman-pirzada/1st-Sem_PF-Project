// -------------------First Method-------------------------
#include <stdio.h>
#include <windows.h>

// Define macros for colors and text effects
#define RESET "\033[0m"           // Reset all attributes
#define BOLD "\033[1m"            // Bold text
#define UNDERLINE "\033[4m"       // Underlined text

// Foreground colors
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"

// Background colors (optional)
#define BG_RED "\033[41m"
#define BG_GREEN "\033[42m"
#define BG_BLUE "\033[44m"

int main() {
    system("");
    printf("Normal text\n");

    // Bold text
    printf(BOLD "This is bold text\n" RESET);

    // Underlined text
    printf(UNDERLINE "This is underlined text\n" RESET);

    // Colored text
    printf(RED "This is red text\n" RESET);
    printf(GREEN "This is green text\n" RESET);
    printf(BLUE "This is blue text\n" RESET);

    // Combining effects
    printf(BOLD UNDERLINE YELLOW "This is bold, underlined, and yellow text\n" RESET);

    // Text with background color
    printf(BG_BLUE WHITE "This is white text with a blue background\n" RESET);

    return 0;
}

// ------------------------Other Method----------------------
/*
#include <stdio.h>
#include <windows.h>

// Function to set text color
void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

int main() {
    // Normal text
    setColor(7); // Default console color
    printf("Normal text\n");

    // Red text
    setColor(12); // Bright red
    printf("This is red text\n");

    // Green text
    setColor(10); // Bright green
    printf("This is green text\n");

    // Blue text
    setColor(9); // Bright blue
    printf("This is blue text\n");

    // Reset to default
    setColor(7);
    printf("Back to normal text\n");

    return 0;
}
*/