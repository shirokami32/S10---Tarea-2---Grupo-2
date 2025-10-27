#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include <random>
using namespace std;

class CuckooHash {
private:
    vector<int> tabla1;
    vector<int> tabla2;
    int size;
    int maxIntentos;
    int vacio = INT_MIN;

    int hash1(int key){
        return key % size;
    }

    int hash2(int key){
        return (key / size + key * 7) % size;
    }
    void rehash() {
        cout << "Rehash activado. Nuevo tamano: " <<size * 2 << endl;
        vector<int> temporal;

        // guarda los datos actuales
        for (int x : tabla1) if (x != vacio) temporal.push_back(x);
        for (int x : tabla2) if (x != vacio) temporal.push_back(x);

        // duplica el size
        size *= 2;
        tabla1.assign(size, vacio);
        tabla2.assign(size, vacio);
        maxIntentos += 5;

        // reinsertar datos
        for (int x : temporal) insert(x);
    }

public:
    CuckooHash(int n, int intentos) {
        size = n;
        maxIntentos = intentos;
        tabla1.assign(size, vacio);
        tabla2.assign(size, vacio);
    }
    void insert(int key) {
        int actual = key;
        int intentos = 0;
        bool enPrimera = true;

        while (intentos < maxIntentos) {
            if (enPrimera) {
                int pos = hash1(actual);
                if (tabla1[pos] == vacio) {
                    tabla1[pos] = actual;
                    return;
                } else {
                    swap(actual, tabla1[pos]);
                    enPrimera = false;
                }
            } else {
                int pos = hash2(actual);
                if (tabla2[pos] == vacio) {
                    tabla2[pos] = actual;
                    return;
                } else {
                    swap(actual, tabla2[pos]);
                    enPrimera = true;
                }
            }
            intentos++;
        }
        rehash();
        insert(actual);
    }

   void print() {
        cout << "Tabla 1: ";
        for (int x : tabla1) {
            if (x == vacio) cout << "_ ";
            else cout << x << " ";
        }
        cout << endl;


        cout << "Tabla 2: ";
        for (int x : tabla2) {
            if (x == vacio) cout << "_ ";
            else cout << x << " ";
        }
        cout << endl;
    }
};

int main() {

    CuckooHash hash(5, 10);

    vector<int> datos(100);
    for (int i = 0; i < 100; ++i){
        datos[i] = i + 1;
    }

    random_device rd;
    mt19937 g(rd());

    shuffle(datos.begin(), datos.end(), g);


    for (int x : datos) {
        cout << "Insertando: " << x << endl;
        hash.insert(x);
        hash.print();
        cout << endl;
    }


    return 0;

}
