#if !defined(BAHDECAYS_H)
#define BAHDECAYS_H


#include "FileHelper.h"
#include "BAHPhysics.h"

// Rename to Bes Analysis Helper  

// ***************************************************************
//
//  CLASS BAHDecays         ( BAH = Besiii Analysis Helper )
//
//    Based on the Final/Intermediate State, get generally relevant items/properties
//      that have been assigned to them
//
// ***************************************************************

class MCTruthHelper;

class BAHDecays{
  // declaring private class data members
private:
  bool m_end=false;
  TString m_Set;
  TString m_FS;
  TString m_IS;
  TString m_HistogramTitle;
  TString m_modeCollectLabel;
  vector<TString> m_MCDecayParticleCuts; // For intermediate decay [pdg numbering]
  vector<TString> m_MCDecayCodeCuts;     // For final particle cuts to get signal
  vector<TString> m_GeneralMCCuts;
  vector<TString> m_GeneralMCLabels; // Has the histogram labels according to pdg intermediate decay above and their decays
  vector<TString> m_GeneralMCTag; // Just an indicator for the speccific MCCut applied. Should mainly be label of intermediate resonance
  vector<TString> m_SimpleMCNames; // Simple written out form of the decay info [name list] recorded. Simplified and only used for terminal/txt printing.
  vector<TString> m_ExtraInfo;
  vector<FSModeInfo*> m_modes;
  vector<pair<int,int>> m_ModeCodes;
  TString m_MCExtras;
  
  //vector<TString> m_FileInfo; // As a bandaid, maybe saving the file info for use in applying INCMC.3770.2021 , INCMC:3770 (<- All 3770 incmc) 
    // ***************
  vector<pair<TString,TString>> m_ParticlesAndLabels;
  vector<pair<TString,TString>> m_Tracks;
  vector<pair<TString,TString>> m_Showers;
  vector<pair<TString,TString>> m_pi0s;
  vector<pair<TString,TString>> m_etas;
  vector<pair<TString,TString>> m_piCs;
  vector<pair<TString,TString>> m_electrons;
  vector<pair<TString,TString>> m_muons;
  vector<pair<TString,TString>> m_protons;
  vector<pair<TString,TString>> m_kaons;
    // ***************
  TString m_Mass1Var="";
  TString m_Mass2Var="";


  void clearAssignments(){
    m_Mass1Var="";
    m_Mass2Var="";
    // ***************
    m_ParticlesAndLabels.clear();
    m_Tracks.clear();
    m_Showers.clear();
    m_pi0s.clear();
    m_etas.clear();
    m_piCs.clear();
    m_electrons.clear();
    m_muons.clear();
    m_protons.clear();
    m_kaons.clear();
    // ***************
    m_ExtraInfo.clear();
    m_modes.clear();
    m_ModeCodes.clear();
    // ***************
    m_MCDecayParticleCuts.clear();
    m_MCDecayCodeCuts.clear();
    m_GeneralMCLabels.clear();
    m_GeneralMCCuts.clear();
    m_GeneralMCTag.clear();
    m_SimpleMCNames.clear();
    return;
  }


public:
  //================================================================================================
  // Useful for just inputting pdg numbers and automattically getitng the sorted cut string for signal
  static TString getMCDecayParts(vector<int> pdgnumbers, bool printcheck =false){
    if(pdgnumbers.size()>6){ BAHDecays::shit();  return ""; }
    TString output="(";
    sort(pdgnumbers.begin(),pdgnumbers.end());
    // Sorting and organizing intial relevant pdgnumbers 
    // [Think Ryan mentioned once negative to postive is safest way... doesn't matter]
    for (unsigned int i = 0; i < pdgnumbers.size(); i++){
      if(printcheck)cout << "pdgID["+FSString::int2TString(i)+"] = " << pdgnumbers[i] << endl;
      output=output+"MCDecayParticle"+FSString::int2TString(i+1)+"=="+FSString::int2TString(pdgnumbers[i]);
      if(i < 5){output=output+" && ";}
    }
    // Fill left over spaces with 0 to focus only on signal decay particles
    for (unsigned int i = pdgnumbers.size(); i < 6 ; i++){
      output=output+"MCDecayParticle"+FSString::int2TString(i+1)+"=="+FSString::int2TString(0);
      if(i < 5){output=output+" && ";}
    }
    return output+")";
  }
  
  static TString getMCDecay(TString IntermediateParticles, bool printcheck =false){
    return getMCDecayParts(ParticlesToIDs(IntermediateParticles),printcheck);
  }

  //================================================================================================
  // Get the Final State to print in ROOT. Useful for getting the final state based on the Set.
  static TString getSetRootName(TString Set){
    TString FinSetName;
    if(Set=="X" ){          FinSetName = "X";                           }
    else if(Set=="gtm" ){   FinSetName = "#gamma#mue(2#nu)";            }
    else if(Set=="get" ){   FinSetName = "#gammae#mu(2#nu)";            }
    else if(Set=="gep" ){   FinSetName = "#gammae#pi(#nu)";             }
    else if(Set=="gepp"){   FinSetName = "#gammae#pi#pi^{0}(#nu)";      }
    else if(Set=="gkk" ){   FinSetName = "#gammaK^{+}K^{-}";            }
    else if(Set=="gpp" ){   FinSetName = "#gamma#pi^{+}#pi^{-}";        }
    else if(Set=="gPP" ){   FinSetName = "#gammap#bar{p}";              }
    else if(Set=="eepp"){   FinSetName = "#pi^{0}#pi^{0}e^{+}e^{-}";    }
    else if(Set=="mmpp"){   FinSetName = "#pi^{0}#pi^{0}#mu^{+}#mu^{-}";}
    else if(Set=="etgpp" ){ FinSetName = "#eta#gamma#pi^{+}#pi^{-}";    }
    else{ FinSetName = ""; }
    return FinSetName;
  }
  
