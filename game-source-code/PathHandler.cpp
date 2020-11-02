#include "PathHandler.h"

PathHandler::PathHandler(std::shared_ptr<MazeManager> maze)
{
    _maze = maze;
    _delta.reset();
}

PathHandler::~PathHandler(){}

PathHandler::PathHandler(){}


bool PathHandler::isValidPath(Direction dir, std::shared_ptr<IDynamicMazeEntity> entity)
{
    _IDCheck = entity->getEntityID();
    _EffectCheck = entity->getEffectStatus();
    sf::Vector2u EntityGridPos = entity->gridPosition();
    sf::Vector2i change;
        switch(dir)
        {
        case Direction::UP:
            {
                change.x  = -1; // looks above
                change.y = 0;
                if (ObjectValid(EntityGridPos, change, true))
                {
                    change.y = -1;
                    auto change2 = change;  change2.y = 1;
                    if (ObjectValid(EntityGridPos, change, false)||ObjectValid(EntityGridPos, change2, false))
                        return true;
                    else
                        return false;
                }
                else
                {   return false;   }
                break;
            }
        case Direction::DOWN:
            {
                change.x = 1;
                change.y = 0;
                if (ObjectValid(EntityGridPos, change, true))
                {
                    change.y = -1;
                    auto change2 = change;  change2.y = 1;
                    if (ObjectValid(EntityGridPos, change, false)||ObjectValid(EntityGridPos, change2, false))
                        return true;
                    else
                        return false;
                }
                else
                {   return false;   }
                break;
            }
        case Direction::LEFT:
            {
                change.x = 0;
                change.y = -1;
                if (ObjectValid(EntityGridPos, change, true))
                {
                    change.x = -1;
                    auto change2 = change;  change2.x = 1;
                    if (ObjectValid(EntityGridPos, change, false)||ObjectValid(EntityGridPos, change2, false))
                        return true;
                    else
                        return false;
                }
                else
                {   return false;   }
                break;
            }
        case Direction::RIGHT:
            {
                change.x = 0;
                change.y = 1;
                if (ObjectValid(EntityGridPos, change, true))
                {
                    change.x = -1;
                    auto change2 = change;  change2.x = 1;
                    if (ObjectValid(EntityGridPos, change, false)||ObjectValid(EntityGridPos, change2, false))
                        return true;
                    else
                        return false;
                }
                else
                {   return false;   }
                break;
            }
        case Direction::NONE:
            break;
        }

            return false;
}


bool PathHandler::ObjectValid(sf::Vector2u EntityGridPos, sf::Vector2i change, bool checkMore)
{
    std::shared_ptr<IMazeEntity> Obstacle;
    Obstacle = _maze->returnGridEntity((EntityGridPos.x+change.x)%60, (EntityGridPos.y+change.y)%55);

    Entity_ID ObID = Obstacle->getEntityID();
    STATUS ObStat = Obstacle->getStatus();
    if (ObStat == STATUS::ACTIVE) //looks twice for path
                {
                    switch(ObID)
                    {
                    case Entity_ID::PATH:
                        {
                            if (checkMore)
                            {
                                //! check the obstacle one ahead of the path
                            if (abs(change.x) == 2 || abs(change.y) == 2)
                            {
                                return true;
                            }
                            if (abs(change.x) == 1 || abs(change.y) == 1)
                            {
                                // add an extra value to check start of new 5 x 5 tile
                                //change the change values
                                if (change.x == 1)
                                {       change.x = 2;       }
                                if (change.x == -1)
                                {       change.x = -2;       }
                                if (change.y == 1)
                                {       change.y = 2;       }
                                if (change.y == -1)
                                {       change.y = -2;       }

                            }

                            //! checks the object one ahead/behind the path.
                           if (ObjectValid(EntityGridPos, change, true))
                                {
                                    // if the object ahead/behind IS a path, then the path is clear
                                    return true;
                                }
                            else
                                // if the object ahead/behinf ISNT a path, and is an active door or
                                // wall, then the path is not clear
                                {       return false;       }
                            }
                            else
                                return true;
                            break;
                        }
                    case Entity_ID::WALL:
                        {   return false;   break;   }
                    case Entity_ID::DOOR:
                        {
                            if (_IDCheck == Entity_ID::PACMAN)
                                {
                                    if (_EffectCheck == EffectStatus::SUPER)
                                    {
                                        return true;
                                    }
                                    else
                                        return false;
                                }
                            else
                                return false;

                            break;
                        }
                    case Entity_ID::FRUIT:
                        {
                            return true;
                            break;
                        }
                    case Entity_ID::GHOST:
                        {
                            return true;
                            break;
                        }
                    case Entity_ID::KEY:
                        {
                            return true;
                            break;
                        }
                    case Entity_ID::PACMAN:
                        {
                            return true;
                            break;
                        }
                    case Entity_ID::POWER_PELLET:
                        {
                            return true;
                            break;
                        }
                    case Entity_ID::SUPER_PELLET:
                        {
                            return true;
                            break;
                        }
                    case Entity_ID::GHOST_DOOR:
                        {
                            //! check the obstacle one ahead of the path
                            if (abs(change.x) == 2 || abs(change.y) == 2)
                            {
                                return true;
                            }
                            if (abs(change.x) == 1 || abs(change.y) == 1)
                            {
                                // add an extra value to check start of new 5 x 5 tile
                                //change the change values
                                if (change.x == 1)
                                {       change.x = 2;       }
                                if (change.x == -1)
                                {       change.x = -2;       }
                                if (change.y == 1)
                                {       change.y = 2;       }
                                if (change.y == -1)
                                {       change.y = -2;       }

                            }

                            //! checks the object one ahead/behind the path.
                           if (ObjectValid(EntityGridPos, change,true))
                                {
                                    // if the object ahead/behind IS a path, then the path is clear
                                    return true;
                                }
                            else
                                // if the object ahead/behinf ISNT a path, and is an active door or
                                // wall, then the path is not clear
                                {       return false;       }
                            return true;
                            break;
                        }
                    }
                }
                else
                {
                    return true;
                }
                return false; //just in case nothing is returned
}


void PathHandler::managePath(std::shared_ptr<IDynamicMazeEntity> entity)
{
    double time = _delta.stop();
    Direction _dir = entity->getDesiredDirection();
        if (isValidPath(_dir, entity))
        {
            switch(_dir)
            {
            case Direction::UP:
                {
                    entity->moveUp(time);
                    break;
                }
            case Direction::DOWN:
                {
                    entity->moveDown(time);
                    break;
                }
            case Direction::LEFT:
                {
                    entity->moveLeft(time);
                    break;
                }
            case Direction::RIGHT:
                {
                    entity->moveRight(time);
                    break;
                }
            case Direction::NONE:
                {
                    break;
                }
            }
        entity->setDesiredDirection(Direction::NONE);
        }
    _delta.reset();
}
