#if !defined(BAHSTRINGS_H)
#define BAHSTRINGS_H
 #include "BAHUtilities.h"

/////////////////////////////////////////////////////////////
//   BAHStrings
//
//   Literally just made this because some strings are long...
//      Can also have title functions for long names variables
//////////////////////////////////////////////////////////////
// Section 1 : Functions to 'get Particle tags' [Basis for many function options]
// Section 2 : Quick String Functions
// Section 3 : Functions to 'get Variable'
// Section 1 : Functions to 'get Variable's title/tags'
// Section 4 : Functions to 'get bounds for variable'
//////////////////////////////////////////////////////////////
//======================================================
//                Particle titles/tags
//======================================================
//--------------------------------------------
// For making the tag that is used for the pdf name
// Ordered so that the harder to contain in checked first
TString getTagfromTeX(TString TexParticle, bool NeedCharge=0){
  if(TexParticle.Contains("gamma")){         return "ph";  }
  else if(TexParticle.Contains("pi^{0}")){   return "pi0"; }
  else if(TexParticle.Contains("K^{0}")){    return "K0";  }
  if(!NeedCharge){
    if(TexParticle.Contains("pi")){          return "pi";  }
    else if(TexParticle.Contains("K")){      return "K";   }
    else if(TexParticle.Contains("p")){      return "p";   }
    else if(TexParticle.Contains("mu")){     return "mu";  }
    else if(TexParticle.Contains("e")){      return "e";   }
  }
  if(NeedCharge){
    if(TexParticle.Contains("pi^{+}")){      return "pi+"; }
    else if(TexParticle.Contains("pi^{-}")){ return "pi-"; }
    else if(TexParticle.Contains("K^{+}")){  return "K+"; }
    else if(TexParticle.Contains("K^{-}")){  return "K-"; }
    else if(TexParticle.Contains("mu^{+}")){ return "mu+"; }
    else if(TexParticle.Contains("mu^{-}")){ return "mu-"; }
    else if(TexParticle.Contains("e^{+}")){  return "e+"; }
    else if(TexParticle.Contains("e^{-}")){  return "e-"; }
    else if(TexParticle.Contains("p")){      return "p+"; }
    else if(TexParticle.Contains("bar{p}")){ return "p-"; }
  }
  return "NO";
}
//--------------------------------------------
// For making the tag that is used for in the PID variable (FSTag for particles)
TString getFSTagfromTeX(TString TexParticle){  // Only used for Track criterias [from my knowledge so far]
  if(TexParticle.Contains("pi")){          return "Pi"; }
  else if(TexParticle.Contains("K")){      return "K";  }
  else if(TexParticle.Contains("p")){      return "P";  }
  else if(TexParticle.Contains("mu")){     return "Mu"; }
  else if(TexParticle.Contains("e")){      return "E";  }
  else{ return "NO";}
}
TString getTeXnoCC(TString TexParticle){  // Only used for Track criterias [from my knowledge so far]
  if(TexParticle.Contains("pi")){          return "#pi"; }
  else if(TexParticle.Contains("K")){      return "K";  }
  else if(TexParticle.Contains("p")){      return "p";  }
  else if(TexParticle.Contains("mu")){     return "#mu"; }
  else if(TexParticle.Contains("e")){      return "e";  }
  else{ return "NO";}
}
//////////////////////////////////////////////////////////////
//======================================================
//                Just useful FUNCTIONS
//======================================================
//--------------------------------------------
  // Since cuts are in vectors, can pass them to one string
  // with some || or && between each cut
TString CutsfromCutVec( vector<TString> CutVector, TString LogicConjunction){
  // Incase im passing an empty vector...
  if(CutVector.size()==0){ 
    SPACEstr("Shit... Bad Vector so using noCut");
    return "(21==21)";
  }
  TString outString = StrfromVec(CutVector,LogicConjunction);
  // surround output with parenthesis because probably gonna treat as a unit
  return "("+outString+")";
}
//--------------------------------------------
  // If getting cuts directly from the cut-pair vector, can get the vector to pass to the function above
