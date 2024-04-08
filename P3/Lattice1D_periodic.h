/**
 * @file Lattice1D.h
 * @author Alba Pérez Rodríguez
 * @version 0.1
 * @date 2024-02-29
 * @brief Clase abstracta Lattice1D que hereda de la clase Lattice y se encarga de definir
 * e implementar las responsabilidades de un retículo unidimensional.
 */

#ifndef LATTICE1D_PERIODIC_H
#define LATTICE1D_PERIODIC_H

#include "Lattice.h"
#include "Cell.h"
#include "Position.h"
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
class Lattice1D_periodic : public Lattice1D<PositionType> {
  // Implementación específica para retículos 1D
 public:
  Lattice1D_periodic(const int& size, FactoryCell<PositionType>& factory);
  virtual ~Lattice1D_periodic();
  Cell* operator[](const PositionType& position) override;
  void NextGeneration() override;
  void Display(std::ostream&);

 private:
  bool periodic_;
  Cell* borderType_;
};

#endif // LATTICE1D_PERIODIC_H