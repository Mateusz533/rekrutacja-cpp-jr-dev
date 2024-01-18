#include <iostream>
#include "Tree.h"
#include "Pine.h"

using namespace std;

int main() {
	auto tree = unique_ptr<Tree>(new Pine());
	tree->grow();
}
