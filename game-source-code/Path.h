#ifndef PATH_H_INCLUDED
#define PATH_H_INCLUDED

#include "IMazeEntity.h"
#include "Common.h"

/** \class Path
 *  \brief This is a Class that inherits from the IMazeEntity class. It
 *  contains virtual functions that have been overridden. It models
 *	a path object. When active Pacman and Ghosts can move into a path.
 *  \author 719597 Tarryn Maggs and 1033379 Thokozani Msezane.
 *  \version 3.0
 */


class Path :public IMazeEntity
{
public:

    /** \brief Parameterized constructor. Creates a Path object.
     *  \param position is of type sf::Vector2f, contains the door's origin position.
     */
    Path(sf::Vector2f position);

    /** \brief Default Destructor. Destroys a Path object.
     */
    ~Path();


    /** \brief Inherited from IMazeEntity. A virtual function that
     *  gets the position of a Path object.
     *  \return sf::Vector2f with the position
     */
    virtual sf::Vector2f getPosition() const override;

    /** \brief Inherited from IMazeEntity. A virtual function that
     *  gets the ID of the Path object.
     *  \return Entity_ID an enumeration type defined in Common.h
     */
    virtual Entity_ID getEntityID() const override;

    /** \brief Inherited from IMazeEntity. A virtual function that
     *  gets the status (active/inactive/transition) of a Path object.
     *  \return STATUS, an enumeration type defined in Common.h
     */
    virtual STATUS getStatus()const override;

    /** \brief Inherited from IMazeEntity. A virtual function that
     *  sets the Path object to inactive.
     */
    virtual void Delete() override;


private:
    Entity_ID _ID;
    sf::Vector2f _PathPosition;
    STATUS Current_Status;
};

#endif // PATH_H_INCLUDED
