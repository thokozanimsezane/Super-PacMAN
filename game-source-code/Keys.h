#ifndef KEYS_H_INCLUDED
#define KEYS_H_INCLUDED

#include "IStaticMazeEntity.h"
#include "Common.h"

/** \class Fruit
 *  \brief This is a Class that inherits from the IStaticMazeEntity class. It
 *  contains virtual functions that have been overridden. It models
 *	a key object. A key is associated with a door(s) which it opens when it is eaten by pacman.
 *  \author 719597 Tarryn Maggs and 1033379 Thokozani Msezane.
 *  \version 3.0
 */


class Keys :public IStaticMazeEntity
{
public:

    /** \brief Parameterized constructor. Creates a Keys object.
     *  \param position is of type sf::Vector2f, contains the key spawn position.
     */
    Keys(sf::Vector2f position);

    /** \brief Default Destructor. Destroys a Keys object.
     */
    ~Keys();

    /** \brief Inherited from IMazeEntity. A virtual function that
     *  gets the position of a Keys object.
     *  \return sf::vector2f with the position.
     */
    virtual sf::Vector2f getPosition() const override; //2D vector representing the position of the object

    /** \brief Inherited from IMazeEntity. A virtual function that
     *  gets the ID of a Keys object.
     *  \return Entity_ID an enumeration type defined in Common.h
     */
    virtual Entity_ID getEntityID() const override;

    /** \brief Inherited from IMazeEntity. A virtual function that
     *  gets the status (active/inactive/transition) of a Keys object.
     *  \return STATUS, an enumeration type defined in Common.h
     */
    virtual STATUS getStatus() const override; //returns the status of the object

    /** \brief Inherited from IMazeEntity. A virtual function that
     *  sets Keys object status to inactive.
     */
    virtual void Delete() override; //sets the object status to inactive

    /** \brief Inherited from IStaticMazeEntity. A virtual function that
     *  gets the grid position of a Keys object.
     *  \return sf::Vector2u with the grid position.
     */
    virtual sf::Vector2u gridPosition() const override;
private:
    STATUS Current_Status;
    sf::Vector2f _KeyPosition;
    Entity_ID _ID;
};

#endif // KEYS_H_INCLUDED
