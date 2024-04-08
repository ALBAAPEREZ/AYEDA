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

#ifndef CELLLIFE51_346_H
#define CELLLIFE51_346_H

#include "Cell.h"
#include "CellLife.h"
#include "lattice.h"

/**
 * @brief Clase CellLife51_346 que hereda de la clase CellLife y
 * que recoge las especificaciones comunes en la implementación de cualquier
 * @tparam PositionType posición de la celda
 */
template <typename PositionType>
class CellLife51_346 : public CellLife {
 public:
  CellLife51_346(const Position&, const State&) : Cell(position_, state_) {}
  void NextState(const Lattice<PositionType>&);
  void UpdateState();
  void Display(std::ostream&);
};

#endif // CELLLIFE51_346_H