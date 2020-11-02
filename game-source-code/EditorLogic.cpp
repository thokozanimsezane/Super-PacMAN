#include "EditorLogic.h"

#include "MazeManager.h"

/* There are 4 screen states to this class.
    0.1.Screen explaining how to navigate through the map editor, click to remove and continue
    1.  Choose if you want to create a new map, edit an existing map or set an existing map as the default
    2.  Design your map
        - when save selected
    3.1 Display problems with the map, click to remove and continue
    3.2 Display text and input filename;
    */


EditorLogic::EditorLogic(const std::string defaultMap)
{
    //load first screen content
    font.loadFromFile("sansation.ttf");
    _select = false;
    _status = LEVEL_INCOMPLETE;
    std::vector<std::vector<int>> IDGrid(60, std::vector<int>(55,0));
    _IDGrid = IDGrid; //empty
    _mapStatus = mapStatus::Choices;

    setMapFilename(defaultMap);//set default
    defaultName = defaultMap;

}

mapStatus EditorLogic::returnMapStatus()
{
    return _mapStatus;
}



void EditorLogic::InterpretMapInput(bool leftClick, sf::Vector2f mouseIn)//(std::pair<bool, sf::Vector2f> mouseInput)
{
    if (leftClick)//if (mouseInput.first)
    {
        mousePos = mouseIn; //mouseInput.second;
        _select = true;
    }
    else
        _select = false;
}

void EditorLogic::InterpretTextInput(bool leftClick, sf::Vector2f mouseIn, sf::String textIN)
{
        TextCheck = textIN;
    if (leftClick)//if (mouseInput.first)
    {
        mousePos = mouseIn; //mouseInput.second;
        _select = true;
    }
    else
        _select = false;
}

/*void EditorLogic::runLogic()
{       //indented are overlays

    //use map status enum to determine which to run
        displayInstructions(); //display instructions of how to operate the map editor
    chooseMap();            // choose which map you would like to use etc
    designMap();            // design the map
        displayMapErrors();
        displayTextInput();
}*/

void EditorLogic::loadChoices()
{
    ChoiceInstructions.clear();
    //! LOAD CONTENT PORTION
if (_mapStatus == mapStatus::Choices)
    {
        _options.clear();
        //load all map files available - done by reading names from a file, whenever a map is created its name is saved to a text file
        FileManager _file;
        _file.readMapNames();

        auto names = _file.returnMapNames();
        for (int i = 0; i < static_cast<int>(names.size()); i++)
        {
            sf::Text name;
            name.setString(names[i]);
            name.setFont(font);
            name.setCharacterSize(25);
            name.setFillColor(sf::Color::White);
            if (i <= 10)
                name.setPosition(100, 24+i*60);
            if (i <= 20 && i >10)
                name.setPosition(265, 24+(i-10)*60);
            if (i <= 30 && i >20)
                name.setPosition(430, 24+(i-20)*60);

            _options.push_back(name);
        }

        // "New" - creates blank map Text
        // "Edit" - creates map based off old map
        // "Set as Default" - sets the chosen map to default -> sets level to complete
        //      -> return mapfilename, save into gamestatemanager
        //create a map which contains all sf::Text linked to a string describing what the vector is
        sf::Text NEW, EDIT, DEFAULT, QuitText;
        std::string txt = "NEW";
        NEW.setString(txt);
        NEW.setFont(font);
        NEW.setCharacterSize(25);
        NEW.setFillColor(sf::Color::White);
        NEW.setPosition(gameWidth+100, 360);
        ChoiceInstructions.push_back(NEW);

        txt = "EDIT";
        EDIT.setString(txt);
        EDIT.setFont(font);
        EDIT.setCharacterSize(25);
        EDIT.setFillColor(sf::Color::White);
        EDIT.setPosition(gameWidth+100, 460);
        ChoiceInstructions.push_back(EDIT);

        txt = "SET AS \n DEFAULT";
        DEFAULT.setString(txt);
        DEFAULT.setFont(font);
        DEFAULT.setCharacterSize(25);
        DEFAULT.setFillColor(sf::Color::White);
        DEFAULT.setPosition(gameWidth+100, 560);
        ChoiceInstructions.push_back(DEFAULT);

        txt = "EXIT";
        QuitText.setString(txt);
        QuitText.setFont(font);
        QuitText.setCharacterSize(25);
        QuitText.setFillColor(sf::Color::White);
        QuitText.setPosition(gameWidth+100, 660);
        ChoiceInstructions.push_back(QuitText);
    }
}


