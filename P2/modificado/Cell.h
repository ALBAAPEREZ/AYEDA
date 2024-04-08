/**
 * ************ PRÁCTICA 2 *************
 * @file Cell.h
 * @author ALBA PÉREZ RODRÍGUEZ
 * @version 0.1
 * @date 2024-02-22
 * @brief Creación de la clase Autómata Celular.
 * Se definen diferentes typedefs, se crea la clase Cell y se definen los métodos de la clase.
 * Un enum para los dos posibles estados de una célula. 
 * Dentro de la clase Cell definimos varios constructores, un destructor, getters y setters. 
 * Como atributos privados de la clase, tenemos el estado de la célula, la posición de la célula en el retículo,
 * el número de vecinos vivos y el siguiente estado de la célula.
 */

#include <iostream>
#include <vector>
#include <utility>

#include "Lattice.h"

#ifndef CELL_H
#define CELL_H

// Declaración adelantada de la clase Lattice
class Lattice;

// Deficion de tipos --> similar a typedef
using State = bool;
using Position = std::pair<int, int>;

/**
 * @brief Enumerado que representa los dos posibles estados de una célula
 * DEAD REPRESENTA EL ESTADO 0
 * ALIVE REPRESENTA EL ESTADO 1
 */
enum StateValue { DEAD, ALIVE };

/**
 * @brief La célula, Cell,es responsable de encapsular su estado binario y su posición dentro del
 * retículo unidimensional que representa al espacio celular. También es responsable de
 * conocer su vecindad y su función de transición
 */
class Cell {
 public:
  // Constructor por defecto
  Cell() {}
  Cell(const Position&, const State&);
  // Getters y setters de la clase
  State getState() const;
  // método modificador para poder establecer la configuración inicial.
  void setState(State);
  // Setter para position
  void setPosition(const Position&);
  // recibe el retículo por parámetro y calcula el siguiente estado sin evolucionar.
  int NextState(const Lattice&);
  // la evolución del autómata celular consiste en hacer que cada célula actualice su valor de estado.
  void UpdateState();
  // método que devuelve el número de vecinos vivos de la célula.
  int Neighbors(const Lattice& lattice);
  // método que imprime el estado de la célula.
  friend std::ostream& operator<<(std::ostream&, const Cell&);
 private:
  State state_; // estado de la célula --> vivo o muerto
  Position position_; // posición de la célula en el retículo
  int neighbors_; // vecinos de la célula vivos
  State next_state_; // siguiente estado de la célula
};

// Sobrecarga del operador de salida
std::ostream& operator<<(std::ostream&, const Cell&);

#endif // CELL_H