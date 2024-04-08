/**
 * @file HashTable.h
 * @author ALBA PÉREZ
 * @version 0.1
 * @date 2024-03-10
 * @copyright Copyright (c) 2024
 * @brief Clase HashTable que hereda de Sequence y que contiene la tabla de dispersión.
 * Además, contiene el tamaño de la tabla, la función de dispersión y la función de exploración.
 * También contiene el tamaño del bloque. Contiene un constructor y un destructor.
 * Enontramos dos clases HashTable, una con template static sequence y otra con template dynamic sequence.
 * Para cada caso de uso, se implementan los métodos Search y Insert.
 */

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <array>

#include "Sequence.h"
#include "DispersionFunction.h"
#include "ExplorationFunctions.h"
#include "nif.h"

//////////////////////////// hash table con template static sequence ///////////////////////
/**
 * @brief Clase HashTable que hereda de Sequence y que contiene la tabla de dispersión.
 * se encarga de la gestión de la tabla hash, la cual es un vector de secuencias.
 * Contiene el tamaño de la tabla, la función de dispersión y la función de exploración.
 * También contiene el tamaño del bloque. Se usa la template Container para poder elegir entre
 * una secuencia estática o dinámica. 
 * @tparam Key clave que se va a dispersar
 * @tparam Container puede ser StaticSequence o DynamicSequence, por defecto es StaticSequence
 */
template <class Key, class Container = StaticSequence<Key>>
class HashTable : public Sequence<Key> {
 public:
  HashTable(unsigned table_size, DispersionFunction<Key>& dispersion, ExplorationFunction<Key>& exploration,unsigned blocksize);
  ~HashTable() {}
  bool Search(const Key& key) const override;
  bool Insert(const Key& key) override;
  bool IsFull() const override { return false; }
  // Método que se encarga de escribir la tabla hash
  std::ostream& write(std::ostream& os) const;
  // metodo menu que permite elegir entre las diferentes opciones
  void menu();

 private:
  unsigned tablesize_;
  unsigned blockSize_;
  std::vector<Container> table_;
  DispersionFunction<Key>* dispersionfunction_;
  ExplorationFunction<Key>* explorationfunction_;
};


// ========================= MÉTODOS =========================
/**
 * @brief Construct a new Hash Table< Key,  Container>:: Hash Table object
 * Constructor de la clase HashTable con template parcial static sequence
 * Se le pasa el tamaño de la tabla, la función de dispersión, la función de exploración y el tamaño del bloque.
 * @tparam Key clave que se va a dispersar
 * @tparam Container clase que se va a usar para la secuencia
 * @param table_size tamaño de la tabla
 * @param dispersion  función de dispersión
 * @param exploration función de exploración
 * @param blocksize tamaño del bloque
 */
template <class Key, class Container>
HashTable<Key, Container>::HashTable(unsigned table_size, DispersionFunction<Key>& dispersion, ExplorationFunction<Key>& exploration, unsigned blocksize) : tablesize_(table_size), dispersionfunction_(&dispersion), explorationfunction_(&exploration), blockSize_(blocksize) {
  table_.resize(table_size, 0);
  StaticSequence<Nif> Sequence(blockSize_);
  for (int i = 0; i < table_size; i++) {
    table_[i] = Sequence;
  }
}

/**
 * @brief Método de la clase HashTable que se encarga de buscar un elemento en la tabla hash
 * Lo que hace es comprorbar si la secuencia está llena, si lo está, 
 * se busca en la secuencia correspondiente. 
 * @tparam Key clave que se va a dispersar
 * @param key clave que se va a buscar
 * @return true true si el elemento ya está en la tabla hash
 * @return false false si el elemento no está en la tabla hash
 */
template <class Key, class Container>
bool HashTable<Key, Container>::Search(const Key& key) const {
  unsigned index = dispersionfunction_->operator()(key);
  return table_[index].Search(key);
}

/**
 * 
 * @brief Método que se encarga de insertar un elemento en la tabla hash
 * Si no existe el elemento en la tabla hash, se añade en la secuencia correspondiente a la posición de la tabla hash
 * Si se ha podido añadir el elemento en la tabla hash, se devuelve un "true"
 * Si no se ha podido añadir el elemento en la tabla hash, se devuelve un "false"
 * @tparam Key clave que se va a dispersar
 * @param key clave que se va a insertar
 * @return true retorna true si el elemento se ha podido insertar en la tabla hash
 * @return false retorna false si el elemento no se ha podido insertar en la tabla hash
 */
template <class Key, class Container>
bool HashTable<Key, Container>::Insert(const Key& key) {
  // Si el elemento ya está en la tabla hash, se devuelve un "false"
  if (Search(key) == true) {
    return false;
  }
  unsigned index = dispersionfunction_->operator()(key);
  // Si la secuencia está llena, se busca en la secuencia correspondiente
  if (table_[index].IsFull()) {
    int i = 0;
    bool inserted = false;
    // mientras la secuencia esté llena
    while (!inserted && i < tablesize_) {
      index = explorationfunction_->operator()(key, i);
      // si la secuencia no está llena, se inserta la clave en la secuencia correspondiente
      if (!table_[index].IsFull()) {
        table_[index].Insert(key);
        inserted = true;
      }
      i++;
    }
    if (!inserted) {
      std::cout << "Error: No se pudo insertar la clave. La tabla está llena." << std::endl;
      return false;
    }
  } else {
    table_[index].Insert(key);
  }
  return true;
}

