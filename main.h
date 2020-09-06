#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include<bits/stdc++.h>
#include "sqlite3.h"
#include "PERSON.h"
#include "BOOK.h"
#include "BOOL.h"
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

enum class STATE{GOODBYE, SIGN_IN, MAIN_MENU};

int maximum_number_of_object = 0;
sqlite3 *DB = nullptr;
const char* database = "Library_Management_System.db";
char *error_message;
string loginusername, loginpassword;
PERSON person;
BOOK book;
BOOL flag;
STATE state;

void splash_screen();
void check_admin_exists();
void first_time();
void create_admin();
void initialize();
void sign_in_page();
void log_in();
int callback_for_login(void *notused, int argc, char **argv, char **azcolname);
void sign_up();
int check_unique_user(string s);
void show_home();
void show_all_books();
int callback_for_count_objects(void *notused, int argc, char **argv, char **azcolname);
int callback_for_all_books(void *notused, int argc, char **argv, char **azcolname);
void show_details_of_particular_book(ll b_id);
int callback_for_details_of_book(void *notused, int argc, char **argv, char **azcolname);
void issue_book(int b_id);
void modify_info_of_book(int b_id);
int callback_for_modify_book(void *notused, int argc, char **argv, char **azcolname);
void delete_book(int b_id);
void search_for_book();
void add_book();
void check_unique_book();
int callback_for_check_unique_book(void *notused, int argc, char **argv, char **azcolname);
void show_all_members();
int callback_for_all_members(void *notused, int argc, char **argv, char **azcolname);
void show_details_of_particular_member(string username);
int callback_for_details_of_member(void *notused, int argc, char **argv, char **azcolname);
void delete_member(string s);
void search_for_member();
void show_history();
int callback_for_all_history(void *notused, int argc, char **argv, char **azcolname);
void show_details_of_particular_history(ll h_id);
int callback_for_details_of_history(void *notused, int argc, char **argv, char **azcolname);
void goodbye_screen();

void splash_screen() /// just a splash screen
{
    system("cls");

    cout<<endl<<endl;
    cout<<"         \\\\-----------------------****-----------------------//"<<endl;
    cout<<"         //                                                  \\\\"<<endl;
    cout<<"         \\\\     WELCOME TO THE LIBRARY MANAGEMENT SYSTEM     //"<<endl;
    cout<<"         //                                                  \\\\"<<endl;
    cout<<"         \\\\-----------------------****-----------------------//"<<endl;
    cout<<endl<<endl;

    sqlite3_open(database, &DB); /// opening sqlite database
    sleep_for(seconds(3));
}

void check_admin_exists()
{
    /// there will be only one admin, so this function checks if the only admin exists or not

    string sql = "SELECT * FROM ADMINTABLE LIMIT 1";

    auto err = sqlite3_exec(DB, sql.c_str(), NULL, NULL, &error_message);

    if(err != SQLITE_OK)
        flag.admin_exists = 0; /// no table, no admin
    else{
        flag.admin_exists = 1; /// there is a table, so there is an admin
        flag.admin_created = 1; /// there is a table, so admin is already created
    }

    return;
}

void first_time()
{
    system("cls");

    /// these are just some funny interface

    cout<<endl<<endl;
    cout<<"                                   HELLO!                        "<<endl;

    sleep_for(seconds(1));
    cout<<endl;

    cout<<"                     I AM INITIATED FOR THE FIRST TIME!          "<<endl;
    cout<<"             I NEED ONE ADMIN ON WHOSE HANDS MY MEMORY DEPENDS!  "<<endl;

    sleep_for(seconds(3));
    cout<<endl;

    cout<<"                    IF YOU ARE MY ADMIN, PLEASE REGISTER!        "<<endl;
    cout<<"                  PLEASE BE CAREFUL OF WHAT YOU WANT TO BE!      "<<endl;
    cout<<"               YOU WILL BE MY ONLY ADMIN, NO ONE ELSE WILL BE!   "<<endl;

    sleep_for(seconds(4));
    cout<<endl;

    cout<<"                     IF YOU WANT TO EXIT, PRESS 'Y' NOW.         "<<endl;
    cout<<"                    IF YOU WANT TO CONTINUE, PRESS ENTER.        "<<endl;
    cout<<endl;
    cout<<"                                      ";

    char c = getchar();
    if(c == 'y' || c == 'Y'){
        flag.admin_created = 0;
        return;
    }

    cout<<"                       SO, YOU ARE MY PRECIOUS ADMIN!            "<<endl;
    cout<<"                CHOOSE YOUR USERNAME AND PASSWORD CAREFULLY!     "<<endl;

    sleep_for(seconds(3));

    /// because its first time, an admin will be created and some other things will be initialized

    create_admin();
    initialize();

    return;
}

void create_admin()
{
    system("cls");

    cout<<endl<<endl;
    cout<<"               CHOOSE YOUR USERNAME AND PASSWORD CAREFULLY!      "<<endl;
    cout<<endl<<endl;
    cout<<"         USERNAME : ";   person.Setusername();
    cout<<"         PASSWORD : ";   person.Setpassword();

    /// only one admin and one table for admin

    string sql = "CREATE TABLE ADMINTABLE("
                        "USERNAME VARCHAR2(15) PRIMARY KEY, "
                        "PASSWORD VARCHAR2(20) NOT NULL) ";

    auto err = sqlite3_exec(DB, sql.c_str(), NULL, NULL, &error_message);

    if(err != SQLITE_OK)
        cout<<"         ERROR! "<<error_message<<endl;

    sql = "INSERT INTO ADMINTABLE "
                "VALUES ('" + person.Getusername() +
                "', '" + person.Getpassword() +
                "')"; /// admin username and password stored

    err = sqlite3_exec(DB, sql.c_str(), NULL, NULL, &error_message);

    if(err != SQLITE_OK)
        cout<<"         ERROR! "<<error_message<<endl;
    else
        flag.admin_created = 1; /// admin has just been created

    cout<<endl;
    cout<<"                       ADMIN CREATED SUCCESSFULLY!               "<<endl;
    cout<<endl;
    getchar();
    cout<<"                         PRESS ENTER TO CONTINUE!                "<<endl;
    cout<<"                                     ";
    getchar();

    return;
}

