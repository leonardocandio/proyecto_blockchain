//
// Created by david on 23/02/2023.
//

#ifndef PROYECTO_BLOCKCHAIN_BTREE_H
#define PROYECTO_BLOCKCHAIN_BTREE_H

#include <iostream>
#include <math.h>
#include <queue>
#include <stack>


using namespace std;

////// NODO BTREE ///////


template<typename TK>
struct Node {
    // array de keys
    TK *keys;
    // array de punteros a hijos
    Node **children;
    // cantidad de keys
    int count;
    // indicador de nodo hoja
    bool leaf;

    Node() : keys(nullptr), children(nullptr), count(0), leaf(true) {}
    Node(int M, bool _leaf = true) {
        this->keys = new TK[M - 1];
        this->children = new Node<TK> *[M];
        for (int i = 0; i < M; i++) {
            this->children[i] = nullptr;
        }
        this->count = 0;
        this->leaf = _leaf;
    }

    int insert(TK value) {
        int i = this->count - 1;
        for (; i >= 0; i--) {
            if (value > this->keys[i]) {
                break;
            } else {
                this->keys[i + 1] = this->keys[i];
            }
        }
        this->keys[i + 1] = value;
        (this->count)++;
        return i + 1;
    }

    int insert(Node<TK> *node, int M, Node<TK> *cmp) {
        int i = M - 1;
        for (; i >= 0; i--) {
            if (children[i] == cmp) {
                break;
            } else {
                this->children[i + 1] = this->children[i];
            }
        }
        this->children[i + 1] = node;
        return i + 1;
    }

    void print() {
        for (int i = 0; i < this->count; i++) {
            cout << this->keys[i] << " ";
        }
        cout << endl;
    }

    void killSelf() {
        for (int i = 0; i <= this->count; i++) {
            if (this->children[i] != nullptr) {
                this->children[i]->killSelf();
            }
        }
        if (this->keys != nullptr) delete[] this->keys;
        if (this->children[0] == nullptr) delete[] this->children;
        delete this;
    }

    void display(const string &sep = ",") {
        int i;
        for (i = 0; i < count; i++) {
            if (children[i] != nullptr) {
                children[i]->display();
            }
            cout << keys[i] << sep;
        }
        if (children[i] != nullptr) {
            children[i]->display();
        }
    }

    void toString(string &result, const string &sep = ",") {
        int i;
        for (i = 0; i < count; i++) {
            if (children[i] != nullptr) {
                children[i]->toString(result, sep);
            }
            result += std::to_string(keys[i]) + sep;
        }
        if (children[i] != nullptr) {
            children[i]->toString(result, sep);
        }
    }

    void display_keys(const string &sep = ",") {
        int i;
        for (i = 0; i < count; i++) {
            cout << keys[i] << sep;
        }
    }


    void remove(int idx) {
        for (; idx < count - 1; idx++) {
            this->keys[idx] = this->keys[idx + 1];
        }
        this->count = this->count - 1;
    }

    void remove(int idx, int M) {
        for (; idx <= count; idx++) {
            this->children[idx] = this->children[idx + 1];
        }
        for (int i = this->count + 1; i < M; i++) {
            this->children[i] = nullptr;
        }
    }
};


/////////// BTREE //////
template<typename TK>
struct SplitResult {
    TK key;
    Node<TK> *right_tree;
    SplitResult() { right_tree = nullptr; }
    SplitResult(TK _k, Node<TK> *_node) : key(_k), right_tree(_node) {}
};

template<typename TK>
class BTree {
private:
    Node<TK> *root;
    int M;// grado u orden del arbol
    int n;// total de elementos en el arbol


public:
    BTree(int _M) : root(nullptr), M(_M), n(0) {}

    bool search(TK key) { return search(this->root, key); };                 //indica si se encuentra o no un elemento
    void insert(TK key);                                                     //inserta un elemento
    void remove(TK key);                                                     //elimina un elemento
    int height() { return height(this->root); };                             //altura del arbol. Considerar altura -1 para arbol vacio
    string toString(const string &sep) { return toString(this->root, sep); };// recorrido inorder

    TK minKey() { return minKey(this->root); };// minimo valor de la llave en el arbol
    TK maxKey() { return maxKey(this->root); };// maximo valor de la llave en el arbol
    void clear() {
        this->root->killSelf();
        this->root = nullptr;
        n = 0;
    };                                   // eliminar todos lo elementos del arbol
    int size() { return n; };            // retorna el total de elementos insertados
    ~BTree() { this->root->killSelf(); };// liberar memoria

    void display_pretty() { display_pretty(this->root); };

