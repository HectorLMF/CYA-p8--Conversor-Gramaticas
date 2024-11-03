#ifndef GRAMMAR_H
#define GRAMMAR_H

#include <string>
#include <vector>

#include "Production.h"

/**
 * @class Grammar
 * @brief Representa una gramática libre de contexto con un conjunto de símbolos terminales, no terminales, un símbolo de arranque y un conjunto de producciones.
 */
class Grammar
{
 public:
  std::vector<char> terminals;            ///< Lista de símbolos terminales.
  std::vector<std::string> nonTerminals;  ///< Lista de símbolos no terminales.
  std::string startSymbol;                ///< Símbolo de arranque de la gramática.
  std::vector<Production> productions;    ///< Lista de producciones de la gramática.

  /**
   * @brief Carga una gramática desde un archivo en formato .gra.
   * @param filename Nombre del archivo de entrada.
   * @return true si la gramática se carga correctamente, false en caso contrario.
   */
  bool loadFromFile(const std::string& filename);

  /**
   * @brief Guarda la gramática actual en un archivo en formato .gra.
   * @param filename Nombre del archivo de salida.
   * @return true si la gramática se guarda correctamente, false en caso contrario.
   */
  bool saveToFile(const std::string& filename);
};

#endif  // GRAMMAR_H
