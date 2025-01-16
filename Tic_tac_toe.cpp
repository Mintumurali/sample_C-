#include <iostream>
using namespace std;

// Tic-Tac-Toe board and game variables
char board[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};
char currentMarker;
int currentPlayer;

// Function to display the current state of the board
void displayBoard() {
    cout << "\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << board[i][j] << " ";
            if (j < 2) cout << "| ";
        }
        cout << "\n";
        if (i < 2) cout << "--|---|--\n";
    }
    cout << "\n";
}

// Function to place a marker on the board
bool placeMarker(int slot) {
    int row = (slot - 1) / 3;
    int col = (slot - 1) % 3;

    // Check if the slot is available
    if (board[row][col] != 'X' && board[row][col] != 'O') {
        board[row][col] = currentMarker;
        return true;
    } else {
        return false;
    }
}

// Function to check if there's a winner
bool checkWinner() {
    // Check rows and columns
    for (int i = 0; i < 3; i++) {
        if ((board[i][0] == board[i][1] && board[i][1] == board[i][2]) ||
            (board[0][i] == board[1][i] && board[1][i] == board[2][i])) {
            return true;
        }
    }

    // Check diagonals
    if ((board[0][0] == board[1][1] && board[1][1] == board[2][2]) ||
        (board[0][2] == board[1][1] && board[1][1] == board[2][0])) {
        return true;
    }

    return false;
}

// Switch to the next player
void switchPlayer() {
    currentPlayer = (currentPlayer == 1) ? 2 : 1;
    currentMarker = (currentMarker == 'X') ? 'O' : 'X';
}

int main() {
    cout << "Welcome to Tic-Tac-Toe!\n\n";

    // Let Player 1 choose their marker
    cout << "Player 1, choose your marker (X or O): ";
    cin >> currentMarker;
    
    while (currentMarker != 'X' && currentMarker != 'O') {
        cout << "Invalid choice. Please choose X or O: ";
        cin >> currentMarker;
    }

    currentPlayer = 1;

    // Display the initial board
    displayBoard();

    for (int turn = 0; turn < 9; turn++) {
        cout << "Player " << currentPlayer << "'s turn. Enter a slot number (1-9): ";
        int slot;
        cin >> slot;

        if (slot < 1 || slot > 9) {
            cout << "Invalid slot. Please choose a number between 1 and 9.\n";
            turn--;
            continue;
        }

        // Try placing the marker
        if (!placeMarker(slot)) {
            cout << "Slot already taken. Choose another slot.\n";
            turn--;
            continue;
        }

        // Show the updated board
        displayBoard();

        // Check for a winner
        if (checkWinner()) {
            cout << "Congratulations! Player " << currentPlayer << " wins!\n";
            return 0;
        }

        // Switch to the next player
        switchPlayer();
    }

    cout << "It's a draw! Well played both!\n";
    return 0;
}
