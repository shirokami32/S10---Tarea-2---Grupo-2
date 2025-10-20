#include <iostream>
#include <vector>
#include <climits>
using namespace std;

class CuckooHash {
private:
    vector<int> tabla1;
    vector<int> tabla2;
    int size;
    int maxIntentos;
    int vacio = INT_MIN;

    int hash1(int key) {
        return key % size;
    }

    int hash2(int key) {
        return (key / size) % size;
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
        tabla1.assign(size, VACIO);
        tabla2.assign(size, VACIO);
    }
    void insert(int key) {
        int actual = key;
        int intentos = 0;
        bool enPrimera = true;

        while (intentos < maxIntentos) {
            if (enPrimera) {
                int pos = hash1(actual);
                if (tabla1[pos] == VACIO) {
                    tabla1[pos] = actual;
                    return;
                } else {
                    swap(actual, tabla1[pos]);
                    enPrimera = false;
                }
            } else {
                int pos = hash2(actual);
                if (tabla2[pos] == VACIO) {
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





int main() {

}
