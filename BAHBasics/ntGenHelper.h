//#if !defined(NTGENHELPER_H)
//#define NTGENHELPER_H

 #include "BAHUtilities.h"
 #include "BAHDecays.h"
 #include "FileHelper.h"
  // vscode-fold=1 

//=========================================================================================================
TString FNS;    TString NTS;
TString FNI;    TString NTI;
TString FNSg;   TString NTSg;
void FNNT( TString Set , bool inclusive){
  TString ntXXX; TString gen;
    if(inclusive){ ntXXX="ntINC";  gen="in";}
      else{        ntXXX="ntEXC";  gen="ex";}
    FNS = getFN(Set,ntXXX,"SIGMC"); 
    NTS = getNT(Set,ntXXX);
    /////////////////////////////////
    FNI = getFN(Set,ntXXX,"INCMC"); 
    NTI = getNT(Set,ntXXX);   
    ///////////////////////////////// 
    FNSg = getFN(Set,"ntGEN"+gen,"SIGMC"); 
    NTSg = getNT(Set,"ntGEN");
    /////////////////////////////////
    SPACEstr("SIGMC FN/NT");
    cout << FNS << endl;
    cout << NTS << endl;
    SPACEstr("INCMC FN/NT");
    cout << FNI << endl;
    cout << NTI << endl;
    SPACEstr("DATA  FN/NT");
    cout << FNSg << endl;
    cout << NTSg << endl;
    SPACEin();
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
vector<pair<TString,int>> getGenNum(int dummy, bool dump=true){  // Currently just looking at SIGMC for scaling
  vector<pair<TString,int>> ModeStuff;
  TString Set;
  bool inclusive;
  // SIGNAL SAMPLES
  if(dummy==0){ Set = "gtm";  inclusive = true;}
  if(dummy==1){ Set = "get";  inclusive = true;}
  if(dummy==2){ Set = "gep";  inclusive = true;}
  if(dummy==3){ Set = "gepp"; inclusive = true;}
  // CONTROL SAMPLES
  if(dummy==4){ Set = "eepp"; inclusive = true; }
  if(dummy==5){ Set = "mmpp"; inclusive = true; }
  if(dummy==6){ Set = "gpp";   inclusive = false; }
  if(dummy==7){ Set = "gPP";   inclusive = false; }
  if(dummy==8){ Set = "gkk";   inclusive = false; }
  if(dummy==9){ Set = "etgpp"; inclusive = false; }
  //1if(dummy==11){Set = "gpp";  inclusive = true; }
  //if(dummy==12){Set = "gPP";  inclusive = true; }
  //=============================================
  FNNT(Set,inclusive);     // Eventually differentiate with years (not need atm i think...)
  BAHDecays DecayInfo(Set);
  if(DecayInfo.badinput()){ BAHDecays::shit(); return ModeStuff;}  // if bad input, then stopping
  FSHistogram::readHistogramCache("../OUTcacheDepot/ntGENtot_"+Set);
  vector<double> GenNumVec;
  //=============================================
  vector<TString> GeneralMCCuts= DecayInfo.getGeneralMCCuts();
  vector<TString> SimpleMCNames = DecayInfo.getSimpleMCNames();
  //=============================================
  // BECAUSE FN/NT is JUST ntGEN, no need for modehistogram/category. Its all in there and wont re-scan unnessesarily
  //       Inputs: (FN|NT|MCCuts|non-MCCuts)
  for(int i=0 ; i < GeneralMCCuts.size() ; i++){
    ModeStuff.push_back(make_pair(SimpleMCNames[i],counter(FNSg,NTSg,DecayInfo.getGeneralMCCuts()[i],noCut)));
  }
  //=============================================
  SPACEstr("SIGMC events in ntGEN "+Set);
  //=============================================
  if(dump){FSHistogram::dumpHistogramCache("../OUTcacheDepot/ntGENtot_"+Set);}
  //=============================================
  //vector<FSModeInfo*> Modes = FSModeCollection::modeVector(DecayInfo.getCategory());
  SPACEin();
  for(int i=0 ; i < GeneralMCCuts.size() ; i++){
    cout << " Number of Events [ "+ModeStuff[i].first+" ]: "<< std::setprecision(7) <<ModeStuff[i].second << endl;
    cout << "--------------" << endl;
    cout << GeneralMCCuts[i] << endl;
    SPACEin();
  }
  return ModeStuff;
}

void checkAllGEN(){
  FSControl::QUIET=true;
  //FSControl::HISTOGRAMCACHING=false;
  vector<pair<TString,int>> ModeStuff;
  vector<pair<TString,int>> dummy;
  for(int i=0 ; i < 10 ; i++){
    dummy = getGenNum(i);
    ModeStuff.insert(ModeStuff.end(), dummy.begin(), dummy.end());
  }
    SPACEstr("---------------------------");
    SPACEstr("---------------------------");
    SPACEstr(" ALL DECAY MODES GENERATED ");
  for(int i=0 ; i < ModeStuff.size(); i++){
    cout << " Number of Events [ "+ModeStuff[i].first+" ]: "<< std::setprecision(7) << ModeStuff[i].second << endl;
    cout << "---------------------------" << endl;
  }
  return;
}



/*

void getGenCHECK(int dummy, bool dump=true){  // Currently just looking at SIGMC for scaling 
  TString Set;
  if(dummy==1){ Set = "gtm"; }  // DON'T HAVE mu SIGMC done.
  if(dummy==2){ Set = "get"; }
  if(dummy==3){ Set = "gep"; }
  if(dummy==4){ Set = "gepp";}
  //=============================================
  FNNT(Set);     // Eventually differentiate with years
  BAHDecays DecayInfo(Set);
  if(DecayInfo.badinput()){ BAHDecays::shit(); return;}  // if bad input, then stopping
  FSHistogram::readHistogramCache("../cacheDepot/ntGENtot_"+Set);
  double GenNum0;
  double GenNum1;
  double GenNum2;
  double GenNumMode;
  double GenNumTOT;
  double GenNum0i;
  double GenNum1i;
  double GenNum2i;
  //=============================================
  vector<TString> ModeCodeCuts = DecayInfo.getModeCodeCuts();
  vector<TString> MCDecayISCuts= DecayInfo.getMCDecayParticleCuts();
  //=============================================
  // BECAUSE FN/NT is JUST ntGEN, no need for modehistogram/category. Its all in there and wont re-scan unnessesarily
  //       Inputs: (FN|NT|MCCuts|non-MCCuts)
  GenNum0 = counter(FNSg,NTSg,DecayInfo.getGeneralMCCuts()[0],noCut);
  GenNum1 = counter(FNSg,NTSg,DecayInfo.getGeneralMCCuts()[1],noCut);
  GenNum2 = counter(FNSg,NTSg,DecayInfo.getGeneralMCCuts()[2],noCut);
  GenNumMode = counter(FNSg,NTSg,ModeCodeCuts[0]+FSOR+ModeCodeCuts[1],noCut);
  //=============================================
  GenNumTOT= counter(FNSg,NTSg,noCut,noCut);
  GenNum0i = counter(FNSg,NTSg,MCDecayISCuts[0],noCut);
  GenNum1i = counter(FNSg,NTSg,MCDecayISCuts[1],noCut);
  GenNum2i = counter(FNSg,NTSg,MCDecayISCuts[2],noCut);
  //=============================================
  //GenNum0t = counter(FNSg,NTSg,MCDecayISCuts[0],noCut);
  //GenNum1t = counter(FNSg,NTSg,MCDecayISCuts[1],noCut);
  //GenNum2t = counter(FNSg,NTSg,MCDecayISCuts[2],noCut);
  //=============================================
  if(dump){FSHistogram::dumpHistogramCache("../cacheDepot/ntGENtot_"+Set);}
  //=============================================
  SPACEstr("SIGMC events in ntGEN "+Set);
  //=============================================
  SPACEin();
  SPACEstr("Chic0 signal in ntGen and cuts applied");
  cout << DecayInfo.getGeneralMCCuts()[0] << endl;
  cout << "//++++++ "+Set+" Chic0 generated:  "<< std::setprecision(7) << GenNum0  << endl;
  SPACEin();
  SPACEstr("Chic1 signal in ntGen and cuts applied");
  cout << DecayInfo.getGeneralMCCuts()[1] << endl;
  cout << "//++++++ "+Set+" Chic1 generated:  "<< std::setprecision(7) << GenNum1  << endl;
  SPACEin();
  SPACEstr("Chic2 signal in ntGen and cuts applied");
  cout << DecayInfo.getGeneralMCCuts()[2] << endl;
  cout << "//++++++ "+Set+" Chic2 generated:  "<< std::setprecision(7) << GenNum2  << endl;
  SPACEin();
  SPACEin();
  SPACEstr(Set+" total in ntGen and cuts applied");
  cout << ModeCodeCuts[0]+FSOR+ModeCodeCuts[1] << endl;
  cout << "//++++++ "+Set+" generated:  "<< std::setprecision(7) << GenNumMode  << endl;
  SPACEin();
  SPACEstr("Difference in Total gen vs chicJ tot gen for Set"+Set+":");
  cout << "//++++++ "+Set+" Difference:  "<< std::setprecision(7) << GenNumMode-(GenNum0+GenNum1+GenNum2)  << endl;
  SPACEin();
  SPACEin();
  SPACEstr("Now checking total vs all three chicJ [final state doesnt matter]:");
  cout << "//++++++ Chic0 generated:  "<< std::setprecision(7) << GenNum0i  << endl;
  cout << "//++++++ Chic1 generated:  "<< std::setprecision(7) << GenNum1i  << endl;
  cout << "//++++++ Chic2 generated:  "<< std::setprecision(7) << GenNum2i  << endl;
  cout << "//++++++ Total in ntGEN :  "<< std::setprecision(7) << GenNumTOT  << endl;
  cout << "//++++++ Difference     :  "<< std::setprecision(7) << GenNumTOT -(GenNum0i+GenNum1i+GenNum2i)  << endl;
  SPACEin();
  SPACEstr("Done with ntGEN total check");
  return;
}
*/