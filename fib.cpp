#include <iostream>
using namespace std;

int main() {
    int n;

    // Ask the user for the number of terms
    cout << "Enter the number of terms in the Fibonacci series: ";
    cin >> n;

    // First two terms of the Fibonacci series
    long long a = 0, b = 1;

    // Display the Fibonacci series
    cout << "Fibonacci Series up to " << n << " terms: " << endl;

    for (int i = 0; i < n; ++i) {
        cout << a << " ";
        long long nextTerm = a + b;
        a = b;
        b = nextTerm;
    }

    cout << endl;

    return 0;
}
