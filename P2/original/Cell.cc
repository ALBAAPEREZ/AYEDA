/**
 * ************ PRÁCTICA 2 *************
 * @file Cell.h
 * @author ALBA PÉREZ RODRÍGUEZ
 * @version 0.1
 * @date 2024-02-22
 * @brief Implementación de los métodos de la clase Cell.
 * Se encuentran los métodos de la clase Cell como el constructor por defecto,
 * el constructor de la célula, el método nextState, el método updateState y
 * la sobrecarga del operador de salida, entre otros.
*/

#include "Cell.h"

/**
 * @brief Construct a new Cell:: Cell object
 * Constructor de la clase celula que recibe como parámetro su posición y estado
 * @param position posición de la célula
 * @param state estado de la célula
 */
Cell::Cell(const Position& position, const State& state) {
  position_ = position;
  state_ = state;
}

/**
 * @brief Getter de la clase Cell que devuelve el estado de la célula
 * Se encarga de devolver el estado de la célula
 * @return State retorna el estado de la célula
 */
State Cell::getState() const { return state_; }

/**
 * @brief Setter que establece el estado de la célula
 * Se encarga de establecer el estado de la célula
 * @param state estado de la célula
 * @return State retorna el estado de la célula nuevo
 */
void Cell::setState(State state) {
  state_ = state;
}

/**
 * @brief Set the Position object
 * Se encarga de establecer la posición de la célula
 * @param pos 
 */
void Cell::setPosition(const Position& pos) {
  position_ = pos;
}

/**
 * @brief Función que se encarga de calcular el siguiente estado de la célula sin evolucionar
 * Realiza el calculo con la regla 23/3
 * Esta regla se basa en que si una célula está viva y tiene 2 o 3 vecinos vivos, entonces sigue viva, en caso contrario muere.
 * @return int retorna el siguiente estado de la célula
 */
int Cell::NextState(const Lattice& lattice) {
  // Calcula el número de vecinos vivos
  int alive_neighbors = Neighbors(lattice);
  State next_state = state_;
  // Aplicamos la regla 23/3
  if (state_ == ALIVE) {
    if (alive_neighbors != 2 || alive_neighbors != 3) {
      next_state = DEAD;
    }
  } else {
    if (alive_neighbors == 3) {
      next_state = ALIVE;
    }
  }
  next_state_ = next_state;
  return next_state;
}

/**
 * @brief Función que devuelve el número de vecinos vivos de la célula.
 * Se encarga de devolver el número de vecinos vivos de la célula
 * @param lattice retículo sobre el que se encuentra la célula
 * @return int retorna el número de vecinos vivos de la célula
 */
int Cell::Neighbors(const Lattice& lattice) {
  int result = 0;
  if (lattice.getCell({position_.first - 1, position_.second - 1}).getState() == ALIVE) ++result;
  if (lattice.getCell({position_.first - 1, position_.second}).getState() == ALIVE) ++result;
  if (lattice.getCell({position_.first - 1, position_.second + 1}).getState() == ALIVE) ++result;
  if (lattice.getCell({position_.first, position_.second - 1}).getState() == ALIVE) ++result;
  if (lattice.getCell({position_.first, position_.second + 1}).getState() == ALIVE) ++result;
  if (lattice.getCell({position_.first + 1, position_.second - 1}).getState() == ALIVE) ++result;
  if (lattice.getCell({position_.first + 1, position_.second}).getState() == ALIVE) ++result;
  if (lattice.getCell({position_.first + 1, position_.second + 1}).getState() == ALIVE) ++result;
  neighbors_ = result;
  return neighbors_;
}

/**
 * @brief Función que se encarga de actualizar el estado de la célula
 * El estado de la célula se actualiza con el siguiente estado
 */
void Cell::UpdateState() {
  state_ = next_state_;
}

/**
 * @brief Sobrecarga del operador de salida
 * Se encarga de imprimir el estado de la célula
 * @param os flujo de salida
 * @param cell celula a imprimir
 * @return std::ostream& flujo de salida
 */
std::ostream& operator<<(std::ostream& os, const Cell& cell) {
  os << ((cell.getState() == DEAD) ? " " : "X");
  return os;
} 