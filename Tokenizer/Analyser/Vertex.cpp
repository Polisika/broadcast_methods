#include "Vertex.h"

bool cond(char str, string c)
{
	return c.find(str) != std::string::npos;
}

bool isInside(const string& str, string c)
{
	if (cond(c[0], "0123456789") && str == "%")
		return true;

	if (cond(c[0], "0123456789") && str == "#")
		return false;

	return c.find(str) != std::string::npos;
}


