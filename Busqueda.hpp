#ifndef Busqueda_hpp
#define Busqueda_hpp
#include <iostream>
#include <vector>
#include "RegComun.hpp"

template <class T>
class Busqueda{
public:
    static std::vector<int> busquedaSecuencial(std::vector <T>, std::string);
   
};

template <class T>
std::vector<int> Busqueda<T>::busquedaSecuencial(std::vector<T> vector, std::string valor){
std::vector<int> indicesComprador;
 for (int i = 0; i < vector.size(); ++i) {
        if (vector[i].getNameOrigin() == valor) {
            indicesComprador.push_back(i);
        }
        if (vector[i].getNameDestiny() == valor) {
            indicesComprador.push_back(i);
        }
         if (vector[i].getDestinyPort() == valor) {
            indicesComprador.push_back(i);
        }
    }
  return indicesComprador;
}

#endif /*Busqueda*/