void EditorLogic::chooseMap()
{
    auto NEWbound = ChoiceInstructions[0].getGlobalBounds(); // sf::Text boundaries
    auto EDITbound = ChoiceInstructions[1].getGlobalBounds();
    auto DEFAULTbound = ChoiceInstructions[2].getGlobalBounds();
    auto quitBound = ChoiceInstructions[3].getGlobalBounds();

    if (_select)
    {
        if(NEWbound.contains(mousePos))
        {
            setMapFilename(""); //set mapfile name to empty
            _mapStatus = mapStatus::Designer;
            loadDesigner();
        }
        if(EDITbound.contains(mousePos))
        {
                //retrieve last selected text
            std::string newName = "maps/" + mapChoiceName;
            setMapFilename(newName);
            _mapStatus = mapStatus::Designer;
            loadDesigner();
        }
        if(DEFAULTbound.contains(mousePos))
        {
            //set selection as default
            defaultName = "maps/" + mapChoiceName; //return map file name and save returned as deafult
            //std::cout << defaultName <<std::endl;
            //exit screen
            _status = LEVEL_COMPLETE;
        }
        if(quitBound.contains(mousePos)) // if the mouse is located within the text boundaries
            _status = LEVEL_COMPLETE;

        for (auto& mapFile : _options)
        {
            auto tempBound = mapFile.getGlobalBounds();
            if (tempBound.contains(mousePos))
            {
                mapChoiceName = mapFile.getString();
                highlightSelection(true);
            }
        }
        _select = false;
    }
}

//! display choice screen
//! UPDATE PORTION

std::vector<sf::Text> EditorLogic::returnText() //not displaying text correctly in desginer (missing choice instructions
{    std::vector<sf::Text> allText;
    for (auto& choice : ChoiceInstructions)
    {
        allText.push_back(choice);
    }
    for (auto& option : _options)
    {
        allText.push_back(option);
    }
    for (auto& noClick : nonClickText)
    {
        allText.push_back(noClick);
    }


    if( _mapStatus == SaveInput)
    {
        _TextInput.setCharacterSize(25);
    _TextInput.setFillColor(sf::Color(128,128,128));
    _TextInput.setPosition(225, 385);

    std::string txt = "Please enter a filename for your new map: ";
    sf::Text _fileName(txt,font);
    _fileName.setCharacterSize(25);
    _fileName.setFillColor(sf::Color::White);
    _fileName.setPosition(225, 360);
    allText.push_back(_fileName);

    sf::Text text("SAVE", font);
    text.setCharacterSize(25);
    text.setFillColor(sf::Color::White);
    text.setPosition(gameWidth+100, 624);
    allText.push_back(text);

    sf::Text QuitText;
    std::string str = "EXIT";
    QuitText.setString(str);
    QuitText.setFont(font);
    QuitText.setCharacterSize(25);
    QuitText.setFillColor(sf::Color::White);
    QuitText.setPosition(gameWidth+100, 660);
    allText.push_back(QuitText);

    txt = "Use the Mouse to \nmake your selection";
    sf::Text mouse;
    mouse.setString(txt);
    mouse.setFont(font);
    mouse.setCharacterSize(15);
    mouse.setFillColor(sf::Color(128,128,128));
    mouse.setPosition(gameWidth+100, 160);
    allText.push_back(mouse);
    }





allText.push_back(_TextInput);


    return allText;
}

void EditorLogic::highlightSelection(bool mapChoice)
{
    if (mapChoice)
    {
        for (int i = 0; i < static_cast<int>(_options.size()); i++)
        {
            if (mapChoiceName == _options[i].getString())
            {
                _options[i].setFillColor(sf::Color::Blue);
                if (i <= 10)
                    _options[i].setPosition(100, 20+i*60);
                if (i <= 20 && i >10)
                    _options[i].setPosition(265, 20+(i-10)*60);
                if (i <= 30 && i >20)
                    _options[i].setPosition(430, 20+(i-20)*60);
            }
            else
            {
                _options[i].setFillColor(sf::Color::White);
                if (i <= 10)
                    _options[i].setPosition(100, 24+i*60);
                if (i <= 20 && i >10)
                    _options[i].setPosition(265, 24+(i-10)*60);
                if (i <= 30 && i >20)
                    _options[i].setPosition(430, 24+(i-20)*60);
            }
        }
    }
    if (!mapChoice)
    {
        int ID = static_cast<int>(_entity->getEntityID());
        for (int i=0;i<10;i++)
        {
            if (i == ID)
            {
                _options[i].setFillColor(sf::Color::Blue);
            }
            else
            {
                _options[i].setFillColor(sf::Color::Yellow);
            }
        }
    }
}