vector<TString> reduceCutVecPair( vector<pair<TString,TString>> StrVec, bool GetCuts=true ){
  vector<TString> dummyVec;
  if(StrVec.size()>0){
    for (unsigned int i = 0; i < StrVec.size(); i++){
      if(GetCuts){ dummyVec.push_back(StrVec[i].second);}
      if(!GetCuts){dummyVec.push_back(StrVec[i].first);}
    }
  }
  return dummyVec;
}
//--------------------------------------------
// For erasing a specific pair based on either TString in pair
vector<pair<TString,TString>> eraseElementPairVec(bool OnlyFirst, vector<pair<TString,TString>> inputVector, bool secondary, TString eraseTarget){
  vector<TString> InputofInterest = reduceCutVecPair(inputVector,secondary);
  // Can uses above vec of interest as conditional checker
  for (int i = 0; i < inputVector.size(); i++){
    if( *(InputofInterest.begin()+i)==eraseTarget){  
        inputVector.erase(inputVector.begin()+i); 
      if(OnlyFirst){return inputVector;}
    }
  }
  return inputVector;
}
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
//======================================================
//                VARIABLE FUNCTIONS
//======================================================
// Setting this up to be consistent so the string checking doesn't mess up
TString getTkEemc(TString ParticleNumber){
  return "(TkEPP"+ParticleNumber+")*(MOMENTUM("+ParticleNumber+"))";
}
//--------------------------------------------
TString getProbVScut( bool emc, TString ParticleType1, TString ParticleType2, TString ParticleNumber){
  if(emc){
    return "(TkProbemc"+ParticleType1+"P"+ParticleNumber+">TkProbemc"+ParticleType2+"P"+ParticleNumber+")";
  }
  return "(TkProb"+ParticleType1+"P"+ParticleNumber+">TkProb"+ParticleType2+"P"+ParticleNumber+")";
}
//--------------------------------------------
TString getProbVS( bool emc, TString ParticleType1, TString ParticleType2, TString ParticleNumber){
  if(emc){
    return "(TkProbemc"+ParticleType1+"P"+ParticleNumber+"-TkProbemc"+ParticleType2+"P"+ParticleNumber+")";
  }
  return "(TkProb"+ParticleType1+"P"+ParticleNumber+"-TkProb"+ParticleType2+"P"+ParticleNumber+")";
}
//--------------------------------------------
//for options: true -> EMC,  false -> no EMC
TString getEProbR( bool emc, TString part){
  if(emc){
    return "(TkProbemcEP"+part+")/(TkProbemcEP"+part+"+TkProbemcPiP"+part+"+TkProbemcKP"+part+")";
  }
  return "(TkProbEP"+part+")/(TkProbEP"+part+"+TkProbPiP"+part+"+TkProbKP"+part+")";
}
//--------------------------------------------
TString getEProbR2( bool emc, TString part){
  if(emc){
    return "(TkProbemcEP"+part+")/(TkProbemcEP"+part+"+TkProbemcPiP"+part+")";
  }
  return "(TkProbEP"+part+")/(TkProbEP"+part+"+TkProbPiP"+part+")";
}
//--------------------------------------------
//--------------------------------------------
// Useful for the MDC chi profiles used, for options: 1->electron,  2->muon,  else->both
TString getMDCchi( TString part, int option){
  if(option==1){return "TkchiDedxEP"+part;}
  else if(option==2){ return "TkchiDedxMuP"+part;}
  else{return "TkchiDedxEP"+part+"+TkchiDedxMuP"+part;}
}
//--------------------------------------------
// Useful for the EMCExtras variable/cut
TString getEMCExtra(TString Set){
  if(Set=="gtm"||Set=="get"){
    return "(EMCEnergy-(TkEPP1*"+MOM+"(1)+TkEPP2*"+MOM+"(2)+ShEnergyP3))";
  }
  else if(Set=="gep"){
    return "(EMCEnergy-(TkEPP1*"+MOM+"(1)+ShEnergyP2+TkEPP3*"+MOM+"(3)))";
  }
  else if(Set=="gepp"){
    return "(EMCEnergy-(TkEPP1*"+MOM+"(1)+ShEnergyP2+TkEPP3*"+MOM+"(3)+ShEnergyP4a+ShEnergyP4b))";
  }
  if(Set=="gpp"||Set=="gkk"){
    return "(EMCEnergy-(ShEnergyP1+TkEPP2*"+MOM+"(2)+TkEPP3*"+MOM+"(3)))";
  }
  if(Set=="gPP"){
    return "(EMCEnergy-(TkEPP1*"+MOM+"(1)+TkEPP2*"+MOM+"(2)+ShEnergyP3))";
  }
  if(Set=="eepp"||Set=="mmpp"){
    return "(EMCEnergy-(TkEPP1*"+MOM+"(1)+TkEPP2*"+MOM+"(2)+ShEnergyP3a+ShEnergyP3b+ShEnergyP4a+ShEnergyP4b))";
  }
  if(Set=="etgpp"){
    return "(EMCEnergy-(ShEnergyP1a+ShEnergyP1b+ShEnergyP2+TkEPP3*"+MOM+"(3)+TkEPP4*"+MOM+"(4)))";
  }
  else return "(EMCEnergy+10)"; // Just a dumb input which should show empty histogram
}
//--------------------------------------------
TString getEnergySumEMC(TString Set){
  if(Set=="gtm"||Set=="get"){
    return "(TkEPP1*"+MOM+"(1)+TkEPP2*"+MOM+"(2)+ShEnergyP3)";
  }
  else if(Set=="gep"){
    return "(TkEPP1*"+MOM+"(1)+ShEnergyP2+TkEPP3*"+MOM+"(3))";
  }
  else if(Set=="gepp"){
    return "(TkEPP1*"+MOM+"(1)+ShEnergyP2+TkEPP3*"+MOM+"(3)+ShEnergyP4a+ShEnergyP4b)";
  }
  if(Set=="gpp"||Set=="gkk"){
    return "(ShEnergyP1+TkEPP2*"+MOM+"(2)+TkEPP3*"+MOM+"(3))";
  }
  if(Set=="gPP"){
    return "(TkEPP1*"+MOM+"(1)+TkEPP2*"+MOM+"(2)+ShEnergyP3)";
  }
  if(Set=="eepp"||Set=="mmpp"){
    return "(TkEPP1*"+MOM+"(1)+TkEPP2*"+MOM+"(2)+ShEnergyP3a+ShEnergyP3b+ShEnergyP4a+ShEnergyP4b)";
  }
  if(Set=="etgpp"){
    return "(ShEnergyP1a+ShEnergyP1b+ShEnergyP2+TkEPP3*"+MOM+"(3)+TkEPP4*"+MOM+"(4))";
  }
  else return "(EMCEnergy*2)"; // Just a dumb input which should show empty histogram
}
//--------------------------------------------
TString getEMCEnergyR(TString Set){
  return "("+getEnergySumEMC(Set)+"/EMCEnergy)";
}
//--------------------------------------------
TString getEMCEnergyRsqr(TString Set){
  TString output;
  output = "pow("+getEMCEnergyR(Set)+",2)";
  return output;
}
//--------------------------------------------
TString getZeroCut(TString Variable, bool GreaterThan){
  if(GreaterThan){ return " ("+Variable+">0) ";}
  return " ("+Variable+"<0) ";
}
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
//======================================================
//                Title/Label FUNCTIONS
//======================================================
  //////////////////////////////////////////////////////////////
  // Gets recoil mass titles based on set name and intermediate state of interest
