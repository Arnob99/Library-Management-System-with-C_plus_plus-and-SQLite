#ifndef BOOK_H
#define BOOK_H

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

class BOOK
{
public:
    BOOK();

    int Getid();
    void Setid();

    string Getname();
    void Setname();

    string Getauthor();
    void Setauthor();

    string Getpublisher();
    void Setpublisher();

    string Getdateofpublish();
    void Setdateofpublish();

    int Getnumberofbooks();
    void Setnumberofbooks();

    int Getcost();
    void Setcost();

private:
    int id;
    string name;
    string author;
    string publisher;
    string dateofpublish;
    int numberofbooks;
    int cost;
};

#endif // BOOK_H
