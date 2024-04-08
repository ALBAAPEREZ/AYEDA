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


#ifndef CELLACE110_H
#define CELLACE110_H

#include "Cell.h"
#include "lattice.h"
#include "CellACE.h"

#include <iostream>
#include <utility>
#include <vector>


/**
 * @brief Clase CellACE110 que hereda de la clase CellACE y
 * que recoge las especificaciones comunes en la implementación de cualquier
 * autómata celular elemental [4]. Esta clase, que sigue siendo abstracta, se puede
 * particularizar para cada una de las 256 posibles reglas de transición definidas para este
 * tipo de autómata celular.
 * @tparam PositionType 
 */
template <typename PositionType>
class CellACE110 : public CellACE {
 public:
  // Constructor propio de la clase CellACE110
  CellACE110(const Position&<PositionType>, const State&) : CellACE(position_, state_) {}
  void NextState(const Lattice<PositionType>& lattice) override;
  void UpdateState();
  void Display(std::ostream&);
};

#endif // CELLACE110_H