#include "pch.h"
#include "Searching.h"
#include "Parsing.h"
#include <string>
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <io.h>
#include <list>
#include <iomanip>

//load all file in my project folder
void Searching::LoadFiles(std::string directoryPath, std::vector<std::string*>& fileList) {
	//declare fullPath include my directoryPatn plus any file with name follow by ".dox"
	std::string fullPath = directoryPath + "/*.dox";

	_finddata_t data;
	intptr_t findFile = _findfirst(fullPath.c_str(), &data);

	if (findFile != -1) {
		int res = 0;
		while (res != -1) {
			fileList.push_back(new std::string(data.name));
			res = _findnext(findFile, &data);
		}
		_findclose(findFile);
	}

	return;
}


//set and get current file
void Searching::Set_CurrentFile(std::string file) {
	currentFile = file;
}
std::string Searching::Get_CurrentFile() {
	return currentFile;
}


//RemovePunctuation() funtion remove all punctuation around the word
//and return the word without any puntuation
std::string Searching::RemovePunctuation(std::string& s) {
	for (size_t i = 0; i < s.length(); ++i)
		if (ispunct(s.at(i)))
			s.erase(i, 1);
	return s;
}

//toLowerCase() function will convert each letter in string 'word' to lowercase
std::string Searching::toLowerCase(std::string& word){
	unsigned int i;
	for (i = 0; i < word.length(); i++) {
		word.at(i) = tolower(word.at(i));
	}
	return word;
}

//set highlight the text I want with color code from 0-15
void Searching::Set_Highlight(std::string text, int color) {
	HANDLE word = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(word, color);
	std::cout << text << std::endl;
	//set back to black background and white text
	SetConsoleTextAttribute(word, 15);
}

/*
**SearchWord function will return all the indexs of the word that user enter
**that found in vector<string> words
**@param: string word enterd by user
**@return: int index was found in all file belong to list<string> fileList
			how many times the word searching appear
*/
void Searching::searchWord( std::vector<std::string> words, std::string search) {
	unsigned int count = 0;

	//output all the index of the word is searching, the first word in file will count at 1 (i+1)
	std::cout << std::setw(15) << std::right << std::setfill('*')  << "Results: " << std::endl;
	for ( int i = 0; i < words.size(); i++) {
		if (search == RemovePunctuation(words.at(i))) {
			count++;
			std::cout << "\"" << search << "\": " << "[" << (i + 1) << "]" << std::endl;
		}
	}
	std::cout << "The word \"" << search << "\" appear: " << count << " times."  << std::endl;

}

void Searching::Contents_Statistics(std::vector<Parsing> parse_Files, std::string fileName) {
	for (Parsing i : parse_Files) {
		//get fileName of Parsing object that match fileName entered by user
		std::string wordSearch;
		std::string fName = i.Get_FileName();
		if (toLowerCase(fileName) == toLowerCase(fName)) {
			i.Get_Statistic(fName);
			i.Display_Words();
			i.Display_Statistics();
			Set_CurrentFile(fName);
			std::cout << "Current file: ";
			//set the color of text in console to light read
			Set_Highlight(Get_CurrentFile(), 12);
			//at current file user can search for a specific word
			std::cout << "Word you are searching: ";
			std::cin >> wordSearch;
			//std::cout << std::setw(15) << std::left << std::setfill('*') << document.Get_CurrentFile() << std::endl;
			searchWord(i.Get_Words(), wordSearch);
		}
	}
}

//'i' case, function will traverse all vector _words in vector<Parsing> and display how many times each file has found the word
void Searching::Words_Searching(std::vector<Parsing> parse_Files, std::string wordSearch) {
	for (Parsing i : parse_Files) {
		i.Get_Statistic(i.Get_FileName());
		std::cout << std::setw(15) << std::left << std::setfill('*');
		Set_Highlight(i.Get_FileName(), 14);
		searchWord(i.Get_Words(), wordSearch);
	}
}

//'l' case, will call HyperLinks() function to repeatedly find the link that user wish;
void Searching::HyperLinks(std::vector<Parsing> parse_Files, std::string fileName) {
	for (Parsing i : parse_Files) {
		//get fileName of Parsing object that match fileName entered by user
		int searchLink = 0;
		std::string fName = i.Get_FileName();

		//if the file's name is one of 15 file's name in vector<Parsing> --> display contents, 
		//set current file and display all the links this file has for user to choose again
		if (toLowerCase(fileName) == toLowerCase(fName)) {
			i.Get_Statistic(fName);
			i.Display_Words();
			std::vector<std::string> linkName = i.Get_Links();
			Set_CurrentFile(fName);
			std::cout << std::endl << std::endl << "Current file: ";
			//set the color of text in console to light read
			Set_Highlight(Get_CurrentFile(), 12);

			//output all the link the current file
			std::cout << std::endl << "------" << linkName.size() << " links in " << Get_CurrentFile() << std::endl;
			for (int i = 0; i < linkName.size(); i++) {
				std::cout << "[" << i + 1 << "] : " << linkName.at(i) << std::endl;
			}
			//calling Search_For_Link() to navigate to its file
			Search_For_Link(parse_Files, linkName, searchLink);
		}
	}
}

/*
**Search_For_Link function will pass parsed files attribute (_links list), which need to compare and the link number to navigate to
**@param: vector of Parsing files, vector of links, and link's number
**@return: current file with the list of links, user will enter the link's number they wish
**@return: the file that corresponding with that link's number
This function will throw exeption if:
	- user enter the link that not in the list
	- user enter not a number for link's number
	- if user want to go back the begining, type number 0
*/
void Searching::Search_For_Link(std::vector<Parsing> parse_Files, std::vector<std::string> linkName, int searchLink) {
	for (Parsing i : parse_Files) {
		std::cout << "Enter the link's number or 0 to go back: ";
		std::cin >> searchLink;
		for (int j = 0; j < linkName.size(); j++) {
			//cout << "test how many link here   " << l << endl;
			//check if user enter the link which in the file
			if (searchLink == j + 1) {
				std::string linkFound = linkName.at(j);
				std::cout << std::endl << "*****" << linkName.at(j) << " link is found. " << std::endl;
				i.Get_Statistic(linkFound);
				i.Display_Words();
				std::cout << std::endl << "Current file: ";
				i.Set_FileName(linkName.at(j));
			}
			else if (std::cin.fail()) {
				std::cin.clear(); //This corrects the stream.
				std::cin.ignore(256, '\n'); //This skips the left over stream data 256 characters.
				throw 1; //if ueser enter anything beside digit will throw exception 1
			}
			else if (searchLink == 0) {
				throw std::string{ "Welcome back!" };
			}
			else if (searchLink <1 || searchLink > linkName.size()) {
				throw std::string{ "The link number is out of range!" };
			}
		}
		//sest current file again
		Set_Highlight(i.Get_FileName(), 12);
		Set_CurrentFile(i.Get_FileName());
		Get_CurrentFile();
		linkName = i.Get_Links();
		std::cout << std::endl << "------" << linkName.size() << " links in file: " << i.Get_FileName() << std::endl;
		for (int i = 0; i < linkName.size(); i++) {
			std::cout << "[" << i + 1 << "] : " << linkName.at(i) << std::endl;
		}
	}
}