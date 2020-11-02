#ifndef IGAMESCREEN_H_INCLUDED
#define IGAMESCREEN_H_INCLUDED

#include "Common.h"

/** \class IDynamicMazeEntity
 *  \brief This is a Interface class to hold different screen states (main menu, play screen, splash screen, map creator). It
 *  contains pure virtual functions that will be overridden by derived classes.
 *  \author 719597 Tarryn Maggs and 1033379 Thokozani Msezane.
 *  \version 3.0
 */

//abstract class to hold different screen states (main menu, play screen, splash screen, map creator)
class IGameScreen
{
public:

    /** \brief A pure virtual function that loads the required images and fonts required for use in the game-specific screen.
     */
    virtual void LoadContent()=0;

    /** \brief A pure virtual function that removes the screen-specific content.
     */
    virtual void RemoveContent()=0;

    //updates according to live keyboard (and mouse for map creator) input events

    /** \brief A pure virtual function that updates the screen-specific content according to live keyboard (and mouse for map creator) input events.
     *  \param _gameWindow is of type sf::RenderWindow - A RenderTarget object defined in SFML, used as the target to draw objects to the window buffer to be displayed later.
     *  \param _event is of type sf::Event - An SFML event object which is used in conjunction with the user-input to determine if a selection has been been made/changed.
     */
    virtual void Update(sf::RenderWindow& _gameWindow, sf::Event& _event)=0;

    /** \brief A pure virtual function that displays the respective screens
     *  \param _window is of type sf::RenderWindow - A RenderTarget object defined in SFML, used as the target to draw objects to the window buffer to be displayed later.
     */
    virtual void Draw(sf::RenderWindow& _window)=0;

    /** \brief A pure virtual function that is used in the main menu screen for option selection.
     */
    virtual Menu menuSelection();

    /** \brief This function returns the game progress game complete/game incomplete/game won/game over.
     *  \return Game_Status an enumeration defined in Common.h
     */
    virtual Game_Status returnGameProgress(){return _status;};

    /** \brief This function returns the game high score.
     *  \return HighScore, a struct defined in Common.h
     */
    virtual HighScore returnHighScore(){return _high;};

    /** \brief This is a virtual function that saves the game high score.
     *  \param _newHighScore is of type HighScore a sturct defined in Common.h
     */
    virtual void saveHighScore(HighScore _newHighScore){_high = _newHighScore;};

	/** \brief This is a virtual function that returns the mapFileName. used for the map editor.
     *  \return string.
     */
    virtual std::string returnMapName(){return _mapFileName;};

private:
    std::string _mapFileName;
    HighScore _high;
    Game_Status _status;

};


#endif // IGAMESCREEN_H_INCLUDED
