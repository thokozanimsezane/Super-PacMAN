#ifndef MAPEDITOR_H_INCLUDED
#define MAPEDITOR_H_INCLUDED

#include "Common.h"
#include "IGameScreen.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "EditorLogic.h"

/** \class MapEditor
 *  \brief This class is responsible for the Map Editor Game Screen, and displays the logic from the Editor Logic Class.
 *  It uses the mapStatus return from the Editor Logic class to determine which state to display.
 *  The first presentation part of this class is responsible for displaying the map file options to the
 *  user and determining the user's choice (selected name, NEW, EDIT, set as default, EXIT). If the user choice is:
 *      'NEW', then a blank map is generated for the user to create.
 *      'EDIT', then it uses the selected filename to populate the screen with the respective entities.
 *      'set as default', then the selected filename is chosen as the default map to load the playscreen, for this
 *          game instance.
 *      'EXIT', then the screen exits to the main menu.
 *  If 'NEW' or 'EDIT' are selected, then this class is responsible for displaying the entity options as well as the
 *  maze relating to the chosen filename (or blank if new), it further displays the selected entity name and each
 *  new entity as they are placed in the maze.
 *  This class is responsible for changing the input type from map to TEXT when the mapStatus changes to SaveInput.
 *  This class uses the SFML Graphics Library to draw the objects to the screen. This screen also displays the options to
 *  either save the new map, or exit to the main menu.
 */

class MapEditor : public IGameScreen
{
public:
    /** \brief Parameterized constructor. Creates a MapEditor object.
     *  \param defaultMap of type const std::string
     */
    MapEditor(const std::string defaultMap);

    /** \brief Loads the required images, fonts and static sprites (for the options menu) required for use in the MapEditor,
     *  depends on the current status of the map editor as described in the class description.
     */
    virtual void LoadContent();

    /** \brief Removes the screen-specific content.
     *  Removes data/content that is no longer required.
     */
    virtual void RemoveContent();

    /** \brief A virtual function that is used for updating the MapEditor screen contents, depends on the current status of the mapEditor
     *  \param sf::RenderWindow - A RenderTarget object defined in SFML, used as the target to draw objects to the window buffer to be displayed later.
     *  \param sf::Event - An SFML event object which is used in conjunction with the user-input to determine if a selection has been been made/changed.
     */
    virtual void Update(sf::RenderWindow& _window, sf::Event& _event);

    /** \brief A virtual function that draws the contents of the buffer (determined by the Update function and the status of the map editor) onto the screen
     *  \param sf::RenderWindow - A RenderTarget object defined in SFML.
     */
    virtual void Draw(sf::RenderWindow& _window);

    /** \brief This function returns the game progress (in this case either: level complete/ level incomplete)
     *  \return Game_Status an enumeration defined in Common.h
     */
    virtual Game_Status returnGameProgress() override;

    /** \brief This function returns the chosen map filename, if 'set as default' option is selected then the returned filename
     *  is the chosen map filename. otherwise it is the previously defined map filename, (if not set previously in the game instance, this
     *  is the original map filename).
     *  \return defaultName, of type string.
     */
    virtual std::string returnMapName() override;

private:

    /** \brief This function is responsible for creating all the new maze entity sprites while in the map editor mode.
    */
    void createSprites();

    /** \brief This function is responsible for setting the private variable _mapFileName, to the given filename. To be used in the
     *  editor portion of this screen.
     *  \param filename is of type string.
     */
    void setMapFilename(const std::string filename);

    /** \brief This function is responsible for creating all the options sprites while in the map editor mode.
    */
    void loadoptionSprites();

    std::vector<std::shared_ptr<sf::Sprite>> loadSprites(std::vector<std::vector<std::shared_ptr<IMazeEntity>>> optionObjects);
    std::vector<std::shared_ptr<sf::Sprite>> loadSprites(std::vector<std::shared_ptr<IMazeEntity>> optionObjects);

    EditorLogic _eLogic;
    mapStatus _mapStat;
    std::vector<sf::Text> writeText;

    std::vector<std::shared_ptr<sf::Sprite>> _entitySprites;
    std::vector<std::shared_ptr<sf::Sprite>> _optionSprites;
    std::vector<std::vector<std::shared_ptr<IMazeEntity>>> _mazeGrid;
    std::vector<std::vector<std::shared_ptr<IMazeEntity>>> _optionGrid;

    std::string _mapFileName;
    std::shared_ptr<InputManager> _input;

    std::map<TextureID, sf::Texture> mapEntityTex;
    Game_Status _status;
    std::string defaultName;

};
#endif // MAPEDITOR_H_INCLUDED
