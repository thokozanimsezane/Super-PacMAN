#include "StopWatch.h"
#include <ctime>
using namespace std;

StopWatch::StopWatch()
{
    _startTime = getProcessTime();
}

StopWatch::~StopWatch(){}

// returns the amount of time in seconds that has passed since the process (i.e. your program) started executing
double StopWatch::getProcessTime()
{
	clock_t time = clock();
	return static_cast<double>(time)/CLOCKS_PER_SEC;
}

void StopWatch::reset() //changes start time to new
{
    _startTime = static_cast<double>(getProcessTime());
}

double StopWatch::stop()
{
    auto end_time = getProcessTime();
    auto process_time = end_time - _startTime;
    return static_cast<double>(process_time);
}