  //================================================================================================
  // Get the Intermediate State to print in ROOT. Useful for getting the Intermediate based on the Set if needed.
  static TString getISRootName(TString IS, TString Set = ""){
    TString OutputName;
    TString IntName;   // TRY TO ALWAYS BE CONSISTENT WITH THIS IS NAMES
    if(     IS=="Xc0"   ||IS=="0"  ||IS=="chic0"){ IntName = "#gamma#chi_{c0}";     }
    else if(IS=="Xc1"   ||IS=="1"  ||IS=="chic1"){ IntName = "#gamma#chi_{c1}";     }
    else if(IS=="Xc2"   ||IS=="2"  ||IS=="chic2"){ IntName = "#gamma#chi_{c2}";     }
    else if(IS=="XcJ"   ||IS=="J"  ||IS=="chicJ"){ IntName = "#gamma#chi_{cJ}";     }
    else if(IS=="Jpsi"  ||IS=="psi"             ){ IntName = "#pi^{0}#pi^{0}J/#psi";}
    else if(IS=="TauTau"||IS=="tt" ||IS=="ditau"){ IntName = "#tau^{+}#tau^{-}";    }
    else if(IS=="X"                             ){ IntName = "X";                   }
    else if(IS=="gX"                            ){ IntName = "#gammaX";             }
    else{ IntName = ""; }
    //-----------------------------------------------------------------
    // If there is a secondary intermediate decay not seen in the final state: [Can add more]
    if(Set=="get"||Set=="gep"||Set=="gepp"){OutputName = IntName+" #rightarrow #gammae#tau";}
    else if(Set=="gtm"){ OutputName = IntName+" #rightarrow #gamma#mu#tau"; }
    else{ OutputName = IntName; }
    //-----------------------------------------------------------------
    return OutputName;
  }
  //================================================================================================
  // Useful for labeling legends on histograms. Can use for background decays of interest.
  // Edit the function below to add new intermediate states
  static TString getSetTitle(TString IntermediateState, TString Set, bool Signal=true, bool bare = false, bool SupressFS = true){
    TString FinSetName = "";
    TString IntName = getISRootName(IntermediateState,Set);
    if(!SupressFS){ FinSetName = getSetRootName(Set);  }
    //-----------------------------------------------------------------
    TString DecayString;
    if(IntName==""||FinSetName==""){ DecayString = IntName+FinSetName;}
      else{ DecayString = IntName+" #rightarrow "+FinSetName;}
    if(bare){ return DecayString; }
    //-----------------------------------------------------------------
    TString modestring;
    if(Signal){  modestring=    "Signal "+DecayString;}
    if(!Signal){ modestring="Background "+DecayString;}
    //-----------------------------------------------------------------
    TString output;
    if(!modestring.Contains("J/#psi")){
      if(Signal){ output=    "Signal "+DecayString;}
      if(!Signal){output="Background "+DecayString;}
    }
    //-----------------------------------------------------------------
    // Bandage solution to long Signal labels. Best to use length of string eventually
    if(modestring.Contains("J/#psi")){
      if(Signal){ output=    "#splitline{Signal}{"+DecayString+"}";}
      if(!Signal){output="#splitline{Background}{"+DecayString+"}";}
    }
    return output;
  }

  //================================================================================================
  // Useful for getting specific Title for Histograms
  static TString getFullTitle(TString Set, TString IntermediateState = "J",  TString InitialState = "psip", TString IS2 = ""){
    //------------------------------------------
    // Setting up names of Intermediate and Final States
    TString FinSetName  = getSetRootName(Set);
    TString IntName     = getISRootName(IntermediateState,Set);
    TString IntName2    = getISRootName(IS2);
    TString InitialName,  OutputTitle;
    //------------------------------------------
    // Setting up initial state ( e+e- or psip or something else...)
    if(InitialState=="psip"||InitialState=="psi(2S)"||InitialState.Contains("3686")){             InitialName = "#psi(2S)";  }
    else if(InitialState=="ee"||InitialState=="3770"||InitialState=="3682"||InitialState=="3650"){InitialName = "e^{+}e^{-}";}
    else{ InitialName = ""; }
    //------------------------------------------
    // Organizing output based on "" returned
    if(InitialName!=""){  InitialName = InitialName+" #rightarrow "; }
    if(IntName    !=""){  IntName     = IntName    +" #rightarrow "; }
    if(IntName2   !=""){  IntName2    = IntName2   +" #rightarrow "; }
    //------------------------------------------
    OutputTitle = InitialName+IntName+IntName2+FinSetName;
    return OutputTitle;
  }

  //================================================================================================
  // Use the directory file to check what kinda of Label to put on the Histogram
  static TString get2DLabel(TString File, TString IntermediateState, TString Set){ 
    TString output = getSetTitle(IntermediateState,Set,false,true);
    if(File.Contains("SIGMC")){ output = "#splitline{Signal MC}{"+output+"}";}
    else if(File.Contains("INCMC")){ output = "#splitline{Background}{Inclusive MC}";}
    else if(File.Contains("DATA")){  output = "#splitline{Data MC}{"+output+"}";}
    else if(File.Contains("CONT")){  output = "Full 3770 Data}";}
    return output;
  }

  //================================================================================================ 
  // Might be useful for making "particle" type histogram arguments for making general stuff (with simple loop)
  static vector<pair<TString,TString>> getParticleType(vector<pair<TString,TString>> ParticlesAndLabels, TString ParticleType){
    vector<pair<TString,TString>> placeholder;
    TString PartLabel;
    for (unsigned int i = 0; i < ParticlesAndLabels.size(); i++){
      PartLabel = ParticlesAndLabels[i].second;
      // If saving tracks
      if((ParticleType=="Tk")&&!(PartLabel.Contains("#gamma")||PartLabel.Contains("#pi^{0}")||PartLabel.Contains("#eta"))){
        placeholder.push_back(ParticlesAndLabels[i]);
      }
      // If saving showers
      if((ParticleType=="Sh")&&((PartLabel.Contains("#gamma")))){
        placeholder.push_back(ParticlesAndLabels[i]);
      }
      // If saving neutral pions
      if((ParticleType=="pi0")&&((PartLabel.Contains("#pi^{0}")))){
        placeholder.push_back(ParticlesAndLabels[i]);
      }
      // If saving etas
      if((ParticleType=="eta")&&((PartLabel.Contains("#eta")))){
        placeholder.push_back(ParticlesAndLabels[i]);
      }
      // If saving charged pions
      if((ParticleType=="piC")&&(PartLabel.Contains("#pi")&&!((PartLabel.Contains("#pi^{0}"))))){
        placeholder.push_back(ParticlesAndLabels[i]);
      }
      // If saving electrons
      if((ParticleType=="e")&&((PartLabel=="e")||(PartLabel.Contains("e^{")))){
        placeholder.push_back(ParticlesAndLabels[i]);
      }
      // If saving muons
      if((ParticleType=="mu")&&((PartLabel=="#mu")||(PartLabel.Contains("#mu^{")))){
        placeholder.push_back(ParticlesAndLabels[i]);
      }
      // If saving protons
      if((ParticleType=="P")&&((PartLabel=="p")||(PartLabel=="#bar{p}"))){
        placeholder.push_back(ParticlesAndLabels[i]);
      }
      // If saving kaons
      if((ParticleType=="K")&&((PartLabel=="K")||(PartLabel.Contains("K^{")))){
        placeholder.push_back(ParticlesAndLabels[i]);
      }
    }
    return placeholder;
  }

  static void shit(){
    cout << "========================="<<endl;
    cout << "SHIT input so stopping function" << endl;
    cout << "========================="<<endl;
    return;
  }
  
