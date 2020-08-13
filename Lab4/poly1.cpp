// FILE: poly1.cpp
// CLASS IMPLEMENTED: polynomial (See poly1.h for documentation)
//

#include <cassert>
#include "poly1.h"
#include <cmath>
#include <climits>
using namespace std;

namespace coen70_lab4
{
	void polynomial::update_current_degree()
	{
		int highest_degree = 0;
		for (int i = 0; i <MAXIMUM_DEGREE; i++)
		{
			if (coef[i] != 0)
			{
				highest_degree = i;
			}
		}
		current_degree = highest_degree;
	}
	
	polynomial::polynomial(double c, unsigned int exponent)
	{
		assert (exponent <= MAXIMUM_DEGREE);
		for (int i = 0; i < MAXIMUM_DEGREE; i++)
		{
			if (i == exponent)
			{
				coef[i] = c;
			}
			else
			{
				coef[i] = 0.0;
			}
		}
		update_current_degree();
	}
	
	void polynomial:: assign_coef(double coefficient, unsigned int exponent)
	{
		assert (exponent <= MAXIMUM_DEGREE);
		coef[exponent] = coefficient;
		update_current_degree();
	}
	
	void polynomial::add_to_coef(double amount, unsigned int exponent)
	{
		assert (exponent <= MAXIMUM_DEGREE);
		coef[exponent] += amount;
		update_current_degree();
	}
	
	void polynomial::clear()
	{
		for (int i = 0; i < MAXIMUM_DEGREE; i++)
		{
			coef[i] = 0.0;
		}
		current_degree = 0;
	}
	
	polynomial polynomial::antiderivative() const
	{
		assert (current_degree < MAXIMUM_DEGREE);
		polynomial antiderivative;
		for (int i = 0; i <= current_degree; i++)
		{
			antiderivative.coef[i+1] = coef[i]/(i+1);
		}
		antiderivative.update_current_degree();
		return antiderivative;
	}
	
	double polynomial::coefficient(unsigned int exponent) const
	{
		if (exponent > MAXIMUM_DEGREE)
		{
			return 0;
		}
		else
		{
			return coef[exponent];
		}
	}
	
	double polynomial::definite_integral(double x0, double x1) const
	{
		polynomial integral;
		double sum = 0.0;
		integral = antiderivative();
		integral.update_current_degree();
		for (int i = 0; i <= integral.current_degree; i++)
		{
			sum += integral.coef[i]*std::pow(x1, i);
			sum -= integral.coef[i]*std::pow(x0, i);
		}
		return sum;
	}
	
	polynomial polynomial::derivative() const
	{
		polynomial derivative;
		for (int i = 0; i <= current_degree; i++)
		{
			derivative.coef[i] = coef[i+1]*(i+1);
		}
		derivative.coef[current_degree] = 0.0;
		derivative.update_current_degree();
		return derivative;
	}
	
	double polynomial::eval(double x) const
	{
		double sum = 0.0;
		for (int i = 0; i <= current_degree; i++)
		{
			sum += coef[i]*std::pow(x, i);
		}
		return sum;
	}
	
	bool polynomial::is_zero() const
	{
		return coef[current_degree] == 0;
	}
	
	unsigned int polynomial::next_term(unsigned int e) const
	{
		for (int i = e +1; i <= current_degree; i++)
		{
			if (coef[i] != 0)
			{
				return i;
			}
		}
		return 0;
	}
	
	unsigned int polynomial::previous_term(unsigned int e) const
	{
		for (int i = e - 1; i >= 0; i--)
		{
			if (coef[i] != 0)
			{
				return i;
			}
		}
		return UINT_MAX;
	}
	
	polynomial operator +(const polynomial& p1, const polynomial& p2)
	{
		polynomial sum;
		for (int i = 0; i <= polynomial::MAXIMUM_DEGREE; i++)
		{
			sum.add_to_coef(p1.coefficient(i), i);
			sum.add_to_coef(p2.coefficient(i), i);
		}
		return sum;
	}
	
	polynomial operator -(const polynomial& p1, const polynomial& p2)
	{
		polynomial dif;
		for (int i = 0; i <= polynomial::MAXIMUM_DEGREE; i++)
		{
			dif.add_to_coef(p1.coefficient(i) - p2.coefficient(i), i);
		}
		return dif;
	}
	
	polynomial operator *(const polynomial& p1, const polynomial& p2)
	{
		assert (p1.degree() + p2.degree() <= polynomial::MAXIMUM_DEGREE);
		polynomial prod;
		for (int i = 0; i<= p1.degree(); i++)
		{
			for (int j = 0; j <= p2.degree(); j++)
			{
				if (p1.coefficient(i) != 0 && p2.coefficient(j) != 0)
				{
					prod.add_to_coef(p1.coefficient(i) * p2.coefficient(j), i + j);
				}
			}
		}
		return prod;
	}
	
	std::ostream& operator <<(std::ostream& out, const polynomial& p)
	{
		bool isFirst = true;
        for (int i = p.degree(); i >= 0; i--) 
		{
            if (p.coefficient(i) != 0) 
			{
                if (isFirst) 
				{
                    if (i == 0) 
					{
                        out << p.coefficient(i);
                    } 
					else if (i == 1) 
					{
                        out << p.coefficient(i) << "x";
                    } 
					else 
					{
                        out << p.coefficient(i) << "x^" << i;
                    }
                    isFirst = false;
                } 
				else 
				{
                    if (i == 0) 
					{
                        if (p.coefficient(i) < 0) 
						{
                            out << " - " << p.coefficient(i)*-1;
                        } 
						else 
						{
                            out << " + " << p.coefficient(i);
                        }
                    } 
					else if (i == 1)
					{
                        if (p.coefficient(i) < 0) 
						{
                            out << " - " << p.coefficient(i)*-1 << "x";
                        } 
						else 
						{
                            out << " + " << p.coefficient(i) << "x";
                        }
                    } 
					else 
					{
                        if (p.coefficient(i) < 0) 
						{
                            out << " - " << p.coefficient(i)*-1 << "x^" << i;
                        } 
						else 
						{
                            out << " + " << p.coefficient(i) << "x^" << i;
                        }
                    }
                }
            }
        }
        
        return out;
    }
}








