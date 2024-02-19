/**
 * ************ PRÁCTICA 1 *************
 * @file Lattice.cc
 * @author ALBA PÉREZ RODRÍGUEZ
 * @version 0.1
 * @date 2024-02-07
 * @brief Creación de la clase Retículo. 
 * Este objeto es responsable de crear y almacenar las células que representan el espacio celular. 
 * También es responsable de controlar la evolución y llevar la cuenta de las generaciones.
 * Aquí encontramos la implementación de los métodos de la clase Lattice como el constructor por defecto,
 * el constructor que carga la configuración inicial del autómata celular en función de la frontera, el método getCell, el método nextGeneration y la sobrecarga del operador de salida.
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
Lattice::Lattice(const int& size, const BorderType& borderType, char* argv[]) {
  // Se ajusta el tamaño del retículo para incluir bordes.
  size_ = size + 2;
  cells_.resize(size_);
  State state;
  // Se itera sobre todas las células en el retículo.
  for (int i = 0; i < size_; ++i) {
    // Verificar el tipo de frontera
    // Se establecen las células en los bordes en estado de vida (ALIVE).
    if (i == size_ / 2) {
      state = ALIVE;
    } else {
      state = DEAD;
    } 
    // Crear la nueva célula con el estado determinado y agregarla al vector de células.
    cells_[i] = new Cell(i, state);
  }
  // si es abierta
  if (borderType == OPEN) {
    if (atoi(argv[5]) == 0  || atoi(argv[5]) == 1) {
      cells_[0] = new Cell(0, (State)atoi(argv[5]));
      cells_[size_ - 1] = new Cell(size_ - 1, (State)atoi(argv[5]));
    } else {
      std::cout << "Error, valor " << argv[5] << " invalido" << std::endl;
    }
  // Si el tipo de frontera es periódica, ajusta los estados de las células en los bordes.
  } else if (borderType == PERIODIC) {
    cells_[0] = cells_[size_ - 2];
    cells_[size_ - 1] = cells_[1];
  // Si el tipo de frontera es reflejante, ajusta los estados de las células en los bordes.
  } else if (borderType == REFLECTIVE) {
    cells_[0] = cells_[1];
    cells_[size_ - 1] = cells_[size_ - 2];
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
Lattice::Lattice(const int size, const BorderType& borderType, const std::string& file_name, char* argv[]) {
  std::ifstream input_file{file_name};
  // verifica si el archivo se abrió correctamente
  if (!input_file.is_open()) {
    std::cerr << "File could not be opened." << std::endl;
    exit(EXIT_FAILURE);
  // Si el archivo se abrio
  } else {
    std::vector<int> start_states;
    int state;
    // Se lee el estado inicial del autómata celular desde un archivo.
    while (input_file >> state) {
      start_states.push_back(state);
    } 
    // Se verifica si el tamaño especificado en la opción "-size" coincide con el número de estados en el archivo.
    if (start_states.size() != static_cast<unsigned>(size)) {
      std::cerr << "Size specified in option \"-size\" does not match with the number of states in the file " << file_name << "." << std::endl; 
      exit(EXIT_FAILURE);
    }
    // Se ajusta el tamaño del retículo para incluir bordes.
    size_ = size + 2;
    cells_.resize(size_);
    borderType_ = borderType;
    State state_aux = DEAD;
    // Se itera sobre todas las células en el retículo.
    for (int i = 0, j = 0; i < size_; ++i) {
      if (i == 0 || i == size_ - 1) {
        state_aux = ALIVE;
      } else {
        state_aux = static_cast<State>(start_states[j++]);
      }
      cells_[i] = new Cell(i, state_aux);
    }
    // si es abierta
    if (borderType == OPEN) {
      if (atoi(argv[5]) == 0  || atoi(argv[5]) == 1) {
        cells_[0] = new Cell(0, (State)atoi(argv[5]));
        cells_[size_ - 1] = new Cell(size_ - 1, (State)atoi(argv[5]));
      } else {
        std::cout << "Error, valor " << argv[5] << " invalido" << std::endl;
      }
    }
    // Si el tipo de frontera es periódica, ajusta los estados de las células en los bordes.
    if (borderType_ == PERIODIC) {
      cells_[0]->setState(cells_[size_ - 2]->getState());
      cells_[size_ - 1]->setState(cells_[1]->getState());
      
    } else if (borderType_ == REFLECTIVE) {
      cells_[0]->setState(cells_[1]->getState());
      cells_[size_ - 1]->setState(cells_[size_ - 2]->getState());
    }
  }
}

/**
 * @brief Destructor de la clase para liberar la memoria de las células
 * Se encarga de liberar la memoria de las células.
 * Si no se hace esto, se producirá una fuga de memoria. Dara
 */
Lattice::~Lattice() {
  for (int i = 1; i < size_ - 1; ++i) {
    delete cells_[i];
  }
}

/**
 * @brief Método que devuelve la célula en la posición dada.
 * Se encarga de devolver la célula en la posición dada
 * @return const Cell& devuelve la célula en la posición dada
 */
const Cell& Lattice::getCell(const Position& position) const {
  return *(cells_[position]);
}

/**
 * @brief Función que evoluciona el autómata celular.
 * Se encarga de evolucionar el autómata celular
 * Hace dos recorridos sobre el retículo. En el primero, cada célula accede a su vecindad y calcula su estado siguiente.
 * En el segundo, cada célula actualiza su estado.
 * Si la frontera es de tipo bucle, se ajustan los estados de las células en los bordes.
 * Esto se hace para que el retículo sea unidimensional y se pueda aplicar la regla 110.
 */
void Lattice::NextGeneration() { 
  std::cout << "Número de células vivas: " << CountAliveCells() << std::endl;
  // Si la frontera es de tipo periodico, se ajustan los estados de las células en los bordes.
  if (borderType_ == PERIODIC) {
    cells_[0]->setState(cells_[size_ - 2]->getState());
    cells_[size_ - 1]->setState(cells_[1]->getState());
  }
  // Si la frontera es de tipo reflective, se ajustan los estados de las células en los bordes.
  if (borderType_ == REFLECTIVE) {
    cells_[0]->setState(cells_[1]->getState());
    cells_[size_ - 1]->setState(cells_[size_ - 2]->getState());
  }
  // Primer recorrido: Cada célula accede a su vecindad y calcula su estado siguiente.
  for (int i = 1; i < size_ - 1; ++i) {
    cells_[i]->Rule30(*this);
  }
  // Segundo recorido: Cada célula actualiza su estado.
  for (int i = 1; i < size_ - 1; ++i) {
    cells_[i]->UpdateState();
  }
}

/**
 * @brief Funcion que calcula las celulas vivas que quedan al final.
 * @return int retorna las celulas vivas
 */
int Lattice::CountAliveCells() const {
  int aliveCount = 0;
  for (const Cell* cell : cells_) {
    if (cell->getState() == ALIVE) {
      aliveCount++;
    }
  }
  return aliveCount;
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
  for (int i = 1; i < lattice.getSize() - 1; ++i) {
    std::cout << lattice.getCell(i);
  }
  os << std::endl;
  return os;
}

