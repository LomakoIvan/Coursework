#include "Applicants.h"
#include "Data.h"
#include "Memory.h"
#include <iostream>

using namespace std;

void PrintSortMenu() {
    cout << "\n----------------Меню для сортировки базы данных----------------\n";
    cout << "\n1)Сортировка вставками по полю \"ФИО\"";
    cout << "\n2)Сортировка вставками по полю \"Оценка\"";
    cout << "\n3)Сортировка Флойда по полю \"ФИО\"";
    cout << "\n4)Сортировка Флойда по полю \"Оценка\"";
    cout << "\n0)Вернуться в главное меню";
}


Applicant* GetApplicantInPosition(Queue& queue, int position) {
    Queue temp_queue;
    Applicant* find_person = nullptr;

    if (position >= queue.GetNodeCount() || position < 0) { return nullptr; }

    for (int i = 0; !queue.isEmpty(); i++) {
        Applicant* person = queue.pop_front();

        if (i == position) {
            find_person = person;
        }

        temp_queue.push_back(*person);
    }

    for (int i = 0; !temp_queue.isEmpty(); i++) {
        queue.push_back(*temp_queue.pop_front());
    }

    return find_person;
}

void SwapApplicantsInPositions(Queue& queue, int position1, int position2) {
    int size = queue.GetNodeCount();
    Applicant* person1 = nullptr;
    Applicant* person2 = nullptr;
    Queue temp_queue;

    if ((position1 >= size || position1 < 0) || (position2 >= size || position2 < 0) || position1 == position2) { return; }

    for (int i = 0; !queue.isEmpty(); i++) {
        Applicant* extracted = queue.pop_front();

        if (i == position1) { person1 = extracted; }
        if (i == position2) { person2 = extracted; }

        temp_queue.push_back(*extracted);
    }

    if (!person1 || !person2) { position1 = position2 = -1; }

    for (int i = 0; !temp_queue.isEmpty(); i++) {
        Applicant extracted = *temp_queue.pop_front();

        if (i == position1) { extracted = *person2; }
        if (i == position2) { extracted = *person1; }

        queue.push_back(extracted);
    }
}

bool isAlphabetically(char* first_str, char* second_str) {
    int min_length = 0;

    if (strlen(first_str) > strlen(second_str)) { min_length = strlen(second_str); }
    else { min_length = strlen(first_str); }

    bool str_swap = false;

    int i = 0;
    for (; i < min_length && (int)first_str[i] == (int)second_str[i]; i++);

    if ((int)first_str[i] > (int)second_str[i]) { str_swap = true; }

    return str_swap;
}


void InsertSortMark(Queue& queue, bool reverse) {
    unsigned int queue_length = queue.GetNodeCount();
    if (queue_length < 2) { return; }

    Queue sortedQueue;
    sortedQueue.push_back(*queue.pop_front());

    while (!queue.isEmpty()) {
        Applicant extracted = *queue.pop_front();

        Queue tempQueue;
        bool inserted = false;

        while (!sortedQueue.isEmpty()) {
            Applicant current = *sortedQueue.pop_front();

            if (!inserted && current.mark > extracted.mark == !reverse) {
                tempQueue.push_back(extracted);
                inserted = true;
            }

            tempQueue.push_back(current);
        }

        if (!inserted) {
            tempQueue.push_back(extracted);
        }

        while (tempQueue.GetNodeCount() > 0) {
            sortedQueue.push_back(*tempQueue.pop_front());
        }
    }

    while (sortedQueue.GetNodeCount() > 0) {
        queue.push_back(*sortedQueue.pop_front());
    }
}

void InsertSortName(Queue& queue, bool reverse) {
    unsigned int queue_length = queue.GetNodeCount();
    if (queue_length < 2) { return; }

    Queue sortedQueue;
    sortedQueue.push_back(*queue.pop_front());

    while (!queue.isEmpty()) {
        Applicant extracted = *queue.pop_front();

        Queue tempQueue;
        bool inserted = false;

        while (!sortedQueue.isEmpty()) {
            Applicant current = *sortedQueue.pop_front();

            if (!inserted && isAlphabetically(current.name, extracted.name) == !reverse) {
                tempQueue.push_back(extracted);
                inserted = true;
            }

            tempQueue.push_back(current);
        }

        if (!inserted) {
            tempQueue.push_back(extracted);
        }

        while (tempQueue.GetNodeCount() > 0) {
            sortedQueue.push_back(*tempQueue.pop_front());
        }
    }

    while (sortedQueue.GetNodeCount() > 0) {
        queue.push_back(*sortedQueue.pop_front());
    }
}


void HeapifyMark(Queue& queue, int size, int i, bool reverse) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    Applicant* rootApplicant = GetApplicantInPosition(queue, i);
    Applicant* leftApplicant = GetApplicantInPosition(queue, left);
    Applicant* rightApplicant = GetApplicantInPosition(queue, right);

    if (left < size && leftApplicant->mark > rootApplicant->mark == !reverse)
        largest = left;

    if (right < size && rightApplicant->mark > GetApplicantInPosition(queue, largest)->mark == !reverse)
        largest = right;

    if (largest != i) {
        SwapApplicantsInPositions(queue, i, largest);
        HeapifyMark(queue, size, largest, reverse);
    }
}

