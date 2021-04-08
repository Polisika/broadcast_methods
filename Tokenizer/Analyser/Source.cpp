#include <fstream>
#include <iostream>
#include "Parser.h"
using namespace std;

int main()
{
	ifstream f("test");
	vector<string>* res;
	res = readFile(f);
	return 0;
}