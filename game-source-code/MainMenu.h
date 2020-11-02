#ifndef MAINMENU_H_INCLUDED
#define MAINMENU_H_INCLUDED

#include "Common.h"
#include "IGameScreen.h"
#include "InputManager.h"


/** \class MainMenu
 *  \brief MainMenu Class inherits from IGameScreen and is responsible for allowing the user to switch between different GameStates,
 *  such as the PlayScreen, HighScores, Settings, MapCreator and Quit. The MainMenu Class is responsible for interpreting user input
 *  (of the form of keyboard inputs) and updating the screen with the respective user selection.
 *  \author 719597 Tarryn Maggs and 1033379 Thokozani Msezane
 *  \version 3.0
 */

class MainMenu : public IGameScreen
{
public:


    /** \brief A default constructor of an object of type MainMenu.
     *  The input type for this state (Main menu) is set to polled.
     */
    MainMenu();

    /** \brief A default destructor, destroys an object of type MainMenu.
     */
    ~MainMenu();

    /** \brief Loads the content in the Main Menu. Loads the required images and fonts required for use in the Main Menu
     */
    virtual void LoadContent();


    /** \brief Removes the screen-specific content.
     *  When navigating away from the main menu - Removes data/content that is no longer required.
     */
    virtual void RemoveContent();

    /** \brief Update the Screen, uses the user-input to determine what to display
     *  \param _window is of type sf::RenderWindow - A RenderTarget object defined in SFML, used as the target to draw objects to the window buffer to be displayed later.
     *  \param _ event is of type sf::Event - An SFML event object which is used in conjunction with the user-input to determine if a selection has been been made/changed.
     */
    virtual void Update(sf::RenderWindow& _window, sf::Event& _event);

    /** \brief Draws the Current Screen content.
     *  Adds the main menu content into the SFML Buffer to be drawn.
     *  \param sf::RenderWindow - A RenderTarget object defined in SFML.
     */
    virtual void Draw(sf::RenderWindow& _window);

    /** \brief Function to return the option selected in the main menu
     *  \return Menu enumeration
     */
    virtual Menu menuSelection();

private:
    std::shared_ptr<InputManager> _menu;
    int _selection;
    Menu MenuSelect;

    sf::Text _Title;
    sf::Font _titleFont;
    sf::Font _menuFont;

    std::vector<sf::Text> _MenuOptions;
    sf::Text MenuList[5]; // 5 options
    bool selected;
//plan to implement in future version
};

#endif // MAINMENU_H_INCLUDED
