//
//  Graph.hpp
//  Graph
//
//  Created by Vicente Cubells on 10/11/20.
//

#ifndef Graph_hpp
#define Graph_hpp

#include <iostream>
#include <vector>
#include <algorithm>
#include "Vertex.hpp"

template <class V, class E>
class Graph {

    std::vector < Vertex<V, E> * > nodes;

public:

    Graph() {}
    ~Graph();

    void addVertex(V & );
    void addVertex(Vertex<V,E> * );
    void addEdge(Vertex<V,E> *, Vertex<V,E> *, const E & );
    void removeEdge(Vertex<V,E> *, Vertex<V,E> *, const E & );

    Vertex<V, E> * search(const V & );
    Vertex<V, E> * search(const Vertex<V,E> *);

    size_t size() const;
    template <class Vn, class En>
    friend std::ostream & operator <<(std::ostream &, const Graph<Vn,En> &);

    void maxConexionesEntrantes();
    void maxConexionesSalientes();
   // void BFS(this->Graph, V & nodeBegin);
};

template<class V, class E>
size_t Graph<V, E>::size() const {
    return nodes.size();
}

template <class V, class E>
Graph<V,E>::~Graph()
{
    for (auto v: nodes) {
        delete v;
    }

    nodes.clear();
}

template <class V, class E>
void Graph<V,E>::addVertex(V & value )
{
    auto vertex = new Vertex<V, E>(value);

    nodes.push_back(vertex);
}

template <class V, class E>
void Graph<V,E>::addVertex(Vertex<V,E> * vertex )
{
    nodes.push_back(vertex);
}

template <class V, class E>
void Graph<V,E>::addEdge(Vertex<V,E> * source, Vertex<V,E> * target, const E & value)
{
    Vertex<V,E> *node = nullptr;

    /* Buscar nodo origen, cambio de función find in node */
    for (auto n : nodes){
        if ( *n == *source){
            node = n;
            break;
        }
    }

    if (node == nullptr) {
        std::cout << "Nodo no encontrado" << std::endl;
        return;
    }
    /* Se crea una copia de node con otra dic o toma la dic de source ?*/

    Edge<V, E> * edge = new Edge<V,E>(value, target);

    node->addEdge(edge);
    target->addEdgeEntrante(edge);

    /* Modificar conexiones entrantes y salientes*/
    node->addConexionesSalientes();
    target->addConexionesEntrantes();

}

/* Modificar remove...*/
template <class V, class E>
void Graph<V,E>::removeEdge(Vertex<V,E> * source, Vertex<V,E> * target, const E & value )
{
    /* Buscar vertex origen */
    auto node = find(nodes.begin(), nodes.end(), source);

    Vertex<V,E> * vertex = (*node);

    auto * edges = vertex->getEdges();

    Edge<V,E> * to_remove = nullptr;

    for (auto e : *edges) {
        if (e->getInfo() == value && e->getTarget() == target) {
            to_remove = e;
            break;
        }
    }
    
    /* Remover nodo y modificar conexiones entrantes, salientes */
    if (to_remove) {
        vertex->removeEdge(to_remove);
        vertex->removeConexionesSalientes();
        target->removeConexionesEntrantes();
    }

}

template <class V, class E>
Vertex<V, E> * Graph<V,E>::search(const V & value )
{
    /* Crear un nodo */
    Vertex<V,E> * vertex = new Vertex<V, E>(value);

    /* Buscar vertex */
    auto node = search(vertex);

    /* Elimiinar el nodo temporal */
    delete vertex;

    /* Regresar el nodo encontrado */
    return node;
}

template <class V, class E>
Vertex<V, E> * Graph<V,E>::search(const Vertex<V,E> * value )
{
  for (auto n : nodes){
    
    if (* n == * value){
      return n;
    }
    
  }
  return nullptr;
}

template <class V, class E>
std::ostream & operator <<(std::ostream & os, const Graph<V,E> & graph)
{
    os << "--- Visualizar grafo:  ---" << std::endl;

    for (auto v :  graph.nodes) {
        os << *v;
    }

    return os;
}

template <class V, class E>
void Graph<V,E>::maxConexionesSalientes(){
    Vertex<V,E> * max = nullptr;
    int maxConex = 0;
    for (auto v : nodes){
       int actual = v->getConexionesSalientes();
        if (actual > maxConex){
            maxConex = actual;
            max = v;
        }
    }

    if (max == nullptr){
        std::cout << "No hay vertices" << std::endl;
        return;
    }
    else {
    std::cout << "El vertice con más conexiones salientes es: " << max->getInfo() << " con: " << max->getConexionesSalientes() << std::endl;
    }
}

template <class V, class E>
void Graph<V,E>::maxConexionesEntrantes(){
    Vertex<V,E> * max = nullptr;
    int maxConex = 0;
    for (auto v : nodes){
       int actual = v->getConexionesEntrantes();
        if (actual > maxConex){
            maxConex = actual;
            max = v;
        }
    }

    if (max == nullptr){
        std::cout << "No hay vertices" << std::endl;
        return;
    }
    else {
    std::cout << "El vertice con más conexiones entrantes es: " << max->getInfo() << " con: " << max->getConexionesEntrantes() << std::endl;
    }
}

//Función recorrido en anchura (BFS) en el grafo a partir de un nodo dado

/*
template <class V, class E>
void Graph<V, E>::BFS(this->Graph, V & nodeBegin) {

  std::cout << "Algoritmo BFS aplicado al grafo : " << std::endl;
  std::vector<bool> visited(graph->size(), false);

  std::queue<int> queue;

  visited[u] = true;
  queue.push(u);

  while (!queue.empty()) {
    u = queue.front();
    std::cout << " ---> " << u << " ";
    queue.pop();

    Vertex<int, int> *vertex = graph->search(u);
    auto edges = vertex->getEdges();

    for (auto edge : *edges) {
      int target = edge->getTarget()->getInfo();
      if (!visited[target]) {
        visited[target] = true;
        queue.push(target);
      }
    }
  }
}// Complejidad: O(v + e)
*/

#endif /* Graph_hpp */
