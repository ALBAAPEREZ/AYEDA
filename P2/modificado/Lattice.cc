/**
 * ************ PRÁCTICA 2 *************
 * @file Lattice.cc
 * @author ALBA PÉREZ RODRÍGUEZ
 * @version 0.1
 * @date 2024-02-22
 * @brief Creación de la clase Retículo. 
 * Aqui se localian los metodos de la clase Retículo. Encontramos los constructores, el destructor, 
 * los métodos de acceso a las células, el método que evoluciona el autómata celular, 
 * el método que devuelve el número de células vivas en el retículo y la sobrecarga del operador de salida.
 */

#include "Lattice.h"

/**
 * @brief Constructor que se encarga de inicializar el retículo cuando no hay archivo de configuración inicial.
 * Se crea un vector de células y se inicializa cada una con el estado correspondiente.
 * Si el tipo de frontera es caliente, se establecen las células en los bordes en estado de vida (ALIVE).
 * Si el tipo de frontera es de bucle, se ajustan los estados de las células en los bordes.
 * Si el tipo de frontera es frío, no se hace nada.
 * @param size tamaño que se le asigna al retículo por linea de comandos
 * @param borderType Tipo de frontera que se le asigna al retículo por linea de comandos
 */
Lattice::Lattice(const BorderType& border, char* argv[]) {
  rows_ = std::atoi(argv[2]);
  columns_ = std::atoi(argv[3]);
  if (border == REFLECTIVE) {
    cells_.resize(std::atoi(argv[2]) + 2, std::vector<Cell*>(std::atoi(argv[3]) + 2));
    for (int i = 0; i < std::atoi(argv[2]) + 2; ++i) {
      for (int j = 0; j < std::atoi(argv[3]) + 2; ++j) {
        cells_[i][j] = new Cell({i, j}, DEAD);
      }
    }
    // Llamar a la función auxiliar para solicitar por teclado las posiciones de las células vivas
    for (int i = 1; i < std::atoi(argv[2]) + 1; ++i) {
      for (int j = 1; j < std::atoi(argv[3]) + 1; ++j) {
        requestUserInput(i, j);
      }
    }
    rows_ += 2;
    columns_ += 2;
  } else if (border == NOFRONTER) {
    cells_.resize(std::atoi(argv[2]), std::vector<Cell*>(std::atoi(argv[3])));
    for (int i = 0; i < std::atoi(argv[2]); ++i) {
      for (int j = 0; j < std::atoi(argv[3]); ++j) {
        cells_[i][j] = new Cell({i, j}, DEAD);
      }
    }
    for (int i = 0; i < std::atoi(argv[2]); ++i) {
      for (int j = 0; j < std::atoi(argv[3]); ++j) {
        requestUserInput(i, j);
      }
    }
  }
  // Aplicar las fronteras según lo indicado por el usuario
  applyBorders(border, argv);
}

/**
 * @brief Método que solicita al usuario el estado inicial de una célula.
 * Se encarga de solicitar al usuario el estado inicial de una célula.
 * Se le pide al usuario que ingrese el estado inicial de la célula en la posición [i, j].
 * @param i indice de la fila
 * @param j indice de la columna
 */
void Lattice::requestUserInput(int i, int j) {
  std::cout << "Ingrese el estado inicial (0 para muerta, 1 para viva) de la celda en la posición [" << i << ", " << j << "]: ";
  int inputState;
  std::cin >> inputState;
  cells_[i][j]->setState((State)(inputState));
}

/**
 * @brief Método que aplica las fronteras al retículo.
 * Se encarga de aplicar las fronteras al retículo.
 * Si el tipo de frontera es OPEN,J Y 1 se establecen las células en los bordes en estado de vida (ALIVE).
 * Si es open y 0 se establecen las células en los bordes en estado de muerte (DEAD).
 * Si es periodic, se ajustan los estados de la forma correspondiente.
 * Si es reflective, se ajustan los estados de la forma correspondiente.
 * Si es nofronter, se ajustan los estados de la forma correspondiente.
 * @param border tipo de frontera
 * @param argv argumentos de la linea de comandos
 */
