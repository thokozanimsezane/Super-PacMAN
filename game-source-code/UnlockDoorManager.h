#ifndef UNLOCKDOORMANAGER_H_INCLUDED
#define UNLOCKDOORMANAGER_H_INCLUDED

#include "Common.h"
#include "MazeManager.h"

//class TooManyDoorObjects linked
/** \class UnlockDoorManager
 *  \brief  UnlockDoorManager is responsible for linking the surrounding groups of 3 doors to a single door vector
 *  which is then used in the allocation of doors to keys, as well as the unlocking of the linked doors when a key is collided
 *  with or a single door object is set to inactive by pacman colliding with it.
 *  \author 719597 Tarryn Maggs and 1033379 Thokozani Msezane.
 *  \version 3.0
 */
class UnlockDoorManager
{
public:

    /** \brief Parameterized constructor. Creates an UnlockDoorManager object. Calls the functions splitObjects, linkDoorTiles
     *  and assignKeys.
     *  \param keyDoors is a vector of shared pointers of type IStaticMazeEntity.
     */
    UnlockDoorManager(vector<shared_ptr<IStaticMazeEntity>>& keyDoors);

    /** \brief A default Constructor, creates an UnlockDoorsManager object.
     */
    UnlockDoorManager();
    //~UnlockDoorManager();
    /** \brief This function uses a map created between the middle door objects of all door groups and their corresponding key
     *  and updates the linked remaining active doors to inactive when a key is collided with - set to inactive.
     *  This function is also responsible to calling the function unlockRestDoor.
     */
    void updateDoors(); //when a key is used

private:
    /** \brief Responsible for spliting the input from the mazeManager, a vector of shared pointers of
     *  type IStaticMazeEntity, into a vector for entities with the ID: Keys and another vector for the entities
     *  with the ID: Doors
     */
    void splitObjects();

    /** \brief Responsible for linking the surrounding groups of 3 door objects into a single vector of door objects which
     *  is then added into a vector of vectors of shared pointers of type IStaticMazeEntity. Each vector within this vector
     *  represents a group of door ojects. Doors are always linked such that the middle door is always stored in the second
     *  second position of the inner vector.
     */
    void linkDoorTiles();

    /** \brief Responsible for assigning a key to a door vector (or multiple door vectors).
     *  Determines which key will be assigned to a door vector by using the checkDistance function to determine the distance
     *  between the middle door of the door vector and the key, if the distance is less than the distance multiplier then the
     *  key is linked to the door vect. This function creates a map which links the key to multiple middle door objects.
     */
    void assignKeys();

    /** \brief This function is used to unlock the rest of the grouped door objects (group of 3) when a single door object is
     *   eaten by super pacman.
     */
    void unlockRestDoor();

    /** \brief This function calculates the distance between two given positions.
     *  \param position1 is of type sf::Vector2f.
     *  \param position2 is of type sf::Vector2f.
     *  \return float. result of the distance calculation between position1 and position2
     */
    float checkDistance(sf::Vector2f position1, sf::Vector2f position2);


    float  checkDistance(sf::Vector2u position1, sf::Vector2u position2);



    float _distanceMultiplier; //created at the start of the level, used in future versions to increase the distance at which keys can be linked
    vector<shared_ptr<IStaticMazeEntity>> _keyAndDoors;
    vector<vector<shared_ptr<IStaticMazeEntity>>> _keyDoors;

    vector<vector<shared_ptr<IStaticMazeEntity>>> doorVect;
    std::map<shared_ptr<IStaticMazeEntity>, vector<shared_ptr<IStaticMazeEntity>> > KeyMap;
    vector<shared_ptr<IStaticMazeEntity>> _door_objects;
    vector<shared_ptr<IStaticMazeEntity>> _key_objects;
};

#endif // UNLOCKDOORMANAGER_H_INCLUDED
