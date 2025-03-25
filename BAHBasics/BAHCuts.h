#if !defined(BAHCUTS_H)
#define BAHCUTS_H

#include "BAHUtilities.h"
#include "BAHStrings.h"
#include "BAHDecays.h"

// ***************************************************************
//
//  CLASS BAHCuts
//
//    Gets Cuts based on the decaymode of interest 
//
// ***************************************************************

class BAHDecays;

class BAHCuts{
  // declaring private class data members
private:
// Basic non-cut [should be consistent with BAHUtilities noCut]
  TString m_Set;  // Just for saving and checking stuff in case
  bool m_Chi2Fit;  // Just for saving and checking stuff in case
  TString m_noCut="(7==7)";
  double m_EPSILON=0.0000001; 


  TString m_MOM = "MOMENTUM";
  int m_finalparts;
  // In case I want to look at serveral criterias and have them saved....
  int m_CutVersion;
  // A placeholder for any additional cuts that wanna be tested later 
  TString m_AdditionalCuts;
  // Sets of Cuts    
  vector<pair<TString,TString>> m_SetCuts; // Cuts applied specificlly to the set of interest
  vector<pair<TString,TString>> m_MassCuts1; // for intermediate state particle 1
  vector<pair<TString,TString>> m_MassCuts2; // for intermediate state particle 2   (can add more if needed later...)
    //vector<TString> m_MassCutColors; // Can eventually use for plots (maybe...)
  vector<pair<TString,TString>> m_FitCuts; // for fits (any chi^2 pretty much)
  vector<pair<TString,TString>> m_ExtraCuts; // for whatever else
  // Below Contains < Variable , VariableCut >
  vector<pair<TString,TString>> m_ShowerCuts; // for basic charged track cuts
  vector<pair<TString,TString>> m_TrackCuts; 
  vector<pair<TString,TString>> m_ElectronCuts; 
  vector<pair<TString,TString>> m_MuonCuts; 
  vector<pair<TString,TString>> m_PionCuts; 
  vector<pair<TString,TString>> m_ProtonCuts; 
  vector<pair<TString,TString>> m_KaonCuts; 
  vector<pair<TString,TString>> m_Pi0Cuts; 
  // Edited Cut Placeholders
  vector<pair<TString,TString>> m_EditedMassBounds; // < "Mass/Var[i]" , "Min_Max" >
  vector<pair<TString,TString>> m_EditedCutBounds;  // <    "Var[i]"   , "Min_Max" >

  void clearCuts(){
    // Intermediate State Set Cuts
    m_MassCuts1.clear();
    m_MassCuts2.clear();
    // General Event Cuts
    m_SetCuts.clear();
    m_FitCuts.clear();
    m_ExtraCuts.clear();
    m_ShowerCuts.clear();
    m_TrackCuts.clear();
    // Particle Based Cuts
    m_ElectronCuts.clear();
    m_MuonCuts.clear();
    m_PionCuts.clear();
    m_Pi0Cuts.clear();
    m_ProtonCuts.clear();
    m_KaonCuts.clear();
    return;
  }
  //Useful for printing outputs
  TString padPairVec( pair<TString,TString> pairvector, int spacing1, TString RLC1,int spacing2, TString RLC2){
    int space1;
    int space2;
    if(pairvector.first.Length()> spacing1){ space1 = pairvector.first.Length()+2;}
      else{ space1 = spacing1;}
    if(pairvector.second.Length()> spacing2){ space2 = pairvector.second.Length()+2;}
      else{ space2 = spacing2;}
    return FSString::padTString(pairvector.first,space1,RLC1)+" "+FSString::padTString(pairvector.second,space2,RLC2);
  }

public:

