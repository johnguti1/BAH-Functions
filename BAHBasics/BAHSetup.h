#if !defined(BAHSETUP_H)
#define BAHSETUP_H

 #include "BAHDecays.h"
 #include "BAHCuts.h"
 #include "BAHStrings.h"
 #include "FileHelper.h"

//---------------------------------
//---------------------------------
// To check Decay and Cut Info:   printAllInfo(TString Set)
//
// To quickly check cuts applied/passed through BAHSetup
//  use  """"""check(TString Set, fit? = true)""""""
//-------------=======-------------
//---------------------------------


//========================================================================
// Since I don't wanna overcomplicate the process, 
// forcing all particle specific cuts to be grouped together. 
// sucks but needed... Makes sense for [P,K,Pi,Mu,E] plots of Prob e/p and other stuff...
TString addCut(TString InitialCut, TString CutAdding){
  if(!BAHCuts::checkCut(InitialCut)){ return CutAdding; }
  return InitialCut+FSAND+CutAdding;
}

//========================================================================
// Since I'm dumb and might mess up looping/automation, 
//   setting up global situation 
//========================================================================
// Here are the global inputs for drawing on histograms 
    // MIGHT JUST ERASE ALL THESE GLOBAL VECTOR-PAIRS AND JUST USE THE FUNCTION
  //=========================================
/* #region Defining Bounds for Histograms */
  //=========================================
  // pair Mass bounds ( just in case )
  pair<TString,TString> minmax_Tau;   
  pair<TString,TString> minmax_Chic0 , minmax_Chic1 ,minmax_Chic2;  
  // Mass bounds for drawing on histograms
  vector<pair<TString,TString>> vecBd_ChicJ;
  vector<pair<TString,TString>> vecBd_Tau;
  vector<pair<TString,TString>> vecBd_Jpsi;
    // Direct Mass reconstructions [Not recoil mass]
  vector<pair<TString,TString>> vecBd_MChicJ;
  vector<pair<TString,TString>> vecBd_MJpsi;
  vector<pair<TString,TString>> vecBd_RMg;
  vector<pair<TString,TString>> vecBd_RhoMassDiff;
  vector<pair<TString,TString>> vecBd_RhoMass;
  // Base Track Bounds
  vector<pair<TString,TString>> vecBd_TkRV;
  vector<pair<TString,TString>> vecBd_TkZV;
  vector<pair<TString,TString>> vecBd_TkCos;
  // Set-based Bounds
  vector<pair<TString,TString>> vecBd_VChi2;
  vector<pair<TString,TString>> vecBd_MMChiDOF;
  vector<pair<TString,TString>> vecBd_Chi2DOF;
  ////////////////////////////
  vector<pair<TString,TString>> vecBd_NTracks;
  vector<pair<TString,TString>> vecBd_NShowers;
  vector<pair<TString,TString>> vecBd_NPi0s;
  vector<pair<TString,TString>> vecBd_MissingMass2;
  vector<pair<TString,TString>> vecBd_EMCExtra;
  vector<pair<TString,TString>> vecBd_VisMass;
  vector<pair<TString,TString>> vecBd_COSpmVg;
  vector<pair<TString,TString>> vecBd_COSgVe;
  vector<pair<TString,TString>> vecBd_COSgVmu;
  ////////////////////////////
  vector<pair<TString,TString>> vecBd_ShDang;
  vector<pair<TString,TString>> vecBd_LogShPi0Pull;
  ////////////////////////////
  vector<pair<TString,TString>> vecBd_pi0_ShDang;
  ////////////////////////////
  vector<pair<TString,TString>> vecBd_TkEMCProbR_e;
  vector<pair<TString,TString>> vecBd_TkEMCProb_e;
  vector<pair<TString,TString>> vecBd_TkEP_e;
  vector<pair<TString,TString>> vecBd_TkCos_e;
  vector<pair<TString,TString>> vecBd_TkMUC_e;
  vector<pair<TString,TString>> vecBd_MOM_e;
  ////////////////////////////
  vector<pair<TString,TString>> vecBd_TkCos_mu;
  vector<pair<TString,TString>> vecBd_TkEP_mu;
  vector<pair<TString,TString>> vecBd_TkEemc_mu;
  vector<pair<TString,TString>> vecBd_TkEMCProbMuvE;
  vector<pair<TString,TString>> vecBd_TkEMCProbMuvK;
  vector<pair<TString,TString>> vecBd_TkEMCProb_mu;
  vector<pair<TString,TString>> vecBd_TkMUC_mu;
  vector<pair<TString,TString>> vecBd_MOM_mu;
  ////////////////////////////
  vector<pair<TString,TString>> vecBd_TkEP_pi;
  vector<pair<TString,TString>> vecBd_TkEMCProb_pi;
  vector<pair<TString,TString>> vecBd_TkEMCProbPivK;
  vector<pair<TString,TString>> vecBd_TkProbPivE;
  vector<pair<TString,TString>> vecBd_TkProbPivK;
  vector<pair<TString,TString>> vecBd_TkProbPivP;
  vector<pair<TString,TString>> vecBd_TkCos_pi;
  vector<pair<TString,TString>> vecBd_TkMUC_pi;
  ////////////////////////////
  vector<pair<TString,TString>> vecBd_TkCos_p;
  vector<pair<TString,TString>> vecBd_TkProbP;
  vector<pair<TString,TString>> vecBd_TkProbPvPi;
  vector<pair<TString,TString>> vecBd_TkProbPvK;
  vector<pair<TString,TString>> vecBd_TkMUC_p;
  ////////////////////////////
  vector<pair<TString,TString>> vecBd_TkProbK;
  vector<pair<TString,TString>> vecBd_TkProbKvPi;
  vector<pair<TString,TString>> vecBd_MOM_KK;
  vector<pair<TString,TString>> vecBd_MOM_K;
  ////////////////////////////
  vector<pair<TString,TString>> vecBd_Emiss;
  vector<pair<TString,TString>> vecBd_Pmiss;
  vector<pair<TString,TString>> vecBd_EPmiss;


  void ClearMinMax(){
    ////////////////////////////
    vecBd_ChicJ.clear();
    vecBd_Tau.clear();
    vecBd_Jpsi.clear();
    // Direct Mass reconstructions [Not recoil mass]
    vecBd_MChicJ.clear();
    vecBd_MJpsi.clear();
    vecBd_RMg.clear();
    vecBd_RhoMassDiff.clear();
    vecBd_RhoMass.clear();
    // Base Track Bounds
    vecBd_TkRV.clear();
    vecBd_TkZV.clear();
    vecBd_TkCos.clear();
    // Set-based Bounds
    vecBd_VChi2.clear();
    vecBd_MMChiDOF.clear();
    vecBd_Chi2DOF.clear();
    ////////////////////////////
    vecBd_NTracks.clear();
    vecBd_NShowers.clear();
    vecBd_NPi0s.clear();
    vecBd_MissingMass2.clear();
    vecBd_EMCExtra.clear();
    vecBd_VisMass.clear();
    vecBd_COSpmVg.clear();
    vecBd_COSgVe.clear();
    vecBd_COSgVmu.clear();
    ////////////////////////////
    vecBd_ShDang.clear();
    vecBd_LogShPi0Pull.clear();
    ////////////////////////////
    vecBd_TkEMCProbR_e.clear();
    vecBd_TkEMCProb_e.clear();
    vecBd_TkEP_e.clear();
    vecBd_TkCos_e.clear();
    vecBd_TkMUC_e.clear();
    vecBd_MOM_e.clear();
    ////////////////////////////
    vecBd_TkCos_mu.clear();
    vecBd_TkEP_mu.clear();
    vecBd_TkEemc_mu.clear();
    vecBd_TkEMCProbMuvE.clear();
    vecBd_TkEMCProbMuvK.clear();
    vecBd_TkEMCProb_mu.clear();
    vecBd_TkMUC_mu.clear();
    vecBd_MOM_mu.clear();
    ////////////////////////////
    vecBd_TkEP_pi.clear();
    vecBd_TkEMCProb_pi.clear();
    vecBd_TkEMCProbPivK.clear();
    vecBd_TkProbPivE.clear();
    vecBd_TkProbPivK.clear();
    vecBd_TkProbPivP.clear();
    vecBd_TkCos_pi.clear();
    vecBd_TkMUC_pi.clear();
    ////////////////////////////
    vecBd_TkCos_p.clear();
    vecBd_TkProbP.clear();
    vecBd_TkProbPvPi.clear();
    vecBd_TkProbPvK.clear();
    vecBd_TkMUC_p.clear();
    ////////////////////////////
    vecBd_TkProbK.clear();
    vecBd_TkProbKvPi.clear();
    vecBd_MOM_KK.clear();
    vecBd_MOM_K.clear();
    ////////////////////////////
    vecBd_Emiss.clear();
    vecBd_Pmiss.clear();
    vecBd_EPmiss.clear();
    ////////////////////////////
  }

/* #endregion */

  // Defining the minmax of variable for easy/consistent drawing on histograms
  // Consistent because they are taken from BAHCuts info
  // IF GONNA PLOT VARIABLE, JUST ADD HERE
