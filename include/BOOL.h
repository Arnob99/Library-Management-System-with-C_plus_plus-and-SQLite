#ifndef BOOL_H
#define BOOL_H

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

class BOOL
{
    public:
        BOOL();
        bool admin_exists, admin_created, admin_logged_in;
        bool user_logged_in, user_is_unique;
        bool particular_object_found, book_is_unique;
};

#endif // BOOL_H
