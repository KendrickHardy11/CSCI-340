/* 	Kendrick Hardy
	z1945923
	CSCI 340-2

	I certify that this is my own work and where appropriate an extension 
	of the starter code provided for the assignment.
*/
#include "twosearch.h"

#include <getopt.h>

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <string>


/**
* see: 
* https://en.wikipedia.org/wiki/Usage_message
* https://www.ibm.com/docs/en/aix/7.2?topic=commands-usage-statements
*
* @param a0 The value of argv[0] (the name of the command) so that it 
*   can be printed.
*
* @note This function will terminate the application via exit(1).
******************************************************************************/
static void usage(const char *a0)
{
    std::cerr << "Usage: " << a0 << " [-l rand_low] [-h rand_high] [-a a_size] [-b b_size] [-x a_seed] [-y b_seed] [-c print_cols] [-w col_width]" << std::endl;
    std::cerr << "    rand_low   = rand() low bound (default=1)" << std::endl;
    std::cerr << "    rand_high  = rand() high bound (default=1000)" << std::endl;
    std::cerr << "    a_size     = size of vector A (default=200)" << std::endl;
    std::cerr << "    b_size     = size of vector B (default=100)" << std::endl;
    std::cerr << "    a_seed     = random seed for vector A (default=1)" << std::endl;
    std::cerr << "    b_seed     = random seed for vector B (default=3)" << std::endl;
    std::cerr << "    print_cols = number of colums per line (default=16)" << std::endl;
    std::cerr << "    col_width  = printed column value width (default=4)" << std::endl;
    exit(1);
} // End of usage()

/**
*Initializes a vector of ints, each int is randomized
*
* @param vec is a vector of ints that stores the random numbers provided by the  rand function
* @param seed is an int that is used to initialize the srand function, vector A and B have their own seed
* @param lo is an int that is the minimum number that random int can be
* @param hi is an int that is the maximum number that the random int can be
*
* ****************************************************************************************************************/
void init_vector(std::vector<int> &vec, int seed, int lo, int hi){

	srand(seed);

	for(size_t i = 0; i < vec.size(); i++){
		vec[i] = rand() % (hi - lo + 1) + lo;
	}
} // End of init_vector()

/**
*sorts a vector of ints
*
* @param v is a vector of ints that is sorted by the program
*
* @Note this method uses std::sort() to sort the vector in ascending order
* **************************************************************************/
void sort_vector(std::vector<int> &v){
	sort(v.begin(), v.end());
} //end of sort_vector()

/**
 * Searches through for each element in a given vector in another given vector using a given search algorithm
 *
 * @param v1 is a vector of ints that will be searched through
 * @param v2 is a vector of ints that will provide the elements to search for in v1
 * @param p is a pointer to a bool method that will be the search algorithm
 * *********************************************************************************************************************/ 
int search_vector(const std::vector<int> &v1, const std::vector<int> &v2, bool (*p)(const std::vector<int> &, int)){
	
	int total = 0; //Total number of matching elemnts found

	for(size_t i = 0; i < v2.size(); i++){
		if(p(v1, v2[i])){
			total += 1;
		}
	}

	return total;
} //End of search_vector()

/**
 * Searches through a vector to find a matching element using the linear search algorithm
 *
 * @param v is the vector that will be searched
 * @param x is the element that the method is searching for in the vector
 *
 * @return true if matching element found or false otherwise
 *
 * @Note this method uses std::find()
 * ***************************************************************************************************/
bool linear_search(const std::vector<int> &v, int x){
	
	std::vector<int>::const_iterator it; //const interator used to iterate through vector v

	it = find(v.begin(), v.end(), x);

	if(it != v.end()){
		return true;
	}
	else{
		return false;
	}
} //End of linear_search()

/**
 * Searches through a vector to find a metching element using the binary search algorithm
 *
 * @param v is the vector that will be searched
 * @param x is the element that the method is searching for in the vector
 *
 * @return true if matching elemnt found or false otherwise
 *
 * @Note this method uses std::binary_search()
 * ***************************************************************************************************/
bool binary_search(const std::vector<int> &v, int x){
	if(std::binary_search(v.begin(), v.end(), x)){
		return true;
	}
	else{
		return false;
	}
} //End of binary_search()

/**
 * prints each element in a vector
 *
 * @param v is the vector that will be printed
 * @param print_cols is the maximimum number of columns to be printed in each row
 * @param col_width the width of each column
 *
 * @Note this method uses std::setw()
 * ******************************************************************************************/
void print_vector(const std::vector<int> &v, int print_cols, int col_width){

	int nums = 0; //number of current columns

	for(size_t i = 0; i < v.size(); ++i){
		if(nums == print_cols){
			std::cout << '|';
			std::cout << "\n";
			nums = 0;
			std::cout << '|' << std::setw(col_width) << v[i] << " ";
			nums += 1;
		}
		else if(i == v.size() - 1){
			std::cout << '|' << std::setw(col_width) << v[i] << " ";
			nums += 1;

			for(int k = nums; k <= print_cols; k++){
				std::cout << '|' << std::setw(col_width) << " " << " ";
			}
		}
		else{
			std::cout << '|' << std::setw(col_width) << v[i] << " ";
			nums += 1;
		}
	}

	std::cout << "\n";
} //End of print_vector()

