#ifndef PERSON_H
#define PERSON_H

#include<bits/stdc++.h>
#include<thread>
#include<chrono>
#define pi              acos(-1)
#define ll              long long
#define ld              long double
#define gcd             __gcd
#define bitscount       __builtin_popcount
#define ff              first
#define ss              second
#define MAXX            1e18
#define MAX             *max_element
#define MIN             *min_element
#define FastRead        ios_base::sync_with_stdio(false);cin.tie(NULL)
//__builtin_popcount()  -->  counts how many 1 s are in a binary represented integer
//accumulate() --> finds sum of an array of integers
using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

class PERSON
{
public:
    PERSON();

    string Getname();
    void Setname();

    string Getusername();
    void Setusername();

    string Getpassword();
    void Setpassword();

    int Gettype();
    void Settype();

    string Getdepartment();
    void Setdepartment();

    string Getcontact();
    void Setcontact();

    string Getemail();
    void Setemail();

private:
    string name;
    string username;
    string password;
    int type;
    string department;
    string contactnumber;
    string email;
};

#endif // PERSON_H