  // ***************************************************************
  // MAKING FUNCTIONS THAT ARE GENERALLY USEFUL
  // ***************************************************************
  // Simple function to check for NULL cuts so they don't spam the output when applied.
  // Using the noCut set from BAHUtilities to be consitent with BAHCuts
  static bool checkCut(TString cut){
    if(cut.Contains(noCut)||cut==("")){ return false;}
    else{ return true;}
  }
  //-----------------------------------------------------------------
  static TString getCutMin(bool cut, TString Variable,  TString Min){
    TString tempstr;
    if(!cut){ tempstr = "(7==7)";}
    if(cut){  tempstr = "("+Min+"<"+Variable+")";}
    return tempstr;
  }
  static TString getCutMax(bool cut, TString Variable,  TString Max){
    TString tempstr;
    if(!cut){tempstr = "(7==7)";}
    if(cut){ tempstr = "("+Variable+"<"+Max+")";}
    return tempstr;
  }
  // Main cut getter that takes into account any situation  ("","") and ("0.0","0,0") return (7==7)
  static TString getCutMinMax(bool cut, TString Variable, pair<TString,TString> MinMax){
    TString tempstr;
    if((MinMax.first=="")||(MinMax.second=="")){
      cout << "===================" << endl;
      cout << "= BAD MINMAX INPUT=" << endl;
      cout << "===== NO CUT ======" << endl;
      cout << "===================" << endl;
      return "(7==7)";
    }
    double min = MinMax.first.TString::Atof();
    double max = MinMax.second.TString::Atof();
    if(!cut){ tempstr = "(7==7)";}
    if(cut){  
      if((fabs(min)>0.0000001)&&(fabs(max)>0.000001)){
        tempstr = " ("+getCutMin(1,Variable,MinMax.first)+"&&"+getCutMax(1,Variable,MinMax.second)+") ";
      }
      //
      if((fabs(min)<0.0000001)&&(fabs(max)>0.0000001)){
        tempstr = " ("+getCutMax(1,Variable,MinMax.second)+") ";
      }
      //
      if((fabs(min)>0.0000001)&&(fabs(max)<0.0000001)){
        tempstr = " ("+getCutMin(1,Variable,MinMax.first)+") ";
      }
      //
      if((fabs(min)<0.0000001)&&(fabs(max)<0.0000001)){
        tempstr = " ((7==7)) ";
      }
    }
    return tempstr;
  }
  // ***************************************************************
  // ***************************************************************
  //-----------------------------------------------------------------
  // Can set/replace the bounds for mass cuts 
  // Should be used after the class/cuts/final-states have been defined.
  //void editMassBound(TString particle, pair<TString,TString> bounds){
  //  m_EditedMassBounds.push_back(make_pair(particle,bounds.first+"_"+bounds.second));
  //}
  //-----------------------------------------------------------------
  // Gets the MinMax of cuts applied to intermediate resonances
  static pair<TString,TString> getMassBound(int CutVersion, TString Set, TString particle){
    //vector<TString> dummy;
    // Checking for an edited Mass bounds
    //if(m_EditedMassBounds.size()<1){ 
    //  for( int i=0 ; i < m_EditedMassBounds.size(); i++ ){
    //    if(m_EditedMassBounds[i].first==particle){
    //      dummy = FSString::parseTString(m_EditedMassBounds[i].second,"_");
    //      return make_pair(dummy[0],dummy[1]); 
    //    }
    //  }
    //}
    //if(particle=="XcJ"){return make_pair("3.3","3.6");}
    if(Set=="gpp"){
      if(particle=="Xc0"){  return make_pair("3.39","3.45");}
      if(particle=="Xc1"){  return make_pair("0.00","0.00");}
      if(particle=="Xc2"){  return make_pair("3.55","3.565");}
    }
    if(particle=="Xc0"){  return make_pair("3.38" ,"3.47");}
    if(Set!="gpp"&&Set!="gkk"){if(particle=="Xc1"){  return make_pair("3.495","3.54");}}
    if(particle=="Xc2"){  return make_pair("3.54" ,"3.59");}
    //if(particle=="Tau"){  return make_pair("1.73686","1.81686");}   // Initial Strict Cut Region
    if(particle=="Tau"){  return make_pair("1.7","1.9");}   // Looser Cut to avoid systematic error concerns
    //if(particle=="Tau"){  return make_pair("1.6","2.0");}   // Loose Cut region to fit/optimize over
    if(particle=="NarrowTau"){  return make_pair("1.6","2.0");}   // Loose Cut region to fit over
    if(particle=="Jpsi"){ return make_pair("3.05"  ,"3.15");}
    if(particle=="MassXcJ"){ 
      //if(Set=="gkk"){ return make_pair("3.30","3.60"); }
      //if(Set=="gpp"){ return make_pair("3.30","3.60"); }
      //if(Set=="gPP"){ return make_pair("3.30","3.60"); }
      //if(Set=="gPP"){ return make_pair("3.48","3.525");} /// Only selecting Xc1
    }
    if(particle=="MassJpsi"){
      if(Set=="eepp"){ return make_pair("2.8"  ,"3.20"); } 
      if(Set=="mmpp"){ return make_pair("3.0"  ,"3.20"); }
    }
    if(Set=="etgpp"){return make_pair("1.0"  ,"3.15"); }
    cout << "================" << endl;
    cout << "==  BAD MASS  ==" << endl;
    cout << "================" << endl;
    return make_pair("0.0","0.0");
  }
  //-----------------------------------------------------------------
  // Gets the MinMax of Cuts based on variable and particle type
  //   Use getTagfromTeX from BAHStrings for label references, Should be consistent
  //   Use Contains so the tag can include the charge if needed or not
  static pair<TString,TString> getMinMaxBounds( TString Set, int CutVersion, TString VariableTag, bool printErrors=false){ // May need to make this Set dependant as well...
    //===================== Cut Version 1 ======================================================
    //SPACEstr(" Using Cut Criteria 1 ");
    if(CutVersion==1){  // Deciding to cut out Endcaps of muon/pion
      if(Set=="gtm"||Set=="get"||Set=="gep"||Set=="gepp"){
        //+++++++++++++++++++++++++++++++
        // General Cuts 
        //if(VariableTag.Contains("VChi2")){       return make_pair("0.0"   ,"15.0");} // 'Optimised' (atm...) Vertex cut 
        if(VariableTag.Contains("EMCExtra")&&(Set.Contains("gep"))){    return make_pair("0.0","0.20"); }
        if(VariableTag.Contains("EMCExtra")&&(!Set.Contains("gep"))){   return make_pair("0.0","0.15"); }
        //+++++++++++++++++++++++++++++++
        // For energetic leptons radiating out photons 
        if(Set=="gtm"){
          if(VariableTag.Contains("COSgV.mu")){return make_pair("0.0","0.90"); }
          if(VariableTag.Contains("COSgV.e")){ return make_pair("0.0","0.90"); }
        }
        //if(VariableTag.Contains("COSgV.mu")&&Set=="gtm"){return make_pair("0.0","0.70"); }
        if(VariableTag.Contains("COSgV.e")&&Set=="get"){ return make_pair("0.0","0.90"); }
        // ++++++++ Neutral Pion Cuts +++++++++++++++++++++++++++++++ 
        if((VariableTag.Contains("ShDangPi0"))){  return make_pair("10.0" ,"0.0");  }   // Cut on both pi0 photons
        // ++++++++ Photon Cuts +++++++++++++++++++++++++++++++  
        if((VariableTag.Contains("ShDang"))&&(Set!="gepp")){  return make_pair("10.0"  ,"0.0"); }   // 1photon ShDang cut
        if((VariableTag.Contains("ShDang"))&&(Set=="gepp")){  return make_pair("10.0" ,"0.0");  }   // 3photon ShDang cut  
        //if((VariableTag.Contains("LogShPi0Pull"))){ return make_pair("3.9","0.0");  }  // Just for Drawing
        //if((VariableTag.Contains("ShPi0Pull"))){  return make_pair("8000","0.0");  }
        // ++++++++ Electron Cuts +++++++++++++++++++++++++++++++ 
        if(VariableTag.Contains("TkEP.e")){       return make_pair("0.925"  ,"1.04"); }
        if(VariableTag.Contains("TkEMCProb.e")){  return make_pair("0.001" ,"0.0");}
        if(VariableTag.Contains("TkProbemcR.e")){ return make_pair("0.8"   ,"0.0");}  // .98 probably best but need verify
        if(VariableTag.Contains("TkCosTheta.e")){ return make_pair("-0.8" ,"0.8"); } 
        // ++++++++ Muon Cuts +++++++++++++++++++++++++++++++ 
        if(VariableTag.Contains("TkCosTheta.mu")){ return make_pair("-0.8" ,"0.8"); } 
        if(VariableTag.Contains("TkEemc.mu")){     return make_pair("0.125","0.275"); }
        if(VariableTag.Contains("TkEMCProb.mu")){  return make_pair("0.001","0.0"); }
        if(VariableTag.Contains("TkEMCProb.MuvE")){return make_pair("0.001","0.0"); }
        if(VariableTag.Contains("TkEMCProb.MuvK")){return make_pair("0.001","0.0"); }
        // ++++++++ Charged Pion Cuts +++++++++++++++++++++++++++++++ 
        if(VariableTag.Contains("TkEP.pi")){      return make_pair( "0.00" ,"0.8"); }
        if(VariableTag.Contains("TkCosTheta.pi")){return make_pair("-0.8" ,"0.8"); } 
        if(VariableTag.Contains("TkProb.PivE")){return make_pair("0.001"   ,"0.0"); }
        if(VariableTag.Contains("TkProb.PivK")){return make_pair("0.001"   ,"0.0"); }
        if(VariableTag.Contains("TkProb.PivP")){return make_pair("0.001"   ,"0.0"); }
        // ++++++++ Specific Momentum Cuts on Leptons ++++++++++++++++++++++++++++++
        //if(Set=="gtm"&&VariableTag.Contains("MOM.mu")){    return make_pair("1.18"  ,"0.0"); }
        //if(Set=="get"&&VariableTag.Contains("MOM.e")){     return make_pair("1.18"  ,"0.0"); }
        // ++++++++ Extra shit to check++++++++++++++++++++++++++++++
        // Only 1 neutrino in signal so fit to 0 Missing mass if tau doesnt decay leptonically.
        if(Set=="gepp"||Set=="gep"){
          if(VariableTag.Contains("Chi2DOF")){  return make_pair("0.0"   ,"10.0");} 
        }
        //if(VariableTag.Contains("Chi2DOF")&&(Set"gep")){  return make_pair("0.0"   ,"10.0");} 
        if(Set=="gepp"){
          if(VariableTag=="RhoMassDiff"){return make_pair("0.0","0.2"); }
          if(VariableTag=="RhoMass"){return make_pair("0.57 "  ,"0.97");}
          //if(VariableTag=="VisMass"){return make_pair("0.0"    ,"0.0"); }
          //if(VariableTag=="Emiss"){  return make_pair("0.45"   ,"0.0"); }
          //if(VariableTag=="Pmiss"){  return make_pair("0.45"   ,"0.0"); }
          //if(VariableTag=="EPmiss"){ return make_pair("0.21"   ,"0.0"); }
        }
      }
      if(Set=="gpp"||Set=="gPP"||Set=="gkk"||Set=="eepp"||Set=="mmpp"){
        //+++++++++++++++++++++++++++++++
        // General CutsMissingMass2
        if(Set=="gPP"){
          if(VariableTag.Contains("Chi2DOF")){     return make_pair("0.0" ,"9.0");  }
          if(VariableTag.Contains("ShDang")){      return make_pair("10.0" ,"0.0"); } 
          //if(VariableTag.Contains("MM2")){     return make_pair("-0.02" ,"0.0");    }
          if(VariableTag.Contains("TkCosTheta.p")){return make_pair("-0.8" ,"0.8"); } 
          if(VariableTag=="TkProb.P"){             return make_pair("0.05" ,"0.0");}
          //if(VariableTag.Contains("TkProb.P")){    return make_pair("0.001","0.0");}
          if(VariableTag.Contains("TkMucDepth.p")){return make_pair("0.0" ,"35.0"); } 
          if(VariableTag.Contains("COS.pmVg")){    return make_pair("0.0" ,"-0.92"); } 
        }
        if(Set=="gpp"){
          //+++++++++++++++++++++++++++++++
          // Charged Pion Cuts
          if(VariableTag.Contains("Chi2DOF")){    return make_pair("0.0" ,"9.0");    }
          //if(VariableTag.Contains("TkEP.pi")){    return make_pair("0.0" ,"0.7");    }
          if(VariableTag.Contains("TkMucDepth.pi")){return make_pair("0.0" ,"35.0"); } 
          if(VariableTag.Contains("TkEMCProb.pi")){  return make_pair("0.2" ,"0.0"); }
          if(VariableTag.Contains("TkEMCProb.PivK")){return make_pair("0.001"   ,"0.0");}
          //if(VariableTag.Contains("TkProb.PivE")){return make_pair("0.001"   ,"0.0");}
          //if(VariableTag.Contains("TkProb.PivK")){return make_pair("0.001"   ,"0.0");}
          //if(VariableTag.Contains("TkProb.PivP")){return make_pair("0.001"   ,"0.0");}
          if(VariableTag.Contains("TkMucDepth.pi")){return make_pair("0.0" ,"35.0"); } 
          if(VariableTag.Contains("COS.pmVg")){    return make_pair("-0.983" ,"0.0"); } 
        }
        if(Set=="gkk"){
          if(VariableTag=="TkProb.K"){            return make_pair("0.05" ,"0.0");}
          //if(VariableTag.Contains("VChi2")){      return make_pair("0.0"   ,"15.0");} //  Vertex cut
          if(VariableTag.Contains("Chi2DOF")){    return make_pair("0.0"  ,"7.0");}
          if(VariableTag.Contains("TkProb.KvPi")){return make_pair("0.001","0.0"); }
          if(VariableTag.Contains("ShDang")){     return make_pair("10.0" ,"0.0"); } 
          //if(VariableTag=="MOM.KK"){              return make_pair("0.09" ,"0.0"); }//0.34
          if(VariableTag.Contains("COS.pmVg")){    return make_pair("0.0" ,"-0.92"); } 
          if(VariableTag=="MOM.K"){     return make_pair("1.5"  ,"0.0"); }// Put After MOM.KK to be safe
        }
        if(Set=="gpp"||Set=="gPP"||Set=="gkk"){
          if(VariableTag.Contains("ShDang")){  return make_pair("25.0","0.0"); } 
        }
        if(VariableTag.Contains("ShDang")){      return make_pair("15.0","0.0"); } // Standard ShDang cut [tightest I could find]
        //+++++++++++++++++++++++++++++++
      }
    } 
    //===================== Cut Version 2 ======================================================
    if(CutVersion==2){  // Deciding to cut out Endcaps of muon/pion/electrons and using PID to recheck
      if(Set=="gtm"||Set=="get"||Set=="gep"||Set=="gepp"){
        //+++++++++++++++++++++++++++++++
        // General Cuts
        if(Set!="gepp"&&VariableTag.Contains("ShDang")){ return make_pair("15.0","0.0"); } // Standard ShDang cut [tightest I could find]
        if(VariableTag.Contains("EMCExtra")){     return make_pair("0.0"   ,"0.2"); }// EMCExtras cut
        // Removing Endcaps one-by-one to see the effects
        if(VariableTag.Contains("TkCosTheta.e")){ return make_pair("-0.8" ,"0.8"); }
        if(VariableTag.Contains("TkCosTheta.mu")){return make_pair("-0.8" ,"0.8"); }
        if(VariableTag.Contains("TkCosTheta.pi")){return make_pair("-0.8" ,"0.8"); }
        //+++++++++++++++++++++++++++++++
        // Electron Cuts
        if(VariableTag.Contains("TkEP.e")){       return make_pair("0.8"  ,"0.0"); }
        if(VariableTag.Contains("TkEMCProb.e")){  return make_pair("0.001" ,"0.0");}
        if(VariableTag.Contains("TkProbemcR.e")){ return make_pair("0.98"   ,"0.0");}
        //+++++++++++++++++++++++++++++++ 
        // Muon Cuts 
        if(VariableTag.Contains("TkEemc.mu")){     return make_pair("0.1"  ,"0.3"); }
        if(VariableTag.Contains("TkEMCProb.mu")){  return make_pair("0.001" ,"0.0"); }
        if(VariableTag.Contains("TkEMCProb.MuvE")){return make_pair("0.001" ,"0.0"); }
        if(VariableTag.Contains("TkEMCProb.MuvK")){return make_pair("0.001" ,"0.0"); }
        //+++++++++++++++++++++++++++++++ 
        // Charged Pion Cuts 
        if(VariableTag.Contains("TkEP.pi")){    return make_pair("0.00"    ,"0.8"); }
        if(VariableTag.Contains("TkProb.PivE")){return make_pair("0.001"   ,"0.0"); }
        if(VariableTag.Contains("TkProb.PivK")){return make_pair("0.001"   ,"0.0"); }
        if(VariableTag.Contains("TkProb.PivP")){return make_pair("0.001"   ,"0.0"); }
      }
      //if(VariableTag.Contains("TkEemc.mu")){   return make_pair("0.1","0.3"); }
      //if(VariableTag.Contains("TkMUC.mu")){    return make_pair("0.0","40.0"); }
    }
    //===========================================================================================
    //+++++++++++++++++++++++++++++++
    //+++++++ Above should be tighter than below, return the looser value if skips 1 or more criteria version
    //+++++++++++++++++++++++++++++++
    if(true){
      // Basic Track Cuts
      if(VariableTag.Contains("TkRVtx")){      return make_pair("-1.0"  ,"1.0"); } // Should always apply on tracks
      if(VariableTag.Contains("TkZVtx")){      return make_pair("-10.0" ,"10.0");} // Should always apply on tracks
      if(VariableTag.Contains("TkCosTheta")){  return make_pair("-0.93" ,"0.93");} // Should always apply on tracks
      //+++++++++++++++++++++++++++++++
      //++++  Set Dependant Cuts
      //+++++++++++++++++++++++++++++++
      // General Cuts
      if(VariableTag.Contains("NTracks")){     return make_pair("1.6"   ,"2.4");}  // Should generally apply
      //if(VariableTag.Contains("VChi2")){       return make_pair("0.0"   ,"25.0");} // Loose Vertex cut
      // Generally Accepted Particle Cuts
      if(VariableTag.Contains("EMCExtra")){    return make_pair("0.0"   ,"0.0"); }// Loose EMCExtras cut
      if(VariableTag.Contains("ShDang")){      return make_pair("10.0"  ,"0.0"); } // Loose ShDang cut 
      // Basic Track Cuts
      if(VariableTag.Contains("TkEP.pi")){     return make_pair("0.0" ,"0.8"); }
      //if(VariableTag.Contains("TkEP.e")){      return make_pair("0.8" ,"1.2"); }
      // Pi0 Cuts  
      //if(Set=="gtm"||Set=="get"||Set=="gep"||Set=="gpp"||Set=="gPP"){       // No pi0s if not gepp
      //  if(VariableTag.Contains("NPi0s")){       return make_pair("0.0"   ,"0.5");}  
      //}
      //if(Set=="gepp"){               // At least 1 pi0
      //  if(VariableTag.Contains("NPi0s")){       return make_pair("0.5"   ,"0.0");}  
      //}
      //if(Set=="eepp"||Set=="mmpp"){  // At least 2 pi0
        //f(VariableTag.Contains("NPi0s")){       return make_pair("1.5"   ,"0.0");}  
      //}
    }
    //+++++++++++++++++++++++++++++++
    // FOR CHECKING ODD INCMC Behaviors
    // Meant more for loading into a cut for the FSvector loaded into the histogram.
    //+++++++++++++++++++++++++++++++
    if(VariableTag.Contains("WeirdCos")){return make_pair("0.80","0.1");} // To check specific empty/boosted spot in e/mu cos(theta) in INCMC
    if(VariableTag.Contains("EndCapCos")){return make_pair("0.80","0.0");} // To check specific empty/boosted spot in e/mu cos(theta) in INCMC
    if(VariableTag.Contains("BadMu")){return make_pair("0.0","0.1");}  // To check Low Probability muon candidates in INCMC
    //+++++++++++++++++++++++++++++++
    //+++++++++++++++++++++++++++++++
    if(printErrors){
    cout << "====================" << endl;
    cout << " input: "+VariableTag << endl;
    cout << "== BAD VariableTag =" << endl;
    cout << "=== so  NO CUT =====" << endl;
    cout << "====================" << endl;
    }
    return make_pair("0.0","0.0");  // Plotting nothing, May cause error in mishap cuts :)
  }
  // ***************************************************************
  // MAYBE can have 
  // ***************************************************************
  vector<pair<TString,TString>> applySetCuts(TString Set, vector<pair<TString,TString>> temppair, int CutVersion = 0){
    // Setup
    TString EMCex=getEMCExtra(Set);
    //if(!CutVersion){ 
    temppair.push_back(make_pair("NTracks"  ,getCutMinMax(1,"NTracks",getMinMaxBounds(Set,CutVersion,"NTracks"))));
    temppair.push_back(make_pair("NPi0s"    ,getCutMinMax(1,"NPi0s"  ,getMinMaxBounds(Set,CutVersion,"NPi0s"))));
    temppair.push_back(make_pair(EMCex      ,getCutMinMax(1,EMCex    ,getMinMaxBounds(Set,CutVersion,"EMCExtra"))));
    temppair.push_back(make_pair("MissingMass2",getCutMinMax(1,"MissingMass2",getMinMaxBounds(Set,CutVersion,"MM2"))));
    temppair.push_back(make_pair("COSINE(1;3)" ,getCutMinMax(1,"COSINE(1;3)",getMinMaxBounds(Set,CutVersion,"COSgV.e")))); // Energetic electron cut
    temppair.push_back(make_pair("COSINE(2;3)" ,getCutMinMax(1,"COSINE(2;3)",getMinMaxBounds(Set,CutVersion,"COSgV.mu")))); // Energetic muon cut
    if(Set=="gepp"){
      temppair.push_back(make_pair("abs(MASS([pi],[pi0])-0.770)",getCutMinMax(1,"abs(MASS([pi],[pi0])-0.770)",getMinMaxBounds(Set,CutVersion,"RhoMassDiff"))));
    }
    if(Set=="gkk"||Set=="gpp"){
      //temppair.push_back(make_pair("MOMENTUM(2,3)" ,getCutMinMax(1,"MOMENTUM(2,3)",getMinMaxBounds(Set,CutVersion,"MOM.KK"))));
      temppair.push_back(make_pair("COSINE(2,3;1)" ,getCutMinMax(1,"COSINE(2,3;1)",getMinMaxBounds(Set,CutVersion,"COS.pmVg"))));
    }
    if(Set=="gPP"){
      temppair.push_back(make_pair("COSINE(1,2;3)" ,getCutMinMax(1,"COSINE(1,2;3)",getMinMaxBounds(Set,CutVersion,"COS.pmVg"))));
    }
    //}
    //if(CutVersion){
    //}
    return temppair;
  }
  // ***************************************************************
  vector<pair<TString,TString>> applyTrackCuts(TString Set, TString Particle, vector<pair<TString,TString>> temppair, int CutVersion = 0){
    TString part = "P"+Particle;
    //if(!CutVersion){ // Baseline Tracking Cuts
      temppair.push_back(    make_pair("TkRVtx"+part,getCutMinMax(1,"TkRVtx"+part    ,getMinMaxBounds(Set,CutVersion,"TkRVtx")  ) ) );
      temppair.push_back(    make_pair("TkZVtx"+part,getCutMinMax(1,"TkZVtx"+part    ,getMinMaxBounds(Set,CutVersion,"TkZVtx")  ) ) );
      temppair.push_back(make_pair("TkCosTheta"+part,getCutMinMax(1,"TkCosTheta"+part,getMinMaxBounds(Set,CutVersion,"TkCosTheta"))));
    //}
    //if(CutVersion){
    //}
    return temppair;
  }
  vector<pair<TString,TString>> applyShowerCuts(TString Set, TString Particle, vector<pair<TString,TString>> temppair, int CutVersion = 0){
    TString part = "P"+Particle;
    //if(!CutVersion){ // Baseline Tracking Cuts
      temppair.push_back(make_pair("ShDang"+part    ,getCutMinMax(1,"ShDang"+part,getMinMaxBounds(Set,CutVersion,"ShDang")) ));
      //temppair.push_back(make_pair("ShE925"+part    ,m_noCut ));
      temppair.push_back(make_pair("ShCosTheta"+part,m_noCut) );
      temppair.push_back(make_pair("ShEnergy"+part  ,m_noCut) );
      //temppair.push_back(make_pair("ShPi0Pull"+part,getCutMinMax(1,"ShPi0Pull"+part,getMinMaxBounds(Set,CutVersion,"ShPi0Pull")) ));
      //temppair.push_back(make_pair("ShTime"+part    ,m_noCut) );
      //temppair.push_back(make_pair("ShMatch"+part   ,m_noCut) );
    //}
    //if(CutVersion){
    //}
    return temppair;
  }
  vector<pair<TString,TString>> applyElectronCuts(TString Set, TString Particle, vector<pair<TString,TString>> temppair, int CutVersion = 0){
    TString part = "P"+Particle;
    TString ProbRatio   = getEProbR(0,Particle);
    TString ProbRatioEMC= getEProbR(1,Particle);
    TString MDCchi = "TkchiDedx";
    //if(!CutVersion){ // Baseline Tracking Cuts
      temppair.push_back(make_pair("TkCosTheta"+part  ,getCutMinMax(1,"TkCosTheta"+part,getMinMaxBounds(Set,CutVersion,"TkCosTheta.e")) ));
      temppair.push_back(make_pair("TkEP"+part        ,getCutMinMax(1,"TkEP"+part       ,getMinMaxBounds(Set,CutVersion,"TkEP.e"))  ));
      temppair.push_back(make_pair("TkMucDepth"+part  ,m_noCut));
      //temppair.push_back(make_pair("TkProbE"+part     ,m_noCut));
      temppair.push_back(make_pair("Tklatmoment"+part ,m_noCut));
      temppair.push_back(make_pair("MOMENTUM("+Particle+")" ,getCutMinMax(1,"MOMENTUM("+Particle+")",getMinMaxBounds(Set,CutVersion,"MOM.e"))));
    //}
    if((Set=="gtm"||Set=="get"||Set=="gep"||Set=="gepp")&&CutVersion==1){  // May apply 0.8 cut on TkCosTheta for electrons
      temppair.push_back(make_pair("TkProbemcE"+part  ,getCutMinMax(1,"TkProbemcE"+part ,getMinMaxBounds(Set,CutVersion,"TkEMCProb.e")) ));
      temppair.push_back(make_pair(ProbRatioEMC       ,getCutMinMax(1,ProbRatioEMC      ,getMinMaxBounds(Set,CutVersion,"TkProbemcR.e"))));
      //temppair.push_back(make_pair("TkCosTheta"+part,getCutMinMax(1,"TkCosTheta"+part,getMinMaxBounds(Set,CutVersion,"TkCosTheta.e")  ) ) );
    }
    return temppair;
  }
  vector<pair<TString,TString>> applyMuonCuts(TString Set, TString Particle, vector<pair<TString,TString>> temppair, int CutVersion = 0){
    TString part = "P"+Particle;
    TString ProbRatio   = "(TkProbE"+part+")/(TkProbE"+part+"+TkProbPi"+part+"+TkProbK"+part+")";
    TString ProbRatioEMC= "(TkProbemcE"+part+")/(TkProbemcE"+part+"+TkProbemcPi"+part+"+TkProbemcK"+part+")";
    TString MDCchi = "TkchiDedx";
    //if(!CutVersion){ // Baseline Tracking Cuts    
      temppair.push_back(make_pair("TkCosTheta"+part         ,getCutMinMax(1,"TkCosTheta"+part,getMinMaxBounds(Set,CutVersion,"TkCosTheta.mu")) ));
      //temppair.push_back(make_pair("TkEP"+part              ,getCutMinMax(1,"TkEP"+part        ,getMinMaxBounds(Set,CutVersion,"TkEP.mu")) ));
      temppair.push_back(make_pair(getTkEemc(Particle)       ,getCutMinMax(1,getTkEemc(Particle),getMinMaxBounds(Set,CutVersion,"TkEemc.mu"))   ));
      temppair.push_back(make_pair("TkMucDepth"+part        ,m_noCut));
      temppair.push_back(make_pair("TkProbMu"+part          ,m_noCut) );
      temppair.push_back(make_pair("Tklatmoment"+part       ,m_noCut));
      temppair.push_back(make_pair("MOMENTUM("+Particle+")" ,getCutMinMax(1,"MOMENTUM("+Particle+")",getMinMaxBounds(Set,CutVersion,"MOM.mu"))));
    //}
    if((Set=="gtm"||Set=="get"||Set=="gep"||Set=="gepp")&&CutVersion==1){
      temppair.push_back(make_pair("TkProbemcMu"+part        ,getCutMinMax(1,"TkProbemcMu"+part ,getMinMaxBounds(Set,CutVersion,"TkEMCProb.mu"))));
      temppair.push_back(make_pair(getProbVS(1,"Mu","E",Particle)  ,getProbVScut(1,"Mu","E",Particle)  ));
      temppair.push_back(make_pair(getProbVS(1,"Mu","K",Particle)  ,getProbVScut(1,"Mu","K",Particle)  ));
      //temppair.push_back(make_pair("TkCosTheta"+part,getCutMin(1,"ShDang"+part,getBounds(CutVersion,0,"ShDang")  ) ) );
    }
    return temppair;
  }
  vector<pair<TString,TString>> applyPionCuts(TString Set, TString Particle, vector<pair<TString,TString>> temppair, int CutVersion = 0){
    TString part = "P"+Particle;
    TString Eemc ="(TkEP"+part+")*("+m_MOM+"("+Particle+"))";
    TString MDCchi = "TkchiDedx";
    //if(!CutVersion){ // Baseline Tracking Cuts         getProbVS(1,TkName,"E",Tk)
      //temppair.push_back(make_pair("TkProbPi"+part        ,getCutMinMax(0,"TkProbPi"+part ,getMinMaxBounds(Set,CutVersion,"TkProb.pi")) ));
      //temppair.push_back(make_pair(getProbVS(0,"Pi","E",Particle)  ,getProbVScut(0,"Pi","E",Particle)  ));
      //temppair.push_back(make_pair(getProbVS(0,"Pi","K",Particle)  ,getProbVScut(0,"Pi","K",Particle)  ));
      //temppair.push_back(make_pair(getProbVS(0,"Pi","P",Particle)  ,getProbVScut(0,"Pi","P",Particle)  ));
      if(Set=="gtm"||Set=="get"||Set=="gep"||Set=="gepp"){
        temppair.push_back(make_pair("TkCosTheta"+part,getCutMinMax(1,"TkCosTheta"+part,getMinMaxBounds(Set,CutVersion,"TkCosTheta.pi"))));
      }
      temppair.push_back(make_pair("TkEP"+part              ,getCutMinMax(1,"TkEP"+part,getMinMaxBounds(Set,CutVersion,"TkEP.pi")) ));
      temppair.push_back(make_pair( Eemc                    ,m_noCut));//getCutMinMax(1, Eemc      ,getMinMaxBounds(Set,CutVersion,"TkE.pi"))  ));
      //temppair.push_back(make_pair("TkMucDepth"+part             ,m_noCut));
      //temppair.push_back(make_pair("TkProbPi"+part               ,m_noCut));
      //temppair.push_back(make_pair("Tklatmoment"+part            ,m_noCut));
      //temppair.push_back(make_pair(MDCchi+"E"+part                     ,m_noCut));
      //temppair.push_back(make_pair(MDCchi+"Mu"+part                    ,m_noCut));
      //temppair.push_back(make_pair(MDCchi+"E"+part+"+"+MDCchi+"Mu"+part,m_noCut));
    //} 
    if(Set=="gpp"&&CutVersion==1){  
      temppair.push_back(make_pair("TkProbemcPi"+part ,getCutMinMax(1,"TkProbemcPi"+part ,getMinMaxBounds(Set,CutVersion,"TkEMCProb.pi"))));
      temppair.push_back(make_pair("TkMucDepth"+part  ,getCutMinMax(1,"TkMucDepth"+part,getMinMaxBounds(Set,CutVersion,"TkMucDepth")) ));
      temppair.push_back(make_pair(getProbVS(1,"Pi","K",Particle)  ,getProbVScut(1,"Pi","K",Particle)  ));
    }
    if((Set=="gep"||Set=="gepp")&&CutVersion==1){  // Here and below, can apply Probability and FS dependant Cuts
      temppair.push_back(make_pair(getProbVS(0,"Pi","E",Particle)  ,getProbVScut(0,"Pi","E",Particle)  ));
      temppair.push_back(make_pair(getProbVS(0,"Pi","K",Particle)  ,getProbVScut(0,"Pi","K",Particle)  ));
      temppair.push_back(make_pair(getProbVS(0,"Pi","P",Particle)  ,getProbVScut(0,"Pi","P",Particle)  ));
    }
    return temppair;
  }
  vector<pair<TString,TString>> applyProtonCuts(TString Set, TString Particle, vector<pair<TString,TString>> temppair, int CutVersion = 0){
    TString part = "P"+Particle;
    TString Eemc ="(TkEP"+part+")*("+m_MOM+"("+Particle+"))";
    //if(!CutVersion){ // Baseline Tracking Cuts         getProbVS(1,TkName,"E",Tk)
      temppair.push_back(make_pair("TkCosTheta"+part,getCutMinMax(1,"TkCosTheta"+part,getMinMaxBounds(Set,CutVersion,"TkCosTheta.p"))));
      temppair.push_back(make_pair("TkEP"+part              ,m_noCut));
      temppair.push_back(make_pair( Eemc                    ,m_noCut));//getCutMinMax(1, Eemc      ,getMinMaxBounds(Set,CutVersion,"TkE.pi"))  ));
      //temppair.push_back(make_pair("TkMucDepth"+part        ,m_noCut));
      //temppair.push_back(make_pair("TkProbPi"+part          ,m_noCut));
    //}
    if((Set=="gPP")&&CutVersion==1){  // May apply 0.8 cut on TkCosTheta for electrons
      temppair.push_back(make_pair("TkMucDepth"+part  ,getCutMinMax(1,"TkMucDepth"+part,getMinMaxBounds(Set,CutVersion,"TkMucDepth")) ));
      //temppair.push_back(make_pair(getProbVS(0,"P","Pi",Particle) ,getProbVScut(0,"P","Pi",Particle)  ));
      //temppair.push_back(make_pair(getProbVS(0,"P","K",Particle)  ,getProbVScut(0,"P","K",Particle)  ));
      temppair.push_back(make_pair("TkProbP"+part     ,getCutMinMax(1,"TkProbP"+part,getMinMaxBounds(Set,CutVersion,"TkProb.P")) ));
    }
    return temppair;
  }
  vector<pair<TString,TString>> applyKaonCuts(TString Set, TString Particle, vector<pair<TString,TString>> temppair, int CutVersion = 0){
    TString part = "P"+Particle;
    TString Eemc ="(TkEP"+part+")*("+m_MOM+"("+Particle+"))";
    //if(!CutVersion){ // Baseline Tracking Cuts         getProbVS(1,TkName,"E",Tk)  m_MOM
    if(Set=="gkk"){
      temppair.push_back(make_pair("TkProbK"+part          ,getCutMinMax(1,"TkProbK"+part       ,getMinMaxBounds(Set,CutVersion,"TkProb.K"))  ));
      temppair.push_back(make_pair(getProbVS(0,"K","Pi",Particle) ,getProbVScut(0,"K","Pi",Particle)  ));
      temppair.push_back(make_pair(m_MOM+"("+Particle+")"  ,getCutMinMax(1,m_MOM+"("+Particle+")",getMinMaxBounds(Set,CutVersion,"MOM.K")) ));
    }
    return temppair;
  }
  vector<pair<TString,TString>> applyPi0Cuts(TString Set, TString Particle, vector<pair<TString,TString>> temppair, int CutVersion = 0){
    TString partA = "P"+Particle+"a";
    TString partB = "P"+Particle+"b";
    temppair.push_back(make_pair("ShDang"+partA    ,getCutMinMax(1,"ShDang"+partA,getMinMaxBounds(Set,CutVersion,"ShDangPi0")) ));
    temppair.push_back(make_pair("ShDang"+partB    ,getCutMinMax(1,"ShDang"+partB,getMinMaxBounds(Set,CutVersion,"ShDangPi0")) ));
    //temppair.push_back(make_pair("ShE925"+part    ,m_noCut ));
    //temppair.push_back(make_pair("ShCosTheta"+part,m_noCut) );
    //temppair.push_back(make_pair("ShEnergy"+part  ,m_noCut) );
    //temppair.push_back(make_pair("ShPi0Pull"+part,getCutMinMax(1,"ShPi0Pull"+part,getMinMaxBounds(Set,CutVersion,"ShPi0Pull")) ));
    //temppair.push_back(make_pair("ShTime"+part    ,m_noCut) );
    //temppair.push_back(make_pair("ShMatch"+part   ,m_noCut) );
    return temppair;
  }
  // ***************************************************************
  // ***************************************************************

