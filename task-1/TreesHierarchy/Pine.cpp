#include "Pine.h"

void Pine::grow() {
	this->leaves.push_back(std::unique_ptr<AbstractLeaf>(new PineNeedle(1)));
	std::cout << "Adding once more pine needle ...";
}