void HeapSortQueueMark(Queue& queue, bool reverse) {
    int n = queue.GetNodeCount();
    if (n < 2) return;

    for (int i = n / 2 - 1; i >= 0; i--) {
        HeapifyMark(queue, n, i, reverse);
    }

    for (int i = n - 1; i > 0; i--) {
        SwapApplicantsInPositions(queue, 0, i);
        HeapifyMark(queue, i, 0, reverse);
    }
}


void HeapifyName(Queue& queue, int size, int i, bool reverse) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    Applicant* rootApplicant = GetApplicantInPosition(queue, i);
    Applicant* leftApplicant = GetApplicantInPosition(queue, left);
    Applicant* rightApplicant = GetApplicantInPosition(queue, right);

    if (left < size && isAlphabetically(leftApplicant->name, rootApplicant->name) == !reverse) {
        largest = left;
    }

    if (right < size && isAlphabetically(rightApplicant->name, GetApplicantInPosition(queue, largest)->name) == !reverse) {
        largest = right;
    }

    if (largest != i) {
        SwapApplicantsInPositions(queue, i, largest);
        HeapifyName(queue, size, largest, reverse);
    }
}

void HeapSortQueueName(Queue& queue, bool reverse) {
    int n = queue.GetNodeCount();
    if (n < 2) return;

    for (int i = n / 2 - 1; i >= 0; i--) {
        HeapifyName(queue, n, i, reverse);
    }

    for (int i = n - 1; i > 0; i--) {
        SwapApplicantsInPositions(queue, 0, i);
        HeapifyName(queue, i, 0, reverse);
    }
}


void SortMenuExercise1() {
    system("cls");

    cout << "Варианты сортировки:";
    cout << "\n1) В алфавитном порядке";
    cout << "\n2) В обратном алфавитном порядке";
    cout << "\n0) Вернуться в главное меню";

    while (true) {
        int option = GetCheckIntData((char*)"\n\nВыберете один из вариантов: ", (char*)"\nОшибка ввода.\n");

        switch (option) {
        case 1: {
            InsertSortName(applicants, false);
            cout << "\nБаза данных была отсортированна в алфавитном порядке\n";
            return;
        }
        case 2: {
            InsertSortName(applicants, true);
            cout << "\nБаза данных была отсортированна в обратном алфавитном порядке";
            return;
        }
        case 0: {
            return;
        }
        default: {
            cout << "\nВарианта под таким номером нет. Попробуйте снова.\n";
            break;
        }
        }
    }
}

void SortMenuExercise2() {
    system("cls");

    cout << "Варианты сортировки:";
    cout << "\n1) От меньшего к большему";
    cout << "\n2) От большего к меньшему";
    cout << "\n0) Вернуться в главное меню";

    while (true) {
        int option = GetCheckIntData((char*)"\n\nВыберете один из вариантов: ", (char*)"\nОшибка ввода.\n");

        switch (option) {
        case 1: {
            InsertSortMark(applicants, false);
            cout << "\nБаза данных была отсортированна по возрастанию\n";
            return;
        }
        case 2: {
            InsertSortMark(applicants, true);
            cout << "\nБаза данных была отсортированна по убыванию\n";
            return;
        }
        case 0: {
            return;
        }
        default: {
            cout << "\nВарианта под таким номером нет. Попробуйте снова.\n";
            break;
        }
        }
    }
}

void SortMenuExercise3() {
    system("cls");

    cout << "Варианты сортировки:";
    cout << "\n1) В алфавитном порядке";
    cout << "\n2) В обратном алфавитном порядке";
    cout << "\n0) Вернуться в главное меню";

    while (true) {
        int option = GetCheckIntData((char*)"\n\nВыберете один из вариантов: ", (char*)"\nОшибка ввода.\n");

        switch (option) {
            case 1: {
                HeapSortQueueName(applicants, false);
                cout << "\nБаза данных была отсортированна в алфавитном порядке\n";
                return;
            }
            case 2: {
                HeapSortQueueName(applicants, true);
                cout << "\nБаза данных была отсортированна в обратном алфавитном порядке";
                return;
            }
            case 0: {
                return;
            }
            default: {
                cout << "\nВарианта под таким номером нет. Попробуйте снова.\n";
                break;
            }
        }
    }
}

void SortMenuExercise4() {
    system("cls");

    cout << "Варианты сортировки:";
    cout << "\n1) От меньшего к большему";
    cout << "\n2) От большего к меньшему";
    cout << "\n0) Вернуться в главное меню";

    while (true) {
        int option = GetCheckIntData((char*)"\n\nВыберете один из вариантов: ", (char*)"\nОшибка ввода.\n");

        switch (option) {
            case 1: {
                HeapSortQueueMark(applicants, false);
                cout << "\nБаза данных была отсортированна по возрастанию\n";
                return;
            }
            case 2: {
                HeapSortQueueMark(applicants, true);
                cout << "\nБаза данных была отсортированна по убыванию\n";
                return;
            }
            case 0: {
                return;
            }
            default: {
                cout << "\nВарианта под таким номером нет. Попробуйте снова.\n";
                break;
            }
        }
    }
}


void SortMenu() {
    bool close = false;

    while (!close) {
        PrintSortMenu();
        
        int option = GetCheckIntData((char*)"\n\nВведите номер сортировки: ", (char*)"\nОшибка ввода\n");

        switch (option) {
            case 1: { SortMenuExercise1(); return; }
            case 2: { SortMenuExercise2(); return; }
            case 3: { SortMenuExercise3(); return; }
            case 4: { SortMenuExercise4(); return; }
            case 0: { return; }
        }

        system("pause");
        system("cls");
    }
}