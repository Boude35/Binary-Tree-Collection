#include "MovieNode.hpp"

using namespace std;

//return wether the node has or not any child
bool
MovieNode::isLeaf() const
{
	return !_right && !_left;
}

//overloading of << operator
ostream& operator<<(ostream &os, const MovieNode &in)
{
	os<<in.value();
	return os;
}
