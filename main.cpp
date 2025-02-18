/*
 * Author: Shayan Mohsin
 * Description: Main entry point for the Minesweeper game using Qt.
 * Date: Feb 6th 
 */

#include <QApplication>
#include "GameWindow.h"

/*
 * Function: main
 * Description: Initializes the Qt application and launches the Minesweeper game.
 * Parameters:
 *   - argc: Number of command line arguments.
 *   - argv: Array of command line argument strings.
 * Returns:
 *   - int: Exit status of the application.
 */
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    GameWindow window; // Create the game window
    window.show(); // Display the game window
    return app.exec(); // Start the Qt event loop
}
