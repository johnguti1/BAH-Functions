#if !defined(BAHPHYSICS_H)
#define BAHPHYSICS_H

 #include "BAHUtilities.h"


  // ********************************************************
  // Converts the particle-name string to a pdgID, Just the inverse of FSPhysics::pdgName.
  // ********************************************************
static int pdgNameToID(TString name){
  int id;
                // Proper input ,  janky-inputs...
  if      (name=="psi(2S)"    ||name=="psi2S"              )   id = FSPhysics::kpdgPsi2S     ;
  else if (name=="gamma"                                   )   id = FSPhysics::kpdgGamma     ;
  else if (name=="gamma_FSR"  ||name=="gammaFSR"           )   id = FSPhysics::kpdgFSRGamma  ;
  else if (name=="h_c"        ||name=="hc"                 )   id = FSPhysics::kpdgHc        ;
  else if (name=="chi_c0"     ||name=="chic0" ||name=="Xc0")   id = FSPhysics::kpdgChic0     ;
  else if (name=="chi_c1"     ||name=="chic1" ||name=="Xc1")   id = FSPhysics::kpdgChic1     ;
  else if (name=="chi_c2"     ||name=="chic2" ||name=="Xc2")   id = FSPhysics::kpdgChic2     ;
  else if (name=="J/psi"      ||name=="Jpsi"               )   id = FSPhysics::kpdgJpsi      ;
  else if (name=="eta_c"      ||name=="etac"               )   id = FSPhysics::kpdgEtac      ;
  else if (name=="phi"                                  )   id = FSPhysics::kpdgPhi       ;
  else if (name=="omega"                                )   id = FSPhysics::kpdgOmega     ;
  else if (name=="pi0"                                  )   id = FSPhysics::kpdgPi0       ;
  else if (name=="pi+"                                  )   id = FSPhysics::kpdgPip       ;
  else if (name=="pi-"                                  )   id = FSPhysics::kpdgPim       ;
  else if (name=="rho0"        ||name=="rho"            )   id = FSPhysics::kpdgRho0      ;
  else if (name=="rho+"                                 )   id = FSPhysics::kpdgRhop      ;
  else if (name=="rho-"                                 )   id = FSPhysics::kpdgRhom      ;
  else if (name=="eta'"                                 )   id = FSPhysics::kpdgEtaprime  ;
  else if (name=="eta"                                  )   id = FSPhysics::kpdgEta       ;
  else if (name=="Ks"                                   )   id = FSPhysics::kpdgKs        ;
  else if (name=="Kl"           ||name=="KL"            )   id = FSPhysics::kpdgKl        ;
  else if (name=="K+"                                   )   id = FSPhysics::kpdgKp        ;
  else if (name=="K-"                                   )   id = FSPhysics::kpdgKm        ;
  else if (name=="p+"           ||name=="p"             )   id = FSPhysics::kpdgPp        ;
  else if (name=="p-"                                   )   id = FSPhysics::kpdgPm        ;
  else if (name=="n"                                    )   id = FSPhysics::kpdgN         ;
  else if (name=="nbar"                                 )   id = FSPhysics::kpdgAntiN     ;
  else if (name=="Delta0"                               )   id = FSPhysics::kpdgDelta0    ;
  else if (name=="Delta+"                               )   id = FSPhysics::kpdgDeltap    ;
  else if (name=="Delta++"                              )   id = FSPhysics::kpdgDeltapp   ;
  else if (name=="e+"                                   )   id = FSPhysics::kpdgEp        ;
  else if (name=="e-"           ||name=="e"             )   id = FSPhysics::kpdgEm        ;
  else if (name=="mu+"                                  )   id = FSPhysics::kpdgMup       ;
  else if (name=="mu-"          ||name=="mu"            )   id = FSPhysics::kpdgMum       ;
  else if (name=="tau+"                                 )   id = FSPhysics::kpdgTaup      ;
  else if (name=="tau-"         ||name=="tau"           )   id = FSPhysics::kpdgTaum      ;
  else if (name=="nuE"          ||name=="nu"            )   id = FSPhysics::kpdgNuE       ;
  else if (name=="nuM"                                  )   id = FSPhysics::kpdgNuMu      ;
  else if (name=="nuT"                                  )   id = FSPhysics::kpdgNuTau     ;
  else if (name=="nuAE"                                 )   id = FSPhysics::kpdgAntiNuE   ;
  else if (name=="nuAM"                                 )   id = FSPhysics::kpdgAntiNuMu  ;
  else if (name=="nuAT"                                 )   id = FSPhysics::kpdgAntiNuTau ;
  else if (name=="f0(600)"                              )   id = FSPhysics::kpdgF0600     ;
  else if (name=="K0"                                   )   id = FSPhysics::kpdgK0        ;
  else if (name=="AK0"                                  )   id = FSPhysics::kpdgAntiK0    ;
  else if (name=="K*+"                                  )   id = FSPhysics::kpdgKstarp    ;
  else if (name=="K*-"                                  )   id = FSPhysics::kpdgKstarm    ;
  else if (name=="K*0"                                  )   id = FSPhysics::kpdgKstar0    ;
  else if (name=="K*0bar"                               )   id = FSPhysics::kpdgAntiKstar0;
  else if (name=="Lambda"                               )   id = FSPhysics::kpdgLambda    ;
  else if (name=="ALambda"                              )   id = FSPhysics::kpdgALambda   ;
  else if (name=="D+"                                   )   id = FSPhysics::kpdgDp        ;
  else if (name=="D-"                                   )   id = FSPhysics::kpdgDm        ;
  else if (name=="D0"                                   )   id = FSPhysics::kpdgD0        ;
  else if (name=="D0bar"                                )   id = FSPhysics::kpdgDA        ; 
  else if (name=="D*+"                                  )   id = FSPhysics::kpdgDstarp    ;
  else if (name=="D*-"                                  )   id = FSPhysics::kpdgDstarm    ;
  else if (name=="D*0"                                  )   id = FSPhysics::kpdgDstar0    ;
  else if (name=="D*0bar"                               )   id = FSPhysics::kpdgDstarA    ;
  // ---------------- Additional niche particles ----------------------------
  else if (name=="rho(2150)^{0}"  ||name=="rho0(2150)"  )   id = -9040113    ;
  else if (name=="K_{2}^{*}(1430)^{0}"                  )   id = 315         ;
  else{
    cout << "== Particle "+name+" ==" << endl;
    cout << "===== Not in List ======" << endl;
    id = 1 ;  // d-quark as dummy
  }
  return id;
}



  // ********************************************************
  // Converts the particle-name string to the pdg mass or whatever Ryan has for the mass (Pretty close to pdg value)
  // ********************************************************
