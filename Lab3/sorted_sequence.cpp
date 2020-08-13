// FILE: sorted_sequence.cpp
// CLASS IMPLEMENTED: sequence (see sorted_sequence.h for documentation)
// 

#include <cassert>
#include "sorted_sequence.h"
using namespace std;

namespace coen70_lab3
{	
	const sorted_sequence::size_type sorted_sequence::CAPACITY;
	
	void sorted_sequence::start()
	{
		assert (size() > 0);
		current_index = 0;
	}
	
	void sorted_sequence::end()
	{
		assert (size() > 0);
		current_index = used - 1;
	}
	
	void sorted_sequence::advance()
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
	
	void sorted_sequence::insert(const value_type& entry)
	{
		assert (size() < CAPACITY);
		if (used == 0)
		{
			data[0]=entry;
			used++;
			return;
		}
		int i;
		for (i=used-1;i>=0;i--)
		{
			if (entry<data[i])
			{
				i--;
			}
			else
			{
				for (int d=used;d>i+1;d--)
				{
					data[d]=data[d-1];
				}
				data[i+1]=entry;
			}
		}
		used++;
		current_index=i+1;
	}
	
	void sorted_sequence::remove_current()
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
	
	void sorted_sequence::remove_front()
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
	
	sorted_sequence::size_type sorted_sequence::size() const 
	{
		return used;
	}
	
	bool sorted_sequence::is_item() const
	{
		return current_index > -1;
	}
	
	sorted_sequence::value_type sorted_sequence::current() const 
	{
		assert (is_item() == true);
		return data[current_index];
	}

	sorted_sequence operator+(sorted_sequence& lhs, sorted_sequence& rhs)
	{
		assert (lhs.size() + rhs.size() <= sorted_sequence::CAPACITY);
		sorted_sequence answer;
		lhs.start();
		while (lhs.is_item())
		{
			answer.insert(lhs.current());
			lhs.advance();
		}
		rhs.start();
		while (rhs.is_item())
		{
			answer.insert(rhs.current());
			rhs.advance();
		}
		return answer;
	}

	sorted_sequence operator+=(sorted_sequence& lhs, sorted_sequence& rhs)
	{
		assert (lhs.size() + rhs.size() <= sorted_sequence::CAPACITY);
		while (rhs.is_item())
		{
			lhs.insert(rhs.current());
			rhs.advance();
		}
		return lhs;
	}
	
	

}