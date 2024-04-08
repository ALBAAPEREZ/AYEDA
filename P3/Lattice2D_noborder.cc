/**
 * @file Lattice2D_noborder.h
 * @author Alba Pérez Rodríguez
 * @version 0.1
 * @date 2024-02-29
 * @brief Clase abstracta Lattice2D_NoBorder que hereda de la clase Lattice2D y se encarga de definir+
 * e implementar las responsabilidades de un retículo bidimensional sin condiciones de contorno.
 * La clase hereda de Lattice2D y es una clase abstracta.
 */

#include "Lattice2D.h"
#include "Position.h"
#include "Lattice2D_noborder.h"

#include <iostream>

/**
 * @brief Clase Lattice2D_NoBorder que hereda de la clase Lattice2D y se encarga de definir
 * e implementar las responsabilidades de un retículo bidimensional sin condiciones de contorno.
 * La clase hereda de Lattice2D
 * @tparam PositionType posición de la celda
 */
template <typename PositionType>
void Lattice2D_NoBorder<PositionType>::NextGeneration() {
  for (int i = 0; i < GetSize(); i++) {
    for (int j = 0; j < GetSize(); j++) {
      cells_[i][j]->NextState();
    }
  }
  for (int i = 0; i < GetSize(); i++) {
    for (int j = 0; j < GetSize(); j++) {
      cells_[i][j]->UpdateState();
    }
  }
}