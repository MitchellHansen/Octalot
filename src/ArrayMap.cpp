#include <ArrayMap.h>

ArrayMap::ArrayMap(Vector3i dimensions) {
	
	this->dimensions = dimensions;
	voxel_data = new char[dimensions.x * dimensions.y * dimensions.z];

	// Init to 0
	for (int i = 0; i < dimensions.x * dimensions.y * dimensions.z; i++) {
		voxel_data[i] = 0;
	}


	// Randomly set data
    srand(time(nullptr));
	for (int x = 0; x < dimensions.x; x++) {
		for (int y = 0; y < dimensions.y; y++) {
			for (int z = 0; z < dimensions.z; z++) {

                if (rand() % 2 == 0)
                    setVoxel(Vector3i(x, y, z), 1);
                else
                    setVoxel(Vector3i(x, y, z), 0);
			}
		}
	}
}


ArrayMap::~ArrayMap() {
	delete[] voxel_data;
}

char ArrayMap::getVoxel(Vector3i position) {
	return voxel_data[position.x + dimensions.x * (position.y + dimensions.z * position.z)];
}


void ArrayMap::setVoxel(Vector3i position, char value) {
	voxel_data[position.x + dimensions.x * (position.y + dimensions.z * position.z)] = value;
}

Vector3i ArrayMap::getDimensions() {
	return dimensions;
}

char* ArrayMap::getDataPtr() {
	return voxel_data;
}