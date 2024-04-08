/**
 * @file Lattice2D_noborder.h
 * @author Alba Pérez Rodríguez
 * @version 0.1
 * @date 2024-02-29
 * @brief Clase abstracta Lattice2D_NoBorder que hereda de la clase Lattice2D y se encarga de definir+
 * e implementar las responsabilidades de un retículo bidimensional sin condiciones de contorno.
 * La clase hereda de Lattice2D y es una clase abstracta.
 */

#ifndef LATTICE2D_NOBORDER_H
#define LATTICE2D_NOBORDER_H

#include "Lattice2D.h"
#include "Position.h"
#include "FactoryCell.h"
#include "Cell.h"

#include <iostream>

/**
 * @brief Clase Lattice2D_NoBorder que hereda de la clase Lattice2D y se encarga de definir
 * e implementar las responsabilidades de un retículo bidimensional sin condiciones de contorno.
 * La clase hereda de Lattice2D
 * @tparam PositionType posición de la celda
 */
template <typename PositionType>
class Lattice2D_NoBorder: public Lattice2D {
 public:
  // Constructor que recibe un fichero y una fábrica de células
  Lattice2D_NoBorder(std::fstream& file, FactoryCell& factory) : Lattice2D(file, factory) {}
  Lattice2D_NoBorder(int rows, int columns, FactoryCell& factory) : Lattice2D(rows, columns, factory) {}
  virtual ~Lattice2D_NoBorder() {}
  // Operador que devuelve la celda en la posición indicada
  Cell* operator[](Position& position);
  void NextGeneration();

 private:
  FactoryCell* factory_;
};

#endif // LATTICE2D_NOBORDER_H