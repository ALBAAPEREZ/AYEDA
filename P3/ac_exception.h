/**
 * @file ac_exception.h
 * @author ALBA PEREZ
 * @version 0.1
 * @date 2024-03-03
 * @brief Clase ac_exception que hereda de la clase std::exception y se encarga de definir
 * e implementar las responsabilidades de una excepción. Esta clase se encarga de lanzar una 
 * excepción con un mensaje de error.
 */

#ifndef AC_EXCEPTION
#define AC_EXCEPTION

#include <exception>
#include <stdexcept>
#include <iostream>

/**
 * @brief Clase ac_exception que hereda de la clase std::exception y se encarga de definir
 * e implementar las responsabilidades de una excepción.
 * Esta clase se encarga de lanzar una excepción con un mensaje de error.
 */
class ac_exception : public std::exception {
 public:
  // Constructor que recibe un mensaje de error
  explicit ac_exception(const char* message) : msg(message) {}
  // Método que devuelve el mensaje de error
  virtual const char* what() const throw() {
    return msg;
  }
 private:
  // Mensaje de error
  const char* msg;
};

#endif // AC_EXCEPTION