/**
 * @brief Método que se encarga de escribir la tabla hash
 * Se recorre la tabla hash y se escribe la secuencia correspondiente a cada posición de la tabla hash
 * Para ello, se recorre la secuencia y se escribe cada elemento de la secuencia 
 * @tparam Key clave que se va a dispersar
 * @tparam Container tipo de secuencia que se va a usar
 * @param os flujo de salida
 * @return std::ostream& retorna el flujo de salida
 */
template <class Key, class Container>
std::ostream& HashTable<Key, Container>::write(std::ostream& os) const {
  for (int i = 0; i < tablesize_; i++) {
    os << "Índice " << i << ": ";
    if (table_[i].Size() > 0) {
      for (int j = 0; j < table_[i].Size(); j++) {
        os << "-> NIF: " << table_[i].getData(j) << " ";
      }
    }
    os << std::endl;
  }
  return os;
}

/**
 * @brief Metodo menu que permite elegir entre las diferentes opciones
 * Se encarga de mostrar un menú con las diferentes opciones que se pueden elegir
 * @tparam Key clave que se va a dispersar
 * @tparam Container clase que se va a usar para la secuencia
 */
template <class Key, class Container>
void HashTable<Key, Container>::menu() {
  int opcion;
  do {
    std::cout << "\n==================== MENÚ ====================\n";
    std::cout << "|                                             |\n";
    std::cout << "|   1. Insertar elemento                      |\n";
    std::cout << "|   2. Buscar elemento                        |\n";
    std::cout << "|   3. Mostrar tabla                          |\n";
    std::cout << "|   4. Salir                                  |\n";
    std::cout << "|                                             |\n";
    std::cout << "==============================================\n";
    std::cout << "Elija una opción: ";
    std::cin >> opcion;
    Key k;
    switch (opcion) {
      case 1:
        std::cout << "Introduzca el elemento que quiere insertar: ";
        std::cin >> k;
        if (Insert(k) == true) {
          std::cout << "El elemento se ha insertado correctamente en la tabla" << std::endl;
          std::cout << std::endl;
        } else {
          std::cout << "El elemento no se ha podido insertar en la tabla" << std::endl;
          std::cout << std::endl;
        }
        break;
      case 2:
        std::cout << "Introduzca el elemento que quiere buscar: ";
        std::cin >> k;
        if (Search(k) == true) {
          std::cout << "El elemento está en la tabla" << std::endl;
          std::cout << std::endl;
        } else {
          std::cout << "El elemento no está en la tabla" << std::endl;
          std::cout << std::endl;
        }
        break;
      case 3:
        write(std::cout);
        break;
      case 4:
        std::cout << std::endl;
        std::cout << "Saliendo del programa..." << std::endl;
        exit(1);
        break;
      default:
        std::cout << "Opción no válida" << std::endl;
        break;
    }
  } while (opcion != 4);
}


//////////////////////////// hash table con template dynamic sequence ///////////////////////
/**
 * @brief Clase HashTable que contiene la tabla hash y las funciones de dispersión y exploración.
 * Esta es la clase que se usará para la dispersión de tipo abierto.. De tipo dinámico.
 * Especializacion parcial de la clase HashTable. 
 * @tparam Key Clave que se va a dispersar
 */
template<class Key> 
class HashTable<Key, DynamicSequence<Key>> {
 public:
  // Constructor de la clase HashTable
  HashTable(unsigned table_size, DispersionFunction<Key>& dispersion, ExplorationFunction<Key>& exploration);
  // Destructor de la clase HashTable
  ~HashTable() {}
  // Método que se encarga de buscar un elemento en la tabla hash
  bool Search(const Key& k) const;
  // Método que se encarga de insertar un elemento en la tabla hash
  bool Insert(const Key& k);
  std::ostream& write(std::ostream& os) const;
  // metodo menu que permite elegir entre las diferentes opciones
  void menu();
  
 private:
  unsigned tablesize_; // Tamaño de la tabla
  DispersionFunction<Key>& dispersion_; // Función de dispersión
  ExplorationFunction<Key>& exploration_; // Función de exploración
  std::vector<DynamicSequence<Key>> table_; // Tabla hash
};


// ========================= IMPLEMENTATION =========================
/**
 * @brief Construct a new Hash Table< Key,  Dynamic Sequence< Key>>:: Hash Table object
 * Constructor de la clase HashTable con template parcial dynamic sequence
 * Se le pasa el tamaño de la tabla, la función de dispersión y la función de exploración.
 * @tparam Key clave que se va a dispersar
 * @param tablesize tamaño de la tabla
 * @param dispersion  función de dispersión
 * @param exploration función de exploración
 */
