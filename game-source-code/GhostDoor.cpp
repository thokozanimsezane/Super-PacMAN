#include "GhostDoor.h"

GhostDoor::GhostDoor(sf::Vector2f position): Current_Status(ACTIVE),_DoorPosition(position), _ID(GHOST_DOOR)
{   }

GhostDoor::~GhostDoor(){}

sf::Vector2f GhostDoor::getPosition() const //2D vector representing the position of the object
{
    return _DoorPosition;
}

Entity_ID GhostDoor::getEntityID() const
{
    return _ID;
}

STATUS GhostDoor::getStatus()  const//returns the status of the object
{
    return Current_Status;
}
void GhostDoor::Delete()
{
    Current_Status = ACTIVE;//remains active - ghost door never deleted
}
