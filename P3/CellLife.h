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

#ifndef CELLLIFE_H
#define CELLLIFE_H

#include "Cell.h"
#include "lattice.h"

/**
 * @brief Clase CellLife que hereda de la clase Cell y con la que se implementa la regla 23/3 y 51/346.
 * Cada una de las posibles variantes del juego, cambiando la definición de la vecindad y utilizando
 * @tparam PositionType posición de la celda
 */
template <typename PositionType>
class CellLife : public Cell {
 public:
  // Constructor propio de la clase CellLife
  CellLife(const Position&, const State&) : Cell(position_, state_) {}
};

#endif // CELLLIFE_H