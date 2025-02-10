#include <iostream>
#include <cmath>
using namespace std;

void printWavePattern(int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            // Generating a wave effect using sine function
            int pos = static_cast<int>(5 * sin(j * 0.5) + 5); 
            if (i == pos)
                cout << "*";
            else
                cout << " ";
        }
        cout << endl;
    }
}

int main() {
    int rows = 10, cols = 40; // Dimensions of the pattern
    printWavePattern(rows, cols);
    return 0;
}
