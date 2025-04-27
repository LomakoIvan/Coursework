#include "Applicants.h"
#include <iostream>

using namespace std;

Node* GetNodeInDeck(Deck& deck, unsigned int node_number) {
	unsigned int node_count = deck.GetNodeCount();
	if (node_number >= node_count || node_number < 0) { return nullptr; }

	Node* node = deck.get_front_node();
	for (int i = 0; i < node_number; i++) {
		node = node->prev_ptr;
	}
	
	return node;
}

void InsertSortMark(Deck& deck) {
	unsigned int node_count = deck.GetNodeCount();
	if (node_count < 2) { return; }
	
	Node* head_node = GetNodeInDeck(deck, 1);
	
	for (int i = 1; head_node != nullptr; i++) {
		Node* this_node = GetNodeInDeck(deck, i - 1);
		
		for (int j = i - 1; j >= 0 && this_node->data.mark > head_node->data.mark; j--) {
			swap(head_node->data, this_node->data);
			head_node = head_node->next_ptr;
			this_node = this_node->next_ptr;
		}

		head_node = GetNodeInDeck(deck, i + 1);
	}
}