#ifndef CommandHandler_h
#define CommandHnadler_h
#include "Searching.h"
#include "Parsing.h"
#include <string>
#include <vector>

/*
CommandHandler class will base on the switch case and call it's functions
1. case 'i', Contens_Statistics() will execute
2. case 's', Word_Searching() will execute
3. case 'l', HyperLinks() will execute
4. case '?', DisplayHelp() will execute
*/
class CommandHandler {	
private :	
	std::string wordSearch;
	std::string command1;
	std::string command2;
	std::vector<Parsing> files;
public:
	//this function will call in main to start the whole program
	void Programing_Start();
	//these function help display the command lisl nicely
	void DisplayHelp();
	void CommandList();
};

#endif // !CommandHandler_h
