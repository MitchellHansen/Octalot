#pragma once
#include <functional>
#include <bitset>
#include <ctime>
#include <queue>
#include "ArrayMap.h"
#include "Logger.h"
#include "Octree.h"
#include "util.hpp"

#define _USE_MATH_DEFINES
#include <cmath>

class Map {
public: 

	// Currently takes a 
	Map(uint32_t dimensions);

	// Sets a voxel in the 3D char dataset
	void setVoxel(Vector3i position, int val);
	
	// Gets a voxel at the 3D position in the octree
	char getVoxel(Vector3i pos);

	// Octree handles all basic octree operations
    Octree octree;
	ArrayMap array_map;

private:

	// ======= DEBUG ===========
	int counter = 0;
	std::stringstream output_stream;
	
	sf::Vector3i dimensions;
	// =========================

	double Sample(int x, int y, double *height_map);
	void SetSample(int x, int y, double value, double *height_map);
	void SampleSquare(int x, int y, int size, double value, double *height_map);
	void SampleDiamond(int x, int y, int size, double value, double *height_map);

};

// Might possibly use this struct for hashing XYZ chunk values into a dict for storage and loading
struct XYZHasher {
	std::size_t operator()(const sf::Vector3i& k) const {
		return ((std::hash<int>()(k.x)
			^ (std::hash<int>()(k.y) << 1)) >> 1)
			^ (std::hash<int>()(k.z) << 1);
	}
};
