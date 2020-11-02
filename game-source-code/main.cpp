#include "Common.h"

#include "GameApplication.h"

/** \mainpage Super Pacman Game
 *  This project was aimed at the development of a SuperPacMan game based on the original pacman game, and the Super Pacman version of the original.
 *  It was required that the game be coded in modern C++17 as the chosen standard for compilation and with the SFML version 2.5.1 graphics library
 *  The game has the following features:
 *  - The game consists of a maze, with maze elements including: walls, doors, keys, pacman, ghosts, super pellets and
 *    power pellets.(there are 'ghost' entities such as ghostDoors and paths, which are used in collision and path management, but cannot be 'seen' by
 *                   the player)
 *  - Each key is assigned to a door(s) which open when pacman eats the key.
 *  - Each dynamic entity moves according to the velocity equation, which means that it should move at the same speed regardless of the computer the game is being played on.
 *  - Pacman can be moved up, down, left or right within the maze and cannot move through locked doors.
 *      Pacman can die when he collides with a ghost.
 *      When pacman eats a power pellet the ghosts turn blue and he can eat them.
 *      When he easts a super pellet he (approximately) triples in size and can eat through unlocked doors his speed also increases, (These effects last for a short time).
 *  - The are 4 ghosts which chase pacman. They can kill pacman when they collide with pacman - the result is changed/determined by the below.
 *      When pacman eats a power pellet the ghosts can be eaten and upon being eaten, they respawn in the ghost house.
 *      When pacman eats a super pellet the ghosts appear flattened and cannot kill or be killed by pacman on collision (unless pacman eats a power-pellet shortly before the collision).
 *  - There a five different levels to the game. The game is won when pacman has eaten all the fruits in all 5 levels
 *  - Pacman has 3 lives and the game is lost when pacman has died three times (has no lives left).
 *  - The game has a Main menu where the player can either choose to PLAY the game, view the HIGHSCORES, enter the MAP EDITOR, or QUIT the game.
 *  - The game saves and display the top 10 highscores and the names of the people who set them. this is viewed in the HIGHSCORES screen of the main menu.
 *  - The game has an interactive map editor which allows the player to choose from a list of map names to either create a NEW map (blank map with no entities), EDIT an existing
 *      chosen map, set a chosen map as the DEFAULT map for gameplay or EXIT to the main menu.
 */

 /** \fn int main()
 *  \brief This function runs the whole game.
 *
 *  \return The application exit code: 0 for successful completion; a negative number to indicate an error
 *
 */

int main()
{
   GameApplication Pacman;
   Pacman.StartGame();

return EXIT_SUCCESS;
}


