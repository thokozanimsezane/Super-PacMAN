#ifndef EFFECTSMANAGER_H_INCLUDED
#define EFFECTSMANAGER_H_INCLUDED

#include "Common.h"
#include "Pacman.h"
#include "Ghost.h"
#include "StopWatch.h"

/* This class is responsible for managing the impact of the effects of super and power pellets on the
    dynamic entities (the ghosts and Pacman)of the maze.
    */

/** \class EffectsManager
 *  \brief This is a EffectsManager Class that is responisble for managing the impacts of the super and
 *  power pellets on the dynamic entities (pacman and ghosts) of the maze
 *  \author 719597 Tarryn Maggs and 1033379 Thokozani Msezane.
 *  \version 3.0
 */
class EffectsManager
{
public:

    /** \brief Default Constructor. Creates an EffectsManager object.
     */
    EffectsManager();

    /** \brief Default Destructor. Destroys an EffectsManager object.
     */
    ~EffectsManager();

    /** \brief Sets the effect status (POWER,SUPER or NORMAL) of the class object, which is used in manageEffects
     *  \param effect of type EffectStatus enum
     */
    void setEffect(EffectStatus effect); // not necessary?

    /** \brief manages the effects, ie it will reset the effectstatus back to normal after a certain amount of time has elapsed
      * \param Entities shared pointer of type IDynamicMazeEntity
      */
    void manageEffects(std::vector<std::shared_ptr<IDynamicMazeEntity>> Entities);

    /** \brief returns the EffectStatus of dynamic entities.
      * \return EffectStatus an enumeration type defined in Common.h
      */
    EffectStatus viewStatus();

private:
    EffectStatus _effect;
    StopWatch _watch;

};
#endif // EFFECTSMANAGER_H_INCLUDED
