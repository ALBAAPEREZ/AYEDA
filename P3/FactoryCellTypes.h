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

#ifndef FACTORY_CELL_TYPES
#define FACTORY_CELL_TYPES

#include "FactoryCell.h"
#include "Position.h"
#include "Cell.h"
#include "CellLife.h"
#include "CellLife23_3.h"
#include "CellLife51_346.h"

/**
 * @brief Clase que implementa la creación de células del tipo ACE110
 * Se implementa el método CreateCell que devuelve un puntero a una célula del tipo ACE110
 * @tparam PositionType representa el tipo de dato que se utiliza para representar la posición de la célula
 */
template <typename PositionType>
class FactoryCellACE110 : public FactoryCell {
 public:
  // Método creador de células
  Cell* CreateCell(PositionType& position, char state) const override {
    return new CellACE110(position, state);
  }
};

/**
 * @brief Clase que implementa la creación de células del tipo ACE30
 * Se implementa el método CreateCell que devuelve un puntero a una célula del tipo ACE30
 * @tparam PositionType PositionType representa el tipo de dato que se utiliza para representar la posición de la célula
 */
template <typename PositionType>
class FactoryCellACE30 : public FactoryCell {
 public:
 // Método creador de células
  Cell* CreateCell(PositionType& position, char state) const override {
    return new CellACE30(position, state);
  }
};

/**
 * @brief Clase que implementa la creación de células del tipo ACE23_3
 * Se implementa el método CreateCell que devuelve un puntero a una célula del tipo ACE23_3
 * Se crea un puntero a una célula del tipo ACE23_3
 * @tparam PositionType posición de la celda
 */
template <typename PositionType>
class FactoryCellACE23_3 : public FactoryCell {
 public:
  // Método creador de células
  Cell* CreateCell(PositionType& position, char state) const override {
    return new CellACE23_3(position, state);
  }
};

/**
 * @brief Clase que implementa la creación de células del tipo ACE51_346
 * Se implementa el método CreateCell que devuelve un puntero a una célula del tipo ACE51_346
 * Se crea un puntero a una célula del tipo ACE51_346
 * @tparam PositionType PositionType representa el tipo de dato que se utiliza para representar la posición de la célula
 */
template <typename PositionType>
class FactoryCellACE51_346 : public FactoryCell {
 public:
  // Método creador de células
  Cell* CreateCell(PositionType& position, char state) const override {
    return new CellACE51_346(position, state);
  }
};

#endif // FACTORY_CELL_TYPES