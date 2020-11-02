#ifndef WALL_H_INCLUDED
#define WALL_H_INCLUDED

#include "IMazeEntity.h"
#include "Common.h"

/** \class Wall
 *  \brief This Class inherits from the IMazeEntity class. It contains virtual functions that have been overridden.
 *  It models a Wall object. A Wall prevents ghosts amd Pacman from moving through it.
 *  \author 719597 Tarryn Maggs and 1033379 Thokozani Msezane.
 *  \version 3.0
 */

class Wall :public IMazeEntity
{
public:

    /** \brief Parameterized constructor. Creates a Wall object.
     *  \param position is of type sf::Vector2f.
     */
    Wall(sf::Vector2f position);

    /** \brief Default Destructor. Destroys a Wall object.
     */
    ~Wall();

    /** \brief Inherited from IMazeEntity. A virtual function that
     *  gets the position of a Wall object.
     *  \return sf::Vector2f with the position of the object.
     */
    virtual sf::Vector2f getPosition() const override;

    /** \brief Inherited from IMazeEntity. A virtual function that
     *  gets the ID of a Wall object.
     *  \return Entity_ID an enumeration type defined in Common.h
     */
    virtual Entity_ID getEntityID() const override;


    /** \brief Inherited from IMazeEntity. A virtual function that
     *  gets the status (active/inactive/transition) of a Wall object.
     *  \return STATUS, an enumeration type defined in Common.h
     */
    virtual STATUS getStatus()const override;

    /** \brief Inherited from IMazeEntity. A virtual function that does
     *  nothing for a Wall object.
     */
    virtual void Delete() override;

private:
    Entity_ID _ID;
    sf::Vector2f _wallPosition;
    STATUS Current_Status;

};


#endif // WALL_H_INCLUDED
