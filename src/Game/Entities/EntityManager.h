#pragma once

#include "Block.h"

class EntityManager {

public:

	std::vector<Entity*> entities;
	std::vector<Block*> blocks;
	void tick();
	void render();
	//method to add entities to the "entities" vector
	void addEntity(Entity* member){entities.push_back(member);} 

};