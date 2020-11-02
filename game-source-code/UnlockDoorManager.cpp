#include "UnlockDoorManager.h"

UnlockDoorManager::UnlockDoorManager(vector<shared_ptr<IStaticMazeEntity>>& keyDoors)
{
    _keyAndDoors = keyDoors;
    splitObjects();
    _distanceMultiplier = 70;
    assignKeys();
}

UnlockDoorManager::UnlockDoorManager(){}

void UnlockDoorManager::splitObjects()
{
    for (auto& obj : _keyAndDoors)
    {
        if (obj->getEntityID() == Entity_ID::KEY)
        {
            _key_objects.push_back(obj);
        }
        else if (obj->getEntityID() == Entity_ID::DOOR)
        {
            _door_objects.push_back(obj);
        }
    }
}

// link key to a door
void UnlockDoorManager::linkDoorTiles()
{
    vector<shared_ptr<IStaticMazeEntity>> doorLink;
    auto TempDoorHolder = _door_objects;

    int doorObjSize = _door_objects.size();
    if ((doorObjSize%3)!=0)
    {
        throw "Too many Door objects, there can only 3 objects per 'door'";
    }

    int i = 0;
    int j = 0;
   for (auto it = TempDoorHolder.begin(); it != TempDoorHolder.end(); it++)
    {
        auto position1 = TempDoorHolder[i]->getPosition();
        doorLink.push_back(TempDoorHolder[i]);
        j = 0;

        for (auto jt = TempDoorHolder.begin(); jt!= TempDoorHolder.end(); jt++)
        {
            if (j == static_cast<int>(TempDoorHolder.size()-2)) //accounts for when we reach the end of the tempdoorholder
            {
                doorLink.push_back(TempDoorHolder[j]);
                doorLink.push_back(TempDoorHolder[j+1]);
                break;
            }
            auto position2 = TempDoorHolder[j]->getPosition();
            if (checkDistance(position1, position2)==12 || checkDistance(position1, position2)== 24)
            {
                doorLink.push_back(TempDoorHolder[j]);
                TempDoorHolder.erase(TempDoorHolder.begin()+j); //so that it doesnt cycle through again
            }
            else
                {   j++;            }
        }

        /*if(doorLink.size() > 3)
        {
            throw "Too many door objects linked";
        }*/

        doorVect.push_back(doorLink);
        if (doorLink.size() == 3)
        {
            i++;
            doorLink.clear();
        }

        // for Map.Orig = 37doors
        if (i == static_cast<int>(TempDoorHolder.size()) || i == doorObjSize/3 ) // breaks once all the doors have been found
        {
            break;
        }
    }
}

//! Note for future release -> randomise the key allocation
void UnlockDoorManager::assignKeys() //assigns all doors in given distance to a single Key
{
    linkDoorTiles(); //before assigning the keys, link all door tiles together
    float Distance;
    auto tempDoorGrouping = doorVect;
    vector<shared_ptr<IStaticMazeEntity>> firstDoor;
    sf::Vector2f emptyPos(0,0); // means no key was assigned. if this is the case - find nearest other first door and assign same key

    // save the center of each grouping of 3 door objects
    // from linkDoorTiles() -> doors are always stored such that the middle door is the 2nd door in the vector
    for (int i = 0; i< static_cast<int>(tempDoorGrouping.size()); i++) // 37
    {
        firstDoor.push_back(tempDoorGrouping[i][1]);
    }
    vector<sf::Vector2f> keyPerDoor;
    int initialFirstDoorSize = firstDoor.size();

    for (int it = 0; it < initialFirstDoorSize; it++)
    {
        auto DoorPos = firstDoor[it]->getPosition();
        int k = 0;
        for (auto& key : _key_objects)
        {
            k++;
            auto keyPos = key->getPosition();
            Distance = checkDistance(keyPos, DoorPos);
            if (Distance <= _distanceMultiplier)
                {
                    keyPerDoor.push_back(keyPos);
                    break;
                }
            if ( k == static_cast<int>(_key_objects.size()))
                {
                        auto checkPos = DoorPos;
                        for (int c = 0; c < static_cast<int>(firstDoor.size()); c++)
                        {
                            auto compareDoor = firstDoor[c];
                            auto comparePos = compareDoor->getPosition();
                            Distance = checkDistance(checkPos, comparePos);
                            //remained relatively the same relationship to a KEY for 115 & 146
                            if (Distance <= 146 && Distance != 0)
                            {
                                keyPerDoor.push_back(keyPerDoor[c]);
                                break;
                            }
                        }
                }
        }
    }
    auto TempKeys = _key_objects;

    vector<shared_ptr<IStaticMazeEntity>> doorsPerKey;
    vector<vector<shared_ptr<IStaticMazeEntity>>> keyDoors;
    for (auto& key : _key_objects)
    {
        doorsPerKey.clear();
        auto KeyPosition = key->getPosition();

        for (int it = 0; it < static_cast<int>(keyPerDoor.size()); it++)
        {
            auto kePDoorPos = keyPerDoor[it];
            if (KeyPosition == kePDoorPos)
            {
                doorsPerKey.push_back(firstDoor[it]);
            }
        }
        keyDoors.push_back(doorsPerKey);
        KeyMap.insert(std::pair<shared_ptr<IStaticMazeEntity>, vector<shared_ptr<IStaticMazeEntity>> > (key,doorsPerKey));
    }
    _keyDoors = keyDoors;
}

 void UnlockDoorManager::updateDoors() //when a key is used
 {
     std::map<shared_ptr<IStaticMazeEntity>, vector<shared_ptr<IStaticMazeEntity>>>::iterator itr;
     for (itr = KeyMap.begin(); itr!= KeyMap.end(); ++itr)
     {
         STATUS keyStat = itr->first->getStatus();
         switch (keyStat)
         {
         case STATUS::ACTIVE:
            {
                //no change
                break;
            }
         case STATUS::INACTIVE:
            {
                for (int i = 0; i < static_cast<int>(itr->second.size()); i++)
                {
                    itr->second[i]->Delete();
                    auto findPos = itr->second[i]->getPosition();
                    for (auto& door : doorVect)
                    {
                        auto checkPos = door[1]->getPosition();
                        if (checkPos == findPos)
                        { // delete the other doors in the linked door vector
                            door[0]->Delete();
                            door[2]->Delete();
                        }
                    }
                }
                break;
            }
         case STATUS::TRANSITION: //door should NEVER be in a transition state
            {
                throw "Door cannot be in a transition state!";
                break;
            }
         }
     }
     unlockRestDoor(); // for if a super pellet has been eaten
 }

 void UnlockDoorManager::unlockRestDoor()
 {
     for (auto& door: doorVect)
     {
         for (int i = 0; i < 3; i++)
         {
             if (door[i]->getStatus() == INACTIVE)
             {
                 int j = i;
                 j++;
                 j = j%3;
                 door[j]->Delete();
                 j++;
                 j = j%3;
                 door[j]->Delete();
                 break;
                 std::cout << "check nothing" << std::endl;
             }
         }
     }
 }

float UnlockDoorManager::checkDistance(sf::Vector2f position1, sf::Vector2f position2)
{
    float distance = sqrt(pow((position1.x - position2.x),2)+ pow((position1.y - position2.y),2));
    return distance;
}
