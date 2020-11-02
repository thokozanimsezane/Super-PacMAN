#ifndef GHOSTDOOR_H_INCLUDED
#define GHOSTDOOR_H_INCLUDED

#include "IStaticMazeEntity.h"
#include "Common.h"
//similar to path class, however will form a barrier for ghosts - not pacman

/** \class GhostDoor
 *  \brief This Class inherits from the IMazeEntity class. It contains virtual functions that have been overridden.
 *  It models a ghost door object. When active prevents ghosts from moving back into the ghost house.
 *  \author 719597 Tarryn Maggs and 1033379 Thokozani Msezane.
 *  \version 3.0
 */

class GhostDoor :public IMazeEntity
{
public:

    /** \brief Parameterized constructor. Creates a GhostDoor object.
     *  \param position is of type sf::Vector2f, contains the ghost door spawn position.
     */
    GhostDoor(sf::Vector2f position);

    /** \brief Default Destructor. Destroys a GhostDoor object.
     */
    ~GhostDoor();

    /** \brief Inherited from IMazeEntity. A virtual function that
     *  gets the position of a GhostDoor object.
     *  \return sf::Vector2f with the position
     */
    virtual sf::Vector2f getPosition() const override;

    /** \brief Inherited from IMazeEntity. A virtual function that
     *  gets the ID of the GhostDoor object.
     *  \return Entity_ID an enumeration type defined in Common.h.
     */
    virtual Entity_ID getEntityID() const override;

    /** \brief Inherited from IMazeEntity. A virtual function that
     *  gets the status (active/inactive/transition) of GhostDoor object.
     *  \return STATUS an enumeration type defined in Common.h.
     */
    virtual STATUS getStatus()const override;

    /** \brief Inherited from IMazeEntity. A virtual function that
     *  sets the GhostDoor object to inactive.
     */
    virtual void Delete() override;

private:
    STATUS Current_Status;
    sf::Vector2f _DoorPosition;
    Entity_ID _ID;
};

#endif // GHOSTDOOR_H_INCLUDED