  // declaring constructor
  BAHDecays( TString FinalStateName ){
    clearAssignments();
    m_Set = FinalStateName;  // Just incase its needed later
    m_HistogramTitle = "#psi(2S) #rightarrow";
    TString ModeFile;
    if(m_Set=="gtm"||m_Set=="get"||m_Set=="gep"||m_Set=="gepp"){  
      ModeFile = "LFVdecays.modes"; 
      m_IS = "XcJ";
    }
    if(m_Set=="eepp"||m_Set=="mmpp"||m_Set=="gpp"||m_Set=="gPP"||m_Set=="gkk"||m_Set=="etgpp"){ 
      ModeFile = "Control.modes"; 
      if(m_Set=="gpp"||m_Set=="gPP"||m_Set=="gkk"){ m_IS = "XcJ"; }
      if(m_Set=="eepp"||m_Set=="mmpp"){ m_IS = "Jpsi"; }
      if(m_Set=="etgpp"){ m_IS = "NOTHING"; }
    }
    // Eventually needa get figure if I should apply stuff independantly or not...
    cout<<" Want Criteria based on "+FinalStateName+" that comes from possibly "+m_IS <<endl;
    FSModeCollection::addModesFromFile(PackagePath+"BAHDecayModes/"+ModeFile);
    /////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////
    // Now looking at intermediate particles
    if(m_IS=="XcJ"){
      m_HistogramTitle = m_HistogramTitle+" #gamma#chi_{cJ} #rightarrow";
      // Can use FSPhysics.h to find the pdg values. In root, can use tab with FSPhysics::kpdg____
      // For using on histogram with signal MC, Setting Up Cut and Name Associated with it.
      m_MCDecayParticleCuts.push_back(getMCDecayParts({FSPhysics::kpdgGamma,FSPhysics::kpdgChic0}));
      m_GeneralMCLabels.push_back(getSetTitle("Xc0",m_Set,true));
      m_GeneralMCTag.push_back("Xc0");
      if(!(m_Set=="gpp"||m_Set=="gkk")){
        m_MCDecayParticleCuts.push_back(getMCDecayParts({FSPhysics::kpdgGamma,FSPhysics::kpdgChic1}));
        m_GeneralMCLabels.push_back(getSetTitle("Xc1",m_Set,true));
        m_GeneralMCTag.push_back("Xc1");
      }
      m_MCDecayParticleCuts.push_back(getMCDecayParts({FSPhysics::kpdgGamma,FSPhysics::kpdgChic2}));
      m_GeneralMCLabels.push_back(getSetTitle("Xc2",m_Set,true));
      m_GeneralMCTag.push_back("Xc2");
      /////////////////////////////////////////////////////////////
      // FINAL STATE BASED OPTIONS [Not super necessary, but useful]
      if((FinalStateName=="gtm")||(FinalStateName=="get")||(FinalStateName=="gPP")){
        m_Mass1Var = m_Mass1Var+"MASS(BES3CMS,-3)";
      }
      if((FinalStateName=="gep")||(FinalStateName=="gepp")){
        m_Mass1Var = m_Mass1Var+"MASS(BES3CMS,-2)";
      }
      if((FinalStateName=="gpp")||(FinalStateName=="gkk")){
        m_Mass1Var = m_Mass1Var+"MASS(BES3CMS,-1)";
      }
      //if((FinalStateName=="etgpp")){ // Get chi_{cJ}s to remove them maybe....
        // Maybe dont even use this decay... Not sure yet..
        //m_Mass1Var = m_Mass1Var+"MASS(BES3CMS,-2)";
      //}
      /////////////////////////////////////////////////////////////
    }
    /////////////////////////////////////////////////////////////
    if(m_IS=="Jpsi"){   // Typically lep,lep,pi,pi  // Can leave final state specific at this moment
      // For using on histogram with signal MC
      m_GeneralMCLabels.push_back(getSetTitle("Jpsi",m_Set,true));  // The set indicates the final/intermediate state of interest
      m_GeneralMCTag.push_back("Jpsi"); //may need to change
      /////////////////////////////////////////////////////////////
      // FINAL STATE BASED OPTIONS [Not super necessary]
      if((FinalStateName=="eepp")||(FinalStateName=="mmpp")){
        // Can use FSPhysics.h to find the pdg values. In root, can use tab with FSPhysics::kpdg____
        m_MCDecayParticleCuts.push_back(getMCDecayParts({FSPhysics::kpdgPi0,FSPhysics::kpdgPi0,FSPhysics::kpdgJpsi}));
        m_HistogramTitle = m_HistogramTitle+" #pi^{0}#pi^{0} J/#psi #rightarrow";
        m_Mass1Var = m_Mass1Var+"MASS(BES3CMS,-3,-4)";
      }
    }
    /////////////////////////////////////////////////////////////
    if(m_IS=="TauTau"){   // Typically lep,lep,pi,pi  // Can leave final state specific at this moment
      // For using on histogram with signal MC
      m_GeneralMCLabels.push_back(getSetTitle("TauTau",m_Set,true));  // The set indicates the final/intermediate state of interest
      m_GeneralMCTag.push_back("TauTau"); //may need to change
      /////////////////////////////////////////////////////////////
      // FINAL STATE BASED OPTIONS [Not super necessary]
      if((FinalStateName=="epp0")){
        // Can use FSPhysics.h to find the pdg values. In root, can use tab with FSPhysics::kpdg____
        m_MCDecayParticleCuts.push_back(getMCDecayParts({FSPhysics::kpdgTaum,FSPhysics::kpdgTaup}));
        m_HistogramTitle = m_HistogramTitle+" #pi^{0}#pi^{0} J/#psi #rightarrow";
        m_Mass1Var = m_Mass1Var+"MASS(2,3)";
      }
    }
    /////////////////////////////////////////////////////////////
    if(m_IS=="NOTHING"){
      if(m_Set=="etgpp"){ 
        m_GeneralMCLabels.push_back(getSetTitle("NO",m_Set,true));  // The set indicates the final/intermediate state of interest
        m_MCDecayParticleCuts.push_back(getMCDecayParts({FSPhysics::kpdgEta,FSPhysics::kpdgGamma,FSPhysics::kpdgPip,FSPhysics::kpdgPim})); // Auto sorts so not worries
        m_Mass1Var = m_Mass1Var+"MASS(BES3CMS,-2)"; // Just to check for backgrounds (2 should be gamma)
        m_GeneralMCTag.push_back("EtaBack");
       }
    }

    /////////////////////////////////////////////////////////////
      // If Lepton Flavor Violating with chi_{cJ} to e tau or mu tau
    if((FinalStateName=="gtm")||(FinalStateName=="get")||(FinalStateName=="gep")||(FinalStateName=="gepp")){
      // FINAL STATE BASED OPTIONS
      if(FinalStateName=="gtm"){
        m_HistogramTitle = m_HistogramTitle+" #gamma#mu#tau";
      }
      if(FinalStateName=="get"||FinalStateName=="gep"||FinalStateName=="gepp"){
        m_HistogramTitle = m_HistogramTitle+" #gammae#tau";
      }
    }
    /////////////////////////////////////////////////////////////

    /////////////////////////////////////////////////////////////
     // To get properties of final state
    if((FinalStateName=="get")||(FinalStateName=="gtm")){
      if(FinalStateName=="gtm"){
        m_FS = "GTM";
        m_HistogramTitle = m_HistogramTitle+" #rightarrow #gamma#mue(2#nu)";
        m_Mass2Var = "MASS(BES3CMS,-3,-2)";
        m_SimpleMCNames.push_back("Xc0->mutau->mue nu");
        m_SimpleMCNames.push_back("Xc1->mutau->mue nu");
        m_SimpleMCNames.push_back("Xc2->mutau->mue nu");
      }
      if(FinalStateName=="get"){
        m_FS = "GET";
        m_HistogramTitle = m_HistogramTitle+" #rightarrow #gammae#mu(2#nu)";
        m_Mass2Var = "MASS(BES3CMS,-3,-1)";
        m_SimpleMCNames.push_back("Xc0->etau->emu nu");
        m_SimpleMCNames.push_back("Xc1->etau->emu nu");
        m_SimpleMCNames.push_back("Xc2->etau->emu nu");
      }
      m_MCExtras = "(MCExtras==2000)";
      m_modeCollectLabel = "gem";   
      
      // Using CHARGED CONJUGATE SO SUPPRESSING SIGNS
      m_ParticlesAndLabels.push_back({"1", "e"});
      m_ParticlesAndLabels.push_back({"2", "#mu"});
      m_ParticlesAndLabels.push_back({"3", "#gamma"});
    }
    /////////////////////////////////////////////////////////////
    else if(FinalStateName=="gep"){ 
      m_FS = "GEP";
      m_HistogramTitle = m_HistogramTitle+" #rightarrow #gammae#pi(#nu)";
      m_Mass2Var = "MASS(BES3CMS,-2,-1)";
      m_MCExtras = "(MCExtras==1000)";
      m_modeCollectLabel = "gep";
      m_SimpleMCNames.push_back("Xc0->ETau->EPi nu");
      m_SimpleMCNames.push_back("Xc1->ETau->EPi nu");
      m_SimpleMCNames.push_back("Xc2->ETau->EPi nu");
      // Using CHARGED CONJUGATE SO SUPPRESSING SIGNS CHARGES
      m_ParticlesAndLabels.push_back({"1", "e"});
      m_ParticlesAndLabels.push_back({"2", "#gamma"});
      m_ParticlesAndLabels.push_back({"3", "#pi"});
    }
    /////////////////////////////////////////////////////////////
    else if(FinalStateName=="gepp"){
      m_FS = "GEPP";
      m_HistogramTitle = m_HistogramTitle+" #rightarrow #gammae#pi#pi^{0}(#nu)";
      m_Mass2Var = "MASS(BES3CMS,-2,-1)";
      m_modeCollectLabel = "gepp";
      m_MCExtras = "(MCExtras==1000)";
      m_SimpleMCNames.push_back("Xc0->etau->epipi0 nu");
      m_SimpleMCNames.push_back("Xc1->etau->epipi0 nu");
      m_SimpleMCNames.push_back("Xc2->etau->epipi0 nu");
      // Using CHARGED CONJUGATE SO SUPPRESSING CHARGES
      m_ParticlesAndLabels.push_back({"1", "e"});
      m_ParticlesAndLabels.push_back({"2", "#gamma"});
      m_ParticlesAndLabels.push_back({"3", "#pi"});
      m_ParticlesAndLabels.push_back({"4", "#pi^{0}"});
    }
    /////////////////////////////////////////////////////////////
    // Verifying Sample For 3770  tau tau -> e pi pi0 (3nu)
    else if(FinalStateName=="epp0"){
      m_FS = "EPP0";
      m_HistogramTitle = m_HistogramTitle+" #rightarrow e#pi#pi^{0}(3#nu)";
      m_Mass2Var = "MASS(1,2)";
      m_modeCollectLabel = "epp0";
      m_MCExtras = "(MCExtras==3000)";
      m_SimpleMCNames.push_back("tautau->epipi0 3nu");
      m_SimpleMCNames.push_back("tautau->epipi0 3nu");
      m_SimpleMCNames.push_back("tautau->epipi0 3nu");
      // Using CHARGED CONJUGATE SO SUPPRESSING CHARGES
      m_ParticlesAndLabels.push_back({"1", "e"});
      m_ParticlesAndLabels.push_back({"2", "#pi"});
      m_ParticlesAndLabels.push_back({"3", "#pi^{0}"});
    }
    /////////////////////////////////////////////////////////////
    // Control (Standard Model) Decay Modes so no Tau.
    else if(FinalStateName=="gPP"){
      m_FS="GPP";
      m_HistogramTitle = m_HistogramTitle+" #gammap#bar{p}";
      m_Mass2Var = "MASS(1,2)";
      m_modeCollectLabel = "gPP";
      m_MCExtras = "";
      m_SimpleMCNames.push_back("gamma Xc0->gamma p+ p-");
      m_SimpleMCNames.push_back("gamma Xc1->gamma p+ p-");
      m_SimpleMCNames.push_back("gamma Xc2->gamma p+ p-");
      // No Charged Conjugate so explicitly write out charges
      m_ParticlesAndLabels.push_back({"1", "p"});
      m_ParticlesAndLabels.push_back({"2", "#bar{p}"});
      m_ParticlesAndLabels.push_back({"3", "#gamma"});
    }
    /////////////////////////////////////////////////////////////
    else if(FinalStateName=="gpp"){
      m_FS="GPIPI";
      m_HistogramTitle = m_HistogramTitle+" #gamma#pi^{+}#pi^{-}";
      m_Mass2Var = "MASS(2,3)";
      m_modeCollectLabel = "gpp";
      m_MCExtras = "";
      m_SimpleMCNames.push_back("gamma Xc0->gamma pi+ pi-");
      //m_SimpleMCNames.push_back("gamma Xc1->gamma pi+ pi-");
      m_SimpleMCNames.push_back("gamma Xc2->gamma pi+ pi-");
      // No Charged Conjugate so explicitly write out charges
      m_ParticlesAndLabels.push_back({"1", "#gamma"});
      m_ParticlesAndLabels.push_back({"2", "#pi^{+}"});
      m_ParticlesAndLabels.push_back({"3", "#pi^{-}"});
    }
    /////////////////////////////////////////////////////////////
    else if(FinalStateName=="eepp"){
      m_FS="EE2PI0";
      m_HistogramTitle = m_HistogramTitle+" #pi^{0}#pi^{0}e^{+}e^{-}";
      m_Mass2Var = "MASS(1,2)";
      m_modeCollectLabel = "eepp";
      m_MCExtras = "";
      m_SimpleMCNames.push_back("pi0 pi0 Jpsi->pi0 pi0 e+ e-");
      // No Charged Conjugate so explicitly write out charges
      m_ParticlesAndLabels.push_back({"1", "e^{+}"});
      m_ParticlesAndLabels.push_back({"2", "e^{-}"});
      m_ParticlesAndLabels.push_back({"3", "#pi^{0}"});
      m_ParticlesAndLabels.push_back({"4", "#pi^{0}"});
    }
    /////////////////////////////////////////////////////////////
    else if(FinalStateName=="mmpp"){
      m_FS="MM2PI0";
      m_HistogramTitle = m_HistogramTitle+" #pi^{0}#pi^{0}#mu^{+}#mu^{-}";
      m_Mass2Var = "MASS(1,2)";
      m_modeCollectLabel = "mmpp";
      m_MCExtras = "";
      m_SimpleMCNames.push_back("pi0 pi0 Jpsi->pi0 pi0 mu+ mu-");
      // No Charged Conjugate so explicitly write out charges
      m_ParticlesAndLabels.push_back({"1", "#mu^{+}"});
      m_ParticlesAndLabels.push_back({"2", "#mu^{-}"});
      m_ParticlesAndLabels.push_back({"3", "#pi^{0}"});
      m_ParticlesAndLabels.push_back({"4", "#pi^{0}"});
    }
    /////////////////////////////////////////////////////////////
    else if(FinalStateName=="gkk"){
      m_FS="GKK";
      m_HistogramTitle = m_HistogramTitle+"#gammaK^{+}K^{-}";
      m_Mass2Var = "MASS(2,3)";
      m_modeCollectLabel = "gkk";
      m_MCExtras = "";
      m_SimpleMCNames.push_back("gamma Xc0->gamma K+ K-");
      //m_SimpleMCNames.push_back("gamma Xc1->gamma K+ K-");
      m_SimpleMCNames.push_back("gamma Xc2->gamma K+ K-");
      // No Charged Conjugate so explicitly write out charges
      m_ParticlesAndLabels.push_back({"1", "#gamma"});
      m_ParticlesAndLabels.push_back({"2", "K^{+}"});
      m_ParticlesAndLabels.push_back({"3", "K^{-}"});
    }
    /////////////////////////////////////////////////////////////
    else if(FinalStateName=="etgpp"){
      m_FS="ETAGPP";
      m_HistogramTitle = m_HistogramTitle+"#gamma#pi^{+}#pi^{-}#eta";
      m_Mass2Var = "MASS(1a,[gamma],[pi+],[pi-])"; // To check error on pi0 full mass cut.
      m_modeCollectLabel = "etgpp";
      m_MCExtras = "";
      m_SimpleMCNames.push_back("eta gamma pi+ pi-");
      // No Charged Conjugate so explicitly write out charges
      m_ParticlesAndLabels.push_back({"1", "#eta"});
      m_ParticlesAndLabels.push_back({"2", "#gamma"});
      m_ParticlesAndLabels.push_back({"3", "#pi^{+}"});
      m_ParticlesAndLabels.push_back({"4", "#pi^{-}"});
    }
    /////////////////////////////////////////////////////////////
    else{//Fuck...
      shit();
      m_end = true;   // Can use this to stop any further operation
      return;
    }
    /////////////////////////////////////////////////////////////
    // Print modes and use ModeVector to select each mode of concern based on Final State
    FSModeCollection::display(m_modeCollectLabel,false);
    m_modes = FSModeCollection::modeVector(m_modeCollectLabel);
    for (unsigned int i = 0; i < m_modes.size(); i++){ // Just as a check on the ModeVector elements
        //cout << m_modes[i]->FSModeInfo::modeString("MODESTRING corresponds to MODEDESCRIPTION") << endl;
        if(m_MCExtras==""){m_MCDecayCodeCuts.push_back(m_modes[i]->FSModeInfo::modeString("(MCDecayCode1==MODECODE1 && MCDecayCode2==MODECODE2)"));}
        if(m_MCExtras!=""){m_MCDecayCodeCuts.push_back(m_modes[i]->FSModeInfo::modeString("(MCDecayCode1==MODECODE1 && MCDecayCode2==MODECODE2 && "+m_MCExtras+")"));}
    }
    /////////////////////////////////////////////////////////////
    // Set up general MC cuts combining the Intermediate state and possible final states from there [THESE ARE THE ONES THAT WILL BE USED!!!!]
    TString combinedFScuts = "";
    for(unsigned int i = 0; i< m_MCDecayCodeCuts.size(); i++){
      if(i==0){combinedFScuts = m_MCDecayCodeCuts[i];}
      if(i!=0){combinedFScuts = combinedFScuts+FSOR+m_MCDecayCodeCuts[i];}
    }
    combinedFScuts = "("+combinedFScuts+")";
    // Now loading fscuts into possible intermediate state cuts to use for plotting SIGNALS with category
    for(unsigned int i = 0; i< m_MCDecayParticleCuts.size(); i++){
      m_GeneralMCCuts.push_back("("+m_MCDecayParticleCuts[i]+FSAND+combinedFScuts+")");
    }
    /////////////////////////////////////////////////////////////
    // Set ModeCodes for final states of interest into a vector
    for (unsigned int i = 0; i < m_modes.size(); i++){
      m_ModeCodes.push_back(m_modes[i]->FSModeInfo::modeCode());
    }
    /////////////////////////////////////////////////////////////
    // For additional concerns, can save the output for specific "particle" type
    m_Tracks    = getParticleType(m_ParticlesAndLabels,"Tk");
    m_Showers   = getParticleType(m_ParticlesAndLabels,"Sh");
    m_electrons = getParticleType(m_ParticlesAndLabels,"e");
    m_muons     = getParticleType(m_ParticlesAndLabels,"mu");
    m_piCs      = getParticleType(m_ParticlesAndLabels,"piC");
    m_pi0s      = getParticleType(m_ParticlesAndLabels,"pi0");
    m_protons   = getParticleType(m_ParticlesAndLabels,"P");
    m_kaons     = getParticleType(m_ParticlesAndLabels,"K");
    m_etas      = getParticleType(m_ParticlesAndLabels,"eta");
  }
  /////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////


