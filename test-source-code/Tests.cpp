#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../game-source-code/Pacman.h"

#include <doctest.h>
#include <iostream>
#include "../game-source-code/Common.h"
#include "../game-source-code/FileManager.h"
#include "../game-source-code/MazeManager.h"
#include "../game-source-code/EffectsManager.h"
#include "../game-source-code/PathHandler.h"
#include "../game-source-code/GhostMovementManager.h"
#include "../game-source-code/CollisionManager.h"
#include <string>

#include <thread>
#include <chrono>

using std::cout;
using std::endl;

// ------------------------- FILE MANAGER ----------------------------------- //
TEST_CASE("File Manager: can Read map file and return the corresponding array of integers")
{
    FileManager testFileManager;

    testFileManager.readMapFile("original.txt");

    int *Tiles = testFileManager.returnMap();

    CHECK(Tiles[17+7*55] == 3);
}

TEST_CASE("File Manager: writes a map into a text file given a 2D vector of integers, which is readable by mazemanager.")
{
    FileManager testFileManager;
    std::vector<std::vector<int>> IDGrid(60, std::vector<int>(55,3)); // choosing random integer value
    testFileManager.writeMap("testSourceCodeMap.txt",IDGrid);

    //test by looking at map, or reading the maze manager?
    MazeManager maze("testSourceCodeMap.txt", false, false); //returns the grid as it is.
    auto elements = maze.packageEverything();
    CHECK_EQ(elements.size(), 3300);
    int num =0;
    for (auto& one : elements)
    {
        if (one->getEntityID() == FRUIT)
        {
            num++;
        }
    }
    CHECK_EQ(elements.size(), num);
}

TEST_CASE("File Manager: Read all high scores and save to vector which can be made accessible to external functions")
{
     FileManager testFileManager;
     testFileManager.readAllHighScores();
     auto AllScores = testFileManager.returnAllHighScores();
     auto highest = testFileManager.returnHighScore();
     CHECK_EQ(AllScores.size(),10);
     // cannot check according to actual names since:
     // remain commented out as this will change depending on if the game has been played and a new high score has been added.
     // however, this functionality is explored in the Test case below

}

TEST_CASE("File Manager: Check if a given high score is a new high score or not, if so, it can write the new score to HighScores.txt")
{
     FileManager testFileManager;
     testFileManager.readAllHighScores();
     auto AllScores = testFileManager.returnAllHighScores();
     CHECK_EQ(AllScores.size(),10);

     HighScore test;
     test.score = 150;
     test.name = "test";
     bool canTest = false;
     if(testFileManager.findNewScore(test))
     {
         testFileManager.saveNewScore(test); // tests manage high scores too
         canTest = true;
     }

     AllScores = testFileManager.returnAllHighScores();
     CHECK_EQ(AllScores.size(),10);

     if  (canTest)
     {
         for (auto& one :AllScores)
         {
             if (one.name == "test")
             {
                 CHECK_EQ(one.score, 150);
             }
         }
     }
}

//!  Will not Run tests to check the write, read and return map names functionality, since this
//!  will ruin the game play as the user could potentially choose an invalid map name.

// --------------------------- MAZE MANAGER -------------------------------- //
TEST_CASE("Maze Manager")
{
    MazeManager maze("original.txt", true, false);

    auto everything = maze.packageEverything();
    vector<shared_ptr<IMazeEntity>> door;
    for (auto& one : everything)
    {
        auto ID = one->getEntityID();
        if (ID == Entity_ID::DOOR)
        {
            door.push_back(one);
        }
    }

    int doorSize = door.size();

    sf::Vector2f position2(78,66);

    auto check = 0;
    for (auto i =0; i< doorSize; i++)
    {
        if (door[i]->getPosition() == position2)
            check = 1;
    }

    CHECK(check == 1);
}

TEST_CASE("Check MazeManager Grid")
{
    MazeManager maze("original.txt", true, false);

    auto element1 = maze.returnGridEntity(2,52);

    CHECK_EQ(element1->getStatus() , STATUS::ACTIVE);
    CHECK_EQ(element1->getEntityID(), Entity_ID::KEY);
    CHECK_EQ(element1->getPosition(), sf::Vector2f(630,30));

    auto mazegrid = maze.ReturnMazeGrid();
    auto entity = mazegrid[2][52];
    CHECK_EQ(entity->getStatus() , STATUS::ACTIVE);
    CHECK_EQ(entity->getEntityID(), Entity_ID::KEY);
    CHECK_EQ(entity->getPosition(), sf::Vector2f(630,30));
}

TEST_CASE("MazeManager Grid & Dynamic Entities")
{
    MazeManager maze("original.txt", true, false);

    sf::Vector2u gridPos;
    auto Dentities = maze.packageDynamicElements();

    for (auto& entity : Dentities)
    {
        Entity_ID eID = entity->getEntityID();
        if (eID == Entity_ID::PACMAN)
        {
            gridPos = entity->gridPosition();
        }
    }

    auto element1 = maze.returnGridEntity(gridPos.x,gridPos.y+3);
    CHECK_EQ(element1->getEntityID(), Entity_ID::DOOR);
    CHECK_EQ(gridPos, sf::Vector2u(37,27));
}


