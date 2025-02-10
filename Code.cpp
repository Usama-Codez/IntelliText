#include <iostream>
#include <unistd.h>  // For sleep() on Linux/Mac
#include <windows.h> // For Sleep() on Windows (Uncomment if on Windows)
using namespace std;

void printHeart(int scale) {
    int width = 40, height = 12; // Adjust heart size
    for (int i = height / 2; i <= height; i += 2) {
        // Left spacing
        for (int j = 1; j < width - i; j += 2)
            cout << " ";
        
        // Left half of heart
        for (int j = 1; j <= i; j++)
            cout << "*";
        
        // Center space
        for (int j = 1; j <= width - i; j++)
            cout << " ";
        
        // Right half of heart
        for (int j = 1; j <= i; j++)
            cout << "*";
        
        cout << endl;
    }

    // Lower part of heart
    for (int i = height; i >= 0; i--) {
        // Spacing for centering
        for (int j = i; j < width / 2; j++)
            cout << " ";
        
        // Bottom of heart
        for (int j = 1; j <= (i * 2) - 1; j++) {
            if (i == height / 2 && j == i) {
                cout << "USAMA"; // Print any name in the heart
                j += 4; // Skip extra characters
            } else {
                cout << "*";
            }
        }
        cout << endl;
    }
}

int main() {
    for (int i = 0; i < 10; i++) { // Animation loop
        system("clear"); // For Linux/Mac
        // system("CLS"); // For Windows (Uncomment if on Windows)
        
        printHeart(i % 3); // Make the heart "pulse"
        
        usleep(200000); // Delay for animation (Linux/Mac)
        // Sleep(200); // Windows version (Uncomment if on Windows)
    }
    return 0;
}
