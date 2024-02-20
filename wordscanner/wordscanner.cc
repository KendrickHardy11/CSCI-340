/*	Kendrick Hardy
	z1945923
	CSCI 340-2
	I certify that this is my own work and where appropriate an extension
	of the starter code provided for the assignment.
*/

#include <iostream>
#include <map>
#include <utility>
#include <algorithm>
#include <string>
#include <iomanip>
#include <cctype>
#include <sstream>

/**
 * Checks if a character is a non alpha number
 *
 * @param i A character from the inital word
 * 
 * @return true or false
 *
 * @note Uses isalnum
 * ***************************************************************/
bool nonAlpha(const char& i){
       if(isalnum(i)){
	       return false;
       }
       else{
	       return true;
       }
} //End of nonAlpha

/**
 * Convert a lowercase letter to an upercase letter
 *
 * @param c A character from the clean word
 *
 * @note Uses tolower
 * *****************************************************************/
void convert(char& c){
	c = tolower(c);
	return;
} //End of convert

/**
 * Removes nonAlpha character from a word and sets all characters to lowercase if any uppercase
 *
 * @param a A string representing the initial word
 * @param b A string representing the new clean word
 *
 * @note Uses std::find_if, std::for_each, and isalnum
 * ******************************************************************************************************/
void clean_entry(const std::string &a, std::string &b){
	auto it = std::find_if(a.begin(), a.end(), isalnum);
	auto it2 = std::find_if(it, a.end(), nonAlpha);

	std::string clean_Word(it, it2);

	b = clean_Word;

	std::for_each(b.begin(), b.end(), convert);
} //End of clean_entry

/**
 * Gets words from input stream and removes punctuation marks
 *
 * @param m A map that stores words
 *
 * @note Uses istringstream
 * *************************************************************************/
void get_words(std::map<std::string, int>& m){

	std::string line;
	while(getline(std::cin, line)){
		std::istringstream iss(line);
		std::string word;
		while(iss >> word){
			const std::string initial = word;
			std::string cleanWord = word;
			clean_entry(initial, cleanWord);
			m[cleanWord]++;
		}
	}
} //End get_words

/**
 * Prints words from map
 *
 * @param m A map that stores words
 *
 * @note Uses setw
 * *******************************************************************/
void print_words(const std::map<std::string, int>& m){

	int NO_ITEMS = 4; 
	int ITEM_WORD_WIDTH = 14;
	int ITEM_COUNT_WIDTH = 3;
	int numIn = 0;
	int itemCount = 0;

	for(auto it = m.begin(); it != m.end(); ++it){
		numIn += (it->second);
		if(itemCount < ITEM_COUNT_WIDTH){
			std::cout << std::setw(ITEM_WORD_WIDTH) << std::left << it->first << " : " << std::setw(NO_ITEMS) << it->second << "\t";
			itemCount++;
		}
		else{
			std::cout << std::setw(ITEM_WORD_WIDTH) << std::left << it->first << " : " << std::setw(NO_ITEMS) << it->second << "\t\n";
			itemCount = 0;
		}
	}
	std::cout << "\n";
	std::cout << "number of words in input stream" << "  :" << numIn << std::endl;
	std::cout << "number of words in output stream" << " :" << m.size() << std::endl;
} //End of print_words

int main(){
	std::map<std::string, int> words; ///< A map that stores the words

	get_words(words); // Gets words from input stream and removes punctuation from words
	print_words(words); // Prints words from words map

	return 0;
}
