/**
 * @file Lattice2D_reflective.cc
 * @author Alba Pérez Rodríguez
 * @version 0.1
 * @date 2024-02-29
 * @brief Clase Lattice2D_reflective que hereda de la clase Lattice2D y se encarga de definir
 * e implementar las responsabilidades de un retículo bidimensional con condiciones de contorno reflectantes.
 */

#include "Lattice2D_reflective.h"
#include "Cell.h"
#include "Lattice2D.h"
#include "Position.h"

#include <iostream>

/**
 * @brief Destroy the Lattice2D_reflective<PositionType>::Lattice2D_reflective object
 * Destructor de la clase Lattice2D_reflective que se encarga de liberar la memoria de las células
 * @tparam PositionType posición de la celda
 */
template <typename PositionType>
Lattice2D_reflective<PositionType>::~Lattice2D_reflective() {
  for (int i = 0; i < this->GetSize(); i++) {
    for (int j = 0; j < this->GetSize(); j++) {
      delete this->cells_[i][j];
    }
  }
}

/**
 * @brief Metodo que se encarga de calcular la siguiente generación de células en el retículo.
 * En ella se aplican dos for que recorren el retículo y otro que actualiza el estado de las células. 
 * @tparam PositionType 
 */
template <typename PositionType>
void Lattice2D_reflective<PositionType>::NextGeneration() {
  for (int i = 0; i < this->GetSize(); i++) {
    for (int j = 0; j < this->GetSize(); j++) {
      this->cells_[i][j]->SetNextState();
    }
  }
  for (int i = 0; i < this->GetSize(); i++) {
    for (int j = 0; j < this->GetSize(); j++) {
      this->cells_[i][j]->UpdateState();
    }
  }   
}