void defineMinMaxVecs(BAHDecays DecayInfo, BAHCuts CutInfo, int CutVersion = 0){
  TString Set= DecayInfo.getSet();
  TString IS= DecayInfo.getIS();
  if(IS=="XcJ"){ // Since mainly using pairs, setup as pairs
    minmax_Chic0 = BAHCuts::getMassBound(CutVersion,Set,"Xc0");
    if(Set!="gpp"&&Set!="gkk"){minmax_Chic1 = BAHCuts::getMassBound(CutVersion,Set,"Xc1");}
    minmax_Chic2 = BAHCuts::getMassBound(CutVersion,Set,"Xc2");
     // Using Pairs to define the lines vector<pairs> used for drawing lines
    vecBd_ChicJ.push_back(minmax_Chic0);
    if(Set!="gpp"&&Set!="gkk"){vecBd_ChicJ.push_back(minmax_Chic1);}
    vecBd_ChicJ.push_back(minmax_Chic2);
    vecBd_MChicJ.push_back(BAHCuts::getMassBound(CutVersion,Set,"MassXcJ") );
  }
  if(IS=="Jpsi"){ // Since mainly using pairs, setup as pairs
    vecBd_Jpsi.push_back(BAHCuts::getMassBound(CutVersion,Set,"Jpsi"));
    vecBd_MJpsi.push_back(BAHCuts::getMassBound(CutVersion,Set,"MassJpsi") );
  }
  if(IS=="NOTHING"){ // Since mainly using pairs, setup as pairs
    vecBd_RMg.push_back(BAHCuts::getMassBound(CutVersion,Set,""));
  }
  ////////////////////////////
  // Tracks bounds
  vecBd_TkRV.push_back(   BAHCuts::getMinMaxBounds(Set,CutVersion,"TkRVtx") );
  vecBd_TkZV.push_back(   BAHCuts::getMinMaxBounds(Set,CutVersion,"TkZVtx") );
  vecBd_TkCos.push_back(  BAHCuts::getMinMaxBounds(Set,CutVersion,"TkCosTheta") );
  ////////////////////////////
  // Set-dependant bounds
  if(Set=="gtm"||Set=="get"||Set=="gep"||Set=="gepp"){
    minmax_Tau =BAHCuts::getMassBound(CutVersion,Set,"Tau"); 
    vecBd_Tau.push_back(minmax_Tau);
  }
  vecBd_VChi2.push_back(    BAHCuts::getMinMaxBounds(Set,CutVersion,"VChi2") );
  vecBd_Chi2DOF.push_back(   BAHCuts::getMinMaxBounds(Set,CutVersion,"Chi2DOF") );
  ////////////////////////////
  vecBd_NTracks.push_back(  BAHCuts::getMinMaxBounds(Set,CutVersion,"NTracks") );
  vecBd_NShowers.push_back( BAHCuts::getMinMaxBounds(Set,CutVersion,"NShowers") );
  vecBd_NPi0s.push_back(    BAHCuts::getMinMaxBounds(Set,CutVersion,"NPi0s") );
  ////////////////////////////
  vecBd_ShDang.push_back(  BAHCuts::getMinMaxBounds(Set,CutVersion,"ShDang") );
  vecBd_LogShPi0Pull.push_back(  BAHCuts::getMinMaxBounds(Set,CutVersion,"LogShPi0Pull") );
  ////////////////////////////
  vecBd_pi0_ShDang.push_back(  BAHCuts::getMinMaxBounds(Set,CutVersion,"ShDangPi0") );
  ////////////////////////////
  vecBd_EMCExtra.push_back(BAHCuts::getMinMaxBounds(Set,CutVersion,"EMCExtra") );
  vecBd_VisMass.push_back(BAHCuts::getMinMaxBounds(Set,CutVersion,"VisMass") );
  vecBd_RhoMassDiff.push_back(BAHCuts::getMinMaxBounds(Set,CutVersion,"RhoMassDiff") );
  vecBd_RhoMass.push_back(BAHCuts::getMinMaxBounds(Set,CutVersion,"RhoMass") );
  vecBd_COSpmVg.push_back(BAHCuts::getMinMaxBounds(Set,CutVersion,"COS.pmVg") );
  vecBd_COSgVe.push_back(BAHCuts::getMinMaxBounds(Set,CutVersion,"COSgV.e") );
  vecBd_COSgVmu.push_back(BAHCuts::getMinMaxBounds(Set,CutVersion,"COSgV.mu") );
  ////////////////////////////
  vecBd_TkEMCProbR_e.push_back(BAHCuts::getMinMaxBounds(Set,CutVersion,"TkProbemcR.e") );
  vecBd_TkEMCProb_e.push_back(  BAHCuts::getMinMaxBounds(Set,CutVersion,"TkEMCProb.e") );
  vecBd_TkEP_e.push_back(  BAHCuts::getMinMaxBounds(Set,CutVersion,"TkEP.e") );
  vecBd_TkCos_e.push_back(BAHCuts::getMinMaxBounds(Set,CutVersion,"TkCosTheta.e") );
  vecBd_MOM_e.push_back( BAHCuts::getMinMaxBounds(Set,CutVersion,"MOM.e") );
  // Muon Prob  
  vecBd_TkCos_mu.push_back(     BAHCuts::getMinMaxBounds(Set,CutVersion,"TkCosTheta.mu") );
  vecBd_TkEP_mu.push_back(      BAHCuts::getMinMaxBounds(Set,CutVersion,"TkEP.mu") );
  vecBd_TkEemc_mu.push_back(    BAHCuts::getMinMaxBounds(Set,CutVersion,"TkEemc.mu") );
  vecBd_TkMUC_mu.push_back(     BAHCuts::getMinMaxBounds(Set,CutVersion,"TkMUC.mu") );
  vecBd_TkEMCProb_mu.push_back( BAHCuts::getMinMaxBounds(Set,CutVersion,"TkEMCProb.mu") );
  vecBd_TkEMCProbMuvE.push_back(  BAHCuts::getMinMaxBounds(Set,CutVersion,"TkEMCProb.MuvE") );
  vecBd_TkEMCProbMuvK.push_back(  BAHCuts::getMinMaxBounds(Set,CutVersion,"TkEMCProb.MuvK") );
  vecBd_TkMUC_pi.push_back(     BAHCuts::getMinMaxBounds(Set,CutVersion,"TkMucDepth.mu") );
  vecBd_MOM_mu.push_back( BAHCuts::getMinMaxBounds(Set,CutVersion,"MOM.mu") );
  // Pion Prob 
  vecBd_TkEP_pi.push_back(  BAHCuts::getMinMaxBounds(Set,CutVersion,"TkEP.pi") );
  vecBd_TkEMCProb_pi.push_back( BAHCuts::getMinMaxBounds(Set,CutVersion,"TkEMCProb.pi") );
  vecBd_TkEMCProbPivK.push_back(  BAHCuts::getMinMaxBounds(Set,CutVersion,"TkEMCProb.PivK") );
  vecBd_TkProbPivE.push_back(  BAHCuts::getMinMaxBounds(Set,CutVersion,"TkProb.PivE") );
  vecBd_TkProbPivK.push_back(  BAHCuts::getMinMaxBounds(Set,CutVersion,"TkProb.PivK") );
  vecBd_TkProbPivP.push_back(  BAHCuts::getMinMaxBounds(Set,CutVersion,"TkProb.PivP") );
  vecBd_TkCos_pi.push_back(  BAHCuts::getMinMaxBounds(Set,CutVersion,"TkCosTheta.pi") );
  vecBd_TkMUC_pi.push_back(     BAHCuts::getMinMaxBounds(Set,CutVersion,"TkMucDepth.pi") );
  //if(Set=="gpp"||Set=="gPP"||Set=="eepp"||Set=="mmpp"){
  if(Set=="gPP"){
    vecBd_MissingMass2.push_back( BAHCuts::getMinMaxBounds(Set,CutVersion,"MM2") );
    vecBd_TkCos_p.push_back(  BAHCuts::getMinMaxBounds(Set,CutVersion,"TkCosTheta.p") );
    vecBd_TkProbP.push_back( BAHCuts::getMinMaxBounds(Set,CutVersion,"TkProb.P") );
    vecBd_TkProbPvPi.push_back( BAHCuts::getMinMaxBounds(Set,CutVersion,"TkProb.PvPi") );
    vecBd_TkProbPvK.push_back(  BAHCuts::getMinMaxBounds(Set,CutVersion,"TkProb.PvK") );
    vecBd_TkMUC_pi.push_back(     BAHCuts::getMinMaxBounds(Set,CutVersion,"TkMucDepth.p") );
  }
  if(Set=="gkk"){
    vecBd_TkProbK.push_back( BAHCuts::getMinMaxBounds(Set,CutVersion,"TkProb.K") );
    vecBd_TkProbKvPi.push_back( BAHCuts::getMinMaxBounds(Set,CutVersion,"TkProb.KvPi") );
    vecBd_MOM_KK.push_back( BAHCuts::getMinMaxBounds(Set,CutVersion,"MOM.KK") );
    vecBd_MOM_K.push_back( BAHCuts::getMinMaxBounds(Set,CutVersion,"MOM.K") );
   }
  ////////////////////////////
  // Other bounds
  ////////////////////////////
  vecBd_Emiss.push_back(  BAHCuts::getMinMaxBounds(Set,CutVersion,"Emiss") );
  vecBd_Pmiss.push_back(  BAHCuts::getMinMaxBounds(Set,CutVersion,"Pmiss") );
  vecBd_EPmiss.push_back(  BAHCuts::getMinMaxBounds(Set,CutVersion,"EPmiss") );
  ////////////////////////////
  //Experimental Crap
}

// A simple way to input a min/max in the proper format of the vector pair
//   Can edit later to accept a long string of pairs and cyle though 'spacers'
vector<pair<TString,TString>> makeLines(TString xmin, TString xmax){
  vector<pair<TString,TString>> outputVec;
  outputVec.push_back(make_pair(xmin,xmax));
  return outputVec;
}

// Defining a vector-pair to make no lines ( since |0.0| < epsilon=0.000001 )
  vector <pair<TString, TString >>  noVals = {make_pair("0.0","0.0")};
// Based on bounds above, can get bounds for plotting lines based on particle type string
// If I just ass the Set and CutVersions, no need for all the vector crap above...
vector<pair<TString,TString>> getLines(TString VariableTag, bool printErrors=false){
  if(VariableTag==""||VariableTag=="NO"){  return noVals;  }  // Quick dummy
  if(VariableTag=="MassJpsi" ){  return vecBd_MJpsi;   }
  if(VariableTag=="MassXcJ" ){   return vecBd_MChicJ;  }
  ////////////////////////////
  if(VariableTag=="RMJpsi" ){   return vecBd_Jpsi;   }
  if(VariableTag=="RMXcJ"){   return vecBd_ChicJ;   }
  if(VariableTag=="RMTau" ){    return vecBd_Tau;     }
  if(VariableTag=="RMNOTHING" ){return vecBd_RMg; }
  if(VariableTag=="TkRV" ){     return vecBd_TkRV;  }
  if(VariableTag=="TkZV" ){     return vecBd_TkZV;  }
  if(VariableTag=="TkCos" ){    return vecBd_TkCos;  }
  if(VariableTag=="VChi2" ){    return vecBd_VChi2;   }
  if(VariableTag=="Chi2DOF"){    return vecBd_Chi2DOF;}
  ////////////////////////////
  if(VariableTag=="NTracks"){   return vecBd_NTracks; }
  if(VariableTag=="NShowers"){  return vecBd_NShowers;}
  if(VariableTag=="NPi0s"){     return vecBd_NPi0s;   }
  if(VariableTag=="MM2"){       return vecBd_MissingMass2;}
  ////////////////////////////
  if(VariableTag=="COS.pmVg"){   return vecBd_COSpmVg;}
  if(VariableTag=="COSgV.e"){   return vecBd_COSgVe;}
  if(VariableTag=="COSgV.mu"){   return vecBd_COSgVmu;}
  if(VariableTag=="RhoMassDiff"){return vecBd_RhoMassDiff;}
  if(VariableTag=="RhoMass"){    return vecBd_RhoMass;}
  if(VariableTag=="VisMass"){    return vecBd_VisMass;}
  if(VariableTag=="Emiss"  ){    return vecBd_Emiss;}
  if(VariableTag=="Pmiss"  ){    return vecBd_Pmiss;}
  if(VariableTag=="EPmiss" ){    return vecBd_EPmiss;}
  ////////////////////////////
  if(VariableTag=="ShDang"){    return vecBd_ShDang;  }
  if(VariableTag=="LogShPi0Pull"){ return vecBd_LogShPi0Pull;}
  ////////////////////////////
  if(VariableTag=="ShDangPi0"){    return vecBd_pi0_ShDang;  }
  ////////////////////////////
  if(VariableTag=="EMCExtra"){  return vecBd_EMCExtra;}
  ////////////////////////////
  // Switch to Contains in-case I switch/use charge dependant cuts or number dependant
  ////////////////////////////
  if(VariableTag.Contains("TkEP.e")){    return vecBd_TkEP_e;  }
  if(VariableTag.Contains("TkCos.e")){   return vecBd_TkCos_e;  }
  if(VariableTag.Contains("ProbEMCR.e")){return vecBd_TkEMCProbR_e;}
  if(VariableTag.Contains("ProbEMC.e")){ return vecBd_TkEMCProb_e;   }
  if(VariableTag.Contains("MOM.e")){   return vecBd_MOM_e;  }
  ////////////////////////////
  if(VariableTag.Contains("TkCos.mu")){   return vecBd_TkCos_mu;  }
  if(VariableTag.Contains("TkEP.mu")){    return vecBd_TkEP_mu;   }
  if(VariableTag.Contains("TkEemc.mu")){  return vecBd_TkEemc_mu; }
  if(VariableTag.Contains("ProbEMC.mu")){      return vecBd_TkEMCProb_mu;   }
  if(VariableTag.Contains("ProbEMCVSe.mu")){   return vecBd_TkEMCProbMuvE;  }
  if(VariableTag.Contains("ProbEMCVSk.mu")){   return vecBd_TkEMCProbMuvK;  }
  if(VariableTag.Contains("MUC.mu")){      return vecBd_TkMUC_mu;   }
  if(VariableTag.Contains("MOM.mu")){   return vecBd_MOM_mu;  }
  ////////////////////////////
  if(VariableTag.Contains("TkCos.pi")){  return vecBd_TkCos_pi; }
  if(VariableTag.Contains("TkEP.pi")){   return vecBd_TkEP_pi;  }
  if(VariableTag.Contains("ProbEMC.pi")){      return vecBd_TkEMCProb_pi;   }
  if(VariableTag.Contains("ProbEMCVSk.pi")){   return vecBd_TkEMCProbPivK;  }
  if(VariableTag.Contains("ProbVSe.pi")){   return vecBd_TkProbPivE;  }
  if(VariableTag.Contains("ProbVSk.pi")){   return vecBd_TkProbPivK;  }
  if(VariableTag.Contains("ProbVSp.pi")){   return vecBd_TkProbPivP;  }
  if(VariableTag.Contains("MUC.pi")){      return vecBd_TkMUC_pi;   }
  //////////////////////////// Always have proton after pi to get correct Contains()
  if(VariableTag.Contains("TkCos.p")){  return vecBd_TkCos_p;  }
  if(VariableTag.Contains("Prob.p")){  return vecBd_TkProbP;  }
  if(VariableTag.Contains("ProbVSpi.p")){  return vecBd_TkProbPvPi;  }
  if(VariableTag.Contains("ProbVSk.p")){   return vecBd_TkProbPvK;  }
  if(VariableTag.Contains("MUC.p")){      return vecBd_TkMUC_p;   }
  ////////////////////////////
  if(VariableTag.Contains("Prob.K")){  return vecBd_TkProbK;  }
  if(VariableTag.Contains("ProbVSpi.K")){  return vecBd_TkProbKvPi;  }
  if(VariableTag.Contains("MOM.KK")){  return vecBd_MOM_KK;  }
  if(VariableTag.Contains("MOM.K")){   return vecBd_MOM_K;  }
  ////////////////////////////
  if(printErrors){
    cout << "=====================" << endl;
    cout << " input: "+VariableTag  << endl;
    cout << "=== Not Saved in ====" << endl;
    cout << "== Global getLines ==" << endl;
    cout << "=====================" << endl;
  }
  return noVals;
}
//========================================================================
// Now Settting up global string for eventual/consistent use
// IF USING MANY SAME PATRTICLES, NEED TO BE MORE GENERAL AND ADD MORE
//========================================================================
  // Useful for plotting each particle individually   [FIX PARTICLE AND LABELS blow]
  TString pG;         TString pGlab;   
  TString pE;         TString pElab; 
  TString pE2;        TString pE2lab; 
  TString pMu;        TString pMulab;   
  TString pMu2;       TString pMu2lab;   
  TString pPiC;       TString pPiClab;  
  TString pPiC2;      TString pPiC2lab;  
  TString pPi0;       TString pPi0lab;
  TString pPi02;      TString pPi02lab;
  TString pPro;       TString pProlab;
  TString pPro2;      TString pPro2lab;
  TString pK;         TString pKlab;
  TString pK2;        TString pK2lab;