void initialize()
{
    /// for simple implementation, password is stored in different table

    string sql = "CREATE TABLE IF NOT EXISTS USERSTABLE("
                        "USERNAME VARCHAR2(15) PRIMARY KEY, "
                        "PASSWORD VARCHAR2(20) NOT NULL) ";

    auto err = sqlite3_exec(DB, sql.c_str(), NULL, NULL, &error_message);

    if(err != SQLITE_OK)
        cout<<"         ERROR! "<<error_message<<endl;

    /// all the personal info is stored in this table

    sql = "CREATE TABLE IF NOT EXISTS PERSONSTABLE( "
                "NAME VARCHAR2(30), "
                "USERNAME VARCHAR2(15), "
                "TYPE INT, "
                "DEPARTMENT VARCHAR2(5), "
                "CONTACT VARCHAR2(20), "
                "EMAIL VARCHAR2(30), "
                "FOREIGN KEY(USERNAME) REFERENCES USERSTABLE(USERNAME) ON DELETE CASCADE)";

    err = sqlite3_exec(DB, sql.c_str(), NULL, NULL, &error_message);

    if(err != SQLITE_OK)
        cout<<"         ERROR! "<<error_message<<endl;

    /// initializes table for books and transaction history

    sql = "CREATE TABLE IF NOT EXISTS BOOKS("
                "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
                "NAME TEXT,"
                "AUTHOR_NAME TEXT, "
                "PUBLISHER TEXT, "
                "DATE_OF_PUBLISHING TEXT, "
                "NUMBER_OF_BOOKS INTEGER, "
                "COST INTEGER)";

    err = sqlite3_exec(DB, sql.c_str(), NULL, NULL, &error_message);

    if(err != SQLITE_OK)
        cout<<"         ERROR! "<<error_message<<endl;

    sql = "CREATE TABLE IF NOT EXISTS HISTORY("
                "HISTORY_ID INTEGER PRIMARY KEY AUTOINCREMENT,"
                "USERNAME VARCHAR2(15), "
                "BOOK_ID INTEGER, "
                "TYPE TEXT, "
                "NUMBER_OF_BOOKS INTEGER, "
                "DATE TEXT, "
                "TOTAL_COST INTEGER)";

    err = sqlite3_exec(DB, sql.c_str(), NULL, NULL, &error_message);

    if(err != SQLITE_OK)
        cout<<"         ERROR! "<<error_message<<endl;
}

void sign_in_page()
{
    system("cls");

    flag.user_logged_in = 0;

    cout<<endl<<endl;
    cout<<"         CHOOSE ONE OPTION :                                     "<<endl;
    cout<<endl;
    cout<<"             1. Log In                                           "<<endl;
    cout<<"             2. Sign Up                                          "<<endl;
    cout<<endl;
    cout<<"             0. Exit                                             "<<endl;
    cout<<endl;
    cout<<"         >>> ";
    ll i;
    while(cin>>i){
        if(i>=0 && i<=2)
            break;
        cout<<"         INVALID INPUT!                                          "<<endl;
        cout<<endl;
        cout<<"         >>> ";
    }
    if(i == 1)
        log_in();
    else if(i == 2)
        sign_up();
    else if(i == 0){
        state = STATE::GOODBYE;
        return;
    }
}

void log_in()
{
    system("cls");

    cout<<endl<<endl;
    cout<<"                                   LOGIN                         "<<endl;
    cout<<endl;
    cout<<"         USERNAME : ";   cin>>loginusername;
    cout<<"         PASSWORD : ";   cin>>loginpassword;
    getchar();
    cout<<endl<<endl;

    flag.admin_logged_in = 0;

    /// checks the login username in the admintable first

    string sql = "SELECT * FROM ADMINTABLE "
                        "WHERE USERNAME = '" + loginusername +
                        "' AND PASSWORD = '" + loginpassword +
                        "'";

    auto err = sqlite3_exec(DB, sql.c_str(), callback_for_login, NULL, &error_message);

    if(err != SQLITE_OK)
        cout<<"         ERROR! "<<error_message<<endl;

    if(flag.user_logged_in)
        flag.admin_logged_in = 1;
    else{
        /// if the login username is not found in admintable, checks in userstable

        sql = "SELECT * FROM USERSTABLE "
                    "WHERE USERNAME = '" + loginusername +
                    "' AND PASSWORD = '" + loginpassword +
                    "'";

        err = sqlite3_exec(DB, sql.c_str(), callback_for_login, NULL, &error_message);

        if(err != SQLITE_OK)
            cout<<"         ERROR! "<<error_message<<endl;
    }

    if(flag.user_logged_in){
        cout<<"                                 LOGGED IN!                      "<<endl;
        state = STATE::MAIN_MENU;
    }
    else
        cout<<"                   USERNAME OR PASSWORD DOES NOT MATCH!          "<<endl;

    cout<<endl;
    cout<<"                         PRESS ENTER TO CONTINUE!                "<<endl;
    cout<<"                                     ";
    getchar();
}

int callback_for_login(void *notused, int argc, char **argv, char **azcolname) /// checks for login username in table and matches login password
{
    for(int i=0; i<argc; i+=2){
        if(loginusername == argv[i]){
            /// if username matches then this username is not free to new sign ups
            /// user_is_unique flag is used in check_unique_user function

            flag.user_is_unique = 0;

            if(loginpassword == argv[i+1]){
                flag.user_logged_in = 1;
                break;
            }
        }
    }

    return 0;
}

