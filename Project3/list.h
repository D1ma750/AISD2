#pragma once
#include <iostream>
#include <stdexcept>
#include <random>
#include <cstdlib>
#include<ctime>
#include <locale>
#include <windows.h>

using namespace std;


// Узел списка
template<typename T>
struct Node {
    T _data;
    Node* _next;

    Node(T value) : _data(value), _next(nullptr) {}
};


// Класс односвязного циклического связного списка
template<typename T>
class LinkedList {
private:
    Node<T>* _head;

public:

    LinkedList() : _head(nullptr) {}


    LinkedList(const LinkedList& other) {
        if (other._head == nullptr) {
            _head = nullptr;
            return;
        }
        _head = new Node<T>(other._head->_data);
        Node<T>* inf = _head;
        Node<T>* otherInf = other._head->_next;
        while (otherInf != nullptr && otherInf != other._head) {
            inf->_next = new Node<T>(otherInf->_data);
            inf = inf->_next;
            otherInf = otherInf->_next;
        }
        inf->_next = _head;
    }


    LinkedList(int size) : _head(nullptr) {
        std::srand(time(NULL));
        for (int i = 0; i < size; ++i) {
            push_tail(std::rand() % 100);
        }
    }


    ~LinkedList() {
        if (_head == nullptr) return;
        Node<T>* inf = _head;
        Node<T>* nextNode;
        do {
            nextNode = inf->_next;
            delete inf;
            inf = nextNode;
        } while (inf != _head);
    }


    LinkedList& operator=(const LinkedList& other) {
        if (this != &other) {
            this->~LinkedList();
            new (this) LinkedList(other);
        }
        return *this;
    }

    void push_tail(const T& value) {       // добавление нового элемента в конец
        Node<T>* newNode = new Node<T>(value);
        if (_head == nullptr) {
            _head = newNode;
            newNode->_next = _head;
        }
        else {
            Node<T>* inf = _head;
            while (inf->_next != _head) {
                inf = inf->_next;
            }
            inf->_next = newNode;
            newNode->_next = _head;
        }
    }

    void push_tail(const LinkedList& other) {        //добавление нового списка в конец
        if (other._head == nullptr) return;
        Node<T>* otherInf = other._head;
        do {
            push_tail(otherInf->_data);
            otherInf = otherInf->_next;
        } while (otherInf != other._head);
    }

    void push_head(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        if (_head == nullptr) {
            _head = newNode;
            newNode->_next = _head;
        }
        else {
            Node<T>* inf = _head;
            while (inf->_next != _head) {
                inf = inf->_next;
            }
            newNode->_next = _head;
            _head = newNode;
            inf->_next = _head;
        }
    }

    void push_head(const LinkedList& list)
    {
        Node<T>* otherInf = list._head;
        for (size_t i = list.GetSize(); i > 0; --i)
        {
            this->push_head(list[i]);
        }
        push_head(otherInf->_data);
    }

    void pop_head() {
        if (_head == nullptr) throw std::runtime_error("List is empty.");
        Node<T>* inf = _head;
        if (inf->_next == _head) {
            delete inf;
            _head = nullptr;
        }
        else {
            Node<T>* tail = _head;
            while (tail->_next != _head) {
                tail = tail->_next;
            }
            _head = _head->_next;
            tail->_next = _head;
            delete inf;
        }
    }


    void pop_tail() {
        if (_head == nullptr) throw std::runtime_error("List is empty.");
        Node<T>* inf = _head;
        if (inf->_next == _head) {
            delete inf;
            _head = nullptr;
        }
        else {
            Node<T>* prev = nullptr;
            while (inf->_next != _head) {
                prev = inf;
                inf = inf->_next;
            }
            prev->_next = _head;
            delete inf;
        }
    }

    // Удаление всех элементов с заданным значением
    void delete_node(const T& value) {
        while (_head != nullptr && _head->_data == value) {
            pop_head();
        }
        if (_head == nullptr) return;
        Node<T>* inf = _head;
        Node<T>* prev = nullptr;
        do {
            if (inf->_data == value) {
                if (prev) {
                    prev->_next = inf->_next;
                    delete inf;
                    inf = prev->_next;
                }
                else {
                    pop_head();
                    inf = _head; // Если голова была удалена, возвращаемся к ней
                }
            }
            else {
                prev = inf;
                inf = inf->_next;
            }
        } while (inf != _head);
    }

    // Доступы по индексу
    T& operator[](int index) {
        if (index < 0) throw std::out_of_range("Index out of range.");
        Node<T>* inf = _head;
        for (int i = 0; i < index && inf != nullptr; ++i) {
            inf = inf->_next;
        }
        if (inf == nullptr) throw std::out_of_range("Index out of range.");
        return inf->_data;
    }

    const T& operator[](int index) const {
        if (index < 0) throw std::out_of_range("Index out of range.");
        Node<T>* inf = _head;
        for (int i = 0; i < index && inf != nullptr; ++i) {
            inf = inf->_next;
        }
        if (inf == nullptr) throw std::out_of_range("Index out of range.");
        return inf->_data;
    }

    // Вывод списка
    void print() const {
        if (_head == nullptr) {
            std::cout << "List is empty." << std::endl;
            return;
        }
        Node<T>* inf = _head;
        do {
            std::cout << inf->_data << " ";
            inf = inf->_next;
        } while (inf != _head);
        std::cout << std::endl;
    }
    
    size_t GetSize() const
    {
        size_t count = 0;
        Node<T>* ptr = this->_head;
        while (ptr->_next != _head)
        {
            ptr = ptr->_next;
            ++count;
        }
        return count;
    }

    T top() const {
        if (isEmpty()) throw runtime_error("List is empty.");
        return _head->_data;
    }

    bool isEmpty() const {
        return _head == nullptr;
    }
};
