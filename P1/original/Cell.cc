/**
 * ************ PRÁCTICA 1 *************
 * @file Cell.h
 * @author ALBA PÉREZ RODRÍGUEZ
 * @version 0.1
 * @date 2024-02-07
 * @brief Implementación de los métodos de la clase Cell
 * Encontramos la implementación de los métodos de la clase Cell como el constructor por defecto, 
 * el constructor de la célula, el método nextState, el método updateState y 
 * la sobrecarga del operador de salida
 * 
*/

#include "Cell.h"

/**
 * @brief Construct a new Cell:: Cell object
 * El constructor de la célula recibe como parámetro su posición dentro del retículo, y
 * de forma opcional su estado en la configuración inicial. Por defecto, la célula se
 * crea con estado «0».
 */
Cell::Cell(const Position& position, const State& state) : state_(state), position_(position) {}

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
 * @brief recibe el retículo por parámetro y calcula el siguiente estado sin evolucionar.
 * Se encarga de calcular el siguiente estado de la célula sin evolucionar
 * @return int retorna el siguiente estado de la célula
 */
int Cell::NextState(const Lattice& lattice) {
  // Get the states of the adjacent cells
  State center_state = lattice.getCell(position_).getState();
  State left_state = lattice.getCell(position_ - 1).getState();
  State right_state = lattice.getCell(position_ + 1).getState();
  // Aplicamos la regla 110
  // Formula que viene dada como: C^(G+1)=(C^(G)+R^(G)+C^(G)*R^(G)+L^(G)*C^(G)*R^(G))%2
  next_state_ = ((center_state + right_state + center_state * right_state + left_state * center_state * right_state) % 2);
  return next_state_;
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
  return os << (cell.getState() == DEAD ? " " : "X");
}