/* #region  Defining Globals Cuts TStrings */
  // A TString for any added cuts to check off-hand real quick.
  TString cut_ADDED;
  // Mass Cuts
  TString cut_Tau;
  TString cut_Chic0 , cut_Chic1 , cut_Chic2 , cut_ChicJ , cut_MChicJ;
  TString cut_Jpsi , cut_MJpsi;
  TString cut_RMg;
  // MC/Mass Cuts (MCM cuts)
  TString cut_MCM_Tau;
  TString cut_MCM_Chic0 , cut_MCM_Chic1, cut_MCM_Chic2 , cut_MCM_ChicJ , cut_MCM_MChicJ;
  TString cut_MCM_Jpsi  , cut_MCM_MJpsi;
  TString cut_MCM_RMg;
  // Track Cuts
  TString cut_tks;
  // Set-Specific Cuts
  TString cut_Vfit , cut_Chi2DOF;
  TString cut_NTracks , cut_NShowers , cut_NPi0s; 
  TString cut_EMCExtra;
  TString cut_MissingMass2; 
  TString cut_RhoMassDiff;
  TString cut_VisMass , cut_MOM_KK , cut_COSpmVg;
  TString cut_COSgVe;
  TString cut_COSgVmu;
  // Shower Cuts
  TString cut_ShDang  ; 
  TString cut_ShE925  ; 
  TString cut_ShCos   ; 
  TString cut_ShEnergy , cut_ShPi0Pull , cut_ShTime , cut_ShMatch; 
  // Pi0 Cuts
  TString cut_pi0_ShDang  ; 
  TString cut_pi0_ShE925  ; 
  TString cut_pi0_ShCos   ; 
  TString cut_pi0_ShEnergy , cut_pi0_ShPi0Pull , cut_pi0_ShTime , cut_pi0_ShMatch; 
  // Electron cuts
  TString cut_e_TkEP   ; 
  TString cut_e_TkCos   ;
  TString cut_e_TkProb  ; 
  TString cut_e_probR   ;
  TString cut_e_probRemc;
  TString cut_e_MDCe    ;
  TString cut_e_MDCm    ;
  TString cut_e_MDCem   ;
  TString cut_e_emcProb ;
  TString cut_e_MOM;
  // Muon Cuts
  TString cut_mu_TkCos;
  TString cut_mu_TkEP ; 
  TString cut_mu_TkEemc ; 
  TString cut_mu_TkProb; 
  TString cut_mu_MDCe  ;
  TString cut_mu_MDCm  ;
  TString cut_mu_MDCem ;
  TString cut_mu_emcProbvE ;
  TString cut_mu_emcProbvK ;
  TString cut_mu_emcProb ;
  TString cut_mu_MUC ;
  TString cut_mu_MOM;
  // Charged Pion Cuts
  TString cut_pi_TkEP ; 
  TString cut_pi_ProbvE ;
  TString cut_pi_ProbvK ;
  TString cut_pi_ProbvP ;
  TString cut_pi_emcProb ;
  TString cut_pi_emcProbvK;
  TString cut_pi_TkCos;
  TString cut_pi_MUC ;
  // Neutral Pion Cuts
  // Proton Cuts
  TString cut_p_TkCos;
  TString cut_p_TkProb; 
  TString cut_p_ProbvPi ;
  TString cut_p_ProbvK ;
  TString cut_p_MUC ;
  // Kaon Cuts
  TString cut_k_ProbvPi;
  TString cut_k_MOM;
  TString cut_k_TkProb; 

/* #endregion */

