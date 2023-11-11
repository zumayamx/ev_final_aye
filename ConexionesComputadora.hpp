#ifndef ConexionesComputadora_hpp
#define ConexionesComputadora_hpp
#include "Stack.hpp"
#include "LinkedList.hpp"
#include "RegComun.hpp"
#include <vector>
#include <iostream>
#include <string>
#include <map>



template<class T>
class ConexionesComputadora{
private:
  std::string IP;
  std::string name;
  Stack<T> * conexionesEntrantes = new Stack<T>(); 
  LinkedList<T> * conexionesSalientes = new LinkedList<T>();
  

public:
  ConexionesComputadora() = default;
  ConexionesComputadora (std::string _ip, std::string _name) : IP(_ip), name(_name) {}

  void llenarConexiones (std::vector<T>);
  int totalConexionesEntrantes();
  int totalConexionesSalientes();
  Stack<T> * getConexionesEntrantes();
  LinkedList<T> * getConexionesSalientes();
  T ultimaConexionEntrante();
  Node<T> * tresConexionesConsecutivas();
//  Map<T, K> conexionesPorDia(std::string date);
  
};

template <class T>
void ConexionesComputadora<T>::llenarConexiones(std::vector<T> registro)
{
  for (auto objeto : registro){
    if (objeto.getipOrigin() == IP)
    {
      conexionesSalientes->insert_back(objeto);
    }
    else if (objeto.getIpDestiny() == IP)
    {
      conexionesEntrantes->push(objeto);
    }
  }
}

template<class T>
Stack<T> * ConexionesComputadora<T>::getConexionesEntrantes(){
  return conexionesEntrantes;
}

template<class T>
int ConexionesComputadora<T>::totalConexionesEntrantes(){
  return conexionesEntrantes->size();
}

template<class T>
int ConexionesComputadora<T>::totalConexionesSalientes(){
  return conexionesSalientes->size();
}

template<class T>
LinkedList<T> * ConexionesComputadora<T>::getConexionesSalientes(){
  return conexionesSalientes;
}

template<class T>
T ConexionesComputadora<T>::ultimaConexionEntrante()
{
  return conexionesEntrantes->top()->getInfo();
}

template <class T>
Node<T> * ConexionesComputadora<T>::tresConexionesConsecutivas()
{
    Node<T> *tmp = conexionesSalientes->first();

    while (tmp != nullptr && tmp->getNext() != nullptr && tmp->getNext()->getNext() != nullptr) 
    {
        std::string webIPprimera = tmp->getInfo().getIpDestiny();
        std::string webIPsegunda = tmp->getNext()->getInfo().getIpDestiny();
        std::string webIPtercera = tmp->getNext()->getNext()->getInfo().getIpDestiny();

        if (webIPprimera == webIPsegunda && webIPsegunda == webIPtercera) 
        {
            return tmp;
        }
      tmp = tmp->getNext();
    }
  return nullptr;
}

//template class<T, K>








#endif /*ConexionesComputadora*/
