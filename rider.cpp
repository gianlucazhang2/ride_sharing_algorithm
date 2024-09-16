#include <fstream>
#include <list>
#include <string>
#include "rider.h"
//constructor
Rider::Rider(std::string first, std::string last, std::string gen, int a, std::string r_ph,
	float rate, std::string pick, float pick_lat, float pick_long, std::string drop,
	float drop_lat, float drop_long, std::string pref, std::string st, std::string d_first,
	std::string d_last, std::string d_ph) {
		first_name = first; 
		last_name = last;
		gender = gen; 
		age = a; 
		r_phone_num = r_ph; 
		rating = rate;
		pickup = pick; 
		pickup_lat = pick_lat; 
		pickup_long = pick_long; 
		dropoff = drop; 
		dropoff_lat = drop_lat; 
		dropoff_long = drop_long; 
		v_type = pref; 
		state = st; 
		driver_first = d_first; 
		driver_last = d_last; 
		driver_phone = d_ph; 
	}

//accessors
std::string Rider::getFirstName() {return first_name;} 
std::string Rider::getLastName() {return last_name;} 
std::string Rider::getPhoneR() {return r_phone_num;}
std::string Rider::getGender() {return gender;}
int Rider::getAge() {return age;}
float Rider::getRating() {return rating;} 
std::string Rider::getPickup() {return pickup;} 
float Rider::getPickLat() {return pickup_lat;}  
float Rider::getPickLong() {return pickup_long;} 
std::string Rider::getDropoff() {return dropoff;}  
float Rider::getDropLat() {return dropoff_lat;} 
float Rider::getDropLong() {return dropoff_long;} 
std::string Rider::getType() {return v_type;}  
std::string Rider::getState() {return state;}  
std::string Rider::getFirstNameD() {return driver_first;} 
std::string Rider::getLastNameD() {return driver_last;} 
std::string Rider::getPhoneD() {return driver_phone;}  

//modifiers
void Rider::setState(std::string st) {state = st;}
void Rider::setDriverFirst(std::string first) {driver_first = first;}
void Rider::setDriverLast(std::string last) {driver_last = last;}
void Rider::setDriverPhone(std::string phone) {driver_phone = phone;} 

//overload operator <<
std::ostream & operator << (std::ostream &out, const Rider &r) {
	out << r.first_name << " " << r.last_name << " " << r.gender << " " << r.age << " " << r.r_phone_num << " " << r.rating << " " << r.pickup << " " << r.pickup_lat << " " << r.pickup_long << " " << r.dropoff << " " << r.dropoff_lat << " " << r.dropoff_long << " " << r.v_type << " " << r.state << " " << r.driver_first << " " << r.driver_last << " " << r.driver_phone; 
	return out; 
}

