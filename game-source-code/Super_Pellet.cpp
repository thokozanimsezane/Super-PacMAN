#include "Super_Pellet.h"

SuperPellet::SuperPellet(sf::Vector2f position):Current_Status(ACTIVE), _SuperPosition(position), _ID(SUPER_PELLET)
{   }
SuperPellet::~SuperPellet(){}

sf::Vector2f SuperPellet::getPosition() const //2D vector representing the position of the object
{
    return _SuperPosition;
}

Entity_ID SuperPellet::getEntityID() const
{
    return _ID;
}

STATUS SuperPellet::getStatus() const //returns the status of the object
{
    return Current_Status;
}

void SuperPellet::Delete() //sets the object status to inactive
{
    Current_Status = INACTIVE;
    //_ID = PATH;
}

sf::Vector2u SuperPellet::gridPosition() const
{
    sf::Vector2u grid;
    // since the position of static maze objects is always initialised as the center of a tile,
    // the addition of 0.5 and using the floor function isnt necessary because the result will
    // always be a whole integer. It is kept here for safety sake
    int column = floor((_SuperPosition.x-6)/12+0.5);
    int row = floor((_SuperPosition.y-6)/12+0.5);
    grid.x = row;
    grid.y = column;
    return grid;
}
