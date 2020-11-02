 #include "FileManager.h"

 bool sortHighScores(HighScore one, HighScore two) { return (one.score > two.score);}


FileManager::FileManager()
{

}

FileManager::~FileManager(){}

void FileManager::readMapFile(const std::string mapName)
{
    int n = 0;
    static int tiles [3300]; // 55(width) x 60(height) number of tiles in the predefined maze size
    std::ifstream InFile;
    InFile.open(mapName);
    if (!InFile.is_open())
        std::cout << "cannot open file" << std::endl;

    while(!InFile.eof())
    {
        InFile >> tiles[n];
        n++;
    }
    InFile.close();
    _tiles = tiles;
}

int * FileManager::returnMap()
{
    return _tiles;
}


void FileManager::writeMap(const std::string filename, std::vector<std::vector<int>> IDs)
{
    std::ofstream outFile;
    outFile.open(filename, std::ofstream::out | std::ofstream::trunc);
    for (auto& one :IDs)
    {
        for (auto& two : one)
        {
            outFile << two;
            outFile << " "; // always write with a space between values
        }
        outFile << "\n";
    }
    outFile.close();
}


//read High Scores
//want to only ever keep the top  10 scores  - always reorder such that first entry is the highest score
void FileManager::readAllHighScores()
{
    std::ifstream infile("HighScores.txt");
    if (!infile.is_open())
    {
        std::cout << "File does not exist" << std::endl;
        throw "HighScores file does not exist";
    }
    HighScore hScore;
    std::vector<HighScore> highScores;
    std::string textline;
    int score;
    std::string name;
    while(getline(infile,textline))
    {
        std::istringstream text_stream(textline);
        text_stream >> score;
        getline(text_stream, name, '\n');

        hScore.score = score;
        hScore.name = name;

        highScores.push_back(hScore);
    }
    _highScores = highScores;
    infile.close();
}

HighScore FileManager::returnHighScore()
{
    return _highScores[0];
}

// Used in main menu - High Scores
std::vector<HighScore> FileManager::returnAllHighScores()
{
    return _highScores;
}

void FileManager::manageHighScores()
{
    //always rewrite file so that highest score is at the top.
    std::sort(_highScores.begin(), _highScores.end(), sortHighScores);
    std::ofstream outFile;

    while(_highScores.size() > 10)
    {
        _highScores.pop_back(); // delete
    }

    outFile.open("HighScores.txt", std::ofstream::out | std::ofstream::trunc);
    for (auto& scores :_highScores)
    {
        while(isspace(scores.name[0])) //makes sure the file is written without any leading zeroes
        {
            std::string newName = scores.name.substr(1);
            scores.name = newName;
        }
        outFile << scores.score;
        outFile << " "; // always write with a space between values
        // then any character cam be contained in the name
        outFile << scores.name;
        outFile << "\n";
    }
    outFile.close();
}

bool FileManager::findNewScore(HighScore hScore)
{
    bool newHighScore = false;
    for (auto& score :_highScores)
    {
        if (score.score < hScore.score)
        {
            newHighScore = true;
        }
    }
    return newHighScore;
}

void FileManager::saveNewScore(HighScore hScore)
{
    _highScores.push_back(hScore);
    manageHighScores(); //restructure if a new input
}

void FileManager::readMapNames()
{
    std::ifstream infile("maps/mapNames.txt");
    if (!infile.is_open())
    {
        std::cout << "File does not exist" << std::endl;
        throw "mapNames file does not exist";
    }
    std::string name;
    std::vector<std::string> mapNames;

    std::string textline;

    while(getline(infile,textline))
    {
        std::istringstream text_stream(textline);
        text_stream >> name;
        mapNames.push_back(name);
    }
    _mapNames = mapNames;
    infile.close();
}

std::vector<std::string> FileManager::returnMapNames()
{
    return _mapNames;
}

void FileManager::writeMapName(std::string name)
{
    std::ofstream outFile;
    outFile.open("maps/mapNames.txt", std::ofstream::app);
    outFile << name;
    outFile << "\n";
    outFile.close();
}
