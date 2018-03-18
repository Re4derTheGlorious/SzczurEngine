#pragma once

/** @file World.hpp
 ** @description Header file with main class of the World module. 
 ** @author Patryk (PsychoX) Ludwikowski <psychoxivi+basementstudios@gmail.com>
 **/

#include <vector>

#include <SFML/System/Vector2.hpp>

#include "Szczur/Debug.hpp"
#include "Szczur/Utility/Modules/Module.hpp"
#include "Szczur/Modules/Window/Window.hpp"
#include "Szczur/Modules/DragonBones/DragonBones.hpp"
#include "ObjectType.hpp"
#include "Map.hpp"

namespace rat {

/** @class World
 ** @description Manages objects in the game world through the maps system, including loading and saving, object types management and other.
 **/
class World : public Module<Window, DragonBones>
{
    using Module::Module;


	
    /* Variables */
public: // @warn priv&prop
    std::vector<ObjectType*> types;
	
	std::vector<Map>	maps;
	Map* 				currentMap = nullptr;
	
	Object*				playerObject = nullptr;



	/* Operators */
public:
	// Module constructor/destructor
	World();
	~World();

	// Disable coping
	World(const World&) = delete;
	World& operator = (const World&) = delete;

	// Disable moving
	World(World&&) = delete;
	World& operator = (World&&) = delete;



	/* Methods */
public:
    // Module system
	void init();
	void update(float deltaTime);
	void render();

	// @todo . load
	// @todo . save
};

}
