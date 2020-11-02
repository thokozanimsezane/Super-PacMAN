#ifndef POWER_PELLET_H_INCLUDED
#define POWER_PELLET_H_INCLUDED

#include "IStaticMazeEntity.h"
#include "Common.h"


/** \class PowerPellet
 *  \brief This Class inherits from the IStaticMazeEntity class. It contains virtual functions that have been overridden.
 *  It models a PowerPellet object. When active it can be eaten by pacman and allows pacman to eat ghosts.
 *  \author 719597 Tarryn Maggs and 1033379 Thokozani Msezane.
 *  \version 3.0
 */


class PowerPellet :public IStaticMazeEntity
{
public:

    /** \brief Parameterized constructor. Creates a PowerPellet object.
     *  \param position is of type sf::Vector2f contains the power pellet spawn position.
     */
    PowerPellet(sf::Vector2f position);

    /** \brief Default Destructor. Destroys a PowerPellet object.
     */
    ~PowerPellet();

    /** \brief Inherited from IMazeEntity. A virtual function that
     *  gets the position of a PowerPellet object.
     *  \return sf::Vector2f with the position.
     */
    virtual sf::Vector2f getPosition() const override; //2D vector representing the position of the object

    /** \brief Inherited from IMazeEntity. A virtual function that
     *  gets the ID of a PowerPellet object.
     *  \return Entity_ID an enumeration type defined in Common.h
     */
    virtual Entity_ID getEntityID() const override;

    /** \brief Inherited from IMazeEntity. A virtual function that
     *  gets the status (active/inactive/transition) of PowerPellet object.
     *  \return STATUS, an enumeration type defined in Common.h
     */
    virtual STATUS getStatus() const override; //returns the status of the object

    /** \brief Inherited from IMazeEntity. A virtual function that
     *  sets the PowerPellet object to inactive.
     */
    virtual void Delete() override; //sets the object status to inactive

    /** \brief Inherited from IStaticMazeEntity. A virtual function that
     *  gets the grid position of a PowerPellet object.
     *  \return sf::Vector2f with the grid position.
     */
    virtual sf::Vector2u gridPosition() const override;


private:
    STATUS Current_Status;
    sf::Vector2f _PowerPosition;
    Entity_ID _ID;
};

#endif // POWER_PELLET_H_INCLUDED
