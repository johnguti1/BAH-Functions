#if !defined(FILEHELPER_H)
#define FILEHELPER_H

 #include "BAHUtilities.h"

//=========================================================================================
//=========================================================================================
//  - File functions and definitions to retrieve the TStrings of directories containing 
//    specific data/MC samples for analysis
//  - Additionally, retrieve the n-tuple names of the relevant data/MC samples
//------------------------------
//  - VERY helpful to name directories and subdirectories with a consistent system 
//    to allow for easy filename retrieval in getFN().
//=========================================================================================
//=========================================================================================
TString BASEPath = ""; // Insert path to your workarea
TString PackagePath = BASEPath+""; // Insert Path to your Packages [like BAH-Functions]
TString DataPath = BASEPath+""; // Insert Path that leads to all of your Data sets and monte carlo samples
//------------------------------
 // I like to have a output directory specifically contanining subsection 
TString OutputFile = BASEPath+"Work-Output/pdfs"; // Sub-directory for pdfs. Can contain more subdirectories
TString OutputTXT = BASEPath+"Work-Output/txts";  // Sub-directory for text files. Can contain more subdirectories
TString ModePath = BASEPath+"Work-Output/txts"; // added for laziness a long time ago
//------------------------------
bool fa=false;   // cause im lazy [and was ignorant, probably useless now]
bool tr=true;    // cause im lazy [and was ignorant, probably useless now]
//=========================================================================================
/////////////////////////////////////////
//  List of Available Files [on my personal pc]
/////////////////////////////////////////
//========  Main Project  ============   gtm  get  gep  geppp
//  "INC-ntINC.SIGMC.3686"            SIGMC
//  "INC-ntGEN.SIGMC.3686"
//------------------------------
//  "INC-ntINC.INCMC.3686"            INCMC
//  "INC-ntINC.INCMC.3686.2009"
//  "INC-ntINC.INCMC.3686.2012"
//  "INC-ntINC.INCMC.3686.2021"
//------------------------------
//  "INC-ntINC.INCMC.3650"            INCMC
//  "INC-ntINC.INCMC.3650.2022"
//------------------------------
//  "INC-ntINC.INCMC.3770"            INCMC
//  "INC-ntINC.INCMC.3650.2021"
//------------------------------
//  "INC-ntINC.DATA.3650"             DATA
//  "INC-ntINC.DATA.3650.2022"
//====================================
//======== EXC Control Samples  ======   gpp  gkk  gPP
//  "EXC-ntINC.SIGMC.3686"            SIGMC
//  "EXC-ntGEN.SIGMC.3686"
//------------------------------
//  "EXC-ntINC.INCMC.3686"            INCMC
//  "EXC-ntINC.INCMC.3686.2012"
//------------------------------
//  "EXC-ntINC.INCMC.3650"            INCMC
//  "EXC-ntINC.INCMC.3650.2022"
//------------------------------
//  "EXC-ntINC.DATA.3650"             DATA
//  "EXC-ntINC.DATA.3650.2022"
//====================================
//===== Old INC Control Samples  =====   gpp  gPP  eepp  mmpp
//  "INC-ntINC.SIGMC.3686"            SIGMC
//  "INC-ntGEN.SIGMC.3686"
//------------------------------
//  "INC-ntINC.INCMC.3686"            INCMC
//  "INC-ntINC.INCMC.3686.2012"
//------------------------------
//  "INC-ntINC.INCMC.3650"            INCMC
//  "INC-ntINC.INCMC.3650.2022"
//------------------------------
//  "INC-ntINC.DATA.3650"             DATA
//  "INC-ntINC.DATA.3650.2022"
////////////////////////////////////////////////





