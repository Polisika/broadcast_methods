#include "Parser.h"
#include "Analyser.h"
#include "Log.h"
#include "Token.h"
#include <fstream>

vector<string>* readFile(ifstream& file)
{
	ofstream out("out.txt");

	vector<string> res;
	// Возьмем реализованный граф
	#pragma region graph
	vertex ident{ "#" };
	vertex digit{ "%" };
	vertex operation{ "<= >= == + - < >" };
	vertex equal{ "=" };
	vertex delimiter{ ", ; ( ) { }" };
	vertex keywords{ "if while" };
	vertex type{ "int" };

	ident.stages = { &equal, &delimiter, &operation, &digit };
	digit.stages = { &operation, &delimiter };
	operation.stages = { &ident, &digit };
	equal.stages = { &ident, &digit };
	delimiter.stages = { &type, &keywords, &delimiter, &ident };
	keywords.stages = { &delimiter, &ident };
	type.stages = { &ident };

	for (char c : operation.variables)
		operation.symbols.insert(c);

	for (char c : equal.variables)
		equal.symbols.insert(c);

	for (char c : type.variables)
		type.symbols.insert(c);

	for (char c : delimiter.variables)
		delimiter.symbols.insert(c);

	for (char c : keywords.variables)
		keywords.symbols.insert(c);

	string f = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM1234567890";
	for (char c : f)
		ident.symbols.insert(c);

	f = "1234567890";
	for (char c : f)
		digit.symbols.insert(c);

	graph* g = new graph();
	vector<vertex*> vertices({ &operation, &equal, &type, &delimiter, &keywords, &ident, &digit });
	g->vertices = vertices;
	g->start = &type;
	g->current = g->start;
#pragma endregion

	Tokenizer* tokenizer = new Tokenizer();
	int line = 1;
	char curr;
	string buff = "";
	string sep = " ,;()\n{}\t";
	while ((curr = file.get()) != -1)
	{
		if (sep.find(curr) == std::string::npos)
		{
			buff += curr;
			continue;
		}

		if (curr == '\t')
		{
			out << '\t';
			continue;
		}

		if (curr == '\n') {
			line++;

			out << endl;
	
			continue;
		}

		bool isReady = false;
		if (buff == "")
		{
			buff = curr;
			isReady = true;
		}
		vertex* v = nextStage(*g, buff);

		if (v == NULL)
		{
			log_error_message("Error: state not found in line " + to_string(line) + " with keyword: " + buff);
			log_error_message("Stage fault");
			return nullptr;
		}


		// Найдем положение в таблице данного токена
		string token = tokenizer->find_token(buff);
		res.push_back(token);
		out << token << " ";

		if (curr != ' ' && !isReady)
		{
			buff = curr;
			vertex* v = nextStage(*g, buff);
			// Найдем положение в таблице данного токена
			string token = tokenizer->find_token(buff);
			res.push_back(token);
			out << token;
			buff = "";
		}

		buff = "";
	}
	return &res;
}
