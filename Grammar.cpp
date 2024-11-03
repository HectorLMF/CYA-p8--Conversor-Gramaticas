#include "Grammar.h"
#include <fstream>
#include <sstream>
#include <iostream>

bool Grammar::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;

    // Leer terminales
    int numTerminals;
    file >> numTerminals;
    terminals.resize(numTerminals);
    for (int i = 0; i < numTerminals; ++i) {
        file >> terminals[i];
    }

    // Leer no terminales
    int numNonTerminals;
    file >> numNonTerminals;
    nonTerminals.resize(numNonTerminals);
    for (int i = 0; i < numNonTerminals; ++i) {
        file >> nonTerminals[i];
    }
    startSymbol = nonTerminals[0];

    // Leer producciones
    int numProductions;
    file >> numProductions;
    std::string left, rightSide;
    for (int i = 0; i < numProductions; ++i) {
        file >> left;
        std::getline(file, rightSide);
        std::istringstream rightStream(rightSide);
        std::vector<std::string> right;
        std::string symbol;
        while (rightStream >> symbol) {
            right.push_back(symbol);
        }
        productions.emplace_back(left, right);
    }
    return true;
}

bool Grammar::saveToFile(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) return false;

    // Escribir terminales
    file << terminals.size() << "\n";
    for (const auto& terminal : terminals) {
        file << terminal << "\n";
    }

    // Escribir no terminales
    file << nonTerminals.size() << "\n";
    for (const auto& nonTerminal : nonTerminals) {
        file << nonTerminal << "\n";
    }

    // Escribir producciones
    file << productions.size() << "\n";
    for (const auto& production : productions) {
        file << production.left << " ";
        for (const auto& symbol : production.right) {
            file << symbol << " ";
        }
        file << "\n";
    }
    return true;
}