TEST_CASE("Maze Manager creates the correct number of walls and paths objects")
{
    MazeManager maze("original.txt", true, false);

    auto dynamicE = maze.packageDynamicElements();
    auto everything = maze.packageEverything();
    vector<shared_ptr<IMazeEntity>> walls;
    vector<shared_ptr<IMazeEntity>> paths;
    vector<shared_ptr<IMazeEntity>> doors;
    vector<shared_ptr<IMazeEntity>> fruit;
    vector<shared_ptr<IMazeEntity>> keys;
    vector<shared_ptr<IMazeEntity>> super;
    vector<shared_ptr<IMazeEntity>> power;
    vector<shared_ptr<IMazeEntity>> ghosts;
    shared_ptr<IMazeEntity> pacman;
    for (auto& entity : dynamicE)
    {
        auto ID = entity->getEntityID();
        if (ID == Entity_ID::GHOST)
        {
            ghosts.push_back(entity);
        }
        else if (ID == Entity_ID::PACMAN)
        {
            pacman = entity;
        }
    }

    for (auto& one : everything)
    {
        auto ID = one->getEntityID();
        switch(ID)
        {
        case Entity_ID::DOOR:
            {
                doors.push_back(one);
                break;
            }
        case Entity_ID::FRUIT:
            {
                fruit.push_back(one);
                break;
            }
        case Entity_ID::GHOST:
            {
                ghosts.push_back(one);
                break;
            }
        case Entity_ID::KEY:
            {
                keys.push_back(one);
                break;
            }
        case PACMAN:
            {
                pacman = one;
                break;
            }
        case Entity_ID::PATH:
            {
                paths.push_back(one);
                break;
            }
        case POWER_PELLET:
            {
                power.push_back(one);
                break;
            }
        case SUPER_PELLET:
            {
                super.push_back(one);
                break;
            }

        case Entity_ID::WALL:
            {
                walls.push_back(one);
                break;
            }
        case Entity_ID::GHOST_DOOR: //not saved in packageElements, only saved in mazegrid
            break;
        }
    }

    //path size includes path objects for the spawn points of ghosts and pacman
    //CHECK(paths.size() == 2530); //! must change if the map is changed //not included in package everything
    CHECK(walls.size() == 607);
    CHECK(doors.size() == 111);
    CHECK(fruit.size() == 31);
    //CHECK(ghosts.size() == 4);
    CHECK(power.size() == 4);
    CHECK(super.size() == 2);
    CHECK(keys.size() == 15);
}

//! Include comprehensive package elements checks

TEST_CASE("Maze Manager: each ghost has a different Ghost_ID")
{
    auto maze = std::make_shared<MazeManager>("original.txt", true, false);
    auto dynamic =  maze->packageDynamicElements();
    for (int i = 0; i < static_cast<int>(dynamic.size()); i++)
    {
        if (dynamic[i]->getEntityID() == GHOST)
        {
            //always defined in such a way that the ghosts are added first and assigned their ID according to the same order
            CHECK_EQ(dynamic[i]->getGhostID(), Ghost_ID(i));
        }
    }
}

// ------------------------ UNLOCK DOOR MANAGER ---------------------------- //

TEST_CASE("Door objects are linked into groups of 3 to create a single door, when one object is set to inactive, all 3 are.")
{

    auto maze = std::make_shared<MazeManager>("original.txt", true, false);
    auto keyDoors = maze->packageKeysDoors();
    UnlockDoorManager testUnlock(keyDoors);
    int inactive_num =0;
    for (auto& entity :keyDoors)
    {
        if (entity->getStatus() == INACTIVE)
        {
            inactive_num++;
        }
    }
    CHECK_EQ(inactive_num,0);   //check that there are no inactive doors

    for (auto& entity : keyDoors)
    {
        if (entity->getEntityID() == DOOR)
        {
            entity->Delete(); //set one door object to inactive
            break;
        }
    }

    for (auto& entity :keyDoors)
    {
        if (entity->getEntityID() == DOOR)
        {
            if (entity->getStatus() == INACTIVE)
            {
                inactive_num++;
            }
        }
    }
    CHECK_EQ(inactive_num,1);

    testUnlock.updateDoors();
    inactive_num =0;
    for (auto& entity :keyDoors)
    {
        if (entity->getEntityID() == DOOR)
        {
            if (entity->getStatus() == INACTIVE)
            {
                inactive_num++;
            }
        }
    }

    CHECK_EQ(inactive_num,3);
}

TEST_CASE("Key unlocks multiple door objects in close proximity")
{
    auto maze = std::make_shared<MazeManager>("original.txt", true, false);
    auto keyDoors = maze->packageKeysDoors();
    UnlockDoorManager testUnlock(keyDoors);

    int inactive_num =0;
    for (auto& entity :keyDoors)
    {
        if (entity->getStatus() == INACTIVE)
        {
            inactive_num++;
        }
    }
    CHECK_EQ(inactive_num,0);   //check that there are no inactive objects

    for (auto& entity : keyDoors)
    {
        if (entity->getEntityID() == KEY) //set one key
        {
            entity->Delete(); //set one key object to inactive
            break;
        }
    }

    //check that the key has been deleted
    for (auto& entity :keyDoors)
    {
        if (entity->getEntityID() == KEY)
        {
            if (entity->getStatus() == INACTIVE)
            {
                inactive_num++;
            }
        }
    }
    CHECK_EQ(inactive_num,1);
    inactive_num =0;
    testUnlock.updateDoors();

    for (auto& entity :keyDoors)
    {
        if (entity->getEntityID() == DOOR)
        {
            if (entity->getStatus() == INACTIVE)
            {
                inactive_num++;
            }
        }
    }

    CHECK_EQ(inactive_num%3,0);
}