void sign_up()
{
    system("cls");

    cout<<endl<<endl;
    cout<<"                                  SIGN UP                        "<<endl;
    cout<<endl;
    cout<<"                    TYPE '0'(ZERO) ANYWHERE TO GO BACK!          "<<endl;
    /// user may want to go back any time
    /// so whenever '0' is entered, it will go back to main menu

    loginusername = "";
    loginpassword = "";

    cout<<endl;
    getchar();
    cout<<"         NAME            : "; person.Setname();
    if(person.Getname() == "0")
        return;
    cout<<"         USERNAME        : "; person.Setusername();
    if(person.Getusername() == "0")
        return;

    /// until an username is not unique, user cannot create his account

    while(!check_unique_user(person.Getusername())){
        cout<<endl;
        cout<<"         THAT USERNAME IS ALREADY TAKEN! "<<endl<<endl;
        cout<<"         USERNAME        : "; person.Setusername();
        if(person.Getusername() == "0")
            return;
    }

    cout<<"         PASSWORD        : "; person.Setpassword();
    if(person.Getpassword() == "0"){
        return;
    }
    cout<<"         CONFIRM PASSWORD: "; cin>>loginpassword;
    if(loginpassword == "0")
        return;

    while(loginpassword != person.Getpassword()){
        cout<<endl;
        cout<<"         PASSWORD IS NOT CONFIREMD CORRECTLY! "<<endl<<endl;
        cout<<"         PASSWORD        : "; person.Setpassword();
        if(person.Getpassword() == "0")
            return;
        cout<<"         CONFIRM PASSWORD: "; cin>>loginpassword;
        if(loginpassword == "0")
            return;
    }
    cout<<endl;

    /// i didnt actually implement anything different for student and teacher

    cout<<"         WHICH ONE ARE YOU ?"<<endl<<endl;
    cout<<"             1. Student"<<endl;
    cout<<"             2. Teacher"<<endl;
    cout<<endl;
    while(true){
        cout<<"         >>> "; person.Settype();
        if(person.Gettype() == 0)
            return;
        if(person.Gettype() != 2 && person.Gettype() != 1)
            cout<<"         INVALID CHOICE! PLEASE CHOOSE AGAIN! "<<endl<<endl;
        else
            break;
    }

    cout<<endl;
    cout<<"         DEPARTMENT      : "; person.Setdepartment();
    if(person.Getdepartment() == "0")
        return;
    cout<<"         CONTACT NO.     : "; person.Setcontact();
    if(person.Getcontact() == "0")
        return;
    cout<<"         EMAIL           : "; person.Setemail();
    if(person.Getemail() == "0")
        return;
    cout<<endl<<endl;

    /// storing username and password

    string sql = "INSERT INTO USERSTABLE "
                        "VALUES ('" + person.Getusername() +
                        "', '" + person.Getpassword() +
                        "')";

    auto err = sqlite3_exec(DB, sql.c_str(), NULL, NULL, &error_message);

    if(err != SQLITE_OK)
        cout<<"         ERROR! "<<error_message<<endl;

    /// storing personal info

    sql = "INSERT INTO PERSONSTABLE "
                "VALUES('" + person.Getname() +
                "', '" + person.Getusername() +
                "', " + to_string(person.Gettype()) +
                ", '" + person.Getdepartment() +
                "', '" + person.Getcontact() +
                "', '" + person.Getemail() +
                "')";

    err = sqlite3_exec(DB, sql.c_str(), NULL, NULL, &error_message);

    if(err != SQLITE_OK)
        cout<<"         ERROR! "<<error_message<<endl;

    getchar();
    cout<<endl;
    cout<<"                         SIGNED UP SUCCESSFULLY!                 "<<endl;
    cout<<endl;
    cout<<"                        PRESS ANY KEY TO CONTINUE!               "<<endl;
    cout<<"                                    ";
    getchar();
    return;
}

int check_unique_user(string s)
{
    /// checks if the intended username is unique in admintable

    loginusername = s;
    flag.user_is_unique = 1;

    string sql = "SELECT * FROM ADMINTABLE "
                        "WHERE USERNAME = '" + loginusername +
                        "'";

    auto err = sqlite3_exec(DB, sql.c_str(), callback_for_login, NULL, &error_message);

    if(err != SQLITE_OK)
        cout<<"         ERROR! "<<error_message<<endl;

    if(flag.user_is_unique){
        /// if username is unique in admintable, checks if the username is unique in usertable
        sql = "SELECT * FROM USERSTABLE "
                    "WHERE USERNAME = '" + s +
                    "'";

        err = sqlite3_exec(DB, sql.c_str(), callback_for_login, NULL, NULL);

        if(err != SQLITE_OK)
            cout<<"         ERROR! "<<error_message<<endl;
    }

    return flag.user_is_unique;
}

void show_home()
{
    system("cls");
    cout<<endl<<endl;
    cout<<"                                  WELCOME!                       "<<endl;
    cout<<endl;
    cout<<"         CHOOSE ONE OPTION : "<<endl;
    cout<<endl;
    cout<<"             1. SHOW ALL THE BOOKS AVAILABLE                     "<<endl;
    cout<<"             2. SEARCH FOR A BOOK                                "<<endl;
    if(flag.admin_logged_in){
        /// if admin logs in, then these options are shown

        cout<<"             3. ADD A BOOK                                       "<<endl;
        cout<<"             4. SHOW ALL THE MEMBERS                             "<<endl;
        cout<<"             5. SEARCH FOR A MEMBER                              "<<endl;
        cout<<"             6. SHOW HISTORY                                     "<<endl;
    }
    cout<<endl;
    cout<<"             0. SIGN OUT                                         "<<endl;
    cout<<endl;
    cout<<"         >>> ";

    ll i;
    while(cin>>i){
        if(i>=0 && i<=2)
            break;
        else if(i>=3 && i<=6 && flag.admin_logged_in)
            break;
        else{
            cout<<"         INVALID INPUT!"<<endl;
            cout<<"         >>> ";
        }
    }

    if(i == 1)
        show_all_books();
    else if(i == 2)
        search_for_book();
    else if(i == 3)
        add_book();
    else if(i == 4)
        show_all_members();
    else if(i == 5)
        search_for_member();
    else if(i == 6)
        show_history();
    else if(i == 0){
        flag.admin_logged_in = 0; /// even if admin did not login, when signs out, anyone including admin is logged out
        state = STATE::SIGN_IN;
        return;
    }
}

