/**
 * @file main.cc
 * @author ALba Pérez
 * @version 0.1
 * @date 2024-03-02
 * @brief Programa principal que implementa el juego de la vida.
 * Aquí se definen las clases y métodos necesarios para implementar el juego de la vida.
 * Econtramos funciones que ofencen el funcionamiento del juego de la vida. 
 * Comporbar argumentos, inicializar el juego, ejecutar el juego y mostrar el juego.
 */

#include "Lattice.h"
#include "CellLife.h"
#include "CellLife23_3.h"
#include "CellLife51_346.h"
#include "Lattice1D.h"
#include "Lattice2D.h"
#include "Cell.h"
#include "Position.h"
#include "PositionDim.h"
#include "Lattice1D_periodic.h"
#include "Lattice2D_reflective.h"
#include "Lattice2D_noBorder.h"
#include "Lattice1D_open.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <limits>

/**
 * @brief Función que se encarga de comprobar los argumentos introducidos por el usuario.
 * Para ello, se Hace uso de la librería iostream.
 * @param argc argumentos introducidos por el usuario
 * @param argv argumentos introducidos por el usuario
 */
void Usage(int argc, char* argv[]) {
  if (argc == 1) {
    std::cout << "No se han introducido argumentos. Pruebe con '" << argv[0] << " --help' para más información" << std::endl;
    exit(EXIT_FAILURE);
  }
  if ((argc == 2 && std::string(argv[1]) == "--help") || std::string(argv[1]) == "-h") {
    std::cout << "Modo de empleo: " << argv[0] << " -dim <d> -size <N,<…>> -cell <t> -border <b> [v] [-init <file>]" << std::endl;
    std::cout << "Donde: " << std::endl;
    std::cout << "  -dim <d> : Dimensión del autómata celular. Obligatorio si no se especifica -init." << std::endl;
    std::cout << "  -size <N,<…>> : Número de células para cada dimensión. Obligatorio si no se especifica -init." << std::endl;
    std::cout << "  -init <file> : Archivo de configuración inicial (opcional)" << std::endl;
    std::cout << "  -cell <t> : Tipo de célula. Puede ser 'Ace100', 'Life23_3', etc. Obligatorio." << std::endl;
    std::cout << "  -border <b> [v]: Tipo de frontera. Puede ser 'open' [0|1], 'reflective', 'periodic' o 'noborder. Obligatorio.'" << std::endl;
    std::cout << std::endl;
    std::cout << "Funcionalidades del programa:" << std::endl;
    std::cout << "  Este programa se encarga de hacer un autómata celular. Este es un modelo matemático y computacional para un sistema dinámico ";
    std::cout << "  que evoluciona en pasos discretos. Es adecuado para modelar sistemas naturales que puedan ser" << std::endl;
    std::cout << "  descritos como una colección masiva de objetos simples que interactúan localmente." << std::endl;
    std::cout << std::endl;
    std::cout << "Ejemplo: " << argv[0] << " -dim 2 -size 10,10 -cell Ace100 -border open 1 -init entrada.txt" << std::endl;
    exit(EXIT_FAILURE);
  }
}

/**
 * @brief Funcion que se encarga de comprobar los argumentos
 * Para ello, se hace uso de la librería iostream.
 * @param argc argumentos introducidos por el usuario
 * @param argv  argumentos introducidos por el usuario
 * @param dim dimensión del autómata celular
 * @param size tamaño del autómata celular
 * @param cellType  tipo de célula
 * @param filename archivo de configuración inicial
 */
