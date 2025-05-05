#ifndef SORTMODULE_H
#define SORTMODULE_H

bool isAlphabetically(char* first_str, char* second_str);

Applicant* GetApplicantInPosition(Queue& queue, int position);

void SwapApplicantsInPositions(Queue& queue, int position1, int position2);


void InsertSortMark(Queue& queue, bool reverse);

void InsertSortName(Queue& queue, bool reverse);


void HeapSortQueueMark(Queue& queue, bool reverse);

void HeapSortQueueName(Queue& queue, bool reverse);

#endif