// ------------------------- EFFECTS MANAGER ------------------------------- //
TEST_CASE("Effects Manager sets and times the effect")
{
    MazeManager maze("original.txt", true, false);

    auto moving = maze.packageDynamicElements();
    std::vector<int> check1;

    //before the effect change
    std::vector<int> test1({0,0,0,0,0});
    for (auto& obj : moving)
    {
        check1.push_back(static_cast<int>(obj->getEffectStatus()));
    }
    CHECK(check1 == test1);

    EffectsManager effectManage;
    effectManage.setEffect(EffectStatus::POWER);
    effectManage.manageEffects(moving);

    std::vector<int> test2({2,2,2,2,2});
    CHECK(moving[0]->getEffectStatus() == EffectStatus::POWER);

    std::vector<int> check2;
    std::cout << "Waiting for 3 seconds to check the timer of the manageEffects"<<std::endl;
    this_thread::sleep_for(chrono::seconds(3));	// wait for 3 seconds - to add time
    effectManage.manageEffects(moving);
    for (auto& obj : moving)
    {
        check2.push_back(static_cast<int>(obj->getEffectStatus()));
    }

    CHECK(check2 == test2);

    std::cout << "Waiting a further 4 seconds, timer is set to elapse after 7 seconds"<<std::endl;
    this_thread::sleep_for(chrono::seconds(4));	// wait for 4 seconds - to add time

    effectManage.manageEffects(moving);

    std::vector<int> check3;
    for (auto& obj : moving)
    {
        check3.push_back(static_cast<int>(obj->getEffectStatus()));
    }
    CHECK(check3 == test1);
    CHECK(moving[0]->getEffectStatus() == EffectStatus::NORMAL);
}
// ------------------------- COLLISION MANAGER ----------------------------- //
TEST_CASE("Pacman Collides with fruit")
{
    auto maze = std::make_shared<MazeManager>("original.txt", true, false);
    CollisionManager collisions(maze, 1); // initialise with 1 life
    auto pacman = maze->returnPacman();
    pacman->setPosition(sf::Vector2f(90, 210));
    auto fruit = maze->returnGridEntity(17,7);
    CHECK_EQ(fruit->getStatus(),ACTIVE);
    collisions.ManageCollisions();
    CHECK_EQ(fruit->getStatus(),INACTIVE);

    CHECK_EQ(collisions.returnScore(),5);
}

TEST_CASE("Pacman Collides with SuperPellet")
{
    auto maze = std::make_shared<MazeManager>("original.txt", true, false);
    CollisionManager collisions(maze, 1); // initialise with 1 life
    auto pacman = maze->returnPacman();
    pacman->setPosition(sf::Vector2f(210, 450));
    auto pellet = maze->returnGridEntity(37,17);
    CHECK_EQ(pellet->getStatus(),ACTIVE);
    collisions.ManageCollisions();
    CHECK_EQ(pellet->getStatus(),INACTIVE);
    CHECK_EQ(pacman->getEffectStatus(), EffectStatus::SUPER);
    CHECK_EQ(collisions.returnScore(),20);
}

TEST_CASE("Pacman Collides with PowerPellet")
{
    auto maze = std::make_shared<MazeManager>("original.txt", true, false);
    CollisionManager collisions(maze, 1); // initialise with 1 life
    auto pacman = maze->returnPacman();
    pacman->setPosition(sf::Vector2f(90, 90));
    auto pellet = maze->returnGridEntity(7,7);
    CHECK_EQ(pellet->getStatus(),ACTIVE);
    collisions.ManageCollisions();
    CHECK_EQ(pellet->getStatus(),INACTIVE);
    CHECK_EQ(pacman->getEffectStatus(), EffectStatus::POWER);
    CHECK_EQ(collisions.returnScore(),15);
}

TEST_CASE("Pacman Collides with Ghost - NORMAL EFFECT")
{
    auto maze = std::make_shared<MazeManager>("original.txt", true, false);
    CollisionManager collisions(maze, 1); // initialise with 1 life
    auto pacman = maze->returnPacman();
    pacman->setPosition(sf::Vector2f(270, 270)); // setting to a ghost position
    CHECK_EQ(pacman->getPosition(),sf::Vector2f(270, 270));
    collisions.ManageCollisions();
    CHECK_FALSE(pacman->getPosition()==sf::Vector2f(270, 270));
    CHECK(collisions.returnLives() == 0);
    CHECK_EQ(pacman->getStatus(), TRANSITION);
}

TEST_CASE("Pacman Collides with Ghost - SUPER EFFECT")
{
    auto maze = std::make_shared<MazeManager>("original.txt", true, false);
    CollisionManager collisions(maze, 1); // initialise with 1 life
    auto pacman = maze->returnPacman();
    pacman->setPosition(sf::Vector2f(210, 450)); // setting to superPellet
    collisions.ManageCollisions();
    CHECK_EQ(pacman->getEffectStatus(), EffectStatus::SUPER);
    pacman->setPosition(sf::Vector2f(270, 270)); // setting to a ghost position
    CHECK_EQ(pacman->getPosition(),sf::Vector2f(270, 270));
    collisions.ManageCollisions();
    CHECK_EQ(pacman->getPosition(),sf::Vector2f(270, 270));
    CHECK(collisions.returnLives() == 1); // no change
}

