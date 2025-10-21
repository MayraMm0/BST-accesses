#pragma once

#include <iostream>
#include "Node.h"

template<typename T>
class SplayTree {
private:
    size_t treeSize;

    // --- ROTACIONES ---
    // Rotación a la derecha
    // Traslada el nodo hijo izquierdo (y) a la posición del nodo actual (x).
    void zig(Node<T>* x){
        Node<T>* y = x->left;
        if (y != nullptr) {
            // El hijo derecho de y se convierte en el nuevo hijo izquierdo de x.
            x->left = y->right;
            if (y->right != nullptr) {
                y->right->parent = x;
            }

            // Reemplaza x por y en el puntero del padre de x
            y->parent = x->parent;
            if (x->parent == nullptr) {
                root = y; // y se convierte en la nueva raíz
            } else if (x == x->parent->left) {
                x->parent->left = y;
            } else {
                x->parent->right = y;
            }

            // Coloca x como hijo derecho de y
            y->right = x;
            x->parent = y;
        }
    }

    // Rotación a la izquierda
    // Traslada el nodo hijo derecho (y) a la posición del nodo actual (x).
    void zag(Node<T>* x){
        Node<T>* y = x->right;
        if (y != nullptr) {
            // El hijo izquierdo de y se convierte en el nuevo hijo derecho de x.
            x->right = y->left;
            if (y->left != nullptr) {
                y->left->parent = x;
            }

            // Reemplaza x por y en el puntero del padre de x.
            y->parent = x->parent;
            if (x->parent == nullptr) {
                root = y; // y se convierte en la nueva raíz
            } else if (x == x->parent->left) {
                x->parent->left = y;
            } else {
                x->parent->right = y;
            }

            // Coloca x como hijo izquierdo de y
            y->left = x;
            x->parent = y;
        }
    }


    // --- SPLAYING (llevar el nodo x a la raíz) --
    void splay(Node<T>* x){
        // Continúa rotando mientras x no sea la raíz
        while (x->parent != nullptr) {

            // Caso general (x tiene abuelo)
            if (x->parent->parent == nullptr) {

                // Caso 1: Zig or Zag (x es hijo de root)
                if (x == x->parent->left) {
                    // x es hijo izquierdo -> rotación a la derecha (Zig) en el padre.
                    zig(x->parent);
                } else {
                    // x es hijo derecho -> rotación a la izquierda (Zag) en el padre.
                    zag(x->parent);
                }
            }

            // Caso 2: Zig-Zig (x, padre y abuelo están alineados a la izquierda)
            else if (x == x->parent->left && x->parent == x->parent->parent->left) {
                zig(x->parent->parent);
                zig(x->parent);
            }

            // Caso 3: Zag-Zag (x, padre y abuelo están alineados a la derecha)
            else if (x == x->parent->right && x->parent == x->parent->parent->right) {
                zag(x->parent->parent);
                zag(x->parent);
            }

            // Caso 4: Zig-Zag (x es hijo derecho, padre es hijo izquierdo
            else if (x == x->parent->right && x->parent == x->parent->parent->left) {
                zag(x->parent);
                zig(x->parent);
            }

            // Caso 5: Zag-Zig (x es hijo izquierdo, padre es hijo derecho
            else {
                zig(x->parent);
                zag(x->parent);
            }
        }
    }

    // BUSCAR O(log n)
    Node<T>* findNode(const T& IP){
        Node<T>* current = root;

        while (current != nullptr) {
            if (IP < current->IP) {
                current = current->left;
            } else if (IP > current->IP) {
                current = current->right;
            } else {
                return current; // Cuando lo encuentra (valores iguales)
            }
        }

        return nullptr; // Si no lo encuentra
    }


    // --- UTILIDADES ---
    void clear(Node<T>* root){
        if (root != nullptr) {
            clear(root->left);
            clear(root->right);
            delete root;
        }
    }

public:
    Node<T>* root;
    SplayTree(): root(nullptr), treeSize(0) {}; // Constructor
    ~SplayTree(){ // Destructor
        clear(root);
    }

