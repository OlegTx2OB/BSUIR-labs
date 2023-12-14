#include <iostream>
#include "TxtFile.h"

using namespace std;
TxtFile::TxtFile(vector<int> IDs)
{
    ofstream outputFile("txt_file.txt");
    if (outputFile.is_open())
    {
        for (const auto& id : IDs) outputFile << id << "\n"; //write into txt file
        outputFile.close();
    }
    else cout << ".txt file cannot be created\n";
}
