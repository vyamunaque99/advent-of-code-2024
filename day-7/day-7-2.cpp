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

    // Función auxiliar para concatenar números
    long long concatenate(long long a, long long b) {
        long long temp = b;
        while (temp > 0) {
            a *= 10;
            temp /= 10;
        }
        return a + b;
    }

    long long evaluateExpression(const std::vector<int>& numbers, const std::vector<char>& operators) {
        std::vector<long long> values(numbers.begin(), numbers.end());
        
        // Evaluamos de izquierda a derecha
        for (size_t i = 0; i < operators.size(); i++) {
            long long result;
            switch (operators[i]) {
                case '+':
                    values[i + 1] = values[i] + values[i + 1];
                    break;
                case '*':
                    values[i + 1] = values[i] * values[i + 1];
                    break;
                case '|': // Operador de concatenación
                    values[i + 1] = concatenate(values[i], values[i + 1]);
                    break;
            }
        }
        return values.back();
    }

    bool canSolve(const Equation& eq) {
        int numOperators = eq.numbers.size() - 1;
        int maxCombinations = 1;
        for (int i = 0; i < numOperators; i++) {
            maxCombinations *= 3; // Ahora tenemos 3 operadores posibles
        }

        // Probamos todas las combinaciones posibles de operadores
        for (int mask = 0; mask < maxCombinations; mask++) {
            std::vector<char> operators;
            int tempMask = mask;
            for (int i = 0; i < numOperators; i++) {
                int op = tempMask % 3;
                if (op == 0) operators.push_back('+');
                else if (op == 1) operators.push_back('*');
                else operators.push_back('|');
                tempMask /= 3;
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