    void rangeSearch(TK min, TK max) {

        rangeSearch(this->root, min, max);
    }

private:
    void rangeSearch(Node<TK> *node, TK min, TK max) {
        if (node == nullptr) return;
        int i = 0;
        while (i < node->count && node->keys[i] < min)
            i++;
        if (i < node->count && node->keys[i] >= min && node->keys[i] <= max)
            cout << node->keys[i] << " ";
        if (node->leaf)
            return;
        rangeSearch(node->children[i], min, max);
        while (i < node->count && node->keys[i] <= max) {
            rangeSearch(node->children[i + 1], min, max);
            i++;
        }
    }

    bool search(Node<TK> *&node, TK key);

    SplitResult<TK> *insert(Node<TK> *&node, TK key);
    void relocate(Node<TK> *&node, TK key, Node<TK> *key_right_tree = nullptr);
    Node<TK> *generate_right_node(Node<TK> *&node, int from);
    SplitResult<TK> *split_par(Node<TK> *&node, TK key, Node<TK> *key_right_tree = nullptr);
    SplitResult<TK> *split_impar(Node<TK> *&node, TK key, Node<TK> *key_right_tree = nullptr);

    void remove(Node<TK> *child, Node<TK> *parent, TK key);
    Node<TK> *successor(Node<TK> *node, int idx);
    Node<TK> *predecessor(Node<TK> *node, int idx);
    Node<TK> *minNode(Node<TK> *node);
    Node<TK> *maxNode(Node<TK> *node);

    int height(Node<TK> *node);
    string toString(Node<TK> *node, const string &sep);

    TK minKey(Node<TK> *node);
    TK maxKey(Node<TK> *node);

    void display_pretty(Node<TK> *root);
};

template<typename TK>
bool BTree<TK>::search(Node<TK> *&node, TK key) {
    if (node == nullptr) { return false; }

    for (int i = 0; i < node->count; i++) {
        if (node->keys[i] == key) {
            return true;
        } else {
            if (key < node->keys[i]) {
                return search(node->children[i], key);
            }
            if (i + 1 == node->count) {
                return search(node->children[i + 1], key);
            }
        }
    }
    return false;
}

template<typename TK>
void BTree<TK>::remove(TK key) {
    if (this->root != nullptr) {
        remove(this->root, this->root, key);
    }
    (this->n)--;
}

