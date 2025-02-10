#include <iostream>
using namespace std;

// Function to calculate GCD using Euclidean algorithm
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    int num1, num2;
    
    // Taking user input
    cout << "Enter two numbers: ";
    cin >> num1 >> num2;
    
    // Calculating and displaying the GCD
    cout << "GCD of " << num1 << " and " << num2 << " is: " << gcd(num1, num2) << endl;

    return 0;
}
