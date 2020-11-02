#ifndef FILEMANAGER_H_INCLUDED
#define FILEMANAGER_H_INCLUDED

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include "Common.h"

/** \class FileManager
 *  \brief This is a FileManager Class that reads in the map and highscores.
 *  The class is also responsible for saving highsores by writing them into a txt file.
 * 	This class is also responsible for writing a map to a file.
 *  \author 719597 Tarryn Maggs and 1033379 Thokozani Msezane.
 *  \version 3.0
 */

class FileManager
{
public:

    /** \brief Default Constructor. Creates a FileManager object.
     */
    FileManager();

    /** \brief Default Destructor. Destroys a FileManager object.
     */
    ~FileManager();

    /** \brief Reads in the array of numbers indicating the format of the maze
     *  \param mapName is the name of the actual map file and is of type string
     */
    void readMapFile(const std::string mapName);

	/** \brief Returns the map created in 'readMapFile'.
     *  \return array of int
     */
    int * returnMap();

	/** \brief Writes the map to a text file specified by the string 'filename'
	 *	\param filename is of type string
	 *	\param IDs is a vector of vectors of integers, representing the 2D grid
	 * 	of the maze objects. The integers represent the static_cast of the entity ID.
	 */
    void writeMap(const std::string filename, std::vector<std::vector<int>> IDs);

    /** \brief Returns the name and score of the player with the highest score (Score is obtained by pacman eating the fruit and ghosts)
     *  \return HighScore is a struct defined in Common.h
     */
    HighScore returnHighScore();

    /** \brief Reads all game highscores from the text file, "HighScores.txt" and saves the results to a private member function as a vector of the struct HighScore.
     */
    void readAllHighScores();

    /** \brief Returns all of the High scores in the game retrieved from the function readAllHighScores.
     *  \return Vector of type HighScore, _highScores
     */
    std::vector<HighScore> returnAllHighScores();

    /** \brief Manages the game highscores, called after saveNewScore. readjusts and rewrites "HighScores.txt".
		This function organises the vector of high scores so that there are a maximum of 10 high scores saved,
		orders the highscores in descending order, and rewrites these HighScores to "HighScores.txt".
     */
    void manageHighScores();

    /** \brief Used to save a new high score. pushes the given highscore to the vector stored by the class.
		Manually called if findNewScore returns true.
     *  \param hScore is of type HighScore
     */
    void saveNewScore(HighScore hScore);

    /** \brief Determines if the input is a new highscore. Function returns true if the given highscore, hScore, is greater than any
		HighScore contained in the _highScores vector created in readAllHighScores.
	 *  \param hScore is of type HighScore
     *  \return bool
     */
    bool findNewScore(HighScore hScore);


	/** \brief Reads all map names from the text file found with path "maps/mapNames.txt", and saves the results to a private member function as a vector of strings.
     */
	void readMapNames();

	/** \brief Returns all of the map names retrieved from the function readMapNames.
     *  \return Vector of strings
     */
    std::vector<std::string> returnMapNames();

	/** \brief Adds a filename specified by the string 'name' to the text file "maps/mapNames.txt".
     *  \param name is of type string
     */
    void writeMapName(std::string name);




private:
    int* _tiles;
    int _highscore;
    std::vector<HighScore> _highScores;
	std::vector<std::string> _mapNames;
};

#endif // FILEMANAGER_H_INCLUDED
