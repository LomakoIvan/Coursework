#include "Applicants.h"
#include "Memory.h"
#include <iostream>

using namespace std;

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