void Lattice::applyBorders(const BorderType& border, char* argv[]) {
  if (border == OPEN) {
    if (atoi(argv[5]) == 0 || atoi(argv[5]) == 1) {
      // Valor del estado para las celdas de la frontera
      State borderState = (State)(atoi(argv[5]));
      // Añadir una célula en cada borde con el estado fijo
      for (int i = 0; i < rows_; ++i) {
        cells_[i][0]->setState(borderState);
        cells_[i][columns_ - 1]->setState(borderState);
      }
      for (int i = 0; i < columns_; ++i) {
        cells_[0][i]->setState(borderState);
        cells_[rows_ - 1][i]->setState(borderState);
      }
    } else {
      std::cout << "Error, valor " << argv[5] << " invalido" << std::endl;
    }
  // Si el tipo de frontera es periódica, ajusta los estados de las células en los bordes.
  } else if (border == PERIODIC) {
    for (int i = 0; i < rows_; ++i) {
      cells_[i][0] = cells_[i][columns_ - 2];
      cells_[i][columns_ - 1] = cells_[i][1];
    }
    for (int j = 0; j < columns_; ++j) {
      cells_[0][j] = cells_[rows_ - 2][j];
      cells_[rows_ - 1][j] = cells_[1][j];
    }
  // Si el tipo de frontera es reflejante, ajusta los estados de las células en los bordes.
  // MODIFICACION --> VECINDAD EN CRUZ DOBLE POR LOS LADOS. 
  // Las diagonales no se toman en cuenta, solo los lados.
  } else if (border == REFLECTIVE) {
    // Reflejar las esquinas
    cells_[0][0] = cells_[2][2];
    cells_[rows_ - 1][0] = cells_[rows_ - 3][2];
    cells_[0][columns_ - 1] = cells_[2][columns_ - 3];
    cells_[rows_ - 1][columns_ - 1] = cells_[rows_ - 3][columns_ - 3];
    // Reflejar los bordes 
    // Recorremos el retículo y ajustamos los estados de las células en los bordes.
    for (int i = 2; i < rows_ - 2; ++i) {
      cells_[i][0] = cells_[i][2];
      cells_[i][1] = cells_[i][3];
      cells_[i][columns_ - 1] = cells_[i][columns_ - 3];
      cells_[i][columns_ - 2] = cells_[i][columns_ - 4];
    }
    // Recorremos el retículo y ajustamos los estados de las células en los bordes.
    for (int i = 2; i < columns_ - 2; ++i) {
      cells_[0][i] = cells_[2][i];
      cells_[1][i] = cells_[3][i];
      cells_[rows_ - 1][i] = cells_[rows_ - 3][i];
      cells_[rows_ - 2][i] = cells_[rows_ - 4][i];
    }
    // Si no hay frontera se ajustan los estados de las células en los bordes.
  } else if (border == NOFRONTER) {
    // Crear una nueva matriz con el tamaño expandido
    for (int i = 0; i < std::atoi(argv[2]); ++i) {
      std::cout << "it i: " << i << std::endl;
      for (int j = 0; j < std::atoi(argv[3]); ++j) {
        if (j == 5) exit(EXIT_FAILURE);
        std::cout << "it j: " << j << std::endl;
        if (i == 0 && j == 0 && cells_[i][j]->getState() == ALIVE) {
          std::vector<Cell*> temp(std::atoi(argv[3]) + 1);
          for (int k = 0; k < std::atoi(argv[3]) + 1; ++k) {
            temp[k] = new Cell({i, j}, DEAD);
          }
          cells_.insert(cells_.begin(), temp);
          for (long unsigned k = 1; k < cells_.size(); ++k) {
            cells_[k].insert(cells_[k].begin(), new Cell({i, j}, DEAD));
          }
          for (long unsigned k = 0; k < cells_.size(); ++k) {
            for (long unsigned l = 0; l < cells_[k].size(); ++l) {
              cells_[k][l]->setPosition({k, l});
            } 
          }
          ++rows_;
          ++columns_;
        } else if (i == 0 && j == std::atoi(argv[3]) - 1 && cells_[i][j]->getState() == ALIVE) {
          std::vector<Cell*> temp(std::atoi(argv[3]) + 1);
          for (int k = 0; k < std::atoi(argv[3]) + 1; ++k) {
            temp[k] = new Cell({i, j}, DEAD);
          }
          cells_.insert(cells_.begin(), temp);
          for (long unsigned k = 1; k < cells_.size(); ++k) {
            cells_[k].push_back(new Cell({i, j}, DEAD));
          }
          for (long unsigned k = 0; k < cells_.size(); ++k) {
            for (long unsigned l = 0; l < cells_[k].size(); ++l) {
              cells_[k][l]->setPosition({k, l});
            } 
          }
          ++rows_;
          ++columns_;
        } else if (i == std::atoi(argv[2]) - 1 && j == 0 && cells_[i][j]->getState() == ALIVE) {
          std::vector<Cell*> temp(std::atoi(argv[3]) + 1);
          for (int k = 0; k < std::atoi(argv[3]) + 1; ++k) {
            temp[k] = new Cell({i, j}, DEAD);
          }
          cells_.push_back(temp);
          for (long unsigned k = 1; k < cells_.size(); ++k) {
            cells_[k].insert(cells_[k].begin(), new Cell({i, j}, DEAD));
          }
          for (long unsigned k = 0; k < cells_.size(); ++k) {
            for (long unsigned l = 0; l < cells_[k].size(); ++l) {
              cells_[k][l]->setPosition({k, l});
            } 
          }
          ++columns_;
          ++rows_;
        } else if (i == std::atoi(argv[2]) - 1 && j == std::atoi(argv[3]) - 1 && cells_[i][j]->getState() == ALIVE) {
          std::vector<Cell*> temp(std::atoi(argv[3]) + 1);
          for (int k = 0; k < std::atoi(argv[3]) + 1; ++k) {
            temp[k] = new Cell({i, j}, DEAD);
          }
          cells_.push_back(temp);
          for (long unsigned k = 1; k < cells_.size(); ++k) {
            cells_[k].push_back(new Cell({i, j}, DEAD));
          }
          for(long unsigned k = 0; k < cells_.size(); ++k) {
            for (long unsigned l = 0; l < cells_[k].size(); ++l) {
              cells_[k][l]->setPosition({k, l});
            } 
          }
          ++columns_;
          ++rows_;
        } else {
          if (i == 0) {
            std::vector<Cell*> temp(std::atoi(argv[3]));
            for (int k = 0; k < std::atoi(argv[3]); ++k) {
              temp[k] = new Cell({i, j}, DEAD);
            }
            cells_.insert(cells_.begin(), temp);
            for (long unsigned k = 0; k < cells_.size(); ++k) {
              cells_[k][j]->setPosition({k, j});
            }
            ++rows_;
          } else if (i == std::atoi(argv[2]) - 1) {
            std::vector<Cell*> temp(std::atoi(argv[3]));
            for (int k = 0; k < std::atoi(argv[3]); ++k) {
              temp[k] = new Cell({i, j}, DEAD);
            }
            cells_.push_back(temp);
            for (long unsigned k = 0; k < cells_.size(); ++k) {
              cells_[k][j]->setPosition({k, j});
            }
            ++rows_;
          } else if (j == 0) {
            for (long unsigned k = 0; k < cells_.size(); ++k) {
              cells_[k].insert(cells_[k].begin(), new Cell({i, j}, DEAD));
            }
            for (long unsigned k = 0; k < cells_.size(); ++k) {
              cells_[k][j]->setPosition({k, j});
            }
            ++columns_;
          } else if (j == std::atoi(argv[3]) - 1) {
            for (long unsigned k = 0; k < cells_.size(); ++k) {
              cells_[k].push_back(new Cell({i, j}, DEAD));
            }
            for (long unsigned k = 0; k < cells_.size(); ++k) {
              cells_[k][j]->setPosition({k, j});
            }
            ++columns_;
          }
        }
      }
    }
  }
}