void EditorLogic::loadDesigner() //load content portion of Designer
{
    ChoiceInstructions.clear();
    _options.clear();
    _entity = std::make_shared<Path>(sf::Vector2f(0,0)); //set default choice entity to a path

        // display objects on RHS of screen
    //_release = false;
    sf::Text text, QuitText;
    std::string txt = "SAVE";
    text.setString(txt);
    text.setFont(font);
    text.setCharacterSize(25);
    text.setFillColor(sf::Color::White);
    text.setPosition(gameWidth+100, 624);
    ChoiceInstructions.push_back(text);

    std::string str = "EXIT";
    QuitText.setString(str);
    QuitText.setFont(font);
    QuitText.setCharacterSize(25);
    QuitText.setFillColor(sf::Color::White);
    QuitText.setPosition(gameWidth+100, 660);
    ChoiceInstructions.push_back(QuitText);

     sf::Text _opt[10]; //10 options
    _opt[0].setString("<-- Path");
    _opt[1].setString("<-- Wall");
    _opt[2].setString("<-- Door");
    _opt[3].setString("<-- Fruit");
    _opt[4].setString("<-- Pacman");
    _opt[5].setString("<-- Ghost");
    _opt[6].setString("<-- Power Pellet");
    _opt[7].setString("<-- Super Pellet");
    _opt[8].setString("<-- Key");
    _opt[9].setString("<-- Ghost Door");

    for (int i=0;i<10;i++)
    {
        _opt[i].setFont(font);
        _opt[i].setColor(sf::Color::Yellow);
        _opt[i].setCharacterSize(20);
        _opt[i].setPosition(gameWidth+100, 24+i*60);
        _options.push_back(_opt[i]); //highlightable options
    }
        loadMap(_mapFileName);
        loadOptions();
}

void EditorLogic::loadMap(const std::string filename)
{
    if (filename.empty())
    {
    std::vector<std::vector<std::shared_ptr<IMazeEntity>>> mazeGrid(60, std::vector<std::shared_ptr<IMazeEntity>>(55,0));
    sf::Vector2f position, startpos; //start position for comparison
    float xendpos, yendpos;

    for (unsigned int counterX = 0; counterX < 55; ++counterX)
	{
		for (unsigned int counterY = 0; counterY < 60; ++counterY)
		{
		    startpos = sf::Vector2f(counterX * mapTileSize.x, counterY * mapTileSize.y);
            xendpos = (counterX + 1) * mapTileSize.x;
            yendpos = (counterY + 1) * mapTileSize.y;

			position.x = (startpos.x + xendpos)/2;
			position.y = (startpos.y + yendpos)/2;

			auto path = std::make_shared<Path>(position);
            mazeGrid[counterY][counterX] = path;
            _IDGrid[counterY][counterX] = static_cast<int>(Entity_ID::PATH);
            // create entire vector with path objects
		}
	}
	_mazeGrid = mazeGrid; //empty maze grid
    }
    else
    {
        MazeManager maze(filename, false, false);
        _mazeGrid = maze.ReturnMazeGrid();
        createIDvector();
    }
}

void EditorLogic::loadOptions()
{
    //create a separate grid to display the choices
    MazeManager maze("EntityOptions.txt", false, true);
    _optionGrid = maze.ReturnMazeGrid();
    _optionGridp = _optionGrid;
	updateOptionGrid();
	//optionGrid used to determine which entity has been selected by mouseClick
}

