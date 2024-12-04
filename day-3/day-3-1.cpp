#include <bits/stdc++.h>
#include <fstream>
#include <iostream>
#include <regex>
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

int main() {
  int result = 0;
  ifstream file("input.txt");
  // String to store each line of the file.
  string line;
  // Arrays of locations

  if (file.is_open()) {
    // Read each line from the file and store it in the
    // 'line' variable.
    while (getline(file, line)) {
      std::regex pattern(R"(mul\(\d+,\d+\))");
      std::smatch matches;
      while (std::regex_search(line, matches, pattern)) {
        string delimiter = ",";
        string mem_input=matches[0].str();
        mem_input=mem_input.substr(4,mem_input.size()-5);
        vector<string> line_string = split(mem_input, delimiter);
        vector<int> line_int={stoi(line_string[0]),stoi(line_string[1])};
        result=result+(line_int[0]*line_int[1]);
        line = matches.suffix()
                   .str(); // Continúa buscando en el resto de la cadena
      }
    }
    file.close();
  } else {
    // Print an error message to the standard error
    // stream if the file cannot be opened.
    cerr << "Unable to open file!" << endl;
  }

  cout << "Result: " << result << endl;
}