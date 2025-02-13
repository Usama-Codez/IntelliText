#include <iostream>
#include <unistd.h>
#include <windows.h> 
#include <mmsystem.h>
using namespace std;

// Function to change text color
void setColor(int color) {
    #ifdef _WIN32
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    #else
        cout << "\033[" << color << "m";
    #endif
}

void printHeart(int scale, int offset, int color) {
    setColor(color);
    int width = 40, height = 12;
    
    for (int k = 0; k < offset; k++)
        cout << endl;
    
    for (int i = height / 2; i <= height; i += 2) {
        for (int j = 1; j < width - i; j += 2)
            cout << " ";
        
        for (int j = 1; j <= i; j++)
            cout << "*";
        
        for (int j = 1; j <= width - i; j++)
            cout << " ";
        
        for (int j = 1; j <= i; j++)
            cout << "*";
        
        cout << endl;
    }

    for (int i = height; i >= 0; i--) {
        for (int j = i; j < width / 2; j++)
            cout << " ";
        
        for (int j = 1; j <= (i * 2) - 1; j++) {
            if (i == height / 2 && j == i) {
                cout << "USAMA";  
                j += 4;
            } else {
                cout << "*";
            }
        }
        cout << endl;
    }
    
    setColor(7);
}

void playMusic() {
    #ifdef _WIN32
        PlaySound(TEXT("music.wav"), NULL, SND_ASYNC | SND_LOOP);
    #else
        system("afplay music.mp3 &");
    #endif
}

int main() {
    int colorCodes[] = {31, 33, 32, 34, 35}; // Red, Yellow, Green, Blue, Purple (Linux/Mac)
    int winColorCodes[] = {4, 6, 2, 1, 5}; // Equivalent Windows colors
    
    playMusic(); // Start playing music 🎵

    for (int i = 0; i < 50; i++) {
        system("CLS"); // For Windows
        // system("clear"); // For Linux/Mac (Uncomment if on Linux)
        
        int colorIndex = i % 5;  // Cycle through colors
        int offset = (i % 6) - 3; // Move heart up & down (bouncing effect)

        #ifdef _WIN32
            printHeart(1, abs(offset), winColorCodes[colorIndex]); // Windows
        #else
            printHeart(1, abs(offset), colorCodes[colorIndex]); // Linux/Mac
        #endif

        usleep(150000); // Animation speed (Linux/Mac)
        // Sleep(150); // Windows version
    }
    return 0;
}
