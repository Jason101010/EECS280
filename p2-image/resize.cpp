// p2-cv.cpp : This file contains the 'main' function.
//Program execution begins and ends there.
//// Project UID af1f95f547e44c8ea88730dfb185559d


#include <iostream>
#include "processing.h"
#include <fstream>
#include <sstream>


using namespace std;

int main(int argc, char* argv[])
{
    if (argc != 4 && argc != 5) {
        cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
            << "WIDTH and HEIGHT must be less than or equal to original"
            << endl;
        return 1;
    }

    Image* img = new Image;
    string filename = argv[1];
    cout << filename << endl;
    ifstream fin;
    string outFile = argv[2];
    ofstream output(outFile);

    fin.open(filename);

    if (!fin.is_open()) {
        cout << "Error opening file: " << filename << endl;
        return 1;
    }

    stringstream input;
    string word;
    while (getline(fin, word)) {
        cout << word << endl;
        input << word << endl;
    }

    Image_init(img, input);

    int width = atoi(argv[3]);
    int height = atoi(argv[4]);

    if (width <= 0 || width > Image_width(img)) {
        cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
            << "WIDTH and HEIGHT must be less than or equal to original"
            << endl;
        cout << "if one" << endl;
        return 1;
    }

    if (height <= 0 || height > Image_height(img)) {
        cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
            << "WIDTH and HEIGHT must be less than or equal to original"
            << endl;
        cout << "if two" << endl;

        return 1;
    }

    seam_carve(img, width, height);
    Image_print(img, output);
    delete img;
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files,
//or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again,
//go to File > Open > Project and select the .sln file