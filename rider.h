#include <fstream>
#include <list>
#include <string>

class Rider {
public:
//constructor
	Rider(std::string first, std::string last, std::string gen, int a, std::string r_ph,
	float rate, std::string pick, float pick_lat, float pick_long, std::string drop,
	float drop_lat, float drop_long, std::string pref, std::string st, std::string d_first,
	std::string d_last, std::string d_ph); 
	
//accessors
	std::string getFirstName(); 
	std::string getLastName();
	std::string getPhoneR();
	std::string getGender();
	int getAge();
	float getRating();
	std::string getPickup();
	float getPickLat(); 
	float getPickLong();
	std::string getDropoff(); 
	float getDropLat();
	float getDropLong();
	std::string getType(); 
	std::string getState(); 
	std::string getFirstNameD(); 
	std::string getLastNameD(); 
	std::string getPhoneD(); 
	
//modifiers
	void setState(std::string st); 
	void setDriverFirst(std::string first); 
	void setDriverLast(std::string last);
	void setDriverPhone(std::string phone); 

//operator overload
	friend std::ostream & operator << (std::ostream &out, const Rider &r);
	
private: 
	std::string first_name, last_name, gender, r_phone_num, pickup, dropoff, v_type, state, driver_first, 
	driver_last, driver_phone; 
	int age; 
	float rating, pickup_lat, pickup_long, dropoff_lat, dropoff_long; 
}; 