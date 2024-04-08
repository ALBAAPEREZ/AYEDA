/**
 * @file CellACE110.h
 * @author Alba Pérez Rodríguez
 * @version 0.1
 * @date 2024-02-29
 * @brief Clase abstracta CellACE que hereda de la clase Cell y 
 * que recoge las especificaciones comunes en la implementación de cualquier
 * autómata celular elemental [4]. Esta clase, que sigue siendo abstracta, se puede
 * particularizar para cada una de las 256 posibles reglas de transición definidas para este 
 * tipo de autómata celular.
 * Aqui se implementan la regla 110 y la regla 30.
 */

#include "Cell.h"
#include "CellACE.h"
#include "CellACE30.h"

#include <iostream>
#include <utility>
#include <vector>

/**
 * @brief Método que implementa la regla 30 del autómata celular elemental
 * Esta regla se define por la fórmula: C^(G+1)=(L^(G)+C^(G)+R^(G)+C^(G)*R^(G))%2
 * @tparam PositionType representa el tipo de dato que se utiliza para representar la posición de la célula
 * @param lattice representa la red de células
 */
template <typename PositionType>
void CellACE30<PositionType>::NextState(const Lattice<PositionType>& lattice) {
  const int C = state_;
  int next_state{0};
  // Obtenemos los estados de las células adyacentes
  int L = lattice.getCell(position_ - 1).getState();
  int R = lattice.getCell(position_ + 1).getState();  
  // Formula que viene dada como: C^(G+1)=(L^(G)+C^(G)+R^(G)+C^(G)*R^(G))%2
  next_state = (L + C + R + C * R) % 2;
  next_state_ = next_state;
}

/**
 * @brief Método que actualiza el estado de la célula
 * Se actualiza el estado de la célula al estado siguiente
 */
template <typename PositionType>
void CellACE30<PositionType>::UpdateState() {
  state_ = next_state_;
}

/**
 * @brief Método que muestra el estado de la célula
 * Se muestra un espacio si el estado es 0 y una X si el estado es 1
 * @param os flujo de salida
 */
template <typename PositionType>
void CellACE30<PositionType>::Display(std::ostream& os) {
  // SI el estado es 0 se muestra un espacio, si es 1 se muestra una X
  if (state_ == 0) {
    os << " ";
  } else {
    os << "X";
  }
}