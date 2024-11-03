#ifndef PRODUCTION_H
#define PRODUCTION_H

#include <string>
#include <vector>

class Production
{
 public:
  std::string left;                // Lado izquierdo de la producción
  std::vector<std::string> right;  // Lado derecho de la producción

  // Constructor
  Production(std::string l, std::vector<std::string> r)
      : left(l), right(r) {}

  // Sobrecarga del operador ==
  bool operator==(const Production& other) const
  {
    return left == other.left && right == other.right;
  }
};

#endif  // PRODUCTION_H
