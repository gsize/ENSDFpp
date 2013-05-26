/**\file DoubleMath.h
   \author Rikard Lundmark
   \brief Contains important function(s) to compare double numbers.
 */

#ifndef MATH_H
#define MATH_H //!<Inclusion guard
#include <math.h>
#endif

#ifndef DOUBLEMATH_H
#define DOUBLEMATH_H //!<Inclusion guard.

inline bool doubleEquality(double d1, //!<Number to compare with d2.
			   double d2, //!<Number to compare with d1.
			   double eps = 1E-9 //!<Tolerance.
			   ) //!<Compares if two double numbers d1 and d2 has a relative difference smaller than a small number eps. 
{
  if((d1+d2)!=0)
    return fabs(d1-d2)/(fabs(d1+d2))<=eps;
  else
    return (d1-d2)==0;
}

#endif