void show_all_books()
{
    ll limit = 0, pages = 0;
    maximum_number_of_object = 0;

    string sql = "SELECT COUNT(ID) FROM BOOKS";

    auto err = sqlite3_exec(DB, sql.c_str(), callback_for_count_objects, NULL, &error_message);

    if(err != SQLITE_OK)
        cout<<"         ERROR! "<<error_message<<endl;

    pages = maximum_number_of_object/20;
    if(maximum_number_of_object%20 || pages == 0)
        pages++;

    while(true){
        system("cls");

        cout<<endl<<endl;
        cout<<"                                  BOOKS                          "<<endl;
        cout<<endl;
        cout<<left<<"         "<<setw(5)<<"ID"<<"  "<<setw(25)<<"NAME"<<"  "<<setw(20)<<"AUTHOR"<<endl;

        sql = "SELECT * FROM BOOKS "
                    "ORDER BY NAME LIMIT " + to_string(limit) +
                    ", 20";

        flag.particular_object_found = 0;

        err = sqlite3_exec(DB, sql.c_str(), callback_for_all_books, NULL, &error_message);

        if(err != SQLITE_OK)
            cout<<"         ERROR! "<<error_message<<endl;

        cout<<endl;
        if(limit == (pages - 1)*20)
            cout<<"                             END OF RESULTS!                     "<<endl;
        cout<<endl;
        cout<<"         SHOWING 20 RESULTS PER PAGE.                            "<<endl;
        cout<<"         SHOWING " + to_string((limit/20)+1) + " of " + to_string(pages) + " pages."<<endl;
        cout<<endl;
        cout<<"         1. PREVIOUS PAGE                      2. NEXT PAGE      "<<endl;
        cout<<"             3. GO TO A PARTICULAR PAGE                          "<<endl;
        if(flag.particular_object_found)
            cout<<"             4. SHOW DETAILS OF PARTICULAR BOOK                  "<<endl;
        cout<<endl;
        cout<<"             0. GO BACK TO MAIN MENU                             "<<endl;
        cout<<endl;
        ll i, j;
        cout<<"         YOUR CHOICE >>> ";
        while(cin>>i){
            if(i>=0 && i<=3)
                break;
            if(flag.particular_object_found && i == 4)
                break;

            cout<<"         INVALID INPUT!"<<endl;
            cout<<"         YOUR CHOICE >>> ";
        }
        if(i == 0)
            return;
        else if(i == 1)
            limit = max(0LL, limit - 20);
        else if(i == 2)
            limit = min(limit + 20, (pages - 1)*20);
        else if(i == 3){
            cout<<"         PAGE NUMBER >>> ";
            while(cin>>j){
                if(j>0 && j<=pages)
                    break;
                cout<<"         INVALID INPUT!"<<endl;
                cout<<"         PAGE NUMBER >>> ";
            }
            limit = (j - 1)*20;
        }
        else if(i == 4){
            ll b_id;
            cout<<"         BOOK ID >>> ";
            cin>>b_id;
            show_details_of_particular_book(b_id);
        }
    }

    return;
}

int callback_for_count_objects(void *notused, int argc, char **argv, char **azcolname)
{
    for(int i=0; i<argc; i++){
        if(argv[i] == NULL)
            maximum_number_of_object = 0;
        else
            maximum_number_of_object = stoi(argv[i]);
    }

    return 0;
}

int callback_for_all_books(void *notused, int argc, char **argv, char **azcolname)
{
    flag.particular_object_found = 1;

    cout<<left<<"         ";
    for(ll i=0; i<argc; i++){
        string s = argv[i];
        if(azcolname[i] == string("ID"))
            cout<<setw(5)<<s.substr(0, 5)<<"  ";
        if(azcolname[i] == string("NAME"))
            cout<<setw(25)<<s.substr(0, 25)<<"  ";
        if(azcolname[i] == string("AUTHOR_NAME"))
            cout<<setw(20)<<s.substr(0, 20)<<endl;
//        if(azcolname[i] == string("COST"))
//            cout<<endl;
    }
    return 0;
}

void show_details_of_particular_book(ll b_id)
{
    system("cls");

    cout<<endl<<endl;
    cout<<"                                 DETAILS                         "<<endl;
    cout<<endl;

    flag.particular_object_found = 0;

    string sql = "SELECT * FROM BOOKS "
                        "WHERE ID = " + to_string(b_id);

    auto err = sqlite3_exec(DB, sql.c_str(), callback_for_details_of_book, NULL, &error_message);

    if(err != SQLITE_OK)
        cout<<"         ERROR! "<<error_message<<endl;

    if(!flag.particular_object_found)
        cout<<"               SORRY, WE DO NOT HAVE ANY BOOK WITH THIS ID!      "<<endl;

    cout<<endl<<endl;
    if(flag.particular_object_found && !flag.admin_logged_in)
        cout<<"             1. ISSUE THIS BOOK                                  "<<endl;
    if(flag.particular_object_found && flag.admin_logged_in){
        cout<<"             1. MODIFY INFORMATION OF THIS BOOK                  "<<endl;
        cout<<"             2. DELETE THIS BOOK                                 "<<endl;
    }
    cout<<endl;
    cout<<"             0. GO BACK                                          "<<endl;
    cout<<endl;
    cout<<"         YOUR CHOICE >>> ";

    ll i;
    while(cin>>i){
        if(i>=0 && i<=1)
            break;
        if(flag.admin_logged_in && i == 2)
            break;
        cout<<"         INVALID INPUT!"<<endl;
        cout<<"         YOUR CHOICE >>> ";
    }

    flag.particular_object_found = 0;

    if(i == 0)
        return;
    else if(i == 1 && !flag.admin_logged_in){
        getchar();
        issue_book(b_id);
        return;
    }
    else if(i == 1 && flag.admin_logged_in)
        modify_info_of_book(b_id);
    else if(i == 2){
        cout<<"         ARE YOU SURE YOU WANT TO DELETE THIS BOOK ?             "<<endl;
        cout<<"         TYPE 'YES' TO DELETE, OTHERWISE IT WILL NOT DELETE.     "<<endl;
        cout<<endl;
        cout<<"         >>> ";
        string s;
        cin>>s;
        if(s == "YES")
            delete_book(b_id);
    }

    return;
}

int callback_for_details_of_book(void *notused, int argc, char **argv, char **azcolname)
{
    flag.particular_object_found = 1;
    for(ll i=0; i<argc; i++){
        cout<<"         "<<setw(20)<<azcolname[i];
        cout<<" : "<<argv[i]<<endl;
    }

    return 0;
}

void issue_book(int b_id)
{
    cout<<endl;

    string sql = "INSERT INTO HISTORY("
                        "USERNAME, BOOK_ID, TYPE, "
                        "NUMBER_OF_BOOKS, DATE, TOTAL_COST) "
                        "VALUES('" + loginusername +
                        "', " + to_string(b_id) +
                        ", 'ISSUE', 1, date('now'), 0)";

    auto err = sqlite3_exec(DB, sql.c_str(), NULL, NULL, &error_message);

    if(err != SQLITE_OK)
        cout<<"         ERROR! "<<error_message<<endl;

    sql = "UPDATE BOOKS "
                "SET NUMBER_OF_BOOKS = ("
                        "SELECT NUMBER_OF_BOOKS FROM BOOKS "
                        "WHERE ID = " + to_string(b_id) + ")-1 "
                "WHERE ID = " + to_string(b_id);

    err = sqlite3_exec(DB, sql.c_str(), NULL, NULL, &error_message);

    if(err != SQLITE_OK)
        cout<<"         ERROR! "<<error_message<<endl;
    else
        cout<<"                               BOOK ISSUED!                      "<<endl;

    cout<<endl;
    cout<<"                         PRESS ENTER TO CONTINUE!                "<<endl;
    cout<<"         ";
    getchar();

    return;
}