TEST_CASE("Pacman Collides with Ghost - POWER EFFECT")
{
    auto maze = std::make_shared<MazeManager>("original.txt", true, false);
    CollisionManager collisions(maze, 1); // initialise with 1 life
    auto pacman = maze->returnPacman();
    pacman->setPosition(sf::Vector2f(90, 90)); // setting to powerPellet
    collisions.ManageCollisions();
    CHECK_EQ(pacman->getEffectStatus(), EffectStatus::POWER);
    pacman->setPosition(sf::Vector2f(270, 270)); // setting to a ghost position
    CHECK_EQ(pacman->getPosition(),sf::Vector2f(270, 270));
    collisions.ManageCollisions();
    CHECK_EQ(pacman->getPosition(),sf::Vector2f(270, 270));
    CHECK(collisions.returnLives() == 1); // no change
    CHECK_EQ(collisions.returnScore(),40);
    //ghost respawns too. - can check position, but from ghost tests, we know this is true
}

// ---------------------------- PATH HANDLER ------------------------------- //
TEST_CASE("Path Handler, pacman moves UP")
{
    auto maze = std::make_shared<MazeManager>("original.txt", true, false);
    PathHandler pathHandle(maze);


    sf::Vector2f PacPos, PacPos2;
    auto pacman = maze->returnPacman();
    pacman->setDesiredDirection(Direction::UP); //valid path for pacman

    PacPos = pacman->getPosition();
    std::cout << "Waiting for 1 second to check the time dependant movement of Pacman using PathHandler"<<std::endl;
    this_thread::sleep_for(chrono::seconds(1));	// wait for 3 seconds - to add time

    pathHandle.managePath(pacman);

    PacPos2 = pacman->getPosition();
    CHECK_FALSE(PacPos.y == PacPos2.y);
    CHECK(PacPos.x == PacPos2.x);
}

TEST_CASE("Path Handler, pacman moves DOWN")
{
    auto maze = std::make_shared<MazeManager>("original.txt", true, false);
    PathHandler pathHandle(maze);

    auto pacman = maze->returnPacman();
    sf::Vector2f PacPos, PacPos2;
    pacman->setDesiredDirection(Direction::DOWN);
    PacPos = pacman->getPosition();
    std::cout << "Waiting for 1 second to check the time dependant movement of Pacman using PathHandler"<<std::endl;
    this_thread::sleep_for(chrono::seconds(1));	// wait for 3 seconds - to add time
    pathHandle.managePath(pacman);
    PacPos2 = pacman->getPosition();

    CHECK_FALSE(PacPos.y == PacPos2.y);
    CHECK(PacPos.x == PacPos2.x);
}

TEST_CASE("Path Handler, pacman moves LEFT")
{
    auto maze = std::make_shared<MazeManager>("original.txt", true, false);
    PathHandler pathHandle(maze);

    auto pacman = maze->returnPacman();
    sf::Vector2f PacPos, PacPos2;
    pacman->setDesiredDirection(Direction::LEFT);
    PacPos = pacman->getPosition();
    std::cout << "Waiting for 0.1 seconds to check the time dependant movement of Pacman using PathHandler"<<std::endl;
    this_thread::sleep_for(chrono::milliseconds(100));	// wait for 100ms - to add time
    pathHandle.managePath(pacman);
    PacPos2 = pacman->getPosition();

    CHECK(PacPos.y == PacPos2.y);
    CHECK_FALSE(PacPos.x == PacPos2.x);

    pacman->setDesiredDirection(Direction::LEFT);
    std::cout << "Waiting for 0.1 seconds to check the time dependant movement of Pacman using PathHandler"<<std::endl;
    this_thread::sleep_for(chrono::milliseconds(100));	// wait for 100ms - to add time
    pathHandle.managePath(pacman);

    pacman->setDesiredDirection(Direction::LEFT);
    PacPos = pacman->getPosition();
    std::cout << "Waiting for 0.1 seconds to check the time dependant movement of Pacman using PathHandler"<<std::endl;
    this_thread::sleep_for(chrono::milliseconds(100));	// wait for 100ms - to add time
    pathHandle.managePath(pacman);
    PacPos2 = pacman->getPosition();
    CHECK_EQ(PacPos, PacPos2);
    CHECK(PacPos.x == PacPos2.x);
    CHECK(PacPos.y == PacPos2.y); //when distance c
}