  // ***************************************************************
  // FINALLY GOING TO USE THE FUNCTIONS ABOVE FOR OBJECT
  // ***************************************************************
  // declaring constructor
  BAHCuts(BAHDecays DecayInfo, int CutVersion = 1, bool Chi2Fit = false){ // MASS AND FIT CUTS ARE SET HERE 
    clearCuts();
    m_CutVersion = CutVersion;
    TString Set = DecayInfo.getSet();
    m_Set = DecayInfo.getSet();
    TString FS = DecayInfo.getFS();
    TString IS = DecayInfo.getIS();
    ///////////////////////////////////////////////////////////////
    // Set up baseline Resonance Mass Cuts for MASS1 and MASS2 [Defined in BAHDecays] 
    TString  Mass1 = DecayInfo.getMass1Var();  // Typically Main resonance Mass variable (Recoil usually)
    TString  Mass2 = DecayInfo.getMass2Var();  // Typically a secondary resonance Mass variable [ MASS(BES3CMS,...) or MASS(...) ]
    if(IS=="XcJ"){
      m_MassCuts1.push_back(make_pair(Mass1,getCutMinMax(1,DecayInfo.getMass1Var(),getMassBound(CutVersion,Set,"Xc0"))));
      if(!(Set=="gpp"||Set=="gkk")){m_MassCuts1.push_back(make_pair(Mass1,getCutMinMax(1,DecayInfo.getMass1Var(),getMassBound(CutVersion,Set,"Xc1"))));}
      m_MassCuts1.push_back(make_pair(Mass1,getCutMinMax(1,DecayInfo.getMass1Var(),getMassBound(CutVersion,Set,"Xc2"))));
    }
    if(IS=="Jpsi"){
      m_MassCuts1.push_back(make_pair(Mass1,getCutMinMax(1,DecayInfo.getMass1Var(),getMassBound(CutVersion,Set,"Jpsi"))));
    }
    if(IS=="NOTHING"){
      m_MassCuts1.push_back(make_pair(Mass1,getCutMinMax(1,DecayInfo.getMass1Var(),getMassBound(CutVersion,Set,"NO"))));
    }
    ///////////////////////////////////////////////////////////////
    // Secondary  Mass Cut Setup
    if((Set=="gtm")||(Set=="get")||(Set=="gep")||(Set=="gepp")){
      m_MassCuts2.push_back(make_pair(Mass2,getCutMinMax(1,DecayInfo.getMass2Var(),getMassBound(CutVersion,Set,"Tau"))));
    }
    if((Set=="eepp")||(Set=="mmpp")){
      m_MassCuts2.push_back(make_pair(Mass2,getCutMinMax(1,DecayInfo.getMass2Var(),getMassBound(CutVersion,Set,"Mass"+IS))));
    }
    if((Set=="gpp")||(Set=="gPP")||(Set=="gkk")){
      m_MassCuts2.push_back(make_pair(Mass2,getCutMinMax(1,DecayInfo.getMass2Var(),getMassBound(CutVersion,Set,"Mass"+IS))));
    }
    ///////////////////////////////////////////////////////////////
    // Get Additional cut info Based on Final State 
    ///////////////////////////////////////////////////////////////
    // Don't intend to look at stuff off vertex
    m_FitCuts.push_back(make_pair("VChi2",  getCutMinMax(1,"VChi2",  getMinMaxBounds(Set,CutVersion,"VChi2"))));
    // Get Additional cut info Based on Final State 
    if(Set=="gep"||Set=="gepp"||Set=="gpp"||Set=="gPP"||Set=="gkk"||Set=="etgpp"){
      if(Chi2Fit){m_FitCuts.push_back(make_pair("Chi2DOF",getCutMinMax(1,"Chi2DOF",getMinMaxBounds(Set,CutVersion,"Chi2DOF"))));}
    }
    ///////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////
    // Way more Cuts for each type of particle so the setup is done
    // previosly and looped over here. 
    // Cuts are the base cuts and can be more specific above ^^^
    ///////////////////////////////////
    vector<pair<TString,TString>> CutDummy;
    ///////////////////////////////////
    // Loading Set Specific cuts into Set cut vector
    CutDummy = applySetCuts(Set,CutDummy,CutVersion);
    m_SetCuts = CutDummy;
    CutDummy.clear();
    //----------------------------------
    // Loading Track cuts into track cut vector
    for (unsigned int i = 0; i < DecayInfo.getTracks().size(); i++){
      CutDummy = applyTrackCuts(Set,DecayInfo.getTracks()[i].first,CutDummy,CutVersion);
    }
    m_TrackCuts = CutDummy;
    CutDummy.clear();
    //----------------------------------
    // Loading Shower cuts into shower cut vector
    for (unsigned int i = 0; i < DecayInfo.getShowers().size(); i++){
      CutDummy = applyShowerCuts(Set,DecayInfo.getShowers()[i].first,CutDummy,CutVersion);
    }
    m_ShowerCuts = CutDummy;
    CutDummy.clear();
    //----------------------------------
    // Loading Electron cuts into electron cut vector
    for (unsigned int i = 0; i < DecayInfo.getElectrons().size(); i++){
      CutDummy = applyElectronCuts(Set,DecayInfo.getElectrons()[i].first,CutDummy,CutVersion);
    }
    m_ElectronCuts = CutDummy;
    CutDummy.clear();
    //----------------------------------
    // Loading Muon cuts into muon cut vector
    for (unsigned int i = 0; i < DecayInfo.getMuons().size(); i++){
      CutDummy = applyMuonCuts(Set,DecayInfo.getMuons()[i].first,CutDummy,CutVersion);
    }
    m_MuonCuts = CutDummy;
    CutDummy.clear();
    //----------------------------------
    // Loading Pion cuts into pion cut vector
    for (unsigned int i = 0; i < DecayInfo.getPiCs().size(); i++){
      CutDummy = applyPionCuts(Set,DecayInfo.getPiCs()[i].first,CutDummy,CutVersion);
    }
    m_PionCuts = CutDummy;
    CutDummy.clear();
    //----------------------------------
    // Loading proton cuts into proton cut vector
    for (unsigned int i = 0; i < DecayInfo.getProtons().size(); i++){
      CutDummy = applyProtonCuts(Set,DecayInfo.getProtons()[i].first,CutDummy,CutVersion);
    }
    m_ProtonCuts = CutDummy;
    CutDummy.clear();
    //----------------------------------
    for (unsigned int i = 0; i < DecayInfo.getKaons().size(); i++){
      CutDummy = applyKaonCuts(Set,DecayInfo.getKaons()[i].first,CutDummy,CutVersion);
    }
    m_KaonCuts = CutDummy;
    CutDummy.clear();
    //----------------------------------
    for (unsigned int i = 0; i < DecayInfo.getPi0s().size(); i++){
      CutDummy = applyPi0Cuts(Set,DecayInfo.getPi0s()[i].first,CutDummy,CutVersion);
    }
    m_Pi0Cuts = CutDummy;
    CutDummy.clear();
    //----------------------------------
  }
  ///////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////
  // Functions to get relevant cut info
  int getCutVersion(){ return m_CutVersion; }
  bool checkChi2Fit(){ return m_Chi2Fit;    }
  void SetChi2Fit(bool Chi2Fit){ 
    if((!(m_Chi2Fit==Chi2Fit))&&(Chi2Fit)){ 
      m_Chi2Fit = Chi2Fit;  
      // If Chi2Fit Was not previously applied, update and add the Fit Cuts
      // Get Additional cut info Based on Final State 
      if(m_Set=="gep"||m_Set=="gepp"||m_Set=="gpp"||m_Set=="gPP"||m_Set=="gkk"||m_Set=="etgpp"){
        m_FitCuts.push_back(make_pair("Chi2DOF",getCutMinMax(1,"Chi2DOF",getMinMaxBounds(m_Set,m_CutVersion,"Chi2DOF"))));
      }
    }
    else if(!(m_Chi2Fit==Chi2Fit)&&(!Chi2Fit)){ 
      // Get Additional cut info Based on Final State 
      m_Chi2Fit = Chi2Fit;  
      if(m_FitCuts.size()>0){m_FitCuts.clear();}
    }
    else{ cout << "No Chi2Fit Change Applied"<< endl; }
    return;
  }
  // Initial Mass resonance Variables and Cuts
  vector<pair<TString,TString>> getMass1Cuts(){     return m_MassCuts1;}
  // Secondary Mass resonance Variables and Cuts
  vector<pair<TString,TString>> getMass2Cuts(){     return m_MassCuts2;}
  // Initial Mass resonance Variables and Cuts
  vector<pair<TString,TString>> getSetCuts(){       return m_SetCuts;}
  // Fit Variables and Cuts
  vector<pair<TString,TString>> getFitCuts(){       return m_FitCuts;}
  // Base Track Variables and Cuts
  vector<pair<TString,TString>> getTrackCuts(){     return m_TrackCuts;}
  // Shower Variables and Cuts
  vector<pair<TString,TString>> getShowerCuts(){    return m_ShowerCuts;}
  // Charged Particle Variables and Cuts
  vector<pair<TString,TString>> getElectronCuts(){  return m_ElectronCuts;}
  vector<pair<TString,TString>> getMuonCuts(){      return m_MuonCuts;}
  vector<pair<TString,TString>> getChargedPiCuts(){ return m_PionCuts;}
  vector<pair<TString,TString>> getProtonCuts(){    return m_ProtonCuts;}
  vector<pair<TString,TString>> getKaonCuts(){      return m_KaonCuts;}
  vector<pair<TString,TString>> getPi0Cuts(){       return m_Pi0Cuts;}
  //======================================================================================================
  TString getModeMassCuts(TString Set, TString IntermediateDecay1, TString IntermediateDecay2 = ""){
    TString OutputCut1, OutputCut2, FinalOutput;
    //------------------------------------------
    // Check Different 'Set's to get correct mass cuts
    if(Set=="gtm"||Set=="get"||Set=="gep"||Set=="gepp"){
      //------------------------------------------
      if(IntermediateDecay1=="Xc0"     ||IntermediateDecay1=="chi_c0"){ OutputCut1 = m_MassCuts1[0].second;  }
      else if(IntermediateDecay1=="Xc1"||IntermediateDecay1=="chi_c1"){ OutputCut1 = m_MassCuts1[1].second;  }
      else if(IntermediateDecay1=="Xc2"||IntermediateDecay1=="chi_c2"){ OutputCut1 = m_MassCuts1[2].second;  }
      else{ OutputCut1 = ""; }
      //------------------------------------------
      if(IntermediateDecay2=="tau"){  OutputCut2 = m_MassCuts2[0].second;  }
      else{ OutputCut2 = ""; }
      //------------------------------------------
    }
    else{ return noCut;  }   // Too Lazy to add more decay modes
    //------------------------------------------
    // Setting up output properly
    if(OutputCut1!=""&&OutputCut2==""){     FinalOutput = OutputCut1; }
    else if(OutputCut1==""&&OutputCut2!=""){FinalOutput = OutputCut2; }
    else{ FinalOutput = OutputCut1+FSAND+OutputCut2;  }
    //------------------------------------------
    return FinalOutput;
  }
  //======================================================================================================
  // Retrieve the proper combined cut of MC resonance cut and mass cuts (MassCut1+FSAND+MCSignalCut1)||( .... )
  /*
  TString getModeMassMCCuts(TString Set, TString IntermediateDecay1, TString IntermediateDecay2 = ""){
    TString OutputCut1, OutputCut2, FinalOutput;
    //------------------------------------------
    // Check Different 'Set's to get correct mass and MC cuts
    if(Set=="gtm"||Set=="get"||Set=="gep"||Set=="gepp"){
      //------------------------------------------
      if(IntermediateDecay1=="Xc0"     ||IntermediateDecay1=="chi_c0"){ 
        OutputCut1 = m_MassCuts1[0].second;  
      }
      else if(IntermediateDecay1=="Xc1"||IntermediateDecay1=="chi_c1"){ 
        OutputCut1 = m_MassCuts1[1].second;  
      }
      else if(IntermediateDecay1=="Xc2"||IntermediateDecay1=="chi_c2"){
        OutputCut1 = m_MassCuts1[2].second;  
      }
      else{ OutputCut1 = ""; }
      //------------------------------------------
      if(Set=="gtm"||Set=="get"||Set=="gep"||Set=="gepp"){

      }
    }
    */
  //======================================================================================================
  ///////////////////////////////////////////////////////////////
  // Additional Cuts [No need for the vector pair]
  TString getAdditionalCuts(){ return m_AdditionalCuts;}
  void setAdditionalCuts( TString NewCut ){ m_AdditionalCuts = "("+NewCut+")";}
  void addAdditionalCuts( TString NewCut , TString LogicalConnection ){ m_AdditionalCuts = m_AdditionalCuts+LogicalConnection+"("+NewCut+")";}
  ///////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////
  TString getCutStrNonMC(bool IncludeMassCuts){
    TString CutOutput = noCut;
    // Put Tracks at top since annoying to differentiate in Strings. Otherwise, method (looping) described below.
    for(int i=0; i<m_TrackCuts.size();i++){   if(checkCut(m_TrackCuts[i].second))   CutOutput = CutOutput+FSAND+m_TrackCuts[i].second;}
    if(IncludeMassCuts){
      if(m_MassCuts1.size()>1){
        CutOutput = CutOutput +FSAND+ CutsfromCutVec(eraseStrfromVec(reduceCutVecPair(m_MassCuts1,1),noCut),"||");
      }
      if(m_MassCuts2.size()>1){
        CutOutput = CutOutput +FSAND+ CutsfromCutVec(eraseStrfromVec(reduceCutVecPair(m_MassCuts1,1),noCut),"||");
      }
    }
    // Looping through Cut-Pair Vectors, checking the cut (seconds) if its a noCut, and if not adding it to String. 
    for(int i=0; i<m_FitCuts.size();i++){     if(checkCut(m_FitCuts[i].second))     CutOutput = CutOutput+FSAND+m_FitCuts[i].second;}
    for(int i=0; i<m_SetCuts.size();i++){     if(checkCut(m_SetCuts[i].second))     CutOutput = CutOutput+FSAND+m_SetCuts[i].second;}
    for(int i=0; i<m_ShowerCuts.size();i++){  if(checkCut(m_ShowerCuts[i].second))  CutOutput = CutOutput+FSAND+m_ShowerCuts[i].second;}
    for(int i=0; i<m_ElectronCuts.size();i++){if(checkCut(m_ElectronCuts[i].second))CutOutput = CutOutput+FSAND+m_ElectronCuts[i].second;}
    for(int i=0; i<m_MuonCuts.size();i++){    if(checkCut(m_MuonCuts[i].second))    CutOutput = CutOutput+FSAND+m_MuonCuts[i].second;}
    for(int i=0; i<m_PionCuts.size();i++){    if(checkCut(m_PionCuts[i].second))    CutOutput = CutOutput+FSAND+m_PionCuts[i].second;}
    for(int i=0; i<m_ProtonCuts.size();i++){  if(checkCut(m_ProtonCuts[i].second))  CutOutput = CutOutput+FSAND+m_ProtonCuts[i].second;}
    for(int i=0; i<m_KaonCuts.size();i++){    if(checkCut(m_KaonCuts[i].second))    CutOutput = CutOutput+FSAND+m_KaonCuts[i].second;}
    for(int i=0; i<m_Pi0Cuts.size();i++){     if(checkCut(m_Pi0Cuts[i].second))     CutOutput = CutOutput+FSAND+m_Pi0Cuts[i].second;}
    return CutOutput;
  }
  ///////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////
  vector<pair<TString,TString>> getCutsNonMC(bool IncludeMassCuts){
    vector<pair<TString,TString>> CutCollection;
    // Put Tracks at top since annoying to differentiate in Strings. Otherwise, method (looping) described below.
    for(int i=0; i<m_TrackCuts.size();i++){   if(checkCut(m_TrackCuts[i].second))   CutCollection.push_back(m_TrackCuts[i]);}
    if(IncludeMassCuts){
      for(int i=0; i<m_MassCuts1.size();i++){   if(checkCut(m_MassCuts1[i].second))   CutCollection.push_back(m_MassCuts1[i]);}
      if(m_MassCuts2.size()>1){
      for(int i=0; i<m_MassCuts2.size();i++){   if(checkCut(m_MassCuts2[i].second))   CutCollection.push_back(m_MassCuts2[i]);}
      }
    }
    // Looping through Cut-Pair Vectors, checking the cut (seconds) if its a noCut, and if not adding it to vector output. 
    for(int i=0; i<m_FitCuts.size();i++){     if(checkCut(m_FitCuts[i].second))     CutCollection.push_back(m_FitCuts[i]);}
    for(int i=0; i<m_SetCuts.size();i++){     if(checkCut(m_SetCuts[i].second))     CutCollection.push_back(m_SetCuts[i]);}
    for(int i=0; i<m_ShowerCuts.size();i++){  if(checkCut(m_ShowerCuts[i].second))  CutCollection.push_back(m_ShowerCuts[i]);}
    for(int i=0; i<m_ElectronCuts.size();i++){if(checkCut(m_ElectronCuts[i].second))CutCollection.push_back(m_ElectronCuts[i]);}
    for(int i=0; i<m_MuonCuts.size();i++){    if(checkCut(m_MuonCuts[i].second))    CutCollection.push_back(m_MuonCuts[i]);}
    for(int i=0; i<m_PionCuts.size();i++){    if(checkCut(m_PionCuts[i].second))    CutCollection.push_back(m_PionCuts[i]);}
    for(int i=0; i<m_ProtonCuts.size();i++){  if(checkCut(m_ProtonCuts[i].second))  CutCollection.push_back(m_ProtonCuts[i]);}
    for(int i=0; i<m_KaonCuts.size();i++){    if(checkCut(m_KaonCuts[i].second))    CutCollection.push_back(m_KaonCuts[i]);}
    for(int i=0; i<m_Pi0Cuts.size();i++){     if(checkCut(m_Pi0Cuts[i].second))     CutCollection.push_back(m_Pi0Cuts[i]);}
    return CutCollection;
  }
  ///////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////
  vector<pair<TString,TString>> getCutTypeVec(TString VariableType){
    if(VariableType.Contains("Track"))    return m_TrackCuts;
    if(VariableType.Contains("Mass1"))    return m_MassCuts1;
    if(VariableType.Contains("Mass2"))    return m_MassCuts2;
    if(VariableType.Contains("Fit"))      return m_FitCuts;
    if(VariableType.Contains("Set"))      return m_SetCuts;
    if(VariableType.Contains("Shower"))   return m_ShowerCuts;
    if(VariableType.Contains("Electron")) return m_ElectronCuts;
    if(VariableType.Contains("Muon"))     return m_MuonCuts;
    if(VariableType.Contains("Pion"))     return m_PionCuts;
    if(VariableType.Contains("Proton"))   return m_ProtonCuts;
    if(VariableType.Contains("Kaon"))     return m_KaonCuts;
    if(VariableType.Contains("Pi0"))      return m_Pi0Cuts;
    cout << " Bad Type, returning single dummy cut " << endl;
    return {make_pair( "0.0" , "0.0" )};
  }

