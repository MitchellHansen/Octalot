
/**
 * Title:     Octalot
 * Author:    Mitchell Hansen
 * License:   TBD
 */



#include <memory>
#include <Cube.hpp>
#include "Map.h"

int main() {

	std::shared_ptr<Map> map = std::make_shared<Map>(32);;

	Cube<int> t;
	return 0;
}