static double NameToMass(TString name){
  double mass;
                // Proper input ,  janky-input
  if      (name=="psi(2S)"    ||name=="psi2S"              )   mass = FSPhysics::XMpsi2S    ;  // 3.686093
  else if (name=="h_c"        ||name=="hc"                 )   mass = FSPhysics::XMhc       ;  // 3.52593
  else if (name=="chi_c0"     ||name=="chic0" ||name=="Xc0")   mass = FSPhysics::XMchic0    ;  // 3.41476
  else if (name=="chi_c1"     ||name=="chic1" ||name=="Xc1")   mass = FSPhysics::XMchic1    ;  // 3.51066
  else if (name=="chi_c2"     ||name=="chic2" ||name=="Xc2")   mass = FSPhysics::XMchic2    ;  // 3.55620
  else if (name=="J/psi"      ||name=="Jpsi"               )   mass = FSPhysics::XMJpsi     ;  // 3.096916
  else if (name=="eta_c"      ||name=="etac"               )   mass = FSPhysics::XMetac     ;  // 2.9804
  else if (name=="rho0"       ||name=="rho"                )   mass = FSPhysics::XMrho      ;  // 0.7755  [Assuming same masses]
  else if (name=="rho+"                                    )   mass = FSPhysics::XMrho      ;  // 0.7755  [Assuming same masses]
  else if (name=="rho-"                                    )   mass = FSPhysics::XMrho      ;  // 0.7755  [Assuming same masses]
  else if (name=="omega"                                   )   mass = FSPhysics::XMomega    ;  // 0.78265
  else if (name=="phi"                                     )   mass = FSPhysics::XMphi      ;  // 1.01946
  else if (name=="K+"                                      )   mass = FSPhysics::XMK        ;  // 0.493677
  else if (name=="K-"                                      )   mass = FSPhysics::XMK        ;  // 0.493677
  else if (name=="p+"           ||name=="p"                )   mass = FSPhysics::XMp        ;  // 0.938272
  else if (name=="p-"                                      )   mass = FSPhysics::XMp        ;  // 0.938272
  else if (name=="n"                                       )   mass = FSPhysics::XMn        ;  // 0.939565
  else if (name=="pi0"                                     )   mass = FSPhysics::XMpi0      ;  // 0.134977
  else if (name=="pi+"          ||name=="pi"               )   mass = FSPhysics::XMpi       ;  // 0.13957
  else if (name=="pi-"                                     )   mass = FSPhysics::XMpi       ;  // 0.13957
  else if (name=="e+"                                      )   mass = FSPhysics::XMe        ;  // 0.000511
  else if (name=="e-"           ||name=="e"                )   mass = FSPhysics::XMe        ;  // 0.000511
  else if (name=="mu+"                                     )   mass = FSPhysics::XMmu       ;  // 0.105658
  else if (name=="mu-"          ||name=="mu"               )   mass = FSPhysics::XMmu       ;  // 0.105658
  else if (name=="gamma"                                   )   mass = 0.0    ;
  else if (name=="gamma_FSR"    ||name=="gammaFSR"         )   mass = 0.0    ;
  else if (name=="tau+"                                    )   mass = 1.77686      ;  // pdg value
  else if (name=="tau-"         ||name=="tau" ||name=="Tau")   mass = 1.77686      ;  // pdg value
  else{
    cout << "== Particle "+name+" ==" << endl;
    cout << "===== Not in List ======" << endl;
    mass = 0.0 ;  // d-quark as dummy
  }
  return mass;
}

