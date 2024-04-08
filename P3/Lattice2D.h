/**
 * @file Lattice2D.h
 * @author Alba Pérez Rodríguez
 * @version 0.1
 * @date 2024-02-29
 * @brief Clase abstracta Lattice2D que hereda de la clase Lattice y se encarga de definir
 * e implementar las responsabilidades de un retículo bidimensional.
 */

#ifndef LATTICE2D_H
#define LATTICE2D_H

#include "Lattice.h"
#include "Cell.h" 
#include "Position.h"
#include "FactoryCell.h"
#include "Lattice2D.h"

#include <iostream>
#include <utility>
#include <vector>

/**
 * @brief  Clase abstracta Lattice2D que hereda de la clase Lattice y se encarga de definir
 * e implementar las responsabilidades de un retículo bidimensional.
 * @tparam PositionType posición de la celda
 */
template <typename PositionType>
class Lattice2D : public Lattice<PositionType> {
  // Implementación específica para retículos 2D
 public:
  // Constructor que recibe un fichero y una fábrica de células
  Lattice2D(std::fstream& file, FactoryCell<PositionType>& factory);
  virtual ~Lattice2D();
  void NextGeneration() override;
  std::size_t Population() const override;
  void SetSize(int size) { size_ = size; };
  int GetSize() const { return size_; };
  std::ostream& Display(std::ostream& os) const;

 private:
  std::vector<std::vector<Cell*>> cells_;
  int size_;
};

#endif // LATTICE2D_H