template<typename TK>
void BTree<TK>::remove(Node<TK> *child, Node<TK> *parent, TK key) {
    int i = 0;
    bool found = false;
    for (; i < child->count; i++) {
        if (key == child->keys[i]) {
            found = true;
            break;
        }
    }
    // *No se encontro y es un nodo hoja.
    if (!found & child->leaf) {
        return;
    }
    // *No se encontro y es un nodo interno.
    else if (!found & !child->leaf) {
        int idx = 0;
        for (; idx < child->count; idx++) {
            if (key < child->keys[idx]) {
                remove(child->children[idx], child, key);
                break;
            } else if (idx + 1 == child->count) {
                remove(child->children[idx + 1], child, key);
                break;
            }
        }
    }
    // *Se encontro y es un nodo hoja.
    else if (found & child->leaf) {
        child->remove(i);
    }
    // *Se encontro y es un nodo interno.
    else if (found & !child->leaf) {
        Node<TK> *sc = successor(child, i);
        TK temp = sc->keys[0];
        sc->keys[0] = key;
        child->keys[i] = temp;
        remove(child->children[i + 1], child, key);
        //return; // warning
    }

    // !Important
    int minKeys = floor((this->M - 1) / 2);
    if (child->count < minKeys && child != this->root) {
        int ichild = 0;
        for (; ichild <= parent->count; ichild++) {
            if (parent->children[ichild] == child) {
                break;
            }
        }
        Node<TK> *hermano = nullptr;
        int idxKeyParent;
        int idxNodeHermano;
        bool right = false;
        if (ichild == 0)// *Inmediato derecho.
        {
            idxNodeHermano = ichild + 1;
            idxKeyParent = ichild;
            right = true;
            if (parent->children[ichild + 1]->count > minKeys) {
                hermano = parent->children[ichild + 1];
            }
        } else if (ichild == parent->count)// *Inmediato izquierdo.
        {
            idxKeyParent = ichild - 1;
            idxNodeHermano = ichild - 1;
            if (parent->children[ichild - 1]->count > minKeys) {
                hermano = parent->children[ichild - 1];
            }
        } else if (0 < ichild & ichild < parent->count)// *Inmediato derecho e izquierdo.
        {
            if (parent->children[ichild + 1]->count > minKeys) {
                hermano = parent->children[ichild + 1];
                idxKeyParent = ichild;
                right = true;
            } else if (parent->children[ichild - 1]->count > minKeys) {
                hermano = parent->children[ichild - 1];
                idxKeyParent = ichild - 1;
            } else {
                idxNodeHermano = ichild + 1;
                idxKeyParent = ichild;
                right = true;
            }
        }

        // Rotacion
        if (hermano != nullptr) {
            child->insert(parent->keys[idxKeyParent]);
            parent->remove(idxKeyParent);
            right ? parent->insert(hermano->keys[0]) : parent->insert(hermano->keys[hermano->count - 1]);
            right ? hermano->remove(0) : hermano->remove(hermano->count - 1);
            if (!(child->leaf)) {
                if (right) {
                    child->children[child->count] = hermano->children[0];
                    hermano->remove(0, this->M);
                } else {
                    for (int i = child->count; i >= 0; i--) {
                        child->children[i + 1] = child->children[i];
                    }
                    child->children[0] = hermano->children[hermano->count + 1];
                    hermano->remove(hermano->count + 1, this->M);
                }
            }
            // Merge
        } else {
            /*       cout<<"Merge INICIO"<<endl;
      cout<<"Parent: ";parent->display_keys();cout<<endl;
      cout<<"Child: ";child->display_keys();cout<<endl; */

            Node<TK> *hermano = parent->children[idxNodeHermano];
            /*       cout<<"Hermano: ";hermano->display_keys();cout<<endl;
 */
            if (!right) {
                Node<TK> *temp = child;
                child = hermano;
                hermano = temp;
                idxNodeHermano++;
            }

            // Inserta elementos del hermano al nodo
            int idxInsertedParent = child->insert(parent->keys[idxKeyParent]);
            parent->remove(idxKeyParent);
            for (int idx_hermano = 0; idx_hermano < hermano->count; idx_hermano++) {
                child->insert(hermano->keys[idx_hermano]);
            }
            // Inserta hojas del nodo hermano al nodo merge
            if (!(child->leaf)) {
                for (int idx_child_hermano = 0; idx_child_hermano <= hermano->count; idx_child_hermano++) {
                    child->children[idxInsertedParent + 1] = hermano->children[idx_child_hermano];
                    hermano->children[idx_child_hermano] = nullptr;
                    idxInsertedParent++;
                }
            }
            Node<TK> *temp = hermano;
            parent->remove(idxNodeHermano, this->M);
            /*       cout<<"Merge FINAL"<<endl;
      cout<<"Parent after: ";parent->display_keys();cout<<endl;
      cout<<"Child after: ";child->display_keys();cout<<endl;
      cout<<"Hermano after: ";hermano->display_keys();cout<<endl; */

            temp->killSelf();
        }
    } else if (child == this->root && child->count == 0) {
        /*     cout<<"rrrr"<<endl;
 */
        if (child->children[0] != nullptr) {
            Node<TK> *temp = child->children[0];
            child->children[0] = nullptr;
            this->root->killSelf();
            this->root = temp;
        }
    }
}

template<typename TK>
Node<TK> *BTree<TK>::successor(Node<TK> *node, int idx) {
    return minNode(node->children[idx + 1]);
}

template<typename TK>
Node<TK> *BTree<TK>::predecessor(Node<TK> *node, int idx) {
    return maxNode(node->children[idx - 1]);
}

template<typename TK>
Node<TK> *BTree<TK>::minNode(Node<TK> *node) {
    if (node->leaf) {
        return node;
    } else {
        return minNode(node->children[0]);
    }
}

template<typename TK>
Node<TK> *maxNode(Node<TK> *node) {
    if (node->leaf) {
        return node;
    } else {
        return maxNode(node->children[node->count]);
    }
}

template<typename TK>
void BTree<TK>::insert(TK key) {
    if (this->root == nullptr) {
        this->root = new Node<TK>(this->M, true);
        root->insert(key);
    } else {
        SplitResult<TK> *split_result = insert(this->root, key);
        if (split_result != nullptr) {
            Node<TK> *parent = new Node<TK>(M, false);
            parent->keys[0] = split_result->key;
            parent->children[0] = root;
            parent->children[1] = split_result->right_tree;
            parent->count = 1;
            root = parent;
        }
    }
    (this->n)++;
}

template<typename TK>
SplitResult<TK> *BTree<TK>::insert(Node<TK> *&node, TK key) {
    int i = 0;
    while (i < node->count && key > node->keys[i])
        i++;
    if (i < node->count && node->keys[i] == key)
        return nullptr;

    if (node->leaf) {
        // si la hoja tiene espacio, insertar
        if (node->count < M - 1)
            relocate(node, key);
        // dividir y retornar el resultado al antecesor
        else if (M % 2 == 0)
            return split_par(node, key);
        else
            return split_impar(node, key);
    }
    // es nodo interno
    else {
        // insertar en el hijo respectivo
        SplitResult<TK> *split_result = insert(node->children[i], key);
        // si split_result != null es porque se produjo un split en el children[i]
        if (split_result != nullptr) {
            // si hay espacio, reubicar el split_result
            if (node->count < M - 1)
                relocate(node, split_result->key, split_result->right_tree);
            // caso, dividir y retornar el nuevo nodo al antecesor
            else if (M % 2 == 0)
                return split_par(node, split_result->key, split_result->right_tree);
            else
                return split_impar(node, split_result->key, split_result->right_tree);
        }
    }
    return nullptr;
}