void modify_info_of_book(int b_id)
{
    system("cls");

    getchar();
    cout<<endl<<endl;
    cout<<"                                MODIFY BOOK                      "<<endl;
    cout<<endl;

    flag.particular_object_found = 0;

    string sql = "SELECT * FROM BOOKS "
                        "WHERE ID = " + to_string(b_id);

    auto err = sqlite3_exec(DB, sql.c_str(), callback_for_modify_book, NULL, &error_message);

    if(err != SQLITE_OK)
        cout<<"         ERROR! "<<error_message<<endl;

    if(flag.particular_object_found){
        cout<<endl;
        cout<<"              YOU CANNOT CHANGE THE NAME, AUTHOR, PUBLISHER      "<<endl;
        cout<<"                     AND DATE OF PUBLISHING OF A BOOK!           "<<endl;
        cout<<endl;
        cout<<"         TYPE '-1' IN THE FIELD WHICH YOU DO NOT WANT TO CHANGE! "<<endl;
        cout<<endl;
        cout<<"                    TYPE '-2' IN THE FIELD TO GO BACK!           "<<endl;
        cout<<endl;
        while(true){
            cout<<"         QUANTITY            : "; book.Setnumberofbooks();
            if(book.Getnumberofbooks() == -2)
                return;
            cout<<"         COST                : "; book.Setcost();
            if(book.Getcost() == -2)
                return;

            getchar();

            cout<<endl;
            cout<<"         IS ALL THE INFORMATION ALLRIGHT ? (Y/N)                 "<<endl;
            cout<<endl;
            cout<<"         >>> ";

            char c = getchar();
            getchar();
            if(c == 'y' || c == 'Y')
                break;
        }
        cout<<endl;

        bool f = 0;
        sql = "UPDATE BOOKS "
                    "SET ";
        if(book.Getnumberofbooks() != -1){
            f = 1;
            sql += "NUMBER_OF_BOOKS = " + to_string(book.Getnumberofbooks());
        }
        if(book.Getcost() != -1){
            if(f)
                sql += ",";
            f = 1;
            sql += "COST = " + to_string(book.Getcost());
        }
        sql += " WHERE ID = " + to_string(b_id);

        err = sqlite3_exec(DB, sql.c_str(), NULL, NULL, &error_message);

        if(err != SQLITE_OK)
            cout<<"         ERROR! "<<error_message<<endl;
        else
            cout<<"                         BOOK INFORMATION UPDATED!               "<<endl;
    }
    else{
        cout<<"               SORRY, WE DID NOT FIND ANY BOOK WITH THIS ID!     "<<endl;
    }
    cout<<endl;
    cout<<"                         PRESS ENTER TO CONTINUE!                "<<endl;
    cout<<"                                     ";
    getchar();

    return;
}

int callback_for_modify_book(void *notused, int argc, char **argv, char **azcolname)
{
    flag.particular_object_found = 1;

    return 0;
}

void delete_book(int b_id)
{
    string sql = "INSERT INTO HISTORY("
                        "USERNAME, BOOK_ID, TYPE, "
                        "NUMBER_OF_BOOKS, DATE, TOTAL_COST) "
                        "VALUES('" + loginusername +
                        "', " + to_string(b_id) +
                        ", 'DELETE', -1, date('now'), 0)";

    auto err = sqlite3_exec(DB, sql.c_str(), NULL, NULL, &error_message);

    if(err != SQLITE_OK)
        cout<<"         ERROR! "<<error_message<<endl;

    sql = "DELETE FROM BOOKS "
                        "WHERE ID = " + to_string(b_id);

    err = sqlite3_exec(DB, sql.c_str(), NULL, NULL, &error_message);

    cout<<endl;
    if(err != SQLITE_OK)
        cout<<"         ERROR! "<<error_message<<endl;
    else
        cout<<"         DELETED BOOK!                                           "<<endl;
    cout<<endl;
    getchar();
    cout<<"                         PRESS ENTER TO CONTINUE!                "<<endl;
    cout<<"                                     ";
    getchar();
}

void search_for_book()
{
    system("cls");

    getchar();

    cout<<endl<<endl;
    cout<<"                                  SEARCH                         "<<endl;
    cout<<endl;
    cout<<"                 YOU DONT NEED TO MATCH THE WHOLE NAME :)        "<<endl;
    cout<<endl;
    cout<<"         BOOK NAME : "; book.Setname();

    cout<<endl;
    cout<<left<<"         "<<setw(5)<<"ID"<<"  "<<setw(25)<<"NAME"<<"  "<<setw(20)<<"AUTHOR"<<endl;
    cout<<endl;

    string sql = "SELECT * FROM BOOKS "
                        "WHERE NAME LIKE '%" + book.Getname() + "%'";

    flag.particular_object_found = 0;

    auto err = sqlite3_exec(DB, sql.c_str(), callback_for_all_books, NULL, &error_message);

    if(err != SQLITE_OK)
        cout<<"         ERROR! "<<error_message<<endl;

    if(!flag.particular_object_found)
        cout<<"         SORRY, WE DO NOT HAVE ANY BOOK WITH THIS NAME!          "<<endl;
    cout<<endl;
    if(flag.particular_object_found)
        cout<<"             1. SHOW DETAILS OF A PARTICULAR BOOK                    "<<endl;
    flag.particular_object_found = 0;
    cout<<"             0. GO BACK TO MAIN MENU                             "<<endl;
    cout<<endl;
    cout<<"         YOUR CHOICE >>> ";
    ll i;
    while(cin>>i){
        if(i>=0 && i<=1)
            break;

        cout<<"         INVALID INPUT!"<<endl;
        cout<<"         YOUR CHOICE >>> ";
    }
    if(i == 0)
        return;
    else if(i == 1){
        ll b_id;
        cout<<"         BOOK ID >>> ";
        cin>>b_id;
        show_details_of_particular_book(b_id);
    }

    return;
}