// For reseting Global Cuts for different decay modes
void resetGlobals(){
  // Useful for plotting each particle individually
  pG="";         pGlab="";
  pE="";         pElab="";
  pE2="";        pE2lab="";
  pMu="";        pMulab="";
  pMu2="";       pMu2lab="";
  pPiC="";       pPiClab="";
  pPiC2="";      pPiC2lab="";
  pPi0="";       pPi0lab="";
  pPi02="";      pPi02lab="";
  pPro="";       pProlab="";
  pPro2="";      pPro2lab="";
  pK="";         pKlab="";
  pK2="";        pK2lab="";
  // Added Cuts
  cut_ADDED="";
  // Mass Cuts
  cut_Tau="";
  cut_ChicJ="";
  cut_Chic0="";
  cut_Chic1="";
  cut_Chic2="";
  cut_Jpsi="";
  cut_MChicJ="";
  cut_MJpsi="";
  // MC/Mass Cuts
  cut_MCM_Tau="";
  cut_MCM_ChicJ="";
  cut_MCM_Chic0="";
  cut_MCM_Chic1="";
  cut_MCM_Chic2="";
  cut_MCM_Jpsi="";
  cut_MCM_MChicJ="";
  cut_MCM_MJpsi="";
  // Track Cuts
  cut_tks="";
  // General Cuts
  cut_Vfit="";
  cut_Chi2DOF="";
  cut_NTracks="";
  cut_NShowers="";
  cut_NPi0s="";
  cut_EMCExtra="";
  cut_MissingMass2="";
  cut_VisMass="";
  cut_MOM_KK="";
  cut_RhoMassDiff="";
  cut_COSpmVg="";
  cut_COSgVe="";
  cut_COSgVmu="";
  // Shower Cuts
  cut_ShDang="";
  cut_ShE925="";
  cut_ShCos="";
  cut_ShEnergy="";
  cut_ShPi0Pull="";
  cut_ShTime="";
  cut_ShMatch="";
  // Pi0 Cuts
  cut_pi0_ShDang="";
  cut_pi0_ShE925="";
  cut_pi0_ShCos="";
  cut_pi0_ShEnergy="";
  cut_pi0_ShPi0Pull="";
  cut_pi0_ShTime="";
  cut_pi0_ShMatch="";
  // Electron Cuts
  cut_e_TkEP="";
  cut_e_TkCos="";
  cut_e_TkProb="";
  cut_e_probR="";
  cut_e_probRemc="";
  cut_e_MDCe="";
  cut_e_MDCm="";
  cut_e_MDCem="";
  cut_e_emcProb="";
  cut_e_MOM="";
  // Muon Cuts
  cut_mu_TkCos="";
  cut_mu_TkEP="";
  cut_mu_TkEemc="";
  cut_mu_TkProb="";
  cut_mu_MDCe="";
  cut_mu_MDCm="";
  cut_mu_MDCem="";
  cut_mu_emcProbvE="";
  cut_mu_emcProbvK="";
  cut_mu_emcProb="";
  cut_mu_MUC="";
  cut_mu_MOM="";
  // Pion cuts
  cut_pi_ProbvE="";
  cut_pi_ProbvK="";
  cut_pi_ProbvP="";
  cut_pi_emcProb="";
  cut_pi_emcProbvK="";
  cut_pi_TkCos="";
  cut_pi_TkEP="";
  // Proton cuts
  cut_p_TkCos="";
  cut_p_TkProb="";
  cut_p_ProbvPi="";
  cut_p_ProbvK="";
  // Kaon cuts
  cut_k_ProbvPi="";
  cut_k_MOM="";
  cut_k_TkProb="";
}
//========================================================================
// Not Necessary but might be useful for quick plotting... (maybe?)
vector<pair<TString,TString>> defineParticles(TString Set, BAHDecays DecayInfo){
  // Output is formated a charged particles, the gamma then pi0's and the etas (if any etas)
  // Edited to output this for convenience... (rarely use these otherwise)
  vector<pair<TString,TString>> Output;
  // LFV Signal Decay Modes
  if(Set=="gtm"||Set=="get"){
    pE  =DecayInfo.getElectrons()[0].first;    pElab   =DecayInfo.getElectrons()[0].second;
    pG  =DecayInfo.getShowers()[0].first;      pGlab   =DecayInfo.getShowers()[0].second;
    pMu =DecayInfo.getMuons()[0].first;        pMulab  =DecayInfo.getMuons()[0].second;
    Output.push_back(make_pair(pE ,pElab));
    Output.push_back(make_pair(pMu,pMulab));
    Output.push_back(make_pair(pG ,pGlab));
  }
  if(Set=="gep"||Set=="gepp"){
    pE  =DecayInfo.getElectrons()[0].first;    pElab   =DecayInfo.getElectrons()[0].second;
    pG  =DecayInfo.getShowers()[0].first;      pGlab   =DecayInfo.getShowers()[0].second;
    pPiC=DecayInfo.getPiCs()[0].first;         pPiClab =DecayInfo.getPiCs()[0].second;
    Output.push_back(make_pair(pE ,pElab ));
    Output.push_back(make_pair(pPiC,pPiClab));
    Output.push_back(make_pair(pG,pGlab  ));
    if(Set=="gepp"){
      pPi0=DecayInfo.getPi0s()[0].first;       pPi0lab =DecayInfo.getPi0s()[0].second;
      Output.push_back(make_pair(pPi0,pPi0lab));
    }
  }
  // LFV Control Decay Modes
  if(Set=="gpp"){
    pG  = DecayInfo.getShowers()[0].first;      pGlab   =DecayInfo.getShowers()[0].second;
    pPiC= DecayInfo.getPiCs()[0].first;         pPiClab =DecayInfo.getPiCs()[0].second;
    pPiC2=DecayInfo.getPiCs()[1].first;         pPiC2lab=DecayInfo.getPiCs()[1].second;
    Output.push_back(make_pair(pPiC ,pPiClab ));
    Output.push_back(make_pair(pPiC2,pPiC2lab));
    Output.push_back(make_pair(pG,pGlab      ));
  }
  if(Set=="gPP"){
    pG   = DecayInfo.getShowers()[0].first;     pGlab   =DecayInfo.getShowers()[0].second;
    pPro = DecayInfo.getProtons()[0].first;     pProlab =DecayInfo.getProtons()[0].second;
    pPro2=DecayInfo.getProtons()[1].first;      pPro2lab=DecayInfo.getProtons()[1].second;
    Output.push_back(make_pair(pPro ,pProlab ));
    Output.push_back(make_pair(pPro2,pPro2lab));
    Output.push_back(make_pair(pG   ,pGlab   ));
  }
  if(Set=="gkk"){
    pG   = DecayInfo.getShowers()[0].first;      pGlab  =DecayInfo.getShowers()[0].second;
    pK   = DecayInfo.getKaons()[0].first;        pKlab  =DecayInfo.getKaons()[0].second;
    pK2  = DecayInfo.getKaons()[1].first;        pK2lab =DecayInfo.getKaons()[1].second;
    Output.push_back(make_pair(pK ,pKlab ));
    Output.push_back(make_pair(pK2,pK2lab));
    Output.push_back(make_pair(pG ,pGlab ));
  }
  if(Set=="eepp"||Set=="mmpp"){
    if(Set=="eepp"){
      pE  = DecayInfo.getElectrons()[0].first;    pElab   =DecayInfo.getElectrons()[0].second;
      pE2 = DecayInfo.getElectrons()[1].first;    pE2lab  =DecayInfo.getElectrons()[1].second;
      Output.push_back(make_pair(pE ,pElab ));
      Output.push_back(make_pair(pE2,pE2lab));
    }
    if(Set=="mmpp"){
      pMu  = DecayInfo.getMuons()[0].first;    pMulab    =DecayInfo.getMuons()[0].second;
      pMu2 = DecayInfo.getMuons()[1].first;    pMu2lab   =DecayInfo.getMuons()[1].second;
      Output.push_back(make_pair(pMu ,pMulab ));
      Output.push_back(make_pair(pMu2,pMu2lab));
    }
    pPi0= DecayInfo.getPi0s()[0].first;         pPi0lab =DecayInfo.getPi0s()[0].second;
    pPi02=DecayInfo.getPi0s()[1].first;         pPi02lab=DecayInfo.getPi0s()[1].second;
    Output.push_back(make_pair(pPi0 ,pPi0lab ));
    Output.push_back(make_pair(pPi02,pPi02lab));
  }
  return Output;
}
//========================================================================
// Now defining cuts to use in getModeCut and GetCutExcept and elsewhere
// Cycling through vector of cuts to get specific cuts to apply/define here
//  BEST WORKS WHEN ONLY ONE PARTICLE OF EACH
void defineCuts(bool cut, BAHDecays DecayInfo, BAHCuts CutInfo){
  TString Set= DecayInfo.getSet();
  TString IS = DecayInfo.getIS();
  resetGlobals();
  if(!cut){return;}
  //========================
  if(BAHCuts::checkCut(CutInfo.getAdditionalCuts())){ cut_ADDED =CutInfo.getAdditionalCuts(); cout<<"HERE: extra stuff"<<endl;}
  //========================
  //========================
  // setting global mass cuts
  if(IS=="XcJ"){
    if(Set=="gpp"||Set=="gkk"){
      if(BAHCuts::checkCut(CutInfo.getMass1Cuts()[0].second)){ cut_Chic0 = CutInfo.getMass1Cuts()[0].second;}
      if(BAHCuts::checkCut(CutInfo.getMass1Cuts()[1].second)){ cut_Chic2 = CutInfo.getMass1Cuts()[1].second;}
    }
    else{
      if(BAHCuts::checkCut(CutInfo.getMass1Cuts()[0].second)){ cut_Chic0 = CutInfo.getMass1Cuts()[0].second;}
      if(BAHCuts::checkCut(CutInfo.getMass1Cuts()[1].second)){ cut_Chic1 = CutInfo.getMass1Cuts()[1].second;}
      if(BAHCuts::checkCut(CutInfo.getMass1Cuts()[1].second)){ cut_Chic2 = CutInfo.getMass1Cuts()[2].second;}
    }
    cut_ChicJ = CutsfromCutVec(reduceCutVecPair(CutInfo.getMass1Cuts()),"||");
    cout << cut_ChicJ << endl;
    //----------------------------
    if(Set=="gtm"||Set=="get"||Set=="gep"||Set=="gepp"){
      cut_Tau  = CutInfo.getMass2Cuts()[0].second;
    }
    //----------------------------
    if(Set=="gpp"||Set=="gPP"||Set=="gkk"){
      if(Set!="gkk")cut_MChicJ=CutInfo.getMass2Cuts()[0].second;
    }
  }
  //----------------------------
  if(IS=="Jpsi"){
    cut_Jpsi = CutInfo.getMass1Cuts()[0].second;
    cut_MJpsi= CutInfo.getMass2Cuts()[0].second;
  }
  //----------------------------
  if(IS=="NOTHING"){
    cut_RMg = CutInfo.getMass1Cuts()[0].second;
  }
  //========================
  //========================
  // setting globals of MC/Mass for proper resonance cuts
  if(IS=="XcJ"){
    if(Set=="gpp"||Set=="gkk"){
      if(BAHCuts::checkCut(cut_Chic0)){ cut_MCM_Chic0 = "("+cut_Chic0+FSAND+BAHDecays::getMCDecay("chi_c0")+")";}
      if(BAHCuts::checkCut(cut_Chic2)){ cut_MCM_Chic2 = "("+cut_Chic0+FSAND+BAHDecays::getMCDecay("chi_c2")+")";}
      cut_MCM_ChicJ = "("+cut_MCM_Chic0+FSAND+cut_MCM_Chic2+")";
    }
    else{
      if(BAHCuts::checkCut(cut_Chic0)){ cut_MCM_Chic0 = "("+cut_Chic0+FSAND+BAHDecays::getMCDecay("chi_c0")+")";}
      if(BAHCuts::checkCut(cut_Chic1)){ cut_MCM_Chic1 = "("+cut_Chic0+FSAND+BAHDecays::getMCDecay("chi_c1")+")";}
      if(BAHCuts::checkCut(cut_Chic2)){ cut_MCM_Chic2 = "("+cut_Chic0+FSAND+BAHDecays::getMCDecay("chi_c2")+")";}
      cut_MCM_ChicJ = "("+cut_MCM_Chic0+FSAND+cut_MCM_Chic1+FSAND+cut_MCM_Chic2+")";
    }
    cout << cut_MCM_ChicJ << endl;
    //----------------------------
    if(Set=="gtm"||Set=="get"||Set=="gep"||Set=="gepp"){
      cut_MCM_Tau  = "("+cut_Tau+FSAND+BAHDecays::getMCDecay("tau")+")";
    }
    //----------------------------
    if(Set=="gpp"||Set=="gPP"||Set=="gkk"){
      if(Set!="gkk") cut_MCM_MChicJ= "("+cut_MChicJ+FSAND+BAHDecays::getMCDecay("Jpsi")+")";
    }
  }
  //----------------------------
  if(IS=="Jpsi"){
    cut_MCM_Jpsi =  "("+cut_Jpsi+FSAND+BAHDecays::getMCDecay("Jpsi")+")";;
    cut_MCM_MJpsi=  "("+cut_MJpsi+FSAND+BAHDecays::getMCDecay("Jpsi")+")";;
  }
  //=============================
  //=============================
  // setting global track cuts  (Straight Forward so first)
  for(unsigned int i = 0; i < CutInfo.getTrackCuts().size(); i++){
    if(i==0){cut_tks = CutInfo.getTrackCuts()[i].second;} 
    else{cut_tks = cut_tks +FSAND+ CutInfo.getTrackCuts()[i].second;} 
  }
  //========================
  // setting global Fit cuts   (Straight Forward so second)
  for(unsigned int i = 0; i < CutInfo.getFitCuts().size(); i++){
    if(CutInfo.getFitCuts()[i].first=="VChi2"){         cut_Vfit    = CutInfo.getFitCuts()[i].second;} 
    if(CutInfo.getFitCuts()[i].first=="Chi2DOF"){       cut_Chi2DOF = CutInfo.getFitCuts()[i].second;} 
  }
  //========================
  // setting global Set-specific cuts
  for(unsigned int i = 0; i < CutInfo.getSetCuts().size(); i++){
    if(CutInfo.getSetCuts()[i].first=="NTracks"){          cut_NTracks  =CutInfo.getSetCuts()[i].second;} 
    if(CutInfo.getSetCuts()[i].first=="NShowers"){         cut_NShowers =CutInfo.getSetCuts()[i].second;} 
    if(CutInfo.getSetCuts()[i].first=="NPi0s"){            cut_NPi0s    =CutInfo.getSetCuts()[i].second;} 
    if(CutInfo.getSetCuts()[i].first=="MissingMass2"){     cut_MissingMass2=CutInfo.getSetCuts()[i].second;} 
    if(CutInfo.getSetCuts()[i].first==getEMCExtra(Set)){   cut_EMCExtra =CutInfo.getSetCuts()[i].second;} 
    if(CutInfo.getSetCuts()[i].first=="COSINE(1;3)"){      cut_COSgVe=CutInfo.getSetCuts()[i].second;}
    if(CutInfo.getSetCuts()[i].first=="COSINE(2;3)"){      cut_COSgVmu=CutInfo.getSetCuts()[i].second;}
    if(Set=="gepp"){
      if(CutInfo.getSetCuts()[i].first=="MASS(1,2,3,[pi0])"){          cut_VisMass    =CutInfo.getSetCuts()[i].second;}
      if(CutInfo.getSetCuts()[i].first=="abs(MASS([pi],[pi0])-0.770)"){cut_RhoMassDiff=CutInfo.getSetCuts()[i].second;} 
    }
    if(Set=="gkk"){          // Need to use TStrCheck for wildcards
      //if(TStrCheck(CutInfo.getSetCuts()[i].first,"MOMENTUM(?,?)")){cut_MOM_KK=CutInfo.getSetCuts()[i].second;}
    }
    if(Set=="gPP"||Set=="gkk"||Set=="gpp"){          // Need to use TStrCheck for wildcards
      if(TStrCheck(CutInfo.getSetCuts()[i].first,"COSINE(?,?;?)")){cut_COSpmVg=CutInfo.getSetCuts()[i].second;}
    }
  }
  //========================
  // setting global shower cuts
  for(unsigned int i = 0; i < CutInfo.getShowerCuts().size(); i++){
    if(TStrCheck(CutInfo.getShowerCuts()[i].first,"ShDangP?")){    cut_ShDang  =addCut(cut_ShDang  ,CutInfo.getShowerCuts()[i].second);} 
    if(TStrCheck(CutInfo.getShowerCuts()[i].first,"ShE925P?")){    cut_ShE925  =addCut(cut_ShE925  ,CutInfo.getShowerCuts()[i].second);} 
    if(TStrCheck(CutInfo.getShowerCuts()[i].first,"ShCosThetaP?")){cut_ShCos   =addCut(cut_ShCos   ,CutInfo.getShowerCuts()[i].second);} 
    if(TStrCheck(CutInfo.getShowerCuts()[i].first,"ShEnergyP?")){  cut_ShEnergy=addCut(cut_ShEnergy,CutInfo.getShowerCuts()[i].second);} 
    if(TStrCheck(CutInfo.getShowerCuts()[i].first,"ShPi0PullP?")){cut_ShPi0Pull=addCut(cut_ShPi0Pull,CutInfo.getShowerCuts()[i].second);} 
    if(TStrCheck(CutInfo.getShowerCuts()[i].first,"ShTimeP?")){    cut_ShTime  =addCut(cut_ShTime  ,CutInfo.getShowerCuts()[i].second);} 
    if(TStrCheck(CutInfo.getShowerCuts()[i].first,"ShMatchP?")){   cut_ShMatch =addCut(cut_ShMatch ,CutInfo.getShowerCuts()[i].second);} 
  }
  //========================
  // setting global electron cuts
  for(unsigned int i = 0; i < CutInfo.getElectronCuts().size(); i++){
    if(TStrCheck(CutInfo.getElectronCuts()[i].first,"TkCosThetaP?")){      cut_e_TkCos   =addCut(cut_e_TkCos   ,CutInfo.getElectronCuts()[i].second);} 
    if(TStrCheck(CutInfo.getElectronCuts()[i].first,"TkEPP?")){            cut_e_TkEP    =addCut(cut_e_TkEP    ,CutInfo.getElectronCuts()[i].second);} 
    if(TStrCheck(CutInfo.getElectronCuts()[i].first,"TkProbEP?")){         cut_e_TkProb  =addCut(cut_e_TkProb  ,CutInfo.getElectronCuts()[i].second);} 
    if(TStrCheck(CutInfo.getElectronCuts()[i].first,getMDCchi("?",1))){    cut_e_MDCe    =addCut(cut_e_MDCe    ,CutInfo.getElectronCuts()[i].second);}
    if(TStrCheck(CutInfo.getElectronCuts()[i].first,getMDCchi("?",2))){    cut_e_MDCm    =addCut(cut_e_MDCm    ,CutInfo.getElectronCuts()[i].second);}
    if(TStrCheck(CutInfo.getElectronCuts()[i].first,getMDCchi("?",3))){    cut_e_MDCem   =addCut(cut_e_MDCem   ,CutInfo.getElectronCuts()[i].second);}
    if(TStrCheck(CutInfo.getElectronCuts()[i].first,"TkProbemcEP?")){      cut_e_emcProb =addCut(cut_e_emcProb ,CutInfo.getElectronCuts()[i].second);}
    if(TStrCheck(CutInfo.getElectronCuts()[i].first,getEProbR(false,"?"))){cut_e_probR   =addCut(cut_e_probR   ,CutInfo.getElectronCuts()[i].second);}
    if(TStrCheck(CutInfo.getElectronCuts()[i].first,getEProbR(true,"?"))){ cut_e_probRemc=addCut(cut_e_probRemc,CutInfo.getElectronCuts()[i].second);}
    if(TStrCheck(CutInfo.getElectronCuts()[i].first,"MOMENTUM(?)") ){      cut_e_MOM     =addCut(cut_e_MOM     ,CutInfo.getElectronCuts()[i].second);}
  }
  //========================
  // setting global muon cuts 
  for(unsigned int i = 0; i < CutInfo.getMuonCuts().size(); i++){
    if(TStrCheck(CutInfo.getMuonCuts()[i].first,"TkCosThetaP?")){   cut_mu_TkCos  =addCut(cut_mu_TkCos    ,CutInfo.getMuonCuts()[i].second);} 
    if(TStrCheck(CutInfo.getMuonCuts()[i].first,"TkEPP?")){         cut_mu_TkEP   =addCut(cut_mu_TkEP     ,CutInfo.getMuonCuts()[i].second);} 
    if(TStrCheck(CutInfo.getMuonCuts()[i].first,getTkEemc("?"))){   cut_mu_TkEemc =addCut(cut_mu_TkEemc   ,CutInfo.getMuonCuts()[i].second);} 
    if(TStrCheck(CutInfo.getMuonCuts()[i].first,"TkMucDepthP?")){   cut_mu_MUC    =addCut(cut_mu_MUC      ,CutInfo.getMuonCuts()[i].second);}
    if(TStrCheck(CutInfo.getMuonCuts()[i].first,getMDCchi("?",1))){ cut_mu_MDCe   =addCut(cut_mu_MDCe     ,CutInfo.getMuonCuts()[i].second);}
    if(TStrCheck(CutInfo.getMuonCuts()[i].first,getMDCchi("?",2))){ cut_mu_MDCm   =addCut(cut_mu_MDCm     ,CutInfo.getMuonCuts()[i].second);}
    if(TStrCheck(CutInfo.getMuonCuts()[i].first,getMDCchi("?",3))){ cut_mu_MDCem  =addCut(cut_mu_MDCem    ,CutInfo.getMuonCuts()[i].second);}
    if(TStrCheck(CutInfo.getMuonCuts()[i].first,"TkProbMuP?")){     cut_mu_TkProb =addCut(cut_mu_TkProb   ,CutInfo.getMuonCuts()[i].second);} 
    if(TStrCheck(CutInfo.getMuonCuts()[i].first,"TkProbemcMuP?")){  cut_mu_emcProb=addCut(cut_mu_emcProb,CutInfo.getMuonCuts()[i].second);}
    if(TStrCheck(CutInfo.getMuonCuts()[i].first,getProbVS(true,"Mu","E","?"))){cut_mu_emcProbvE =addCut(cut_mu_emcProbvE,CutInfo.getMuonCuts()[i].second);}
    if(TStrCheck(CutInfo.getMuonCuts()[i].first,getProbVS(true,"Mu","K","?"))){cut_mu_emcProbvK =addCut(cut_mu_emcProbvK,CutInfo.getMuonCuts()[i].second);}
    if(TStrCheck(CutInfo.getMuonCuts()[i].first,"MOMENTUM(?)") ){              cut_mu_MOM       =addCut(cut_mu_MOM,CutInfo.getMuonCuts()[i].second);}
  }
  //========================
  // setting global charged pion cuts
  for(unsigned int i = 0; i < CutInfo.getChargedPiCuts().size(); i++){
    if(TStrCheck(CutInfo.getChargedPiCuts()[i].first,"TkCosThetaP?")){               cut_pi_TkCos  =addCut(cut_pi_TkCos  ,CutInfo.getChargedPiCuts()[i].second);} 
    if(TStrCheck(CutInfo.getChargedPiCuts()[i].first,"TkEPP?")){                     cut_pi_TkEP   =addCut(cut_pi_TkEP   ,CutInfo.getChargedPiCuts()[i].second);}
    if(TStrCheck(CutInfo.getChargedPiCuts()[i].first,"TkMucDepthP?")){               cut_pi_MUC    =addCut(cut_pi_MUC    ,CutInfo.getChargedPiCuts()[i].second);} 
    if(TStrCheck(CutInfo.getChargedPiCuts()[i].first,"TkProbemcPiP?")){              cut_pi_emcProb=addCut(cut_pi_emcProb,CutInfo.getChargedPiCuts()[i].second);}
    if(TStrCheck(CutInfo.getChargedPiCuts()[i].first,getProbVS(true,"Pi","K","?"))){cut_pi_emcProbvK=addCut(cut_pi_emcProbvK,CutInfo.getChargedPiCuts()[i].second);}
    if(TStrCheck(CutInfo.getChargedPiCuts()[i].first,getProbVS(false,"Pi","E","?"))){cut_pi_ProbvE =addCut(cut_pi_ProbvE ,CutInfo.getChargedPiCuts()[i].second);}
    if(TStrCheck(CutInfo.getChargedPiCuts()[i].first,getProbVS(false,"Pi","K","?"))){cut_pi_ProbvK =addCut(cut_pi_ProbvK ,CutInfo.getChargedPiCuts()[i].second);}
    if(TStrCheck(CutInfo.getChargedPiCuts()[i].first,getProbVS(false,"Pi","P","?"))){cut_pi_ProbvP =addCut(cut_pi_ProbvP ,CutInfo.getChargedPiCuts()[i].second);}
  }
  //========================
  // setting global proton cuts
  for(unsigned int i = 0; i < CutInfo.getProtonCuts().size(); i++){
    if(TStrCheck(CutInfo.getProtonCuts()[i].first,"TkCosThetaP?")){               cut_p_TkCos   =addCut(cut_p_TkCos  ,CutInfo.getProtonCuts()[i].second);} 
    if(TStrCheck(CutInfo.getProtonCuts()[i].first,"TkMucDepthP?")){               cut_p_MUC     =addCut(cut_p_MUC    ,CutInfo.getProtonCuts()[i].second);} 
    if(TStrCheck(CutInfo.getProtonCuts()[i].first,"TkProbPP?")){                  cut_p_TkProb  =addCut(cut_p_TkProb ,CutInfo.getProtonCuts()[i].second);} 
    if(TStrCheck(CutInfo.getProtonCuts()[i].first,getProbVS(false,"P","Pi","?"))){cut_p_ProbvPi =addCut(cut_p_ProbvPi,CutInfo.getProtonCuts()[i].second);}
    if(TStrCheck(CutInfo.getProtonCuts()[i].first,getProbVS(false,"P","K","?"))){ cut_p_ProbvK  =addCut(cut_p_ProbvK ,CutInfo.getProtonCuts()[i].second);}
  }
  //========================
  // setting global kaon cuts
  for(unsigned int i = 0; i < CutInfo.getKaonCuts().size(); i++){
    if(TStrCheck(CutInfo.getKaonCuts()[i].first,"TkProbKP?")){     cut_k_TkProb =addCut(cut_k_TkProb   ,CutInfo.getKaonCuts()[i].second);} 
    if(TStrCheck(CutInfo.getKaonCuts()[i].first,getProbVS(false,"K","Pi","?"))){ cut_k_ProbvPi =addCut(cut_k_ProbvPi,CutInfo.getKaonCuts()[i].second);}
    if(TStrCheck(CutInfo.getKaonCuts()[i].first,"MOMENTUM(?)") ){                cut_k_MOM     =addCut(cut_k_MOM,CutInfo.getKaonCuts()[i].second);}
  }
  //========================
  // setting global neutral pion cuts
  for(unsigned int i = 0; i < CutInfo.getPi0Cuts().size(); i++){
    if(TStrCheck(CutInfo.getPi0Cuts()[i].first,"ShDangP??")){    cut_pi0_ShDang  =addCut(cut_pi0_ShDang  ,CutInfo.getPi0Cuts()[i].second);} 
    if(TStrCheck(CutInfo.getPi0Cuts()[i].first,"ShE925P??")){    cut_pi0_ShE925  =addCut(cut_pi0_ShE925  ,CutInfo.getPi0Cuts()[i].second);} 
    if(TStrCheck(CutInfo.getPi0Cuts()[i].first,"ShCosThetaP??")){cut_pi0_ShCos   =addCut(cut_pi0_ShCos   ,CutInfo.getPi0Cuts()[i].second);} 
    if(TStrCheck(CutInfo.getPi0Cuts()[i].first,"ShEnergyP??")){  cut_pi0_ShEnergy=addCut(cut_pi0_ShEnergy,CutInfo.getPi0Cuts()[i].second);} 
    if(TStrCheck(CutInfo.getPi0Cuts()[i].first,"ShPi0PullP??")){cut_pi0_ShPi0Pull=addCut(cut_pi0_ShPi0Pull,CutInfo.getPi0Cuts()[i].second);} 
    if(TStrCheck(CutInfo.getPi0Cuts()[i].first,"ShTimeP??")){    cut_pi0_ShTime  =addCut(cut_pi0_ShTime  ,CutInfo.getPi0Cuts()[i].second);} 
    if(TStrCheck(CutInfo.getPi0Cuts()[i].first,"ShMatchP??")){   cut_pi0_ShMatch =addCut(cut_pi0_ShMatch ,CutInfo.getPi0Cuts()[i].second);} 
  }
}
//===============================================================================================
//===============================================================================================
// Gets all cuts applied. Checks the global variable to no spam null cuts
TString getModeCut(bool cut, TString Set){
  TString tempstr;
  if(cut==false){tempstr = "(6==6)";}
  if(cut==true){ 
    tempstr = "(9==9)";
    //=================================
    // For any additional offhand cuts applied
    if(BAHCuts::checkCut(cut_ADDED))       tempstr = tempstr +FSAND+ cut_ADDED;
    //=================================
    // For getting resonance regions
    if(Set=="gtm"||Set=="get"||Set=="gep"||Set=="gepp"){
      if(BAHCuts::checkCut(cut_ChicJ  ))   tempstr = tempstr +FSAND+ cut_ChicJ;
      if(BAHCuts::checkCut(cut_Tau    ))   tempstr = tempstr +FSAND+ cut_Tau;
    }
    if(Set=="gpp"||Set=="gPP"||Set=="gkk"){
      if(BAHCuts::checkCut(cut_ChicJ  ))   tempstr = tempstr +FSAND+ cut_ChicJ;
      if(BAHCuts::checkCut(cut_MChicJ  ))  tempstr = tempstr +FSAND+ cut_MChicJ;
    }
    if(Set=="eepp"||Set=="mmpp"){
      if(BAHCuts::checkCut(cut_Jpsi    ))   tempstr = tempstr +FSAND+ cut_Jpsi;
      if(BAHCuts::checkCut(cut_MJpsi   ))   tempstr = tempstr +FSAND+ cut_MJpsi;
    }
    if(Set=="etgpp"){
      if(BAHCuts::checkCut(cut_RMg   ))   tempstr = tempstr +FSAND+ cut_RMg;
    }
    //=================================
    //=================================
    //===== Track Cuts
    if(BAHCuts::checkCut(cut_tks      ))   tempstr = tempstr +FSAND+ cut_tks ; 
    //===== PID Cuts
    //=================================   
    tempstr = tempstr+"   "; // Just a spacer for reading final cuts
    //=================================   
    //===== Vertex Cuts
    if(BAHCuts::checkCut(cut_Vfit     ))   tempstr = tempstr +FSAND+ cut_Vfit;
    if(BAHCuts::checkCut(cut_Chi2DOF    )) tempstr = tempstr +FSAND+ cut_Chi2DOF;
    //=================================   
    tempstr = tempstr+"   "; // Just a spacer for reading final cuts
    //=================================   
    //===== Set Cuts
    if(BAHCuts::checkCut(cut_NTracks    )) tempstr = tempstr +FSAND+ cut_NTracks;
    if(BAHCuts::checkCut(cut_NShowers   )) tempstr = tempstr +FSAND+ cut_NShowers;
    if(BAHCuts::checkCut(cut_NPi0s      )) tempstr = tempstr +FSAND+ cut_NPi0s;
    if(BAHCuts::checkCut(cut_EMCExtra   )) tempstr = tempstr +FSAND+ cut_EMCExtra;
    if(BAHCuts::checkCut(cut_MissingMass2))tempstr = tempstr +FSAND+ cut_MissingMass2;
    if(BAHCuts::checkCut(cut_VisMass    )) tempstr = tempstr +FSAND+ cut_VisMass;
    if(BAHCuts::checkCut(cut_MOM_KK     )) tempstr = tempstr +FSAND+ cut_MOM_KK;
    if(BAHCuts::checkCut(cut_RhoMassDiff)) tempstr = tempstr +FSAND+ cut_RhoMassDiff;
    if(BAHCuts::checkCut(cut_COSpmVg    )) tempstr = tempstr +FSAND+ cut_COSpmVg;
    if(BAHCuts::checkCut(cut_COSgVe     )) tempstr = tempstr +FSAND+ cut_COSgVe;
    if(BAHCuts::checkCut(cut_COSgVmu    )) tempstr = tempstr +FSAND+ cut_COSgVmu;
    //=================================   
    tempstr = tempstr+"   "; // Just a spacer for reading final cuts
    //=================================   
    //===== Photon Cuts
    if(BAHCuts::checkCut(cut_ShDang   ))   tempstr = tempstr +FSAND+ cut_ShDang;
    if(BAHCuts::checkCut(cut_ShE925   ))   tempstr = tempstr +FSAND+ cut_ShE925;
    if(BAHCuts::checkCut(cut_ShCos    ))   tempstr = tempstr +FSAND+ cut_ShCos;
    if(BAHCuts::checkCut(cut_ShEnergy ))   tempstr = tempstr +FSAND+ cut_ShEnergy;
    if(BAHCuts::checkCut(cut_ShPi0Pull ))   tempstr = tempstr +FSAND+ cut_ShPi0Pull ;
    if(BAHCuts::checkCut(cut_ShTime   ))   tempstr = tempstr +FSAND+ cut_ShTime;
    if(BAHCuts::checkCut(cut_ShMatch  ))   tempstr = tempstr +FSAND+ cut_ShMatch;
    //=================================   
    //===== Photon Cuts
    if(BAHCuts::checkCut(cut_pi0_ShDang   ))   tempstr = tempstr +FSAND+ cut_pi0_ShDang;
    //=================================   
    tempstr = tempstr+"   "; // Just a spacer for reading final cuts
    //=================================   
    //===== Electron Cuts
    if(BAHCuts::checkCut(cut_e_TkEP   ))   tempstr = tempstr +FSAND+ cut_e_TkEP;
    if(BAHCuts::checkCut(cut_e_TkProb ))   tempstr = tempstr +FSAND+ cut_e_TkProb;
    if(BAHCuts::checkCut(cut_e_probR  ))   tempstr = tempstr +FSAND+ cut_e_probR;
    if(BAHCuts::checkCut(cut_e_probRemc))  tempstr = tempstr +FSAND+ cut_e_probRemc ;
    if(BAHCuts::checkCut(cut_e_MDCe   ))   tempstr = tempstr +FSAND+ cut_e_MDCe  ;
    if(BAHCuts::checkCut(cut_e_MDCm   ))   tempstr = tempstr +FSAND+ cut_e_MDCm ;
    if(BAHCuts::checkCut(cut_e_MDCem  ))   tempstr = tempstr +FSAND+ cut_e_MDCem;
    if(BAHCuts::checkCut(cut_e_TkCos  ))   tempstr = tempstr +FSAND+ cut_e_TkCos;
    if(BAHCuts::checkCut(cut_e_emcProb))   tempstr = tempstr +FSAND+ cut_e_emcProb;
    if(BAHCuts::checkCut(cut_e_MOM))       tempstr = tempstr +FSAND+ cut_e_MOM;
    if(Set=="gtm"|Set=="get"||Set=="mmpp"){
      //=================================   
      tempstr = tempstr+"   "; // Just a spacer for reading final cuts
      //=================================   
      //===== Muon Cuts
      if(BAHCuts::checkCut(cut_mu_TkCos  ))  tempstr = tempstr +FSAND+ cut_mu_TkCos;
      if(BAHCuts::checkCut(cut_mu_TkEP  ))   tempstr = tempstr +FSAND+ cut_mu_TkEP;
      if(BAHCuts::checkCut(cut_mu_TkEemc))   tempstr = tempstr +FSAND+ cut_mu_TkEemc;
      if(BAHCuts::checkCut(cut_mu_TkProb))   tempstr = tempstr +FSAND+ cut_mu_TkProb;
      if(BAHCuts::checkCut(cut_mu_MDCe  ))   tempstr = tempstr +FSAND+ cut_mu_MDCe;
      if(BAHCuts::checkCut(cut_mu_MDCm  ))   tempstr = tempstr +FSAND+ cut_mu_MDCm;
      if(BAHCuts::checkCut(cut_mu_MDCem ))   tempstr = tempstr +FSAND+ cut_mu_MDCem;
      if(BAHCuts::checkCut(cut_mu_emcProbvE))tempstr = tempstr +FSAND+ cut_mu_emcProbvE;
      if(BAHCuts::checkCut(cut_mu_emcProbvK))tempstr = tempstr +FSAND+ cut_mu_emcProbvK;
      if(BAHCuts::checkCut(cut_mu_emcProb))  tempstr = tempstr +FSAND+ cut_mu_emcProb;
      if(BAHCuts::checkCut(cut_mu_MUC    ))  tempstr = tempstr +FSAND+ cut_mu_MUC;
      if(BAHCuts::checkCut(cut_mu_MOM))      tempstr = tempstr +FSAND+ cut_mu_MOM;
    }
    if(Set=="gep"||Set=="gepp"||Set=="gpp"||Set=="etgpp"){
      //=================================   
      tempstr = tempstr+"   "; // Just a spacer for reading final cuts
      //=================================   
      //===== Charged Pion Cuts 
      if(BAHCuts::checkCut(cut_pi_TkCos))   tempstr = tempstr +FSAND+ cut_pi_TkCos;
      if(BAHCuts::checkCut(cut_pi_TkEP  ))  tempstr = tempstr +FSAND+ cut_pi_TkEP;
      if(BAHCuts::checkCut(cut_pi_ProbvE))  tempstr = tempstr +FSAND+ cut_pi_ProbvE;
      if(BAHCuts::checkCut(cut_pi_ProbvK))  tempstr = tempstr +FSAND+ cut_pi_ProbvK;
      if(BAHCuts::checkCut(cut_pi_ProbvP))  tempstr = tempstr +FSAND+ cut_pi_ProbvP;
      if(BAHCuts::checkCut(cut_pi_emcProb)) tempstr = tempstr +FSAND+ cut_pi_emcProb;
      if(BAHCuts::checkCut(cut_pi_emcProbvK))tempstr = tempstr +FSAND+ cut_pi_emcProbvK;
      if(BAHCuts::checkCut(cut_pi_MUC   ))  tempstr = tempstr +FSAND+ cut_pi_MUC;
    }
    if(Set=="gPP"){
      //=================================
      tempstr = tempstr+"   "; // Just a spacer for reading final cuts
      //=================================
      //===== Proton Cuts
      if(BAHCuts::checkCut(cut_p_TkCos))    tempstr = tempstr +FSAND+ cut_p_TkCos;
      if(BAHCuts::checkCut(cut_p_TkProb))   tempstr = tempstr +FSAND+ cut_p_TkProb;
      if(BAHCuts::checkCut(cut_p_ProbvPi))  tempstr = tempstr +FSAND+ cut_p_ProbvPi;
      if(BAHCuts::checkCut(cut_p_ProbvK))   tempstr = tempstr +FSAND+ cut_p_ProbvK;
      if(BAHCuts::checkCut(cut_p_MUC    ))  tempstr = tempstr +FSAND+ cut_p_MUC;
    }
    if(Set=="gkk"){
      //=================================
      tempstr = tempstr+"   "; // Just a spacer for reading final cuts
      //=================================
      //===== Kaon Cuts
      if(BAHCuts::checkCut(cut_k_ProbvPi))  tempstr = tempstr +FSAND+ cut_k_ProbvPi;
      if(BAHCuts::checkCut(cut_k_MOM))      tempstr = tempstr +FSAND+ cut_k_MOM;
      if(BAHCuts::checkCut(cut_k_TkProb))   tempstr = tempstr +FSAND+ cut_k_TkProb;
      //if(BAHCuts::checkCut(cut_MOM_KK))     tempstr = tempstr +FSAND+ cut_MOM_KK;
    }
    //=================================
    //===== Pi0 Cuts
    if(BAHCuts::checkCut(cut_pi0_ShDang   ))   tempstr = tempstr +FSAND+ cut_pi0_ShDang;
    if(BAHCuts::checkCut(cut_pi0_ShE925   ))   tempstr = tempstr +FSAND+ cut_pi0_ShE925;
    if(BAHCuts::checkCut(cut_pi0_ShCos    ))   tempstr = tempstr +FSAND+ cut_pi0_ShCos;
    if(BAHCuts::checkCut(cut_pi0_ShEnergy ))   tempstr = tempstr +FSAND+ cut_pi0_ShEnergy;
    if(BAHCuts::checkCut(cut_pi0_ShPi0Pull ))  tempstr = tempstr +FSAND+ cut_pi0_ShPi0Pull ;
    if(BAHCuts::checkCut(cut_pi0_ShTime   ))   tempstr = tempstr +FSAND+ cut_pi0_ShTime;
    if(BAHCuts::checkCut(cut_pi0_ShMatch  ))   tempstr = tempstr +FSAND+ cut_pi0_ShMatch;
    //=================================   
  }
  return tempstr;
}
//******************************************************************************************
// Based on decay set and input cut(s), get all other cuts except the input cut(s).
TString getCutEx( TString Set, TString cut, bool NOCUT = false){ // NOCUT is useless atm...
  TString check = getModeCut(true,Set);
  if(!BAHCuts::checkCut(cut)){  
    SPACEstr(" CUT FAILS CHECK, SEEMS REDUNTANT OR EMPTY so adding everything");
    cout << "Input Cut:  " << cut << endl;
    SPACEstr("Output Cut:");
  }
  if(!check.Contains(cut)){  
    SPACEstr(" CUT NOT IN TOTAL CUT [or Multiple cuts input] ");
    cout << cut << endl;
    SPACEin();
  }
  TString agcut("(2==2)"); // Redundant placeholder and addresses no input cuts (also nice identifier)
  //=================================
  // If there are addtional cuts that I'm checking, Putting them at the FRONT to highlight their existence, otherwise its (2==2)
  // Also, Can't remove this unless remove this. Forces user to implement cuts in the system correctly to check things.
    if(BAHCuts::checkCut(cut_ADDED))      agcut = cut_ADDED +FSAND+ agcut;
  //=================================
  // For getting resonance regions
  if(Set=="gtm"||Set=="get"||Set=="gep"||Set=="gepp"){
    if(BAHCuts::checkCut(cut_Tau    )&&!cut.Contains(cut_Tau    ))    agcut = agcut +FSAND+ cut_Tau   ; 
    if(BAHCuts::checkCut(cut_ChicJ  )&&!cut.Contains(cut_ChicJ  ))    agcut = agcut +FSAND+ cut_ChicJ ; 
  }
  if(Set=="gpp"||Set=="gPP"||Set=="gkk"){
    if(BAHCuts::checkCut(cut_ChicJ  )&&!cut.Contains(cut_ChicJ  ))    agcut = agcut +FSAND+ cut_ChicJ ; 
    if(BAHCuts::checkCut(cut_MChicJ )&&!cut.Contains(cut_MChicJ ))    agcut = agcut +FSAND+ cut_MChicJ ; 
  }
  if(Set=="eepp"||Set=="mmpp"){
    if(BAHCuts::checkCut(cut_Jpsi   )&&!cut.Contains(cut_Jpsi   ))    agcut = agcut +FSAND+ cut_Jpsi ; 
    if(BAHCuts::checkCut(cut_MJpsi  )&&!cut.Contains(cut_MJpsi  ))    agcut = agcut +FSAND+ cut_MJpsi ; 
  }
  if(Set=="etgpp"){
    if(BAHCuts::checkCut(cut_RMg      )&&!cut.Contains(cut_RMg   ))       agcut = agcut +FSAND+ cut_RMg ;
  }
  //=================================
  //===== Track Cuts 
  if(BAHCuts::checkCut(cut_tks     )&&!cut.Contains(cut_tks     ))    agcut = agcut +FSAND+ cut_tks     ;   
  //===== Vertex Cuts 
  if(BAHCuts::checkCut(cut_Vfit    )&&!cut.Contains(cut_Vfit    ))    agcut = agcut +FSAND+ cut_Vfit    ;   
  if(BAHCuts::checkCut(cut_Chi2DOF )&&!cut.Contains(cut_Chi2DOF ))    agcut = agcut +FSAND+ cut_Chi2DOF   ;  
  //===== Set Cuts 
  if(BAHCuts::checkCut(cut_NTracks )&&!cut.Contains(cut_NTracks ))    agcut = agcut +FSAND+ cut_NTracks ;  
  if(BAHCuts::checkCut(cut_NShowers)&&!cut.Contains(cut_NShowers))    agcut = agcut +FSAND+ cut_NShowers ;  
  if(BAHCuts::checkCut(cut_NPi0s   )&&!cut.Contains(cut_NPi0s   ))    agcut = agcut +FSAND+ cut_NPi0s ;  
  if(BAHCuts::checkCut(cut_EMCExtra)&&!cut.Contains(cut_EMCExtra))    agcut = agcut +FSAND+ cut_EMCExtra ;  
  if(BAHCuts::checkCut(cut_MissingMass2)&&!cut.Contains(cut_MissingMass2))agcut = agcut +FSAND+ cut_MissingMass2;
  if(BAHCuts::checkCut(cut_VisMass )&&!cut.Contains(cut_VisMass ))    agcut = agcut +FSAND+ cut_VisMass;
  if(BAHCuts::checkCut(cut_MOM_KK  )&&!cut.Contains(cut_MOM_KK  ))    agcut = agcut +FSAND+ cut_MOM_KK ;
  if(BAHCuts::checkCut(cut_RhoMassDiff)&&!cut.Contains(cut_RhoMassDiff))agcut = agcut +FSAND+ cut_RhoMassDiff ;
  if(BAHCuts::checkCut(cut_COSpmVg )&&!cut.Contains(cut_COSpmVg ))    agcut = agcut +FSAND+ cut_COSpmVg ;
  if(BAHCuts::checkCut(cut_COSgVe  )&&!cut.Contains(cut_COSgVe  ))    agcut = agcut +FSAND+ cut_COSgVe ;
  if(BAHCuts::checkCut(cut_COSgVmu )&&!cut.Contains(cut_COSgVmu ))    agcut = agcut +FSAND+ cut_COSgVmu ;
  //===== Photon Cuts 
  if(BAHCuts::checkCut(cut_ShDang  )&&!cut.Contains(cut_ShDang  ))    agcut = agcut +FSAND+ cut_ShDang ;   
  if(BAHCuts::checkCut(cut_ShE925  )&&!cut.Contains(cut_ShE925  ))    agcut = agcut +FSAND+ cut_ShE925 ;   
  if(BAHCuts::checkCut(cut_ShCos   )&&!cut.Contains(cut_ShCos   ))    agcut = agcut +FSAND+ cut_ShCos ;   
  if(BAHCuts::checkCut(cut_ShEnergy)&&!cut.Contains(cut_ShEnergy))    agcut = agcut +FSAND+ cut_ShEnergy ;   
  if(BAHCuts::checkCut(cut_ShPi0Pull)&&!cut.Contains(cut_ShPi0Pull))    agcut = agcut +FSAND+ cut_ShPi0Pull ;   
  if(BAHCuts::checkCut(cut_ShTime  )&&!cut.Contains(cut_ShTime  ))    agcut = agcut +FSAND+ cut_ShTime ;   
  if(BAHCuts::checkCut(cut_ShMatch )&&!cut.Contains(cut_ShMatch ))    agcut = agcut +FSAND+ cut_ShMatch ;  
  //===== Photons from Pi0 Cuts 
  if(BAHCuts::checkCut(cut_pi0_ShDang  )&&!cut.Contains(cut_pi0_ShDang  ))    agcut = agcut +FSAND+ cut_pi0_ShDang ;   
  //===== Electron Cuts 
  if(BAHCuts::checkCut(cut_e_TkEP  )&&!cut.Contains(cut_e_TkEP  ))    agcut = agcut +FSAND+ cut_e_TkEP ;  
  if(BAHCuts::checkCut(cut_e_TkProb)&&!cut.Contains(cut_e_TkProb))    agcut = agcut +FSAND+ cut_e_TkProb ;  
  if(BAHCuts::checkCut(cut_e_probR )&&!cut.Contains(cut_e_probR ))    agcut = agcut +FSAND+ cut_e_probR ;  
  if(BAHCuts::checkCut(cut_e_probRemc)&&!cut.Contains(cut_e_probRemc))agcut = agcut +FSAND+ cut_e_probRemc ;  
  if(BAHCuts::checkCut(cut_e_MDCe  )&&!cut.Contains(cut_e_MDCe  ))    agcut = agcut +FSAND+ cut_e_MDCe ;  
  if(BAHCuts::checkCut(cut_e_MDCm  )&&!cut.Contains(cut_e_MDCm  ))    agcut = agcut +FSAND+ cut_e_MDCm ;  
  if(BAHCuts::checkCut(cut_e_MDCem )&&!cut.Contains(cut_e_MDCem ))    agcut = agcut +FSAND+ cut_e_MDCem ;  
  if(BAHCuts::checkCut(cut_e_TkCos )&&!cut.Contains(cut_e_TkCos ))    agcut = agcut +FSAND+ cut_e_TkCos ;  
  if(BAHCuts::checkCut(cut_e_emcProb)&&!cut.Contains(cut_e_emcProb))  agcut = agcut +FSAND+ cut_e_emcProb;
  if(BAHCuts::checkCut(cut_e_MOM   )&&!cut.Contains(cut_e_MOM   ))    agcut = agcut +FSAND+ cut_e_MOM;
  //===== Muon Cuts
  if(BAHCuts::checkCut(cut_mu_TkCos )&&!cut.Contains(cut_mu_TkCos ))  agcut = agcut +FSAND+ cut_mu_TkCos;
  if(BAHCuts::checkCut(cut_mu_TkEP  )&&!cut.Contains(cut_mu_TkEP  ))  agcut = agcut +FSAND+ cut_mu_TkEP ;  
  if(BAHCuts::checkCut(cut_mu_TkEemc)&&!cut.Contains(cut_mu_TkEemc))  agcut = agcut +FSAND+ cut_mu_TkEemc ;
  if(BAHCuts::checkCut(cut_mu_TkProb)&&!cut.Contains(cut_mu_TkProb))  agcut = agcut +FSAND+ cut_mu_TkProb ;  
  if(BAHCuts::checkCut(cut_mu_MUC   )&&!cut.Contains(cut_mu_MUC   ))  agcut = agcut +FSAND+ cut_mu_MUC ;
  if(Set=="gtm"||Set=="get"||Set=="mmpp"){ // Specialized criteria
    if(BAHCuts::checkCut(cut_mu_MDCe  )&&!cut.Contains(cut_mu_MDCe  ))  agcut = agcut +FSAND+ cut_mu_MDCe ;   
    if(BAHCuts::checkCut(cut_mu_MDCm  )&&!cut.Contains(cut_mu_MDCm  ))  agcut = agcut +FSAND+ cut_mu_MDCm ;   
    if(BAHCuts::checkCut(cut_mu_MDCem )&&!cut.Contains(cut_mu_MDCem ))  agcut = agcut +FSAND+ cut_mu_MDCem ;   
    if(BAHCuts::checkCut(cut_mu_emcProbvE)&&!cut.Contains(cut_mu_emcProbvE)) agcut = agcut +FSAND+ cut_mu_emcProbvE;
    if(BAHCuts::checkCut(cut_mu_emcProbvK)&&!cut.Contains(cut_mu_emcProbvK)) agcut = agcut +FSAND+ cut_mu_emcProbvK;
    if(BAHCuts::checkCut(cut_mu_emcProb)&&!cut.Contains(cut_mu_emcProb))agcut = agcut +FSAND+ cut_mu_emcProb;
    if(BAHCuts::checkCut(cut_mu_MOM   )&&!cut.Contains(cut_mu_MOM   )) agcut  = agcut +FSAND+ cut_mu_MOM;
  }
  //===== Charged Pion Cuts
  if(BAHCuts::checkCut(cut_pi_TkCos  )&&!cut.Contains(cut_pi_TkCos )) agcut = agcut +FSAND+ cut_pi_TkCos;
  if(BAHCuts::checkCut(cut_pi_TkEP   )&&!cut.Contains(cut_pi_TkEP  )) agcut = agcut +FSAND+ cut_pi_TkEP;
  if(BAHCuts::checkCut(cut_pi_ProbvE )&&!cut.Contains(cut_pi_ProbvE)) agcut = agcut +FSAND+ cut_pi_ProbvE;
  if(BAHCuts::checkCut(cut_pi_ProbvK )&&!cut.Contains(cut_pi_ProbvK)) agcut = agcut +FSAND+ cut_pi_ProbvK;
  if(BAHCuts::checkCut(cut_pi_ProbvP )&&!cut.Contains(cut_pi_ProbvP)) agcut = agcut +FSAND+ cut_pi_ProbvP;
  if(BAHCuts::checkCut(cut_pi_MUC    )&&!cut.Contains(cut_pi_MUC   )) agcut = agcut +FSAND+ cut_pi_MUC ;
  if(Set=="gep"||Set=="gepp"||Set=="gpp"){ // Specialized criteria
    if(BAHCuts::checkCut(cut_pi_emcProb)&&!cut.Contains(cut_pi_emcProb))agcut = agcut +FSAND+ cut_pi_emcProb;
    if(BAHCuts::checkCut(cut_pi_emcProbvK)&&!cut.Contains(cut_pi_emcProbvK)) agcut = agcut +FSAND+ cut_pi_emcProbvK;
  }
  //===== Proton Cuts
  if(BAHCuts::checkCut(cut_p_TkCos   )&&!cut.Contains(cut_p_TkCos  )) agcut = agcut +FSAND+ cut_p_TkCos;
  if(BAHCuts::checkCut(cut_p_TkProb  )&&!cut.Contains(cut_p_TkProb  ))agcut = agcut +FSAND+ cut_p_TkProb;
  if(BAHCuts::checkCut(cut_p_ProbvPi )&&!cut.Contains(cut_p_ProbvPi)) agcut = agcut +FSAND+ cut_p_ProbvPi;
  if(BAHCuts::checkCut(cut_p_ProbvK  )&&!cut.Contains(cut_p_ProbvK))  agcut = agcut +FSAND+ cut_p_ProbvK;
  if(BAHCuts::checkCut(cut_p_MUC     )&&!cut.Contains(cut_p_MUC    )) agcut = agcut +FSAND+ cut_p_MUC ;
  //===== Kaon Cuts
  if(BAHCuts::checkCut(cut_k_ProbvPi )&&!cut.Contains(cut_k_ProbvPi)) agcut = agcut +FSAND+ cut_k_ProbvPi;
  if(BAHCuts::checkCut(cut_k_MOM     )&&!cut.Contains(cut_k_MOM    )) agcut = agcut +FSAND+ cut_k_MOM;
  if(BAHCuts::checkCut(cut_k_TkProb  )&&!cut.Contains(cut_k_TkProb  ))agcut = agcut +FSAND+ cut_k_TkProb;
  //===== Neutral Pion Cuts 
  if(BAHCuts::checkCut(cut_pi0_ShDang   )&&!cut.Contains(cut_pi0_ShDang   )) agcut = agcut +FSAND+ cut_pi0_ShDang ;   
  if(BAHCuts::checkCut(cut_pi0_ShE925   )&&!cut.Contains(cut_pi0_ShE925   )) agcut = agcut +FSAND+ cut_pi0_ShE925 ;   
  if(BAHCuts::checkCut(cut_pi0_ShCos    )&&!cut.Contains(cut_pi0_ShCos    )) agcut = agcut +FSAND+ cut_pi0_ShCos ;   
  if(BAHCuts::checkCut(cut_pi0_ShEnergy )&&!cut.Contains(cut_pi0_ShEnergy )) agcut = agcut +FSAND+ cut_pi0_ShEnergy ;   
  if(BAHCuts::checkCut(cut_pi0_ShPi0Pull)&&!cut.Contains(cut_pi0_ShPi0Pull)) agcut = agcut +FSAND+ cut_pi0_ShPi0Pull ;   
  if(BAHCuts::checkCut(cut_pi0_ShTime   )&&!cut.Contains(cut_pi0_ShTime   )) agcut = agcut +FSAND+ cut_pi0_ShTime ;   
  if(BAHCuts::checkCut(cut_pi0_ShMatch  )&&!cut.Contains(cut_pi0_ShMatch  )) agcut = agcut +FSAND+ cut_pi0_ShMatch ;  
  return agcut;
}
//========================================================================
// Because Same Variable Cuts are different for particles types, 
//    useful to get the global cuts based on particle type.
//========================================================================
TString TkEpCut(TString ParticleTag){
  if(ParticleTag=="e"  ){return cut_e_TkEP; }
  if(ParticleTag=="mu" ){return cut_mu_TkEP;}
  if(ParticleTag=="pi" ){return cut_pi_TkEP;}
  return noCut;
}
TString TkEemcCut(TString ParticleTag){
  if(ParticleTag=="mu" ){return cut_mu_TkEemc;}
  //if(ParticleTag=="pi" ){return cut_pi_TkEemc; }
  return noCut;
}
TString TkCosCut(TString ParticleTag){
  if(ParticleTag=="e"  ){return cut_e_TkCos; }
  if(ParticleTag=="mu" ){return cut_mu_TkCos; }
  if(ParticleTag=="pi" ){return cut_pi_TkCos; }
  if(ParticleTag=="p" ){return cut_p_TkCos; }
  return noCut;
}
TString ProbVsPiCut(TString ParticleTag){
  if(ParticleTag=="e"  ){return cut_pi_ProbvE; }
  if(ParticleTag=="K"  ){return cut_pi_ProbvK; }
  if(ParticleTag=="p"  ){return cut_pi_ProbvP; }
  return noCut;
}
TString EMCProbVsECut(TString ParticleTag){
  if(ParticleTag=="mu"  ){return cut_mu_emcProbvE; }
  if(ParticleTag=="pi"  ){return cut_pi_ProbvE; }
  return noCut;
}
TString TkMOMCut(TString ParticleTag){
  if(ParticleTag=="K"  ){return cut_k_MOM; }
  if(ParticleTag=="mu" ){return cut_mu_MOM;}
  if(ParticleTag=="e"  ){return cut_e_MOM; }
  return noCut;
}
TString MUCdepthCut(TString ParticleTag){
  if(ParticleTag=="p"   ){return cut_p_MUC; }
  if(ParticleTag=="pi"  ){return cut_pi_MUC; }
  if(ParticleTag=="mu"  ){return cut_mu_MUC; }
  return noCut;
}
TString ProbVsCut(bool emc, TString ParticleTag, TString ParticleTagVS){
  if((!emc)&&ParticleTag=="K"){
    if(ParticleTagVS=="pi" ){return cut_k_ProbvPi;}
  }
  if((!emc)&&ParticleTag=="p"){
    if(ParticleTagVS=="pi" ){return cut_p_ProbvPi;}
    if(ParticleTagVS=="K"  ){return cut_p_ProbvK; }
  }
  if((!emc)&&ParticleTag=="pi"){
    if(ParticleTagVS=="e"  ){return cut_pi_ProbvE; }
    if(ParticleTagVS=="K"  ){return cut_pi_ProbvK; }
    if(ParticleTagVS=="p"  ){return cut_pi_ProbvP; }
  }
  return noCut;
}
TString ProbCut(bool emc, TString ParticleTag){
  if(emc){
    if(ParticleTag=="pi"  ){return cut_pi_emcProb; }
    if(ParticleTag=="mu"  ){return cut_mu_emcProb; }
    if(ParticleTag=="e"  ){return  cut_e_emcProb; }
  }
  if(!emc){
    if(ParticleTag=="K"  ){return cut_k_TkProb; }
    if(ParticleTag=="p"  ){return cut_p_TkProb; }
  }
  return noCut;
}
TString COSgVTk(TString ParticleTag){
  if(ParticleTag=="e"   ){return cut_COSgVe; }
  if(ParticleTag=="mu"  ){return cut_COSgVmu; }
  return noCut;
}
//========================================================================
//========================================================================
// NEEDED to avoid push_back errors
void initiateSetup(){
  //--------------------------
  ClearMinMax(); // Need to clear since using push_back
  resetGlobals();// Clearing cuts from setup
  FSControl::QUIET=true;
  //--------------------------
  return;
}
//------------------------------------------
// Just a grouping of the define functions used here
void SetupGlobals(BAHDecays DecayInfo, BAHCuts CutInfo,TString Set, int CutVersion = 1){
  //--------------------------
  defineMinMaxVecs(DecayInfo,CutInfo,CutVersion);
  defineCuts(true,DecayInfo,CutInfo);
  // Just in case it is needed it is setup here as well  [particle number and TeX-labels]
  defineParticles(Set,DecayInfo);
  //----------------------------------
  return;
}
//------------------------------------------