TEST_CASE("Path Handler, pacman moves RIGHT") //pacman still moves
{
    auto maze = std::make_shared<MazeManager>("original.txt", true, false);
    PathHandler pathHandle(maze);

    auto pacman = maze->returnPacman();
    sf::Vector2f PacPos, PacPos2;
    pacman->setDesiredDirection(Direction::RIGHT);
    PacPos = pacman->getPosition();
    std::cout << "Waiting for 0.1 seconds to check the time dependant movement of Pacman using PathHandler"<<std::endl;
    this_thread::sleep_for(chrono::milliseconds(100));	// wait for 100ms - to add time
    pathHandle.managePath(pacman);
    PacPos2 = pacman->getPosition();

    CHECK_FALSE(PacPos.x == PacPos2.x);
    CHECK(PacPos.y == PacPos2.y);

    pacman->setDesiredDirection(Direction::RIGHT);
    std::cout << "Waiting for 0.1 seconds to check the time dependant movement of Pacman using PathHandler"<<std::endl;
    this_thread::sleep_for(chrono::milliseconds(100));	// wait for 100ms - to add time
    pathHandle.managePath(pacman);

    pacman->setDesiredDirection(Direction::RIGHT);
    PacPos = pacman->getPosition();
    std::cout << "Waiting for 0.1 seconds to check the time dependant movement of Pacman using PathHandler"<<std::endl;
    this_thread::sleep_for(chrono::milliseconds(100));	// wait for 100ms - to add time
    pathHandle.managePath(pacman);
    PacPos2 = pacman->getPosition();
    CHECK_EQ(PacPos, PacPos2);
    CHECK(PacPos.x == PacPos2.x);
    CHECK(PacPos.y == PacPos2.y); //when distance c
}


// ------------------------ GHOST MOVEMENT MANAGER ------------------------- //
TEST_CASE("ghost move manager")
{
    auto maze = std::make_shared<MazeManager>("original.txt", true, false);
    auto pathH = std::make_shared<PathHandler>(maze);
    //auto pacman = maze->returnPacman();
    auto moving = maze->packageDynamicElements();

    GhostMovementManager GhostMove(maze);

    //can use the following, this method will however take up a lot of code in order to differentiate between the 2 separate modes
    std::cout << "Waiting for 0.1 seconds to check the time dependant movement of Ghost using Ghost Movement Manager"<<std::endl;
    this_thread::sleep_for(chrono::milliseconds(100));	// wait for 3 seconds - to add time
    GhostMove.moveToValidPath(moving);
    for (auto& one : moving)
    {
        if (one->getEntityID() != PACMAN)
        {
            // check here each time
        }
    }
    //ghost moves to path depending on active game criteria, the effect status of
    // the entities as well as a timer for each individual ghost which determines when
    // the ghost left the ghost spawn box.

    //check timer
    /*difficult to analyse here, each individual object movement was tested
    the functions used here are fairly similar to the pathHandler
    */
    // in order to effectively test here, the test case would be significantly large as we would need
    // to make the program 'sleep' multiple times and call the moveToValidPath function after each 'sleep'

}


//* ------------------------ IDynamicMazeEntity --------------------------- *//
// ------------------------------ PACMAN ----------------------------------- //
TEST_CASE("Check Default Pacman construction")
{
    sf::Vector2f centerScreen(gameWidth/2, gameHeight/2);
    Pacman testPac(centerScreen);
    sf::Vector2f checkDefaultPosition = testPac.getPosition();

    CHECK(centerScreen == checkDefaultPosition);

    Entity_ID checkID = Entity_ID::PACMAN;
    CHECK_EQ(testPac.getEntityID(), checkID);

    STATUS checkSTATUS = STATUS::ACTIVE;
    CHECK_EQ(testPac.getStatus(), checkSTATUS);

    EffectStatus checkEffect = EffectStatus::NORMAL;
    CHECK_EQ(testPac.getEffectStatus(), checkEffect);

    CHECK_EQ(testPac.getOrientation(), Orientation::FACING_RIGHT);
}

TEST_CASE("Pacman can be 'deleted' (set to Transition)")
{
    sf::Vector2f centerScreen(gameWidth/2, gameHeight/2);
    Pacman testPac(centerScreen);
    testPac.Delete();
    CHECK_EQ(testPac.getStatus(), STATUS::TRANSITION);
}

TEST_CASE("Pacman can be respawned at spawnpoint")
{
    sf::Vector2f centerScreen(gameWidth/2, gameHeight/2);
    Pacman testPac(centerScreen);
    testPac.setPosition(sf::Vector2f(120,30));
    testPac.Delete();
    testPac.reSpawn();
    CHECK_EQ(testPac.getStatus(), STATUS::TRANSITION);
    CHECK_EQ(testPac.getPosition(), centerScreen);
}
TEST_CASE("Pacman can be 'reset' (set to ACTIVE)")
{
    sf::Vector2f centerScreen(gameWidth/2, gameHeight/2);
    Pacman testPac(centerScreen);
    testPac.Delete();
    testPac.reSpawn();
    testPac.Reset();
    CHECK_EQ(testPac.getStatus(), STATUS::ACTIVE);
}

TEST_CASE("Pacman's Orientation is changed when it moves")
{
    sf::Vector2f centerScreen(gameWidth/2, gameHeight/2);
    Pacman testPac(centerScreen);
    CHECK_EQ(testPac.getOrientation(), Orientation::FACING_RIGHT);

    double delta = 0.1;
    testPac.moveLeft(delta);
    CHECK_EQ(testPac.getOrientation(), Orientation::FACING_LEFT);

    testPac.moveUp(delta);
    CHECK_EQ(testPac.getOrientation(), Orientation::FACING_UP);

    testPac.moveDown(delta);
    CHECK_EQ(testPac.getOrientation(), Orientation::FACING_DOWN);

    testPac.moveRight(delta);
    CHECK_EQ(testPac.getOrientation(), Orientation::FACING_RIGHT);
}

