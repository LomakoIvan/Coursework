#include "Applicants.h"
#include <iostream>

using namespace std;

Node* GetNodeInDeck(Deck& deck, unsigned int node_number) {
	unsigned int node_count = deck.GetNodeCount();
	if (node_number >= node_count) { return nullptr; }

	Node* node = deck.get_front_node();
	for (int i = 0; i < node_number; i++) {
		node = node->prev_ptr;
	}
	
	return node;
}

void InsertSortMark(Deck& deck) {
	unsigned int node_count = deck.GetNodeCount();
	if (node_count < 2) { return; }
	
	Node* current_node = GetNodeInDeck(deck, 1);
	
	for (int i = 1; current_node != nullptr; i++) {
		Node* this_node = GetNodeInDeck(deck, i - 1);
		Applicant key = current_node->data;
		
		int j = i - 1;
		for (; j >= 0 && this_node->data.mark > key.mark; j--) {
			current_node->data = this_node->data;
			current_node = this_node;
			this_node = this_node->next_ptr;
		}

		if (j != i - 1) {
			current_node->data = key;
		}

		current_node = GetNodeInDeck(deck, i + 1);
	}
}