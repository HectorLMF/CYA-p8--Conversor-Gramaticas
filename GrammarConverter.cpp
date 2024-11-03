#include "GrammarConverter.h"

#include <algorithm>  // std::find
#include <fstream>
#include <iostream>
#include <map>  // std::map
#include <set>  // std::set

/**
 * @brief Realiza la conversión de la gramática a Forma Normal de Chomsky (CNF).
 * En CNF, cada producción debe ser de la forma A -> BC o A -> a.
 */
void GrammarConverter::convertToCNF()
{
  std::vector<Production> newProductions;
  std::map<std::string, std::string> terminalToNonTerminal;

  int counter = 1;

  for (auto& production : grammar.productions)
  {
    if (production.right.size() == 1)
    {
      const std::string& symbol = production.right[0];

      if (symbol.size() == 1 && std::find(grammar.terminals.begin(), grammar.terminals.end(), symbol[0]) != grammar.terminals.end())
      {
        if (terminalToNonTerminal.find(symbol) == terminalToNonTerminal.end())
        {
          std::string newNonTerminal = "T" + std::to_string(counter++);
          grammar.nonTerminals.push_back(newNonTerminal);
          terminalToNonTerminal[symbol] = newNonTerminal;
          newProductions.push_back(Production(newNonTerminal, {symbol}));
        }
        production.right[0] = terminalToNonTerminal[symbol];
      }
    }
  }

  for (const auto& production : grammar.productions)
  {
    if (production.right.size() <= 2)
    {
      newProductions.push_back(production);
    }
    else
    {
      std::string lastNonTerminal = production.left;
      for (size_t i = 0; i < production.right.size() - 2; ++i)
      {
        std::string newNonTerminal = "N" + std::to_string(counter++);
        grammar.nonTerminals.push_back(newNonTerminal);
        newProductions.push_back(Production(lastNonTerminal, {production.right[i], newNonTerminal}));
        lastNonTerminal = newNonTerminal;
      }
      newProductions.push_back(Production(lastNonTerminal, {production.right[production.right.size() - 2], production.right.back()}));
    }
  }

  grammar.productions = newProductions;
}

/**
 * @brief Elimina las producciones unitarias de la gramática.
 */
void GrammarConverter::removeUnitProductions()
{
  std::set<std::pair<std::string, std::string>> unitPairs;

  for (const auto& production : grammar.productions)
  {
    if (production.right.size() == 1 &&
        std::find(grammar.nonTerminals.begin(), grammar.nonTerminals.end(), production.right[0]) != grammar.nonTerminals.end())
    {
      unitPairs.insert({production.left, production.right[0]});
    }
  }

  bool changed = true;
  while (changed)
  {
    changed = false;
    std::set<std::pair<std::string, std::string>> newUnitPairs;

    for (const auto& [A, B] : unitPairs)
    {
      for (const auto& production : grammar.productions)
      {
        if (production.left == B && !(production.right.size() == 1 && std::find(grammar.nonTerminals.begin(), grammar.nonTerminals.end(), production.right[0]) != grammar.nonTerminals.end()))
        {
          Production newProduction(A, production.right);
          if (std::find(grammar.productions.begin(), grammar.productions.end(), newProduction) == grammar.productions.end())
          {
            grammar.productions.push_back(newProduction);
            newUnitPairs.insert({A, production.right[0]});
            changed = true;
          }
        }
      }
    }
    unitPairs.insert(newUnitPairs.begin(), newUnitPairs.end());
  }

  grammar.productions.erase(std::remove_if(grammar.productions.begin(), grammar.productions.end(), [&](const Production& production)
                                           { return production.right.size() == 1 && std::find(grammar.nonTerminals.begin(), grammar.nonTerminals.end(), production.right[0]) != grammar.nonTerminals.end(); }),
                            grammar.productions.end());
}

/**
 * @brief Elimina las producciones epsilon (vacías) de la gramática.
 */
void GrammarConverter::removeEpsilonProductions()
{
  std::set<std::string> nullableSymbols;
  bool changed = true;

  while (changed)
  {
    changed = false;
    for (const auto& production : grammar.productions)
    {
      if (production.right.size() == 1 && production.right[0] == "&")
      {
        nullableSymbols.insert(production.left);
      }
      else if (std::all_of(production.right.begin(), production.right.end(), [&](const std::string& symbol)
                           { return nullableSymbols.find(symbol) != nullableSymbols.end(); }))
      {
        if (nullableSymbols.find(production.left) == nullableSymbols.end())
        {
          nullableSymbols.insert(production.left);
          changed = true;
        }
      }
    }
  }

  std::vector<Production> newProductions;
  for (const auto& production : grammar.productions)
  {
    if (production.right.size() == 1 && production.right[0] == "&")
    {
      continue;
    }

    newProductions.push_back(production);

    std::vector<size_t> nullablePositions;
    for (size_t i = 0; i < production.right.size(); ++i)
    {
      if (nullableSymbols.find(production.right[i]) != nullableSymbols.end())
      {
        nullablePositions.push_back(i);
      }
    }

    int numCombinations = 1 << nullablePositions.size();
    for (int i = 1; i < numCombinations; ++i)
    {
      std::vector<std::string> newRight = production.right;
      for (size_t j = 0; j < nullablePositions.size(); ++j)
      {
        if (i & (1 << j))
        {
          newRight[nullablePositions[j]] = "";
        }
      }

      newRight.erase(std::remove(newRight.begin(), newRight.end(), ""), newRight.end());
      if (!newRight.empty())
      {
        newProductions.push_back(Production(production.left, newRight));
      }
    }
  }

  grammar.productions = newProductions;
}
