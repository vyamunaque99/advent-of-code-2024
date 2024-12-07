#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

struct Equation {
    long long testValue;
    std::vector<int> numbers;
};

class EquationSolver {
private:
    std::vector<Equation> equations;

    long long evaluateExpression(const std::vector<int>& numbers, const std::vector<char>& operators) {
        long long result = numbers[0];
        for (size_t i = 0; i < operators.size(); i++) {
            if (operators[i] == '+') {
                result += numbers[i + 1];
            } else if (operators[i] == '*') {
                result *= numbers[i + 1];
            }
        }
        return result;
    }

    bool canSolve(const Equation& eq) {
        int numOperators = eq.numbers.size() - 1;
        int maxCombinations = 1 << numOperators; // 2^n combinaciones

        // Probamos todas las combinaciones posibles de operadores
        for (int mask = 0; mask < maxCombinations; mask++) {
            std::vector<char> operators;
            for (int i = 0; i < numOperators; i++) {
                operators.push_back((mask & (1 << i)) ? '*' : '+');
            }

            if (evaluateExpression(eq.numbers, operators) == eq.testValue) {
                return true;
            }
        }
        return false;
    }

public:
    void addEquation(const std::string& line) {
        std::istringstream iss(line);
        Equation eq;
        std::string temp;
        
        // Leer el valor de prueba
        getline(iss, temp, ':');
        eq.testValue = std::stoll(temp);

        // Leer los números
        while (iss >> temp) {
            eq.numbers.push_back(std::stoi(temp));
        }

        equations.push_back(eq);
    }

    long long solve() {
        long long sum = 0;
        for (const auto& eq : equations) {
            if (canSolve(eq)) {
                sum += eq.testValue;
            }
        }
        return sum;
    }
};

int main() {
    std::ifstream file("input.txt");
    std::string line;
    EquationSolver solver;

    while (std::getline(file, line)) {
        if (!line.empty()) {
            solver.addEquation(line);
        }
    }

    long long result = solver.solve();
    std::cout << "Resultado total de calibración: " << result << std::endl;

    return 0;
}