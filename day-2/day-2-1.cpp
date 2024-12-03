#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

bool comp_asc(int a, int b)
{
    return a < b;
}

bool comp_desc(int a, int b)
{
    return a > b;
}

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

int main(){
    int result = 0;
    ifstream file("input.txt");
    // String to store each line of the file.
    string line;
    // Arrays of locations

    if (file.is_open()){
        // Read each line from the file and store it in the
        // 'line' variable.
        while (getline(file, line))
        {
            string delimiter = " ";
            vector<string> line_string = split(line, delimiter);
            vector<int> line_int;
            for (int i = 0; i < line_string.size(); i++){
                line_int.push_back(stoi(line_string[i]));
            }
            if (is_sorted(line_int.begin(), line_int.end(), comp_asc) || is_sorted(line_int.begin(), line_int.end(), comp_desc)){
                int cant_asc_desc=0;
                for (int i = 0; i < line_int.size()-1; i++){
                    if(abs(line_int[i+1]-line_int[i])>=1 && abs(line_int[i+1]-line_int[i])<=3)cant_asc_desc++;
                }
                if (cant_asc_desc==line_int.size()-1) result++;
            }
        }
        file.close();
    }
    else{
        // Print an error message to the standard error
        // stream if the file cannot be opened.
        cerr << "Unable to open file!" << endl;
    }

    cout << "Result: " << result << endl;
}