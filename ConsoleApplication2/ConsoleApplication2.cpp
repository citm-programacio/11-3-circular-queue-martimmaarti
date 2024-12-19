#include <iostream>
using namespace std;

class CircularQueue {
public:
    CircularQueue(int capacity = 3) {
        _capacity = capacity;
        _array = new int[_capacity];
        _front = 0;
        _back = 0;
        _size = 0;
    }

    ~CircularQueue() {
        delete[] _array;
    }

    void enqueue(int value) {
        if (_size == _capacity) {  // Si la cola está llena, redimensionar
            resize();
        }

        _array[_back] = value;  // Insertar el valor en la posición de _back
        _back++;  // Mover _back a la siguiente posición circular
        _size++;  // Incrementar el tamaño
    }

    void dequeue() {
        if (empty()) {
            cout << "Queue is empty. Cannot dequeue.\n";
        }

        _front = (_front + 1) % _capacity;  // Mover _front a la siguiente posición circular
        _size--;  // Decrementar el tamaño
    }

    int size() const {
        return _size;
    }

    bool empty() const {
        return _size == 0;
    }

    void print() const {
        if (empty()) {
            cout << "Queue is empty. Nothing to print.\n";
            return;
        }

        cout << "Queue elements: ";
        int index = _front;
        for (int i = 0; i < _size; ++i) {
            cout << _array[index] << " ";
            index++;  // Avanzar circularmente
        }
        cout << endl;
    }

private:
    int _front;
    int _back;
    int* _array;
    int _capacity;
    int _size;

    void resize() {
        int newCapacity = _capacity +1;  // Duplicar la capacidad
        int* newArray = new int[newCapacity];

        // Copiar los elementos existentes
        int index = _front;
        for (int i = 0; i < _size; ++i) {
            newArray[i] = _array[index];
            index = (index + 1) % _capacity;  // Avanzar circularmente
        }

        // Actualizar punteros y capacidades
        delete[] _array;  // Liberar la memoria del arreglo anterior
        _array = newArray;  // Apuntar al nuevo arreglo
        _capacity = newCapacity;
        _front = 0;  // El frente siempre comienza en 0
        _back = _size;  // El siguiente índice disponible es después del último valor
    }
};

int main() {
    CircularQueue q(3);

    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    q.print();  // Imprime: Queue elements: 10 20 30

    q.enqueue(40);  // Esto dispara un cambio de tamaño
    q.print();  // Imprime: Queue elements: 10 20 30 40

    q.dequeue();  // Elimina el 10
    q.enqueue(50);
    q.print();  // Imprime: Queue elements: 20 30 40 50

    return 0;
}
