#include "Token.h"

string Tokenizer::find_token(string word)
{
	if (dict.find(word) == dict.end())
	{
		int index = variables->add_element(word);
		string token = "(4, " + to_string(index) + ")";
		dict.insert(
			make_pair(word, token)
		);
		return token;
	}
	else
		return dict[word];
}

void Tokenizer::fill_dict(KeyTable* keywords)
{
	for (int i = 0; i < keywords->values->size(); i++)
	{
		string token = "(" + to_string(keywords->type) + ", " + to_string(i) + ")";
		dict.insert(
			make_pair(keywords->values->at(i), token)
		);
	}
}

Tokenizer::Tokenizer()
{
	keywords = new KeyTable(TableType::KEYWORDS);
	operations = new KeyTable(TableType::OPERATIONS);
	delimeters = new KeyTable(TableType::DELIMETERS);

	variables = new VariableTable<int>();

	fill_dict(keywords);
	fill_dict(operations);
	fill_dict(delimeters);
}