TEST_CASE("Pacman Effect Status can be set and Retrieved")
{
    sf::Vector2f centerScreen(gameWidth/2, gameHeight/2);
    Pacman testPac(centerScreen);
    testPac.setEffectStatus(EffectStatus::POWER);
    CHECK_EQ(testPac.getEffectStatus(),EffectStatus::POWER);
}

TEST_CASE("Pacman can accurately set and get desired direction")
{
    sf::Vector2f centerScreen(gameWidth/2, gameHeight/2);
    Pacman testPac(centerScreen);
    testPac.setDesiredDirection(Direction::LEFT);
    CHECK_EQ(testPac.getDesiredDirection(),Direction::LEFT);
}


TEST_CASE("Pacman grid position changes when moved ")
{
    double delta = 0.1;
    sf::Vector2f position(330, 270);
    Pacman testPac(position);
    auto gridPos = testPac.gridPosition();
    CHECK_EQ(gridPos, sf::Vector2u(22,27));
    testPac.moveUp(delta); //moves 5 each time
    testPac.moveUp(delta);
    gridPos = testPac.gridPosition();
    CHECK_EQ(gridPos, sf::Vector2u(21,27));
}

TEST_CASE("Check Pacman move functionality")
{
    double delta = 0.1;
    sf::Vector2f centerScreen(gameWidth/2, gameHeight/2);
    Pacman testPac(centerScreen);
    sf::Vector2f checkDefaultPosition = testPac.getPosition();
    testPac.moveUp(delta);
    sf::Vector2f currentPosition = testPac.getPosition();
    CHECK_FALSE(checkDefaultPosition == currentPosition);

    sf::Vector2f newPos(checkDefaultPosition.x, checkDefaultPosition.y - 4.f);
    CHECK(currentPosition == newPos);
}

// pacman does not 'leave' the screen permanently, if he is able to move offscreen,
// he then appears on the other side to where he disappeared.
TEST_CASE("Check Pacman movement boundaries and move functionality")
{
    double delta = 0.1;
    sf::Vector2f centerScreen(gameWidth/2, gameHeight/2);
    Pacman testPac(centerScreen);
    testPac.setPosition(sf::Vector2f((gameWidth-6),(gameHeight-6)));
    testPac.moveRight(delta);

    sf::Vector2f currentPosition = testPac.getPosition();
    sf::Vector2f checkPosition(6.f, currentPosition.y);
    CHECK_EQ(currentPosition, checkPosition);

    testPac.moveDown(delta);
    currentPosition = testPac.getPosition();
    sf::Vector2f checkPosition2(6.f,6.f);
    CHECK_EQ(currentPosition, checkPosition2);

    testPac.moveUp(delta);
    currentPosition = testPac.getPosition();
    CHECK_EQ(currentPosition, sf::Vector2f(currentPosition.x, gameHeight-6));

    testPac.moveLeft(delta);
    currentPosition = testPac.getPosition();
    CHECK_EQ(currentPosition, sf::Vector2f(gameWidth-6, currentPosition.y));
}

// ----------------------------- GHOST ---------------------------------- //
TEST_CASE("Default Ghost construction")
{
    sf::Vector2f centerScreen(gameWidth/2, gameHeight/2);
    Ghost testGhost(centerScreen);
    sf::Vector2f checkDefaultPosition = testGhost.getPosition();

    CHECK(centerScreen == checkDefaultPosition);

    Entity_ID checkID = Entity_ID::GHOST;
    CHECK_EQ(testGhost.getEntityID(), checkID);

    STATUS checkSTATUS = STATUS::ACTIVE;
    CHECK_EQ(testGhost.getStatus(), checkSTATUS);

    EffectStatus checkEffect = EffectStatus::NORMAL;
    CHECK_EQ(testGhost.getEffectStatus(), checkEffect);

    CHECK_EQ(testGhost.getGhostID(),Ghost_ID::RED);
}

TEST_CASE("Ghost can be 'deleted' (set to Transition)")
{
    sf::Vector2f centerScreen(gameWidth/2, gameHeight/2);
    Ghost testGhost(centerScreen);
    testGhost.Delete();
    CHECK_EQ(testGhost.getStatus(), STATUS::TRANSITION);
}

TEST_CASE("Ghost can be respawned")
{
    sf::Vector2f centerScreen(gameWidth/2, gameHeight/2);
    Ghost testGhost(centerScreen);
    testGhost.setPosition(sf::Vector2f(120,30));
    testGhost.Delete();
    testGhost.reSpawn();
    CHECK_EQ(testGhost.getStatus(), STATUS::TRANSITION);
    CHECK_EQ(testGhost.getPosition(), centerScreen);
}

TEST_CASE("Ghost can be reset (set to ACTIVE)")
{
    sf::Vector2f centerScreen(gameWidth/2, gameHeight/2);
    Ghost testGhost(centerScreen);
    testGhost.Delete();
    testGhost.reSpawn();
    testGhost.Reset();
    CHECK_EQ(testGhost.getStatus(), STATUS::ACTIVE);
}

TEST_CASE("Ghost ID can be set and retrieved")
{
    sf::Vector2f centerScreen(gameWidth/2, gameHeight/2);
    Ghost testGhost(centerScreen);
    testGhost.setGhostID(Ghost_ID::BLUE);
    CHECK_EQ(testGhost.getGhostID(),Ghost_ID::BLUE);
}

