#ifndef PATHHANDLER_H_INCLUDED
#define PATHHANDLER_H_INCLUDED

#include "IMazeEntity.h"
#include "IDynamicMazeEntity.h"
#include "MazeManager.h"
#include "StopWatch.h"

/** \class PathHandler
 *  \brief Determines if Pacman's desired direction is valid or not, if not valid then pacman cant move.
 *   Responsible for moving pacman when desired direction is a valid path.
 *  \author 719597 Tarryn Maggs and 1033379 Thokozani Msezane.
 *  \version 3.0
 */

class PathHandler
{
public:

    /** \brief Parameterized constructor. Creates a PathHandler object.
     *  \param maze is a shared pointer of type MazeManager.
     */
    PathHandler(std::shared_ptr<MazeManager> maze);

    /** \brief Default constructor. Creates a PathHandler object.
     */
    PathHandler();

    /** \brief Default destructor. Destroys a PathHandler object.
     */
    ~PathHandler();

    /** \brief This function is responsible for moving an IDynamicMazeEntity (pacman) in its desired direction if it is a valid path.
     *  \param Shared pointer of type IDynamicMazeEntity.
     */
    void managePath(std::shared_ptr<IDynamicMazeEntity>);

private:

    /** \brief This function checks if the path in the direction specified by dir is not a wall or door
     *  \param dir is of type Direction
     *  \param entity is a shared pointer of type IDynamicMazeEntity.
     *  \return bool
     */
    bool isValidPath(Direction dir, std::shared_ptr<IDynamicMazeEntity> entity);

    /** \brief This function is called by isValidPath to check whether the desired direction is a valid path, by determining what entity is at the position = change + entityGridPos.
     *  \param EntityGridPos is of type sf::Vector2u. it is the grid position of the dynamic entity.
     *  \param change is of type sf::Vector2i. determines how far and in which direction we are looking for the valid path
     *  \return bool
     */
    bool ObjectValid(sf::Vector2u EntityGridPos, sf::Vector2i change, bool checkMore);

    std::shared_ptr<MazeManager> _maze;
    Entity_ID _IDCheck;
    EffectStatus _EffectCheck;
    StopWatch _delta;

};

#endif // PATHHANDLER_H_INCLUDED
