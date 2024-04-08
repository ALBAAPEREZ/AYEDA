/**
 * @file Lattice1D.h
 * @author Alba Pérez Rodríguez
 * @version 0.1
 * @date 2024-02-29
 * @brief Clase abstracta Lattice1D que hereda de la clase Lattice y se encarga de definir
 * e implementar las responsabilidades de un retículo unidimensional.
 */

#include "Lattice.h"
#include "Cell.h"
#include "Position.h"
#include "Lattice1D.h"
#include "Lattice1D_periodic.h"

#include <iostream>
#include <utility>
#include <vector>

/**
 * @brief Clase abstracta Lattice1D que hereda de la clase Lattice y se encarga de definir
 * e implementar las responsabilidades de un retículo unidimensional.
 * Implementa la frontera periódica. Esta es : 
 *  cells_[0]->setState(cells_[size_ - 2]->getState());
 *  cells_[size_ - 1]->setState(cells_[1]->getState());
 * @tparam PositionType Posición de la celda
 */
template <typename PositionType>
Lattice1D_periodic<PositionType>::Lattice1D_periodic(const int& size, FactoryCell<PositionType>& factory) : Lattice1D<PositionType>(size, factory) {
  periodic_ = true;
  borderType_ = factory.CreateCell(PositionType(0));
  borderType_->SetState(0);
  this->cells_[0] = borderType_;
  this->cells_[this->GetSize() - 1] = borderType_;
}


/**
 * @brief Destructor de la clase Lattice1D_periodic
 * @tparam PositionType Posición de la celda
 */
template <typename PositionType>
Lattice1D_periodic<PositionType>::~Lattice1D_periodic() {
  delete borderType_;
}

/**
 * @brief Método que se encarga de calcular el siguiente estado de todas las celdas del retículo.
 * Para ello, se utiliza el método NextState de la clase Cell.
 * @tparam PositionType Posición de la celda
 * @param position posición de la celda
 * @param state estado de la celda
 * @return State siguiente estado de la celda
 */
template <typename PositionType>
void Lattice1D_periodic<PositionType>::NextGeneration() {
  std::vector<Cell*> new_cells(this->GetSize());
  for (int i = 0; i < this->GetSize(); i++) {
    new_cells[i] = this->cells_[i]->NextState(this->Neighbors(PositionType(i)));
  }
  this->cells_ = new_cells;
}

/**
 * @brief Método que se encarga de mostrar el estado de todas las celdas del retículo.
 * @param os flujo de salida
 */
template <typename PositionType>
void Lattice1D_periodic<PositionType>::Display(std::ostream& os) {
  for (int i = 0; i < this->GetSize(); i++) {
    os << this->cells_[i]->GetState();
  }
  os << std::endl;
}