void checkArgs(int argc, char* argv[], int& dim, std::vector<int>& size, std::string& cellType, std::string& filename) {
  for (int i = 1; i < argc; i++) {
    std::string arg = argv[i];
    // Comprobación del dim
    if (arg == "-dim") {
      if (i + 1 < argc) {
        dim = std::stoi(argv[++i]);
        if (dim <= 0) {
          std::cerr << "La dimensión del autómata celular debe ser un número entero positivo" << std::endl;
          exit(EXIT_FAILURE);
        }
      } else {
        std::cerr << "Dimensión del autómata celular no encontrada. Use '-dim <d>'" << std::endl;
        exit(EXIT_FAILURE);
      }
    // Comprobación del size
    } else if (arg == "-size") {
      if (i + 1 < argc) {
        std::string sizeArg = argv[++i];
        std::stringstream ss(sizeArg);
        int num;
        while (ss >> num) {
          size.push_back(num);
          if (ss.peek() == ',')
            ss.ignore();
        }
      } else {
        std::cerr << "Tamaño del autómata celular no encontrado. Use '-size <N,<…>>'" << std::endl;
        exit(EXIT_FAILURE);
      }
    // Comprobación del tipo de célula
    } else if (arg == "-cell") {
      if (i + 1 < argc) {
        cellType = argv[++i];
      } else {
        std::cerr << "Tipo de célula no encontrado. Use '-cell <t>'" << std::endl;
        exit(EXIT_FAILURE);
      }
    // Comprobación del archivo de configuración inicial
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
 * @brief Metodo que se encarga de inicializar el juego
 * Para ello, se hace uso de la librería iostream. Las opciones:
 * Presionar 'n' para calcular y mostrar la siguiente generación.
 * Presionar 'L' para calcular y mostrar las siguientes cinco generaciones.
 * Presionar 'c' para que los comandos 'n' y 'L' dejen de mostrar el estado y sólo se muestre la población.
 * Presionar 's' para salvar el autómata celular a un fichero.
 * Presionar 'x' para salir del juego.
 * @param filename nombre del archivo donde se guardará el autómata celular
 */
template <typename CellType, typename LatticeType>
void RunGame(const std::string& filename) {
  LatticeType lattice(filename);
  char option;
  // Bucle que se encarga de mostrar el autómata celular y las opciones que el usuario puede elegir
  do {
    std::cout << lattice;
    std::cout << "Población: " << lattice.Population() << std::endl;
    std::cout << "Opciones:\n"
              << "  n: Calcular y mostrar la siguiente generación\n"
              << "  L: Calcular y mostrar las siguientes cinco generaciones\n"
              << "  c: Cambiar el modo de visualización\n"
              << "  s: Guardar el estado actual en un archivo\n"
              << "  x: Salir del juego\n";
    std::cout << "Introduzca una opción: ";
    std::cin >> option;
    switch (option) {
      case 'n':
        lattice.NextGeneration();
        break;
      case 'L':
        for (int i = 0; i < 5; i++) {
          lattice.NextGeneration();
          std::cout << lattice;
          std::cout << "Población: " << lattice.Population() << std::endl;
        }
        break;
      case 'c':
        lattice.SetDisplay(false);
        break;
      case 's':
        lattice.Save(filename);
        std::cout << "El estado actual se ha guardado en el archivo " << filename << std::endl;
        break;
      case 'x':
        std::cout << "Saliendo del juego...." << std::endl;
        break;
      default:
        std::cout << "Opción no reconocida" << std::endl;
        break;
    }
  } while (option != 'x');
}

/**
 * @brief Función principal que se encarga de ejecutar el juego
 * Se encarga de ejecutar el juego de la vida.
 * @param argc número de argumentos
 * @param argv  argumentos introducidos por el usuario
 * @return int  valor de retorno
 */
int main(int argc, char* argv[]) {
  Usage(argc, argv);
  int dim = 0;
  std::vector<int> size;
  std::string cellType;
  std::string filename;
  // Comprobación de los argumentos
  checkArgs(argc, argv, dim, size, cellType, filename);
  // Si introducen un archivo de configuración inicial, dependiendo la dimension y el tipo de célula, se ejecuta el juego
  if (!filename.empty()) {
    if (dim == 2) {
      if (cellType == "Life23_3") {
        RunGame<CellLife<Position>, Lattice2D<Position>>(filename);
      } else if (cellType == "Life51_346") {
        RunGame<CellLife51_346<Position>, Lattice2D<Position>>(filename);
      } else {
        std::cerr << "Tipo de célula no reconocido" << std::endl;
        exit(EXIT_FAILURE);
      }
    } else if (dim == 1) {
      if (cellType == "Ace110") {
        RunGame<CellLife<Position>, Lattice1D<Position>>(filename);
      } else if (cellType == "Ace30") {
        RunGame<CellLife51_346<Position>, Lattice1D<Position>>(filename);
      } else {
        std::cerr << "Tipo de célula no reconocido" << std::endl;
        exit(EXIT_FAILURE);
      }
    } else {
      std::cerr << "Dimensión no reconocida" << std::endl;
      exit(EXIT_FAILURE);
    }
  // Si no se introduce un archivo de configuración inicial, se ejecuta el juego
  } else {
    if (dim == 2) {
      if (cellType == "Life23_3") {
        RunGame<CellLife<Position>, Lattice2D<Position>>(filename);
      } else if (cellType == "Life51_346") {
        RunGame<CellLife51_346<Position>, Lattice2D<Position>>(filename);
      } else {
        std::cerr << "Tipo de célula no reconocido" << std::endl;
        exit(EXIT_FAILURE);
      }
    } else if (dim == 1) {
      if (cellType == "Ace110") {
        RunGame<CellLife<Position>, Lattice1D<Position>>(filename);
      } else if (cellType == "Ace30") {
        RunGame<CellLife51_346<Position>, Lattice1D<Position>>(filename);
      } else {
        std::cerr << "Tipo de célula no reconocido" << std::endl;
        exit(EXIT_FAILURE);
      }
    } else {
      std::cerr << "Dimensión no reconocida" << std::endl;
      exit(EXIT_FAILURE);
    }
  }
  return 0;
}