template<typename TK>
void BTree<TK>::relocate(Node<TK> *&node, TK key, Node<TK> *key_right_tree) {
    int i = node->count - 1;
    // se  mueve las keys para dejar espacio para la nueva key
    while (i >= 0 && key < node->keys[i]) {
        node->keys[i + 1] = node->keys[i];
        node->children[i + 2] = node->children[i + 1];
        i--;
    }
    i++;
    node->keys[i] = key;
    node->children[i + 1] = key_right_tree;
    node->count++;
}

template<typename TK>
Node<TK> *BTree<TK>::generate_right_node(Node<TK> *&node, int from) {
    Node<TK> *right_node = new Node<TK>(M, node->leaf);
    // copiar llaves e hijos desde el nodo original
    int i = from, j = 0;
    while (i < M - 1)// recordar que el nodo esta lleno
    {
        right_node->keys[j] = node->keys[i];
        right_node->children[j] = node->children[i];
        i++;
        j++;
    }
    right_node->children[j] = node->children[i];
    right_node->count = j;
    return right_node;
}

template<typename TK>
SplitResult<TK> *BTree<TK>::split_par(Node<TK> *&node, TK key, Node<TK> *key_right_tree) {
    // calcular el elemento central
    int m = (M - 1) / 2;
    TK middle = node->keys[m];
    // crear nodo derecho desde m+1
    Node<TK> *right_node = generate_right_node(node, m + 1);
    // actualizar la cantidad de elementos del nodo
    node->count = m;
    // insertar la key en el lado respectivo
    if (key < middle)
        relocate(node, key, key_right_tree);
    else
        relocate(right_node, key, key_right_tree);
    // retornar el elemento central y el nodo derecho
    return new SplitResult<TK>(middle, right_node);
}

template<typename TK>
SplitResult<TK> *BTree<TK>::split_impar(Node<TK> *&node, TK key, Node<TK> *key_right_tree) {
    Node<TK> *right_node;
    TK middle;
    // calcular el elemento central correctamente
    int m = (M - 1) / 2;
    if (key > node->keys[m]) {
        right_node = generate_right_node(node, m + 1);
        middle = node->keys[m];
        node->count = m;
        relocate(right_node, key, key_right_tree);
    } else {
        m = m - 1;
        right_node = generate_right_node(node, m + 1);
        if (key < node->keys[m]) {
            middle = node->keys[m];
            node->count = m;
            relocate(node, key, key_right_tree);
        } else {// en caso que la llave a insertar ocupe la mitad
            middle = key;
            node->count = m + 1;
            right_node->children[0] = key_right_tree;
        }
    }
    // retornar el elemento central y el nodo derecho
    return new SplitResult<TK>(middle, right_node);
}


template<typename TK>
int BTree<TK>::height(Node<TK> *node) {
    if (node == nullptr) {
        return -1;
    } else {
        return 1 + height(node->children[0]);
    }
}

template<typename TK>
string BTree<TK>::toString(Node<TK> *node, const string &sep) {
    string result = "";
    root->toString(result, sep);
    return result.substr(0, result.size() - sep.length());
}

template<typename TK>
TK BTree<TK>::minKey(Node<TK> *node) {
    if (root == nullptr) { throw std::out_of_range("Tree is empty"); }
    if (node->leaf) {
        return node->keys[0];
    } else {
        return minKey(node->children[0]);
    }
}

template<typename TK>
TK BTree<TK>::maxKey(Node<TK> *node) {
    if (root == nullptr) { throw std::out_of_range("Tree is empty"); }
    if (node->leaf) {
        return node->keys[node->count - 1];
    } else {
        return maxKey(node->children[node->count]);
    }
}

template<typename TK>
void BTree<TK>::display_pretty(Node<TK> *root) {
    if (root == NULL)
        return;
    int i, j, n;
    queue<Node<TK> *> q;
    q.push(root);
    while (!q.empty()) {
        n = q.size();
        for (i = 0; i < n; i++) {
            Node<TK> *node = q.front();
            cout << "<";
            for (j = 0; j < node->count; j++)
                cout << node->keys[j] << " ";
            cout << "> ";
            q.pop();
            if (!node->leaf) {
                q.push(node->children[0]);
                for (j = 1; j <= node->count; j++)
                    q.push(node->children[j]);
            }
        }
        cout << endl;
    }
}


#endif//PROYECTO_BLOCKCHAIN_BTREE_H
