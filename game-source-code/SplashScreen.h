#ifndef SPLASHSCREEN_H_INCLUDED
#define SPLASHSCREEN_H_INCLUDED

#include "Common.h"
#include "IGameScreen.h"
//  SplashScreen Class - displays the title of the Game and instructions for playing.

/** \class SplashScreen
 *  \brief This Class inherits from IGameScreen and it displays title of the game as well as game control instructions.
 *  \author 719597 Tarryn Maggs and 1033379 Thokozani Msezane
 *  \version 3.0
 */

class SplashScreen :public IGameScreen
{
    public:
        //  Default Constructor
        /** \brief A default constructor of an object of type SplashScreen, creates a SplashScreen Object.
         */
        SplashScreen();

        /** \brief A default destructor of an object of type SplashScreen, destroys a SplashScreen Object.
         */
        ~SplashScreen();

        //  function to display the splashscreen

        /** \brief Loads the required images and fonts required for use in the SplashScreen
         */
        virtual void LoadContent();

        /** \brief Removes the screen-specific content.
         *  Removes data/content that is no longer required. (not used in this class)
         */
        virtual void RemoveContent();

         /** \brief A virtual function that is used for updating the splash screen contents
          *  \param sf::RenderWindow - A RenderTarget object defined in SFML, used as the target to draw objects to the window buffer to be displayed later.
          *  \param sf::Event - An SFML event object which is used in conjunction with the user-input to determine if a selection has been been made/changed.
          */
        virtual void Update(sf::RenderWindow& _window, sf::Event& _event);


        /** \brief Draws the SplashScreen content.
         *  Adds the SplashScreen content into the SFML Buffer to be drawn.
         *  \param sf::RenderWindow - A RenderTarget object defined in SFML.
         */
        virtual void Draw(sf::RenderWindow& _window);

       /** \brief This function returns the game progress which is always set to 'level incomplete'.
         *  \return Game_Status an enumeration defined in Common.h
         */
        virtual Game_Status returnGameProgress() override;


    private:
        sf::Texture _splashTexture;
        sf::Text _title;
        sf::Font font;
        sf::Sprite _background;
};

#endif // SPLASHSCREEN_H_INCLUDED