/**
 * @brief Construct a new Lattice:: Lattice object
 * Se encarga de inicializar el retículo cuanco se le pasa un archivo de configuración inicial.
 * Se crea un vector de células y se inicializa cada una con el estado correspondiente.
 * Si el tipo de frontera es caliente, se establecen las células en los bordes en estado de vida (ALIVE).
 * Si el tipo de frontera es de bucle, se ajustan los estados de las células en los bordes.
 * Si el tipo de frontera es frío, no se hace nada.
 * Además, se lee el estado inicial del autómata celular desde un archivo.
 */
Lattice::Lattice(const BorderType& border, std::string& filename) {
  // Assign the border type
  borderType_ = border;
  // Open the file
  std::ifstream file(filename);
  if (!file.is_open()) {
    throw std::runtime_error("Could not open the file");
  }
  // Read the number of rows and columns from the file
  std::string line;
  if (std::getline(file, line)) {
    rows_ = std::stoi(line);
  } else {
    throw std::runtime_error("Error reading the number of rows");
  }
  if (std::getline(file, line)) {
    columns_ = std::stoi(line);
  } else {
    throw std::runtime_error("Error reading the number of columns");
  }
  if (rows_ <= 0 || columns_ <= 0) {
    throw std::runtime_error("The number of rows and columns must be greater than 0");
  }
  std::cout << "Number of rows: " << rows_ << std::endl;
  std::cout << "Number of columns: " << columns_ << std::endl;
  // Adjust the size of the lattice to include borders
  cells_.resize(rows_, std::vector<Cell*>(columns_));
  for (int i = 1; i < rows_ - 1; ++i) {
    std::istringstream iss(line);
    for (int j = 1; j < columns_ - 1; ++j) {
      int cellState;
      if (!(iss >> cellState)) {
        throw std::runtime_error("Error reading cell state");
      }
      cells_[i][j] = new Cell({i, j}, (cellState == 1) ? ALIVE : DEAD);
    }
  }
  // Borders
  applyBorders(border, nullptr);
}

