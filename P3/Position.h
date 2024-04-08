/**
 * @file Position.h
 * @author Alba Pérez Rodríguez
 * @version 0.1
 * @date 2024-02-29
 * @brief Clase abstracta Position para permitir representar
 * posiciones en retículos de cualquier dimensión. De esta se heredaran la clase 
 * PositionDim que podrá ser de 1 o 2 dimensiones.
 */

#ifndef POSITION_H
#define POSITION_H

#include "Lattice.h"
#include "Cell.h"

#include <iostream>
#include <utility>
#include <stdarg.h>

/**
 * @brief Clase abstracta Position para permitir representar posiciones en retículos
 * de cualquier dimensión. Se heredará de la clase Position. Ademas, cuenta con una
 * plantilla de clase para poder definir el tipo de coordenada que se usará.
 * @tparam Dim dimensión del retículo, puede ser 1 o 2
 * @tparam Coordinate_t define el tipo de coordenada que se usará
 */
typedef int Coor_t;
class Position {
 public:
  // Operador de acceso a la i-ésima coordenada
  virtual Coor_t operator[](unsigned int) const = 0;
};

#endif // POSITION_H

