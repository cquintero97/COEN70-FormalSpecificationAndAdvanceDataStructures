// FILE: sequence.cpp
// IMPLEMENTS: The functions of the sequence class
// ( See sequence.h for implementation).

#include "sequence.h"
#include <cassert>
#include <cstdlib>
#include <iostream>

using namespace std;

namespace coen70_lab7 
{   
    sequence::sequence() 
	{
	// Sets all ptrs to NULL and many_nodes to 0
        head_ptr = NULL;
        tail_ptr = NULL;
        cursor = NULL;
        precursor = NULL;
        many_nodes = 0;
    }
    
    sequence::sequence(const sequence& source) 
	{
        if (!source.is_item()) 
		{
            list_copy(source.head_ptr, head_ptr, tail_ptr);
            precursor = NULL;
            cursor = NULL;
        } 
		else if (source.head_ptr == source.cursor) 
		{
            list_copy(source.head_ptr, head_ptr, tail_ptr);
            precursor = NULL;
            cursor = head_ptr;
        } 
		else 
		{
            list_piece(source.head_ptr, source.precursor, head_ptr, precursor);
            list_piece(source.cursor, source.tail_ptr, cursor, tail_ptr);
            precursor->set_link(cursor);
        }
        many_nodes = source.many_nodes;
    }
	
    sequence::~sequence() 
	{
        list_clear(head_ptr);
    }
    
    void sequence::start() 
	{
        if (many_nodes == 0) 
		{
            precursor = NULL;
            cursor = NULL;
        } 
		else 
		{
            precursor = NULL;
            cursor = head_ptr;
        }
    }
    
    void sequence::end() 
	{
        if (many_nodes == 0) 
		{
            precursor = NULL;
            cursor = NULL;
        }
		else if (many_nodes == 1) 
		{
            precursor = NULL; //since only one node
            cursor = tail_ptr;
        } 
		else 
		{
		// for more than one node
            cursor = tail_ptr;
            precursor = head_ptr;
            for (int i = 1; i < many_nodes-1; i++) 
			{
                precursor = precursor->link();
            }
        }
    }
    
    void sequence::advance() 
	{
        assert(is_item()); 
        if (cursor == tail_ptr) 
		{
            precursor = NULL;
            cursor = NULL;
        } 
		else 
		{
            precursor = cursor;
            cursor = cursor->link();
        }
    }
    
    void sequence::insert(const value_type& entry) 
	{
        if (many_nodes == 0) 
		{
            head_ptr = new node(entry);
            tail_ptr = head_ptr;
            cursor = head_ptr;
            precursor = NULL;
        } 
		else if (many_nodes == 1) 
		{
            list_head_insert(head_ptr, entry);
            tail_ptr = head_ptr->link();
            cursor = head_ptr;
            precursor = NULL;
        } 
		else 
		{
            if (cursor == NULL) 
			{
                list_head_insert(head_ptr, entry);
                cursor = head_ptr;
                precursor = NULL;
            } 
			else 
			{
                list_insert(precursor, entry);
                cursor = precursor->link();
            }
        }
        many_nodes++;
    }
    
    void sequence::attach(const value_type& entry) 
	{
        if (many_nodes == 0) 
		{
            list_head_insert(head_ptr, entry);
            cursor = head_ptr;
            tail_ptr = head_ptr;
            precursor = NULL;
        } 
		else if (many_nodes == 1) 
		{
            list_insert(cursor, entry);
            precursor = cursor;
            cursor = cursor->link();
            tail_ptr = cursor;
        } 
		else 
		{
            if (cursor == tail_ptr)
			{
                list_insert(cursor, entry);
                precursor = cursor;
                cursor = cursor->link();
                tail_ptr = cursor;
            } 
			else if (cursor == NULL) 
			{
                list_insert(tail_ptr, entry);
                precursor = tail_ptr;
                tail_ptr = tail_ptr->link();
                cursor = tail_ptr;
            } 
			else 
			{
                list_insert(cursor, entry);
                precursor = cursor;
                cursor = cursor->link();
            }
        }
        many_nodes++;
    }
    
    void sequence::remove_current() 
	{
        assert(is_item());  
        if (many_nodes == 1) 
		{
            list_head_remove(cursor);
        } 
		else 
		{
            if (precursor == NULL) 
			{
                list_head_remove(head_ptr);
                cursor = head_ptr;
            } 
			else 
			{
                if (cursor->link() != NULL) 
				{
                    cursor = cursor->link();
                } 
				else 
				{
                    cursor = NULL;
                }
                list_remove(precursor);
            }
        }
        many_nodes--;
    }
	
    void sequence::operator =(const sequence& source) 
	{
        if (!source.is_item()) 
		{
            list_copy(source.head_ptr, head_ptr, tail_ptr);
            precursor = NULL;
            cursor = NULL;
        } 
		else if (source.head_ptr == source.cursor) 
		{
            list_copy(source.head_ptr, head_ptr, tail_ptr);
            precursor = NULL;
            cursor = head_ptr;
        } 
		else 
		{
            list_piece(source.head_ptr, source.precursor, head_ptr, precursor);
            list_piece(source.cursor, source.tail_ptr, cursor, tail_ptr);
            precursor->set_link(cursor);
        }
        many_nodes = source.many_nodes;
    }
    
    sequence::size_type sequence::size() const 
	{
        return many_nodes;
    }
    
    bool sequence::is_item() const 
	{
        return (cursor != NULL);
    }
    
    sequence::value_type sequence::current() const 
	{
        assert(is_item());  
        return cursor->data();
    }
}