    // Getters de size y empty
    size_t size() const { return treeSize; }

    bool empty() const { return root == nullptr; }

    // --- OPERACIONES PRINCIPALES ---
    // INSERTAR O(log n)
    void insert(const T& IP){
        Node<T>* newNode = new Node<T>(IP);

        if (root == nullptr) {
            root = newNode;
            ++treeSize;
            return;
        }

        Node<T>* current = root;
        Node<T>* parent = nullptr;

        // Encuentra punto de inserción para que el árbol mantenga la propiedad BST y sea complete
        while (current != nullptr) {
            parent = current;
            if (IP < current->IP) {
                current = current->left;
            } else if (IP > current->IP) {
                current = current->right;
            } else {
                // Si ya existe, no inserta duplicados pero hace splay
                delete newNode;
                splay(current);
                return;
            }
        }

        // Inserta nuevo nodo
        newNode->parent = parent;
        if (IP < parent->IP) {
            parent->left = newNode;
        } else {
            parent->right = newNode;
        }

        ++treeSize;
        splay(newNode); // Splay el nuevo nodo a la raíz
    }

    // BUSCAR O(log n)
    bool find(const T& IP) {
        Node<T>* node = root;
        while (node != nullptr) {
            if (IP < node->IP) {
                node = node->left;
            } else if (IP > node->IP) {
                node = node->right;
            } else {
                splay(node);
                return true;
            }
        }
        return false;
    }


    // ELIMINAR O(log n)
    bool remove(const T& IP){
        Node<T>* node = findNode(IP);

        if (node == nullptr) {
            return false; // No se encontró
        }

        splay(node);

        if (node->left == nullptr) {
            // No hay subárbol izquierdo, reemplazar con derecho
            root = node->right;
            if (root != nullptr) {
                root->parent = nullptr;
            }
        } else if (node->right == nullptr) {
            // No hay arbol derecho, reemplazar con izquierdo
            root = node->left;
            if (root != nullptr) {
                root->parent = nullptr;
            }
        } else {
            // Ambos subárboles existen
            Node<T>* rightSubtree = node->right;
            root = node->left;
            root->parent = nullptr;

            // Encuentra el máximo del subárbol izquierdo y splay
            Node<T>* maxLeft = root;
            while (maxLeft->right != nullptr) {
                maxLeft = maxLeft->right;
            }
            splay(maxLeft);

            // Conecta el subárbol derecho
            maxLeft->right = rightSubtree;
            rightSubtree->parent = maxLeft;
        }

        delete node;
        --treeSize;
        return true;
    }

    // InOrder Traversal
    void inOrderTraversal(Node<T>* node) const {
        if (node != nullptr) {
            inOrderTraversal(node->left);
            std::cout << node->IP << " ";
            inOrderTraversal(node->right);
        }
    }

    // --- FUNCIÓN PRINT ---
    void print() const {
        if (root == nullptr) {
            std::cout << "El árbol está vacío." << std::endl;
            return;
        }
        std::cout << "Árbol en orden ascendente: ";
        inOrderTraversal(root); // Inicia el recorrido desde la raíz
        std::cout << std::endl;
    }


    // SOBRECARGA DE OPERADOR
    friend std::ostream& operator<<(std::ostream& os, const SplayTree<T>& tree) {
        if (tree.root == nullptr) {
            return os << "[]"; // Representación de un árbol vacío
        }

        os << "[";
        std::queue<Node<T>*> q;
        q.push(tree.root);
        bool first = true;

        while (!q.empty()) {
            Node<T>* current = q.front();
            q.pop();

            // Formateo de la salida en línea recta
            if (!first) {
                os << ", ";
            }
            os << current->IP;
            first = false;

            // Añade hijos no nulos a la cola
            if (current->left != nullptr) {
                q.push(current->left);
            }
            if (current->right != nullptr) {
                q.push(current->right);
            }
        }

        os << "]";
        return os;
    }
};