  ///////////////////////////////////////////////////////////////
  void displayless(){
    cout  <<  "=========================================================="<<endl;
    cout  <<  "      Cuts Applied on "+m_Set << endl;   
    cout  <<  "   Cut Version Used :  " <<  m_CutVersion   << endl;   
    cout  <<  "=========================================================="<<endl;
    printCutVecExcept( m_TrackCuts    ,"(7==7)");
    printCutVecExcept( m_MassCuts1    ,"(7==7)");
    printCutVecExcept( m_MassCuts2    ,"(7==7)");
    printCutVecExcept( m_FitCuts      ,"(7==7)");
    printCutVecExcept( m_SetCuts      ,"(7==7)");
    printCutVecExcept( m_ShowerCuts   ,"(7==7)");
    printCutVecExcept( m_ElectronCuts ,"(7==7)");
    printCutVecExcept( m_MuonCuts     ,"(7==7)");
    printCutVecExcept( m_PionCuts     ,"(7==7)");
    printCutVecExcept( m_ProtonCuts   ,"(7==7)");
    printCutVecExcept( m_KaonCuts     ,"(7==7)");
    printCutVecExcept( m_Pi0Cuts      ,"(7==7)");
    if(BAHCuts::checkCut(m_AdditionalCuts)){
      cout << m_AdditionalCuts << endl;
      THINLINE();
    }     
  }

  
  ///////////////////////////////////////////////////////////////
  // zero-out a cut in one of the cut vectors of variable types.
  void nullifyCut( TString VariableType, TString Variable ){
    if(VariableType.Contains("Added")){
      m_AdditionalCuts     = noCut;
      return;
    }
    vector<pair<TString,TString>> CutVector = getCutTypeVec(VariableType);
    for (unsigned int i = 0; i < CutVector.size(); i++){
      if(checkCut(CutVector[i].second)&&CutVector[i].first.Contains(Variable)){
        if(VariableType.Contains("Track"))    m_TrackCuts[i].second     = noCut;
        if(VariableType.Contains("Mass1"))    m_MassCuts1[i].second     = noCut;
        if(VariableType.Contains("Mass2"))    m_MassCuts2[i].second     = noCut;
        if(VariableType.Contains("Fit"))      m_FitCuts[i].second       = noCut;
        if(VariableType.Contains("Set"))      m_SetCuts[i].second       = noCut;
        if(VariableType.Contains("Shower"))   m_ShowerCuts[i].second    = noCut;
        if(VariableType.Contains("Electron")) m_ElectronCuts[i].second  = noCut;
        if(VariableType.Contains("Muon"))     m_MuonCuts[i].second      = noCut;
        if(VariableType.Contains("Pion"))     m_PionCuts[i].second      = noCut;
        if(VariableType.Contains("Proton"))   m_ProtonCuts[i].second    = noCut;
        if(VariableType.Contains("Kaon"))     m_KaonCuts[i].second      = noCut;
        if(VariableType.Contains("Pi0"))      m_Pi0Cuts[i].second       = noCut;
      }
    }
    return;
  }


