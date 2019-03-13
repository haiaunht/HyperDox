#include "pch.h"
#include "CommandHandler.h"
#include "Parsing.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <Windows.h>
#include "Searching.h"
using namespace std;

//create object document from Searching class to use Searching's functions such as to lowercase, 
//set and get current file and searchWord
Searching document;

void CommandHandler::Programing_Start() {
	//create Searching object to load all files, set and get current file etc.
	Searching document;

	//variable fileList will store all the files that are found in my project folder
	vector<string*> fileList;
	document.LoadFiles("C:\\Users\\HaiAu\\source\\repos\\Term Project", fileList);

	//display out to console if those files are successuflly uploaded
	cout << "Successfully Loading: " << endl;
	for (string* item : fileList)
		cout << "C:\\Users\\HaiAu\\source\\repos\\Term Project " << *item << endl;

	//create an vector of Object Parsing, each object store infomation of 
	//how many word, how many links, how many anchor, and the statistics of each files
	vector<Parsing> parse_Files;
	for (string* file : fileList) {
		parse_Files.push_back(Parsing(*file));
	}


	//declare variable that will entered by user	
	char command;	// will hold char 'i', 's', 'l', '?', or 'q'
	string fileName;	//will hold the file's name
	string wordSearch;	//will hold the word that user want to search for

	//set the console color to be white
	HANDLE word = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(word, 15);

	//create object CommandHandler to handle each case of i, s, l, ? or q
	//prompt user to enter any command they wish and command will pass through swich statement
	//CommandHandler userCommand;
	CommandList();
	cin >> command;


	//use the while loop to keep taking demand from user until user enter q for quit
	while (command != 'q' || command != 'Q') {
		switch (command)
		{
			//case 'i' then file's name will display all the content + statistics of that file
		case 'I':
		case 'i':
			cin >> fileName;
			document.Contents_Statistics(parse_Files, fileName);
			break;
			//case 's' then file's name will display how many times the 'word' appear in each file
		case 's':
		case 'S':
			cin >> wordSearch;
			document.Words_Searching(parse_Files, wordSearch);
			break;
			//case 'l' will show all the contents and all the hyperlinks, user will be able to nevigate to any links in the list
		case 'l':
		case 'L':
			try {
				//if HyperLinks function throw execption "link out of range" or "link must be a number", multiple catch case will catch
				cin >> fileName;
				document.HyperLinks(parse_Files, fileName);
				cout << "Wrong file's name!" << endl;	// if user enter wrong name file, output the error	
				break;
			}
			catch (int& e) {
				cerr << "The link number must be a digit!" << endl;
				break;
			}
			catch (string& e) {
				cout << e << endl;
				break;
			}
			//case "?" show all the commands 
		case '?':
			DisplayHelp();
			break;
		case 'q':
		case 'Q':
			exit(EXIT_SUCCESS);
			break;
		default:
			cout << "This is not a valid demand!" << endl;
			break;
		}
		cout << endl;

		//ask if user want another demand or quit the program
		cin >> command;
	}

}

//display the command list
void CommandHandler::CommandList() {
	std::cout << "Please enter your command:" << std::endl;
	std::cout << "\t<I file's name> to see contents and statistics of that file (Ex: i zoos.dox) " << std::endl;
	std::cout << "\t<s word> to search how many times it appears in each file (Ex: s panda)" << std::endl;
	std::cout << "\t<L file's name> to search for link (Ex: \"l top.dox\") " << std::endl;
	std::cout << "\t<q> to quit or <?> for Help. " << std::endl;
}

//display Help
void CommandHandler::DisplayHelp() {
	std::cout << "Help? Available commands are: " << std::endl;
	std::cout << "\t<I file's name> to see contents and statistics of that file (Ex: i zoos.dox) " << std::endl;
	std::cout << "\t<s word> to search the word in text (Ex: s panda)" << std::endl;
	std::cout << "\t<L file's name link> to search for link (Ex: \"l top.dox\") " << std::endl;
	std::cout << "\t<q> to quit or <?> for Help. " << std::endl;
}
