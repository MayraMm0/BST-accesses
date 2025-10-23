#pragma once
#include <iostream>
#include <queue>
#include "Node.h"
using namespace std;

template <typename T>
class BinarySearchTree{
public:
    Node<T>* root;

    BinarySearchTree(): root(nullptr) {}

    void destroy(Node<T>* currentNode) {
        if (currentNode == nullptr) return;
        if (currentNode->left) destroy(currentNode->left);
        if (currentNode->right) destroy(currentNode->right);
        delete currentNode;
    }
    ~BinarySearchTree() { destroy(root); }

    Node<T>* getRoot() {
        return root;
    }

    // ------ MÉTODOS AUXILIARES PARA ACTUALIZAR ALTURA -----

    // Regresa altura del nodo
    int height_of(Node<T>* node) const {
        if (!node) return -1;
        return node->height;
    }

    // Actualiza el height basado en sus hijos
    void update_height(Node<T>* node) {
        // Height: 1 + la height max de hijos
        node->height = 1 + max(height_of(node->left), height_of(node->right));
    }

    // Va de current a la raíz, actualizando
    void update_ancestor_heights(Node<T>* current) {
        // Empieza con el parent del que se acaba de insertar
        while (current != nullptr) {
            // 1. Recalcula height de current
            update_height(current);

            // 2. Se mueve a parent
            current = current->parentNode;
        }
    }

    // ------ FUNCIÓN PARA INSERTAR O(log n) ------
    void insert(T value){
        Node<T>* newNode = new Node(value);

        if (root == nullptr){ // Si el árbol está vacío
            root = newNode;   // Solo se añade la raíz
            return;
        }

        Node<T>* temp = root;
        Node<T>* parent = nullptr; // ancestro de current

        while(true){
            parent = temp;

            if(newNode->value < temp->value){
                if(temp->left == nullptr){ // Si no hay nodo puede insertar
                    temp->left = newNode;
                    newNode->parentNode = parent;

                    update_ancestor_heights(parent); // Actualiza alturas
                    return;
                }
                temp = temp->left; // Si había nodo, pasa al siguiente y vuelve a comparar
            } else {
                if(temp->right == nullptr){ // Si no hay nodo puede insertar
                    temp->right = newNode;
                    newNode->parentNode = parent;

                    update_ancestor_heights(parent); // Actualiza alturas
                    return;
                }
                temp = temp->right; // Si había nodo, pasa al siguiente y vuelve a comparar
            }
        }
    }

    // ------ FUNCIÓN PARA BUSCAR O(log n) ------
    Node<T>* contains(T value){
        if (root == nullptr) return nullptr; // Si está vacío
        Node<T>* temp = root;

        while(temp){
            if (value < temp->value){
                temp = temp->left;
            }
            else if (value > temp-> value){
                temp = temp->right;
            } else {
                return temp; // Encontró el nodo
            }
        }
        return nullptr; // llega al final sin encontrar value
    }

    // ------ whatlevelamI O(1) ------
    int get_level(Node<T>* currentNode){
        if (currentNode == nullptr) return -1;
        else {
            return currentNode->get_height();
        }
    }

    // ------ ancestors O(1) ------
    void ancestor(Node<T>* currentNode){
        if (currentNode == nullptr) return;
        cout << "ancestro: " << currentNode->get_parent()->value << "\n";
    }

    // ------ HEIGHT O(1) ------
    int get_height(){
        return root->height;
    }


    // ------ VISIT FUNCTIONS O(n) ------

    // Preorder
    void PreOrder(Node<T>* node){
        while (node != nullptr) { // Hasta que se procesa el árbol completo

            if (node->left == nullptr) {// CASO 1. No hay hijos izquierdos
                // Como es PreOrder, sale el nodo ANTES que sus hijos derechos
                cout << node->value << " ";
                // Pasamos al hijo derecho
                node = node->right;

            } else { // 2. CASO: El nodo actual Sí tiene hijo izquierdo
                // 2a. Encontramos el "predecesor in-order" del nodo actual
                // predecesor in-order: el nodo más a la derecha en el subárbol izquierdo
                // (valor más grande sigue siendo más pequeño)
                Node<T>* curr = node->left;

                // Recorremos a la derecha en el subárbol izquierdo.
                while (curr->right != nullptr && curr->right != node) {
                    curr = curr->right; // detectar el enlace temporal (ver si ya recorrimos el camino)
                }

                if (curr->right == node) {  // El enlace temporal ya EXISTE (Ya visitamos el subárbol izquierdo)
                    // Restauramos el árbol original
                    curr->right = nullptr;
                    // pasamos al hijo derecho.
                    node = node->right;

                } else { // No hay enlace temporal (Visitaremos el subárbol izquierdo por primera vez)
                    //Visitamos el nodo actual (PreOrder)
                    cout << node->value << " ";
                    // Se crea enlace temporal: el predecesor (curr) apunta al nodo actual.
                    curr->right = node;
                    // Nos movemos al hijo izquierdo
                    node = node->left;
                }
            }
        }
        cout << "\n";
    }

    // Inorder
    void InOrder(){
        stack<Node<T>*> stk;
        Node<T>* curr = root;

        while (curr != nullptr || stk.empty() == false) {

            // Vamos al leftmost
            while (curr != nullptr) {

                // Vamos añadiendo los izquierdos
                stk.push(curr);
                curr = curr->left;
            }

            // Current ya es null
            curr = stk.top();
            stk.pop();
            cout << curr->value << " ";

            // Ya visitamos el nodo y su left
            // Pasamos a la derecha
            curr = curr->right;
        }
    }


    // Postorder
    void PostOrder(Node<T>* currentNode){
        if(currentNode->left){
            PostOrder(currentNode->left);
        }
        if (currentNode->right){
            PostOrder(currentNode->right);
        }
        cout << currentNode->value << " ";
    }

    // Level by level
    void levelByLevel(){
        if (!root) return;

        queue<Node<T>*> myQueue;
        myQueue.push(root);

        while(myQueue.size()>0){
            Node<T>* currentNode = myQueue.front();
            myQueue.pop();
            cout<< currentNode->value <<" ";

            if(currentNode->left){
                myQueue.push(currentNode->left);
            }
            if(currentNode->right){
                myQueue.push(currentNode->right);
            }
        }
        cout << "\n";
    }

};