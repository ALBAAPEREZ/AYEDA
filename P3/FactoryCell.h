/**
 * @file FactoryCell.h
 * @author Alba Pérez Rodríguez
 * @version 0.1
 * @date 2024-02-29
 * @brief Clase abstracta FactoryCell que se encarga de definir e implementar las responsabilidades
 * de una fábrica de células. A partir de la clase base se derivan dos tipos de fábricas:
 * 1. FactoryCellAce100
 * 2. FactoryCellACE30
 * 3. FactoryCellLife23/3
 * 4. FactoryCellLife51/346
 * @tparam PositionType representa el tipo de dato que se utiliza para representar la posición de la célula
 * @see Cell.h
 */

#ifndef FACTORYCELL_H
#define FACTORYCELL_H


#include "Cell.h"
#include "Position.h"
#include "Lattice.h"

/**
 * @brief Clase abstracta FactoryCell que se encarga de definir e implementar las responsabilidades
 * de una fábrica de células. A partir de la clase base se derivan dos tipos de fábricas:
 * 1. FactoryCellAce100
 * 2. FactoryCellACE30
 * 3. FactoryCellLife23/3
 * 4. FactoryCellLife51/346
 * @tparam PositionType representa el tipo de dato que se utiliza para representar la posición de la célula
 */
template <typename PositionType>
class FactoryCell {
 public:
  // Método creador de células
  virtual Cell* createCell(const Position&, const State&) = 0;
};

#endif // FACTORYCELL_H