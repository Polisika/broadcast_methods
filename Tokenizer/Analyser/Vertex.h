#pragma once
#include <set>
#include <string>
#include <vector>

using namespace std;

struct vertex;

struct vertex
{
	// for any symbols == #
	// for any numbers == @
	string variables; 
	set<vertex*> stages;
	set<char> symbols;
};

bool isInside(const string& str, string c);