//=========================================================================================
//=========================================================================================
//=========================================================================================
// For getting to the directories and finding the specific file names of the root files
TString getFN( TString Set, TString ntXXX, TString Type, bool moreskim = false){
  TString TypePath;
  TString fn;      // output
  TString rootfile;
  TString ModeName;// For differntiating root files/content inside
  TString SkimTag;
  //==========================================================================
  if(Set.Contains("tt")){ 
    ModeName = "TauTau";
    //if(Set.Contains("gtm")||Set.Contains("get")){ SkimTag = "fixed"; }  // Only relevant for lepton modes since the recoil mass cut was wrong so re-did it
    //else{ SkimTag = "SKIM"; }
    //if(Type=="EVTGEN")
    fn = BASEPath+"MainProject/_AnalysisFocus_/SIGMC/SIGMC.12.tauBACK/SKIM/SKIM.ntINC_TauTau_MODECODE.root";   // via EVTGEN psi(2S) decay
    fn = BASEPath+"MainProject/_AnalysisFocus_/SIGMC/SIGMC.12.tauBACK/SKIM/SKIM.ntINC_TauTau_MODECODE.root";   // via EVTGEN psi(2S) decay
    //fn = BASEPath+"MainProject/_AnalysisFocus_/SIGMC/SIGMC.12.tauee/SKIM?/SKIM.ntINC_TauTau_MODECODE.root";   // via KKMC 
    // For 3770 tau tau MC
    //fn = BASEPath+"MainProject/_AnalysisFocus_/SIGMC/SIGMC.3770.2021.ditau/SKIM.1/SKIM.ntINC_TauTau_MODECODE.root";
    return fn;
  }  // background MC
  //==========================================================================
  if(moreskim){ SkimTag = "smaller"; }
  else{ 
    if(Type.Contains("INCMC.3770")){ SkimTag = "SKIM.?"; }
    else{ SkimTag = "SKIM"; }
  }
  //==========================================================================
  if(Set=="gpp"||Set=="gPP"||Set=="eepp"||Set=="mmpp"||Set=="gkk"||Set=="etgpp"){ ModeName = "Control";}
  if(Set=="gep"||Set=="gepp"){ ModeName = "TAUPI";}
  if(Set=="gtm"){ ModeName = "MUTAU";}
  if(Set=="get"){ ModeName = "ETAU";}
  if(ntXXX.Contains("ntGEN")){  rootfile = "SKIM.ntGEN.root";  } 
  else{  rootfile = "SKIM."+ntXXX+"_"+ModeName+"_MODECODE.root"; }
  //==========================================================================
  // SIGMC (based on 2012 INCMC)
  if(Set=="gtm"||Set=="get"||Set=="gep"||Set=="gepp"){
    if(Type.Contains("SIGMC")){
      if(Set!="gtm"){TypePath=(BASEPath+"MainProject/_AnalysisFocus_/_signalMC_/SIGMC.12.e/"+ SkimTag+"/");}  // Need to erase and copy new
      if(Set=="gtm"){TypePath=(BASEPath+"MainProject/_AnalysisFocus_/_signalMC_/SIGMC.12.mu/"+SkimTag+"/");}
    }
    if(Type.Contains("INCMC.09")){TypePath=(BASEPath+"MainProject/_AnalysisFocus_/_BES3sampleMC_/INCMC.3686/INCMC.3686.2009/"+SkimTag+"/");}
    if(Type.Contains("INCMC.12")){TypePath=(BASEPath+"MainProject/_AnalysisFocus_/_BES3sampleMC_/INCMC.3686/INCMC.3686.2012/"+SkimTag+"/");}
    if(Type.Contains("INCMC.21")){TypePath=(BASEPath+"MainProject/_AnalysisFocus_/_BES3sampleMC_/INCMC.3686/INCMC.3686.2021/"+SkimTag+"/");}  // preskimmed to be less
    //===========================
    if(Type.Contains("INCMC.3650")){TypePath=(BASEPath+"MainProject/_AnalysisFocus_/_BES3sampleMC_/INCMC.3650/INCMC.3650.2022/SKIM/");} 
    //===========================
    if(Type.Contains("INCMC.3770")){TypePath=(BASEPath+"MainProject/_AnalysisFocus_/_BES3sampleMC_/INCMC.3770/INCMC.3770.2021/SKIM*/");} // preskimmed to be less
    //===========================
    if(Type.Contains("CONT.3650")){ TypePath=(BASEPath+"MainProject/_AnalysisFocus_/_continuumBkg_/CONT.3650/CONT.3650.2022/SKIM/");}
    //===========================
    if(Type.Contains("CONT.3770.11")){ TypePath=(BASEPath+"MainProject/_AnalysisFocus_/_continuumBkg_/CONT.3770/CONT.3770.11/"+SkimTag+"/");}
    if(Type.Contains("CONT.3770.21")){ TypePath=(BASEPath+"MainProject/_AnalysisFocus_/_continuumBkg_/CONT.3770/CONT.3770.21/"+SkimTag+"/");}
    //===========================
    // NEED TO REPLACE THIS, JUST A TEST FILE USING 3650 FOR NOW!!!!!!!
    //if(Type.Contains("DATA.3686.SEMI")){ TypePath=(BASEPath+"MainProject/_AnalysisFocus_/_continuumBkg_/CONT.3650/CONT.3650.2022/SKIM/");}
    if(Type.Contains("DATA.3686.SEMI")){ TypePath=(BASEPath+"MainProject/_AnalysisFocus_/DATA/DATA.3686.Semi/DATA.3686.Semi.*/SKIM*/");}
  }
  //==========================================================================
    //Control Samples
  if((ntXXX=="ntINC"||ntXXX.Contains("in"))&&(Set=="gpp"||Set=="gPP"||Set=="eepp"||Set=="mmpp")){
    // Old Control Samples (sample.0)
    if(Type=="SIGMC"){ TypePath=(BASEPath+"MainProject/Old__AnalysisFocus_/control/SIGMC/SKIM/"); }
    if(Type=="INCMC"){ TypePath=(BASEPath+"MainProject/Old__AnalysisFocus_/control/INCMC/SKIM/"); }
    if(Type=="DATA"){  TypePath=(BASEPath+"MainProject/Old__AnalysisFocus_/control/DATA/SKIM/");  }
  }
  if((ntXXX=="ntEXC"||ntXXX.Contains("ex"))&&(Set=="gpp"||Set=="gPP"||Set=="gkk"||Set=="etgpp")){
    // New Control Samples (sample.1)
    if(Type=="SIGMC"){ TypePath=(BASEPath+"MainProject/_AnalysisFocus_/control/EXCsample/SIGMC.1/SKIM/"); }
    if(Type=="INCMC"){ TypePath=(BASEPath+"MainProject/_AnalysisFocus_/control/EXCsample/INCMC.3686.12/SKIM/"); }
    if(Type=="INCMC.3650"){ TypePath=(BASEPath+"MainProject/_AnalysisFocus_/control/EXCsample/INCMC.3650.22/SKIM/"); }
    if(Type=="DATA"){  TypePath=(BASEPath+"MainProject/_AnalysisFocus_/control/EXCsample/DATA.3686.12/SKIM/");  }
  }
  return TypePath+rootfile;
}