/**
 * @brief Destroy the Lattice:: Lattice object
 * Destructor de clase que se encarga de liberar la memoria de las células.
 * Se encarga de liberar la memoria de las células.
 */
Lattice::~Lattice() {
  if (borderType_ == REFLECTIVE) {
    for (int i = 1; i < rows_ - 1; ++i) {
      for (int j = 1; j < columns_ - 1; ++j) {
        delete cells_[i][j];
        cells_[i][j] = nullptr;
      }
    }
  } else if (borderType_ == NOFRONTER) {
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < columns_; ++j) {
        delete cells_[i][j];
        cells_[i][j] = nullptr;
      }
    }
  }
}

/**
 * @brief Método que devuelve la célula en la posición dada.
 * Se encarga de devolver la célula en la posición dada
 * @return const Cell& devuelve la célula en la posición dada
 */
const Cell& Lattice::getCell(const Position& position) const {
  return *(cells_[position.first][position.second]);
}

/**
 * @brief Get the Border object
 * Getter que devuelve el tipo de frontera
 * @return const LBorderType& retorna el tipo de frontera
 */
const BorderType& Lattice::getBorder() const {
  return borderType_;
}

/**
 * @brief Set the Rows object
 * Setter que establece el número de filas.
 */
void Lattice::setRows(int rows) {
  rows_ = rows;
}

/**
 * @brief Set the Columns object
 * setter que establece el número de columnas.
 */
void Lattice::setColumns(int columns) {
  columns_ = columns;
}

