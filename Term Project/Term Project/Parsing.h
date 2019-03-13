#pragma once
#ifndef _Parsing_h
#define _Parsing_h

#include <list>
#include <string>
#include <vector>

/*Parsing class will pass each loaded file in Parsing() function and store :
	- statistics ( total words count, averagelength )
	- anchor list
	- link list
	- vector of words
	- set highligh of the wanted text
*/
class Parsing {
private:	
	std::string file; //file name 
	std::vector<std::string> _anchors;//anchor tags
	std::vector<std::string> _links; //links tags
	std::vector<std::string> _words; // words search information
	unsigned total_WordCount;	//total words counted
	float average_WordLength;	//average of all the words length

public:
	Parsing(std::string fileName) { file = fileName;  };
	void Set_FileName( std::string fileName ) {
		file = fileName;
	}
	std::string Get_FileName() {
		return file;
	};
	void Get_Statistic(std::string file);
	void Display_Words();
	void Display_Statistics();
	std::vector<std::string> Get_Anchors();
	std::vector<std::string> Get_Links();
	std::vector<std::string> Get_Words();
	void Set_Highlight(std::string text, int color);
};


#endif // !Parsing_h