void add_book()
{
    system("cls");

    cout<<endl<<endl;
    cout<<"                                 ADD BOOK                        "<<endl;
    cout<<endl;
    cout<<"                    TYPE '0'(ZERO) ANYWHERE TO GO BACK!          "<<endl;
    cout<<"                     JUST DON'T MAKE ANY BOOK FREE! :)           "<<endl;
    cout<<endl;
    while(true){
        getchar();

        cout<<"         NAME                : "; book.Setname();
        if(book.Getname() == "0")
            return;
        cout<<"         AUTHOR              : "; book.Setauthor();
        if(book.Getauthor() == "0")
            return;
        cout<<"         PUBLISHER           : "; book.Setpublisher();
        if(book.Getpublisher() == "0")
            return;
        cout<<"         DATE OF PUBLISHING  : "; book.Setdateofpublish();
        if(book.Getdateofpublish() == "0")
            return;
        cout<<"         QUANTITY            : "; book.Setnumberofbooks();
        if(book.Getnumberofbooks() == 0)
            return;
        cout<<"         COST                : "; book.Setcost();
        if(book.Getcost() == 0)
            return;

        getchar();

        cout<<endl;
        cout<<"         IS ALL THE INFORMATION ALLRIGHT ? (Y/N)                 "<<endl;
        cout<<endl;
        cout<<"         >>> ";

        char c = getchar();
        getchar();
        if(c == 'y' || c == 'Y')
            break;
    }
    cout<<endl;

    flag.book_is_unique = 1;

    check_unique_book();

    if(flag.book_is_unique){
        maximum_number_of_object = 0;

        string sql = "SELECT MAX(ID) FROM BOOKS";

        auto err = sqlite3_exec(DB, sql.c_str(), callback_for_count_objects, NULL, &error_message);

        if(err != SQLITE_OK)
            cout<<"         ERROR! "<<error_message<<endl;

        sql = "INSERT INTO HISTORY("
                            "USERNAME, BOOK_ID, TYPE, "
                            "NUMBER_OF_BOOKS, DATE, TOTAL_COST) "
                            "VALUES('" + loginusername +
                            "', " + to_string(maximum_number_of_object + 1) +
                            ", 'BUY', " + to_string(book.Getnumberofbooks()) +
                            ", date('now'), " + to_string(book.Getnumberofbooks() * book.Getcost()) + ")";

        err = sqlite3_exec(DB, sql.c_str(), NULL, NULL, &error_message);

        if(err != SQLITE_OK)
            cout<<"         ERROR! "<<error_message<<endl;

        sql = "INSERT INTO BOOKS("
                            "NAME, AUTHOR_NAME, PUBLISHER, "
                            "DATE_OF_PUBLISHING, NUMBER_OF_BOOKS, COST) "
                            "VALUES('" + book.Getname() +
                            "', '" + book.Getauthor() +
                            "', '" + book.Getpublisher() +
                            "', '" + book.Getdateofpublish() +
                            "', " + to_string(book.Getnumberofbooks()) +
                            ", " + to_string(book.Getcost()) +
                            ")";

        err = sqlite3_exec(DB, sql.c_str(), NULL, NULL, &error_message);

        if(err != SQLITE_OK)
            cout<<"         ERROR! "<<error_message<<endl;
        else
            cout<<"                         BOOK ADDED SUCCESSFULLY!                "<<endl;
    }
    else{
        maximum_number_of_object = 0;

        string sql = "SELECT NUMBER_OF_BOOKS FROM BOOKS "
                            "WHERE NAME = '" + book.Getname() +
                            "' AND AUTHOR_NAME = '" + book.Getauthor() +
                            "' AND PUBLISHER = '" + book.Getpublisher() +
                            "' AND COST = " + to_string(book.Getcost());

        auto err = sqlite3_exec(DB, sql.c_str(), callback_for_count_objects, NULL, &error_message);

        if(err != SQLITE_OK)
            cout<<"         ERROR! "<<error_message<<endl;

        sql = "UPDATE BOOKS "
                    "SET NUMBER_OF_BOOKS = " + to_string(maximum_number_of_object + book.Getnumberofbooks()) +
                    " WHERE NAME = '" + book.Getname() +
                    "' AND AUTHOR_NAME = '" + book.Getauthor() +
                    "' AND PUBLISHER = '" + book.Getpublisher() +
                    "' AND COST = " + to_string(book.Getcost());

        err = sqlite3_exec(DB, sql.c_str(), NULL, NULL, &error_message);

        if(err != SQLITE_OK)
            cout<<"         ERROR! "<<error_message<<endl;
        else
            cout<<"                         BOOK ADDED SUCCESSFULLY!                "<<endl;
    }
    cout<<endl;
    cout<<"         1. ADD ANOTHER BOOK                                     "<<endl;
    cout<<endl;
    cout<<"         0. GO BACK TO MENU                                      "<<endl;
    cout<<endl;
    cout<<"         YOUR CHOICE >>> ";

    ll i;
    while(cin>>i){
        if(i>=0 && i<=1)
            break;
        cout<<"         INVALID CHOICE! "<<endl;
        cout<<"         YOUR CHOICE >>> "<<endl;
    }

    if(i == 1)
        add_book();

    return;
}

void check_unique_book()
{
    string sql = "SELECT * FROM BOOKS "
                        "WHERE NAME = '" + book.Getname() +
                        "' AND AUTHOR_NAME = '" + book.Getauthor() +
                        "' AND PUBLISHER = '" + book.Getpublisher() +
                        "' AND COST = " + to_string(book.Getcost());

    auto err = sqlite3_exec(DB, sql.c_str(), callback_for_check_unique_book, NULL, &error_message);

    if(err != SQLITE_OK)
        cout<<"         ERROR! "<<error_message<<endl;
}

int callback_for_check_unique_book(void *notused, int argc, char **argv, char **azcolname)
{
    flag.book_is_unique = 0;

    return 0;
}

