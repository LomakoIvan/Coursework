#ifndef APPLICANTS_H
#define APPLICANTS_H

struct Applicant {
	char* name;
	char* addr;
	int mark;
	char* date;
};

struct Deck {
private:
	struct Node {
		Applicant data;
		Node* next_ptr;
		Node* prev_ptr;
	};

	Node* start_node = nullptr;
	Node* end_node = nullptr;
	int node_count = 0;

	void ClearDataInApplicant(Applicant& applicant);

public:
	void Init();
	void DisplayFrontToBack();
	void DisplayBackToFront();
	void push_back(Applicant data);
	void push_front(Applicant data);
	Applicant* pop_front();
	Applicant* pop_back();
	int GetNodeCount();
	bool isEmpty();
	void Clear();
};

extern Deck applicants;

#endif