/**
 * prints the percent of matching elements in vector B found in vector A
 *
 * @param found the number of elements in vectir B found in vector A
 * @param total is the size of vector B
 *
 * @Note this method uses std::fixed and std::setprecision()
 * *************************************************************************************/
void print_stat(int found, int total){
	
	double num_Successes; //Number of matching elements found
	num_Successes = (((double) found / (double) total) * 100);
	std::cout << "Percent of Successful Searches = " << std::fixed << std::setprecision(2) << num_Successes << "%" << std::endl;
} //End of print_stat()



/**
* Parse the command-line args, create and sort vector A, create vector B,
* search vector A for those elements appearing in vector B using both
* a linear and binary search, and print the hit-rate (the percentage of 
* items in B that have been located in A.)
*
* If an invalid command-line arg is encountered, print a Usage statement 
* and terminte with an exit-status of 1.
*
* @return zero
******************************************************************************/
int main(int argc, char **argv)
{
    // Demonstrate the use of getopt() to override default config parameters 
    int rand_low = 1;
    int rand_high = 1000;
    int a_size = 200;
    int b_size = 100;
    int a_seed = 1;
    int b_seed = 3;
    int print_cols = 16;
    int col_width = 4;

    int opt;
    // see: http://faculty.cs.niu.edu/~winans/CS340/2022-sp/#getopt
    while ((opt = getopt(argc, argv, "a:b:c:h:l:w:x:y:")) != -1)
    {
        switch(opt)
        {
        case 'a':
            // see https://en.cppreference.com/w/cpp/string/basic_string/stol
            a_size = std::stoi(optarg); // override the default for a_size
            break;

        case 'b':
            b_size = std::stoi(optarg);
            break;
        case 'c':
            print_cols = std::stoi(optarg);
            break;
        case 'h':
            rand_high = std::stoi(optarg);
            break;
        case 'l':
            rand_low = std::stoi(optarg);
            break;
        case 'w':
            col_width = std::stoi(optarg);
            break;
        case 'x':
            a_seed = std::stoi(optarg);
            break;
        case 'y':
            b_seed = std::stoi(optarg);
            break;
            
        default:
            // got an arg that is not recognized...
            usage(argv[0]);     // pass the name of the program so it can print it
        }
    }

    // Make sure there are not any more arguments (after the optional ones)
    if (optind < argc)
        usage(argv[0]);

    std::vector<int> A(a_size); 
    std::vector<int> B(b_size);

    init_vector(A, a_seed, rand_low, rand_high); //initializes vector A
    init_vector(B, b_seed, rand_low, rand_high); //initializes vector B

    std::cout << "A vector: \n" << std::endl;

    //prints dashes above columns
    for(int i = 0; i < print_cols; i++){
	    for(int j = 0; j < (col_width + 2); j++){
		    std::cout << '-';
	    }
    }
    std::cout << '-' << std::endl;

    print_vector(A, print_cols, col_width); //prints vector A

    //prints dashes below columns
    for(int i = 0; i < print_cols; i++){
	    for(int j = 0; j < (col_width + 2); j++){
		    std::cout << '-';
	    }
    }
    std::cout << '-' << std::endl << std::endl;

    sort_vector(A); //sorts vector A

    std::cout << "A vector sorted: \n" << std::endl;

    //prints dashes above columns
    for(int i = 0; i < print_cols; i++){
	    for(int j = 0; j < (col_width + 2); j++){
		    std::cout << '-';
	    }
    }
    std::cout << '-' << std::endl;

    print_vector(A, print_cols, col_width); //prints vector A(again)

    //prints dashes below columns
    for(int i = 0; i < print_cols; i++){
	    for(int j = 0; j < (col_width + 2); j++){
		    std::cout << '-';
	    }
    }
    std::cout << '-' << std::endl << std::endl;;

    std::cout << "B vector: \n" << std::endl;
    
    //prints dashes above columns
    for(int i = 0; i < print_cols; i++){
	    for(int j = 0; j < (col_width + 2); j++){
		    std::cout << '-';
	    }
    }
    std::cout << '-' << std::endl;

    print_vector(B, print_cols, col_width); // prints vector B

    //prints dashes below columns
    for(int i = 0; i < print_cols; i++){
	    for(int j = 0; j < (col_width + 2); j++){
		    std::cout << '-';
	    }
    }
    std::cout << '-' << std::endl << std::endl;

    int successes = search_vector(A, B, linear_search); //searches for element in vector A and stores result in successes

    std::cout << "Linear Search: ";
    print_stat(successes, b_size); //prints percent of matching elements found

    successes = search_vector(A, B, binary_search); //searches for element in vector A(again)

    std::cout << "Binary Search: ";
    print_stat(successes, b_size); //prints percemt of matching elements found


    return 0;

} // End of main()

