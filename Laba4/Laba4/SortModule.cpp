#include "Applicants.h"
#include "Memory.h"
#include <iostream>

using namespace std;

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


void InsertSortMark(Queue& queue) {
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

            if (!inserted && current.mark > extracted.mark) {
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

void InsertSortName(Queue& queue) {
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

            if (!inserted && isAlphabetically(current.name, extracted.name)) {
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


void heapifyMark(Queue& queue, int size, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    Applicant* rootApplicant = GetApplicantInPosition(queue, i);
    Applicant* leftApplicant = GetApplicantInPosition(queue, left);
    Applicant* rightApplicant = GetApplicantInPosition(queue, right);

    if (left < size && leftApplicant->mark > rootApplicant->mark)
        largest = left;

    if (right < size && rightApplicant->mark > GetApplicantInPosition(queue, largest)->mark)
        largest = right;

    if (largest != i) {
        SwapApplicantsInPositions(queue, i, largest);
        heapifyMark(queue, size, largest);
    }
}

void heapSortQueueMark(Queue& queue) {
    int n = queue.GetNodeCount();
    if (n < 2) return;

    for (int i = n / 2 - 1; i >= 0; i--) {
        heapifyMark(queue, n, i);
    }

    for (int i = n - 1; i > 0; i--) {
        SwapApplicantsInPositions(queue, 0, i);
        heapifyMark(queue, i, 0);
    }
}


void heapifyName(Queue& queue, int size, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    Applicant* rootApplicant = GetApplicantInPosition(queue, i);
    Applicant* leftApplicant = GetApplicantInPosition(queue, left);
    Applicant* rightApplicant = GetApplicantInPosition(queue, right);

    if (left < size && isAlphabetically(leftApplicant->name, rootApplicant->name)) {
        largest = left;
    }

    if (right < size && isAlphabetically(rightApplicant->name, GetApplicantInPosition(queue, largest)->name)) {
        largest = right;
    }

    if (largest != i) {
        SwapApplicantsInPositions(queue, i, largest);
        heapifyName(queue, size, largest);
    }
}

void heapSortQueueName(Queue& queue) {
    int n = queue.GetNodeCount();
    if (n < 2) return;

    for (int i = n / 2 - 1; i >= 0; i--) {
        heapifyName(queue, n, i);
    }

    for (int i = n - 1; i > 0; i--) {
        SwapApplicantsInPositions(queue, 0, i);
        heapifyName(queue, i, 0);
    }
}