TEST_CASE("Ghost Effect Status can be set and Retrieved")
{
    sf::Vector2f centerScreen(gameWidth/2, gameHeight/2);
    Ghost testGhost(centerScreen);
    testGhost.setEffectStatus(EffectStatus::POWER);
    CHECK_EQ(testGhost.getEffectStatus(),EffectStatus::POWER);
}

TEST_CASE("Ghost can accurately set and get desired direction")
{
    sf::Vector2f centerScreen(gameWidth/2, gameHeight/2);
    Ghost testGhost(centerScreen);
    testGhost.setDesiredDirection(Direction::LEFT);
    CHECK_EQ(testGhost.getDesiredDirection(),Direction::LEFT);
}

TEST_CASE("Ghost grid position changes when moved ")
{
    double delta = 0.1;
    sf::Vector2f position(330, 270);
    Ghost testGhost(position);
    auto gridPos = testGhost.gridPosition();
    CHECK_EQ(gridPos, sf::Vector2u(22,27));
    testGhost.moveUp(delta); //moves 5 each time
    testGhost.moveUp(delta);
    gridPos = testGhost.gridPosition();
    CHECK_EQ(gridPos, sf::Vector2u(21,27));
}

TEST_CASE("Check Ghost move functionality")
{
    double delta = 0.1;
    sf::Vector2f centerScreen(gameWidth/2, gameHeight/2);
    Ghost testGhost(centerScreen);
    sf::Vector2f checkDefaultPosition = testGhost.getPosition();
    testGhost.moveUp(delta);
    sf::Vector2f currentPosition = testGhost.getPosition();
    CHECK_FALSE(checkDefaultPosition == currentPosition);

    sf::Vector2f newPos(checkDefaultPosition.x, checkDefaultPosition.y - 3.5f);
    CHECK(currentPosition == newPos);
}

TEST_CASE("Check Ghost movement boundaries and move functionality")
{
    double delta = 0.1;
    sf::Vector2f centerScreen(gameWidth/2, gameHeight/2);
    Ghost testGhost(centerScreen);
    testGhost.setPosition(sf::Vector2f((gameWidth-6),(gameHeight-6)));
    testGhost.moveRight(delta);

    sf::Vector2f currentPosition = testGhost.getPosition();
    sf::Vector2f checkPosition(6.f, currentPosition.y);
    CHECK_EQ(currentPosition, checkPosition);

    testGhost.moveDown(delta);
    currentPosition = testGhost.getPosition();
    sf::Vector2f checkPosition2(6.f,6.f);
    CHECK_EQ(currentPosition, checkPosition2);

    testGhost.moveUp(delta);
    currentPosition = testGhost.getPosition();
    CHECK_EQ(currentPosition, sf::Vector2f(currentPosition.x, gameHeight-6));

    testGhost.moveLeft(delta);
    currentPosition = testGhost.getPosition();
    CHECK_EQ(currentPosition, sf::Vector2f(gameWidth-6, currentPosition.y));
}

//* ----------------------- IStaticMazeEntity --------------------------- *//
// ------------------------------ DOORS ---------------------------------- //
TEST_CASE("Door Default Construction")
{
    sf::Vector2f position(30,30);
    Doors testDoor(position);
    CHECK_EQ(position, testDoor.getPosition());

    CHECK_EQ(Entity_ID::DOOR, testDoor.getEntityID());
    CHECK_EQ(STATUS::ACTIVE, testDoor.getStatus());
}

TEST_CASE("Door can be deleted(set to INACTIVE)")
{
    sf::Vector2f position(30,30);
    Doors testDoor(position);
    CHECK_EQ(STATUS::ACTIVE, testDoor.getStatus());
    testDoor.Delete();
    CHECK_EQ(STATUS::INACTIVE, testDoor.getStatus());
}

TEST_CASE("Door returns correct Grid Position")
{
    sf::Vector2f position(30,30);
    Doors testDoor(position);
    sf::Vector2u gridPos(2,2);
    CHECK_EQ(gridPos, testDoor.gridPosition());
}

// ------------------------------ KEYS ---------------------------------- //
TEST_CASE("Key Default Construction")
{
    sf::Vector2f position(30,30);
    Keys testKey(position);
    CHECK_EQ(position, testKey.getPosition());

    CHECK_EQ(Entity_ID::KEY, testKey.getEntityID());
    CHECK_EQ(STATUS::ACTIVE, testKey.getStatus());
}

TEST_CASE("Key can be deleted(set to INACTIVE)")
{
    sf::Vector2f position(30,30);
    Keys testKey(position);
    CHECK_EQ(STATUS::ACTIVE, testKey.getStatus());
    testKey.Delete();
    CHECK_EQ(STATUS::INACTIVE, testKey.getStatus());
}

TEST_CASE("Key returns correct Grid Position")
{
    sf::Vector2f position(30,30);
    Keys testKey(position);
    sf::Vector2u gridPos(2,2);
    CHECK_EQ(gridPos, testKey.gridPosition());
}

// ----------------------------- FRUIT ---------------------------------- //
TEST_CASE("Fruit Default Construction")
{
    sf::Vector2f position(30,30);
    Fruit testFruit(position);
    CHECK_EQ(position, testFruit.getPosition());

    CHECK_EQ(Entity_ID::FRUIT, testFruit.getEntityID());
    CHECK_EQ(STATUS::ACTIVE, testFruit.getStatus());
}

