#pragma once
#include <algorithm>
#include <functional>
#include <random>
#include "util.hpp"
#include "Vector3.hpp"

class ArrayMap {
	

public:

	ArrayMap(Vector3i dimensions);
	~ArrayMap();

	char getVoxel(Vector3i position);
	void setVoxel(Vector3i position, char value);
	Vector3i getDimensions();

	// =========== DEBUG =========== //
	char* getDataPtr();

private:

	char *voxel_data;
	Vector3i dimensions;
	
};
