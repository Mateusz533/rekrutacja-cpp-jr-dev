#pragma once
#include <vector>
#include <memory>
#include "AbstactLeaf.h"
#include "Branch.h"
#include "Trunk.h"

class Tree {
public:
	virtual ~Tree() = default;
	virtual void grow() = 0;

protected:
	Trunk trunk;
	std::vector<Branch> branches;
	std::vector<std::unique_ptr<AbstractLeaf>> leaves;
};
