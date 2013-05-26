/**\file HalfLifeEstimator.h
   \author Rikard Lundmark
   \brief Header file for the HalfLifeEstimator class.
*/
/**\file HalfLifeEstimator.cpp
   \author Rikard Lundmark
   \brief Source file for the HalfLifeEstimator class.
*/

#include <math.h>
#include <iostream>
using namespace std;

#ifndef ELECTRONMASSINMEV
#define ELECTRONMASSINMEV 510.998903 //!<Electron mass in MeV
#endif

#ifndef ONEU
#define ONEU 931.494 //!<One u.
#endif

#ifndef MEVTOJ
#define MEVTOJ 1.602177E-13 //!<Conversion unit for MeV to J
#endif

#ifndef HEMASS
#define HEMASS 4.00260325415 //!<Helium mass in u.
#endif

#ifndef ONEUKG
#define ONEUKG 1.660539E-27 //!<One u in kg.
#endif

#ifndef SPEEDOFLIGHT
#define SPEEDOFLIGHT 299792458 //!<Speed of light in vacuum.
#endif

#ifndef HBAR
#define HBAR 1.05457148E-34 //!<Planck constant.
#endif

#ifndef KKONST
#define KKONST 8.98755179E9 //!<Constant in Coulomb's law
#endif

#ifndef ELEMENTARYCHARGE
#define ELEMENTARYCHARGE 1.60217646E-19 //!<Elementary charge.
#endif

#ifndef HALFLIFEESTIMATOR_H
#define HALFLIFEESTIMATOR_H //!<Inclusion guard.
/**Estimates the half life for alpha decay using Geiger Nutall.
   \author Rikard Lundmark
 */
class HalfLifeEstimator{
 public:
  HalfLifeEstimator(); //!<Constructor.
  double estimateHalfLife(double QValueInMeV //!<QValue in MeV
			  , unsigned short int A //!<Atomic mass
			  , unsigned short int Z //!<Atomic number (charge)
			  ); //!<Estimates the half life, returns a value in seconds. Estimation through alpha decay, of course.
 private:
};
#endif
