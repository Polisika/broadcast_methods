#pragma once
#include <string>
#include <map>
#include "Table.h"


using namespace std;

// Создать таблицы
class Tokenizer
{
public:
	KeyTable* keywords;
	KeyTable* operations;
	KeyTable* delimeters;
	VariableTable<int>* variables;
	map<string, string> dict;

	Tokenizer();

	string find_token(string word);

	void fill_dict(KeyTable*);
};