void EditorLogic::updateOptionGrid()
{
    //copy into a new grid
    auto newGrid = _optionGrid;
    for (int row = 0; row< 60; row++)
    {
        for (int col = 0; col<3; col++)
        {
            auto entity = _optionGrid[row][col];
            auto ID = entity->getEntityID();
            switch (ID)
            {
            case Entity_ID::DOOR:
                {
                    newGrid[row-1][col] = entity;
                    newGrid[row+1][col] = entity;

                    newGrid[row][col-1] = entity;
                    newGrid[row][col+1] = entity;
                    break;
                }
            case Entity_ID::PATH:
                break;
            case Entity_ID::WALL:
                {
                    newGrid[row-1][col] = entity;
                    newGrid[row+1][col] = entity;

                    newGrid[row][col-1] = entity;
                    newGrid[row][col+1] = entity;
                    break;
                }
            case Entity_ID::GHOST:
                {
                    newGrid[row-1][col] = entity;
                    newGrid[row+1][col] = entity;

                    newGrid[row][col-1] = entity;
                    newGrid[row][col+1] = entity;
                    break;
                }
            case Entity_ID::GHOST_DOOR:
                {
                    newGrid[row-1][col] = entity;
                    newGrid[row+1][col] = entity;

                    newGrid[row][col-1] = entity;
                    newGrid[row][col+1] = entity;
                    break;
                }
            case Entity_ID::PACMAN:
                {
                    newGrid[row-1][col] = entity;
                    newGrid[row+1][col] = entity;

                    newGrid[row][col-1] = entity;
                    newGrid[row][col+1] = entity;
                    break;
                }
            case Entity_ID::KEY:
                {
                    newGrid[row-1][col] = entity;
                    newGrid[row+1][col] = entity;

                    newGrid[row][col-1] = entity;
                    newGrid[row][col+1] = entity;
                    break;
                }
            case Entity_ID::POWER_PELLET:
                {
                    newGrid[row-1][col] = entity;
                    newGrid[row+1][col] = entity;

                    newGrid[row][col-1] = entity;
                    newGrid[row][col+1] = entity;
                    break;
                }
            case Entity_ID::SUPER_PELLET:
                {
                    newGrid[row-1][col] = entity;
                    newGrid[row+1][col] = entity;

                    newGrid[row][col-1] = entity;
                    newGrid[row][col+1] = entity;
                    break;
                }
            case Entity_ID::FRUIT:
                {
                    newGrid[row-1][col] = entity;
                    newGrid[row+1][col] = entity;

                    newGrid[row][col-1] = entity;
                    newGrid[row][col+1] = entity;
                    break;
                }
            }
        }
    }
    _optionGrid = newGrid;
}

std::vector<std::vector<std::shared_ptr<IMazeEntity>>> EditorLogic::returnMaze()
{
    return _mazeGrid;
}

std::vector<std::vector<std::shared_ptr<IMazeEntity>>> EditorLogic::returnOptionGrid()
{

    return _optionGridp;
}
void EditorLogic::Designer()
{
    auto mouseGrid = gridPosition(mousePos);
    //if (_mapStatus == mapStatus::Designer) // if not in text input mode
    //{
        auto saveBound = ChoiceInstructions[0].getGlobalBounds(); // sf::Text boundaries
        if(saveBound.contains(mousePos)) // if the mouse is located within the text boundaries
        {
            if (checkMap())
            {
                    //_input->setInputType(TEXT); //changed in mapeditor
                    _mapStatus = mapStatus::SaveInput; //move to text input mode
                    //loadTextMode();

            }
        }
        auto quitBound = ChoiceInstructions[1].getGlobalBounds();
        if(quitBound.contains(mousePos)) // if the mouse is located within the text boundaries
            _status = LEVEL_COMPLETE;

        //else if (_input->rightClick()){} //use in future versions to remove entities
        if (_select) // if a left click has occurred
        {
            if (mouseGrid.y >=  60 && mouseGrid.y < 63 ) //if click occured on option side
            {
                auto entity = _optionGrid[mouseGrid.x][mouseGrid.y-60]; //retrieve option grid
                _entity = entity;
                highlightSelection(false);
                    //highlight selected
            }
            else if (mouseGrid.y < 55) //if click occured on map side
            {
                updateMap();
                //std::cout<< static_cast<int>(_mazeGrid[mouseGrid.x][mouseGrid.y]->getEntityID()) <<std::endl;
            }
            _select = false; //set to false once everything has been updated
        }
    //}
}

