#ifndef PLAYSCREEN_H_INCLUDED
#define PLAYSCREEN_H_INCLUDED

#include "Common.h"
#include "IGameScreen.h"
#include "InputManager.h"
#include "IMazeEntity.h"
#include "LogicPresenter.h"
#include "ResourceManager.h"

/** \class PlayScreen
 *  \brief This Class inherits from IGameScreen and is responsible for  Responsible for presenting/displaying the game Logic, creates the game Logic event.
 *   creates the resource Manager, and saves the previous highscore It renders all active game objects to the screen (excluding paths as they are redundant - dont need to be seen),
 *   displays lives remaining, current score and high score.
 *  \author 719597 Tarryn Maggs and 1033379 Thokozani Msezane
 *  \version 3.0
 */

class PlayScreen :public IGameScreen
{
public:

    /** \brief A default constructor of an object of type PlayScreen, creates a PlayScreen Object.
     *  \param mapFilename of type const string. it stores the path to the map file used to initialise the maze
     */
    PlayScreen(const std::string mapFilename);

    /** \brief A default destructor, destroys an object of type PlayScreen.
     */
    ~PlayScreen();

    /** \brief Loads the required images and fonts required for use in the PlayScreen
     */
    virtual void LoadContent();

    /** \brief Removes the screen-specific content.
     *  Removes data/content that is no longer required.
     */
    virtual void RemoveContent();

    /** \brief A virtual function that is used for updating the playscreen screen contents
     *  \param sf::RenderWindow - A RenderTarget object defined in SFML, used as the target to draw objects to the window buffer to be displayed later.
     *  \param sf::Event - An SFML event object which is used in conjunction with the user-input to determine if a selection has been been made/changed.
     */
    virtual void Update(sf::RenderWindow& _window, sf::Event& _event);

    /** \brief Draws the PlayScreen content.
     *  Adds the PlayScreen content into the SFML Buffer to be drawn.
     *  \param sf::RenderWindow - A RenderTarget object defined in SFML.
     */
    virtual void Draw(sf::RenderWindow& _window);

    /** \brief This function returns the game progress (level complete/ level incomplete/ game won / game over)
     *  \return Game_Status an enumeration defined in Common.h
     */
    virtual Game_Status returnGameProgress() override;

    /** \brief returns the highscore of the player
     *  \return HighScore, a struct defined in Common.h
     */
    virtual HighScore returnHighScore() override;

    /** \brief saves the game's new highscore
     *  \param _newHighScore is of type HighScore a struct defined in Common.h
     */
    virtual void saveHighScore(HighScore _newHighScore) override; // used to pass high score into each screen

private:
    // map textures to entities
    /** \brief This functions maps textures to corresponding entities
     *  \param _window is of type sf::RenderWindow.
     *  \param _event is of type sf::_event.
     */
    void manageInput(sf::RenderWindow& _window, sf::Event& _event);

    /** \brief This functions increments the game level. It reloads the resources with the corresponding level, saves the current lives remaining and the
	 *	previous score. It then resets the LogicPresenter with the remaining lives, thereby creating a new level.
     */
    void changeLevel();

    std::string _mapFileName;
    std::map<TextureID, sf::Texture> mapEntityTex;
    std::shared_ptr<InputManager> _input;
    LogicPresenter _logicP; // initialised with 3
    ResourceManager _resource;
    std::vector<std::shared_ptr<sf::Sprite>> _entitySprites;
    sf::Texture _texture;
    std::vector<std::shared_ptr<IMazeEntity>> _renderObjects;
    std::vector<std::shared_ptr<IDynamicMazeEntity>> _renderDynamicObjects;
    int PreviousScore;
    int CurrentLives;
    int _level;
    int _highscore;
    FileManager file;
    int flashCount = 1;
};

#endif // PLAYSCREEN_H_INCLUDED
