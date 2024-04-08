/**
 * @file Cell.h
 * @author Alba Pérez Rodríguez
 * @version 0.1
 * @date 2024-02-29
 * @brief Clase abstracta Cell de la que derivan las clases CellACE y CellLife
 * Contiene las especificaciones y el código común a cualquier tipo de célula. 
 */

#ifndef CELL_H
#define CELL_H

#include "Lattice.h"
#include "Position.h"

#include <iostream>
#include <utility>
#include <vector>
#include <fstream>
#include <stdarg.h>

// Declaración adelantada de la clase Lattice
template <typename PositionType> 
class Lattice;

// Type alias para el estado de la célula
using State = bool;

/**
 * @brief Clase abstracta Cell de la que derivan las clases CellACE y CellLife
 * En ella se recogen las especificaciones y el código común a cualquier tipo de célula.
 * @tparam PositionType posición de la célula en el retículo
 */
template <typename PositionType>
class Cell {
 public:
  // Constructor por defecto
  Cell();
  Cell(Position& position, const State& state) : position_(position), state_(state) {}
  virtual State NextState(const Lattice<PositionType>& lattice) = 0;  // Calcula el estado de la célula en la siguiente generación
  State GetState() const { return state_; }  // Devuelve el estado de la célula
  void SetState(State state) { state_ = state; }  // Establece el estado de la célula
  void SetNextState(State state) { next_state_ = state; }  // Establece el estado de la célula en la siguiente generación
  virtual void UpdateState() { state_ = next_state_; }  // Actualiza el estado de la célula
  friend std::ostream& operator<<(std::ostream& os, const Cell& cell);
  virtual void Display(std::ostream& os) const = 0;  // Muestra el estado de la célula

 protected:
  Position& position_;  // Posición de la célula en el retículo
  State state_;  // Estado de la célula
  State next_state_;  // Estado de la célula en la siguiente generación
};


#endif // CELL_H