#ifndef BSTNode_hpp
#define BSTNode_hpp

#include <iostream>
#include <map>
#include <vector>
#include <queue>

template<class K, class V>
class BSTNode{
public:
    std::pair<K, V> data;
    BSTNode<K, V>* left;
    BSTNode<K, V>* right;
    BSTNode<K, V>* root;
    BSTNode() : root(nullptr) {}
    BSTNode(std::pair<K, V> data) : data(data), left(nullptr), right(nullptr) {}

    void insertValue(std::pair<K, V> data);
    BSTNode<K, V> * insertNode(BSTNode<K, V>* node, std::pair<K, V> data);
    void printTopN(int n);
    void printTopNUntil(BSTNode<K, V>* node, int n, int& count);
    std::map<K, V> getTopSitios(int n);
    void getTop(BSTNode<K, V>* node, int n, int& count, std::map<K, V>& topSitios);

};

template<class K, class V>
void BSTNode<K, V>::insertValue(std::pair<K, V> data) {
    root = insertNode(root, data);
}

//Función para insertar nodo
//Complejidad: Peor caso O(n)
//             Mejor caso O(1)
template<class K, class V>
BSTNode<K, V> * BSTNode<K, V>::insertNode(BSTNode<K, V>* node, std::pair<K, V> data) {
    // Si el árbol/subárbol está vacío, crea un nuevo nodo
    if (node == nullptr) {
        return new BSTNode<K, V>(data);
    }

    // Si el valor a insertar es mayor que el valor del nodo actual a la derecha
    if (data.second > node->data.second) {
        node->right = insertNode(node->right, data);
    }
    // Si el valor es menor, inserta a la izquierda.
    else if (data.second < node->data.second) {
        node->left = insertNode(node->left, data);
    }
    // Si el valor es igual
    else {
        node->left = insertNode(node->left, data);
    }

    return node;
}


//Función para imprimir los primeros n elementos del BST.
//Complejidad: Peor caso O(n)
//             Mejor caso O(1)
template< class K, class V>
void BSTNode<K, V>::printTopN(int n) {
        int count = 0;
        printTopNUntil(this->root, n, count);
    }

template<class K, class V>
void BSTNode<K, V>::printTopNUntil(BSTNode<K, V>* node, int n, int& count) {
        if (node == nullptr || count >= n) {
            return;
        }

        // Ir primero a la derecha porque queremos los valores más altos
        printTopNUntil(node->right, n, count);
        if (count < n) {
            std::cout << node->data.first << ": " << node->data.second << std::endl;
            count++;
        }
        // Luego ir a la izquierda
        printTopNUntil(node->left, n, count);
    }

//Función que devuelve un mapa con los n elementos conmás registros
//Complejidad: Peor caso O(n)
//             Mejor caso O(1)
template <class K, class V>
std::map<K, V> BSTNode<K, V>::getTopSitios(int n) {
    std::map<K, V> topSitios;
    int count = 0;
    getTop(this->root, n, count, topSitios);
    return topSitios;
}

template<class K, class V>
void BSTNode<K, V>::getTop(BSTNode<K, V>* node, int n, int& count, std::map<K, V>& topSitios) {
    if (node == nullptr || count >= n) {
        return;
    }
    getTop(node->right, n, count, topSitios);

    if (count < n) {
        topSitios[node->data.first] = node->data.second;
        count++;
    }

    getTop(node->left, n, count, topSitios);
}

#endif /* BSTNode_hpp */