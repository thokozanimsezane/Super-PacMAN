#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>
#include <iterator>
#include <map>
#include <algorithm>

/** \class Common
 *  \brief A class contain containing enumerations and variables common and used by more than one class.
 *  \author 719597 Tarryn Maggs and 1033379 Thokozani Msezane.
 *  \version 3.0
 */

///! Variables to define the dimensions of the game window
const int gameWidth = 660; // width for 12 x 12 pixels  (maze width = 55tiles)
const int gameHeight = 720; // height for 12 x 12 pixels (maze width = 60tiles)
const int totalWidth = 900;
//const int screenHeight = 100;
//const int totalHeight = gameHeight + screenHeight;

///! Variable to store the total effectTime
const double effectTime = 7;


/** \enum UserInput
 *  \brief A strongly typed enum that contains the user input for controlling pacman.
 */
enum UserInput
{
    left=0, /**<Represents the user desired direction left.*/
    right,  /**<Represents the user desired direction right.*/
    up,     /**<Represents the user desired direction up.*/
    down,   /**<Represents the user desired direction down.*/
    space   /**<Represents the user input from the keyboard spacebar.*/
};


/** \enum mapStatus
 *  \brief A strongly typed enum that contains the different map creator status'.
 */
enum mapStatus
{
    Instructions,       /**<Represents the Instructions screen for the map creator.*/ //not yet implemented
    EditorMenu,         /**<Represents the editor menu screen of the map creator.*/ //not yet implemented
    Choices,            /**<Represents the choices screen of the map creator.*/
    Designer,           /**<Represents the Designer screen of the map creator.*/
    Errors,             /**<Represents the Error screen of the map creator.*/ //not yet implemented, will display reasons why map cant be saved
    SaveInput           /**<Represents the User input screen for a filename in the map creator.*/

};

/** \enum Entity_ID
 *  \brief A strongly typed enum that contains the IDs for different entities.
 */
enum Entity_ID //changed from MazeCellType
{
    PATH=0,         /**<Represents the ID for the game entity path.*/
    WALL,           /**<Represents the ID for the game entity wall.*/
    DOOR,           /**<Represents the ID for the game entity door.*/
    FRUIT,          /**<Represents the ID for the game entity fruit.*/
    PACMAN,         /**<Represents the ID for the game entity pacman.*/
    GHOST,          /**<Represents the ID for the game entity ghost.*/
    POWER_PELLET,   /**<Represents the ID for the game entity power pellet.*/
    SUPER_PELLET,   /**<Represents the ID for the game entity super pellet.*/
    KEY,            /**<Represents the ID for the game entity key.*/
    GHOST_DOOR      /**<Represents the ID for the game entity ghost door.*/
};


/** \enum Ghost_ID
 *  \brief A strongly typed enum that contains the IDs for different ghosts.
 */
enum Ghost_ID
{
    RED=0,      /**<Represents the ID for the red ghost.*/
    BLUE,       /**<Represents the ID for the blue ghost.*/
    PINK,       /**<Represents the ID for the pink ghost.*/
    ORANGE,     /**<Represents the ID for the orange ghost.*/
    DEADGHOST   /**<Represents the ID for the deadghost ghost.*/
};

/** \enum TextureID
 *  \brief A strongly typed enum that contains Texture IDs for different objects and diffferent effect status'.
 */
enum TextureID
{
    WallTex=0,          /**< Represents the texture used for a wall object.*/
    DoorTex,            /**< Represents the texture used for a door object.*/
    KeyTex,             /**< Represents the texture used for a key object.*/
    FruitTex,           /**< Represents the texture used for a fruit object.*/
    SuperTex,           /**< Represents the texture used for a superpellet object.*/
    PowerTex,           /**< Represents the texture used for a powerpellet object.*/
    GhostPinkTex,       /**< Represents the texture used for the pink ghost object.*/
    GhostBlueTex,       /**< Represents the texture used for the blue ghost object.*/
    GhostOrangeTex,     /**< Represents the texture used for the orange ghost object.*/
    FlatGhostRedTex,    /**< Represents the texture used for a flattened red ghost.*/
    FlatGhostPinkTex,   /**< Represents the texture used for a flattened pink ghost.*/
    FlatGhostBlueTex,   /**< Represents the texture used for a flattened blue ghost.*/
    FlatGhostOrangeTex, /**< Represents the texture used for a flattened orange ghost.*/
    GhostRedTex,        /**< Represents the texture used for the red ghost object.*/
    PacmanTex,          /**< Represents the texture used for the pacman object.*/
    SuperPacmanTex,     /**< Represents the texture used for the super pacman object.*/
    DeadGhostTex        /**< Represents the texture used for a deadghost.*/
};


