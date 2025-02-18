/*
 * Author: Shayan Mohsin 
 * Description: Implementation file for the Board class, which handles Minesweeper game logic.
 * Date: Thursday Feb 6th
 */

#include "Board.h"
#include <cstdlib>
#include <ctime>

/*
 * Function: Board
 * Description: Constructor initializing the board size and mine count.
 * Parameters:
 *   - width: Number of columns in the board.
 *   - height: Number of rows in the board.
 *   - mineCount: Total number of mines in the board.
 */
Board::Board(int width, int height, int mineCount)
    : width(width), height(height), mineCount(mineCount) {
    grid.resize(height);
    for (int i = 0; i < height; ++i) {
        grid[i].resize(width);
    }
}

/*
 * Function: generateBoard
 * Description: Randomly places mines on the board while avoiding the first move position.
 * Parameters:
 *   - startX: X-coordinate of the first move.
 *   - startY: Y-coordinate of the first move.
 */
void Board::generateBoard(int startX, int startY) {
    srand(time(nullptr));
    int placedMines = 0;
    while (placedMines < mineCount) {
        int x = rand() % width;
        int y = rand() % height;
        if (!grid[y][x].mine && !(x == startX && y == startY)) {
            grid[y][x].mine = true;
            placedMines++;
        }
    }
}

/*
 * Function: countAdjacentMines
 * Description: Counts the number of mines surrounding a given cell.
 * Parameters:
 *   - x: X-coordinate of the cell.
 *   - y: Y-coordinate of the cell.
 * Returns:
 *   - int: Number of adjacent mines.
 */
int Board::countAdjacentMines(int x, int y) const {
    int count = 0;
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            int nx = x + dx, ny = y + dy;
            if (nx >= 0 && nx < width && ny >= 0 && ny < height && grid[ny][nx].mine) {
                count++;
            }
        }
    }
    return count;
}

/*
 * Function: revealCell
 * Description: Reveals a cell and, if no adjacent mines, cascades to reveal connected empty spaces.
 * Parameters:
 *   - x: X-coordinate of the cell.
 *   - y: Y-coordinate of the cell.
 */
void Board::revealCell(int x, int y) {
    if (grid[y][x].revealed || grid[y][x].flagged) return;
    grid[y][x].revealed = true;
    grid[y][x].adjacentMines = countAdjacentMines(x, y);
    if (grid[y][x].adjacentMines == 0) {
        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                int nx = x + dx, ny = y + dy;
                if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                    revealCell(nx, ny);
                }
            }
        }
    }
}

/*
 * Function: toggleFlag
 * Description: Toggles the state of a flag on a cell. 
 * Flags cycle through three states: unmarked → flagged → uncertain (?) → unmarked.
 * Parameters:
 *   - x: X-coordinate of the cell.
 *   - y: Y-coordinate of the cell.
 */
void Board::toggleFlag(int x, int y) {
    if (!grid[y][x].revealed) {
        if (!grid[y][x].flagged) {
            grid[y][x].flagged = true;  // First, flag it as a mine
        } else if (!grid[y][x].uncertain) {
            grid[y][x].uncertain = true;  // Then, mark as uncertain (?)
            grid[y][x].flagged = false;
        } else {
            grid[y][x].flagged = false; // Reset to unmarked
            grid[y][x].uncertain = false;
        }
    }
}

/*
 * Function: checkWin
 * Description: Checks if the player has revealed all non-mine cells.
 * Returns:
 *   - bool: True if the player has won, false otherwise.
 */
bool Board::checkWin() const {
    for (const auto& row : grid) {
        for (const auto& cell : row) {
            if (!cell.mine && !cell.revealed) return false;
        }
    }
    return true;
}

/*
 * Function: isMine
 * Description: Checks if the given cell contains a mine.
 * Parameters:
 *   - x: X-coordinate of the cell.
 *   - y: Y-coordinate of the cell.
 * Returns:
 *   - bool: True if the cell contains a mine, false otherwise.
 */
bool Board::isMine(int x, int y) const {
    return grid[y][x].mine;
}


/*
 * Function: resetBoard
 * Description: Resets the board for a new game, clearing all cells and placing new mines.
 * Parameters:
 *   - startX: X-coordinate of the first move for the new game.
 *   - startY: Y-coordinate of the first move for the new game.
 */
void Board::resetBoard(int startX, int startY) {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            grid[y][x] = {false, false, false, false, 0}; // Reset each cell
        }
    }
    generateBoard(startX, startY); // Regenerate mines
}
