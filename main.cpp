#include <fstream>
#include <iostream>
#include <sstream>
#include <list>
#include <string>
#include <regex>
#include <cmath>
#include "driver.h"
#include "rider.h"

//driver.txt --> driver list
std::list<Driver> writeDrivers(std::string input) {
	std::list<Driver> list; 
	std::ifstream istr(input); 
	std::string line; 
	while(std::getline(istr,line)) {
		// Split the line into individual entries
		std::istringstream iss(line);
		std::string entry;
		while(iss >> entry) {
			// Add each entry to the corresponding vector
			std::string f = entry; 
			iss>>entry; 
			std::string l = entry; 
			iss>>entry; 
			std::string g = entry; 
			iss>>entry; 
			int a = stoi(entry); 
			iss>>entry; 
			std::string p = entry;
			iss>>entry; 
			float r = std::stof(entry);
			iss>>entry; 
			float la = std::stof(entry);
			iss>>entry; 
			float lo = std::stof(entry);
			iss>>entry; 
			std::string v = entry;
			iss>>entry; 
			std::string s = entry;
			iss>>entry; 
			std::string rf = entry;
			iss>>entry; 
			std::string rl = entry;
			iss>>entry; 
			std::string rp = entry; 
			Driver d(f, l, g, a, p, r, la, lo, v, s, rf, rl, rp); 
			list.push_back(d); 
		}
	}
	return list; 
}

//riders.txt --> rider list
std::list<Rider> writeRiders(std::string input) {
	std::list<Rider> list; 
	std::ifstream istr(input); 
	std::string line; 
	while(std::getline(istr,line)) {
		// Split the line into individual entries
		std::istringstream iss(line);
		std::string entry;
		while(iss >> entry) {
			// Add each entry to the corresponding vector
			std::string f = entry; 
			iss>>entry; 
			std::string l = entry; 
			iss>>entry; 
			std::string g = entry; 
			iss>>entry; 
			int a = stoi(entry); 
			iss>>entry; 
			std::string p = entry;
			iss>>entry; 
			float ra = std::stof(entry);
			iss>>entry; 
			std::string pu = entry;
			iss>>entry; 
			float pla = std::stof(entry);
			iss>>entry; 
			float plo = std::stof(entry);
			iss>>entry; 
			std::string d = entry;
			iss>>entry; 
			float dla = std::stof(entry);
			iss>>entry; 
			float dlo = std::stof(entry);
			iss>>entry; 
			std::string v = entry;
			iss>>entry; 
			std::string s = entry;
			iss>>entry; 
			std::string df = entry;
			iss>>entry; 
			std::string dl = entry;
			iss>>entry; 
			std::string dp = entry; 
			Rider r(f, l, g, a, p, ra, pu, pla, plo, d, dla, dlo, v, s, df, dl, dp); 
			list.push_back(r); 
		}
	}
	return list;
}




//checks if phone number if correct format
bool validPhone(std::string num) {
	std::regex r("[0-9]{3}-[0-9]{3}-[0-9]{4}"); 
	if (std::regex_match(num, r)) {
		return true; 
	}
	else { return false;}
}

//calculate distance between two coords
double calculateDistance(double lat1, double lon1, double lat2, double lon2) {
    const double radiusOfEarth = 6371.0; // Earth's radius in kilometers

    // convert latitude and longitude from degrees to radians
    lat1 *= M_PI / 180.0;
    lon1 *= M_PI / 180.0;
    lat2 *= M_PI / 180.0;
    lon2 *= M_PI / 180.0;

    // Haversine formula
    double dLat = lat2 - lat1;
    double dLon = lon2 - lon1;
    double a = sin(dLat / 2.0) * sin(dLat / 2.0) + cos(lat1) * cos(lat2) * sin(dLon / 2.0) * sin(dLon / 2.0);
    double c = 2.0 * atan2(sqrt(a), sqrt(1.0 - a));
    // distance in kilometers
    double distanceKM = radiusOfEarth * c;
    // convert it to distance in miles
    double distanceMiles = distanceKM * 0.621371;

    return distanceMiles;
}


//find driver based on phone number
Driver* findDriver_(std::list<Driver> drivers, std::string number) {
	std::list<Driver>::iterator d; 
	Driver* driver = NULL; 
	for (d=drivers.begin(); d != drivers.end(); ++d) {
		if ((*d).getPhoneD() == number) {
			driver = new Driver((*d)); 
		}
	}
	return driver; 
}

