#ifndef GHOSTMOVEMENTMANAGER_H_INCLUDED
#define GHOSTMOVEMENTMANAGER_H_INCLUDED

#include "Common.h"
#include "Pacman.h"
#include "PathHandler.h"
#include "Ghost.h"
#include <cmath>
#include <algorithm>
#include "StopWatch.h"

/** \class GameMovementManager
 *  \brief This is a class that handles how ghost entities will move throughout the maze.
 *  \author 719597 Tarryn Maggs and 1033379 Thokozani Msezane.
 *  \version 3.0
 */
class GhostMovementManager
{
public:
    /** \brief Parametrized Constructor, creates a GhostMovementManager object.
     *  \param maze is a shared pointer of type MazeManger
     */
    GhostMovementManager(std::shared_ptr<MazeManager> maze);

     /** \brief Default Destructor, destroys a GhostMovementManager object.
      */
    ~GhostMovementManager();

    /** \brief This function moves each ghost to its desired path, it uses chooseMovement.
     *  \param Entities is a vector of shared pointers of type IDynamicMazeEntity.
     */
    void moveToValidPath(std::vector<std::shared_ptr<IDynamicMazeEntity>>& Entities);


private:
    /** \brief This function decides how the entity (ghost) will move depending on _watch status, the effect status and position of the entity.
     *  \param _ghost is a shared pointer of type IDynamicMazeEntity.
     *  \param _watch is of type StopWatch.
     */
    void chooseMovement(std::shared_ptr<IDynamicMazeEntity> _ghost, StopWatch _watch);

    /** \brief This function checks if the ghost is in the spawn box defined as the center box of the maze
     *  \param  position is of type sf::Vector2f.
     *  \return bool.
     */
    bool checkSpawnPointBox(sf::Vector2f position);

    /** \brief This function is called if checkSpawnPointBox returns true, and causes the ghost to move out of the spawn point box
    *  \param _ghost is a shared pointer of type IDynamicMazeEntity.
    *  \param _watch is of type StopWatch
    */
    void moveOut(std::shared_ptr<IDynamicMazeEntity> _ghost, StopWatch _watch);

    /** \brief This function moves the entity, _ghost, towards its respective/designated corner of the maze
    *   \param  _ghost is a shared pointer of type IDynamicMazeEntity.
    */
    void moveDesignated(std::shared_ptr<IDynamicMazeEntity> _ghost);

    /** \brief This function moves the IDynamicMazeEntity (_ghost), towards the position defined by pacPosition
    *  \param  _ghost is a shared pointer of type IDynamicMazeEntity.
    *  \param  pacPosition is of type Vector2f.
    */
    void moveTowards(std::shared_ptr<IDynamicMazeEntity> _ghost, sf::Vector2f pacPosition);

    /** \brief This function determines which direction of two chosen directions, dir1 and dir2, has the longest valid path.
    * It calls checkFuturePath to determine if the path is valid.
    *  \param  dir1 is of type Direction.
    *  \param  dir2 is of type Direction.
    *  \param  _ghost is a shared pointer of type IDynamicMazeEntity.
    *  \return Direction. returns the direction which has the longest valid path, if neither are valid then returns Direction::NONE.
    */
    Direction checkoptions(Direction dir1, Direction dir2, std::shared_ptr<IDynamicMazeEntity> _ghost);

    /** \brief This function is called by checkoptions to determine if the path in the desired direction, dir, is valid.
     *  \param _ghost is a shared pointer of type IDynamicMazeEntity.
     *  \param dir is of type Direction.
     *  \return bool
     */
    bool checkFuturePath(Direction dir, std::shared_ptr<IDynamicMazeEntity> _ghost);

    /** \brief This function is called by checkFuturePath, and is used to determine the length of the valid path in the desired direction, dir.
     *  \param dir is of type Direction.
     *  \param entity is a shared pointer of type IDynamicMazeEntity
     *  \param changenum is of type int. used to check the path changenum positions in the desired direction, dir.
     *  \return bool
     */
    bool checkAhead(Direction dir, std::shared_ptr<IDynamicMazeEntity> entity, int changenum);

     /** \brief This function checks if the object at the position determined by EntityGridPos + change is a valid path or not.
     *  \param  EntityGridPos is of type sf::Vector2u.
     *  \param  change is of type sf::Vector2i.
     *  \return bool
     */
    bool ObjectValid(sf::Vector2u EntityGridPos, sf::Vector2i change);

    std::shared_ptr<MazeManager> _maze;
    int _change;
    sf::Vector2f pacReference;

    StopWatch _red;
    StopWatch _blue;
    StopWatch _pink;
    StopWatch _orange;

    StopWatch _delta;
    double time;

};

#endif // GHOSTMOVEMENTMANAGER_H_INCLUDED
