// FILE: sequence.cpp
// CLASS IMPLEMENTED: sequence (see sequence.h for documentation)
// 

#include <cassert>
#include "sequence.h"
using namespace std;

namespace coen70_lab3
{	
	const sequence::size_type sequence::CAPACITY;
	
	void sequence::start()
	{
		assert (size() > 0);
		current_index = 0;
	}
	
	void sequence::end()
	{
		assert (size() > 0);
		current_index = used - 1;
	}
	
	void sequence::advance()
	{
		assert (is_item() == true);
		if (current_index == used - 1)
		{
			current_index = -1;
		}
		else
		{
			current_index ++;
		}
	}
	
	void sequence::insert(const value_type& entry)
	{
		assert (size() < CAPACITY);
		if (current_index > -1)
		{
			for (int i = used; i > current_index;i--)
			{
				data[i] = data[i-1];
			}
			data[current_index] = entry;
		}
		else
		{
			current_index = 0;
			for (int i = used; i > current_index;i--)
			{
				data[i] = data[i-1];
			}
			data[current_index] = entry;
		}
		used++;
	}
	
	void sequence::insert_front(const value_type& entry)
	{
		assert (size() < CAPACITY);
		if (used > 0)
		{
			for (int i = used; i > 0; i--)
			{
				data[i] = data[i-1];
			}
		}
		data[0] = entry;
		current_index = 0;
		used++;
	}
	
	void sequence::attach(const value_type& entry)
	{
		assert (size() < CAPACITY);
		if (current_index > -1)
		{
			for (int i = used; i > current_index + 1; i--)
			{
				data[i] = data[i-1];
			}
			data[current_index + 1] = entry;
			current_index++;
		}
		else
		{
			data[used] = entry;
			current_index = used;
		}
		used++;
		
	}
	
	void sequence::attach_back(const value_type& entry)
	{
		assert (size() < CAPACITY);
		data[used] = entry;
		current_index = used;
		used++;
	}
	
	void sequence::remove_current()
	{
		assert (is_item() == true);
		if (current_index = used - 1)
		{
			current_index = -1;	
		}
		else
		{
			for (int i = current_index; i < used - 1; i++)
			{
				data[i] = data[i + 1];
			}
		}
		used--;
	}
	
	void sequence::remove_front()
	{
		assert ( is_item() == true);
		for (int i = 0; i < used - 1; i--)
		{
			data[i] = data[i+1];
		}
		used--;
		if (used = 0)
		{
			current_index = -1;
		}
		else
		{
			current_index = 0;
		}
	}
	
	sequence::size_type sequence::size() const 
	{
		return used;
	}
	
	bool sequence::is_item() const
	{
		return current_index > -1;
	}
	
	sequence::value_type sequence::current() const 
	{
		assert (is_item() == true);
		return data[current_index];
	}
	
	sequence operator+(sequence& lhs, sequence& rhs)
	{
		assert (lhs.size() + rhs.size() <= sequence::CAPACITY);
		sequence answer;
		lhs.start();
		while (lhs.is_item())
		{
			answer.attach(lhs.current());
			lhs.advance();
		}
		rhs.start();
		while (rhs.is_item())
		{
			answer.attach(rhs.current());
			rhs.advance();
		}
		return answer;
	}

	sequence operator+=(sequence& lhs, sequence& rhs)
	{
		assert (lhs.size() + rhs.size() <= sequence::CAPACITY);
		while (rhs.is_item())
		{
			lhs.attach(rhs.current());
			rhs.advance();
		}
		return lhs;
	}
	

}