void EditorLogic::TextInputMode() // need to send confirm button too?
{
    sf::Text text("SAVE", font);
    text.setCharacterSize(25);
    text.setFillColor(sf::Color::White);
    text.setPosition(gameWidth+100, 624);

    sf::Text QuitText;
    std::string str = "EXIT";
    QuitText.setString(str);
    QuitText.setFont(font);
    QuitText.setCharacterSize(25);
    QuitText.setFillColor(sf::Color::White);
    QuitText.setPosition(gameWidth+100, 660);
    //name Text File.
    sf::Text in(TextCheck,font);
    _TextInput = in; //to display
    if (_select)
    {
        //auto saveBound = ChoiceInstructions[0].getGlobalBounds(); // sf::Text boundaries
       auto saveBound = text.getGlobalBounds();
        //right clicked on save button -> saves the map and exits to main menu
        if(saveBound.contains(mousePos)) // if the mouse is located within the text boundaries
        {
            //save text file and new map
            //Check for new line character first then continue, the following does not successfully remove a newline character
            /*std::string one = TextCheck;
            std::cout << one ;
            auto newLinePos = one.find('\n');
            if (newLinePos!= std::string::npos)
            {
                one.erase(newLinePos,1);
            }
            std::cout << one;
            TextCheck = one;*/
            createIDvector();
            TextCheck = TextCheck + ".txt";
            FileManager file;
            file.writeMapName(TextCheck);
            TextCheck = "maps/" + TextCheck;
            file.writeMap(TextCheck,_IDGrid);
            setMapFilename("");

            _status = LEVEL_COMPLETE;
        }
        // quit without saving
         auto quitBound = QuitText.getGlobalBounds();
        //auto quitBound = ChoiceInstructions[1].getGlobalBounds();
        if(quitBound.contains(mousePos)) // if the mouse is located within the text boundaries
            _status = LEVEL_COMPLETE;
    }
}

void EditorLogic::loadTextMode()
{
    //ChoiceInstructions.clear();
    //nonClickText.clear();
    //_select=false;
    //_options.clear(); //no reason to not display

    //display user input
    _TextInput.setCharacterSize(25);
    _TextInput.setFillColor(sf::Color(128,128,128));
    _TextInput.setPosition(225, 385);

    std::string txt = "Please enter a filename for your new map: ";
    sf::Text _fileName(txt,font);
    _fileName.setCharacterSize(25);
    _fileName.setFillColor(sf::Color::White);
    _fileName.setPosition(225, 360);
    ChoiceInstructions.push_back(_fileName);

    sf::Text text("SAVE", font);
    text.setCharacterSize(25);
    text.setFillColor(sf::Color::White);
    text.setPosition(gameWidth+100, 624);
    ChoiceInstructions.push_back(text);

    sf::Text QuitText;
    std::string str = "EXIT";
    QuitText.setString(str);
    QuitText.setFont(font);
    QuitText.setCharacterSize(25);
    QuitText.setFillColor(sf::Color::White);
    QuitText.setPosition(gameWidth+100, 660);
    ChoiceInstructions.push_back(QuitText);

}


void EditorLogic::updateMap() //updates the vector and ID grid
{
    auto mouseGrid = gridPosition(mousePos);
    sf::Vector2f position;
    position.y = 6 + (mouseGrid.x*12);
    position.x = 6 + (mouseGrid.y*12);
    _IDGrid[mouseGrid.x][mouseGrid.y] = static_cast<int>(_entity->getEntityID());
    switch(_entity->getEntityID())
    {
        case Entity_ID::DOOR:
        {
            auto object = std::make_shared<Doors>(position);
            _mazeGrid[mouseGrid.x][mouseGrid.y] = object;
            break;
        }
        case Entity_ID::PATH:
        {
            auto object = std::make_shared<Path>(position);
            //std::cout<< static_cast<int>(_mazeGrid[mouseGrid.x][mouseGrid.y]->getEntityID()) <<std::endl;
            _mazeGrid[mouseGrid.x][mouseGrid.y] = object;

                break;
        }
        case Entity_ID::WALL:
        {
            auto object = std::make_shared<Wall>(position);
            _mazeGrid[mouseGrid.x][mouseGrid.y] = object;
            break;
        }
        case Entity_ID::GHOST:
        {
            auto object = std::make_shared<Ghost>(position);
            _mazeGrid[mouseGrid.x][mouseGrid.y] = object;
            break;
        }
        case Entity_ID::GHOST_DOOR:
        {
            auto object = std::make_shared<GhostDoor>(position);
            _mazeGrid[mouseGrid.x][mouseGrid.y] = object;
            break;
        }
        case Entity_ID::PACMAN:
        {
            auto object = std::make_shared<Pacman>(position);
            _mazeGrid[mouseGrid.x][mouseGrid.y] = object;
            break;
        }
        case Entity_ID::KEY:
        {
            auto object = std::make_shared<Keys>(position);
            _mazeGrid[mouseGrid.x][mouseGrid.y] = object;
            break;
        }
        case Entity_ID::POWER_PELLET:
        {
            auto object = std::make_shared<PowerPellet>(position);
            _mazeGrid[mouseGrid.x][mouseGrid.y] = object;
            break;
        }
        case Entity_ID::SUPER_PELLET:
        {
            auto object = std::make_shared<SuperPellet>(position);
            _mazeGrid[mouseGrid.x][mouseGrid.y] = object;
            break;
        }
        case Entity_ID::FRUIT:
        {
            auto object = std::make_shared<Fruit>(position);
            _mazeGrid[mouseGrid.x][mouseGrid.y] = object;
            break;
        }
    }
    //std::string mapCheckstr = "tempMaps/mapCheck" + std::to_string(mapCheck)+".txt";
    //FileManager filec;
    //filec.writeMap(mapCheckstr,_IDGrid);
}

