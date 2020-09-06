#include "BOOK.h"

BOOK::BOOK():name(""), author(""), publisher(""), dateofpublish(""), numberofbooks(0), cost(0) {}

string BOOK::Getname() { return name; }
void BOOK::Setname() { getline(cin, name); }

string BOOK::Getauthor() { return author; }
void BOOK::Setauthor() { getline(cin, author); }

string BOOK::Getpublisher() { return publisher; }
void BOOK::Setpublisher() { getline(cin, publisher); }

string BOOK::Getdateofpublish() { return dateofpublish; }
void BOOK::Setdateofpublish() { cin>>dateofpublish; }

int BOOK::Getnumberofbooks() { return numberofbooks; }
void BOOK::Setnumberofbooks() { cin>>numberofbooks; }

int BOOK::Getcost() { return cost; }
void BOOK::Setcost() { cin>>cost; }
