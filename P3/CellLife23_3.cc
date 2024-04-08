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
#include "CellLife23_3.h"

/**
 * @brief Meotodo que actualiza el estado de la célula en función de la vecindad.
 * Se realiza la regla 23/3. Esta regla se basa en que una célula muerta con 3 células vecinas vivas,
 * se convierte en una célula viva. Una célula viva con 2 o 3 células vecinas vivas, sigue viviendo.
 * @tparam PositionType posición de la célula
 * @param lattice red de células
 */
template <typename PositionType>
void CellLife23_3<PositionType>::NextState(const Lattice<PositionType>& lattice) {
  int alive_count{0};
  State next_state;
  const State C = state_;
  // Obtenemos los estados de las células adyacentes
  State E = lattice.GetCell(Position(position_.first+1, position_.second)).GetState();
  if (E == State::Vivo) alive_count++;
  State W = lattice.GetCell(Position(position_.first-1, position_.second)).GetState();
  if (W == State::Vivo) alive_count++;
  State N = lattice.GetCell(Position(position_.first, position_.second-1)).GetState();
  if (N == State::Vivo) alive_count++;
  State S = lattice.GetCell(Position(position_.first, position_.second+1)).GetState();
  if (S == State::Vivo) alive_count++;
  State NE = lattice.GetCell(Position(position_.first+1, position_.second-1)).GetState();
  if (NE == State::Vivo) alive_count++;
  State NW = lattice.GetCell(Position(position_.first-1, position_.second-1)).GetState();
  if (NW == State::Vivo) alive_count++;
  State SE = lattice.GetCell(Position(position_.first+1, position_.second+1)).GetState();
  if (SE == State::Vivo) alive_count++;
  State SW = lattice.GetCell(Position(position_.first-1, position_.second+1)).GetState();
  if (SW == State::Vivo) alive_count++;
  // comprueba si la célula está viva o muerta
  if (C == State::Muerto) {
    // Si la célula está muerta y tiene 3 células vecinas vivas, se convierte en una célula viva
    if (alive_count == 3) {
      next_state = State::Vivo;
    }
    else {
      next_state = State::Muerto;
    }
  } else {
    // Si la célula está viva y tiene 2 o 3 células vecinas vivas, sigue viva
    if (alive_count < 2 || alive_count > 3) {
      next_state = State::Muerto;
    } else {
      next_state = State::Vivo;
    }
  }  
  next_state_ = next_state;
}

/**
 * @brief Método que actualiza el estado de la célula
 * Se actualiza el estado de la célula al estado siguiente
 */
template <typename PositionType>
void CellLife23_3<PositionType>::UpdateState() {
  state_ = next_state_;
}

/**
 * @brief Método que muestra el estado de la célula
 * @param os flujo de salida
 */
template <typename PositionType>
void CellLife23_3<PositionType>::Display(std::ostream& os) {
  if (state_ == '0') {
    os << "X";
  } else {
    os << " ";
  }
}