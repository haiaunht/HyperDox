/*
**Hai-Au Bui, Term Project
**Professor Ferguson, CSD233
**This program contain 5 cases which are:
			1. User enter "I" or "i" follow by the file's name to see all the contents and statistics of that file. Then user can search 
				a specific word at current file.
			2. User enter "S" or "s" follow by the string "word", the program will traverse each vector _words of each parsed file to
				find how many time the word appear, then display result how many words/each file/ all 15 files
			3. User enter "L" or "l" follow by "file's name" to see the file's contents and user will see all the hyperlinks in a 
				corresponding order start from 1 to end. User can enter the link's number to nevigate to that link
						+ if user enter the link which is less than 1 or more than the number of links
						  that the file has, an exception will be throw that "link out of range"
						  the main will handle this exception. 
						  -----Ex: diet.dox has 6 links. I have to enter number 1 through 6 to navigate to each link.
						  -----If I enter number less than 0 or greater than 6, exception number 1 will be thrown
						  -----main catch this int& e. I tested and it is successful!
						+ if user enter the link which is not a number, string exception "link must be a digit" will be thrown
						  -----I tested it and it is successful! 
						+ if user want to go back from begining, type number 0
			4. User enter '?" for Help
			5. User enter "Q" or "q" to quit the program
*/

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <exception>
#include <algorithm>
#include <ctype.h>
#include <Windows.h>
#include "Searching.h"
#include "Parsing.h"
#include "CommandHandler.h"


int main()
{	
	//create CommandHanler object execute_Myproject, and call its function Programing_start()
	CommandHandler execute_MyProject;
	execute_MyProject.Programing_Start();

	return 0;
}
