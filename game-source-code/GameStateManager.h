#ifndef GAMESTATEMANAGER_H_INCLUDED
#define GAMESTATEMANAGER_H_INCLUDED

 #include <stack>

#include "Common.h"
#include "InputManager.h"
#include "IGameScreen.h"
#include "PlayScreen.h"
#include "SplashScreen.h"
#include "GameOverScreen.h"
#include "GameWonScreen.h"
#include "MainMenu.h"
#include "MapEditor.h"
//manages the various game States of the game
// SplashScreen, MainMenu, PlayScreen, EndGame Screen etc

/** \class GameStateManager
 *  \brief This is a class that manages the various states of the game, states include the SplashScreen,
 *  MainMenu, PlayScreen, EndGame, GameOver, GameWon etc
 *  \author 719597 Tarryn Maggs and 1033379 Thokozani Msezane.
 *  \version 3.0
 */

class GameStateManager
{
public:

    /** \brief Default constructor that creates a GameStateManager object.
     */
    GameStateManager();

    /** \brief Default destructor that destroys a GameStateManager object.
     */
    ~GameStateManager();

    /** \brief This function responsible for creating a game state.
     *  \param _State is of type GameState an enumeration defined in Common.h
     */
    void createState(GameState _State);

    /** \brief This function responsible for clearing a game state.
     */
    void clearState();

    /** \brief This function responsible for updating game states.
     *  \param _State is of type GameState, an enumeration defined in Common.h
     *  \param _window is of type sf::RenderWindow - A RenderTarget object defined in SFML, used as the target to draw objects to the window buffer to be displayed
     */
    void updateState(GameState _State, sf::RenderWindow& _window);

    /** \brief This function responsible for returning game states.
     *  \return GameState, an enumeration defined in Common.h
     */
    GameState returnState();


    /** \brief This function responsible for displaying game high scores.
     *  \param _window is of type sf::RenderWindow - A RenderTarget object defined in SFML, used as the target to draw objects to the window buffer to be displayed
     */
    void displayHighScores(sf::RenderWindow& _window);



private:
	std::string _mapFilename;
    std::shared_ptr<InputManager> _userInput;
    std::stack<std::shared_ptr<IGameScreen>> _screenStack;
    GameState _currentState;
    sf::RenderWindow _GameWindow;
    sf::Event _event;
    static int GameInstance;
    GameState _gameState;
    Game_Status _gameStatus;
    HighScore _newHighScore;
    HighScore _fileHighScore;
    FileManager file;
    StopWatch button;
};


#endif // GAMESTATEMANAGER_H_INCLUDED
