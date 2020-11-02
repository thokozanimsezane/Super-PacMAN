#ifndef EDITORLOGIC_H_INCLUDED
#define EDITORLOGIC_H_INCLUDED

#include "Common.h"
#include "FileManager.h"
#include "IMazeEntity.h"

#include <string>
#include <iostream>

/** \class EditorLogic
 *  \brief This class is responsible for the Map Editor Logic.
 *  The first presentation part of this class is responsible for creating the map editor logic that displays the map file options to the
 *  user. It further interprets the user input (selected name, NEW, EDIT, set as default, EXIT). If the user choice is:
 *      'NEW', then a blank map is generated for the user to create.
 *      'EDIT', then it uses the selected filename to populate the screen with the respective entities.
 *      'set as default', then the selected filename is chosen as the default map to load the playscreen, for this
 *          game instance.
 *      'EXIT', then the screen exits to the main menu.
 *  If 'NEW' or 'EDIT' are selected, then this class is responsible for creating the entity options as well as creating the
 *  maze relating to the chosen filename (or blank if new), and creates the new objects as they are placed in the game.
 *  It further manages the user input and highlights the user's option selection.
 *  It uses the MazeManager class to populate the grid that is used.
 *  This screen also manages the user choice to save or exit the map editor. If save is selected, the function checkMap
 *  is called to ensure that the map created is valid according to certain criteria. If the save criteria is successful
 *  then the map logic is changed to textInput, and manages the users text input and saves the new map file.
 */

class EditorLogic
{
public:
    /** \brief Parameterized constructor. Creates a EditorLogic object.
     *  \param filename of type const std::string
     */
    EditorLogic(const std::string filename);

    /** \brief This function is responsible for sending the EditorLogic mapStatus to the presentation layer.
     *  \return mapStatus enum.
     */
    mapStatus returnMapStatus();

    /** \brief  This function is responsible for managing and interpreting the user input when in the 'choice' mapStatus
     *  or in the Designer mapStatus.
     *  \param leftClick of type bool. Determines if a left click has occurred.
     *  \param mouseIN of type sf::Vector2f. returns the mouse position.
     */
    void InterpretMapInput(bool leftClick, sf::Vector2f mouseIn);

    /** \brief  This function is responsible for managing and interpreting the user input when in the 'SaveInput' mapStatus.
     *  \param leftClick of type bool. Determines if a left click has occurred.
     *  \param mouseIN of type sf::Vector2f. returns the mouse position.
     *  \param textIN of type sf::String. Returns the user text input
     */
    void InterpretTextInput(bool leftClick, sf::Vector2f mouseIn, sf::String textIN);

    /** \brief This function is responsible for loading the text used in the 'Choices' screen of the editor Logic.
    */
    void loadChoices();

    /** \brief This function is used when the mapStatus is 'Designer', it is responsible for loading the maze according
     *  to the respective filename as well as the options objects and text.
     */
    void loadDesigner();

    /** \brief This function is responsible for loading the data used in the 'SaveInput' screen of the editor Logic.
     */
    void loadTextMode();

    /** \brief This function is responsible for highlighting the user selection (Either the map name
     *  -if mapChoice is true else the option maze entity)
     *  \param mapChoice of type bool.
     */
    void highlightSelection(bool mapChoice);

    /** \brief This function is responsible for managing the map editor when the mapStatus is set to 'Choices'.
     */
    void chooseMap();

    /** \brief This function is responsible for managing the map editor when the mapStatus is set to 'Designer'.
     */
    void Designer();

    /** \brief This function is responsible for managing the map editor when the mapStatus is set to 'SaveInput'.
     */
    void TextInputMode();

    /** \brief This function returns the chosen map filename, if 'set as default' option is selected then the returned filename
     *  is the chosen map filename. otherwise it is the previously defined map filename, (if not set previously in the game instance, this
     *  is the original map filename).
     *  \return defaultName, of type string.
     */
    std::string returnMapName();

    /** \brief This function returns the game progress (in this case either: level complete/ level incomplete)
     *  \return Game_Status an enumeration defined in Common.h
     */
    Game_Status returnGameProgress();

    /** \brief This function is responsible for packaging all sf::Text objects to be sent to the presentation layer to be displayed.
     *  \return vector of sf::Text objects.
     */
    std::vector<sf::Text> returnText();

    /** \brief This function is responsible for packaging the maze entity objects to be sent to the presentation layer to be displayed.
     *  \return vector of vectors of shared pointers to an IMazeEntity objects.
     */
    std::vector<std::vector<std::shared_ptr<IMazeEntity>>> returnMaze();

    /** \brief This function is responsible for packaging the option entity objects to be sent to the presentation layer to be displayed.
     *  \return vector of vectors of shared pointers to an IMazeEntity objects.
     */
    std::vector<std::vector<std::shared_ptr<IMazeEntity>>> returnOptionGrid();

private:

    /** \brief This function is responsible for setting the private variable _mapFileName, to the given filename. To be used in the
     *  editor portion of this screen.
     *  \param filename is of type string.
     */
    void setMapFilename(const std::string filename);

    /** \brief This function is responsible for loading the map according to the given filename.
     *  \param filename is of type string.
     */
    void loadMap(const std::string filename);

    /** \brief This function is responsible for loading all the options objects, and saving each to a respective
     *  vector to be diplayed later.
     */
    void loadOptions();

    /** \brief This function updates the option grid so that the clickable area of the entity is increased.
     */
    void updateOptionGrid();

    /** \brief This function is responsible for updating the maze 2D vector. It is called when a left mouse click occurs
     *  in the maze grid and places a new entity in the grid position corresponding to the mouse click.
     */
    void updateMap();

    /** \brief This function is called before the map can be saved and determines whether the created map fits certain criteria.
     *  \return bool. returns true if all criteria are met and false otherwise.
     */
    bool checkMap();

    /** \brief This function is responsible for creating the vector of vectors of the enum EntityID, which is used by a FileManager to
     *  create the new map/maze.
     */
    void createIDvector();
    sf::Vector2u gridPosition(sf::Vector2f position);

    // member variables used for all/most
    std::string _mapFileName;
    mapStatus _mapStatus;
    Game_Status _status;

    std::string defaultName;

    bool _select; //set to true when a left mouse click occurs
    sf::Vector2f mousePos;
    sf::Font font;
    std::vector<sf::Text> _options; //highlightable text
    std::vector<sf::Text> ChoiceInstructions; // clickable text. constant - maybe create a single vector that changes depending on the screen
    std::vector<sf::Text> nonClickText;

    // member variables for choosing map screen
    std::string mapChoiceName;

    // member variables for design map screen
    std::vector<std::shared_ptr<IMazeEntity>> optionObjects;
    std::vector<std::vector<std::shared_ptr<IMazeEntity>>> _optionGrid;
    std::vector<std::vector<std::shared_ptr<IMazeEntity>>> _optionGridp; //sent for display - unaltered
    std::vector<std::vector<std::shared_ptr<IMazeEntity>>> _mazeGrid;
    std::vector<std::vector<int>> _IDGrid;
    std::shared_ptr<IMazeEntity> _entity; // used to indicate which option entity has been selected

    // member variables for input text screen
    sf::String TextCheck;
    sf::Text _TextInput;

};

#endif // EDITORLOGIC_H_INCLUDED