  // Functions to get relevant properties for each decay

  bool badinput(){return m_end;}
  TString getCategory(){return m_modeCollectLabel;}
  TString getTitle(){return m_HistogramTitle;}
  TString getSet(){return m_Set;} 
  TString getFS(){return m_FS;}
  TString getIS(){return m_IS;}
  vector<pair<TString,TString>> getPartsAndNames(){ return m_ParticlesAndLabels;}
  //vector<TString> getMCDecayModes(){ return m_MCDecayModes;}
  vector<TString> getExtraInfo(){ return m_ExtraInfo;}
  vector<pair<int,int>> getModeCodes(){ return m_ModeCodes;}              // Gets Ryan's Final State ModeCodes
  vector<TString> getModeCodeCuts(){ return m_MCDecayCodeCuts;}           // OBSOLETE?!? // Cuts based on Ryan's Final State ModeCodes 
  vector<TString> getMCDecayParticleCuts(){return m_MCDecayParticleCuts;} // OBSOLETE?!? // Cuts based on pdg's numbering scheme for the Intermediate State
  vector<TString> getGeneralMCCuts(){return m_GeneralMCCuts;}             // For each "set" using both the previosly noted  [FS & IS]
  vector<TString> getGeneralMCTags(){return m_GeneralMCTag;}              // Just for resonance scaling mainly and can be used in BAHDataSets
  vector<TString> getGeneralMCLabels(){return m_GeneralMCLabels;}         // Labels for the General Cuts to use in the TLegend
  vector<TString> getSimpleMCNames(){return m_SimpleMCNames;}     // simple Labels for printing out without "#psi(2s)#rightarrow #mu^{+}" -> "  -> mu+ " 
  vector<FSModeInfo*> getMCModeInfo(){return m_modes;}
  //--------------------------------------------------------------
  // Can add more variables is needed
  TString getMass1Var(){return m_Mass1Var;}
  TString getMass2Var(){return m_Mass2Var;}
  //--------------------------------------------------------------
  // Useful for getting variable/cuts and saving the label for histograms
  vector<pair<TString,TString>> getTracks(){  return m_Tracks;}
  vector<pair<TString,TString>> getShowers(){ return m_Showers;}
  vector<pair<TString,TString>> getElectrons(){return m_electrons;}
  vector<pair<TString,TString>> getMuons(){   return m_muons;}
  vector<pair<TString,TString>> getPiCs(){    return m_piCs;}
  vector<pair<TString,TString>> getPi0s(){    return m_pi0s;}
  vector<pair<TString,TString>> getProtons(){ return m_protons;}
  vector<pair<TString,TString>> getKaons(){   return m_kaons;}
  vector<pair<TString,TString>> getEtas(){    return m_etas;}
  //--------------------------------------------------------------
  //--------------------------------------------------------------
  // Functions to add relevant properties for each decay

