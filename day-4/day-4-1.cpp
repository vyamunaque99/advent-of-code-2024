#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class WordSearch
{
private:
    std::vector<std::string> grid;
    const std::string target = "XMAS";

    bool checkDirection(int row, int col, int dRow, int dCol)
    {
        if (row + 3 * dRow >= grid.size() || row + 3 * dRow < 0)
            return false;
        if (col + 3 * dCol >= grid[0].size() || col + 3 * dCol < 0)
            return false;

        for (int i = 0; i < 4; i++)
        {
            if (grid[row + i * dRow][col + i * dCol] != target[i])
            {
                return false;
            }
        }
        return true;
    }

public:
    WordSearch(std::vector<std::string> &input) : grid(input) {}

    // Método que busca todas las ocurrencias de "XMAS" en la matriz
    // Retorna el número total de ocurrencias encontradas
    int findAllXMAS()
    {
        // Contador para el número de ocurrencias
        int count = 0;
        // Dimensiones de la matriz
        int rows = grid.size();
        int cols = grid[0].size();

        // Vector que define las 8 direcciones posibles para buscar
        // Cada dirección es un par (dRow, dCol) que indica el
        // desplazamiento en filas y columnas
        std::vector<std::pair<int, int>> directions = {
            {0, 1},  // derecha
            {1, 0},  // abajo
            {1, 1},  // diagonal derecha-abajo
            {1, -1}, // diagonal izquierda-abajo
            {0, -1}, // izquierda
            {-1, 0}, // arriba
            {-1, 1}, // diagonal derecha-arriba
            {-1, -1} // diagonal izquierda-arriba
        };

        // Recorre cada celda de la matriz
        for (int row = 0; row < rows; row++)
        {
            for (int col = 0; col < cols; col++)
            {
                // Para cada celda, prueba todas las direcciones posibles
                for (const auto &dir : directions)
                {
                    // Si encuentra "XMAS" en la dirección actual,
                    // incrementa el contador
                    if (checkDirection(row, col, dir.first, dir.second))
                    {
                        count++;
                    }
                }
            }
        }

        return count;
    }
};

int main()
{
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

    WordSearch solver(puzzle);
    int result = solver.findAllXMAS();
    std::cout << "XMAS aparece " << result << " veces" << std::endl;

    return 0;
}