#include "pch.h"
#include "Parsing.h"
#include <fstream>
#include <Windows.h>
#include <iostream>
#include <iomanip>


/*
Get_Statistic() function will pass each file's name argument and stores the relevant info
@param: file - each file that loaded from my project
@return: total_WordCount - integer number of how many words in the file
@return:average_WordLength - float number of total words length / words counted
@return: _anchors - vector of anchor appear in the file
@return: _links - vector of links appear in the file
@return: _words - vector of words appear in the file
*/
void Parsing::Get_Statistic(std::string file) {
	//declare inputFile will read the file and parse the file
	std::ifstream inputFile;
	inputFile.open(file);
	std::vector<std::string> words;
	std::vector<std::string> anchors, links;
	std::string word, anchorName,  linkName;
	unsigned int count = 0;
	double wordLength = 0;
	double averageWordLength = 0;

	//if file can not open, output the error
	if (!inputFile) {
		std::cerr << "Cannot open this file!" << std::endl;
	}
	
	//use while loop to read until the end of the file
	while ( inputFile >> word ){		
		words.push_back(word);
		wordLength += word.length();
		count++;

		//find the name embeded between !# name |
		if (word.find('|#') != std::string::npos) {
			anchorName = word.substr(word.find('|#'), word.length() - 3);
			anchors.push_back(anchorName);
		}

		//find the name embeded between !name :|
		if (word.find(".dox") != std::string::npos) {
			linkName = word.substr(1, (word.find(".dox")+3) );
			links.push_back(linkName);
		}

		//std::cout <<word << " "<< std::endl;
		/*words.push_back(word);
		wordLength += word.length();
		count++;*/
	}
	//close the file
	inputFile.close();	

	//calculate the average length of all the words
	averageWordLength = wordLength / count;
	
	//set all the links, anchors, words attribute to result of vector anchors, links, words
	total_WordCount = count;
	average_WordLength = averageWordLength;
	_anchors = anchors;
	_links = links;
	_words = words;
}

std::vector<std::string> Parsing::Get_Anchors() {
	return _anchors;
}
std::vector<std::string> Parsing::Get_Links() {
	return _links;
}
std::vector<std::string> Parsing::Get_Words() {
	return _words;
}

/*
Display_Words() function will pass the vector of words, output to the console
if it see the link (contain '.dox') will out put yellow highlight color
if it see the anchor ( contian '|#') will out put cyan highlight color
*/
void Parsing::Display_Words() {
	for (std::string w : _words) {
		if (w.find(".dox") != std::string::npos) {			
			Set_Highlight( w , 14);			
		}
		else if (w.find('|#') != std::string::npos) {
			Set_Highlight( w , 3);
		}
		else {
			std::cout << w << " ";
		}
	}	
}

/* This function display amount of words, average_Wordlength, number of links and anchors*/
void Parsing::Display_Statistics() {
	std::cout << std::endl;
	std::cout << std::setw(100) << std::setfill('-') << "\n";
	std::cout << "\nThe number of words in this " << file << ": " << total_WordCount << std::endl;
	std::cout << "The average word length in this " << file << ": ";
	std::cout << std::setprecision(2) << std::fixed;	//set to 2 decimal point
	std::cout << average_WordLength << std::endl;

	//if size of anchor != 0 output the number of links
	if (_anchors.size() != 0) {
		std::cout << _anchors.size() << " anchor(s) in this " << file << std::endl;
	}
	else {
		std::cout << "There is no anchor name in this " << file << std::endl;
	}

	//if size of links != 0 output the number of links
	if (_links.size() != 0) {
		std::cout << _links.size() << " link(s) in this " << file << std::endl;
	}
	else {
		std::cout << "There is no link in this " << file << std::endl;
	}
}

//Set_Highlight() function will highlight the text with color code from 0-15
void Parsing::Set_Highlight(std::string text, int color) {
	HANDLE word = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(word, color);
	std::cout << text << " ";
	//set back to black background and white text
	SetConsoleTextAttribute(word, 15);
}