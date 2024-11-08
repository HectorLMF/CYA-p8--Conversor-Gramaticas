#ifndef GRAMMARCONVERTER_H
#define GRAMMARCONVERTER_H

#include <string>

#include "Grammar.h"

using namespace std;

/**
 * @brief Clase para convertir una gramática a Forma Normal de Chomsky (CNF).
 */
class GrammarConverter
{
 public:
  /**
   * @brief Constructor de GrammarConverter.
   * @param grammar Gramática a convertir.
   */
  GrammarConverter(Grammar& grammar)
      : grammar(grammar) {}

  /**
   * @brief Realiza la conversión de la gramática a Forma Normal de Chomsky.
   */
  void convertToCNF();

  void removeNonAccesible();

  /**
   * @brief Elimina producciones unitarias de la gramática.
   */
  void removeUnitProductions();

  /**
   * @brief Elimina producciones vacías (epsilon) de la gramática.
   */
  void removeEpsilonProductions();

 private:
  Grammar& grammar;
};

#endif  // GRAMMARCONVERTER_H
