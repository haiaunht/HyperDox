#pragma once
#ifndef  Link_h
#define Link_h
#include <string>
#include <vector>
#include <map>

class Link{
private:
	std::vector<std::string> linkList;
	std::map< int, std::string > linkMap;
public:
	void Set_Link(std::vector<std::string> linkList, std::map<  int, std::string> map_of_links);
	std::map<  int, std::string> Get_Map();
	std::string Get_Link( int n );

};

#endif // ! Link_h