  ///////////////////////////////////////////////////////////////
  // zero-out a cut in one of the cut vectors of variable types with cin.
  void nullifyCut(){
    int spacing = 30;
    TString VariableType; 
    TString Variable;
    displayless();
    SPACEin();
    cout << "Type in the Variable Type: " << endl;
    cout << "[Track, Mass1, Mass2, Fit, Set, Shower, Electron, Muon, Pion, Proton, Kaon]" << endl;
    THINLINE();
    cin >> VariableType;
    THINLINE();
    cout << " Type in the Variable to negate : [ List Below ]" << endl;
    THINLINE();
    vector<pair<TString,TString>> CutVector = getCutTypeVec(VariableType);
    for (unsigned int i = 0; i < CutVector.size(); i++){
      if(checkCut(CutVector[i].second)) cout << padPairVec(CutVector[i],spacing,"C",spacing,"C") << endl;
    }
    THINLINE();
    cin >> Variable;
    THINLINE();
    nullifyCut(VariableType,Variable);
    displayless();
    return;
  }



  // display function to print the class data members values based on object
  void display(){
    int spacing = 30;
    cout  <<  "=========================================================="<<endl;
    cout  <<  " "+m_Set+"  Cut Version Used :  " <<  m_CutVersion   << endl;   
    cout  <<  "=========================================================="<<endl;
    cout<<"The Track Variables and Cuts are: "<< endl;   
    for (unsigned int i = 0; i < m_TrackCuts.size(); i++){
      if(checkCut(m_TrackCuts[i].second)) cout << padPairVec(m_TrackCuts[i],spacing,"C",spacing,"C") << endl;
    }
    cout<<"----------------------------------------------------------"<<endl;
    cout<<"The Mass1 Variables and Cuts are: "<< endl;   
    for (unsigned int i = 0; i < m_MassCuts1.size(); i++){
      if(checkCut(m_MassCuts1[i].second)) cout << padPairVec(m_MassCuts1[i],spacing,"C",spacing,"C") << endl;
    }
    cout<<"----------------------------------------------------------"<<endl;
    cout<<"The Mass2 Variables and Cuts are: "<< endl;   
    for (unsigned int i = 0; i < m_MassCuts2.size(); i++){
      if(checkCut(m_MassCuts2[i].second)) cout << padPairVec(m_MassCuts2[i],spacing,"C",spacing,"C") << endl;
    }
    cout<<"----------------------------------------------------------"<<endl;
    cout<<"The Fit Variables and Cuts are: "<< endl;   
    for (unsigned int i = 0; i < m_FitCuts.size(); i++){
      if(checkCut(m_FitCuts[i].second)) cout << padPairVec(m_FitCuts[i],spacing,"C",spacing,"C") << endl;
    }
    cout<<"----------------------------------------------------------"<<endl;
    cout<<"The Set-Specific Variables and Cuts are: "<< endl;   
    for (unsigned int i = 0; i < m_SetCuts.size(); i++){
      if(checkCut(m_SetCuts[i].second)) cout << padPairVec(m_SetCuts[i],spacing,"C",spacing,"C") << endl;
    }
    cout<<"----------------------------------------------------------"<<endl;
    cout<<"The Shower Variables and Cuts are: "<< endl;   
    for (unsigned int i = 0; i < m_ShowerCuts.size(); i++){
      if(checkCut(m_ShowerCuts[i].second)) cout << padPairVec(m_ShowerCuts[i],spacing,"C",spacing,"C") << endl;
    }
    cout<<"----------------------------------------------------------"<<endl;
    cout<<"The Electron Variables and Cuts are: "<< endl;   
    for (unsigned int i = 0; i < m_ElectronCuts.size(); i++){
      if(checkCut(m_ElectronCuts[i].second)) cout << padPairVec(m_ElectronCuts[i],spacing,"C",spacing,"L") << endl;
    }
    cout<<"----------------------------------------------------------"<<endl;
    cout<<"The Muon Variables and Cuts are: "<< endl;   
    for (unsigned int i = 0; i < m_MuonCuts.size(); i++){
      if(checkCut(m_MuonCuts[i].second)) cout << padPairVec(m_MuonCuts[i],spacing,"C",spacing,"L") << endl;
    }
    cout<<"----------------------------------------------------------"<<endl;
    cout<<"The Pion Variables and Cuts are: "<< endl;   
    for (unsigned int i = 0; i < m_PionCuts.size(); i++){
      if(checkCut(m_PionCuts[i].second)) cout << padPairVec(m_PionCuts[i],spacing,"C",spacing,"L") << endl;
    }
    cout<<"----------------------------------------------------------"<<endl;
    cout<<"The Proton Variables and Cuts are: "<< endl;   
    for (unsigned int i = 0; i < m_ProtonCuts.size(); i++){
      if(checkCut(m_ProtonCuts[i].second)) cout << padPairVec(m_ProtonCuts[i],spacing,"C",spacing,"L") << endl;
    }
    cout<<"----------------------------------------------------------"<<endl;
    cout<<"The Kaon Variables and Cuts are: "<< endl;   
    for (unsigned int i = 0; i < m_KaonCuts.size(); i++){
      if(checkCut(m_KaonCuts[i].second)) cout << padPairVec(m_KaonCuts[i],spacing,"C",spacing,"L") << endl;
    }
    cout<<"----------------------------------------------------------"<<endl;
    cout<<"The Pi0 Variables and Cuts are: "<< endl;   
    for (unsigned int i = 0; i < m_Pi0Cuts.size(); i++){
      if(checkCut(m_Pi0Cuts[i].second)) cout << padPairVec(m_Pi0Cuts[i],spacing,"C",spacing,"L") << endl;
    }
    cout <<"=========================================================="<<endl;
  }


