#include "PERSON.h"

PERSON::PERSON():name(""), username(""), password(""), type(0), department(""), contactnumber(""), email("") { }

string PERSON::Getname() { return name; }
void PERSON::Setname() { getline(cin, name); }

string PERSON::Getusername(){ return username; }
void PERSON::Setusername() { cin>>username; }

string PERSON::Getpassword() { return password; }
void PERSON::Setpassword() { cin>>password; }

int PERSON::Gettype() { return type; }
void PERSON::Settype() { cin>>type; }

string PERSON::Getdepartment() { return department; }
void PERSON::Setdepartment() { cin>>department; }

string PERSON::Getcontact() { return contactnumber; }
void PERSON::Setcontact() { cin>>contactnumber; }

string PERSON::Getemail() { return email; }
void PERSON::Setemail() { cin>>email; }
