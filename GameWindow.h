/*
 * Author: Shayan Mohsin
 * Description: Header file defining the GameWindow class which handles UI interactions.
 * Date: Thursday Feb 6th 
 */

#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include <QMessageBox>
#include "Board.h"

// The main game window that handles UI interactions
class GameWindow : public QMainWindow {
    Q_OBJECT  // Required for Qt signals/slots to work
public:
    GameWindow(QWidget *parent = nullptr);

private slots:
    void handleCellClick(); // Handles user clicking on a cell
    void restartGame(); // Resets the game when the player chooses to restart

private:
    Board board; // Game board instance
    QGridLayout *gridLayout; // Layout for arranging buttons
    QVector<QVector<QPushButton*>> buttons; // Button matrix representing cells
    void setupBoard(); // Initializes the game board UI
};

#endif

