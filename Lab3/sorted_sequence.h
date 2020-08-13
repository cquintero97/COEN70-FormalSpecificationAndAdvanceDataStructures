// FILE: sorted_sequence.h
// CLASS PROVIDED: sorted_sequence (part of the namespace scu_coen70)
//
// TYPEDEFS and MEMBER CONSTANTS for the sequence class: 
// typedef ____ value_type
// sorted_sequence::value_type is the data type of the items in the
// sequence. It may be any of the C++ built-in types (int, char,
// etc.), or a class with a default constructor, an assignment operator, and a copy constructor.
//
// typedef ____ size_type
// sorted_sequence::size_type is the data type of any variable that keeps track of how many items are in a sequence.
//
// static const size_type CAPACITY = _____
// sequence::CAPACITY is the maximum number of items that a sequence can hold.
//
// CONSTRUCTOR for the sequence class:
// sequence( )
// Postcondition: The sequence has been initialized as an empty sequence.
//

// MODIFICATION MEMBER FUNCTIONS for the sequence class:
// void start( )
// Postcondition: The first item on the sequence becomes the current
// item(but if the sequence is empty, then there is no current item).
//
// void advance( )
// Precondition: is_item returns true.
// Postcondition: If the current item was already the last item in the
// sequence, then there is no longer any current item. Otherwise, the
// new current item is the item immediately after the original current item.
//
// void insert(const value_type& entry)
// Precondition: size( ) < CAPACITY.
// Postcondition: A new copy of entry has been inserted in the
// sequence in a sorted manner from smallest to largest. If no items in sequence,
// inserted in first position of sorted sequence.
//
// void remove_current( )
// Precondition: is_item returns true.
// Postcondition: The current item has been removed from the sequence,
// and the item after this (if there is one) is now the new current item.
// CONSTANT MEMBER FUNCTIONS for the sequence class: size_type size( ) const
// Postcondition: The return value is the number of items in the
// sequence.
//
// bool is_item( ) const
// Postcondition: A true return value indicates that there is a valid
// "current" item that may be retrieved by
// member function (listed below). A false
// there is no valid current item.
//
// value_type current( ) const
// Precondition: is_item( ) returns true.
// Postcondition: The item returned is the
// sequence.

// void remove_front();
//      Precondtion: isitem() returns true
//      Postcondition: The item at the front of the sequence has been removed from the sequence,
//      and the current item points at the front of the sequence.

//
// VALUE SEMANTICS for the sequence class:
// Assignments and the copy constructor may be used with sequence 
// objects.
#ifndef SORTED_SEQUENCE_H
#define SORTED_SEQUENCE_H
#include <cstdlib>

namespace coen70_lab3 {
    class sorted_sequence {
	public:
        // TYPEDEF and MEMBER CONSTANTS
        typedef double value_type;
        typedef std::size_t size_type;
        static const size_type CAPACITY = 50;
        // CONSTRUCTOR
        sorted_sequence();
        // MODIFICATION MEMBER FUNCTIONS
        void start();
        void end();
        void last(); //helper function to move the current_index to the end of the array. use if you want to
        void advance();
        void insert(const value_type& entry);
        void remove_current();
        void remove_front();
        // CONSTANT MEMBER FUNCTINOS
        size_type size() const;
        bool is_item() const;
        value_type current() const;
        size_type index() const { return current_index; }
        
        
    private:
        // PRIVATE DATA
        value_type data[CAPACITY];
        size_type used;
        size_type current_index;
    };
    
    sorted_sequence operator+(sorted_sequence& lhs, sorted_sequence& rhs);
    sorted_sequence operator+=(sorted_sequence& lhs, sorted_sequence& rhs);
    
}

#endif /*SORTED_SEQUENCE_H*/
