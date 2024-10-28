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
#include <iomanip> // align output
#include <cstdio>  // right align output
#include <chrono>
// required data classes
#include <vector>
#include <list>
#include <set>
#include <fstream>   // file
#include <algorithm> // sort
using namespace std;
using namespace std::chrono; // so chrono:: doesn't have to be used over and over again

// timers to be used in functions
high_resolution_clock::time_point timerStart;
high_resolution_clock::time_point timerEnd;
duration<double, milli> elapsed;

// individual race functions
vector<double> ReadRace(vector<string> &, list<string> &, set<string> &, const string);
vector<double> SortRace(vector<string> &, list<string> &, set<string> &);
vector<double> InsertRace(vector<string> &, list<string> &, set<string> &, const string);
vector<double> DeleteRace(vector<string> &, list<string> &, set<string> &);

int main()
{
    // file to read data from
    const string FILE_NAME = "codes.txt";

    vector<double> readRaceResults = {};
    vector<double> sortRaceResults = {};
    vector<double> insertRaceResults = {};
    vector<double> deleteRaceResults = {};

    // initialize data containers
    vector<string> vecCodes = {};
    list<string> listCodes = {};
    set<string> setCodes = {};
    // to hold race times
    double times[4][3] = {{0}}; // vector | list | set
    // value to insert for race 3
    const string INSERT_CODE = "TESTCODE";
    // iterators
    list<string>::iterator listIter;
    set<string>::iterator setIter;

    // off to the races
    readRaceResults = ReadRace(vecCodes, listCodes, setCodes, FILE_NAME);
    sortRaceResults = SortRace(vecCodes, listCodes, setCodes);
    insertRaceResults = InsertRace(vecCodes, listCodes, setCodes, INSERT_CODE);

    // delete race: delete middle element of containers
    timerStart = high_resolution_clock::now();
    vecCodes.erase(vecCodes.begin() + vecCodes.size() / 2);
    timerEnd = high_resolution_clock::now();
    elapsed = timerEnd - timerStart;
    times[3][0] = elapsed.count();

    timerStart = high_resolution_clock::now();
    listIter = next(listCodes.begin(), listCodes.size() / 2);
    listCodes.erase(listIter);
    timerEnd = high_resolution_clock::now();
    elapsed = timerEnd - timerStart;
    times[3][1] = elapsed.count();

    timerStart = high_resolution_clock::now();
    setIter = next(setCodes.begin(), setCodes.size() / 2);
    setCodes.erase(setIter);
    timerEnd = high_resolution_clock::now();
    elapsed = timerEnd - timerStart;
    times[3][2] = elapsed.count();

    // cout << right << setw(10) << fixed<< "Operation" << "\tVector" << "\tList" << "\tSet\n"
    //      << "Read\t" << readRaceResults.at(0) << "\t" << readRaceResults.at(1) << "\t" << readRaceResults.at(2) << "\n"
    //      << "Sort\t " << readRaceResults.at(0) << "\t" << readRaceResults.at(1) << "\t" << readRaceResults.at(2) << "\n";

    printf("%10s\t%10s\t%10s\t%10s\t\n", "Operation", "Vector", "List", "Set");
    printf("%10s\t%10f\t%10f\t%10f\t\n", "Read", readRaceResults.at(0), readRaceResults.at(1), readRaceResults.at(2));
    printf("%10s\t%10f\t%10f\t%10f\t\n", "Sort", sortRaceResults.at(0), sortRaceResults.at(1), sortRaceResults.at(2));
    printf("%10s\t%10f\t%10f\t%10f\t\n", "Insert", insertRaceResults.at(0), insertRaceResults.at(1), insertRaceResults.at(2));
    // cout << "Insert times: " << times[2][0] << " | " << times[2][1] << " | " << times[2][2] << endl;
    // cout << "Deletion times: " << times[3][0] << " | " << times[3][1] << " | " << times[3][2] << endl;

    return 0;
}

vector<double> ReadRace(vector<string> &vecCodes, list<string> &listCodes, set<string> &setCodes, const string FILE_NAME)
{
    vector<double> times = {};
    ifstream inputFile(FILE_NAME);
    string line = "";
    // guard statement in case input file doesn't open
    if (!inputFile)
    {
        cout << "ERROR: Opening " << FILE_NAME << ": File cannot be opened." << endl;
    }
    // time each container separately and reset cusor
    timerStart = high_resolution_clock::now();
    while (getline(inputFile, line))
    {
        vecCodes.push_back(line); // vector read race
    }
    timerEnd = high_resolution_clock::now();
    elapsed = timerEnd - timerStart;
    times.push_back(elapsed.count());

    // clear eof bit and reset cursor to beginning
    inputFile.clear();
    inputFile.seekg(0);

    timerStart = high_resolution_clock::now();
    while (getline(inputFile, line))
    {
        listCodes.push_back(line); // list read race
    }
    timerEnd = high_resolution_clock::now();
    elapsed = timerEnd - timerStart;
    times.push_back(elapsed.count());

    // clear eof bit and reset cursor to beginning
    inputFile.clear();
    inputFile.seekg(0);

    timerStart = high_resolution_clock::now();
    while (getline(inputFile, line))
    {
        setCodes.insert(line); // set read race
    }
    timerEnd = high_resolution_clock::now();
    elapsed = timerEnd - timerStart;
    times.push_back(elapsed.count());

    // file reading done, close stream
    inputFile.close();

    return times;
}

// sorting race, only vector and list need to be sorted
vector<double> SortRace(vector<string> &vecCodes, list<string> &listCodes, set<string> &setCodes)
{
    vector<double> times = {};
    timerStart = high_resolution_clock::now();
    sort(vecCodes.begin(), vecCodes.end());
    timerEnd = high_resolution_clock::now();
    elapsed = timerEnd - timerStart;
    times.push_back(elapsed.count());

    timerStart = high_resolution_clock::now();
    listCodes.sort();
    timerEnd = high_resolution_clock::now();
    elapsed = timerEnd - timerStart;
    times.push_back(elapsed.count());

    times.push_back(-1); // set is already sorted
    return times;
}

// insert race: place insert code into the middle of the container
// set does not allow for manual placement
vector<double> InsertRace(vector<string> &vecCodes, list<string> &listCodes, set<string> &setCodes, const string INSERT_CODE)
{
    vector<double> times = {};
    list<string>::iterator listIter;
    timerStart = high_resolution_clock::now();
    vecCodes.insert(vecCodes.begin() + vecCodes.size() / 2, INSERT_CODE);
    timerEnd = high_resolution_clock::now();
    elapsed = timerEnd - timerStart;
    times.push_back(elapsed.count());

    timerStart = high_resolution_clock::now();
    listIter = next(listCodes.begin(), listCodes.size() / 2);
    listCodes.insert(listIter, INSERT_CODE);
    timerEnd = high_resolution_clock::now();
    elapsed = timerEnd - timerStart;
    times.push_back(elapsed.count());

    timerStart = high_resolution_clock::now();
    setCodes.insert(INSERT_CODE);
    timerEnd = high_resolution_clock::now();
    elapsed = timerEnd - timerStart;
    times.push_back(elapsed.count());

    return times;
}
vector<double> DeleteRace(vector<string> &, list<string> &, set<string> &);

/* syntax examples:
auto start = high_resolution_clock::now()
auto end = high_resolution_clock::now()
auto duration = duration_cast<milliseconds>(end - start)
duration.count() references elapsed milliseconds
*/