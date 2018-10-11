#ifndef SAMPLE_H_INCLUDED
#define SAMPLE_H_INCLUDED
#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <vector>


using namespace std;

class Sample
{
private:
    string sample_name; // (2)
    string sample_file; // (1)
    map<string,vector<string>> markers;

public:
    Sample(void) {}
    ~Sample() {}

    int parseStream(ifstream &);
    void toSave(ofstream &);
};


#endif // SAMPLE_H_INCLUDED
