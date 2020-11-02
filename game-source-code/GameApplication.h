#ifndef GAMEAPPLICATION_H_INCLUDED
#define GAMEAPPLICATION_H_INCLUDED

#include "GameStateManager.h"

/** \class GameApplication
 *  \brief This is a class that works with GameStateManager to display the different states (screens) of the game, namely: SplashScreen, main game (ACTIVE), game over, game won.
 *  \author 719597 Tarryn Maggs and 1033379 Thokozani Msezane.
 *  \version 3.0
 */

class GameApplication
{
public:

    /** \brief Default Constructor, creates a GameApplication object.
      */
    GameApplication();

    /** \brief Default Destructor, destroys a GameApplication object.
      */
    ~GameApplication();

    /** \brief This function is responsible for starting the game, creates the gamewindow and runs the respective gamescreens.
      */
    void StartGame();
private:

    /** \brief This function is responsible for the splash screen.
      */
    void Splash();

    /** \brief This function is responsible for the gameover screen.
      */
    void GameOver();

    /** \brief This function is responsible for the gamewon screen.
      */
    void GameWon();
    /** \brief This function is responsible for the play screen.
      */
    void Play();


    void MainMenu();
    void MapEditor();

    GameStateManager _gameManager;
    sf::RenderWindow _window;
    sf::Event _event;
};
#endif // GAMEAPPLICATION_H_INCLUDED
