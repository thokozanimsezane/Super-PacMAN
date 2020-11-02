#ifndef ISTATICMAZEENTITY_H_INCLUDED
#define ISTATICMAZEENTITY_H_INCLUDED

#include "Common.h"
#include "IMazeEntity.h"

/** \class IStaticMazeEntity
 *  \brief This is a Interface Class that inherits from the IMazeEntity class. It
 *  contains pure virtual functions that will be overridden by derived classes.
 *  \author 719597 Tarryn Maggs and 1033379 Thokozani Msezane.
 *  \version 3.0
 */


 class IStaticMazeEntity :public IMazeEntity
 {
 public:

     /** \brief A pure virtual function that returns the grid the position of derived class objects.
     *  \return current grid posistion type sf::Vector2u.
     */
    virtual sf::Vector2u gridPosition()const=0;
 };

/* the following maze objects are derived from this class
    - fruit
    - doors
    - keys
    - power pellets
    - super pellets
 */

#endif // ISTATICMAZEENTITY_H_INCLUDED
