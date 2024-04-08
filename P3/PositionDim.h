/**
 * @file PositionDim.h
 * @author Alba Pérez Rodríguez
 * @version 0.1
 * @date 2024-02-29
 * @brief Clase abstracta PositionDim para permitir representar
 * posiciones en retículos de cualquier dimensión. De esta se heredaran la clase
 * PositionDim que podrá ser de 1 o 2 dimensiones.
 */

#ifndef POSITIONDIM_H
#define POSITIONDIM_H

#include "Position.h"

#include <iostream>
#include <utility>
#include <stdarg.h>

/**
 * @brief Clase abstracta PositionDim para permitir representar posiciones en retículos 
 * de cualquier dimensión. Se heredará de la clase Position. Ademas, cuenta con una
 * plantilla de clase para poder definir el tipo de coordenada que se usará.
 * @tparam Dim dimensión del retículo, puede ser 1 o 2
 * @tparam Coordinate_t define el tipo de coordenada que se usará
 */
template <int Dim=2, class Coordinate_t=int>
class PositionDim: public Position {
 private:
  Coor_t Coordinates[Dim];
 public:
  // Constructor con lista variable de parámetros
  PositionDim(int sz, ...) {
    va_list vl;
    va_start(vl, sz);
    for(int d=0; d<Dim; d++) {
      Coordinates[d] = va_arg(vl, Coor_t);  
    }
    va_end(vl);
  }
  // Operador de acceso a la i-ésima coordenada
  Coor_t operator[](unsigned int) const {
    return Coordinates[i];
  }
};

#endif // POSITIONDIM_H