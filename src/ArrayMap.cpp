#include <ArrayMap.h>



ArrayMap::ArrayMap(sf::Vector3i dimensions) {
	
	this->dimensions = dimensions;

	voxel_data = new char[dimensions.x * dimensions.y * dimensions.z];
	for (int i = 0; i < dimensions.x * dimensions.y * dimensions.z; i++) {
		voxel_data[i] = 0;
		//voxel_data[i] = 1;
	}

	setVoxel(sf::Vector3i(1, 1, 5), 1);

	for (int x = 0; x < dimensions.x; x++) {
		for (int y = 0; y < dimensions.y; y++) {
			for (int z = 0; z < dimensions.z; z++) {
				setVoxel(sf::Vector3i(x, y, z), 5);
			}
		}
	}

// 	for (int x = 0; x < dimensions.x/2-1; x++) {
// 		for (int y = 0; y < dimensions.y/2-1; y++) {
// 			for (int z = 0; z < dimensions.z/2-1; z++) {
// 				setVoxel(sf::Vector3i(x, y, z), 5);
// 			}
// 		}
// 	}
}


ArrayMap::~ArrayMap() {
	delete[] voxel_data;
}

char ArrayMap::getVoxel(sf::Vector3i position) {
	return voxel_data[position.x + dimensions.x * (position.y + dimensions.z * position.z)];
}


void ArrayMap::setVoxel(sf::Vector3i position, char value) {
	voxel_data[position.x + dimensions.x * (position.y + dimensions.z * position.z)] = value;
}

sf::Vector3i ArrayMap::getDimensions() {
	return dimensions;
}

char* ArrayMap::getDataPtr() {
	return voxel_data;
}