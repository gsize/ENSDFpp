#include "HalfLifeEstimator.h"

HalfLifeEstimator::HalfLifeEstimator()
{

}


double HalfLifeEstimator::estimateHalfLife(double QValueInMeV, unsigned short int A, unsigned short int Z)
{
  //cout << "ehl:" << QValueInMeV << " " << A << " " << " " << Z << " " << endl;
  double MassInMeV = ONEU*HEMASS;
  double MassInKg =  HEMASS*ONEUKG;
  double separation = 1.25*(pow((double)4,(double)1/3)+pow((double)(A-4),(double)1/3));
  //cout << "separation:" << separation << endl;
  double barrierHeight = 2*(Z-2)*1.44/separation;
  //cout << "mass:" << MassInMeV << endl;
  //cout << "brh:" << barrierHeight << endl;
  double dropDistance = barrierHeight/QValueInMeV;
  //double barrierWidth = dropDistance - separation;
  //cout << MassInMeV << endl;
  double velocity = sqrt(2 * QValueInMeV * pow(SPEEDOFLIGHT,2) / MassInMeV);
  //cout << "velo:" << velocity << endl;
  double frequency = velocity / (2 * separation * 1E-15);
  //cout << "freq:" << frequency << endl;
  double x = QValueInMeV / barrierHeight;
  //cout << "x:" << x << endl;
  //cout << "massinkg:" << MassInKg << endl;
  double G = sqrt(2*MassInKg/(pow(HBAR,2)*(QValueInMeV*MEVTOJ)))*2*(Z-2)*KKONST*pow(ELEMENTARYCHARGE,2)*(acos(sqrt(x))-sqrt(x*(1-x)));
  //cout << "G:" << G << endl;
  double P = exp(-2*G);
  //cout << "P:" << P << endl;
  double l = frequency*P;
  //cout << "l:" << l << endl;
  double Thalf=log(2)/l;
  //cout << "Thalf:" << Thalf << endl;
  return Thalf;
}
