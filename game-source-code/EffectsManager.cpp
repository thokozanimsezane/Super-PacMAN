#include "EffectsManager.h"

// collisions with pellets and ghosts
// checks powerstatus, if power and collides with ghost - ghost dies - status set to transition

// entity->setPowerStatus(POWER)

// vector<shared_ptr<IDynamicMazeEntity>>
// set corresponding status/power status of objects
// what happens to each


//call a timer -reset to normal
EffectsManager::EffectsManager():_effect(EffectStatus::NORMAL)
{}

EffectsManager::~EffectsManager(){}

//called if a collision with a pellet occurs
void EffectsManager::setEffect(EffectStatus effect)
{
    _effect = effect;
    _watch.reset();
}

EffectStatus EffectsManager::viewStatus()
{
    return _effect;
}


//called before or after (or both) collisions
//called before collisions manager. call setEffect with entities if a pellet is hit
void EffectsManager::manageEffects(std::vector<std::shared_ptr<IDynamicMazeEntity>> Entities)
{
    if (_effect == EffectStatus::SUPER || _effect == EffectStatus::POWER)
    {
        if (_watch.stop() < effectTime)
        {
            for (auto& entity : Entities)
                {
                    entity->setEffectStatus(_effect);
                }
        }
        if (_watch.stop() >= effectTime)
        {
                for (auto& entity : Entities)
                {
                    entity->setEffectStatus(EffectStatus::NORMAL);
                }
                _effect = NORMAL;
        }
    }
}

