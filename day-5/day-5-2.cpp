#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <bits/stdc++.h>


using namespace std;

vector<string> sortPages(vector<string> pages, const vector<pair<string, string>>& rules) {
        // Ordenamiento topológico usando las reglas
        for (size_t i = 0; i < pages.size(); i++) {
            for (size_t j = 0; j < pages.size() - 1; j++) {
                bool swapped = false;
                for (const auto& rule : rules) {
                    auto curr = pages[j];
                    auto next = pages[j + 1];
                    if (curr == rule.first && next == rule.second) {
                        continue; // Está en orden correcto
                    }
                    if (curr == rule.second && next == rule.first) {
                        // Necesita intercambio
                        swap(pages[j], pages[j + 1]);
                        swapped = true;
                        break;
                    }
                }
                if (!swapped) {
                    continue;
                }
            }
        }
        return pages;
    }

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
            auto it1 = find(pages.begin(), pages.end(), rule.first);
            auto it2 = find(pages.begin(), pages.end(), rule.second);
            
            if (it1 != pages.end() && it2 != pages.end()) {
                if (distance(pages.begin(), it1) > distance(pages.begin(), it2)) {
                    valid = false;
                    break;
                }
            }
        }

        // Si el conjunto es inválido, lo ordenamos y tomamos el número del medio
        if (!valid) {
            auto sortedPages = sortPages(pages, rules);
            int middle_index = sortedPages.size() / 2;
            result += stoi(sortedPages[middle_index]);
        }
    }

    cout << "The result is: " << result << endl;

    return 0;
}