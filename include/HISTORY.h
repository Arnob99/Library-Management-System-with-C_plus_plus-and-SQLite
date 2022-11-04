#ifndef HISTORY_H
#define HISTORY_H

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

class HISTORY
{
public:
    string username;
    int book_id;

    HISTORY();

    int Getid();
    void Setid();

    string Getusername();
    void Setusername();

    int Getbook_id();
    void Setbook_id();

    string Gettype();
    void Settype();

    int Getnumber_of_books();
    void Setnumber_of_books();

    string Getstarting_date();
    void Setstarting_date();

    string Getstopping_date();
    void Setstopping_date();

private:
    int id;
    string type;
    int number_of_books;
    string starting_date;
    string stopping_date;
};

#endif // HISTORY_H
