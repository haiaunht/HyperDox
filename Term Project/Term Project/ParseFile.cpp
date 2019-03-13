#include "pch.h"
#include "Parsing.h"
#include <iostream>
#include <iomanip>


void ParseFile::set_Stat_file(std::string readFromFile, std::string writeToFile) {
	//file = readFromFile;
	std::ifstream inputFile;
	inputFile.open(readFromFile);

	std::ofstream outputFile{ writeToFile };
	std::vector<std::string> words;
	std::vector<std::string> anchors;
	std::vector<std::string> links;
	std::string word, anchorName, linkName;
	unsigned int count = 0;
	double wordLength = 0;
	double averageWordLength = 0;

	if (!inputFile) {
		std::cerr << "Error open top file file!";
		//return 1; //return 1 to aleat there is a problem
	}
	/*user while loop to find anchor name which is between symbol |# name |
	**and store anchor name in vector "anchors"
	**and find link name which is between symbol | name :| and store in link vector
	*/
	while (!inputFile.eof()) {
		inputFile >> word;

		//find the name embeded between !# name |
		if (word.find('|#') != std::string::npos) {
			//anchorSymbol = word.find('|#');
			anchorName = word.substr(word.find('|#') + 1, word.length() - 3);
			anchors.push_back(anchorName);
		}

		//find the name embeded between !name :|
		else if (word.find(".dox") != std::string::npos) {
			//linkSymbol = word.find('.dox');
			linkName = word.substr(1, word.find('.dox') + 3);
			links.push_back(linkName);
			std::cout << "can it reach here";
		}

		//push every word into words vector
		words.push_back(word);
		wordLength += word.length();
		count++;
	}

	inputFile.close();
	//output all the word of the file out to the console
	for (std::string w : words)
		outputFile << w << " ";
	std::cout << std::endl;

	//calculate the average length of all the words
	averageWordLength = wordLength / count;

	//output number of words, average word length
	outputFile << "\n" << std::setw(100) << std::setfill('-') << "\n";
	outputFile << "\nThe number of words in this " << readFromFile << ": " << count << std::endl;
	outputFile << "The average word length in this " << readFromFile << ": ";
	outputFile << std::setprecision(2) << std::fixed;
	outputFile << averageWordLength << std::endl;


	if (links.size() != 0) {
		std::cout << " I am here";
		outputFile << "Link name in this " << readFromFile << " is:";
		for (std::string l : links)
			outputFile << l << std::endl;
	}
	else {
		outputFile << "There is no link in this " << readFromFile << std::endl;
	}

	//find any word has embeded by symbol |# name | and extract the name
	if (anchors.size() != 0) {
		outputFile << "Anchor name in this " << readFromFile << " is: ";
		for (std::string a : anchors)
			outputFile << a << std::endl;
	}
	else {
		outputFile << "There is no anchor name in this " << readFromFile << std::endl;
	}

	outputFile.close();
	output_Statistics = writeToFile;

}

std::string ParseFile::get_Stat_File() {
	return output_Statistics;
}
