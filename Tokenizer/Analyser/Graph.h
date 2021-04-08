#pragma once
#include "Vertex.h"
#include <vector>

using namespace std;

struct graph
{

	vector<vertex*> vertices;
	vertex* current;
	vertex* start;
};