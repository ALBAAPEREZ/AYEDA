/**
 * @file CellLife.h
 * @author Alba Pérez Rodríguez
 * @version 0.1
 * @date 2024-02-29
 * @brief Clase abstracta CellLife que hereda de la clase Cell y
 * Esta clase, que sigue siendo abstracta, se puede particularizar para cada una de
 * las posibles variantes del juego, cambiando la definición de la vecindad y utilizando
 * distintas reglas de transición local.
 * Aqui se implementa la regla "23/3” y “51/346”.
 */

#include "Cell.h"
#include "CellLife.h"
#include "CellLife51_346.h"

/**
 * @brief Meotodo que actualiza el estado de la célula en función de la vecindad.
 * Se realiza la regla 51/346. Esta regla se basa en que una célula muerta con 3, 4, 5 o 6 células vecinas vivas,
 * se convierte en una célula viva. Una célula viva con 5, 6, 7 u 8 células vecinas vivas, sigue viviendo.
 * @tparam PositionType posición de la célula
 * @param lattice red de células
 */
template <typename PositionType>
void CellLife51_346<PositionType>::NextState(const Lattice<PositionType>& lattice) {
  int alive_count{0};
  State next_state;
  // Comprobar el estado de las células vecinas y contar las células vivas
  for (int dx = -1; dx <= 1; dx++) {
    for (int dy = -1; dy <= 1; dy++) {
      if (dx == 0 && dy == 0) continue;  // Skip the center cell
      State neighbor_state = lattice.GetCell(Position(position_.first + dx, position_.second + dy)).GetState();
      if (neighbor_state == State::Vivo) alive_count++;
    }
  }
  // Aplicar la regla 51/346
  if (state_ == State::Vivo) {
    if (alive_count == 5 || alive_count == 1 || alive_count == 3) {
      next_state = State::Vivo;
    } else {
      next_state = State::Muerto;
    }
  } else {  // state_ == State::Muerto
    if (alive_count == 3 || alive_count == 4 || alive_count == 6) {
      next_state = State::Vivo;
    } else {
      next_state = State::Muerto;
    }
  }
  next_state_ = next_state;
}

/**
 * @brief Método que actualiza el estado de la célula.
 * Se actualiza el estado de la célula al estado siguiente
 */
template <typename PositionType>
void CellLife51_346<PositionType>::UpdateState() {
  state_ = next_state_;
}

/**
 * @brief Método que muestra el estado de la célula.
 * @param os flujo de salida
 */
template <typename PositionType>
void CellLife51_346<PositionType>::Display(std::ostream& os) {
  if (state_ == '0') {
    os << " ";
  } else {
    os << "X";
  }
}