/////////////////////////////
//   BESIII Masses from pdt.table 
/////////////////////////////
//  NAME        pdgID  MASS
//---------------------------
//   J/psi        443  3.0969  
//   psi(2S)   100443  3.68610  
//   psi(3770)  30443  3.7737   
//   eta_c        441  2.9839   
//   eta_c(2S)  20441  3.6375   
//   h_c        10443  3.52538  
//   chi_c0     10441  3.41471  
//   chi_c1     20443  3.51067  
//   chi_c2       445  3.55617  
//   e-            11  0.000510999
//   e+           -11  0.000510999  
//   mu-           13  0.1056584   
//   mu+          -13  0.1056584   
//   tau-          15  1.7770      
//   tau+         -15  1.7770
//   pi0          111  0.1349766 
//   pi+          211  0.139570  
//   pi-         -211  0.139570  
//   rho0         113  0.77549   
//   rho+         213  0.77549   
//   rho-        -213  0.77549   
//   omega        223  0.78265   
//   phi          333  1.01946   
//   eta          221  0.547853  
//   K+           321  0.49368   
//   K-          -321  0.49368   
//   K0           311  0.4976    
//   anti-K0     -311  0.4976    
//   K_S0         310  0.4976    
//   K_L0         130  0.4976    






static TString NameToMassStr(TString name){
  return FSString::double2TString(NameToMass(name),7);
}


  // ********************************************************
  // Convert TString of many particles to a sorted vector<int> of pdgIDs
  // "J/psi pi+ pi- gamma" -> {22,211,-211,443}
  // Unless specificed with nuAT [for anti-tau-neutrino], nu -> electron-neutrino
  // ********************************************************
