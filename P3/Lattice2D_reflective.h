/**
 * @file Lattice2D_reflective.h
 * @author Alba Pérez Rodríguez
 * @version 0.1
 * @date 2024-02-29
 * @brief Clase abstracta Lattice2D que hereda de la clase Lattice y se encarga de definir
 * e implementar las responsabilidades de un retículo bidimensional.
 */

#ifndef LATTICE2D_REFLECTIVE_H
#define LATTICE2D_REFLECTIVE_H

#include "Lattice2D.h"
#include "Position.h"
#include "FactoryCell.h"
#include "Cell.h"

#include <iostream>

/**
 * @brief Clase Lattice2D_reflective que hereda de la clase Lattice2D y se encarga de definir
 * e implementar las responsabilidades de un retículo bidimensional con condiciones de contorno reflectantes.
 * La clase hereda de Lattice2D
 * @tparam PositionType posición de la celda
 */
template <typename PositionType>
class Lattice2D_reflective: public Lattice2D {
 public:
 // Constructor que recibe un fichero y una fábrica de células
  Lattice2D_reflective(std::fstream& file, FactoryCell& factory) : Lattice2D(file, factory) {}
  Lattice2D_reflective(int rows, int columns, FactoryCell& factory) : Lattice2D(rows, columns, factory) {}
  virtual ~Lattice2D_reflective() {}
  void NextGeneration();
  Cell* operator[](Position& position);
};

#endif // LATTICE2D_REFLECTIVE_H