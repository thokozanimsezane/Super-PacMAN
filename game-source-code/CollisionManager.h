#ifndef COLLISIONMANAGER_H_INCLUDED
#define COLLISIONMANAGER_H_INCLUDED

#include "Common.h"
#include "IDynamicMazeEntity.h"
#include "MazeManager.h"
#include "EffectsManager.h"
#include "UnlockDoorManager.h"


/** \class CollisionManager
 *  \brief A Logic layer class for handling collisions. Manages all collisons in the game, the score and lives remaining.
 *  It is also responsible for determining the game state according to number of fruit or lives remaining.
 *  \author 719597 Tarryn Maggs and 1033379 Thokozani Msezane.
 *  \version 3.0
 */

class CollisionManager
{
public:

    /** \brief A default Constructor, creates a CollisonManager object.
     */
    CollisionManager();

     /** \brief Parameterized Constructor. Constructs a CollisionManager object. creates a Effects Manager object as a private member
      *  \param maze is of type MazeManager and is a shared pointer to the MazeManager Class.
      *  \param Lives is an interger type it contains the number of lives of pacman.
      */
    CollisionManager(std::shared_ptr<MazeManager> maze, int Lives);


    /** \brief Default Destructor. Destroys a CollisionManager object.
      */
    ~CollisionManager();

    /** \brief Manages the collisons between pacman and other maze elements and manages the collision portion of the logic, by calling the function checkCollisions,
      * Managing the effects and transitions due to certain collisions and calling checkStatus.
      */
    void ManageCollisions();


    /** \brief Returns the score pacman has obtained from eating certain maze elements
      * \param int, returns an integer type.
      */
    int returnScore();

    /** \brief Returns the number of lives pacman has remaining
      * \return int, returns an integer type.
      */
    int returnLives();

    /** \brief Returns the game progress, determined by the function checkStatus.
      * \return Game_Status, an enumeration type defined in Common.h
      */
    Game_Status returnGameProgress();

private:

    /** \brief Checks collisions between pacman and other maze objects and ghost entities and calls corresponding function
      * \param movingObjects is a shared pointer of type IDynamicMazeEntity
      */
    void checkCollisions(std::vector<std::shared_ptr<IDynamicMazeEntity>> movingObjects);

    /** \brief Checks collisions between pacman and the ghosts
      * \param entity1 is a shared pointer of type IDynamicMazeEntity
      * \param entity2 is a shared pointer of type IdynamicMazeEntity
      */
    void PacmanVsGhosts(std::shared_ptr<IDynamicMazeEntity> entity1, std::shared_ptr<IDynamicMazeEntity> entity2);

    /** \brief Checks collisions between pacman and maze elements
      * \param entity1 is a shared pointer of type IDynamicMazeEntity
      * \param element is a shared pointer of type IMazeEntity
      */
    void PacmanVsElements(std::shared_ptr<IDynamicMazeEntity> entity1, std::shared_ptr<IMazeEntity> element);

    /** \brief Checks and sets the game status by determining if all the fruit have been eaten and then setting the _gameStatus to
      * LEVEL_COMPLETE or if there are no lives remaining, sets the _gameStatus to GAME_OVER
      */
    void checkStatus();

    /** \brief Deletes a maze entity if a valid collision has occurred.
      * \param entity is a shared pointer of type IDynamicMazeEntity
      */
    void deleteEntity(std::shared_ptr<IDynamicMazeEntity> entity);

    /** \brief Manages the death transitions of all dynamic maze entities
      * \param movingObjects is a vector of shared pointers of type IDynamicMazeEntity
      */
    void ManageTransitions(std::vector<std::shared_ptr<IDynamicMazeEntity>> movingObjects);

    std::shared_ptr<MazeManager> _maze;
    int _score;
    int _scoreMultiplier = 1;

    EffectsManager _effects;
    int _lives;
    int _FruitEaten;
    Game_Status _gameStatus;
    StopWatch _pacWatch, _red, _blue, _pink, _orange;

};
#endif // COLLISIONMANAGER_H_INCLUDED