  void writeToStream(std::ofstream& outputfile){
    int spacing = 30;
    outputfile  <<  "=========================================================="<<endl;
    outputfile  <<  " "+m_Set+"  Cut Version Used :  " <<  m_CutVersion   << endl;   
    outputfile  <<  "=========================================================="<<endl;
    outputfile<<"The Track Variables and Cuts are: "<< endl;   
    for (unsigned int i = 0; i < m_TrackCuts.size(); i++){
      if(checkCut(m_TrackCuts[i].second)) outputfile << padPairVec(m_TrackCuts[i],spacing,"C",spacing,"C") << endl;
    }
    outputfile<<"----------------------------------------------------------"<<endl;
    outputfile<<"The Mass1 Variables and Cuts are: "<< endl;   
    for (unsigned int i = 0; i < m_MassCuts1.size(); i++){
      if(checkCut(m_MassCuts1[i].second)) outputfile << padPairVec(m_MassCuts1[i],spacing,"C",spacing,"C") << endl;
    }
    outputfile<<"----------------------------------------------------------"<<endl;
    outputfile<<"The Mass2 Variables and Cuts are: "<< endl;   
    for (unsigned int i = 0; i < m_MassCuts2.size(); i++){
      if(checkCut(m_MassCuts2[i].second)) outputfile << padPairVec(m_MassCuts2[i],spacing,"C",spacing,"C") << endl;
    }
    outputfile<<"----------------------------------------------------------"<<endl;
    outputfile<<"The Fit Variables and Cuts are: "<< endl;   
    for (unsigned int i = 0; i < m_FitCuts.size(); i++){
      if(checkCut(m_FitCuts[i].second)) outputfile << padPairVec(m_FitCuts[i],spacing,"C",spacing,"C") << endl;
    }
    outputfile<<"----------------------------------------------------------"<<endl;
    outputfile<<"The Set-Specific Variables and Cuts are: "<< endl;   
    for (unsigned int i = 0; i < m_SetCuts.size(); i++){
      if(checkCut(m_SetCuts[i].second)) outputfile << padPairVec(m_SetCuts[i],spacing,"C",spacing,"C") << endl;
    }
    outputfile<<"----------------------------------------------------------"<<endl;
    outputfile<<"The Shower Variables and Cuts are: "<< endl;   
    for (unsigned int i = 0; i < m_ShowerCuts.size(); i++){
      if(checkCut(m_ShowerCuts[i].second)) outputfile << padPairVec(m_ShowerCuts[i],spacing,"C",spacing,"C") << endl;
    }
    outputfile<<"----------------------------------------------------------"<<endl;
    outputfile<<"The Electron Variables and Cuts are: "<< endl;   
    for (unsigned int i = 0; i < m_ElectronCuts.size(); i++){
      if(checkCut(m_ElectronCuts[i].second)) outputfile << padPairVec(m_ElectronCuts[i],spacing,"C",spacing,"L") << endl;
    }
    outputfile<<"----------------------------------------------------------"<<endl;
    outputfile<<"The Muon Variables and Cuts are: "<< endl;   
    for (unsigned int i = 0; i < m_MuonCuts.size(); i++){
      if(checkCut(m_MuonCuts[i].second)) outputfile << padPairVec(m_MuonCuts[i],spacing,"C",spacing,"L") << endl;
    }
    outputfile<<"----------------------------------------------------------"<<endl;
    outputfile<<"The Pion Variables and Cuts are: "<< endl;   
    for (unsigned int i = 0; i < m_PionCuts.size(); i++){
      if(checkCut(m_PionCuts[i].second)) outputfile << padPairVec(m_PionCuts[i],spacing,"C",spacing,"L") << endl;
    }
    outputfile<<"----------------------------------------------------------"<<endl;
    outputfile<<"The Kaon Variables and Cuts are: "<< endl;   
    for (unsigned int i = 0; i < m_KaonCuts.size(); i++){
      if(checkCut(m_KaonCuts[i].second)) outputfile << padPairVec(m_KaonCuts[i],spacing,"C",spacing,"L") << endl;
    }
    outputfile<<"----------------------------------------------------------"<<endl;
    outputfile<<"The Proton Variables and Cuts are: "<< endl;   
    for (unsigned int i = 0; i < m_ProtonCuts.size(); i++){
      if(checkCut(m_ProtonCuts[i].second)) outputfile << padPairVec(m_ProtonCuts[i],spacing,"C",spacing,"L") << endl;
    }
    outputfile<<"----------------------------------------------------------"<<endl;
    outputfile<<"The Pi0 Variables and Cuts are: "<< endl;   
    for (unsigned int i = 0; i < m_Pi0Cuts.size(); i++){
      if(checkCut(m_Pi0Cuts[i].second)) outputfile << padPairVec(m_Pi0Cuts[i],spacing,"C",spacing,"L") << endl;
    }
    outputfile <<"=========================================================="<<endl;
  }
};





