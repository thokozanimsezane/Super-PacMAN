#ifndef GAMELOGIC_H_INCLUDED
#define GAMELOGIC_H_INCLUDED

#include "Common.h"
#include "CollisionManager.h"
#include "MazeManager.h"
#include "PathHandler.h"
#include "FileManager.h"
#include "GhostMovementManager.h"

//GameLogic class

/** \class GameStateManager
 *  \brief This is a logic layer class that is  responsible for all game logic.
 *  This class creates the game (creates the MazeManager), creates the UnlockDoorManager, the collision manager, the Ghost movement manager, and the pathHandler.
 *  Interprets the user input (it is not responsible for taking the input), and converts user input to a desired direction for pacman.
 *  \author 719597 Tarryn Maggs and 1033379 Thokozani Msezane.
 *  \version 3.0
 */
class GameLogic
{
public:

    /** \brief Parameterized constructor. Creates a GameLogic object.
     *  \param Lives is of type int, holds the number of lives pacman has.
	 *	\param filename is of type string, specifies the map filename (used to create the maze).
     */
    GameLogic(int Lives, std::string filename);

    /** \brief Default Destructor. Destroys a GameLogic object.
     */
    ~GameLogic();

    /** \brief Interprets the user input from the key board.
     *  \param _input is of type UserInput an enumeration type defined in Common.h
     */
    void InterpretInput(UserInput _input);

    /** \brief This function handles the running of the maze, it calls the pathHandler to determine if pacman can be moved in its desired
		direction. It tells the ghostMovement manager to move the ghosts in their desired direction. It calls the collisions manager to
		determine if a collision occurred between entities. It asks the updateDoorManager to update the doors of the maze.
     */
    void runMaze();

    /** \brief This function returns the game progress (level incomplete/complete or game won/over).
     *  \return Game_Status, an enumeration type.
     */
    Game_Status returnGameProgress();


    /** \brief This function packages all the maze entities into a single vector.
     *  \return std::vector of shared pointers of type IMazeEntity.
     */
    std::vector<std::shared_ptr<IMazeEntity>>& packageEntities();

    /** \brief This function packages all the dynamic maze entities into a single vector.
     *  \return std::vector of shared pointers of type IDynamicMazeEntity.
     */
    std::vector<std::shared_ptr<IDynamicMazeEntity>>& packageDynamic();

    /** \brief Returns the score pacamn has obtained from eating the fruit and ghosts.
     *  \return int.
     */
    int returnScore();

    /** \brief This function returns the lives pacman has left.
     *  \return int.
     */
    int returnLives();


private:

    /** \brief Initializes the game logic
     *  \param Lives is of type int.
     */
    void InitializeLogic(int Lives);

    Direction _dir;
    //need to also account for spacebar for speedUp
    std::vector<std::shared_ptr<IDynamicMazeEntity>> _dynamic;
    std::vector<std::shared_ptr<IMazeEntity>> _everything;

    std::shared_ptr<MazeManager> maze;
    CollisionManager _collisions;
    UnlockDoorManager _doorManage;

    std::shared_ptr<PathHandler> _pathHandle;
    std::shared_ptr<Pacman> _pacman;
    std::shared_ptr<GhostMovementManager> _moveGhosts;

};
#endif // GAMELOGIC_H_INCLUDED

