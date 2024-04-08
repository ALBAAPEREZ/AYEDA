/**
 * @file CellLife23_3.h
 * @author Alba Pérez Rodríguez
 * @version 0.1
 * @date 2024-02-29
 * @brief Clase abstracta CellLife23_3 que hereda de la clase CellLife y se encarga de definir
 * e implementar las responsabilidades de un retículo unidimensional. 
 * La clase hereda de CellLife. Esta contiene las especificaciones comunes en la implementación 
 * de cualquier variante del juego, cambiando la definición de la vecindad y utilizando distintas
 * reglas de transición local.
 */

#ifndef CELLLIFE23_3_H
#define CELLLIFE23_3_H

#include "Cell.h"
#include "CellLife.h"
#include "lattice.h"

/**
 * @brief Clase CellLife23_3 que hereda de la clase CellLife y  
 * que recoge las especificaciones comunes en la implementación de cualquier
 * @tparam PositionType posición de la celda
 */
template <typename PositionType>
class CellLife23_3 : public CellLife {
 public:
  // Constructor propio de la clase CellLife23_3
  CellLife23_3(const Position&, const State&) : Cell(position_, state_) {}
  void NextState(const Lattice<PositionType>&);
  void UpdateState();
  void Display(std::ostream&);
};

#endif // CELLLIFE23_3_H