bool EditorLogic::checkMap() //check if the map
{
    //check map criteria..
        //doors must be divisible by 3
        //must not have more than 2 super pellets
        // no more than 4 super pellets
        // only 4 ghosts
    std::vector<std::shared_ptr<IMazeEntity>> ghosts;
    std::vector<std::shared_ptr<IMazeEntity>> pacman;
    std::vector<std::shared_ptr<IMazeEntity>> doors;
    std::vector<std::shared_ptr<IMazeEntity>> super;
    std::vector<std::shared_ptr<IMazeEntity>> power;
    std::vector<std::shared_ptr<IMazeEntity>> fruit;
    std::vector<std::shared_ptr<IMazeEntity>> key;
    for (auto& one : _mazeGrid)
    {
        for (auto& objects : one)
        {
            auto eID = objects->getEntityID();
			switch(eID)
            {
            case Entity_ID::PACMAN:
                {
                    pacman.push_back(objects);
                    break;
                }
            case Entity_ID::GHOST:
                {
                    ghosts.push_back(objects);
                    break;
                }
            case Entity_ID::DOOR:
                {
                    doors.push_back(objects);
                    break;
                }
            case Entity_ID::FRUIT:
                {
                    fruit.push_back(objects);
                    break;
                }
            case Entity_ID::GHOST_DOOR:
                {
                    break;
                }
            case Entity_ID::PATH:
                {
                    break;
                }
            case Entity_ID::KEY:
                {
                    key.push_back(objects);
                    break;
                }
            case Entity_ID::POWER_PELLET:
                {
                    power.push_back(objects);
                    break;
                }
            case Entity_ID::SUPER_PELLET:
                {
                    super.push_back(objects);
                    break;
                }
            case Entity_ID::WALL:
                {
                    break;
                }
            }
        }
    }

    if (pacman.size()!=1)
        return false;
    if(ghosts.size() > 4 || ghosts.size()==0)
        return false;
    if (fruit.size() == 0)
        return false;
    if (key.size() == 0)
        return false;
    if (doors.size()%3 != 0) //and make sure there are more than a certain amount
        return false;
    if (super.size() >2)
        return false;
    if (power.size() >4)
        return false;

    return true;
}
// called before saving map
void EditorLogic::createIDvector()
{
    for (int x = 0; x< 55; x++)
    {
        for (int y = 0; y< 60; y++)
        {
            auto ID = _mazeGrid[y][x]->getEntityID();
            _IDGrid[y][x] = static_cast<int>(ID);
        }
    }
}

sf::Vector2u EditorLogic::gridPosition(sf::Vector2f position)
{
    sf::Vector2u grid;
    // since the position of static maze objects is always initialised as the center of a tile,
    // the addition of 0.5 and using the floor function isnt necessary because the result will
    // always be a whole integer. It is kept here for safety sake
    int column = floor((position.x-6)/12+0.5);
    int row = floor((position.y-6)/12+0.5);
    grid.x = row;
    grid.y = column;
    return grid;
}


void EditorLogic::setMapFilename(const std::string filename)
{    _mapFileName = filename;}


std::string EditorLogic::returnMapName()
{
    return defaultName;
}

Game_Status EditorLogic::returnGameProgress()
{
    return _status;
}
