#ifndef MAZEMANAGER_H_INCLUDED
#define MAZEMANAGER_H_INCLUDED

#include "FileManager.h"
#include "Common.h"
#include "Pacman.h"
#include "Ghost.h"
#include "Wall.h"
#include "Path.h"
#include "Fruit.h"
#include "Keys.h"
#include "Doors.h"
#include "Super_Pellet.h"
#include "Power_Pellet.h"
#include "GhostDoor.h"

using std::shared_ptr;
using std::vector;

//const int map_width = 55;
//const int map_height = 60;
const sf::Vector2f mapTileSize(12,12); //each maze tile is 12x12pixels

/** \class MazeManager
 *  \brief A Logic layer class, it creates the maze itself, reads a map file and populates maze with
 *   every element corresponding to the map. This class is the base functional class of the entire game.
 *   It creates all the objects and sends them to GameLogic.  Maze manager also returns a vector
 *   of vectors (simulates the concept of a 2D grid, where the first entry is the row and the second entry is the column).
 *  \author 719597 Tarryn Maggs and 1033379 Thokozani Msezane.
 *  \version 3.0
 */
class MazeManager
{
public:

    /** \brief Parameterized Constructor. Constructs a MazeManager object.
     *  This class is responsible for loading all entities from the text file. This function calls the Initialize function.
     *  \param filename is of type string. Used to call the fileManager to create the maze from the specified filename.
     *  \param isGame is of type bool. used to determine if the maze is being called from the main game or the map editor
     *  \param isOptions is of type bool. used to determine if the maze manager is being called to created the options menu of the map editor
     */
    MazeManager(const std::string filename, bool isGame, bool isOptions);

    /** \brief Default Destructor. Destroys a MazeManager object.
      */
    ~MazeManager();

    /** \brief This function is a shared pointer of type IMazeEntity and
     *   returns the enitity in the specified grid position. This function is used to determine collisions or the possibility
     *  between elements of the maze.
     *  \param row is of tpe int.
     *  \param column is of type int.
     */
    shared_ptr<IMazeEntity> returnGridEntity(int row, int column);

    /** \brief This function is a shared pointer of type Pacman and returns a Pacman object
     *  \return Shared pointer of type Pacman.
     */
    shared_ptr<Pacman>& returnPacman();

    /** \brief This function returns the number of fruit objects in the maze
     *  \return int.
     */
    int returnFruitNumber();

    // includes pacman and ghosts
    /** \brief This function packages all dynamic elements (ghost/pacman) into a single returnable vector to be used elsewhere
     *  \return Vector of shared pointers of type IDynamicMazeEntity.
     */
    vector<shared_ptr<IDynamicMazeEntity>>& packageDynamicElements();

    // includes packagePaths, packageElements & path objects
    // called in initialisation - avoids it being called multiple times thereby increasing operation time
    /** \brief This function packages all maze elements, except for Dynamic elements, into a single returnable vector to be used elsewhere
     *  \return Vector of shared pointers of type IMazeEntity.
     */
    vector<shared_ptr<IMazeEntity>>& packageEverything();

    //to be sent to UnlockDoorManager
    /** \brief This function packages all key and door elements into a single returnable vector to be used in UnlockDoorManager
     *   \return Vector of shared pointers of type IStaticMazeEntity.
     */
    vector<shared_ptr<IStaticMazeEntity>>& packageKeysDoors();

	//to be sent to Map Editor
    /** \brief This function packages all maze entities into a vector of vectors, representing the 2D grid of the maze
     *   \return Vector of vectors of shared pointers of type IStaticMazeEntity.
     */
    std::vector<std::vector<std::shared_ptr<IMazeEntity>>> ReturnMazeGrid();


private:
        int* _tiles;
        /** \brief This function is responsible for the creation of the maze elements, it is used to populate the game with the entities
         *  specified by the array created using the specified filename in the constructor
         *  \param isGame is of type bool. used to determine if the maze is being called from the main game or the map editor
         *  \param isOptions is of type bool. used to determine if the maze manager is being called to created the options menu of the map editor
         */
        void Initialize(bool isGame, bool isOptions);

        /** \brief This function is used to create a vector of obstruction_objects of type IMazeEntity. It includes the wall and door objects created.
         */
        void packPaths();

        /** \brief This function is used to create a vector of Maze_objects of type IMazeEntity. It includes fruit, super_pellets, power_pellets
         *  and key objects created.
         */
        void packElements();

        /** \brief This function is responsible for packaging all dynamic maze entities into a single vector to be sent to the Logic Layer.
         *  It includes the ghost objects and the pacman object. This function is further responsible for the setting of each ghost's individual ghost ID.
         */
        void PackDynamicElements();

        /** \brief This function is responsible for packaging all elements (except the dynamic elements), from the functions packPaths and packElements, to
         *  be sent to the Logic Layer of the game.
         */
        void packEverything();

        /** \brief This function is responsible for updating the maze grid if the MazeManager has been called from inGame, (Created with inGame = true).
         *  This function increases the radius in which collisions can occur with the entities: Key, Power_Pellet, Super_Pellet and Fruit. By altering the
         *  maze Grid such that the new grid has a shared pointer which lies to the left and right of the central object as well as above and below.
         */
        void updateGrid();

        vector<vector<shared_ptr<IMazeEntity>>> _mazeGrid;

        shared_ptr<Pacman> _pacman;
        vector<shared_ptr<Wall>> _wall_objects;
        vector<shared_ptr<Path>> _path_objects;
        vector<shared_ptr<Doors>> _door_objects;
        vector<shared_ptr<Fruit>> _fruit_objects;
        vector<shared_ptr<Keys>> _key_objects;
        vector<shared_ptr<SuperPellet>> _super_objects;
        vector<shared_ptr<PowerPellet>> _power_objects;
        vector<shared_ptr<Ghost>> _Ghost_objects;

        vector<shared_ptr<IStaticMazeEntity>> _keyAndDoors;

        vector<shared_ptr<IMazeEntity>> obstruction_objects_;
        vector<shared_ptr<IStaticMazeEntity>> Maze_objects_;

        vector<shared_ptr<IDynamicMazeEntity>> Dynamic_objects_;
        vector<shared_ptr<IMazeEntity>> package_everything_;
};

#endif // MAZEMANAGER_H_INCLUDED
