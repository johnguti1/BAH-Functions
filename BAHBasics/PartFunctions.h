#ifndef PARTFUNCTIONS_H
#define PARTFUNCTIONS_H

using namespace std;
  // vscode-fold=1

 //==============================================================================================
 //======================================== Important Variables =================================
TString pmagS(TString Part){
  TString p = ("sqrt(  pow(PxP"+Part+",2.0)+pow(PyP"+Part+",2.0)+pow(PzP"+Part+",2.0) )");
  return p;
}
TString ptS(TString Part){
  TString p = ("sqrt(  pow(PxP"+Part+",2.0)+pow(PyP"+Part+",2.0) )");
  return p;
}
TString EnS(TString Part, TString mass){
  TString E = ("sqrt(  pow("+mass+",2) + pow("+pmagS(Part)+",2) )");
  return E;
}
TString CosS(TString Part1, TString Part2){   // SHOULD CHECK DIFFERENCE IN THIS VS TKCOS
  TString coS = ("( (PxP"+Part1+"*PxP"+Part2+")+(PyP"+Part1+"*PyP"+Part2+")+(PzP"+Part1+"*PzP"+Part2+") )/("+pmagS(Part1)+"*"+pmagS(Part2)+")");
  return coS;
}
TString InvM_2(TString Part1, TString M1, TString Part2, TString M2){
  TString INV=("sqrt( pow("+EnS(Part1,M1)+"+"+EnS(Part2,M2)+",2)-pow(PxP"+Part1+"+PxP"+Part2+",2)-pow(PyP"+Part1+"+PyP"+Part2+",2) -pow(PzP"+Part1+"+PzP"+Part2+",2) )");
  return INV;
}
void SetMacro(){
FSTree::defineMacro("RM3", 3, "(sqrt(pow((EnP[I]-EnP[J]-EnP[M]),2)-"
                                        "pow((PxP[I]-PxP[J]-PxP[M]),2)-"
                                        "pow((PyP[I]-PyP[J]-PyP[M]),2)-"
                                        "pow((PzP[I]-PzP[J]-PzP[M]),2)))" );

FSTree::defineMacro("PMiss", 4, "(sqrt(pow((PxP[I]-PxP[J]-PxP[M]-PxP[N]),2)+"
                                      "pow((PyP[I]-PyP[J]-PyP[M]-PxP[N]),2)+"
                                      "pow((PzP[I]-PzP[J]-PzP[M]-PxP[N]),2)))" );

FSTree::defineMacro("Pvis3", 3, "(sqrt(pow((PxP[I]+PxP[J]+PxP[M]),2)+"
                                      "pow((PyP[I]+PyP[J]+PyP[M]),2)+"
                                      "pow((PzP[I]+PzP[J]+PzP[M]),2)))" );
}

