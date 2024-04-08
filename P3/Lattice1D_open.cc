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
#include "Lattice1D_open.h"
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
Lattice1D_open<PositionType>::Lattice1D_open(const int& size, FactoryCell<PositionType>& factory, bool open) : Lattice1D<PositionType>(size, factory), open_(open) {
  Position* pos;
  // Si el borde es abierto, se crea una célula de tipo 0 en el borde, sino, de tipo 1
  if (open_ == 0) {
    pos = new PositionDim<1>(1, -1);
    borderType_ = factory.CreateCell(*pos, '0');
  } else {
    pos = new PositionDim<1>(1, -1);
    borderType_ = factory.CreateCell(*pos, '1');
  }
}

/**
 * @brief Constructor de la clase Lattice1D_open
 * Recibe un fichero y una fábrica de células. se encarga de inicializar el retículo con las células
 * @tparam PositionType posición de la celda
 * @param file fichero de entrada
 * @param factory fábrica de células
 * @param open_type tipo de borde
 */
template <typename PositionType>
Lattice1D_open<PositionType>::Lattice1D_open(std::fstream& file, FactoryCell<PositionType>& factory, bool open_type) : Lattice1D<PositionType>(file, factory), open_(open_type) {
  Position* pos;
  if (open_ == 0) {
    pos = new PositionDim<1>(1, -1);
    borderType_ = factory.CreateCell(*pos, '0');
  } else {
    pos = new PositionDim<1>(1, -1);
    borderType_ = factory.CreateCell(*pos, '1');
  }
}

/**
 * @brief Destructor de la clase Lattice1D_open
 * @tparam PositionType posición de la celda
 */
template <typename PositionType>
Lattice1D_open<PositionType>::~Lattice1D_open() {
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
void Lattice1D_open<PositionType>::NextGeneration() {
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
void Lattice1D_open<PositionType>::Display(std::ostream& os) {
  for (int i = 0; i < this->GetSize(); i++) {
    os << this->cells_[i]->GetState();
  }
  os << std::endl;
}




