#if !defined(VOIGHTFIT_H)
#define VOIGHTFIT_H

#include "/home/johnguti/FSRoot/FSFit/FSFitPrivate.h"

using namespace std;


class FSFitVOIGT : public FSFitFunction{
  public:
    FSFitVOIGT(TString n_fName, double n_xLow, double n_xHigh) :
      FSFitFunction(n_fName,n_xLow,n_xHigh){ 
      addParameter("A",10.0,"size");
      addParameter("s",10.0,"sigma");
      addParameter("M",10.0,"mass");
      addParameter("W",10.0,"width");
    }
    double fx (double x){
      double A = getParameterValue("A");
      double s = getParameterValue("s");
      double M = getParameterValue("M");
      double W = getParameterValue("W");
      return A*TMath::Voigt(x-M,s,W,4);
    }
    FSFitVOIGT* clone(){ return new FSFitVOIGT("",m_xLow,m_xHigh); }


};



#endif