#ifndef LOGICPRESENTER_H_INCLUDED
#define LOGICPRESENTER_H_INCLUDED

#include "GameLogic.h"

/** \class LogicPresenter
 *  \brief A Logic layer class which is responsible for providing a bridge between the logic and presentation
 *  layers of the game.
 *  \author 719597 Tarryn Maggs and 1033379 Thokozani Msezane.
 *  \version 3.0
 */
//future versions can expand on this and base this class off an abstract presentation class. the abstract base class would form the basis for the interface between logic and presentation layers.
class LogicPresenter // :public IPresentation
{
public:
    /** \brief Parameterized Constructor. Constructs a LogicPresenter object.
     *  \param Lives is of type int, it contains the number of lives of pacman.
	 *  \param filename is of type string, it contains the filepath for the map file.
     */
    LogicPresenter(int Lives, std::string filename);

     /** \brief Default Destructor. Destroys a LogicPresenter object.
      */
    ~LogicPresenter();

    /** \brief This function is responsible for asking the gameLogic to run the game logic processes.
     */
    void PacMaze();


    /** \brief This function is responsible for sending the userInput retrieved from the presentation layer
     *  to the logic layer, GameLogic.
     *  \param _input is of type UserInput an enumeration defined in Common.h
     */
    void sendUserInput(UserInput _input);

    /** \brief This function stores all maze entities into a single returnable vector
     *  \return a vector of shared pointers of type IMazeEnitity.
     */
    std::vector<std::shared_ptr<IMazeEntity>>& PackageEverything();

    /** \brief This function stores all maze dynamic maze entities into a single returnable vector
     *  \return a vector of shared pointers of type IDynamicMazeEnitity.
     */
    std::vector<std::shared_ptr<IDynamicMazeEntity>>& PackageDynamic();

    /** \brief  Returns the score pacman has obtained from eating certain maze elements, retrieved from the game logic
     *  \return int.
     */
    int returnScore();

    /** \brief This function returns the number of lives pacman has left, retrieved from the game logic .
     *  \return int.
     */
    int returnLives();

    /** \brief This function returns the game progress (game complete/ game incomplete/ game won / game over),
     *  retrieved from the game logic.
     *  \return Game_Status an enumeration type defined in Common.h
     */
    Game_Status returnGameProgress();

private:
    GameLogic _GameLogic;

};

#endif // LOGICPRESENTER_H_INCLUDED
