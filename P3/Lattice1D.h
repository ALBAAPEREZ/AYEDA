/**
 * @file Lattice1D.h
 * @author Alba Pérez Rodríguez
 * @version 0.1
 * @date 2024-02-29
 * @brief Clase abstracta Lattice1D que hereda de la clase Lattice y se encarga de definir
 * e implementar las responsabilidades de un retículo unidimensional.
 */

#ifndef LATTICE1D_H
#define LATTICE1D_H

#include "Lattice.h"
#include "Cell.h"
#include <Position.h>
#include "FactoryCell.h"

#include <iostream>
#include <utility>
#include <vector>

/**
 * @brief Clase abstracta Lattice1D que hereda de la clase Lattice y se encarga de definir
 * e implementar las responsabilidades de un retículo unidimensional.
 * @tparam PositionType Posición de la celda
 */
template <typename PositionType>
class Lattice1D : public Lattice<PositionType> {
  // Implementación específica para retículos 1D
 public:
  Lattice1D(std::fstream& file, FactoryCell<PositionType>& factory);
  Lattice1D(int size, FactoryCell<PositionType>& factory);
  virtual ~Lattice1D();
  void NextGeneration() override;
  void SetSize(int size);
  int GetSize() const;
  std::size_t Population() const override;
  std::ostream& Display(std::ostream& os) const;

 private:
  std::vector<Cell*> cells_;
  int size_;
};

#endif // LATTICE1D_H