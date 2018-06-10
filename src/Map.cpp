#include "Map.h"



Map::Map(uint32_t dimensions) : array_map(sf::Vector3i(dimensions, dimensions, dimensions)) {

	if ((int)pow(2, (int)log2(dimensions)) != dimensions)
		Logger::log("Map dimensions not an even exponent of 2", Logger::LogLevel::ERROR, __LINE__, __FILE__);

	sf::Vector3i dim3(dimensions, dimensions, dimensions);

	Logger::log("Generating Octree", Logger::LogLevel::INFO);
	octree.Generate(array_map.getDataPtr(), dim3);

	Logger::log("Validating Octree", Logger::LogLevel::INFO);
	if (!octree.Validate(array_map.getDataPtr(), dim3)) {
		Logger::log("Octree validation failed", Logger::LogLevel::ERROR, __LINE__, __FILE__);
	}
}

void Map::setVoxel(sf::Vector3i pos, int val) {
	array_map.getDataPtr()[pos.x + array_map.getDimensions().x * (pos.y + array_map.getDimensions().z * pos.z)] = val;
}

char Map::getVoxel(sf::Vector3i pos) {
	return array_map.getDataPtr()[pos.x + array_map.getDimensions().x * (pos.y + array_map.getDimensions().z * pos.z)];
	return octree.GetVoxel(pos).found;
}

double Map::Sample(int x, int y, double *height_map) {
	return height_map[(x & (dimensions.x - 1)) + (y & (dimensions.y - 1)) * dimensions.x];
}

void Map::SetSample(int x, int y, double value, double *height_map) {
	height_map[(x & (dimensions.x - 1)) + (y & (dimensions.y - 1)) * dimensions.x] = value;
}

void Map::SampleSquare(int x, int y, int size, double value, double *height_map) {
	int hs = size / 2;

	double a = Sample(x - hs, y - hs, height_map);
	double b = Sample(x + hs, y - hs, height_map);
	double c = Sample(x - hs, y + hs, height_map);
	double d = Sample(x + hs, y + hs, height_map);

	SetSample(x, y, ((a + b + c + d) / 4.0) + value, height_map);
}

void Map::SampleDiamond(int x, int y, int size, double value, double *height_map) {
	int hs = size / 2;

	double a = Sample(x - hs, y, height_map);
	double b = Sample(x + hs, y, height_map);
	double c = Sample(x, y - hs, height_map);
	double d = Sample(x, y + hs, height_map);

	SetSample(x, y, ((a + b + c + d) / 4.0) + value, height_map);
}
