#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int SIZE = 4;


void printBoard(int board[][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            cout << board[i][j] << "\t";
        }
        cout << endl;
    }
}

void initializeBoard(int board[][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = 0;
        }
    }
}

void generateNewNumber(int board[][SIZE]) {
    int count = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) {
                count++;
            }
        }
    }

    if (count == 0) {
        return;
    }

    int index = rand() % count;
    count = 0;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) {
                if (count == index) {
                    board[i][j] = (rand() % 2 + 1) * 2;
                    return;
                }
                count++;
            }
        }
    }
}

bool isGameOver(int board[][SIZE]) {
    // Проверяем наличие пустых ячеек
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) {
                return false;
            }
        }
    }

    // Проверяем возможность объединения соседних ячеек по горизонтали
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE - 1; j++) {
            if (board[i][j] == board[i][j + 1]) {
                return false;
            }
        }
    }

    // Проверяем возможность объединения соседних ячеек по вертикали
    for (int j = 0; j < SIZE; j++) {
        for (int i = 0; i < SIZE - 1; i++) {
            if (board[i][j] == board[i + 1][j]) {
                return false;
            }
        }
    }

    return true;
}

void mergeLeft(int board[][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE - 1; j++) {
            if (board[i][j] == board[i][j + 1]) {
                board[i][j] *= 2;
                board[i][j + 1] = 0;
            }
        }
    }
}

void moveLeft(int board[][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        int index = 0;
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] != 0) {
                board[i][index] = board[i][j];
                if (j != index) {
                    board[i][j] = 0;
                }
                index++;
            }
        }
    }
}

void mergeRight(int board[][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = SIZE - 1; j > 0; j--) {
            if (board[i][j] == board[i][j - 1]) {
                board[i][j] *= 2;
                board[i][j - 1] = 0;
            }
        }
    }
}

void moveRight(int board[][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        int index = SIZE - 1;
        for (int j = SIZE - 1; j >= 0; j--) {
            if (board[i][j] != 0) {
                board[i][index] = board[i][j];
                if (j != index) {
                    board[i][j] = 0;
                }
                index--;
            }
        }
    }
}

void mergeUp(int board[][SIZE]) {
    for (int j = 0; j < SIZE; j++) {
        for (int i = 0; i < SIZE - 1; i++) {
            if (board[i][j] == board[i + 1][j]) {
                board[i][j] *= 2;
                board[i + 1][j] = 0;
            }
        }
    }
}

void moveUp(int board[][SIZE]) {
    for (int j = 0; j < SIZE; j++) {
        int index = 0;
        for (int i = 0; i < SIZE; i++) {
            if (board[i][j] != 0) {
                board[index][j] = board[i][j];
                if (i != index) {
                    board[i][j] = 0;
                }
                index++;
            }
        }
    }
}

void mergeDown(int board[][SIZE]) {
    for (int j = 0; j < SIZE; j++) {
        for (int i = SIZE - 1; i > 0; i--) {
            if (board[i][j] == board[i - 1][j]) {
                board[i][j] *= 2;
                board[i - 1][j] = 0;
            }
        }
    }
}

void moveDown(int board[][SIZE]) {
    for (int j = 0; j < SIZE; j++) {
        int index = SIZE - 1;
        for (int i = SIZE - 1; i >= 0; i--) {
            if (board[i][j] != 0) {
                board[index][j] = board[i][j];
                if (i != index) {
                    board[i][j] = 0;
                }
                index--;
            }
        }
    }
}

void playGame() {
    int board[SIZE][SIZE];
    initializeBoard(board);
    generateNewNumber(board);
    generateNewNumber(board);

    while (true) {
        system("clear"); // Очищаем консоль

        cout << "2048 Game" << endl;
        cout << "-----------------------------" << endl;
        printBoard(board);

        if (isGameOver(board)) {
            cout << "Game Over!" << endl;
            break;
        }

        cout << "Enter a move (W/A/S/D): ";
        char move;
        cin >> move;

        switch (move) {
            case 'w':
            case 'W':
                moveUp(board);
                mergeUp(board);
                moveUp(board);
                break;
            case 'a':
            case 'A':
                moveLeft(board);
                mergeLeft(board);
                moveLeft(board);
                break;
            case 's':
            case 'S':
                moveDown(board);
                mergeDown(board);
                moveDown(board);
                break;
            case 'd':
            case 'D':
                moveRight(board);
                mergeRight(board);
                moveRight(board);
                break;
            default:
                continue;
        }

        generateNewNumber(board);
    }
}

int main() {
    srand(time(0));
    playGame();
    return 0;
}
