#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <fstream>

using namespace std;

struct Position {
    int x, y;
    bool operator<(const Position& other) const {
        return x < other.x || (x == other.x && y < other.y);
    }
};

struct Guard {
    Position pos;
    char direction;  // '^', '>', 'v', '<'
};

class GuardSimulator {
private:
    std::vector<std::string> map;
    std::set<Position> visited;
    int rows, cols;

    // Verifica si una posición está dentro del mapa
    bool isInBounds(int x, int y) {
        return x >= 0 && x < rows && y >= 0 && y < cols;
    }

    // Obtiene la siguiente dirección al girar a la derecha
    char turnRight(char dir) {
        switch (dir) {
            case '^': return '>';
            case '>': return 'v';
            case 'v': return '<';
            case '<': return '^';
            default: return dir;
        }
    }

    // Obtiene la siguiente posición basada en la dirección actual
    Position getNextPosition(Position current, char dir) {
        switch (dir) {
            case '^': return {current.x - 1, current.y};
            case '>': return {current.x, current.y + 1};
            case 'v': return {current.x + 1, current.y};
            case '<': return {current.x, current.y - 1};
            default: return current;
        }
    }

public:
    GuardSimulator(std::vector<std::string>& input) : map(input) {
        rows = map.size();
        cols = map[0].size();
    }

    int simulateGuardPath() {
        // Encuentra la posición inicial del guardia
        Guard guard = {{0, 0}, '^'};
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (map[i][j] == '^') {
                    guard.pos = {i, j};
                    break;
                }
            }
        }

        // Comienza la simulación
        visited.insert(guard.pos);

        while (true) {
            Position nextPos = getNextPosition(guard.pos, guard.direction);
            
            // Verifica si el guardia sale del mapa
            if (!isInBounds(nextPos.x, nextPos.y)) {
                break;
            }

            // Si hay un obstáculo adelante, gira a la derecha
            if (map[nextPos.x][nextPos.y] == '#') {
                guard.direction = turnRight(guard.direction);
            } else {
                // Avanza a la siguiente posición
                guard.pos = nextPos;
                visited.insert(guard.pos);
            }
        }

        return visited.size();
    }
};

int main() {
    std::vector<std::string> input;
    std::string line;
    ifstream file("input.txt");
    // Lee el mapa de entrada
    while (std::getline(file, line) && !line.empty()) {
        input.push_back(line);
    }
    GuardSimulator simulator(input);
    int result = simulator.simulateGuardPath();
    std::cout << "Posiciones distintas visitadas: " << result << std::endl;

    return 0;
}