//find rider based on phone number
Rider* findRider(std::list<Rider> riders, std::string number) {
	std::list<Rider>::iterator r;
	Rider* rider = NULL; 
	for (r = riders.begin(); r != riders.end(); ++r) {
		if ((*r).getPhoneR() == number) {
			rider = new Rider((*r)); 
		}
	}
    return rider; 	
}


//find closest driver 
Driver* findDriver(std::list<Driver> drivers, Rider rider, double& dis) {
	std::list<Driver>::iterator d; 
	Driver* driver = NULL;
	//set minimum distance
	double min = 0.0; 
	for (d = drivers.begin(); d != drivers.end(); ++d) {
		if ((*d).getState() == "Available" && (*d).getType() == rider.getType()) {
			min = calculateDistance((*d).getLat(), (*d).getLong(), rider.getPickLat(), rider.getPickLong());
			break; 
		}
	}
	for (d = drivers.begin(); d != drivers.end(); ++d) {
		if ((*d).getState() == "Available" && (*d).getType() == rider.getType()) {
			double distance = calculateDistance((*d).getLat(), (*d).getLong(), rider.getPickLat(), rider.getPickLong()); 
			if (distance < min) {
				delete driver; 
				min = distance;
				driver = new Driver((*d));
			}
		}
	}
	dis = min; 
	return driver; 
}


