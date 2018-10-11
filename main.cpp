#include <iostream>
#include <cstring>
#include <bits/stdc++.h>
#include "Sample.h"
using namespace std;

enum state
{
    END_LINE = 0,
    END_SAMPLE,
    END_FILE
};

int main(int argc, char* argv[])
{
 /*   if(argc == 2)
        if(!strcmp( argv[ 1 ], "--info" ))
        {
            cout<<"Ver 5 (11.10.2018)";
            return 0;
        }
    if(argc == 1)
    {
        cout<<"Podaj nazwe pliku *.txt";
        return 1;
    }
    if(argc != 2)
    {
        cout<<"Podaj tylko nazwe pliku np. nazwa.txt";
        return 2;
    }

    string file ="[v5]convert-";
    ifstream read;
    read.open(argv[1]);
    if(read.fail())
    {
        cout<<"Brak pliku lub nie mozna go otworzyc. \n"
        << "Sprawdz czy program i plik sa w tym samym katalogu lub czy sciezka do pliku jest prawidlowa";
        return 3;
    }
    //ofstream saveFile(file+argv[1]);
*/
    string line;    //buffer for first line in file
    ifstream rawFile;   //input file
    rawFile.open("1.txt");

    if(rawFile.fail())
    {
        cout<<"Blad odczytu - rawFile.fail() return true";
        return 1;
    }

    getline(rawFile,line);
    cout<<"Ilosc alleli: "<<count(line.begin(),line.end(),'\t')-3<<'\n';

    Sample sample;
    ofstream saveFile("work.txt");  //output file

    int status = 0;

    while(1)
    {
            status = sample.parseStream(rawFile);
        if(status == END_SAMPLE)
        {
            sample.toSave(saveFile);
            continue;
        }
        else if(status == END_FILE)
            break;
    }
    //cout<<"-----DEBUG------PLIK PRZETWORZONY\n";
    return 0;
}