vector<int> ParticlesToIDs(TString particles = "J/psi psi2s psi2S psi2S gamma"){
  vector<int> pdgIDvector;
  vector<TString> NameVector = FSString::parseTString(particles);
  for( int i = 0 ; i < NameVector.size() ; i++ ){
    pdgIDvector.push_back(pdgNameToID(NameVector[i]));
    if(pdgIDvector[i]==1){
      cout << " Particle [ "+NameVector[i]+" ] in string is not in list" << endl;
    }
  }
  sort(pdgIDvector.begin(), pdgIDvector.end(),[](const int & a, const int & b){ return a < b; });
  return pdgIDvector;
}

TString getMCExtrasNum(TString FSDecayString){
  vector<TString> ExtrasVector;
  int MCExtraNums = 0;
  if(FSDecayString.Contains("(")){ ExtrasVector = FSString::parseTString(FSString::captureParentheses(FSDecayString,0)); }
  else{ ExtrasVector = FSString::parseTString(FSDecayString); }
  for(  int i = 0 ; i < ExtrasVector.size() ; i++ ){
    cout << ExtrasVector[i] << endl;
         if (ExtrasVector[i].Contains("nu") ) MCExtraNums += 1000;
    else if (ExtrasVector[i].Contains("K")  ) MCExtraNums += 100;
    else if (ExtrasVector[i]=="nbar"        ) MCExtraNums += 10;
    else if (ExtrasVector[i]=="n"           ) MCExtraNums += 1;
  }
  return FSString::int2TString(MCExtraNums);
}





  // ********************************************************
  // Simple QED Cross-Section Calcuator for charged leptons 
  //   calculation is done based on MeV for convenience 
  // ********************************************************

double CS_diTauSum(){
  double W     = 3.686;   // CMS - energy in GeV 
  double alpha = 1/137;   // Fine structure constant (NOT 1/128)
  double beta  = sqrt(1-(2*NameToMass("Tau"))/(pow(W,2)));

  double prefacNumerator = 4*TMath::Pi()*pow(alpha,2)*beta*(3-pow(beta,2));
  double prefactor2 = (beta*(3-pow(beta,2))/2);
  double prefactor3 = (beta*(3-pow(beta,2))/2);
  return 1.0;
}


double lepCS(double energy, int pdgIDLeptons){
  double outputNum;
  double LeptonMass;
  if(abs(pdgIDLeptons)==FSPhysics::kpdgTaum){ 
    LeptonMass = 1776.86; 
    if(energy<3.56){ return 0.0; }  // Think the threshold is around this CMS-energy
  }
  if(abs(pdgIDLeptons)==FSPhysics::kpdgMum ){ LeptonMass =  105.66; }
  if(abs(pdgIDLeptons)==FSPhysics::kpdgEm  ){ LeptonMass =   0.511; }
  return LeptonMass;
}

  // ********************************************************
  // Simple Cross-Section getter for a 
  //    limited Number of "final-states"
  // ********************************************************

double eeCS(TString Energy, vector<int> pdgIDvector){ 
  double outputCS;
  THINLINE();
  cout << " Energy [MeV] :  " << Energy <<  endl;
  if(pdgIDvector.size()>1){
    cout << " pdgID [1] :  " << pdgIDvector[0] <<  endl;
    cout << " pdgID [2] :  " << pdgIDvector[1] <<  endl;
    outputCS = lepCS(FSString::TString2double(Energy),pdgIDvector[0]);
  }
  else{
    outputCS = 5.0;
  }
  return outputCS;
}
double eeCS(TString Energy, TString particles){ 
  vector<int> pdgIDvector = ParticlesToIDs(particles);
  return eeCS(Energy,pdgIDvector);
}


