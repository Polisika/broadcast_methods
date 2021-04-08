#include "Analyser.h"
#include "Log.h"

vertex* nextStage(graph& g, string& buff)
{
	string sep = " ;,()";
	vertex* prev = g.current;
	vertex* curr;

	// нужно обработать токен
	if (g.current == g.start)
	{
		g.start = NULL;
		return g.current;
	}

	for (auto& v : prev->stages)
	{
		bool criteria = isInside(v->variables, buff);
		bool flag = v->symbols.find(buff[0]) != v->symbols.end();

		string numbers = "0123456789";
		if (buff == "int" || ((numbers.find(buff[0]) != string::npos) && v->variables == "#"))
			flag = false;

		// isInside(v->variables, buff)
		if (criteria || flag)
		{
			curr = v;
			g.current = curr;
			return curr;
		}
	}
	
	return NULL;
}

vertex* selectStage(vertex& prev, char p, string& buff)
{
	if (p == ' ')
		// выделили токен
		return NULL;
	else
	{
		buff += p;
		if (prev.symbols.find(p) != prev.symbols.end())
			return &prev;
		else
			// значит что мы выделили токен
			return NULL;
	}
}