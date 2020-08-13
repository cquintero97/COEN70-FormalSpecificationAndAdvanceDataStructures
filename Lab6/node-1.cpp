// FILE: node.cpp
// IMPLEMENTS: The functions of the node class and the
// linked list toolkit (see node1.h for documentation).
// INVARIANT for the node class:
//   The data of a node is stored in data_field
//   and the link to the next node is stored in link_field.

#include "node.h"
#include <cassert> // Provides assert
#include <cstdlib>	// Provides NULL and size_t
#include <iostream>

namespace coen70_lab7 
{
    size_t list_length(const node* head_ptr)
        // Library facilities used: cstdlib
		{
        const node* cursor;
        size_t answer;
        
        answer = 0;
        for (cursor = head_ptr; cursor != NULL; cursor = cursor->link())
            ++answer;

        return answer;
    }

    void list_head_insert(node*& head_ptr, const node::value_type& entry) {
    	head_ptr = new node(entry, head_ptr);
    }

    void list_insert(node* previous_ptr, const node::value_type& entry) 
	{
    	node *insert_ptr;

    	insert_ptr = new node(entry, previous_ptr->link());
    	previous_ptr->set_link(insert_ptr);
    }

    node* list_search(node* head_ptr, const node::value_type& target) 
    // Library facilities used: cstdlib
    {
		node *cursor;

    	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link())
    	    if (target == cursor->data())
        		return cursor;

    	return NULL;
    }

    const node* list_search(const node* head_ptr, const node::value_type& target)
    // Library facilities used: cstdlib
	{	
		const node* cursor;

    	for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
    	    if (target == cursor->data( ))
        		return cursor;

    	return NULL;
    }

    node* list_locate(node* head_ptr, size_t position)
    // Library facilities used: cassert, cstdlib
	{
    	node* cursor;
    	size_t i;

    	assert (0 < position);
    	cursor = head_ptr;
    	for (i = 1; (i < position) && (cursor != NULL); i++)
    	    cursor = cursor->link();

    	return cursor;
    }

    const node* list_locate(const node* head_ptr, size_t position)
    // Library facilities used: cassert, cstdlib
	{
    	const node* cursor;
    	size_t i;

    	assert (0 < position);
    	cursor = head_ptr;
    	for (i = 1; (i < position) && (cursor != NULL); i++)
    	    cursor = cursor->link();

    	return cursor;
    }

    void list_head_remove(node*& head_ptr) 
	{
    	node* remove_ptr;

    	remove_ptr = head_ptr;
    	head_ptr = head_ptr->link();
    	delete remove_ptr;
    }

    void list_remove(node* previous_ptr) 
	{
		node* remove_ptr;

    	remove_ptr = previous_ptr->link();
    	previous_ptr->set_link(remove_ptr->link());
    	delete remove_ptr;
    }

    void list_clear(node*& head_ptr)
    // Library facilities used: cstdlib
	{
    	while (head_ptr != NULL)
    	    list_head_remove(head_ptr);
    }

    void list_copy(const node* source_ptr, node*& head_ptr, node*& tail_ptr)
    // Library facilities used: cstdlib
	{
    	head_ptr = NULL;
    	tail_ptr = NULL;

    	// Handle the case of the empty list.
    	if (source_ptr == NULL)
    	    return;

    	// Make the head node for the newly created list, and put data in it.
    	list_head_insert(head_ptr, source_ptr->data());
    	tail_ptr = head_ptr;

    	// Copy the rest of the nodes one at a time, adding at the tail of new list.
    	source_ptr = source_ptr->link();
    	while (source_ptr != NULL) 
		{
    	    list_insert(tail_ptr, source_ptr->data());
    	    tail_ptr = tail_ptr->link();
    	    source_ptr = source_ptr->link();
    	}
    }

    void list_piece(node* start_ptr, node* end_ptr, node*& head_ptr, node*& tail_ptr)
	{
        head_ptr = NULL;
        tail_ptr = NULL;
        // in case of empty list
        if (start_ptr == NULL)
		{
            return;
        }
        node *cursor;
        bool sameList = false;	//Checks if end_ptr and start_ptr are in the same list
        for (cursor = start_ptr; cursor != NULL && !sameList; cursor = cursor->link()) 
		{
            if (cursor == end_ptr)
                sameList = true;
        }
        if (!sameList)
            return;
        list_head_insert(head_ptr, start_ptr->data()); 
        tail_ptr = head_ptr; // tail_ptr points at head_ptr for newly created list
        // copies nodes one after another at the tail ends
        for (cursor = start_ptr->link(); cursor != NULL; cursor = cursor->link()) {
            list_insert(tail_ptr, cursor->data());
            tail_ptr = tail_ptr->link();
            if (cursor == end_ptr)
                return;
        }
    }

    size_t list_occurrences(node* head_ptr, const node::value_type& target) 
	{
        const node *cursor;
        size_t occurences = 0;
        for (cursor = head_ptr; cursor != NULL; cursor = cursor->link()) 
		{
            if (cursor->data() == target) 
			{
                occurences++; // counts number of occurences
            }
        }
        return occurences;
    }

    void list_insert_at(node*& head_ptr, const node::value_type& entry, size_t position) 
	{
        assert(position > 0);
        assert(position <= list_length(head_ptr)+1);
        node *cursor;
        if (position == 1) 
		{
            list_head_insert(head_ptr, entry);
        } 
		else 
		{
            cursor = list_locate(head_ptr, position-1);
            assert(cursor!= NULL);
            list_insert(cursor, entry);
        }
    }

    node::value_type list_remove_at(node*& head_ptr, size_t position) 
	{
        assert(position > 0);
        assert(position <= list_length(head_ptr)+1);     
        node *cursor;
        node::value_type result;       
        if (position == 1) 
		{
            assert(head_ptr != NULL);
            result = head_ptr->data();
            list_head_remove(head_ptr);
        } 
		else 
		{
            cursor = list_locate(head_ptr, position-1);
            assert(cursor != NULL);
            assert(cursor->link() != NULL);
            result = cursor->link()->data();
            list_remove(cursor);
        }    
        return result;
    }

    node* list_copy_segment(node* head_ptr, size_t start, size_t finish) 
	{
        assert(head_ptr != NULL);
        assert(start >= 1);
        assert(start <= finish);
        assert(finish <= list_length(head_ptr));
        node *start_ptr;
        node *finish_ptr;
        node *head;
        node *tail;       
        start_ptr = list_locate(head_ptr, start);
        finish_ptr = list_locate(start_ptr, finish-start+1);
        list_piece(start_ptr, finish_ptr, head, tail);
        return head;
    }
}
