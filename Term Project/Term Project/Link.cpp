#include "pch.h"
#include "Link.h"


void Link::Set_Link(std::vector<std::string> linkList, std::map<int, std::string> map_of_links) {
	for (int i = 0; i < linkList.size(); i++)
		map_of_links.emplace( i, linkList.at(i) );

	linkMap = map_of_links;
}

//std::map<  int, std::string> Get_Map() {
//	return linkMap;
//}
//
//std::string Get_Link( int numberofLink ) {
//	return linkMap.at( numberofLink) ;
//}