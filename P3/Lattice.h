/**
 * @file Lattice.h
 * @author Alba Pérez Rodríguez
 * @version 0.1
 * @date 2024-02-29
 * @brief Clase abstracta Lattice y define las responsabilidades asignadas a este tipo
 * de datos, permitiendo que sean sus clases derivadas las que especifican las diferentes
 * implementaciones. A partir de la clase base se derivan dos tipos de retículo:
 * 1. Unidimensional (Lattice1D)
 * 2. Bidimensional (Lattice2D)
 */

#ifndef LATTICE_H
#define LATTICE_H

#include "Cell.h"
#include "Position.h"

#include <iostream>
#include <utility>

// Declaración adelantada de la clase Cell
template <typename PositionType>
class Cell;

/**
 * @brief Clase abstracta Lattice que define las responsabilidades asignadas a este tipo
 * de datos, permitiendo que sean sus clases derivadas las que especifican las diferentes
 * implementaciones. A partir de la clase base se derivan dos tipos de retículo:
 * 1. Unidimensional (Lattice1D)
 * 2. Bidimensional (Lattice2D)
 * @tparam PositionType posición de la celda
 */
template <typename PositionType> 
class Lattice {
 public:
  Lattice() = default;
  virtual ~Lattice() = default;
  Cell& operator[](const PositionType& position) = 0;
  virtual void NextGeneration() = 0;
  virtual std::size_t Population() const = 0;
  virtual std::ostream& Display(std::ostream& os) const = 0;
  friend std::ostream& operator<<(std::ostream& os, const Lattice<PositionType>& lattice);
};

#endif // LATTICE_H