#pragma once
#include <algorithm>
#include <functional>
#include <random>
#include<SFML/Graphics.hpp>
#include "util.hpp"

class ArrayMap {
	

public:

	ArrayMap(sf::Vector3i dimensions);
	~ArrayMap();

	char getVoxel(sf::Vector3i position);
	void setVoxel(sf::Vector3i position, char value);
	sf::Vector3i getDimensions();

	// =========== DEBUG =========== //
	char* getDataPtr();

private:

	char *voxel_data;
	sf::Vector3i dimensions;
	
};
