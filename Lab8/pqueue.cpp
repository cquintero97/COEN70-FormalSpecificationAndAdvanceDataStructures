// FILE: pqueue.cpp
// IMPLEMENTS: The functions of the PriorityQueue class and node class 
// (see pqueue.h for documentation).
//

#include "pqueue.h"
#include <cassert>

namespace coen70_lab8 
{
    PriorityQueue::PriorityQueue(PriorityQueue& other) 
	{
        if (head_ptr == other.head_ptr)
            return;       
        // sets head_ptr as NULL
        head_ptr = NULL;
        many_nodes = 0;
        // if list is empty
        if (other.head_ptr == NULL)
            return;
        node* cursor = other.head_ptr;
		// Copy the nodes one at a time
        while (cursor != NULL) 
		{
            insert(cursor->data(), cursor->priority());
            cursor = cursor->link();
        }
    }
    
    PriorityQueue::~PriorityQueue() 
	{
        node* remove_ptr;
        while (head_ptr != NULL) 
		{
            remove_ptr = head_ptr;
            head_ptr = head_ptr->link();
            delete remove_ptr;
        }
        many_nodes = 0;
    }
    
    void PriorityQueue::operator =(const PriorityQueue& other) 
	{
        if (head_ptr == other.head_ptr)
            return;     
        // Clear all nodes in pqueue
        node* remove_ptr;
        while (head_ptr != NULL) 
		{
            remove_ptr = head_ptr;
            head_ptr = head_ptr->link();
            delete remove_ptr;
        }
        many_nodes = 0;        
        // if list is empty
        if (other.head_ptr == NULL)
            return;        
        node* cursor = other.head_ptr;
        // Copy the nodes one at a time
        while (cursor != NULL) 
		{
            insert(cursor->data(), cursor->priority());
            cursor = cursor->link();
        }
    }
    
    PriorityQueue::Item PriorityQueue::get_front() 
	{
        assert(size() > 0);       
        Item item = head_ptr->data();
        node* remove_ptr = head_ptr;
        head_ptr = head_ptr->link();
        delete remove_ptr;
        many_nodes--;  
        return item;
    }
    
    void PriorityQueue::insert(const Item& entry, unsigned int priority) 
	{
        if (head_ptr == NULL) // new ptr for head if empty list
		{
            head_ptr = new node(entry, priority);
            many_nodes++;
        } 
		else 
		{
            node* cursor = head_ptr;
            if (priority > cursor->priority()) //if priority of node is greater than head priority
			{ 
                node* temp = head_ptr;
                head_ptr = new node(entry, priority);
                many_nodes++;
                head_ptr->set_link(temp);
            } 
			else 
			{
                while (cursor->link() != NULL) 
				{
                    if (priority > cursor->link()->priority()) 
					{ 	
					// if priority is greater than cursor->link()->priority()
					//cursor links to a new node and set the new link to old link
                        node* temp = cursor->link(); 
                        cursor->set_link(new node(entry, priority)); 
                        many_nodes++;
                        cursor->link()->set_link(temp);
                        return;
                    }
                    cursor = cursor->link();
                }
				// if priority is less than all nodes then create new node at end of pqueue
                cursor->set_link(new node(entry, priority)); 
                many_nodes++;
			}
        }
    }
}
