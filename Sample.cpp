#include "Sample.h"

enum state
{
    END_LINE = 0,
    END_SAMPLE,
    END_FILE
};

int Sample::parseStream(ifstream  &file)
{
    string sample_file_buf;
    string marker_buffer;
    string data_buffer;
    vector<string> db;

    if(file)
    {
        if(sample_file.empty()) {
            getline(file, sample_file, '\t');
            //cout<<"Czy pusty sample?\n";
        }
        else
        {
            streampos _beginLine = file.tellg();        // ustala pozycje wskaznika w pliku
            getline(file, sample_file_buf, '\t');
            if(sample_file != sample_file_buf)  // czy dalej ta sama probka?
            {
                sample_file = sample_file_buf;
                streampos _endLine = file.tellg();
                file.seekg(_beginLine - _endLine, ios_base::cur); //cofa wskaznik w pliku na poczatek linii

                return END_SAMPLE;
            }

        }
        getline(file, sample_name, '\t');
        getline(file,marker_buffer,'\t');

        while(file.peek() != '\n')
        {
            getline(file,data_buffer,'\t');
            db.push_back(data_buffer);
        }
        file.ignore();

        markers.insert(pair<string,vector<string>>(marker_buffer,db));

        //cout<<"Sample File: "<< sample_file<<endl;

        return END_LINE;

    }
    else
        //cout<<"Koniec pliku!\n";
        return END_FILE;
}

void Sample::toSave(ofstream & file)
{
    /*naglowek*/
    static bool header = false;
    if(!header)
    {
        header = true;
        file<<"Nazwa probki\\Markery";
        for(auto x : markers)
            file<<'\t'<<x.first;
        file<<'\n';
    }
    file<<sample_name;

    bool nextElement = false;
    for(auto marker : markers)
    {
        file<<'\t';
        for(auto data : marker.second)
            if(data == "" || data == "OL")
                continue;
            else
            {   if(nextElement == true)
                    file<<", ";
                file<<data;
                nextElement = true;
            }
        nextElement = false;
    }
    file<<'\n';
    markers.clear();
}
