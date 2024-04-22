//============================================================================
// Name        : VectorSorting.cpp
// Author      : Alexa Szlykowicz
// Version     : 1.0
// Copyright   : Copyright © 2017
// Description : Vector Sorting Algorithms
//============================================================================

#include <algorithm>
#include <iostream>
#include <time.h>

//#include "CSVparser.hpp"
#include "CSVparser.h"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations
double strToDouble(string str, char ch);

// define a structure to hold bid information
struct Bid {
    string bidId; // unique identifier
    string title;
    string fund;
    double amount;

    Bid() {
        amount = 0.0;
    }
};

//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information to the console (std::out)
 *
 * @param bid struct containing the bid info
 */
void displayBid(Bid bid) {
    cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | "
         << bid.fund << endl;
    return;
}

/**
 * Prompt user for bid information using console (std::in)
 *
 * @return Bid struct containing the bid info
 */
Bid getBid() {
    Bid bid;

    cout << "Enter Id: ";
    cin.ignore();
    getline(cin, bid.bidId);

    cout << "Enter title: ";
    getline(cin, bid.title);

    cout << "Enter fund: ";
    cin >> bid.fund;

    cout << "Enter amount: ";
    cin.ignore();
    string strAmount;
    getline(cin, strAmount);
    bid.amount = strToDouble(strAmount, '$');

    return bid;
}

/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
vector<Bid> loadBids(string csvPath) {
    cout << "Loading CSV file " << csvPath << endl;

    // Define a vector data structure to hold a collection of bids.
    vector<Bid> bids;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    try {
        // loop to read rows of a CSV file
        for (int i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the collection of bids
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            //cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;

            // push this bid to the end
            bids.push_back(bid);
        }
    } catch (csv::Error &e) {
        std::cerr << e.what() << std::endl;
    }
    return bids;
}

// FIXME (2a): Implement the quick sort logic over bid.title - DONE

/**
 * Partition the vector of bids into two parts, low and high
 *
 * @param bids Address of the vector<Bid> instance to be partitioned
 * @param begin Beginning index to partition
 * @param end Ending index to partition
 */
int partition(vector<Bid> &bids, int begin, int end) {
    //set low and high equal to begin and end
    int low = begin;
    int high = end;
    bool done = false;

    // pick the middle element as pivot point

    Bid pivot = bids.at(low + (high - low) / 2);

    // while not done
    while (!done) {
        // keep incrementing low index while bids[low] < bids[pivot]
        while (bids[low].title < pivot.title) {
            ++low;
        }
        // keep decrementing high index while bids[pivot] < bids[high]
        while (pivot.title < bids[high].title) {
            --high;
        }
        /* If there are zero or one elements remaining,
        all bids are partitioned. Return high */
        if (low >= high) {
            done = true;

        } else {
            Bid tempHolder = bids[low];
            bids[low] = bids[high];
            bids[high] = tempHolder;

            // move low and high closer ++low, --high
            ++low;
            --high;
        }

    }
    return high;
}

/**
 * Perform a quick sort on bid title
 * Average performance: O(n log(n))
 * Worst case performance O(n^2))
 *
 * @param bids address of the vector<Bid> instance to be sorted
 * @param begin the beginning index to sort on
 * @param end the ending index to sort on
 */
void quickSort(vector<Bid> &bids, int begin, int end) {
    //set mid equal to 0
    int mid = 0;

    /* Base case: If there are 1 or zero bids to sort,
     partition is already sorted otherwise if begin is greater
     than or equal to end then return*/
    if (begin >= end) {
        return;
    }
    /* Partition bids into low and high such that
     midpoint is location of last element in low */
    mid = partition(bids, begin, end);

    // recursively sort low partition (begin to mid)
    quickSort(bids, begin, mid);

    // recursively sort high partition (mid+1 to end)
    quickSort(bids, mid + 1, end);

}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

/**
 * The one and only main() method
 */
int main(int argc, char *argv[]) {

    // process command line arguments
    string csvPath;
    switch (argc) {
        case 2:
            csvPath = argv[1];
            break;
        default:
            //csvPath = "eBid_Monthly_Sales_Dec_2016.csv";
            csvPath = "eBid_Monthly_Sales.csv";
    }

    // Define a vector to hold all the bids
    vector<Bid> bids;

    // Define a timer variable
    clock_t ticks;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load Bids" << endl;
        cout << "  2. Display All Bids" << endl;
        cout << "  3. Quick Sort All Bids" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

            case 1:
                // Initialize a timer variable before loading bids
                ticks = clock();

                // Complete the method call to load the bids
                bids = loadBids(csvPath);

                cout << bids.size() << " bids read" << endl;

                // Calculate elapsed time and display result
                ticks = clock() - ticks; // current clock ticks minus starting clock ticks
                cout << "time: " << ticks << " clock ticks" << endl;
                cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

                break;

            case 2:
                // Loop and display the bids read
                for (int i = 0; i < bids.size(); ++i) {
                    displayBid(bids[i]);
                }
                cout << endl;

                break;

                // FIXME (2b): Invoke the quick sort and report timing results
            case 3:
                ticks = clock();
                // Method call to perform quick sort
                quickSort(bids, 0, bids.size() - 1);
                for (int i = 0; i < bids.size(); ++i) {
                    displayBid(bids[i]);
                }
                cout << endl;
                ticks = clock() - ticks;
                cout << "time: " << ticks << " clock ticks" << endl;
                cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
                break;

        }
    }

    cout << "Good bye." << endl;

    return 0;
}
