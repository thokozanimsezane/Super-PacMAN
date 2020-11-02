#include "LogicPresenter.h"

LogicPresenter::LogicPresenter(int Lives, std::string filename): _GameLogic(Lives, filename)
{
    //set game status to incomplete
}

LogicPresenter::~LogicPresenter()
{}

void LogicPresenter::PacMaze()
{
    _GameLogic.runMaze();
}


void LogicPresenter::sendUserInput(UserInput _input)
{
    _GameLogic.InterpretInput(_input);
}

std::vector<std::shared_ptr<IMazeEntity>>& LogicPresenter::PackageEverything()
{
    return _GameLogic.packageEntities();
}

std::vector<std::shared_ptr<IDynamicMazeEntity>>& LogicPresenter::PackageDynamic()
{
    return _GameLogic.packageDynamic();
}

int LogicPresenter::returnScore()
{
    return _GameLogic.returnScore();
}

int LogicPresenter::returnLives()
{
    return _GameLogic.returnLives();
}

Game_Status LogicPresenter::returnGameProgress()
{
    return _GameLogic.returnGameProgress();
}