template<class Key>
HashTable<Key, DynamicSequence<Key>>::HashTable(unsigned table_size, DispersionFunction<Key>& dispersion, ExplorationFunction<Key>& exploration) : tablesize_(table_size), dispersion_(dispersion), exploration_(exploration) {
  table_.resize(table_size);
  for (int i = 0; i < table_size; i++) {
    DynamicSequence<Key> Sequence;
    table_[i] = Sequence;
  }
}

/**
 * @brief Método de la clase HashTable que se encarga de buscar un elemento en la tabla hash
 * Lo que hace es comprorbar si la secuencia está llena, si lo está, 
 * se busca en la secuencia correspondiente. 
 * @tparam Key clave que se va a dispersar
 * @param key clave que se va a buscar
 * @return true true si el elemento ya está en la tabla hash
 * @return false false si el elemento no está en la tabla hash
 */
template<class Key>
bool HashTable<Key, DynamicSequence<Key>>::Search(const Key& key) const {
  unsigned index = dispersion_(key);
  for (int i = 0; i < table_[index].Size(); i++) {
    if (table_[index].isInList(key)) {
      return true;
    }
  }
  return false;
}

/**
 * @brief Método que se encarga de insertar un elemento en la tabla hash
 * Si no existe el elemento en la tabla hash, se añade en la secuencia correspondiente a la posición de la tabla hash
 * Si se ha podido añadir el elemento en la tabla hash, se devuelve un "true"
 * Si no se ha podido añadir el elemento en la tabla hash, se devuelve un "false"
 * @tparam Key clave que se va a dispersar
 * @param key clave que se va a insertar
 * @return true retorna true si el elemento se ha podido insertar en la tabla hash
 * @return false retorna false si el elemento no se ha podido insertar en la tabla hash
 */
template<class Key>
bool HashTable<Key, DynamicSequence<Key>>::Insert(const Key& key) {
  if (Search(key) == true) {
    return false;
  }
  unsigned index = dispersion_(key);
  table_[index].Insert(key);
  return true;
}

/**
 * @brief Método que se encarga de escribir la tabla hash
 * Se recorre la tabla hash y se escribe la secuencia correspondiente a cada posición de la tabla hash
 * Para ello, se recorre la secuencia y se escribe cada elemento de la secuencia 
 * @tparam Key clave que se va a dispersar
 * @param os flujo de salida
 * @return std::ostream& retorna el flujo de salida
 */
template<class Key>
std::ostream& HashTable<Key, DynamicSequence<Key>>::write(std::ostream& os) const {
  for (int i = 0; i < table_.size(); i++) {
    os << "Índice " << i << ": ";
    if (!table_[i].getList().empty()) {
      for (const auto& element : table_[i].getList()) {
        os << "-> NIF: " << element << " ";
      }
    }
    os << std::endl;
  }
  return os;
}

/**
 * @brief Metodo menu que permite elegir entre las diferentes opciones
 * Se encarga de mostrar un menú con las diferentes opciones que se pueden elegir
 * @tparam Key clave que se va a dispersar
 * @tparam DynamicSequence clase que se va a usar para la secuencia
 */
template<class Key>
void HashTable<Key, DynamicSequence<Key>>::menu() {
  int opcion;
  do {
    std::cout << "\n==================== MENÚ ====================\n";
    std::cout << "|                                             |\n";
    std::cout << "|   1. Insertar elemento                      |\n";
    std::cout << "|   2. Buscar elemento                        |\n";
    std::cout << "|   3. Mostrar tabla                          |\n";
    std::cout << "|   4. Salir                                  |\n";
    std::cout << "|                                             |\n";
    std::cout << "==============================================\n";
    std::cout << "Elija una opción: ";
    std::cin >> opcion;
    Key k;
    switch (opcion) {
      case 1:
        std::cout << "Introduzca el elemento que quiere insertar: ";
        std::cin >> k;
        if (Insert(k) == true) {
          std::cout << "El elemento se ha insertado correctamente en la tabla" << std::endl;
          std::cout << std::endl;
        } else {
          std::cout << "El elemento no se ha podido insertar en la tabla" << std::endl;
          std::cout << std::endl;
        }
        break;
      case 2:
        std::cout << "Introduzca el elemento que quiere buscar: ";
        std::cin >> k;
        if (Search(k) == true) {
          std::cout << "El elemento está en la tabla" << std::endl;
          std::cout << std::endl;
        } else {
          std::cout << "El elemento no está en la tabla" << std::endl;
          std::cout << std::endl;
        }
        break;
      case 3:
        write(std::cout);
        break;
      case 4:
        std::cout << std::endl;
        std::cout << "Saliendo del programa..." << std::endl;
        break;
      default:
        std::cout << "Opción no válida" << std::endl;
        break;
        exit(1);
    }
  } while (opcion != 4);
}


#endif // HASHTABLE_H
