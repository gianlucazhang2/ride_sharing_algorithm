#include <fstream>
#include <list>
#include <string>
#include "driver.h"

//constructor
Driver::Driver(std::string first, std::string last, std::string gen, int a, 
	std::string d_ph, float rate, float lat, float longi, std::string type, 
	std::string st, std::string r_first, std::string r_last, std::string r_ph) {
		first_name = first; 
		last_name = last; 
		gender = gen; 
		age = a;
		d_phone_num = d_ph; 
		rating = rate;
		latitude = lat; 
		longitude = longi; 
		v_type = type; 
		state = st; 
		rider_first = r_first; 
		rider_last = r_last; 
		rider_phone = r_ph; 
	}

//accessors
std::string Driver::getFirstName() {return first_name;}
std::string Driver::getLastName() {return last_name;}
std::string Driver::getPhoneD() {return d_phone_num;}
int Driver::getAge() {return age;}
std::string Driver::getGender() {return gender;}
float Driver::getRating() {return rating;}
float Driver::getLat() {return latitude;}
float Driver::getLong() {return longitude;}
std::string Driver::getType() {return v_type;}
std::string Driver::getState() {return state;}
std::string Driver::getFirstNameR() {return rider_first;}
std::string Driver::getLastNameR() {return rider_last;}
std::string Driver::getPhoneR() {return rider_phone;}


//modifiers
void Driver::setState(std::string st) {state = st;}
void Driver::setRiderFirst(std::string first) {rider_first = first;}
void Driver::setRiderLast(std::string last) {rider_last = last;}
void Driver::setRiderPhone(std::string phone) {rider_phone = phone;}

//overload operator <<
std::ostream & operator << (std::ostream &out, const Driver &d) {
	out << d.first_name << " " << d.last_name << " " << d.gender << " " << d.age << " " << d.d_phone_num << " " << d.rating << " " << d.latitude << " " << d.longitude << " " << d.v_type << " " << d.state << " " << d.rider_first << " " << d.rider_last << " " << d.rider_phone; 
	return out; 
}

