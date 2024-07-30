#include <iostream>
#include <vector>

class NQueens {
private:
    int n;
    std::vector<std::vector<int>> board;

    bool isSafe(int row, int col) {
        // Check this row on left side
        for (int i = 0; i < col; i++)
            if (board[row][i])
                return false;

        // Check upper diagonal on left side
        for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
            if (board[i][j])
                return false;

        // Check lower diagonal on left side
        for (int i = row, j = col; j >= 0 && i < n; i++, j--)
            if (board[i][j])
                return false;

        return true;
    }

    bool solveNQUtil(int col) {
        if (col >= n)
            return true;

        for (int i = 0; i < n; i++) {
            if (isSafe(i, col)) {
                board[i][col] = 1;

                if (solveNQUtil(col + 1))
                    return true;

                board[i][col] = 0; // Backtrack
            }
        }

        return false;
    }

public:
    NQueens(int size) : n(size), board(size, std::vector<int>(size, 0)) {}

    bool solveNQ() {
        if (solveNQUtil(0) == false) {
            std::cout << "Solution does not exist";
            return false;
        }

        printSolution();
        return true;
    }

    void printSolution() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++)
                std::cout << " " << board[i][j] << " ";
            std::cout << std::endl;
        }
    }
};

int main() {
    int n = 8; // Change this to solve for different board sizes
    NQueens nQueens(n);
    nQueens.solveNQ();
    return 0;
}