void show_all_members()
{
    ll limit = 0, pages = 0;
    maximum_number_of_object = 0;

    string sql = "SELECT COUNT(USERNAME) FROM PERSONSTABLE";

    auto err = sqlite3_exec(DB, sql.c_str(), callback_for_count_objects, NULL, &error_message);

    if(err != SQLITE_OK)
        cout<<"         ERROR! "<<error_message<<endl;

    pages = maximum_number_of_object/20;
    if(maximum_number_of_object%20 || pages == 0)
        pages++;

    while(true){
        system("cls");

        cout<<endl<<endl;
        cout<<"                                 MEMBERS                         "<<endl;
        cout<<endl;
        cout<<left<<"         "<<setw(25)<<"NAME"<<"  "<<setw(15)<<"USERNAME"<<"  "<<setw(10)<<"DEPARTMENT"<<endl;
        cout<<endl;

        sql = "SELECT * FROM PERSONSTABLE "
                    "ORDER BY NAME LIMIT " + to_string(limit) +
                    ", 20";

        flag.particular_object_found = 0;

        err = sqlite3_exec(DB, sql.c_str(), callback_for_all_members, NULL, &error_message);

        if(err != SQLITE_OK)
            cout<<"         ERROR! "<<error_message<<endl;

        cout<<endl;
        if(limit == (pages - 1)*20)
            cout<<"                             END OF RESULTS!                     "<<endl;
        cout<<endl;
        cout<<"         SHOWING 20 RESULTS PER PAGE.                            "<<endl;
        cout<<"         SHOWING " + to_string((limit/20)+1) + " of " + to_string(pages) + " pages."<<endl;
        cout<<endl;
        cout<<"         1. PREVIOUS PAGE                      2. NEXT PAGE      "<<endl;
        cout<<"             3. GO TO A PARTICULAR PAGE                          "<<endl;
        if(flag.particular_object_found)
            cout<<"             4. SHOW DETAILS OF PARTICULAR MEMBER                  "<<endl;
        flag.particular_object_found = 0;
        cout<<endl;
        cout<<"         0. GO BACK TO MAIN MENU                                 "<<endl;
        cout<<endl;
        ll i, j;
        cout<<"         YOUR CHOICE >>> ";
        while(cin>>i){
            if(i>=0 && i<=4)
                break;

            cout<<"         INVALID INPUT!"<<endl;
            cout<<"         YOUR CHOICE >>> ";
        }
        if(i == 0)
           return;
        else if(i == 1)
            limit = max(0LL, limit - 20);
        else if(i == 2)
            limit = min(limit + 20, (pages - 1)*20);
        else if(i == 3){
            cout<<"         PAGE NUMBER >>> ";
            while(cin>>j){
                if(j>0 && j<=pages)
                    break;
                cout<<"         INVALID INPUT!"<<endl;
                cout<<"         PAGE NUMBER >>> ";
            }
            limit = (j - 1)*20;
        }
        else if(i == 4){
            string username;
            cout<<"         USERNAME >>> ";
            cin>>username;
            show_details_of_particular_member(username);
        }
    }
}

int callback_for_all_members(void *notused, int argc, char **argv, char **azcolname)
{
    flag.particular_object_found = 1;

    cout<<left<<"         ";
    for(ll i=0; i<argc; i++){
        string s = argv[i];
        if(azcolname[i] == string("NAME"))
            cout<<setw(25)<<s.substr(0, 25)<<"  ";
        if(azcolname[i] == string("USERNAME"))
            cout<<setw(15)<<s.substr(0, 15)<<"  ";
        if(azcolname[i] == string("DEPARTMENT"))
            cout<<setw(10)<<s.substr(0, 10)<<endl;
    }

    return 0;
}

void show_details_of_particular_member(string s)
{
    system("cls");

    cout<<endl<<endl;
    cout<<"                                 DETAILS                         "<<endl;
    cout<<endl;

    flag.particular_object_found = 0;

    string sql = "SELECT * FROM PERSONSTABLE "
                        "WHERE USERNAME = '" + s + "'";

    auto err = sqlite3_exec(DB, sql.c_str(), callback_for_details_of_member, NULL, &error_message);

    cout<<endl;

    if(err != SQLITE_OK)
        cout<<"         ERROR! "<<error_message<<endl;

    if(!flag.particular_object_found)
        cout<<"           SORRY, WE DO NOT HAVE ANY MEMBER WITH THIS USERNAME!  "<<endl;
    else if(flag.particular_object_found && flag.admin_logged_in)
        cout<<"             1. DELETE THIS MEMBER                               "<<endl;

    cout<<endl;
    cout<<"             0. GO BACK TO MAIN MENU                             "<<endl;
    cout<<endl;
    cout<<"         YOUR CHOICE >>> ";
    ll i;
    while(cin>>i){
        if(flag.particular_object_found && flag.admin_logged_in && i == 1)
            break;
        if(i == 0)
            break;
    }
    if(i == 0)
        return;
    else if(i == 1){
        cout<<"         ARE YOU SURE YOU WANT TO DELETE " + s + " ?           "<<endl;
        cout<<"         TYPE 'YES' TO DELETE, OTHERWISE IT WILL NOT DELETE.     "<<endl;
        cout<<endl;
        cout<<"         >>> ";
        string c;
        cin>>c;
        if(c == "YES")
            delete_member(s);
    }

    return;
}

int callback_for_details_of_member(void *notused, int argc, char **argv, char **azcolname)
{
    flag.particular_object_found = 1;
    string s;
    for(ll i=0; i<argc; i++){
        s = argv[i];
        if(azcolname[i] == string("TYPE") && s == "1")
            s = "STUDENT";
        if(azcolname[i] == string("TYPE") && s == "2")
            s = "TEACHER";
        cout<<"         "<<setw(11)<<azcolname[i];
        cout<<" : "<<s<<endl;
    }

    return 0;
}

void delete_member(string s)
{
    cout<<s<<endl;
    /// sqlite does not support foreign keys by default, so here we enable it

    string sql = "PRAGMA FOREIGN_KEYS = ON";

    auto err = sqlite3_exec(DB, sql.c_str(), NULL, NULL, &error_message);

    if(err != SQLITE_OK)
        cout<<"         ERROR! "<<error_message<<endl;

    sql = "DELETE FROM USERSTABLE "
                "WHERE USERNAME = '" + s + "' ";

    err = sqlite3_exec(DB, sql.c_str(), NULL, NULL, &error_message);

    cout<<endl;
    if(err != SQLITE_OK)
        cout<<"         ERROR! "<<error_message<<endl;
    else
        cout<<"         DELETED MEMBER.                                         "<<endl;
    cout<<endl;
    getchar();
    cout<<"                         PRESS ENTER TO CONTINUE!                "<<endl;
    cout<<"                                     ";
    getchar();
}

void search_for_member()
{
    system("cls");

    getchar();

    cout<<endl<<endl;
    cout<<"                                  SEARCH                         "<<endl;
    cout<<endl;
    cout<<"                 YOU DONT NEED TO MATCH THE WHOLE NAME :)        "<<endl;
    cout<<endl;
    cout<<"         MEMBER NAME : "; person.Setname();

    cout<<endl;
    cout<<left<<"         "<<setw(25)<<"NAME"<<"  "<<setw(15)<<"USERNAME"<<"  "<<setw(10)<<"DEPARTMENT"<<endl;
    cout<<endl;

    string sql = "SELECT * FROM PERSONSTABLE "
                        "WHERE NAME LIKE '%" + person.Getname() + "%'";

    flag.particular_object_found = 0;

    auto err = sqlite3_exec(DB, sql.c_str(), callback_for_all_members, NULL, &error_message);

    if(err != SQLITE_OK)
        cout<<"         ERROR! "<<error_message<<endl;

    if(!flag.particular_object_found)
        cout<<"         SORRY, WE DO NOT HAVE ANY MEMBER WITH THIS NAME!        "<<endl;
    cout<<endl;
    if(flag.particular_object_found){
        cout<<"             1. SHOW DETAILS OF A PARTICULAR MEMBER              "<<endl;
        cout<<endl;
    }

    flag.particular_object_found = 0;

    cout<<"             0. GO BACK TO MAIN MENU                             "<<endl;
    cout<<endl;
    cout<<"         YOUR CHOICE >>> ";
    ll i;
    while(cin>>i){
        if(i>=0 && i<=1)
            break;
    }
    if(i == 0)
        return;
    else if(i == 1){
        string username;
        cout<<"         USERNAME >>> ";
        cin>>username;
        show_details_of_particular_member(username);
    }

    return;
}

