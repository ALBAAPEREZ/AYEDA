/**
 * @file CellACE.h
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

#ifndef CELLACE_H
#define CELLACE_H

#include "Cell.h"
#include "lattice.h"

#include <iostream>
#include <utility>
#include <vector>

/**
 * @brief Clase CellACE que hereda de la clase Cell y
 * que recoge las especificaciones comunes en la implementación de cualquier
 * @tparam PositionType posición de la célula
 */
template <typename PositionType>
class CellACE : public Cell {
 public:
  // Constructor propio de la clase CellACE
  CellACE(const PositionType& position, const State& state) : Cell(position, state) {}
};



#endif // CELLACE_H

