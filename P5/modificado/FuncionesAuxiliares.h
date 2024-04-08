/**
 * @file FuncionesAuxiliares.h
 * @author ALBA PÉREZ RODRÍGUEZ alu0101513768@ull.edu.es
 * @version 0.1
 * @date 2024-03-25
 * @brief Funciones auxiliares que se van a usar en el main.
 * Se define las funcoines de usage, parseargs y un struct para guardar los argumentos. 
 */

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H


#include <iostream>
#include <string>

/**
 * @brief Estructura Options que contiene las opciones que se pueden pasar por línea de comandos.
 * Se debe pasar el tamaño de la secuencia, el tipo de ordenación, la introducción de datos y si
 * se quiere mostrar el rastro.
 */
struct Options {
  unsigned sequenceSize;
  std::string ordenationType;
  std::string introducingData;
  bool trace = false;
  std::string fileName;
};

// Función que imprime un mensaje rodeado de asteriscos en forma de caja
void PrintBox(const std::string& message);
// Muestra el uso del programa
void Usage(int argc, char* argv[]);
// Parsea los argumentos de la línea de comandos
Options ParseArguments(int argc, char* argv[]);

#endif