int main(int argc, char *argv[]) {
	if (argc != 8) {
		exit(0); 
	}
	
	//output streams
	std::ofstream msg(argv[3]); 
	std::ofstream d_update(argv[4]);
	std::ofstream r_update(argv[5]); 
	
	//checks if phone number format is correct
	if (!validPhone(argv[6])) {
		msg<<"Phone number is invalid." << std::endl; 
		exit(0); 
	}
	
	std::string phone_number = argv[6]; 
	std::string action = argv[7]; 
	
	//write lists
	std::list<Driver> drivers = writeDrivers(argv[1]); 
	std::list<Rider> riders = writeRiders(argv[2]); 
	
	//ride request case
	if (action == "request") {
		Rider* ptr; 
		ptr = findRider(riders, phone_number); 
		if (ptr == NULL) {
			msg << "Account does not exist." << std::endl;
			delete ptr;			
			exit(0); 
		}
		Rider rider = (*ptr); 
		delete ptr; 
		if (rider.getState() == "Driver_on_the_way") {
			msg<<"You have already requested a ride and your driver is on the way to the pickup location."<<std::endl;
			exit(0); 
		}
		if (rider.getState() == "During_the_trip") {
			msg<<"You can not request a ride at this moment as you are already on a trip."<<std::endl;
			exit(0); 			
		}
		msg << "Ride requested for user " << rider.getFirstName() << ", looking for an " << rider.getType() << " vehicle."<<std::endl;
		msg << "Pick Up Location: " << rider.getPickup() << ", Drop Off Location: " << rider.getDropoff() << "."<<std::endl; 
		Driver* dptr; 
		double dis = 0.0; 
		dptr = findDriver(drivers, rider, dis); 
		if (dptr == NULL) {
			msg << "Sorry we can not find a driver for you at this moment." << std::endl;
			delete dptr; 
		}
		else {
			Driver driver = (*dptr); 
			delete dptr;  
			std::string distance = std::to_string(dis).substr(0, 3); 
			msg << "We have found the closest driver " << driver.getFirstName() << "(" << driver.getRating() << ") for you." << std::endl; 
			msg << driver.getFirstName() << " is now " << distance << " miles away from you."; 
			//update drivers.txt
			driver.setState("On_the_way_to_pickup"); 
			driver.setRiderFirst(rider.getFirstName());
			driver.setRiderLast(rider.getLastName());
			driver.setRiderPhone(rider.getPhoneR()); 
			for (Driver d: drivers) {
				if (d.getPhoneD() == driver.getPhoneD()) {
					d_update << driver << std::endl; 
				}
				else {d_update << d << std::endl;} 
			}
			//update rider.txt
			rider.setState("Driver_on_the_way"); 
			rider.setDriverFirst(driver.getFirstName()); 
			rider.setDriverLast(driver.getLastName());
			rider.setDriverPhone(driver.getPhoneD());
			for (Rider r: riders) {
				if (r.getPhoneR() == rider.getPhoneR()) {
					r_update << rider << std::endl; 
				}
				else { r_update << r << std::endl; }
			}
		}
		
	}
	
	//ride cancel case 
	if (action == "cancel") {
		Driver * ptr; 
		ptr = findDriver_(drivers, phone_number); 
		if (ptr == NULL) { //check if rider requested
			delete ptr; 
			Rider* rptr; 
			rptr = findRider(riders, phone_number);
			if (rptr == NULL) {
				delete rptr; 
				msg<<"Account does not exist." << std::endl; 
				exit(0); 
			}
			else { //cancel by rider case
				Rider rider = (*rptr); 
				delete rptr; 
				if (rider.getState() != "Driver_on_the_way") {
					msg << "You can only cancel a ride request if your driver is currently on the way to the pickup location." << std::endl;
					exit(0);
				}
				msg<<"Ride request for user " << rider.getFirstName() << " is now canceled by the user." << std::endl; 
				//update drivers.txt
				for (Driver d: drivers) {
					if (d.getPhoneD() == rider.getPhoneD()) {
						d.setState("Available"); 
						d.setRiderFirst("null"); 
						d.setRiderLast("null");
						d.setRiderPhone("null"); 
						d_update << d << std::endl; 
					}
					else {d_update << d << std::endl;}
				}
				//update riders.txt
				std::list<Rider>::iterator r; 
				for (r=riders.begin(); r != riders.end(); ++r) {
					if ((*r).getPhoneR() == rider.getPhoneR()) {
						r = riders.erase(r); 
						r--; 
					}
					else {
						r_update << (*r) << std::endl; 
					}
				}
			}
		}
		else { //cancel by driver case
			Driver driver = (*ptr); 
			delete ptr;
			if (driver.getState() != "On_the_way_to_pickup") {
				msg<<"You can only cancel a ride request if you are currently on the way to the pickup location." << std::endl; 
				exit(0); 
			}
			//find driver's rider
			Rider* ptrr; 
			ptrr = findRider(riders, driver.getPhoneR()); 
			Rider rider = (*ptrr);
			delete ptrr; 
			msg << "Your driver " << driver.getFirstName() << " has cancelled the ride request. We will now find a new driver for you." << std::endl;
			msg << "Ride requested for user " << rider.getFirstName() << ", looking for a " << rider.getType() << " vehicle." << std::endl;
			msg << "Pick Up Location: " << rider.getPickup() << ", Drop Off Location: " << rider.getDropoff() << "."<<std::endl; 
			Driver* dptr; 
			double dis = 0.0; 
			dptr = findDriver(drivers, rider, dis); 
			if (dptr == NULL) {
				msg << "Sorry we can not find a driver for you at this moment." << std::endl;
				delete dptr; 
			}
			else {
				Driver new_driver = (*dptr); 
				delete dptr; 
				std::string distance = std::to_string(dis).substr(0, 3); 
				msg << "We have found the closest driver " << new_driver.getFirstName() << "(" << new_driver.getRating() << ") for you." << std::endl; 
				msg << new_driver.getFirstName() << " is now " << distance << " miles away from you."; 
				//update drivers.txt
				new_driver.setState("On_the_way_to_pickup"); 
				new_driver.setRiderFirst(rider.getFirstName());
				new_driver.setRiderLast(rider.getLastName());
				new_driver.setRiderPhone(rider.getPhoneR()); 
				driver.setState("Available");
				driver.setRiderFirst("null");
				driver.setRiderLast("null");
				driver.setRiderPhone("null");
				for (Driver d: drivers) {
					if (d.getPhoneD() == new_driver.getPhoneD()) {
						d_update << new_driver << std::endl; 
					}
					else if (d.getPhoneD() == driver.getPhoneD()) {
						d_update << driver << std::endl; 
					}
					else {d_update << d << std::endl;} 
				}
				//update rider.txt
				rider.setState("Driver_on_the_way"); 
				rider.setDriverFirst(new_driver.getFirstName()); 
				rider.setDriverLast(new_driver.getLastName());
				rider.setDriverPhone(new_driver.getPhoneD());
				for (Rider r: riders) {
					if (r.getPhoneR() == rider.getPhoneR()) {
						r_update << rider << std::endl; 
					}
					else { r_update << r << std::endl; }
				}
			}
		}
		
		
		
		
		
		
	}
	
	return 0; 
}