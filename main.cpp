#include <iostream>

#include "Grammar.h"
#include "GrammarConverter.h"

/**
 * @brief Imprime el texto de ayuda del programa.
 */
void printHelp()
{
  std::cout << "Modo de empleo: ./Grammar2CNF input.gra output.gra\n";
}

/**
 * @brief Punto de entrada principal del programa.
 * @param argc Número de argumentos de línea de comandos.
 * @param argv Array de argumentos de línea de comandos.
 * @return Código de estado de ejecución (0 si es exitoso).
 */
int main(int argc, char* argv[])
{
  if (argc == 2 && std::string(argv[1]) == "--help")
  {
    printHelp();
    return 0;
  }
  else if (argc != 3)
  {
    std::cerr << "Error: número incorrecto de argumentos.\n";
    printHelp();
    return 1;
  }

  Grammar grammar;
  if (!grammar.loadFromFile(argv[1]))
  {
    std::cerr << "Error al cargar la gramática.\n";
    return 1;
  }

  GrammarConverter converter(grammar);
  converter.convertToCNF();

  if (!grammar.saveToFile(argv[2]))
  {
    std::cerr << "Error al guardar la gramática.\n";
    return 1;
  }

  std::cout << "Conversión completada correctamente.\n";
  return 0;
}
