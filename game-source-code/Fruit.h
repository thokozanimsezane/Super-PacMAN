#ifndef FRUIT_H_INCLUDED
#define FRUIT_H_INCLUDED

#include "IStaticMazeEntity.h"
#include "Common.h"

/** \class Fruit
 *  \brief This is a Fruit Class that inherits from the IStaticMazeEntity class. It
 *  contains virtual functions that have been overridden. It models
 *	a fruit object. A fruit can be eaten by pacman when in active state.
 *  \author 719597 Tarryn Maggs and 1033379 Thokozani Msezane.
 *  \version 3.0
 */

class Fruit :public IStaticMazeEntity
{
public:

    /** \brief Parameterized constructor. Creates a Fruit object.
      *  \param position is of type sf::Vector2f, contains the fruit spawn position
      */
    Fruit(sf::Vector2f position);

    /** \brief Default Destructor. Destroys a Fruit object.
      */
    ~Fruit();

    /** \brief Inherited from IMazeEntity. A virtual function that
      *  gets the position of a fruit object.
      *  \return sf::vector2f with the position.
      */
    virtual sf::Vector2f getPosition() const override; //2D vector representing the position of the object

    /** \brief Inherited from IMazeEntity. A virtual function that
      *  gets the ID of a Fruit object.
      *  \return Entity_ID, an enumeration type defined in Common.h.
      */
    virtual Entity_ID getEntityID() const override;

    /** \brief Inherited from IMazeEntity. A virtual function that
      *  gets the status (active/inactive/transition) of a fruit object.
      *  \return STATUS, an enumeration type defined in Common.h.
      */
    virtual STATUS getStatus() const override; //returns the status of the object

     /** \brief Inherited from IMazeEntity. A virtual function that
      *  sets fruit object status to inactive.
      */
    virtual void Delete() override; //sets the object status to inactive


    /** \brief Inherited from IStaticMazeEntity. A virtual function that
      *  gets the grid position of a fruit object.
      *  \return sf::Vector2u with the grid position.
      */
    virtual sf::Vector2u gridPosition() const override;

private:
    STATUS Current_Status;
    sf::Vector2f _FruitPosition;
    Entity_ID _ID;
};

#endif // FRUIT_H_INCLUDED