void show_history()
{
    ll limit = 0, pages = 0;
    maximum_number_of_object = 0;

    string sql = "SELECT COUNT(ID) FROM HISTORY";

    auto err = sqlite3_exec(DB, sql.c_str(), callback_for_count_objects, NULL, &error_message);

    if(err != SQLITE_OK)
        cout<<"         ERROR! "<<error_message<<endl;

    pages = maximum_number_of_object/20;
    if(maximum_number_of_object%20 || pages == 0)
        pages++;

    while(true){
        system("cls");

        cout<<endl<<endl;
        cout<<"                                 HISTORY                         "<<endl;
        cout<<endl;
        cout<<left<<"         "<<setw(5)<<"ID"<<"  "<<setw(15)<<"USERNAME"<<"  "<<setw(7)<<"BOOK ID"<<"  "<<setw(10)<<"TYPE"<<endl;

        sql = "SELECT * FROM HISTORY "
                    "LIMIT " + to_string(limit) + ", 20";

        flag.particular_object_found = 0;

        err = sqlite3_exec(DB, sql.c_str(), callback_for_all_history, NULL, &error_message);

        if(err != SQLITE_OK)
            cout<<"         ERROR! "<<error_message<<endl;

        cout<<endl;
        if(limit == (pages - 1)*20)
            cout<<"                             END OF RESULTS!                     "<<endl;
        cout<<endl;
        cout<<"         SHOWING 20 RESULTS PER PAGE.                            "<<endl;
        cout<<"         SHOWING " + to_string((limit/20)+1) + " of " + to_string(pages) + " pages."<<endl;
        cout<<endl;
        cout<<"         1. PREVIOUS PAGE                      2. NEXT PAGE      "<<endl;
        cout<<"             3. GO TO A PARTICULAR PAGE                          "<<endl;
        if(flag.particular_object_found)
            cout<<"             4. SHOW DETAILS OF PARTICULAR HISTORY               "<<endl;
        cout<<endl;
        cout<<"             0. GO BACK TO MAIN MENU                             "<<endl;
        cout<<endl;
        ll i, j;
        cout<<"         YOUR CHOICE >>> ";
        while(cin>>i){
            if(i>=0 && i<=3)
                break;
            if(flag.particular_object_found && i == 4)
                break;

            cout<<"         INVALID INPUT!"<<endl;
            cout<<"         YOUR CHOICE >>> ";
        }
        if(i == 0)
            return;
        else if(i == 1)
            limit = max(0LL, limit - 20);
        else if(i == 2)
            limit = min(limit + 20, (pages - 1)*20);
        else if(i == 3){
            cout<<"         PAGE NUMBER >>> ";
            while(cin>>j){
                if(j>0 && j<=pages)
                    break;
                cout<<"         INVALID INPUT!"<<endl;
                cout<<"         PAGE NUMBER >>> ";
            }
            limit = (j - 1)*20;
        }
        else if(i == 4){
            ll h_id;
            cout<<"         HISTORY ID >>> ";
            cin>>h_id;
            show_details_of_particular_history(h_id);
        }
    }

    return;
}

void show_details_of_particular_history(ll h_id)
{
    system("cls");

    cout<<endl<<endl;
    cout<<"                                 DETAILS                         "<<endl;
    cout<<endl;

    flag.particular_object_found = 0;

    string sql = "SELECT * FROM HISTORY "
                        "WHERE HISTORY_ID = " + to_string(h_id);

    auto err = sqlite3_exec(DB, sql.c_str(), callback_for_details_of_history, NULL, &error_message);

    if(err != SQLITE_OK)
        cout<<"         ERROR! "<<error_message<<endl;

    if(!flag.particular_object_found)
        cout<<"               SORRY, WE DO NOT HAVE ANY BOOK WITH THIS ID!      "<<endl;

    cout<<endl<<endl;
    getchar();
    cout<<"                         PRESS ENTER TO CONTINUE!                "<<endl;
    cout<<"                                     ";
    getchar();

    return;
}

int callback_for_details_of_history(void *notused, int argc, char **argv, char **azcolname)
{
    flag.particular_object_found = 1;

    for(ll i=0; i<argc; i++){
        cout<<"         "<<setw(15)<<azcolname[i];
        cout<<" : "<<argv[i]<<endl;
    }

    return 0;
}

int callback_for_all_history(void *notused, int argc, char **argv, char **azcolname)
{
    flag.particular_object_found = 1;

    cout<<left<<"         ";
    for(ll i=0; i<argc; i++){
        string s = argv[i];
        if(azcolname[i] == string("HISTORY_ID"))
            cout<<setw(5)<<s.substr(0, 5)<<"  ";
        if(azcolname[i] == string("USERNAME"))
            cout<<setw(15)<<s.substr(0, 15)<<"  ";
        if(azcolname[i] == string("BOOK_ID"))
            cout<<setw(7)<<s.substr(0, 7)<<"  ";
        if(azcolname[i] == string("TYPE"))
            cout<<setw(10)<<s.substr(0, 10)<<endl;
    }

    return 0;
}

void goodbye_screen()
{
    system("cls");

    sqlite3_close(DB);

    cout<<endl<<endl;
    cout<<"                          THANK YOU FOR USING                    "<<endl;
    cout<<"                       LIBRARY MANAGEMENT SYSTEM                 "<<endl;
    cout<<endl;
    cout<<"         \\\\-----------------------***-----------------------// "<<endl;
    cout<<endl;
    cout<<"                              CREATED BY:                        "<<endl;
    cout<<"                    MISHAL AL RAHMAN    - 180041133              "<<endl;
    cout<<"                    TAUSIF KHAN ARNOB   - 180041138              "<<endl;
    cout<<"                    TAWRATUR RASHID     - 180041141              "<<endl;
    cout<<endl<<endl;

    return;
}


#endif // MAIN_H_INCLUDED
