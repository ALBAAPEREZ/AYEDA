/**
 * @file AuxiliarFunctions.h
 * @author ALBA PÉREZ RODRÍGUEZ
 * @version 0.1
 * @date 2024-03-10
 * @copyright Copyright (c) 2024
 * @brief Funciones auxiliares para el manejo de la línea de comandos.
 * Se declara la estructura Options que contiene las opciones que se pueden pasar por línea de comandos.
 */

#include <iostream>
#include <string>


/**
 * @brief Struct Options que contiene las opciones que se pueden pasar por línea de comandos.
 * Se debe pasar el tamaño de la tabla, la función de dispersión, el tipo de hash, 
 * el tamaño del bloque y la función de exploración.
 */
struct Options {
  unsigned tableSize;
  std::string dispersionFunction;
  std::string hashType;
  unsigned blockSize = 0;
  std::string explorationFunction;
  unsigned num;
};

// Muestra el uso del programa
void Usage(int argc, char* argv[]);
// Parsea los argumentos de la línea de comandos
Options ParseArguments(int argc, char* argv[]);