TString MCvRmom_3(TString Part1,TString Part2){
  TString INV="sqrt(pow(MCDecayParticlePxP"+Part1+"-PxP"+Part2+",2)";
  INV   = INV    +"+pow(MCDecayParticlePyP"+Part1+"-PyP"+Part2+",2)";
  INV   = INV    +"+pow(MCDecayParticlePzP"+Part1+"-PzP"+Part2+",2))";
  return INV;
}
TString pt2S(TString Part1, TString Part2){ // Transverse momentum magnitude of two particles  (z of beam is BeamE*cos(0.011)~ 0.99*BeamE so x,y are transverse)
  TString Ptrans = ("sqrt( pow( PxP"+Part1+"+PxP"+Part2+",2)  +  pow( PyP"+Part1+"+PyP"+Part2+",2)  )");
  return Ptrans;
}
TString p3magS(TString Part1, TString Part2, TString Part3){ // Momentum Magnitude of three particles
  TString Ptrans = ("sqrt(pow( PxP"+Part1+"+PxP"+Part2+"+PxP"+Part3+",2)"  
                       +"+pow( PyP"+Part1+"+PyP"+Part2+"+PyP"+Part3+",2)"    
                       +"+pow( PzP"+Part1+"+PzP"+Part2+"+PzP"+Part3+",2)  )");
  return Ptrans;
}
TString emmS(TString Part1, TString Part2){ // Maximal Missing Energy of two charged tracks   
  TString Emm = ("(3.686 - "+pmagS(Part1)+"-"+pmagS(Part2)+")");
  return Emm;
}
TString PTEM(TString Part1, TString Part2){
  TString ptem = (  pt2S(Part1,Part2)+"/"+emmS(Part1,Part2)  );
  return ptem;
}
TString ACO(TString Part1, TString Part2){  // Angle between the transverse momentums  (x,y)  z is beam line
    TString aco = ( "( acos(  ((PxP"+Part1+"*PxP"+Part2+")+(PyP"+Part1+"*PyP"+Part2+"))  /  ("+pmagS(Part1)+"*"+pmagS(Part2)+")   )*180/3.14159265 )");
    return aco;
}
//================================= Important Variables titles to plot ===============================
TString CosS_t(TString Part1, TString Part2){
  TString coSt = ("Cos(#theta_{"+Part1+","+Part2+"})");
  return coSt;
}
// CAN WRITE THIS FUNCTION INTO SET TSTRING IN ISFSASSIGNMENT SO NO WORRY ABOUT REDEFINITIONS 2vs3 particles
TString InvM_2t(TString Set, TString Part1, TString Part2){
  TString invT;
  if(Set == "gpp"){ invT = ("Mass(#pi^{+}_{"+Part1+"},#pi^{-}_{"+Part2+"})"); }
  if(Set == "gkk"){ invT = ("Mass(K^{+}_{"+Part1+"},K^{-}_{"+Part2+"})"); }
  if(Set == "gPP"){ invT = ("Mass(p^{+}_{"+Part1+"},p^{-}_{"+Part2+"})"); }

  if(Set=="gem"){ invT = ("Mass(e_{"+Part1+"},#mu_{"+Part2+"})"); }
  //if((Set=="ge-m+")||(Set=="gem")){ invT = ("Mass(e^{-}_{"+Part1+"},#mu^{+}_{"+Part2+"})"); }
  return invT;
}
//=====================================================================================================
//===================================== getCut Functions ==============================================
//=====================================================================================================
  TString getcutMASS(bool cut, TString p1, TString p2, TString massmin, TString massmax){
    TString tempstr;
    if((cut==false)||(massmin=="(1==1)")||(massmax=="(1==1)")){ return tempstr = noCut;}
    if(cut==true){ 
      tempstr= "(("+massmin+"< MASS("+p1+","+p2+"))&&( MASS("+p1+","+p2+")<"+massmax+"))";
    }
    return tempstr;
  }
  TString getcutTKVERT(bool cut,  TString Set){
    TString tempstr;
    if(cut==false){ return tempstr = noCut;}
    if(cut==true){ 
      if((Set=="gpp")||(Set=="gkk")){
              tempstr="( abs(TkRVtxP2)<1.0 && abs(TkRVtxP3)<1.0 && abs(TkZVtxP2)<10.0 && abs(TkZVtxP3)<10.0 )";}
        else{ tempstr="( abs(TkRVtxP1)<1.0 && abs(TkRVtxP2)<1.0 && abs(TkZVtxP1)<10.0 && abs(TkZVtxP2)<10.0 )";}
    }
    return tempstr;
  }
  TString getcutTKCOS(bool cut,  TString Set, TString cutmax){
    TString tempstr;
    if((cut==false)||(cutmax=="(1==1)")){ return tempstr = noCut;}
    if(cut==true){ 
      if((Set=="gpp")||(Set=="gkk")){
              tempstr="( abs(TkCosThetaP2)<"+cutmax+" && abs(TkCosThetaP3)< "+cutmax+")";}
        else{ tempstr="( abs(TkCosThetaP1)<"+cutmax+" && abs(TkCosThetaP2)< "+cutmax+")";}
    }
    return tempstr;
  }
  TString getcutDANG(bool cut,  TString Ph, TString cutmin){
    TString tempstr;
    if((cut==false)||(cutmin=="(1==1)")){ return tempstr = noCut;}
    if(cut==true){ tempstr="( "+cutmin+" < ShDangP"+Ph+" )";}
    return tempstr;
  }
TString getcutRM(bool cut,  TString Ph, TString cutmin, TString cutmax){
  TString tempstr;
  if((cut==false)||(cutmin=="(1==1)")||(cutmax=="(1==1)")){ return tempstr = noCut;}
  if(cut==true){ tempstr="(("+cutmin+"<MASS(BES3CMS,-"+Ph+"))&&(MASS(BES3CMS,-"+Ph+")<"+cutmax+"))";}
  return tempstr;
}
TString getcutRM3(bool cut,  TString Ph, TString Tk, TString cutmin, TString cutmax){
  TString tempstr;
  if((cut==false)||(cutmin=="(1==1)")||(cutmax=="(1==1)")){ return tempstr = noCut;}
  if(cut==true){ tempstr="(("+cutmin+"<MASS(BES3CMS,-"+Ph+",-"+Tk+"))&&(MASS(BES3CMS,-"+Ph+",-"+Tk+")<"+cutmax+"))";}
  return tempstr;
}
TString getcutRM3max(bool cut,  TString p1, TString p2, TString cutmax){
  TString tempstr;
  if((cut==false)||(cutmax=="(1==1)")){ return tempstr = noCut;}
  if(cut==true){ tempstr="(MASS(BES3CMS,-"+p1+",-"+p2+")<"+cutmax+")";}
  return tempstr;
}
//=====================================================================================================
  TString getcutMucMIN(bool cut, TString Part, TString cutmin){
    TString tempstr;
    if((cut==false)||(cutmin=="(1==1)")){ return tempstr = noCut;}
    if(cut==true){ tempstr="(( " +cutmin+ " < TkMucDepthP"+Part+")  )";}
    return tempstr;
  }
  TString getcutMucMAX(bool cut, TString Part, TString cutmax){
    TString tempstr;
    if((cut==false)||(cutmax=="(1==1)")){ return tempstr = noCut;}
    if(cut==true){ tempstr="((TkMucDepthP"+Part+" < " +cutmax+ " )  )";}
    return tempstr;
  }
