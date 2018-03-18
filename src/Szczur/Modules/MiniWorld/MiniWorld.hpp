#pragma once

#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Szczur/Modules/Script/Script.hpp"
#include "Szczur/Modules/Input/Input.hpp"
#include "Szczur/Modules/Window/Window.hpp"

#include "Szczur/Modules/MiniWorld/MiniMap.hpp"

namespace rat {

struct MiniWorld : public Module<Window, Input, Script>
{
	int state = 0;
	
	bool pause = false;

	std::vector<std::unique_ptr<MiniMap>> maps;
	int currentMap;
	MiniMap* map = nullptr; // <<< current map
	
	sf::RenderTexture canvas;
	
	MiniWorld();
	
	~MiniWorld();
	
	MiniMap* latestMap();
	
	void newMap();
	
	void update(float deltaTime);
	
	void render();
	
	void init();
	
	void initScript();
	
#ifdef EDITOR
	bool drawMapEditor = true;
	void editor();
#endif
};

}