TString RM_t(TString Set, TString IS){
  TString RMt;
  if(IS=="XcJ"||IS=="ChicJ"){
    if(Set=="gtm"||Set=="get"||Set=="gep"||Set=="gepp"||Set=="gpp"||Set=="gPP"||Set=="gkk"){ 
      RMt = ("Recoil Mass(#gamma)"); 
    }
  }
  else if(IS=="Jpsi"){
    if(Set=="eepp"){ RMt = ("Recoil Mass(#pi^{0},#pi^{0})"); }
    if(Set=="mmpp"){ RMt = ("Recoil Mass(#pi^{0},#pi^{0})"); }
  }
  else if(IS=="Tau"){
    if(Set=="gtm"){ RMt = ("Recoil Mass(#gamma,#mu)");}
    if(Set=="get"||Set=="gep"||Set=="gepp"){
      RMt = ("Recoil Mass(#gamma,e)");  
    }
  }
  else{
      RMt = ("Recoil Mass(#gamma)");  
  }
  return RMt;
}
//--------------------------------------------
// Gets mass titles based on set name and intermediate state of interest
TString Mass_t(TString Set, TString IS){
  TString Mass_title;
  if(IS=="XcJ"){
    if(Set=="gpp"){ Mass_title = ("Mass(#pi^{+},#pi^{-})"); }
    if(Set=="gPP"){ Mass_title = ("Mass(p,#bar{p})"); }
    if(Set=="gkk"){ Mass_title = ("Mass(K^{+},K^{-})"); }
  }
  else if(IS=="Jpsi"){
    if(Set=="eepp"){ Mass_title = ("Mass(e^{+},e^{-})"); }
    if(Set=="mmpp")Mass_title = ("Mass(e^{+},e^{-})"); 
  }
  else{
    if(Set=="etgpp")Mass_title = ("Mass(#eta,#gamma,#pi^{+},#pi^{-})"); 
  }
  return Mass_title;
}
//--------------------------------------------
TString getProbVS_t( bool emc, TString ParticleLabel1, TString ParticleLabel2){
  if(emc){
    return "[#it{P}'("+ ParticleLabel1+")-#it{P}'("+ ParticleLabel2+")]_{"+ParticleLabel1+"}";
  }
  return "[#it{P}("+ ParticleLabel1+")-#it{P}("+ ParticleLabel2+")]_{"+ParticleLabel1+"}";
}
//--------------------------------------------
// Gets electron probability ratio title/label based on some candidate
TString getEProbR_t( bool emc, TString Candidate){
  if(emc){
    return "#frac{#it{P}'(e)}{#it{P}'(e)+#it{P}'(#pi)+#it{P}'(K)} of "+Candidate;
  }
  return "#frac{#it{P}(e)}{#it{P}(e)+#it{P}(#pi)+#it{P}(K)} of "+Candidate;
}
TString getEProbR2_t( bool emc, TString Candidate){
  if(emc){
    return "#frac{#it{P}'(e)}{#it{P}'(e)+#it{P}'(#pi)} of "+Candidate;
  }
  return "#frac{#it{P}(e)}{#it{P}(e)+#it{P}(#pi)} of "+Candidate;
}
//--------------------------------------------
TString getEMCEnergyR_t(TString Set){
  TString output;
  if(Set=="gtm"||Set=="get"){
    output = "E^{EMC}_{#gamma}+E^{EMC}_{e}+E^{EMC}_{#mu}";
  }
  else if(Set=="gep"){
    output = "E^{EMC}_{#gamma}+E^{EMC}_{e}+E^{EMC}_{#pi}";
  }
  else if(Set=="gepp"){
    output = "E^{EMC}_{#gamma}+E^{EMC}_{e}+E^{EMC}_{#pi}+E^{EMC}_{#pi^{0}}";
  }
  else if(Set=="gpp"){
    output = "E^{EMC}_{#gamma}+E^{EMC}_{#pi^{+}}+E^{EMC}_{#pi^{-}}";  //1636 1639 1646 1648 1651 1652 1655 1658 1660 1670 1671 1680 
  }
  else if(Set=="gkk"){
    output = "E^{EMC}_{#gamma}+E^{EMC}_{K^{+}}+E^{EMC}_{K^{-}}";
  }
  else if(Set=="gPP"){
    output = "E^{EMC}_{#gamma}+E^{EMC}_{p}+E^{EMC}_{#bar{p}}";
  }
  else if(Set=="eepp"){
    output = "E^{EMC}_{#pi^{0}}+E^{EMC}_{#pi^{0}}+E^{EMC}_{e^{+}}+E^{EMC}_{e^{-}}";
  }
  else if(Set=="mmpp"){
    output = "E^{EMC}_{#pi^{0}}+E^{EMC}_{#pi^{0}}+E^{EMC}_{#mu^{+}}+E^{EMC}_{#mu^{-}}";
  }
  else if(Set=="etgpp"){
    output = "E^{EMC}_{#gamma}+E^{EMC}_{#eta}+E^{EMC}_{#pi^{+}}+E^{EMC}_{#pi^{-}}";
  }
  else{ return output = "Bad input: 2";}
  output = "("+output+")/(Total EMC Energy)";
  return output;
}
//--------------------------------------------
TString getEMCEnergyRsqr_t(TString Set){
  TString output;
  output = "["+getEMCEnergyR_t(Set)+"]^{2}";
  return output;
}
//======================================================
//                Bound FUNCTIONS
//======================================================
TString TkEp_Bds(TString TexParticle){
  if(TexParticle.Contains("e")){  return  "(100,0.6,1.2)"; }
  if(TexParticle.Contains("pi")){ return  "(100,-0.01,0.9)"; }
  if(TexParticle.Contains("K")){  return  "(100,-0.01,1.0)"; }
  else{ return  "(100,0.0,0.8)"; }
}
//--------------------------------------------
TString TkEemc_Bds(TString TexParticle){
  if(TexParticle.Contains("e")){  return  "(100,0.1,2.0)"; }
  if(TexParticle.Contains("pi")){  return  "(100,-0.1,2.0)"; }
  if(TexParticle.Contains("mu")){  return  "(100,-0.02,0.5)"; }
  if(TexParticle.Contains("p")){  return  "(100,-0.01,1.45)"; }
  if(TexParticle.Contains("K")){  return  "(100,-0.01,1.5)"; }
  else{ return  "(100,0.0,0.8)"; }
}
//--------------------------------------------
TString TkMOM_Bds(TString Set,TString TexParticle){
  if((Set=="gtm")&&(TexParticle.Contains("m"))){  return  "100,0.9,1.6"; }
  if(Set.Contains("e")&&(TexParticle.Contains("e"))){  return  "100,0.9,1.6"; }
  if(Set=="gPP"){  return  "100,1.2,1.8"; }
  if(Set=="gpp"){  return  "100,1.5,1.9"; }
  else{ return  "100,0.0,2.0"; }
}
//--------------------------------------------
TString TkMass_Bds(TString TexParticle){
  if(TexParticle.Contains("e")){  return  "(100,-0.05,0.2)"; }
  if(TexParticle.Contains("mu")){  return "(100,0.0,0.2)"; }
  if(TexParticle.Contains("pi")){  return "(100,0.0,0.2)"; }
  else{ return  "(100,0.0,1.0)"; }
}
//--------------------------------------------
TString Mass_Bds( TString IS){
  if(IS=="Jpsi"){return "(100,2.8,3.3)"; }
  if(IS=="XcJ"){ return "(100,3.3,3.6)"; }
  else{ return "(100,2.8,3.6)"; }
}
//--------------------------------------------
#endif