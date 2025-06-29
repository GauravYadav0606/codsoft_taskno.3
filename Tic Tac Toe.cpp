#include <iostream>
using namespace std;

char board[3][3];
char currentPlayer = 'X';

void resetBoard() {
    char pos = '1';
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = pos++;
}

void showBoard() {
    cout << "\n";
    for (int i = 0; i < 3; i++) {
        cout << " ";
        for (int j = 0; j < 3; j++) {
            cout << board[i][j];
            if (j < 2) cout << " | ";
        }
        if (i < 2) cout << "\n---|---|---\n";
    }
    cout << "\n\n";
}

bool isValid(int pos) {
    return pos >= 1 && pos <= 9;
}

bool makeMove(int pos) {
    int row = (pos - 1) / 3;
    int col = (pos - 1) % 3;

    if (board[row][col] != 'X' && board[row][col] != 'O') {
        board[row][col] = currentPlayer;
        return true;
    }
    return false;
}

bool checkWin() {
    for (int i = 0; i < 3; i++) {
        if ((board[i][0] == currentPlayer &&
             board[i][1] == currentPlayer &&
             board[i][2] == currentPlayer) ||
            (board[0][i] == currentPlayer &&
             board[1][i] == currentPlayer &&
             board[2][i] == currentPlayer))
            return true;
    }

    if ((board[0][0] == currentPlayer &&
         board[1][1] == currentPlayer &&
         board[2][2] == currentPlayer) ||
        (board[0][2] == currentPlayer &&
         board[1][1] == currentPlayer &&
         board[2][0] == currentPlayer))
        return true;

    return false;
}

bool checkDraw() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] != 'X' && board[i][j] != 'O')
                return false;
    return true;
}

void changePlayer() {
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}

int main() {
    char again;

    do {
        resetBoard();
        currentPlayer = 'X';
        bool over = false;

        while (!over) {
            showBoard();
            int move;
            cout << "Player " << currentPlayer << ", pick a spot (1-9): ";
            cin >> move;

            if (!cin || !isValid(move)) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Not a number from 1 to 9. Try again.\n";
                continue;
            }

            if (!makeMove(move)) {
                cout << "Spot already used. Try again.\n";
                continue;
            }

            if (checkWin()) {
                showBoard();
                cout << "Player " << currentPlayer << " wins!\n";
                over = true;
            } else if (checkDraw()) {
                showBoard();
                cout << "It's a draw!\n";
                over = true;
            } else {
                changePlayer();
            }
        }

        cout << "Play again? (y/n): ";
        cin >> again;

    } while (again == 'y' || again == 'Y');

    cout << "Thanks for playing!\n";
    return 0;
}
