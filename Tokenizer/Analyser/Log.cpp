#include "Log.h"

void log_error_message(string mes)
{
	ofstream log("error.txt", std::ios::app);
	log << mes << endl;
	log.close();
}