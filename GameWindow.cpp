/*
 * Author: Shayan Mohsin
 * Description: Implementation file for GameWindow class, handling UI interactions.
 * Date Thursday Feb6th 
 */

#include "GameWindow.h"
#include <QVBoxLayout>
#include <QMessageBox>

/*
 * Function: GameWindow
 * Description: Constructor initializes the game board UI and connects buttons.
 * Parameters:
 *   - parent: Parent QWidget (default is nullptr).
 */
GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent), board(30, 16, 99) {
    board.generateBoard(0, 0);  // Generate mines when the game starts
    QWidget *centralWidget = new QWidget(this);
    gridLayout = new QGridLayout;
    buttons.resize(16);
    for (int i = 0; i < 16; ++i) {
        buttons[i].resize(30);
    }

    for (int y = 0; y < 16; ++y) {
        for (int x = 0; x < 30; ++x) {
            QPushButton *button = new QPushButton;
            button->setFixedSize(30, 30);
            gridLayout->addWidget(button, y, x);
            buttons[y][x] = button;
            connect(button, &QPushButton::clicked, this, &GameWindow::handleCellClick);
        }
    }
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(gridLayout);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
}

/*
 * Function: restartGame
 * Description: Resets the board and UI for a new game.
 */
void GameWindow::restartGame() {
    board.resetBoard(0, 0); // Reset board with new mine locations
    for (int y = 0; y < 16; ++y) {
        for (int x = 0; x < 30; ++x) {
            buttons[y][x]->setText(""); // Clear button text
            buttons[y][x]->setEnabled(true); // Enable all buttons
        }
    }
}

/*
 * Function: handleCellClick
 * Description: Handles user interaction with the Minesweeper grid, processes clicks, and checks for game over condition.
 */
void GameWindow::handleCellClick() {
    QPushButton *clickedButton = qobject_cast<QPushButton*>(sender());
    if (!clickedButton) return;
    
    int x = -1, y = -1;
    for (int i = 0; i < 16; ++i) {
        for (int j = 0; j < 30; ++j) {
            if (buttons[i][j] == clickedButton) {
                x = j;
                y = i;
                break;
            }
        }
    }
    if (x == -1 || y == -1) return;

    if (board.isMine(x, y)) {
        QMessageBox::critical(this, "Game Over", "You clicked on a mine! Game over! Do you want to restart?");
        restartGame(); // Restart the game when player acknowledges the message
        return;
    }

    board.revealCell(x, y);
    clickedButton->setText(QString::number(board.countAdjacentMines(x, y))); // Display adjacent mine count
}