  // If the Label Does NOT include "Signal", it was carve out of the new cut INCMC from the remaining INCMC.
  // Should ALWAYS do these together.... [may cause errors otherwise]
  // MAINLY SHOULD USE addGeneralMCDecay unless doing some variable based crap. 
  void addGeneralMCTags( TString NewTag ){     m_GeneralMCTag.push_back(NewTag);}        // Internal Label used to differentiate Cuts/Modes
  void addGeneralMCLabels( TString NewLabel ){ m_GeneralMCLabels.push_back(NewLabel);}   // Label used on the Legend 
  void addGeneralMCCuts( TString NewCut ){     m_GeneralMCCuts.push_back(NewCut);}       // Cut used for the relevant Cut/Mode
  void addSimpleMCName( TString NewDecayList ){m_SimpleMCNames.push_back(NewDecayList);} // A simple name for when printing/writing Cut/Mode to a file
  //--------------------------------------------------------------
  //void editGeneralMCCuts(int CutVecPosition, TString addedCut ){ m_GeneralMCCuts[VecPosition].second = m_GeneralMCCuts[VecPosition].second+FSAND+"("+addedCut+")" ;}       // Cut used for the relevant Cut/Mode
  //--------------------------------------------------------------

  //void addVariableMode( TString ModeLabel, TString VariableCut , TString LegendLabel, TString ExtraTag = ""){
    //TString OutputCut;
    //TString OutputLabel;
    //TString InitialLabel = "";        TString EndLabel = "";
    // Setting up incase I want to differentiate, OTHERWISE, just typye NO or something
    //if(ModeLabel!="NO"){
    //  if(ModeLabel.Contains("Sig")||ModeLabel.Contains("SIG")){       InitialLabel = "#splitline{Signal}{";     }
    //  else if(ModeLabel.Contains("Back")|ModeLabel.Contains("BACK")){ InitialLabel = "#splitline{Background}{"; }
    //  else{ InitialLabel = "#splitline{"+ModeLabel+"}{ "; }
    //  EndLabel = "}";
    //}
  //}


