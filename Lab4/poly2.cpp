// FILE: poly2.cpp
// CLASS IMPLEMENTED: polynomial (see poly2.h for documentation)

#include <iostream>
#include <iomanip>
#include <cassert>
#include "poly2.h"
#include <cmath>
#include <climits>
#include <algorithm>

using namespace std;

namespace coen70_lab4_2 {
    
    void polynomial::update_current_degree() 
	{
        current_degree = 0;
        for (int i = coef_size - 1; coef_size != 0 && i >= 0; i--) 
		{
            if (coef[i] != 0.0) 
			{
                current_degree = i;
                break;
            }
        }
    }
	
    void polynomial::increaseArray(unsigned int exponent) 
	{
        if (exponent >= coef_size) 
		{
            
            double *temp = coef;
            coef_size = exponent + 1;
            coef = new double[coef_size];
            assert(coef != NULL);
            for (int i = 0; i < coef_size; i++) 
			{
                coef[i] = 0;
            }
            if (temp != NULL) 
			{
                for (size_t i = 0; i <= current_degree; i++) 
				{
                    coef[i] = temp[i];
                }
                delete[] temp;
            }
            current_degree = exponent;
        }
    }	

	polynomial::polynomial(double c, unsigned int exponent)
	{
        coef_size = 0;
        current_degree = 0;
        coef = NULL;
        increaseArray(exponent);
        coef[exponent] = c;
    }
    
    polynomial::~polynomial() 
	{
        delete[] coef;
    }	
	
    polynomial::polynomial(const polynomial& other) 
	{
        coef_size = other.coef_size;
        coef = new double[coef_size];
        assert(coef != NULL);
        for (int i = 0; i < coef_size; i++) 
		{
            coef[i] = 0;
        }
        for (int i = 0; i < coef_size; i++) 
		{
            coef[i] = other.coef[i];
        }
        
        current_degree = other.current_degree;
    }
    
	void polynomial::assign_coef(double coefficient, unsigned int exponent) {
        increaseArray(exponent);
        coef[exponent] = coefficient;
        update_current_degree();
    }

    void polynomial::add_to_coef(double amount, unsigned int exponent) 
	//adds to the coef and assigns it
	{
        assign_coef(coefficient(exponent) + amount, exponent);
    }

	void polynomial::clear() 
	// makes the coefficients all 0
	{
        for (size_t i = 0; i <= current_degree; i++) 
		{
            coef[i] = 0.0;
        }
        current_degree = 0;
    }
    
    polynomial& polynomial::operator =(const polynomial& other) 
	{
        if (this != &other) 
		{
            clear();
            increaseArray(other.current_degree);
            copy(other.coef, other.coef+other.current_degree+1, coef);
        }
        return *this;
    }

    polynomial polynomial::antiderivative() const 
    // Calculates the anti-derivative and returns the polynomial
	{
        polynomial p(0.0, current_degree+1);
        for (size_t i = 1; i <= this->degree()+1; i++) 
		{
            p.assign_coef(this->coefficient(i-1) / i , i);
        }
        return p;
    }

	double polynomial::coefficient(unsigned int exponent) const 
	{
        if (exponent > current_degree)
		// return 0.0 if exponent larger than current_degree
		{
            return 0.0;
		}
        return coef[exponent];
    }

    double polynomial::definite_integral(double x0, double x1) const 
	{
        polynomial ant = this->antiderivative();
        return ant.eval(x1) - ant.eval(x0);
    }

	polynomial polynomial::derivative() const 
	//this calculates derivative and returns the polynomial
	{
        polynomial p;
        for (size_t i = 0; i < this->degree(); i++) 
		{
            p.assign_coef( this->coefficient(i+1) * (i+1), i);
        }
        return p;
    }

	double polynomial::eval(double x) const 
	{
        double sum = 0;
        for (size_t i = 0; i <= current_degree; i++) 
		{
            double cur_coef = coefficient(i);
            if (cur_coef != 0) 
			{
                sum += cur_coef*pow(x, i);
            }
        }
        return sum;
    }

    bool polynomial::is_zero() const 
	{
        if (current_degree == 0 && coef[0] == 0.0)
		{
            return true;
		}
        else
		{
            return false;
		}
    }

	unsigned int polynomial::next_term(unsigned int e) const 
	//looks for next term
	{
        for (size_t i = e+1; i <= current_degree; i++) 
		{
            if (coef[i] != 0)
			{
                return i;
			}
        }
        return 0;
    }

	unsigned int polynomial::previous_term(unsigned int e) const 
	//looks for previous term
	{
        for (int i = e-1; i >= 0; i--) 
		{
            if (coef[i] != 0)
			{
                return i;
			}
        }      
        return UINT_MAX;
    }

    polynomial operator +(const polynomial& p1, const polynomial& p2) 
	//operator definition to add polynomials together and return added polynomial
	{
        polynomial p3 = p1;       
        for (size_t i = 0; i <= p2.degree(); i++) 
		{
            p3.add_to_coef(p2.coefficient(i), i);
        }
        return p3;
    }

    polynomial operator -(const polynomial& p1, const polynomial& p2) 
	//operator definition to subtract polynomials and return subtracted polynomial
	{
        polynomial p3 = p1;     
        for (size_t i = 0; i <= p2.degree(); i++) 
		{
            p3.add_to_coef(-p2.coefficient(i), i);
        }
        return p3;
    }

    polynomial operator *(const polynomial& p1, const polynomial& p2) 
	//operator definition to multiply polynomials and return product polynomial
	{
        polynomial p3(0.0, p1.degree() + p2.degree());
        for (size_t i = 0; i <= p1.degree(); i++) 
		{
            for (size_t j = 0; j <= p2.degree(); j++) 
			{
                p3.add_to_coef(p1.coefficient(i) * p2.coefficient(j), i+j);
            }
        }
        return p3;
    }

    std::ostream& operator <<(std::ostream& out, const polynomial& p) 
	{
        // Save settings for output
        int pres = out.precision();
        out << std::fixed;
        out << std::setprecision(1);
        if (p.is_zero())
		{
            out << 0.00;
		}
        else 
		{
            bool firstPrint = true;
            for (int i = p.degree(); i >= 0; i--) 
			{
                double oCoef = p.coefficient(i);
                if (oCoef != 0.0) 
				{
                    if (!firstPrint) 
					{
                        out << ((oCoef < 0) ? " - " : " + ");
                    }
                    out << ((firstPrint) ? oCoef : abs(oCoef));
                    if (i > 0)
                    {
                        out << "x";
                        if (i > 1)
						{
                            out << "^" << i;
						}
                    }
                    if (firstPrint)
					{
                        firstPrint = false;
					}
                }
            }
        }
        // reset settings
        out << setprecision(pres);
        return out;
    }
}
