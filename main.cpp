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
    if(argc == 2)
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


    string line;    //buffer for first line in file
    ifstream rawFile;   //input file
    string file ="[v5]convert-";
    rawFile.open(argv[1]);
    if(rawFile.fail())
    {
        cout<<"Brak pliku lub nie mozna go otworzyc. \n"
        << "Sprawdz czy program i plik sa w tym samym katalogu lub czy sciezka do pliku jest prawidlowa";
        return 3;
    }

    getline(rawFile,line);
    cout<<"Ilosc alleli: "<<count(line.begin(),line.end(),'\t')-3<<'\n';

    Sample sample;
    ofstream saveFile(file+argv[1]); //output file

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

