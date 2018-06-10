#include "Map.h"



Map::Map(uint32_t dimensions) : array_map(Vector3i(dimensions, dimensions, dimensions)) {

	if ((int)pow(2, (int)log2(dimensions)) != dimensions)
		Logger::log("Map dimensions not an even exponent of 2", Logger::LogLevel::ERROR, __LINE__, __FILE__);

	Vector3i dim3(dimensions, dimensions, dimensions);

	Logger::log("Generating Octree", Logger::LogLevel::INFO);
	octree.Generate(array_map.getDataPtr(), dim3);

	Logger::log("Validating Octree", Logger::LogLevel::INFO);
	if (!octree.Validate(array_map.getDataPtr(), dim3)) {
		Logger::log("Octree validation failed", Logger::LogLevel::ERROR, __LINE__, __FILE__);
	}
}

void Map::setVoxel(Vector3i pos, int val) {
	array_map.getDataPtr()[pos.x + array_map.getDimensions().x * (pos.y + array_map.getDimensions().z * pos.z)] = val;
}

char Map::getVoxel(Vector3i pos) {
	return array_map.getDataPtr()[pos.x + array_map.getDimensions().x * (pos.y + array_map.getDimensions().z * pos.z)];
	return octree.GetVoxel(pos).found;
}