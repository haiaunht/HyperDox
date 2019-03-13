#ifndef  _Searching_H_
#define _Searching_H_
#include <string>
#include <vector>
#include <fstream>
#include "Parsing.h"

/*
Class Searching will contain functions:
	+ load files, set and get current file
	+ RemovePuntuation to remove punct in vector word to match which what user enter
	+ searchWord: to search the word in vector words and find the match with its position

*/
class Searching {
private:
	unsigned int count = 0;
	std::string currentFile;
	
public:
	void LoadFiles(std::string directoryPath, std::vector<std::string*>& fileList);	
	void Set_CurrentFile(std::string file);
	std::string Get_CurrentFile();
	std::string RemovePunctuation(std::string& s);
	void searchWord(std::vector<std::string> words, std::string search);
	std::string toLowerCase(std::string& word);
	void Set_Highlight(std::string text, int color);
	void Contents_Statistics(std::vector<Parsing> parse_Files, std::string fileName);
	void Words_Searching(std::vector<Parsing> parse_Files, std::string wordSearch);
	void HyperLinks(std::vector<Parsing> parse_Files, std::string fileName);
	void Search_For_Link(std::vector<Parsing> parse_Files, std::vector<std::string> linkName, int searchLink);
};


#endif // ! _Searching_H_