void printCuts(TString Set){  
  // creating object of class for decay mode
  BAHDecays DecayInfo(Set);

  if(DecayInfo.badinput()){ BAHDecays::shit(); return;}  // if bad input, then stopping

  // creating object of class for cuts based on decay info
  BAHCuts CutInfo(DecayInfo,1);
  if(CutInfo.checkChi2Fit()){ cout << " Chi2Fit -> True" << endl;}
  else{ cout << " Chi2Fit -> False" << endl;}

  if(Set.Contains("gep")){  CutInfo.SetChi2Fit(true);}

    
  // printing Both class's member data
  //cout << endl << endl;
  //DecayInfo.display();
  //cout << endl << endl;
  CutInfo.display();

  CutInfo.displayless();
  //CutInfo.nullifyCut();

}


void printCuts(int dummy = 1){
  TString Set;
  if(dummy==1){ Set = "gtm"; }  // DON'T HAVE mu SIGMC done.
  if(dummy==2){ Set = "get"; }
  if(dummy==3){ Set = "gep"; }
  if(dummy==4){ Set = "gepp";}
  if(dummy==5){ Set = "gpp"; }
  if(dummy==6){ Set = "gPP"; }
  if(dummy==7){ Set = "eepp";}
  if(dummy==8){ Set = "mmpp";}
  printCuts(Set);
}


#endif
