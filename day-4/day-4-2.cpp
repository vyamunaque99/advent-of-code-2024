#include <iostream>
#include <vector>
#include <string>
#include <fstream>


using namespace std;

class XMASFinder {
private:
    vector<string> grid;
    
    bool checkMAS(const string& str) {
        return str == "MAS" || str == "SAM";
    }
    
    bool isValidXMAS(int row, int col) {
        if (row < 1 || row >= grid.size() - 1 || 
            col < 1 || col >= grid[0].size() - 1) {
            return false;
        }
        
        string diag1 = string() + 
                      grid[row-1][col-1] + 
                      grid[row][col] + 
                      grid[row+1][col+1];
        
        string diag2 = string() + 
                      grid[row-1][col+1] + 
                      grid[row][col] + 
                      grid[row+1][col-1];
        
        return (checkMAS(diag1) && checkMAS(diag2)) ||
               (checkMAS(diag1) && checkMAS(string(diag2.rbegin(), diag2.rend()))) ||
               (checkMAS(string(diag1.rbegin(), diag1.rend())) && checkMAS(diag2)) ||
               (checkMAS(string(diag1.rbegin(), diag1.rend())) && 
                checkMAS(string(diag2.rbegin(), diag2.rend())));
    }

public:
    XMASFinder(const vector<string>& input) : grid(input) {}
    
    int countXMAS() {
        int count = 0;
        for (int row = 1; row < grid.size() - 1; row++) {
            for (int col = 1; col < grid[0].size() - 1; col++) {
                if (grid[row][col] == 'A' && isValidXMAS(row, col)) {
                    count++;
                }
            }
        }
        return count;
    }
};

int main() {
    std::vector<std::string> puzzle;
    std::string line;
    ifstream file("input.txt");

    if (file.is_open())
    {
        // Read each line from the file and store it in the
        // 'line' variable.
        while (getline(file, line))
        {
            if (line.empty())
                break;
            puzzle.push_back(line);
        }
        file.close();
    }
    else
    {
        // Print an error message to the standard error
        // stream if the file cannot be opened.
        cerr << "Unable to open file!" << endl;
    }
    
    XMASFinder finder(puzzle);
    int result = finder.countXMAS();
    cout << "Se encontraron " << result << " X-MAS" << endl;
    
    return 0;
}