/** \enum STATUS
 *  \brief A strongly typed enum that contains the status for all entities.
 */
enum STATUS
{
    ACTIVE=0,  /**< Represents an entity's active state.*/
    INACTIVE,  /**< Represents an entity's inactive state.*/
    TRANSITION /**< Represents an entity's transition state.*/
};

// enumuration for status of pacman/ghosts to account for the effect of pellets
/** \enum EffectStatus
 *  \brief A strongly typed enum that contains the status of pacman and ghost as a result of the pellets.
 */
enum EffectStatus
{
    NORMAL=0, /**< Represents pacman/ghost normal state.*/
    SUPER,     /**< Represents pacman/ghost super state as a result of a super pellet being eaten.*/
    POWER     /**< Represents pacman/ghost super state as a result of a power pellet being eaten.*/
};

/** \enum GameState
 *  \brief A strongly typed enum that contains the state of the game the application is currently running.
 */
enum class GameState
{
    SPLASH=0,       /**< Represents the splash-screen game state.*/
    MAIN_MENU,      /**< Represents the main menu game state.*/
	HIGHSCORES,		/**< Represents the HighScores game state.*/
    MAP_CREATOR, 	/**< Represents the Map Creator game state.*/
    ACTIVE,         /**< Represents the active game state.*/
    GAME_OVER,      /**< Represents the game-over game state.*/
    GAME_WON        /**< Represents the game-won game state.*/
};


// loading from file infor
// will need to layout cells correctly
// each cell type will have a set of coordinates for collisions
/** \enum Orientation
 *  \brief A strongly typed enum that contains the orientation for pacman's sprite
 */
enum Orientation //object orientation -used to rotate pacman's sprite
{
    FACING_LEFT,   /**< Represents pacman's orientation when facing left.*/
    FACING_RIGHT,  /**< Represents pacman's orientation when facing right.*/
    FACING_UP,     /**< Represents pacman's orientation when facing up.*/
    FACING_DOWN    /**< Represents pacman's orientation when facing down.*/
};

/** \enum Direction
 *  \brief A strongly typed enum containing the movement direction for all moving game objects
 */
enum Direction // Specifies The Direction Of Movement of all moving game objects
{
    LEFT=0,     /**< Represents the left movement direction.*/
    RIGHT,      /**< Represents the right movement direction.*/
    UP,         /**< Represents the up movement direction.*/
    DOWN,       /**< Represents the down movement direction.*/
    NONE        /**< Represents the none movement direction.*/
};

/** \enum InputType
 *  \brief A strongly typed enum containing the type of input used in the game
 */
enum InputType
{
    POLLED=0,   /**< Represents the polled input type, this is the default type used in menus.*/
    //default - used in menus
    LIVE,       /**< Represents the live input type used in game play.*/
    // game play
    TEXT,        /**< Represents the text input type.*/
	MAP         /**< Represents the Map input type - using the mouse.*/
};



/** \enum Menu
 *  \brief A strongly typed enum containing the selection option in the menuscreen
 */
enum Menu // highlight selection
{
    Play=0,      /**< Represents the play selection in menu.*/
    HighScores,  /**< Represents the highscores selection in menu.*/
    MapCreator,  /**< Represents the map creator selection in menu.*/
    Settings, // implemented later - used to change which buttons you can use?
    Quit         /**< Represents the quit selection in menu.*/
};


/** \struct HighScore
 *  \brief A struct that stores highscore and string name of person who set highscore
 */
struct HighScore
{
    int score;
    std::string name;
};

/** \enum Game_Status
 *  \brief A strongly typed enum containing the game play status
 */
enum Game_Status
{
    LEVEL_INCOMPLETE=0,     /**< Represents game status during gameplay.*/
    LEVEL_COMPLETE,         /**< Represents game status when a level has been completed.*/
    //PAUSE,    //want to implement
    GAME_OVER,              /**< Represents game status when pacman has no lives left.*/
    GAME_WON                /**< Represents game status when all levels have been completed.*/
};


#endif // COMMON_H_INCLUDED
