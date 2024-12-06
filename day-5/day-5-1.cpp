#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <bits/stdc++.h>


using namespace std;

// Mover split fuera de main
vector<string> split(const string& str, char delim) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(str);
    while (getline(tokenStream, token, delim)) {
        tokens.push_back(token);
    }
    return tokens;
}

int main()
{
    int result = 0;
    std::vector<std::string> page_orders, page_numbers;
    std::string line;
    ifstream file("input.txt");
    bool change_page = false;

    if (file.is_open())
    {

        // 'line' variable.
        while (getline(file, line))
        {
            if (line.empty())
            {
                change_page = true;
            }
            else
            {
                if (!change_page)
                    page_orders.push_back(line);
                else
                    page_numbers.push_back(line);
            }
        }
        file.close();
    }
    else
    {
        // Print an error message to the standard error
        // stream if the file cannot be opened.
        cerr << "Unable to open file!" << endl;
    }


    vector<pair<string, string>> rules;
    
    // Procesar las reglas de ordenamiento
    for (const auto& order : page_orders) {
        auto parts = split(order, '|');
        rules.push_back({parts[0], parts[1]});
    }

    // Validar cada conjunto de páginas
    for (const auto& numbers : page_numbers) {
        auto pages = split(numbers, ',');
        bool valid = true;
        
        // Verificar cada regla aplicable
        for (const auto& rule : rules) {
            // Encontrar posiciones de las páginas en la regla
            auto it1 = find(pages.begin(), pages.end(), rule.first);
            auto it2 = find(pages.begin(), pages.end(), rule.second);
            
            // Si ambas páginas están presentes, verificar el orden
            if (it1 != pages.end() && it2 != pages.end()) {
                if (distance(pages.begin(), it1) > distance(pages.begin(), it2)) {
                    valid = false;
                    break;
                }
            }
        }
        if(valid){
            if (!pages.empty()) {
                int middle_index = pages.size() / 2;
                result += stoi(pages[middle_index]);
            }
        }
        
    }

    cout << "The result is: " << result << endl;

    return 0;
}