TEST_CASE("Fruit can be deleted(set to INACTIVE)")
{
    sf::Vector2f position(30,30);
    Fruit testFruit(position);
    CHECK_EQ(STATUS::ACTIVE, testFruit.getStatus());
    testFruit.Delete();
    CHECK_EQ(STATUS::INACTIVE, testFruit.getStatus());
}

TEST_CASE("Fruit returns correct Grid Position")
{
    sf::Vector2f position(30,30);
    Fruit testFruit(position);
    sf::Vector2u gridPos(2,2);
    CHECK_EQ(gridPos, testFruit.gridPosition());
}

// -------------------------- SUPERPELLETS ------------------------------ //
TEST_CASE("SuperPellet Default Construction")
{
    sf::Vector2f position(30,30);
    SuperPellet testSuperPellet(position);
    CHECK_EQ(position, testSuperPellet.getPosition());

    CHECK_EQ(Entity_ID::SUPER_PELLET, testSuperPellet.getEntityID());
    CHECK_EQ(STATUS::ACTIVE, testSuperPellet.getStatus());
}

TEST_CASE("SuperPellet can be deleted(set to INACTIVE)")
{
    sf::Vector2f position(30,30);
    SuperPellet testSuperPellet(position);
    CHECK_EQ(STATUS::ACTIVE, testSuperPellet.getStatus());
    testSuperPellet.Delete();
    CHECK_EQ(STATUS::INACTIVE, testSuperPellet.getStatus());
}

TEST_CASE("SuperPellet returns correct Grid Position")
{
    sf::Vector2f position(30,30);
    SuperPellet testSuperPellet(position);
    sf::Vector2u gridPos(2,2);
    CHECK_EQ(gridPos, testSuperPellet.gridPosition());
}


// -------------------------- POWERPELLETS ------------------------------ //
TEST_CASE("SuperPellet Default Construction")
{
    sf::Vector2f position(30,30);
    PowerPellet testPowerPellet(position);
    CHECK_EQ(position, testPowerPellet.getPosition());

    CHECK_EQ(Entity_ID::POWER_PELLET, testPowerPellet.getEntityID());
    CHECK_EQ(STATUS::ACTIVE, testPowerPellet.getStatus());
}

TEST_CASE("SuperPellet can be deleted(set to INACTIVE)")
{
    sf::Vector2f position(30,30);
    PowerPellet testPowerPellet(position);
    CHECK_EQ(STATUS::ACTIVE, testPowerPellet.getStatus());
    testPowerPellet.Delete();
    CHECK_EQ(STATUS::INACTIVE, testPowerPellet.getStatus());
}

TEST_CASE("SuperPellet returns correct Grid Position")
{
    sf::Vector2f position(30,30);
    PowerPellet testPowerPellet(position);
    sf::Vector2u gridPos(2,2);
    CHECK_EQ(gridPos, testPowerPellet.gridPosition());
}

//* -------------------------- IMazeEntity ----------------------------- *//
// ----------------------------- PATH ----------------------------------- //
TEST_CASE("Path Default Construction")
{
    sf::Vector2f position(30,30);
    Path testPath(position);
    CHECK_EQ(position, testPath.getPosition());

    CHECK_EQ(Entity_ID::PATH, testPath.getEntityID());
    CHECK_EQ(STATUS::ACTIVE, testPath.getStatus());
}

TEST_CASE("Path delete does nothing")
{
    sf::Vector2f position(30,30);
    Path testPath(position);
    CHECK_EQ(STATUS::ACTIVE, testPath.getStatus());
    testPath.Delete();
    CHECK_EQ(STATUS::ACTIVE, testPath.getStatus());
}

// ----------------------------- WALLS ---------------------------------- //
TEST_CASE("Wall Default Construction")
{
    sf::Vector2f position(30,30);
    Wall testWall(position);
    CHECK_EQ(position, testWall.getPosition());

    CHECK_EQ(Entity_ID::WALL, testWall.getEntityID());
    CHECK_EQ(STATUS::ACTIVE, testWall.getStatus());
}

TEST_CASE("Wall delete does nothing")
{
    sf::Vector2f position(30,30);
    Wall testWall(position);
    CHECK_EQ(STATUS::ACTIVE, testWall.getStatus());
    testWall.Delete();
    CHECK_EQ(STATUS::ACTIVE, testWall.getStatus());
}

// -------------------------- GHOST-DOOR ------------------------------- //
TEST_CASE("GhostDoor Default Construction")
{
    sf::Vector2f position(30,30);
    GhostDoor testGhostDoor(position);
    CHECK_EQ(position, testGhostDoor.getPosition());

    CHECK_EQ(Entity_ID::GHOST_DOOR, testGhostDoor.getEntityID());
    CHECK_EQ(STATUS::ACTIVE, testGhostDoor.getStatus());
}

TEST_CASE("GhostDoor delete does nothing")
{
    sf::Vector2f position(30,30);
    GhostDoor testGhostDoor(position);
    CHECK_EQ(STATUS::ACTIVE, testGhostDoor.getStatus());
    testGhostDoor.Delete();
    CHECK_EQ(STATUS::ACTIVE, testGhostDoor.getStatus());
}