/**
 * @brief Función que evoluciona el autómata celular en formato matriz
 * Se encarga de evolucionar el autómata celular.
 * Se ajustan los estados de las células en los bordes.
 * Se recorre el retículo y se calcula el siguiente estado de cada célula.
 * 
 */
void Lattice::NextGeneration() {
  if (borderType_ == REFLECTIVE) {
    // Recorremos el retículo y calculamos el siguiente estado de cada célula.
    for (int i = 1; i < rows_- 1; ++i) {
      for (int j = 1; j < columns_- 1; ++j) {
        cells_[i][j]->NextState(*this);
      }
    }
    // Recorremos el retículo y actualizamos el estado de cada célula.
    for (int i = 1; i < rows_- 1; ++i) {
      for (int j = 1; j < columns_ - 1; ++j) {
        cells_[i][j]->UpdateState();
      }
    }
  } else if (borderType_ == NOFRONTER) {
    std::cout << rows_ << " " << columns_ << std::endl;
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < columns_; ++j) {
        cells_[i][j]->NextState(*this);
      }
    }
    // Recorremos el retículo y actualizamos el estado de cada célula.
    for (int i = 1; i < rows_- 1; ++i) {
      for (int j = 1; j < columns_ - 1; ++j) {
        cells_[i][j]->UpdateState();
      }
    }
    applyBorders(borderType_, nullptr);
  }
}

/**
 * @brief Función que devuelve el número de células vivas en el retículo.
 * Se encarga de devolver el número de células vivas en el retículo
 * Para ello, se recorre el retículo y se cuenta el número de células vivas.
 * @return std::size_t retorna el número de células vivas en el retículo
 */
std::size_t Lattice::Population() const {
  std::size_t population = 0;
  // Se recorre el retículo y se cuenta el número de células vivas.
  for (int i = 1; i < rows_ - 1; ++i) {
    for (int j = 1; j < columns_ - 1; ++j) {
      if (cells_[i][j]->getState() == ALIVE) {
        population++;
      }
    }
  }
  return population;
}

/**
 * @brief Metodo que se encarga de guardar el estado del retículo en un string
 * Lo que hace es recorrer el retículo y guardar el estado de cada célula en un string
 * Para ello, si la célula está muerta, se guarda un espacio, si está viva, se guarda una X.
 * @param lattice 
 * @return std::string 
 */
std::string Lattice::SaveToString(std::string& lattice) {
  for (int i = 1; i < getRows() - 1; ++i) {
    for (int j = 1; j < getColumns() - 1; ++j) {
      lattice += (getCell({i, j}).getState() == DEAD) ? " " : "X";
    }
    lattice.push_back('\n');
  }
  return lattice;
}

/**
 * @brief Sobrecarga del operador de acceso a las células del retículo
 *  Permite acceder a las células del retículo en la posicion [i][j]
 * @return Cell& retorna la célula en la posición dada
 */
Cell& Lattice::operator[](const Position& position) {
  return *(cells_[position.first][position.second]);
}

/**
 * @brief Sobre carga del operador de inserción
 * Se encarga de imprimir el estado del retículo 
 * @param os flujo de salida
 * @param reticulo retículo a imprimir
 * @return std::ostream& flujo de salida
 */
std::ostream& operator<<(std::ostream& os, const Lattice& lattice) {
 // Recorremos todo el retículo e imprimimos el estado de cada célula
  if (lattice.getBorder() == NOFRONTER) {
    for (int i = 0; i < lattice.getRows(); ++i) {
      for (int j = 0; j < lattice.getColumns(); ++j) {
        os << lattice.getCell({i, j});
      }
      os << std::endl;
    }
  } else {
    for (int i = 1; i < lattice.getRows() - 1; ++i) {
      for (int j = 1; j < lattice.getColumns() - 1; ++j) {
        os << lattice.getCell({i, j});
      }
      os << std::endl;
    }
  }
  return os;
}

