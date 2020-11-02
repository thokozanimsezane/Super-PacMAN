#ifndef DOORS_H_INCLUDED
#define GHOST_H_INCLUDED

#include "IStaticMazeEntity.h"
#include "Common.h"

/** \class Doors
 *  \brief This is a Doors Class that inherits from the IStaticMazeEntity class. It
 *  contains virtual functions that have been overridden. It models
 *	a door object. When active pacmann cannot move into a door, when inactive pacman can move through a door.
 *  \author 719597 Tarryn Maggs and 1033379 Thokozani Msezane.
 *  \version 3.0
 */

class Doors :public IStaticMazeEntity
{
public:

    /** \brief Parameterized constructor. Creates a Doors object.
      *  \param position is of type sf::Vector2f, contains the doors spawn position.
      */
    Doors(sf::Vector2f position);

    /** \brief Default Destructor. Destroys a Doors object.
      */
    ~Doors();

    /** \brief Inherited from IMazeEntity. A virtual function that
      *  gets the position of a Doors object.
      *  \return sf::Vector2f with the position.
      */
    virtual sf::Vector2f getPosition() const override; //2D vector representing the position of the object

    /** \brief Inherited from IMazeEntity. A virtual function that
      *  gets the ID of the Doors object.
      *  \return Entity_ID an enumeration type defined in Common.h
      */
    virtual Entity_ID getEntityID() const override;

     /** \brief Inherited from IMazeEntity. A virtual function that
      *  gets the status (active/inactive/transition) of door object.
      *  \return STATUS, an enumeration type defined in Common.h
      */
    virtual STATUS getStatus() const override; //returns the status of the object

     /** \brief Inherited from IMazeEntity. A virtual function that
      *  sets the Doors object to inactive.
      */
    virtual void Delete() override; //sets the object status to inactive

     /** \brief Inherited from IStaticMazeEntity. A virtual function that
      *  gets the grid position of door object.
      *  \return sf::Vector2u with the grid position.
      */
    virtual sf::Vector2u gridPosition() const override;
private:
    STATUS Current_Status;
    sf::Vector2f _DoorPosition;
    Entity_ID _ID;

};

#endif // DOORS_H_INCLUDED
