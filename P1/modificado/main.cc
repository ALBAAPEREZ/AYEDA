/**
 * ************ PRÁCTICA 1 *************
 * @file main.cc
 * @author ALBA PÉREZ RODRÍGUEZ
 * @version 0.1
 * @date 2024-02-07
 * @brief Programa principal. Este programa se encarga de hacer un autómata celular. 
 * Se recibe por línea de comandos el tamaño del retículo, el tipo de frontera y el archivo de configuración inicial.
 * Se crea el retículo y se evoluciona el autómata celular. La simulación se puede detener en cualquier momento pulsando un carácter elegido como fin de ejecución.
*/

#include <iostream>
#include <fstream>
#include <cstring>

#include "Cell.h"
#include "Lattice.h"

/**
 * @brief Función que imprime el modo de empleo del programa
 * Si no se especifica ningún argumento o se especifica --help, se imprime el modo de empleo
 * @param argc número de argumentos
 * @param argv nombre de los argumentos
 */
void Usage(int argc, char* argv[]) {
  if (argc == 1) {
    std::cout << "No se han introducido argumentos. Pruebe con '" << argv[0] << " --help' para más información" << std::endl;
    exit(EXIT_FAILURE);
  }
  if ((argc == 2 && std::string(argv[1]) == "--help") || std::string(argv[1]) == "-h") {
    std::cout << "Modo de empleo: " << argv[0] << " -size <n> -border <type> [0|1] [-init <file>]" << std::endl;
    std::cout << "Donde: " << std::endl;
    std::cout << "  -size <n> : Tamaño del retículo obligatorio" << std::endl;
    std::cout << "  -border <type> [0|1]: Tipo de frontera. Puede ser 'open', 'periodic' o 'reflective. Obligatotio.'" << std::endl;
    std::cout << "  -init <file> : Archivo de configuración inicial (opcional)" << std::endl;
    std::cout << std::endl;
    std::cout << "Funcionalidades del programa:" << std::endl;
    std::cout << "  Este programa se encarga de hacer un autómata celular. Este es un modelo matemático y computacional para un sistema dinámico ";
    std::cout << "  que evoluciona en pasos discretos. Es adecuado para modelar sistemas naturales que puedan ser" << std::endl;
    std::cout << "  descritos como una colección masiva de objetos simples que interactúan localmente." << std::endl;
    std::cout << std::endl;
    std::cout << "Ejemplo: " << argv[0] << " -size 10 -border open 1 -init entrada.txt" << std::endl;
    exit(EXIT_FAILURE);
  }
}

/**
 * @brief Funcion que se encarga de comprobar los argumentos
 * Hace todo el control de versiones de los argumentos.
 * @param argc es el número de argumentos
 * @param argv es el nombre de los argumentos
 * @param size tamaño del reticulo
 * @param borderType tipo de frontera que se le asigna al retículo por linea de comandos
 */
void checkArgs(int argc, char* argv[], int& size, BorderType& borderType, std::string& filename) {
  for (int i = 1; i < argc; i++) {
    std::string arg = argv[i];
    // Comprobación del size
    if (arg == "-size") {
      if (i + 1 < argc) {
        size = std::stoi(argv[++i]);
        if (size <= 0) {
          std::cerr << "El tamaño del retículo debe ser un número entero positivo" << std::endl;
          exit(EXIT_FAILURE);
        }
      } else {
        std::cerr << "Tamaño del retículo no encontrado. Use '-size <n>'" << std::endl;
        exit(EXIT_FAILURE);
      }
    // Comprobación del tipo de frontera
    } else if (arg == "-border") {
       if (i + 1 < argc) {
        std::string borderArg = argv[++i];
        // Comprobación directa de las opciones válidas
        if (borderArg == "open") {
          borderType = OPEN;
          if (i + 1 < argc) {
            int option = std::stoi(argv[++i]);
            if (option != 0 && option != 1) {
              std::cerr << "La opción de frontera abierta debe ser 0 o 1" << std::endl;
              exit(EXIT_FAILURE);
            }
          } else {
            std::cerr << "Opción de frontera abierta no encontrada. Use '-border open <option>'" << std::endl;
            exit(EXIT_FAILURE);
          }
        } else if (borderArg == "periodic") {
          borderType = PERIODIC;
        } else if (borderArg == "reflective") {
          borderType = REFLECTIVE;
        } else {
          std::cerr << "Tipo de frontera no reconocido. Use '-border <type>'" << std::endl;
          exit(EXIT_FAILURE);
        }
      } else {
        std::cerr << "Tipo de frontera no encontrado. Use '-border <type>'" << std::endl;
        exit(EXIT_FAILURE);
      }
    // Comprobación del archivo de configuración inicial -- > si existe
    } else if (arg == "-init") {
      if (i + 1 < argc) {
        filename = argv[++i];
      } else {
        std::cerr << "Archivo de configuración inicial no encontrado. Use '-init <filename>'" << std::endl;
        exit(EXIT_FAILURE);
      }
    } else {
      std::cerr << "Argumento no reconocido: " << arg << std::endl;
      exit(EXIT_FAILURE);
    }
  }
}

/**
 * @brief Función que evoluciona el autómata celular
 * Se encarga de evolucionar el autómata celular.
 * La simulación se puede detener en cualquier momento pulsando un carácter elegido como fin de ejecución.
 * En este caso, se detiene la simulación si el usuario pulsa la tecla 'q'.
 * @param lattice reticulo a evolucionar 
 */
void CellEvolution(Lattice& lattice) {
  unsigned iteration = 0;
  char user_input;
  std::cout << "Press 'q' to quit or 'Enter' to continue: ";
  do {
    std::cout << lattice << "Iteration: " << iteration++ << std::endl;
    lattice.NextGeneration();
    user_input = std::cin.get();
    // mientras que el usuario no pulse la tecla 'q' se sigue evolucionando
  } while (user_input != 'q');
}

/**
 * @brief Programa principal main
 * Aquí se recibe por línea de comandos el tamaño del retículo, el tipo de frontera y el archivo de configuración inicial
 * A partir de estos datos se crea el retículo y se evoluciona el autómata celular.
 * La simulación se puede detener en cualquier momento pulsando un carácter elegido como fin de ejecución.
 * @param argc numero de argumentos
 * @param argv nombre de los argumentos
 * @return int retorna 0 si se ejecuta correctamente
 */
int main(int argc, char* argv[]) {
  // Utilización del programa
  Usage(argc, argv);
  int size;
  BorderType borderType;
  std::string borderType_aux{argv[4]};
  std::string filename;
  // Asignamos el tipo de frontera
  if (borderType_aux == "open") {
    borderType = OPEN;
  } else if (borderType_aux == "periodic") {
    borderType = PERIODIC;
  } else if (borderType_aux == "reflective") {
    borderType = REFLECTIVE;
  }
  // Comprobamos los argumentos
  checkArgs(argc, argv, size, borderType, filename);
  // Si el archivo de configuración inicial está vacío, se crea el retículo sin él
  if (filename.empty()) {
    Lattice lattice(size, borderType, argv);
    CellEvolution(lattice);
  // Si el archivo de configuración inicial no está vacío, se crea el retículo con él
  } else {
    Lattice lattice(size, borderType, filename, argv);
    CellEvolution(lattice);
  }
  std::cout << "Ending simulation." << std::endl;
  return 0;
}