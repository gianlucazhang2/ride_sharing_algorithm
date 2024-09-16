#include <fstream>
#include <list>
#include <string>

class Driver {
public:
//constructor
	Driver(std::string first, std::string last, std::string gen, int a, 
	std::string d_ph, float rate, float lat, float longi, std::string type, 
	std::string st, std::string r_first, std::string r_last, std::string r_ph); 
	
//accessors
	std::string getFirstName(); 
	std::string getLastName();
	std::string getPhoneD();
	int getAge();
	std::string getGender(); 
	float getRating();
	float getLat(); 
	float getLong();
	std::string getType(); 
	std::string getState(); 
	std::string getFirstNameR(); 
	std::string getLastNameR(); 
	std::string getPhoneR(); 
	
//modifiers
	void setState(std::string st); 
	void setRiderFirst(std::string first); 
	void setRiderLast(std::string last);
	void setRiderPhone(std::string phone); 
	
//operator overload
	friend std::ostream & operator << (std::ostream &out, const Driver &d);

private:
	std::string first_name, last_name, gender, d_phone_num, v_type, state, rider_first, rider_last, rider_phone; 
	int age; 
	float rating, latitude, longitude; 
};
	