double eeDiTauCs(){
  return 4.35; // Total ee -> tt 
}







  // Assuming FSRoot is pre-loaded

// ***************************************************
//  HELICITY, GOTTFRIED-JACKSON, AND PRODUCTION ANGLES
// ***************************************************
//
//  Starting with either of these processes:
//            e+(D) e-(Q) --> J/psi(S);  J/psi(S) --> rho0(R) pi0(C);  rho0(R) --> pi+(A) pi-(B)
//            gamma(D) p(Q) --> CM(S);  CM(S) --> phi(R) p'(C);  phi(R) --> K+(A) K-(B)  
//    (2) D --> Q + S;  S --> R + C;  R --> A + B
//          example:
//            chi_c1(D) --> gamma(Q) J/psi(S);  J/psi(S) --> rho0(R) pi0(C);  rho0(R) --> pi+(A) pi-(B)
// ***************************************************
//    calculate the helicity or Gottfried-Jackson angles for particle A or the
//    production angle for particle R.
// ***************************************************
//  Procecure for the production angle of R:
//    * First boost all four-vectors to the S rest frame, where R and C are back-to-back [pR = -pC]
//        and D and Q are either (1) back-to-back [pD = -pQ] or (2) parallel [pD = pQ].
//    * Rotate all four-vectors so pD is along the z-axis.  
//    * Return the cosine of the polar angle of pR (prodcostheta). 


//    (2) D --> Q + S;  S --> R + C;  R --> A + B   [Doesn't make sense to use]
//            psi(2S)[D] --> gamma(Q)  chi_{cJ}(S) ;   chi_{cJ}(S)  --> pi+(R) pi-(C)    Known:  D , Q , R , C  ,Can set B=0 to get Q=A
        

//    (1) D + Q --> S;  S --> R + C;  R --> A + B
//            gamma(D) p(Q) --> CM(S);  CM(S) --> phi(R) p'(C);  phi(R) --> K+(A) K-(B)  
//    * First boost all four-vectors to the S rest frame, where R and C are back-to-back [pR = -pC]
//        and D and Q are either (1) back-to-back [pD = -pQ] or (2) parallel [pD = pQ].



//    (1)   D + Q    -->    S;         S        -->   R    +   C;          R    -->   A   +  B
//       e+(D) e-(Q)--> psi(2S)[S]; psi(2S)[S] --> chi_{cJ}  gamma;   chi_{cJ}  --> pi+(A) pi-(B)
//  Procedure for the Gottried-Jackson angles of A:
//    * First boost all four-vectors to the R rest frame, where A and B are back-to-back [pA = -pB]
//        and S and C are parallel [pS = pC].
//    * Return the cosine of the angle between the boosted AB, AC or CB

double
gjDecayCosAB(double PxPA, double PyPA, double PzPA, double EnPA,
                   double PxPB, double PyPB, double PzPB, double EnPB,
                   double PxPC, double PyPC, double PzPC, double EnPC){
  TLorentzVector PA(PxPA,PyPA,PzPA,EnPA);
  TLorentzVector PB(PxPB,PyPB,PzPB,EnPB);
  TLorentzVector PC(PxPC,PyPC,PzPC,EnPC);
  TLorentzVector PR = PA + PB;
    // boost all needed four-vectors to the R rest frame
  PA.Boost(-1.0*PR.BoostVector());
  PB.Boost(-1.0*PR.BoostVector());
  PC.Boost(-1.0*PR.BoostVector());
    //
  double DotProd   = PA.Px()*PB.Px() + PA.Py()*PB.Py() + PA.Pz()*PB.Pz();
  double Magnitude1 = sqrt( pow(PA.Px(),2) + pow(PA.Py(),2) + pow(PA.Pz(),2) );             
  double Magnitude2 = sqrt( pow(PB.Px(),2) + pow(PB.Py(),2) + pow(PB.Pz(),2) );    
    // returning the Angle between the boosted A B
  return DotProd/(Magnitude1*Magnitude2);
}

  // ********************************************************

