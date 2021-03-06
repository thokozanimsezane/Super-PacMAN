#ifndef GAMEWONSCREEN_H
#define GAMEWONSCREEN_H

#include "Common.h"
#include "IGameScreen.h"
#include "InputManager.h"
#include "FileManager.h"


/**	\class GameOverScreen
 *  \brief A presentation layer class that inherits from IGameScreenClass. It
 *  contains virtual functions that have been overridden.
 *  uses the SFML library to display that the game is won and a summary of the game scores.
 *  \author 719597 Tarryn Maggs and 1033379 Thokozani Msezane.
 *	\version 3.0
 */

class GameWonScreen :public IGameScreen
{
   public:

        /** \brief Default constructor that creates a GameWonScreen object.
         */
        GameWonScreen();

        /** \brief Default destructor that destroys a GameWonScreen object.
         */
        ~GameWonScreen();

        /** \brief A virtual function that loads the required images and fonts required for use in the Game Won Screen.
         *  Reads in and updates highscores if a highscore has been set for displaying in the game over screen.
         */
        virtual void LoadContent();

        /** \brief A virtual function that removes the screen-specific content (not used in this class).
         */
        virtual void RemoveContent();

        /** \brief A virtual function that is used for updating the game won screen contents
         *  \param _window is of type sf::RenderWindow - A RenderTarget object defined in SFML, used as the target to draw objects to the window buffer to be displayed later.
         *  \param _event is of type sf::Event - An SFML event object which is used in conjunction with the user-input to determine if a selection has been been made/changed.
         */
        virtual void Update(sf::RenderWindow& _window, sf::Event& _event);

        /** \brief A virtual function that draws the contents of the buffer (the game won screen) onto the screen
         *  \param _window is of type sf::RenderWindow - A RenderTarget object defined in SFML.
         */
        virtual void Draw(sf::RenderWindow& _window);

        /** \brief This function returns the game progress which is game won.
         *  \return Game_Status an enumeration defined in Common.h
         */
        virtual Game_Status returnGameProgress() override;

        /** \brief This function returns the game high score.
         *  \return HighScore, a struct defined in Common.h
         */
        virtual HighScore returnHighScore() override;

        /** \brief This is a virtual function that saves the game high score.
         *  \param _newHighScore is of type HighScore a sturct defined in Common.h
         */
        virtual void saveHighScore(HighScore _newHighScore) override; // used to pass high score into each screen


    private:
        sf::Texture _gameWonTexture;
        sf::Text _title;
        sf::Font font;
        sf::Sprite _background;

        sf::Text _controls;
        sf::Text _yourHS;
        sf::Text _highHS;
        HighScore _highScore;
        std::string _newHighScoreString = " ";
        sf::Text _TextInput;
        std::shared_ptr<InputManager> _input;

        sf::String stringCheck;
        std::string enterName;
        bool newHigh = false;

};

#endif // GAMEWONSCREEN_H
