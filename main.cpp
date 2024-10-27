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
#include <fstream>   // file
#include <algorithm> // sort
using namespace std;
using namespace std::chrono; // so chrono:: doesn't have to be used over and over again

// timer
high_resolution_clock::time_point timerStart;
high_resolution_clock::time_point timerEnd;
duration<double, milli> elapsed;

vector<double> ReadRace(vector<string> &, list<string> &, set<string> &, const string);
vector<double> SortRace();
vector<double> InsertRace();
vector<double> DeleteRace();

int main()
{
    // file to read data from
    const string FILE_NAME = "codes.txt";

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

    // sorting race, only vector and list need to be sorted
    timerStart = high_resolution_clock::now();
    sort(vecCodes.begin(), vecCodes.end());
    timerEnd = high_resolution_clock::now();
    elapsed = timerEnd - timerStart;
    times[1][0] = elapsed.count();

    timerStart = high_resolution_clock::now();
    listCodes.sort();
    timerEnd = high_resolution_clock::now();
    elapsed = timerEnd - timerStart;
    times[1][1] = elapsed.count();

    times[1][2] = -1; // set is already sorted

    // insert race: place insert code into the middle of the container
    // set does not allow for manual placement
    timerStart = high_resolution_clock::now();
    vecCodes.insert(vecCodes.begin() + vecCodes.size() / 2, INSERT_CODE);
    timerEnd = high_resolution_clock::now();
    elapsed = timerEnd - timerStart;
    times[2][0] = elapsed.count();

    timerStart = high_resolution_clock::now();
    listIter = next(listCodes.begin(), listCodes.size() / 2);
    listCodes.insert(listIter, INSERT_CODE);
    timerEnd = high_resolution_clock::now();
    elapsed = timerEnd - timerStart;
    times[2][1] = elapsed.count();

    timerStart = high_resolution_clock::now();
    setCodes.insert(INSERT_CODE);
    timerEnd = high_resolution_clock::now();
    elapsed = timerEnd - timerStart;
    times[2][2] = elapsed.count();

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

    cout << "Read times: " << times[0][0] << " | " << times[0][1] << " | " << times[0][2] << endl;
    cout << "Sort times: " << times[1][0] << " | " << times[1][1] << " | " << times[1][2] << endl;
    cout << "Insert times: " << times[2][0] << " | " << times[2][1] << " | " << times[2][2] << endl;
    cout << "Deletion times: " << times[3][0] << " | " << times[3][1] << " | " << times[3][2] << endl;

    return 0;
}

vector<double> ReadRace(vector<string> &vecCodes, list<string> &listCodes, set<string> &setCodes, const string FILE_NAME)
{
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
    times[0][0] = elapsed.count();

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
    times[0][1] = elapsed.count();

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
    times[0][2] = elapsed.count();

    // file reading done, close stream
    inputFile.close();
}
void SortRace();
void InsertRace();
void DeleteRace();

/* syntax examples:
auto start = high_resolution_clock::now()
auto end = high_resolution_clock::now()
auto duration = duration_cast<milliseconds>(end - start)
duration.count() references elapsed milliseconds
*/