/**
 * ************ PRÁCTICA 1 *************
 * @file Lattice.h
 * @author ALBA PÉREZ RODRÍGUEZ
 * @version 0.1
 * @date 2024-02-07
 * @brief Creación de la clase Retículo. 
 * Este objeto es responsable de crear y almacenar las células que representan el espacio celular. 
 * También es responsable de controlar la evolución y llevar la cuenta de las generaciones.
 * Se compone de un constructor que recibe el tamaño del retículo y el tipo de frontera, otro constructor que recibe el tamaño del retículo, 
 * el tipo de frontera y el archivo de configuración inicial, un método que devuelve la célula en la posición dada, un método que evoluciona el autómata celular 
 * y un método que imprime el estado del retículo. Ademas, se sobrecarga el operador de salida.
 * 
*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <new>
#include <limits>

#ifndef LATTICE_H
#define LATTICE_H

#include "Cell.h"

/**
 * @brief Enumerado que representa los tres posibles tipos de frontera
 * Puede ser fria, caliente o periodica
 */
enum BorderType { PERIODIC, REFLECTIVE, OPEN };

// Declaración adelantada de la clase Cell
class Cell;

/**
 * @brief Clase Retículo 
 * Esta clase contiene los métodos y atributos necesarios para crear y almacenar las 
 * células que representan el espacio celular. Controla la evolución y lleva la cuenta de las generaciones.
 */
class Lattice {
 public:
  // Constructor al que se le pasa en tamaño del retículo y lo contruye
  Lattice(const int& size, const BorderType& borderType, char* argv[]);
  // Constructor al que se le pasa el tamaño del retículo, el tipo de frontera y el archivo de configuración inicial
  Lattice(const int, const BorderType&, const std::string&, char* argv[]);
  // Destructor de la clase para liberar la memoria de las células
  ~Lattice();
  // Getters de la clase
  std::vector<Cell*> getCells() const { return cells_; }
  int getSize() const { return size_; }
  // método que devuelve la célula en la posición dada.
  const Cell& getCell(const Position&) const;
  // método que evoluciona el autómata celular.
  void NextGeneration();
  // método que imprime el estado del retículo.
  friend std::ostream& operator<<(std::ostream&, const Lattice&);
 private:
  std::vector<Cell*> cells_;
  int size_;
  // tipo de frontera
  BorderType borderType_;
};

// Sobrecarga del operador de salida
std::ostream& operator<<(std::ostream&, const Lattice&);

#endif // LATTICE_H