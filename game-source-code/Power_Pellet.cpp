#include "Power_Pellet.h"

PowerPellet::PowerPellet(sf::Vector2f position):Current_Status(ACTIVE), _PowerPosition(position), _ID(POWER_PELLET)
{   }

PowerPellet::~PowerPellet(){}

sf::Vector2f PowerPellet::getPosition() const //2D vector representing the position of the object
{
    return _PowerPosition;
}
Entity_ID PowerPellet::getEntityID() const
{
    return _ID;
}

STATUS PowerPellet::getStatus() const //returns the status of the object
{
    return Current_Status;
}
void PowerPellet::Delete() //sets the object status to inactive
{
    Current_Status = INACTIVE;
    //_ID = PATH;
}

sf::Vector2u PowerPellet::gridPosition() const
{
    sf::Vector2u grid;
    // since the position of static maze objects is always initialised as the center of a tile,
    // the addition of 0.5 and using the floor function isnt necessary because the result will
    // always be a whole integer. It is kept here for safety sake
    int column = floor((_PowerPosition.x-6)/12+0.5);
    int row = floor((_PowerPosition.y-6)/12+0.5);
    grid.x = row;
    grid.y = column;
    return grid;
}
