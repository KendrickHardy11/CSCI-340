/*	Kendrick Hardy
	z1945923
	CSCI 340-2

	I certify that this is my own work and where appropriate an extension
	of the starter code provided for the assignment.
*/

#include "josephus.h"

#include <list>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <getopt.h>


void print_underlined_string(const std::string &message);
void print_list(const std::list<std::string> &collection, const unsigned &eliminations, int num_cols);


/**
* Print a 'Usage' message and exit(1).
*
* @param a0 The name of the command to include in the usage message.
*****************************************************************************/
static void usage(const char *a0)
{
    std::cerr << "Usage: " << a0 << " [-n number of people] [-m modulus] [-p print frequency] [-c print columns]" << std::endl;
    exit(1);
}


/**
* Create a std::list of prople with generated ID/names and reduce the
* list as per the Josephus problem algorithm.
*****************************************************************************/
int main(int argc, char **argv)
{
    unsigned num_people = 41;       // The number of people to start with
    unsigned modulus = 3;           // The count used to determine the elimination
    unsigned print_frequency = 13;  // How often to print the state of the system
    unsigned num_cols = 12;         // Number of colums to print per line

    int opt;
    while ((opt = getopt(argc, argv, "n:m:p:c:")) != -1)
    {
        switch (opt)
        {
        case 'n':
            std::istringstream(optarg) >> num_people;
            break;
        case 'm':
            std::istringstream(optarg) >> modulus;
            break;
        case 'p':
            std::istringstream(optarg) >> print_frequency;
            break;
        case 'c':
            std::istringstream(optarg) >> num_cols;
            break;
        default:
            usage(argv[0]);
        }
    }

    if (optind < argc)
        usage(argv[0]); // If we get here, there was extra junk on command line

    std::list<std::string> list; 

    std::generate_n(std::back_inserter(list), num_people, SEQ(num_people)); //generates the names inside of list

    print_list(list, 0, num_cols); //prints the initial group of names

    unsigned total_Elim = 0; /*!< The total eliminated names from the list */

    unsigned pos = 1; /*!< The position of the iterator relative to the counting distance */

    auto it = list.begin(); /*!< An iterator starting at the beginning of the list of names */

    while((int) list.size() > 1){

	    if(++it == list.end()){
		    if(pos == modulus){
			    pos = 1;
			    total_Elim += 1;
			    it = list.begin();
			    list.pop_back();

			    if(total_Elim % print_frequency == 0){
				    print_list(list, total_Elim, num_cols);
			    }
		    }
		    else if(pos < modulus){
			    pos += 1;
			    it = list.begin();
		    }
	    }
	    else{
		    --it;
	    	    if(pos == modulus){
			    it = list.erase(it);
		    	    total_Elim += 1;
		    	    pos = 1;

			    if(total_Elim % print_frequency == 0){
				    print_list(list, total_Elim, num_cols);
			    }
		    }
		    else{
			    ++it;
			    pos += 1;
		    }
	    }
    }

    std::cout << std::endl;

    const unsigned end_Elims = total_Elim;

    std::cout << std::endl;

    std::cout << "Eliminations Completed";

    print_list(list, end_Elims, num_cols); //prints the last remaining name in the list



  return 0;
}

/**
 * prints a the list of strings with a maximum number of columns
 *
 * @param collection The list that will be printed
 * @param eliminations The number of strings that are eliminated from the collection
 * @param num_cols The maximum number of columns for each print
 *
 * @note uses stringstream
 * *******************************************************************************************************/
void print_list(const std::list<std::string> &collection, const unsigned &eliminations, int num_cols){

	if(collection.size() == 1){
		std::cout << std::endl;
		std::stringstream ss;
		ss << eliminations;
		std::string newString = ss.str();
		const std::string elim_Message = "After eliminating " + newString + " people";
		print_underlined_string(elim_Message);
		for(auto e : collection){
			std::cout << e;
		}
	}
	else if(eliminations == 0){
		const std::string elim_Message = "Initial group of people";
		print_underlined_string(elim_Message);
		int nums = 0;

		for(auto e : collection){
			if(nums == num_cols - 1){
				std::cout << e;
				std::cout << "\n";
				nums = 0;
			}
			else{
				std::cout << e << ", ";
				nums += 1;
			}
		}

		std::cout << std::endl;
		std::cout << std::endl;
	}
	else{
		std::stringstream ss;
		ss << eliminations;
		std::string newString = ss.str();
		const std::string elim_Message = "After eliminationg " + newString + " people";
		print_underlined_string(elim_Message);
		int nums = 0;

		for(auto e : collection){
			if(nums == num_cols - 1){
				std::cout << e;
				std::cout << "\n";
				nums = 0;
			}
			else{
				std::cout << e << ", ";
				nums += 1;
			}
		}

		std::cout << std::endl;
		std::cout << std::endl;
	}
} //End of print_list

/**
 * Prints the underlined header before the printed list
 *
 * @param message A string containing the number of eliminated strings from the list if an were
 * eliminated
 * **********************************************************************/
void print_underlined_string(const std::string &message){
	
	std::cout << message << std::endl;

	for(size_t  i = 0; i < message.length(); i++){
		std::cout << '-';
	}

	std::cout << std::endl;
} //End of print_underlined_string
