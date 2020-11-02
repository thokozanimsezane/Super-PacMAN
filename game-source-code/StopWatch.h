#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <ctime>
#include <iostream>

/** \class StopWatch
 *  \brief This class is responsible for all timing needs of the game, it is used in EffectsManager, PathHandler
 *  and GhostMovementManager
 *  \author 719597 Tarryn Maggs and 1033379 Thokozani Msezane.
 *  \version 3.0
 */

using namespace std;

class StopWatch {
public:

    /** \brief A default constructor of an object of type StopWatch, creates a StopWatch Object.
     */
    StopWatch();

    /** \brief A default destructor, destroys a type StopWatch object.
     */
    ~StopWatch();

    /** \brief This function resets the start time of the stopwatch.
     */
    void reset();

    /** \brief This function uses the start time to determine how much time has elapsed since you started the stopwatch
     *  \return double
     */
    double stop(); // uses the start time to determine how much time has elapsed since you started the stopwatch

private:

    /** \brief This function return the time that has elapsed since the process started runnning
     *  \return double
     */
    double getProcessTime();

    double _startTime;
    double _timeElapsed;
    };

// returns the amount of time in seconds that has passed since the process (i.e. your program) started executing
//double getProcessTime();


#endif
