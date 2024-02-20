/*	Kendrick Hardy
	z1945923
	CSCI 340-2
	I certify that this is my own work and where appropriate an extension
	of the starter code provided for the assignment.
*/

#include <iostream>
#include <deque>
#include <stack>
#include <string>

class car
{
public:
    car(int id, const std::string &license) : id(id), license(license) {}

    /// Call this to increment the number of times the car has been moved.
    void move(){
	    num_moves++;
    }

    /// @return the number of times that the car has been moved.
    int get_num_moves() const{
	    return num_moves;
    }

    /// @return A reference to the license for this car.
    const std::string &get_license() const{
	    return license;
    }

    /**
    * Overload the << so this can print itself as:
    *    Car X with license plate "Y"
    ******************************************************************/
    friend std::ostream& operator<<(std::ostream& lhs, const car& rhs){
	    lhs << "Car " << rhs.id << " with license plate \"" << rhs.license << "\"";
	    return lhs;
    }

private:
    int id;                 ///< The ID number for this car (assigned by the garage)
    std::string license;    ///< license plate of this car.
    int num_moves = {0};    ///< how many times the car was moved within the garage.
};


class garage
{
public:
        garage(size_t limit = 10) : parking_lot_limit(limit) {}

        /// @param license The license of the car that has arrived.
        void arrival(const std::string &license);

        /// @param license The license of the car that has departed.
        void departure(const std::string &license);

private:
        int next_car_id = { 1 };
        std::deque<car> parking_lot;
        size_t parking_lot_limit;
};

/**
 * Adds a car to the parking lot
 *
 * @param license The license of a given car
 * **********************************************************/
void garage::arrival(const std::string &license){
	if(parking_lot.size() != parking_lot_limit){
		car vehicle = car(next_car_id++, license);

		parking_lot.push_back(vehicle);

		std::cout << vehicle << " has arrived.\n\n";
	}
	else{
		car vehicle = car(next_car_id++, license);

		std::cout << vehicle << " has arrived,\n";
		std::cout << "    ";

		std::cout << "But the garage is full!\n\n";
	}
} //End of arrival

/**
 * Removes a car from  parking lot by searching the parking lot until it finds the car
 *
 * @param license the licence of a given car
 *
 * @note creates a stack
 * ***************************************************************************************************/
void garage::departure(const std::string &license){

	bool found = false; ///< Checks whether or not the car was found in the parking lot
	
	for(int i = 0; i < (int) parking_lot.size(); i++){
		if(parking_lot[i].get_license() == license){
			found = true;
			break;
		}
	}

	if(!found){
		std::cout << "No car with licence plate \"" << license << "\"" << " is in the garage." << std::endl;
		return;
	}

	std::stack<car> moved; ///< A stack that holds the cars that are being moved

	car vehicle = parking_lot.front(); ///< the first car in the parking lot

	while(vehicle.get_license() != license){
		moved.push(vehicle);

		parking_lot.pop_front();

		vehicle = parking_lot.front();
	}

	parking_lot.pop_front();

	while(moved.size() > 0){
		car vehicle = moved.top();
		vehicle.move();
		parking_lot.push_front(vehicle);
		moved.pop();
	}

	std::cout << vehicle << " has departed, \n    car was moved ";

	if(vehicle.get_num_moves() == 0){
		std::cout << vehicle.get_num_moves() + 1 << " time in the garage." << std::endl;
	}
	else{
		std::cout << vehicle.get_num_moves() + 1 << " times in the garage." << std::endl;
	}

	std::cout << std::endl;
} //End of departure

/**
 * Get the input from a given file
 *
 * @param line The current line of input
 * @param xact_type Corresponds to an arrival or a departure event
 * @param license The license plate number of the car
 *
 * @note uses the subtring method
 * ******************************************************************************/
void get_input_vals(const std::string &line, char &xact_type, std::string &license){
	xact_type = line[0]; ///< The act that will be taken

	license = line.substr(2, line.length() - 3); ///< the license for the car
} //End of get_input_vals

int main(){
	garage SPG; ///< The Scratchemup Parking Garage

	std::string license; ///< The car license
	std::string line; ///< The input line
	char act; ///< The action(arrival or departure)

	while(getline(std::cin, line)){
		get_input_vals(line, act, license);

		if(act == 'A'){
			SPG.arrival(license);
		}
		else if(act == 'D'){
			SPG.departure(license);
		}
		else{
			std::cout << "\'" << act << "\'" << ": invalid action!\n\n";
		}
	}
}
