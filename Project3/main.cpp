#include <iostream>
#include "list.h"

void moveDisk(LinkedList<int>& source, LinkedList<int>& destination) {
    if (!source.isEmpty() && (destination.isEmpty() || source.top() < destination.top())) {
        destination.push_head(source.top());
        source.pop_head();
    }
}

// Рекурсивная функция для решения задачи о Ханойских башнях
void hanoiTower(int n, LinkedList<int>& source, LinkedList<int>& auxiliary, LinkedList<int>& destination) {
    if (n > 0) {
        hanoiTower(n - 1, source, destination, auxiliary);
        moveDisk(source, destination);
        hanoiTower(n - 1, auxiliary, source, destination);
    }
}

int main() {

    // Создаем три башни
    LinkedList<int> list1, list2;
    list2.push_tail(9);
    list2.push_tail(3);
    list2.push_tail(7);
    list2.print();

    list1.push_tail(2);
    list1.push_tail(4);
    list1.push_tail(5);
    list1.push_head(1);
    list1.print();

    list1.push_head(list2);
    list1.print();

    list2.push_tail(list1);
    list2.print();

    list2.pop_head();
    list2.pop_tail();
    list2.print();

    list2.delete_node(4);
    list2.print();

    list1[1] = 10;
    cout << list1[1] << endl;

    int numDisks = 4  ; // Количество дисков

    // Создаем три башни
    LinkedList<int> towerA, towerB, towerC;

    // Заполняем первую башню дисками
    for (int i = numDisks; i >= 1; --i) {
        towerA.push_head(i);
    }

    // Выводим начальное состояние башен
    cout << "Initial state:" << endl;
    cout << "Tower A: "; towerA.print();
    cout << "Tower B: "; towerB.print();
    cout << "Tower C: "; towerC.print();

    // Решаем задачу о Ханойских башнях
    hanoiTower(numDisks, towerA, towerB, towerC);

    // Выводим конечное состояние башен
    cout << "\nFinal state:" << endl;
    cout << "Tower A: "; towerA.print();
    cout << "Tower B: "; towerB.print();
    cout << "Tower C: "; towerC.print();

    return 0;
};