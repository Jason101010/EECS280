// p1-stats.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Project UID 5366c7e2b77742d5b2142097e51561a5

#include <iostream>
#include "stats.h"
#include "p1_library.h"

using namespace std;

int main()
{
    string filename;
    string column_name;
    cout << "enter a filename" << endl;
    cin >> filename;
    cout << "enter a column name" << endl;
    cin >> column_name;
    cout << "reading column " << column_name << " from " << filename << endl;

    vector<double> col = extract_column(filename, column_name);

    cout << "Summary (value: frequency)" << endl;
    vector<pair<double, int>> summary = summarize(col);
    for (int i = 0; i < summary.size(); ++i) {
        cout << summary[i].first << ": " << summary[i].second << endl;
    }
    cout << "count = " << count(col) << endl;
    cout << "sum = " << sum(col) << endl;
    cout << "mean = " << mean(col) << endl;
    cout << "stdev = " << stdev(col) << endl;
    cout << "median = " << median(col) << endl;
    cout << "mode = " << mode(col) << endl;
    cout << "min = " << min(col) << endl;
    cout << "max = " << max(col) << endl;
    cout << "  0th percentile = " << percentile(col, 0.0) <<endl;
    cout << " 25th percentile = " << percentile(col, 0.25) << endl;
    cout << " 50th percentile = " << percentile(col, 0.5) << endl;
    cout << " 75th percentile = " << percentile(col, 0.75) << endl;
    cout << "100th percentile = " << percentile(col, 1.0) << endl;
       
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
