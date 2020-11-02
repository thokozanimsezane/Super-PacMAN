#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "Common.h"

/** \class InputManager
 *  \brief This class is responsible for retrieving the user/keyboard inputs.
 *  This class uses an enumeration, InputType, with values POLLED, LIVE, TEXT and MAP. When the inputType is set to:
 *  POLLED, the function polls for an event - and sets the respective keyPress logic to true, this inputType is used in
 *  the main menu. The InputType LIVE is used for the main game, it determines if a key is currently being pressed and sets
 *  it's logic to true. The InputType TEXT is used for processing user text input, it is used in the Credit screens (game over
 *  and game won), it translates the user input to a string which is then sent to the display layer. The InputType MAP is used
 *  in the map creator/editor screen, it uses mouse clicks and the mousePosition when a click has occurred and sets the
 *  corresponding logic to true. This type also considers the event when the return (enter) key is pressed, and sends the data to
 *  the presentation layer for analysis.
 *  \author 719597 Tarryn Maggs and 1033379 Thokozani Msezane.
 *  \version 3.0
 */

class InputManager
{
public:

    /** \brief A default Constructor, creates an InputManager object.
     */
    InputManager();

    /** \brief A default Destructor, destroys an InputManager object.
     */
    ~InputManager();

    /** \brief sets the input from the game player to correct enumeration type
     *  \param input is of type InputType an enumeration defined in Common.h
     */
    void setInputType(InputType input);

    /** \brief Retrieves the input from the key board
     *  \param _window is of type sf::RenderWindow - A RenderTarget object defined in SFML, used as the target to draw objects to the window buffer to be displayed later.
     *  \param _ event is of type sf::Event - An SFML event object which is used in conjunction with the user-input to determine if a selection has been been made/changed.
     */
    void retrieveInput(sf::RenderWindow& _GameWindow, sf::Event& _event);

    /** \brief returns the text input from the player
     *  \return sf::String
     */
    sf::String returnText();

    /** \brief clears the stored text input
     */
    void clearText();

    /** \brief Used by retrieveInput to identify if left key from keyboard was pressed
     *  \return bool
     */
    bool Left();

   /** \brief Used by retrieveInput to identify if right key from keyboard was pressed
     *  \return bool
     */
    bool Right();

    /** \brief Used by retrieveInput to identify if up key from keyboard was pressed
     *  \return bool
     */
    bool Up();

   /** \brief Used by retrieveInput to identify if down key from keyboard was pressed
     *  \return bool
     */
    bool Down();

    /** \brief Used by retrieveInput to identify if enter key from keyboard was pressed
     *  \return bool
     */
    bool confirm(); //confirm selecction in menu

    /** \brief Used by retrieveInput to identify if backspace key from keyboard was pressed
     *  \return bool
     */
    bool previous();

    /** \brief Used by retrieveInput to identify if spacebar key from keyboard was pressed
     *  \return bool
     */
    bool isSpeedUp();

    /** \brief Used by retrieveInput to identify a left mouse click
     *  \return bool
     */
    bool leftClick();

    /** \brief Used by retrieveInput to identify a right mouse click
     *  \return bool
     */
    bool rightClick();

    /** \brief Returns the position of the mouse when a mouse click has occurred.
     *  \return sf::Vector2f
     */
    sf::Vector2f returnMousePos();

private:

    /** \brief This function is responsible for reseting all boolean private members to false.
     *  The playerInput string and the mouse Position are not reset in this function.
     */
    void ResetInput();

    InputType _input;
    bool _left;
    bool _right;
    bool _up;
    bool _down;
    bool _confirm;
    bool _escape;
    bool _speedUp;

    bool _leftClick;
    bool _rightClick;

    sf::Vector2f mousePosition;

    sf::String playerInput;
};


#endif // INPUTMANAGER_H
