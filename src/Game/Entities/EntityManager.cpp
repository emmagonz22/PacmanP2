#include "EntityManager.h"

void EntityManager::tick()
{
    //This will remove entity from entities vector
    std::vector<int> toRemove;
    for (int i = 0; i < entities.size(); i++)
    {
        if (!entities[i]->remove)
        {
            entities[i]->tick();
        }
        else
        {
            toRemove.push_back(i);
        }
    }
    for (Block *block : blocks)
    {
        block->tick();
    }
    for (unsigned int removable : toRemove) //remove from entities
    {
        entities.erase(entities.begin() + removable);
    }
}

void EntityManager::render()
{
    for (Entity *entity : entities)
    {
        entity->render();
    }
    for (Block *block : blocks)
    {
        block->render();
    }
}