/**
 * @file Lattice1D.h
 * @author Alba Pérez Rodríguez
 * @version 0.1
 * @date 2024-02-29
 * @brief Clase abstracta Lattice1D que hereda de la clase Lattice y se encarga de definir
 * e implementar las responsabilidades de un retículo unidimensional.
 */


#ifndef LATTICE1D_OPEN_H
#define LATTICE1D_OPEN_H

#include "Lattice.h"
#include "Cell.h"
#include <Position.h>
#include "Lattice1D.h"

#include <iostream>
#include <utility>
#include <vector>

/**
 * @brief Clase abstracta Lattice1D que hereda de la clase Lattice y se encarga de definir
 * e implementar las responsabilidades de un retículo unidimensional.
 * @tparam PositionType Posición de la celda
 */
template <typename PositionType>
class Lattice1D_open : public Lattice1D<PositionType> {
  // Implementación específica para retículos 1D
 public:
  Lattice1D_open(const int& size, FactoryCell<PositionType>& factory, bool open);
  Lattice1D_open(std::fstream& file, FactoryCell<PositionType>& factory, bool open_type);
  ~Lattice1D_open();
  Cell& operator[](const PositionType<PositionType>& position);
  void NextGeneration() override;
  void Display(std::ostream&);

 private:
  bool open_;
  Cell* borderType_;
};

#endif // LATTICE1D_OPEN_H