//========================================================================
//========================================================================
// Can write a getTotCut
// and getCutEx based on final general/global labels when properly assigned
//========================================================================
void printsetup(TString Set, bool IsThereAFit=true, int CutVersion = 1){  // NEED TO ADD MORE HERE...
  BAHDecays DecayInfo(Set);
  if(DecayInfo.badinput()){ BAHDecays::shit(); return;}  // if bad input, then stopping
  BAHCuts CutInfo(DecayInfo,CutVersion,IsThereAFit);  
  defineMinMaxVecs(DecayInfo,CutInfo,CutVersion);
  defineCuts(1,DecayInfo,CutInfo);
  cout << endl;
  // JUST TO CHECK EACH GLOBAL CUT MADE 
  //========================================================================
  SPACEstr("Mass Cuts");
  cout << "Tau Cuts     :  " << cut_Tau<< endl; 
  cout << "XcJ Cuts     :  " << cut_ChicJ << endl;
  cout << "Xc0 Cuts     :  " << cut_Chic0 << endl;
  cout << "Xc1 Cuts     :  " << cut_Chic1 << endl;
  cout << "Xc2 Cuts     :  " << cut_Chic2 << endl;
  SPACEstr("Track Cuts");
  cout << "Track Cuts   :  " << cut_tks   << endl;
  SPACEstr("Fit Cuts");
  cout << "VChi2 Cuts   :  " << cut_Vfit  << endl;
  cout << "Chi2DOF Cuts :  " << cut_Chi2DOF << endl;
  SPACEstr("Set Cuts");
  cout << "Ntracks Cuts :  " << cut_NTracks  << endl;
  cout << "NShowers Cuts:  " << cut_NShowers  << endl;
  cout << "NPi0s Cuts   :  " << cut_NPi0s  << endl;
  cout << "EMCExtra Cuts:  " << cut_EMCExtra  << endl;
  cout << "MissM2 Cuts  :  " << cut_MissingMass2  << endl;
  cout << "VisMass Cuts :  " << cut_VisMass  << endl;
  cout << "MOM_KK Cuts  :  " << cut_MOM_KK  << endl;
  cout << "RhoMDiff Cuts:  " << cut_RhoMassDiff  << endl;
  //cout << "Cut_COSpmVg Cuts :  " << cut_Cut_COSpmVg  << endl;
  SPACEstr("Shower Cuts");
  if(Set=="gtm"||Set=="get"||Set=="gep"||Set=="gepp"||
      Set=="gpp"||Set=="gkk"||Set=="gPP"){
    cout << "ShDang Cut   :  " << cut_ShDang  << endl; 
    cout << "ShE925 Cut   :  " << cut_ShE925  << endl; 
    cout << "ShCos Cut    :  " << cut_ShCos   << endl; 
    cout << "ShEner Cut   :  " << cut_ShEnergy<< endl; 
    cout << "ShPi0Pull Cut :  " << cut_ShPi0Pull<< endl; 
    cout << "ShTime Cut   :  " << cut_ShTime  << endl; 
    cout << "ShMatch Cut  :  " << cut_ShMatch << endl; 
  }
  SPACEstr("Electron Cuts");
  if(Set=="gtm"||Set=="get"||Set=="gep"||Set=="gepp"||
      Set=="eepp"||Set=="tt"){
    cout << cut_e_TkEP     << endl; 
    cout << cut_e_TkProb   << endl; 
    cout << cut_e_probR    << endl;
    cout << cut_e_probRemc << endl;
    cout << cut_e_MDCe     << endl;
    cout << cut_e_MDCm     << endl;
    cout << cut_e_MDCem    << endl;
  }
  SPACEin();
  SPACEstr("Muon Cuts");
  if(Set=="gtm"||Set=="get"||Set=="mmpp"||Set=="tt"){
    cout << cut_mu_TkEP  << endl; 
    cout << cut_mu_TkProb << endl; 
    cout << cut_mu_MDCe   << endl;
    cout << cut_mu_MDCm   << endl;
    cout << cut_mu_MDCem  << endl;
    cout << cut_mu_emcProbvE  << endl;
    cout << cut_mu_emcProbvK  << endl;
    cout << cut_mu_emcProb  << endl;
  }
  SPACEin();
  SPACEstr("Proton Cuts");
  if(Set=="gPP"){
    cout << "TkCos Cuts    :  " << cut_p_TkCos  << endl;
    cout << "TkProb Cuts   :  " << cut_p_TkProb  << endl;
    cout << "ProbvPi Cuts  :  " << cut_p_ProbvPi  << endl;
    cout << "ProbvK Cuts   :  " << cut_p_ProbvK  << endl;
    cout << "MUC Cuts      :  " << cut_p_MUC  << endl;
  }
  SPACEin();
  SPACEstr("Total Set Cut: "+Set);
  cout << getModeCut(1,Set) << endl;
  SPACEin();
  //SPACEstr("getCutEx() Tau Cut:");
  //cout << getCutEx(Set,getCutEx(Set,cut_Tau)) << endl;
  //SPACEin();
  SPACEstr("getCutEx() ChicJ Cut:");
  cout << getCutEx(Set,cut_ChicJ) << endl;
  SPACEin();
  //SPACEstr("getCutEx() Tau/ChicJ Cut:");
  //cout << getCutEx(Set,cut_Tau+cut_ChicJ) << endl;
  //SPACEin();
  //SPACEstr("getCutEx() Vfit Cut:");
  //cout << getCutEx(Set,cut_Vfit) << endl;
  //SPACEin();
  //SPACEstr("getCutEx(getCutEx()) Tau Cut:");
  //cout << getCutEx(Set,getCutEx(Set,cut_Tau)) << endl;
  return;
}
//========================================================================
void printAllInfo(TString Set){
  int CutVer = 1;
  bool Fitted = 1;
  printdecay(Set);
  printCuts(Set);
  SPACEin();
  SPACEstr("Printing Setup Info");
  SPACEin();
  printsetup(Set,Fitted,CutVer);
}
//========================================================================




#endif