  // Probably not needed but can 
  void addMCModeInfo( FSModeInfo* NewFSModeDecay ){ m_modes.push_back(NewFSModeDecay);}
  void dumpGeneralMC(){
    m_GeneralMCCuts.clear();
    m_GeneralMCLabels.clear();
    m_SimpleMCNames.clear();
    m_modes.clear();
  }
  void removeGeneralMCLabels(){ m_GeneralMCLabels.pop_back();}
  void removeGeneralMCCuts(){   m_GeneralMCCuts.pop_back();}
  void removeSimpleMCName(){    m_SimpleMCNames.pop_back();}
  
  // SHOULD PROBABLY break this apart into 3/4 Functions to get each piece individually and use here.
  // IntialDecayString to just show where the intermediate state comes from just is case... (useful for histogram legend)
  void addGeneralMCDecay(TString IntialDecayString, TString ModeLabel, TString ISDecayString = "" , TString FSDecayString = "", TString ExtraCut = ""){
    TString IScut;
    TString ISlabel;
    vector<int> ISpdgNums;
    TString dummyISDecayString;
    vector<int> dummyISpdgNums;
    if(ISDecayString.Contains("Ngamma")){
      cout << "Is it gonna fuck up?" << endl;
      dummyISDecayString = FSString::parseTString(ISDecayString,"Ngamma")[0];  // if ISDS is 'mu+ mu- Ngamma', gives 'mu+ mu-'
      ISpdgNums  = ParticlesToIDs(dummyISDecayString);          // The initial particles without the Ngamma, Saving for later
      cout << "Base Cut String: " << dummyISDecayString << endl;
      dummyISpdgNums = ParticlesToIDs(dummyISDecayString);      // A dummy to add photons for Ngamma
      dummyISpdgNums.push_back(22);      // Adding first photon
      IScut = getMCDecayParts(dummyISpdgNums);
      for(int i = ISpdgNums.size() +1 ; i < 6 ; i++ ){
        dummyISpdgNums.push_back(22);
        IScut = IScut +FSOR+ getMCDecayParts(dummyISpdgNums);
      }
      //---------------------------------
      //if(dummyISpdgNums.size()<3) IScut = getMCDecayParts(dummyISpdgNums.push_back(dumGamma));                // if only 2 things, adding a gamma
      //if(dummyISpdgNums.size()<4) IScut = IScut +FSOR+ getMCDecayParts(dummyISpdgNums.push_back(dumGamma));   // if only 3 things, adding another gamma
      //if(dummyISpdgNums.size()<5) IScut = IScut +FSOR+ getMCDecayParts(dummyISpdgNums.push_back(dumGamma));   // if only 4 things, adding another gamma
      //if(dummyISpdgNums.size()<6) IScut = IScut +FSOR+ getMCDecayParts(dummyISpdgNums.push_back(dumGamma));   // if only 5 things, adding another gamma
      //---------------------------------
      IScut = "("+IScut+")";
      cout << IScut << endl;
    }
    else if(ISDecayString.Contains("gamma chicJ")||ISDecayString.Contains("gamma chi_cJ")){
      //ISpdgNums = ParticlesToIDs("gamma chi_c0"); // A dummy input to 
      IScut = getMCDecay("gamma chi_c0")+FSOR+getMCDecay("gamma chi_c1")+FSOR+getMCDecay("gamma chi_c2");
      cout << IScut << endl;
      IScut = "("+IScut+")";
    }
    else if(ISDecayString.Contains("pi pi Jpsi")){
      //ISpdgNums = ParticlesToIDs("gamma chi_c0"); // A dummy input to 
      IScut = getMCDecay("pi+ pi- Jpsi")+FSOR+getMCDecay("pi0 pi0 Jpsi");
      cout << IScut << endl;
      IScut = "("+IScut+")";
    }
    else{
      ISpdgNums = ParticlesToIDs(ISDecayString); 
      if(ISpdgNums.size()>0){ IScut = getMCDecayParts(ISpdgNums); }
    }
    //---------------------------------
    // Pre-made function to get Intermediate State Cuts, Now just need root label
    //---------------------------------
    // Spacial Cases Up Top
    if(ISDecayString.Contains("gamma chicJ")||ISDecayString.Contains("gamma chi_cJ")){
      ISlabel = "gamma chi_{cJ}";
    }
    //---------------------------------
    else if(ISDecayString.Contains("pi pi Jpsi")){
      ISlabel = "pi pi J/psi";
    }
    //---------------------------------
    else if(ISpdgNums.size()>0){ 
      for(int i=0 ; i < ISpdgNums.size(); i++){
        if(i==0){ ISlabel = FSPhysics::pdgName(ISpdgNums[i]); }
        else{    ISlabel = ISlabel+" "+FSPhysics::pdgName(ISpdgNums[i]); }
      }
      ISlabel = FSString::removeWhiteSpace(ISlabel);
      if(ISDecayString.Contains("Ngamma")){  
        ISlabel = ISlabel+" "+"N#gamma";
      }
    }
    //---------------------------------
    else{
      ISlabel = "";
    }
    //=================================
    // Based on parentheses in FSDecayString like    e+ e- ( nu nu n n )
    // Will check/get Extra info and try to use/label properly, then add to normal MCDC12
    bool NoExtras = !(FSDecayString.Contains("("));
    TString MCDCcut;
    TString MCDClabel;
    // Getting Extras Info: 
    // Makeing FS Cut and Labels
    if(FSDecayString.Sizeof()>1){
      FSModeInfo dummyFS(FSString::parseTString(FSDecayString,"(")[0]);
      if(NoExtras){  
        MCDCcut = dummyFS.modeString("(MCDecayCode1==MODECODE1 && MCDecayCode2==MODECODE2)");
      }
      if(!NoExtras){ 
        MCDCcut = dummyFS.modeString("(MCDecayCode1==MODECODE1 && MCDecayCode2==MODECODE2 && MCExtras=="+getMCExtrasNum(FSDecayString)+")");
      }
      FSDecayString = FSString::removeWhiteSpace(FSDecayString);
    }
    TString OutputCut;
    TString OutputLabel;
    TString InitialLabel = "";        TString EndLabel = "";
    // Setting up incase I want to differentiate, OTHERWISE, just typye NO or something
    if(ModeLabel!="NO"){
      if(ModeLabel.Contains("Sig")||ModeLabel.Contains("SIG")){       InitialLabel = "#splitline{Signal}{";     }
      else if(ModeLabel.Contains("Back")|ModeLabel.Contains("BACK")){ InitialLabel = "#splitline{Background}{"; }
      else{ InitialLabel = "#splitline{"+ModeLabel+"}{ "; }
      EndLabel = "}";
    }
    // Setting up output strings FINALLY:
    cout << "======= Setting up output strings =======" << endl;
    if(IntialDecayString.Sizeof()>1){ InitialLabel = InitialLabel+IntialDecayString;}
    cout << InitialLabel << endl;
    if(IntialDecayString.Sizeof()>1  && FSDecayString.Sizeof()>1){
      OutputCut   = IScut+FSAND+MCDCcut;
      OutputLabel = InitialLabel+FSString::rootSymbols(ISlabel+"\\rightarrow"+FSDecayString)+EndLabel;
    }
    if(IntialDecayString.Sizeof()==1 && FSDecayString.Sizeof()>1){
      OutputCut   = MCDCcut;
      OutputLabel = InitialLabel+FSString::rootSymbols(FSDecayString)+EndLabel;
    }
    if(IntialDecayString.Sizeof()>1  && FSDecayString.Sizeof()==1){
      OutputCut   = IScut;
      OutputLabel = InitialLabel+FSString::rootSymbols(ISlabel)+EndLabel;
    }
    if(ExtraCut!=""){ OutputCut = OutputCut+FSAND+"("+ExtraCut+")"; }
    m_GeneralMCTag.push_back(FSString::removeWhiteSpace(ModeLabel+"_"+ISDecayString+"->"+FSDecayString));
    m_GeneralMCLabels.push_back(OutputLabel);
    m_GeneralMCCuts.push_back("("+OutputCut+")");
    m_SimpleMCNames.push_back(ISDecayString+"->"+FSDecayString);
    cout << "======= Adding Decay to MC Labels/Cuts =======" << endl;
    //cout << OutputLabel << endl;
    //cout << "("+OutputCut+")" << endl;
    return;
  }

