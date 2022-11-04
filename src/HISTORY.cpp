#include "HISTORY.h"

HISTORY::HISTORY():id(0), username(""), book_id(0), type(""), number_of_books(0) { }

int HISTORY::Getid() { return id; }
void HISTORY::Setid() { cin>>id; }

string HISTORY::Getusername() { return username; }
void HISTORY::Setusername() { cin>>username; }

int HISTORY::Getbook_id() { return book_id; }
void HISTORY::Setbook_id() { cin>>book_id; }

string HISTORY::Gettype() { return type; }
void HISTORY::Settype() { cin>>type; }

int HISTORY::Getnumber_of_books() { return number_of_books; }
void HISTORY::Setnumber_of_books() { cin>>number_of_books; }

string HISTORY::Getstarting_date() { return starting_date; }
void HISTORY::Setstarting_date() { cin>>starting_date; }

string HISTORY::Getstopping_date() { return stopping_date; }
void HISTORY::Setstopping_date() { cin>>stopping_date; }
