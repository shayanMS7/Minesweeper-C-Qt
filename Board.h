/*
 * Author: Shayan Mohsin
 * Description: Header file defining the Board class which handles the game logic.
 * Date: Feb 6th 
 */

#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <QVector>

// Represents the Minesweeper board and handles game logic
class Board {
public:
    Board(int width, int height, int mineCount);
    void generateBoard(int startX, int startY); // Generates board with mines
    bool isMine(int x, int y) const; // Checks if a cell contains a mine
    int countAdjacentMines(int x, int y) const; // Counts adjacent mines
    void revealCell(int x, int y); // Reveals a cell and cascades if no adjacent mines
    void toggleFlag(int x, int y); // Toggles flag state on a cell (flag → ? → unmarked cycle)
    bool checkWin() const; // Checks if the game is won
    void resetBoard(int startX, int startY); // Resets the board for a new game

private:
    struct Cell {
        bool mine;       // True if this cell contains a mine
        bool revealed;   // True if this cell has been revealed
        bool flagged;    // True if this cell is flagged
        bool uncertain;  // True if the cell is marked with "?"
        int adjacentMines; // Number of adjacent mines
    };
    QVector<QVector<Cell>> grid; // 2D vector representing the game board
    int width;
    int height;
    int mineCount;
};

#endif
