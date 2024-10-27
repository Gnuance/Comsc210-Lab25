/*
    Lab 25: Which data structure is fastest? In each race, the contestants (a vector, list, and set) will all compete against each other.
        1. There will be four various races! Write a program that will time, record, and report how long it takes each contestant to run these four races:
            a. The first race is READING. The challenge is to read the 20,000 data elements into each of these data structures: vector, list, set
            b. The second race is SORTING. Sort the vector and sort the list. Set the set's value to -1 since a set is already sorted.
            c. The third race is INSERTING. Insert the value "TESTCODE" into the middle of the vector or the middle of the list, or into the set
            d. The fourth race is DELETING. Delete the middle-ish element of the vector, the list, or the set
        2. Use the cool time features of the <chrono> library. You'll just be using a stopwatch on these operations.
    Requirements:
        1. Make your code scalable. It should be simple to add new races.
*/

#include <iostream>
#include <chrono>
// required data classes
#include <vector>
#include <list>
#include <set>
#include <fstream> // read data from file
using namespace std;
using namespace std::chrono; // so chrono:: doesn't have to be used over and over again

// templated function to read data into whatever container is passed. may not be best option for assignment, but we'll see
template <typename T>
void ReadDataInto(T &, const string);

int main()
{
    // file to read data from
    const string FILE_NAME = "codes.txt";
    ifstream inputFile(FILE_NAME);
    // initialize data containers
    vector<string> vecCodes = {};
    list<string> listCodes = {};
    set<string> setCodes = {};
    // to hold race times
    int times[4][3] = {{0}};
    // timer
    high_resolution_clock::time_point start;
    high_resolution_clock::time_point end;


    // guard statement in case input file doesn't open
    if (!inputFile)
    {
        cout << "ERROR: Opening " << FILE_NAME << ": File cannot be opened." << endl;
        return 1;
    }



    return 0;
}

template <typename T>
void ReadDataInto(T &container, const string fileName)
{
}

/* syntax examples:
auto start = high_resolution_clock::now()
auto end = high_resolution_clock::now()
auto duration = duration_cast<milliseconds>(end - start)
duration.count() references elapsed milliseconds
*/