//==========================================================================
//==========================================================================
// For Getting the N-Tuple which contains the relevant physics info from the root file
// Keep simple by using consistence N-tuple names across data set of project
TString getNT( TString Set, TString ntXXX ){
  TString nt;
  if(Set=="tt"){ return nt = ( "ntINC_TauTau_MODECODE"); }
  //
  if((Set=="gep")||(Set=="gepp")){  //ntXXX="ntINC"; 
    if(ntXXX=="ntGEN"){ return ntXXX;  }
    if(ntXXX!="ntGEN"){ return nt = ( ntXXX+"_TAUPI_MODECODE"); }
  }
  if((Set=="gtm")||(Set=="get")){  //ntXXX="ntINC"; 
    if(ntXXX=="ntGEN"){ return ntXXX;  }
    if(Set=="gtm"){ return nt = ( ntXXX+"_MUTAU_MODECODE"); }
    if(Set=="get"){ return nt = ( ntXXX+"_ETAU_MODECODE");  }
  }
  if((Set=="gPP")||(Set=="gpp")||(Set=="gkk")||(Set=="eepp")||(Set=="mmpp")||(Set=="etgpp")){  //ntXXX="ntINC"; 
    if(ntXXX=="ntGEN"){ return ntXXX;  } 
    if(ntXXX!="ntGEN"){ return nt = ( ntXXX+"_Control_MODECODE"); }
  }
  // Last ditch stuff, should remove or edit eventually... 
  //if(!Set.Contains("t")){   //ntXXX="ntEXC";  
  //  if(Type=="INCMC"){  nt = ( ntXXX+"_PSI2S_MODECODE");   }
  //  if(Type=="SIGMC"){  nt = ( ntXXX+"_LFVCHIC_MODECODE"); }
  //  if(Type=="DATA"){   nt = ( ntXXX+"_LFVCHIC_MODECODE"); }
  //}
  SPACEin();
  SPACEstr(" BAD NT Set/ntXXX input ");
  cout << Set << "      " << ntXXX << endl;
  SPACEin();
  return nt;
}
//=========================================================================================
#endif