  // Can use function to group the File with associated cuts (Makes applying cuts way easier [I believe...])
  // Based on some File-Tag and the MCcut (may make specific cut add-er function later)
  /*
  vecter<pair<TString,TString>> function(TString Set, bool KeepSigCuts){
    vecter<pair<TString,TString>> OutputPair;
    vecter<TString> SavedModeCutIndicies;
    TString Set = m_Set;
    for(int i = 0 ; i < m_GeneralMCCuts.size() ; i++ ){
      if(m_GeneralMCLabels[i].Contains("Signal")){
      }
    }
  }
  */

  ///////////////////////////////////////////////////////////////
  /*
  void displayless(){
    cout  <<  "=========================================================="<<endl;
    cout  <<  "      Cuts Applied on "+m_Set << endl;   
    cout  <<  "   Cut Version Used :  " <<  m_CutVersion   << endl;   
    cout  <<  "=========================================================="<<endl;
    //------------------------------------------
    cout<<"The ParticlesAndLabels pair-vector has: " << endl;
    printCutVecExcept( m_ParticlesAndLabels    ,"");
    //------------------------------------------
    cout<<"The Tracks pair-vector has: " << endl;
    printCutVecExcept( m_Tracks    ,"");
    //------------------------------------------
    cout<<"The Showers pair-vector has: " << endl;
    printCutVecExcept( m_Showers      ,"");
    //------------------------------------------
    cout<<"The Charged pi pair-vector has: " << endl;
    printCutVecExcept( m_piCs      ,"");
    //------------------------------------------
    cout<<"The Neutral pi pair-vector has: " << endl;
    printCutVecExcept( m_pi0s      ,"");
    //------------------------------------------
    cout<<"The Electron pair-vector has: " << endl;
    printCutVecExcept( m_electrons      ,"");
    //------------------------------------------
    cout<<"The Muons pair-vector has: " << endl;
    printCutVecExcept( m_muons      ,"");
    //------------------------------------------
    cout<<"The Protons pair-vector has: " << endl;
    printCutVecExcept( m_protons       ,"");
    //------------------------------------------
    cout<<"The Kaons pair-vector has: " << endl;
    printCutVecExcept( m_kaons      ,"");
    //------------------------------------------
    cout<<"The Etas pair-vector has: " << endl;
    printCutVecExcept(  m_etas      ,"");
    //------------------------------------------
    cout<<"The ExtraInfo vector has: (May add stuff eventually) ";
    printCutVecExcept(  m_ExtraInfo      ,"");
    //------------------------------------------
    cout<<"The MCModeCode (FSRoot numbering) int pair-vector has: "<< endl;
    
    //------------------------------------------
    if(BAHCuts::checkCut(m_AdditionalCuts)){
      cout << m_AdditionalCuts << endl;
      THINLINE();
    }     
  }
  

    cout<<"The ExtraInfo vector has: (May add stuff eventually) ";
    m_ExtraInfo.size()     }
    cout<<endl<<"-------------------------------------------"<<endl;
    cout<<"The MCModeCode (FSRoot numbering) int pair-vector has: "<< endl;
    for (unsigned int i = 0; i < m_ModeCodes.size(); i++){
      cout << "Code1: "<< m_ModeCodes[i].first << " , Code2: "<< m_ModeCodes[i].second << endl;;
    }
    cout<<"-------------------------------------------"<<endl;
    // Can get the numbers from Ryans list to add more
    cout<<"The MCDecayMode Cuts (FSRoot numbering) vector has: "<< endl; 
    m_MCDecayCodeCuts.size()    dl;
    }
    cout <<"-------------------------------------------"<<endl;
    cout<<"The MCDecayParticle Cuts (pdg numbering [can get values from Ryan's FSString]) vector has: "<< endl;   
    m_MCDecayParticleCuts.size()    <endl;
    }
    cout <<"-------------------------------------------"<<endl;
    cout<<"The GeneralMCLabels vector has: "<< endl;   
    m_GeneralMCLabels.size()    l;
    }
    cout <<"-------------------------------------------"<<endl;
    cout<<"The GeneralMCCuts [MAIN USED FOR HISTOGRAMS] vector has : "<< endl;   
    m_GeneralMCCuts.size()    
    }
  */