double
gjDecayCosAC(double PxPA, double PyPA, double PzPA, double EnPA,
                   double PxPB, double PyPB, double PzPB, double EnPB,
                   double PxPC, double PyPC, double PzPC, double EnPC){
  TLorentzVector PA(PxPA,PyPA,PzPA,EnPA);
  TLorentzVector PB(PxPB,PyPB,PzPB,EnPB);
  TLorentzVector PC(PxPC,PyPC,PzPC,EnPC);
  TLorentzVector PR = PA + PB;
    // boost all needed four-vectors to the R rest frame
  PA.Boost(-1.0*PR.BoostVector());
  PB.Boost(-1.0*PR.BoostVector());
  PC.Boost(-1.0*PR.BoostVector());
    // Defining Part needed for cos
  double DotProd   = PA.Px()*PC.Px() + PA.Py()*PC.Py() + PA.Pz()*PC.Pz();
  double Magnitude1 = sqrt( pow(PA.Px(),2) + pow(PA.Py(),2) + pow(PA.Pz(),2) );             
  double Magnitude2 = sqrt( pow(PC.Px(),2) + pow(PC.Py(),2) + pow(PC.Pz(),2) );    
    // returning the Angle between the boosted A B
  return DotProd/(Magnitude1*Magnitude2);
}

  // ********************************************************

double
gjDecayCosBC(double PxPA, double PyPA, double PzPA, double EnPA,
                   double PxPB, double PyPB, double PzPB, double EnPB,
                   double PxPC, double PyPC, double PzPC, double EnPC){
  TLorentzVector PA(PxPA,PyPA,PzPA,EnPA);
  TLorentzVector PB(PxPB,PyPB,PzPB,EnPB);
  TLorentzVector PC(PxPC,PyPC,PzPC,EnPC);
  TLorentzVector PR = PA + PB;
    // boost all needed four-vectors to the R rest frame
  PA.Boost(-1.0*PR.BoostVector());
  PB.Boost(-1.0*PR.BoostVector());
  PC.Boost(-1.0*PR.BoostVector());
    // Defining Part needed for cos
  double DotProd   = PB.Px()*PC.Px() + PB.Py()*PC.Py() + PB.Pz()*PC.Pz();
  double Magnitude1 = sqrt( pow(PB.Px(),2) + pow(PB.Py(),2) + pow(PB.Pz(),2) );             
  double Magnitude2 = sqrt( pow(PC.Px(),2) + pow(PC.Py(),2) + pow(PC.Pz(),2) );    
    // returning the Angle between the boosted A B
  return DotProd/(Magnitude1*Magnitude2);
}


void
MakeNewDefinitions(){
    FSTree::defineMacro("GJCosAB", 3, "gjDecayCosAB("
                                  "PxP[I],PyP[I],PzP[I],EnP[I],"
                                  "PxP[J],PyP[J],PzP[J],EnP[J],"
                                  "PxP[M],PyP[M],PzP[M],EnP[M])");
    FSTree::defineMacro("GJCosBC", 3, "gjDecayCosBC("
                                  "PxP[I],PyP[I],PzP[I],EnP[I],"
                                  "PxP[J],PyP[J],PzP[J],EnP[J],"
                                  "PxP[M],PyP[M],PzP[M],EnP[M])");
    FSTree::defineMacro("GJCosAC", 3, "gjDecayCosAC("
                                  "PxP[I],PyP[I],PzP[I],EnP[I],"
                                  "PxP[J],PyP[J],PzP[J],EnP[J],"
                                  "PxP[M],PyP[M],PzP[M],EnP[M])");
}











#endif