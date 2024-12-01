#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

std::vector<std::string> split(std::string s, std::string delimiter)
{
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos)
    {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }

    res.push_back(s.substr(pos_start));
    return res;
}

int main()
{
    int result=0;
    ifstream file("input.txt");
    // String to store each line of the file.
    string line;
    // Arrays of locations
    vector<int> location_1;
    vector<int> location_2;

    if (file.is_open())
    {
        // Read each line from the file and store it in the
        // 'line' variable.
        while (getline(file, line))
        {
            string delimiter = "   ";
            vector<string> line_string = split(line, delimiter);
            vector<int> line_int={stoi(line_string[0]),stoi(line_string[1])};
            location_1.push_back(line_int[0]);
            location_2.push_back(line_int[1]);
        }
        file.close();
    }
    else
    {
        // Print an error message to the standard error
        // stream if the file cannot be opened.
        cerr << "Unable to open file!" << endl;
    }
    // Location 1 and 2 have same size
    int location_size=location_1.size();
    // Sorting arrays
    sort(location_1.begin(),location_1.end());
    sort(location_2.begin(),location_2.end());
    
    for(int i=0;i<location_size;i++){
        int distance=abs(location_1[i]-location_2[i]);
        result+=distance;
    }
    cout<<"Result: "<<result<<endl;
}