  // display function to print the class data members values based on object
  void display(){
    cout  <<  "==========================================="<<endl;
    cout << " For labeling for documents: Set, FS, IS  are used "<< endl;
    cout << " Set (my label for decay mode) is: "+getSet() << endl;
    cout << " IS  (Intermediate State)      is: "+getIS() << endl;
    cout << " FS  (Final State)             is: "+getFS() << endl;
    cout << " The category label for FSMode is : "+getCategory() << endl;
    cout<<"-------------------------------------------"<<endl;
    cout << " The first  Mass Variable   ("+getIS()+") : "+getMass1Var() << endl;
    cout << " The second Mass Variable   (Tau or Mass) : "+getMass2Var() << endl;
    cout<<"-------------------------------------------"<<endl;
    cout << " The Histogram Title is: " << endl << getTitle() << endl;
    cout <<"==========================================="<<endl;
    cout<<"The ParticlesAndLabels pair-vector has: " << endl;
    for (unsigned int i = 0; i < m_ParticlesAndLabels.size(); i++){
      cout << m_ParticlesAndLabels[i].first << " " << m_ParticlesAndLabels[i].second<< endl;
    }
    cout<<"-------------------------------------------"<<endl;
    cout<<"The Tracks pair-vector has: " << endl;
    for (unsigned int i = 0; i < m_Tracks.size(); i++){
      cout << m_Tracks[i].first << " " << m_Tracks[i].second<< endl;
    }
    cout<<"-------------------------------------------"<<endl;
    cout<<"The Showers pair-vector has: " << endl;
    for (unsigned int i = 0; i < m_Showers.size(); i++){
      cout << m_Showers[i].first << " " << m_Showers[i].second<< endl;
    }
    cout<<"-------------------------------------------"<<endl;
    cout<<"The Charged pi pair-vector has: " << endl;
    for (unsigned int i = 0; i < m_piCs.size(); i++){
      cout << m_piCs[i].first << " " << m_piCs[i].second<< endl;
    }
    cout<<"-------------------------------------------"<<endl;
    cout<<"The Neutral pi pair-vector has: " << endl;
    for (unsigned int i = 0; i < m_pi0s.size(); i++){
      cout << m_pi0s[i].first << " " << m_pi0s[i].second<< endl;
    }
    cout<<"-------------------------------------------"<<endl;
    cout<<"The Electron pair-vector has: " << endl;
    for (unsigned int i = 0; i < m_electrons.size(); i++){
      cout << m_electrons[i].first << " " << m_electrons[i].second<< endl;
    }
    cout<<"-------------------------------------------"<<endl;
    cout<<"The Muons pair-vector has: " << endl;
    for (unsigned int i = 0; i < m_muons.size(); i++){
      cout << m_muons[i].first << " " << m_muons[i].second<< endl;
    }
    cout<<"-------------------------------------------"<<endl;
    cout<<"The Protons pair-vector has: " << endl;
    for (unsigned int i = 0; i < m_protons.size(); i++){
      cout << m_protons[i].first << " " << m_protons[i].second<< endl;
    }
    cout<<"-------------------------------------------"<<endl;
    cout<<"The Kaons pair-vector has: " << endl;
    for (unsigned int i = 0; i < m_kaons.size(); i++){
      cout << m_kaons[i].first << " " << m_kaons[i].second<< endl;
    }
    cout<<"-------------------------------------------"<<endl;
    cout<<"The Etas pair-vector has: " << endl;
    for (unsigned int i = 0; i < m_etas.size(); i++){
      cout << m_etas[i].first << " " << m_etas[i].second<< endl;
    }
    cout<<"-------------------------------------------"<<endl;
    cout<<"The ExtraInfo vector has: (May add stuff eventually) ";
    for (unsigned int i = 0; i < m_ExtraInfo.size(); i++){
      cout << m_ExtraInfo[i] << " ";
    }
    cout<<endl<<"-------------------------------------------"<<endl;
    cout<<"The MCModeCode (FSRoot numbering) int pair-vector has: "<< endl;
    for (unsigned int i = 0; i < m_ModeCodes.size(); i++){
      cout << "Code1: "<< m_ModeCodes[i].first << " , Code2: "<< m_ModeCodes[i].second << endl;;
    }
    cout<<"-------------------------------------------"<<endl;
    // Can get the numbers from Ryans list to add more
    cout<<"The MCDecayMode Cuts (FSRoot numbering) vector has: "<< endl; 
    for (unsigned int i = 0; i < m_MCDecayCodeCuts.size(); i++){
      cout << m_MCDecayCodeCuts[i] << endl;
    }
    cout <<"-------------------------------------------"<<endl;
    cout<<"The MCDecayParticle Cuts (pdg numbering [can get values from Ryan's FSString]) vector has: "<< endl;   
    for (unsigned int i = 0; i < m_MCDecayParticleCuts.size(); i++){
      cout << m_MCDecayParticleCuts[i] <<endl;
    }
    cout <<"-------------------------------------------"<<endl;
    cout<<"The GeneralMCLabels vector has: "<< endl;   
    for (unsigned int i = 0; i < m_GeneralMCLabels.size(); i++){
      cout << m_GeneralMCLabels[i] <<endl;
    }
    cout <<"-------------------------------------------"<<endl;
    cout<<"The GeneralMCCuts [MAIN USED FOR HISTOGRAMS] vector has : "<< endl;   
    for (unsigned int i = 0; i < m_GeneralMCCuts.size(); i++){
      cout << m_GeneralMCCuts[i] <<endl;
    }
    cout <<"==========================================="<<endl;
  }
};

void printdecay(TString Set){
    // creating object of class using default constructor
    BAHDecays TEST(Set);
    //TEST.Decay(Set);
    if(TEST.badinput()){ BAHDecays::shit(); return;}  // if bad input, then stopping
    
    // printing class data members 
    cout << endl << endl;
    //TEST.addGeneralMCDecay("INCMC","tau+ tau-");
    TEST.addGeneralMCDecay("#psi(2S) #rightarrow","3686 INCMC","gamma chicJ");
    //TEST.display();
    return;
}

#endif