//=====================================================================================================
  TString getcutEp(bool cut, TString Part, TString cutmin, TString cutmax){
    TString tempstr;
    if((cut==false)||(cutmin=="(1==1)")||(cutmax=="(1==1)")){ return tempstr = noCut;}
    if(cut==true){
      tempstr="((" +cutmin+"< TkEPP"+Part+" )&&( TkEPP"+Part+" < " +cutmax+ " )  )";
    }
    return tempstr;
  }
  TString getcutEcal(bool cut, TString Part, TString cutmin, TString cutmax){
  TString tempstr;
    if((cut==false)||(cutmin=="(1==1)")||(cutmax=="(1==1)")){ return tempstr = noCut;}
    if(cut==true){
      tempstr="( ("+cutmin+"<(TkEPP"+Part+")*("+MOM+"("+Part+")) )&&( (TkEPP"+Part+")*("+MOM+"("+Part+")) < " +cutmax+ " )  )";
    }
    return tempstr;
}  
TString getcutEcalmax(bool cut, TString Part,TString cutmax){
  TString tempstr;
    if((cut==false)||(cutmax=="(1==1)")){ return tempstr = noCut;}
    if(cut==true){
      tempstr="(  ((TkEPP"+Part+")*("+MOM+"("+Part+"))) < " +cutmax+ " )  ";
    }
    return tempstr;
}
//======================================= Set==FS Specific PID cuts for Probability ===================
  TString getcutProb(bool cut, TString Set, TString Part, TString cutmin){   // NEED TO DEFINE FOR e mu and mu e
    TString tempstr;
    if((cut==false)||(cutmin=="(1==1)")){ return tempstr = noCut;}
    if(cut==true){
      if(Set=="gpp"){
        tempstr="((" +cutmin+ "< TkProbPiP"+Part+" ))";
      }
      if(Set=="gPP"){
        tempstr="((" +cutmin+ "< TkProbPP"+Part+" )&&( TkProbMuP"+Part+" < TkProbPP"+Part+" ))";
      }
      if(Set=="gkk"){
        tempstr="((" +cutmin+ "< TkProbKP"+Part+" )&&( TkProbMuP"+Part+" < TkProbKP"+Part+" )&&( TkProbPiP"+Part+" < TkProbKP"+Part+" ))";
      }
      if((Set=="ge+m-")||(Set=="ge-m+")||(Set=="gt+m-")||(Set=="gt-m+")||(Set=="ge+t-")||(Set=="ge-t+")||(Set=="get")||(Set=="gtm")){ // electron is always P1 w/ muon P2 in these modes
        if(Part=="1"){ tempstr="(" +cutmin+ 
        "< (TkProbEP1)/(TkProbEP1+TkProbPiP1+TkProbKP1) )"; }
        if(Part=="2"){ tempstr="((" +cutmin+ "< TkProbMuP2))";}//( TkProbEP2 < TkProbMuP2 )&&( TkProbPiP2 < TkProbMuP2 ))"; }
      }
    }
    return tempstr;
  }
  TString getcutProbNGL(bool cut, TString Part, TString ProbGreater, TString ProbLess ){
    TString tempstr;
    if(cut==false){ return tempstr = noCut;}
    tempstr = "( TkProb"+ProbLess+"P"+Part+" < TkProb"+ProbGreater+"P"+Part+" )";
    return tempstr;
  }  
  TString getcutProbMin(bool cut, TString Prob, TString Part, TString min){
    TString tempstr;
    if(cut==false){ return tempstr = noCut;}
    tempstr = "( "+min+" < TkProb"+Prob+"P"+Part+" )";
    return tempstr;
  }
  TString getcutChi2(bool cut, TString cutmax){
    TString tempstr;
    if((cut==false)||(cutmax=="(1==1)")){ return tempstr = noCut;}
    if(cut==true){ tempstr ="( Chi2DOF < " +cutmax+" )";}
    return tempstr;
  }
  TString getcutNShow(bool cut, TString cutmax){
    TString tempstr;
    if((cut==false)||(cutmax=="(1==1)")){ return tempstr = "( 1 <= NShowers )";}
    if(cut==true){ tempstr="(( 1 <= NShowers )&&( NShowers < "+cutmax+" ))";;}
    return tempstr;
  }

#endif