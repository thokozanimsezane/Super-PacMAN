#ifndef SUPER_PELLET_H_INCLUDED
#define SUPER_PELLET_H_INCLUDED

#include "IStaticMazeEntity.h"
#include "Common.h"

/** \class SuperPellet
 *  \brief This Class inherits from the IStaticMazeEntity class. It contains virtual functions that have been overridden.
 *  It models a SuperPellet object. When active it can be eaten by pacman and allows pacman to resize, increase speed and eat through doors.
 *  \author 719597 Tarryn Maggs and 1033379 Thokozani Msezane.
 *  \version 3.0
 */

class SuperPellet :public IStaticMazeEntity
{
public:
    /** \brief Parameterized constructor. Creates a SuperPellet object.
     *  \param position is of type sf::Vector2f contains the super pellet spawn position.
     */
    SuperPellet(sf::Vector2f position);

    /** \brief Default Destructor. Destroys a SuperPellet object.
     */
    ~SuperPellet();


     /** \brief Inherited from IMazeEntity. A virtual function that
     *  gets the position of a SuperPellet object.
     *  \return sf::Vector2f with the position.
     */
    virtual sf::Vector2f getPosition() const override; //2D vector representing the position of the object


     /** \brief Inherited from IMazeEntity. A virtual function that
     *  gets the ID of a SuperPellet object.
     *  \return Entity_ID an enumeration type defined in Common.h
     */
    virtual Entity_ID getEntityID() const override;

    /** \brief Inherited from IMazeEntity. A virtual function that
     *  gets the status (active/inactive/transition) of SuperPellet object.
     *  \return  STATUS, an enumeration type defined in Common.h
     */
    virtual STATUS getStatus() const override; //returns the status of the object


    /** \brief Inherited from IMazeEntity. A virtual function that
     *  sets the SuperPellet object to inactive.
     */
    virtual void Delete() override; //sets the object status to inactive

    /** \brief Inherited from IStaticMazeEntity. A virtual function that
     *  gets the grid position of a SuperPellet object.
     *  \return sf::Vector2f with the grid position.
     */
    virtual sf::Vector2u gridPosition() const override;
private:
    STATUS Current_Status;
    sf::Vector2f _SuperPosition;
    Entity_ID _ID;
};


#endif // SUPER_PELLET_H_INCLUDED
