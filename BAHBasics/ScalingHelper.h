#if !defined(SCALINGHELPER_H)
#define SCALINGHELPER_H

 #include "BAHUtilities.h"
 #include "BAHDecays.h"
 #include "BAHCuts.h"
 #include "FileHelper.h"
 #include "BAHPhysics.h"

//=======================================================================================================
// Based on the results, will set the cross section of e+e- -> psi(2S) to be  6.72887e-07 so N ~ 329.666 Million
void ApproxCS(TString Energy = "3686", TString Particle = "psi2S"){
  vector<pair<double,double>> ApproxXsection;  // N/Sigma
  // N=Sigma*Lumin -> Sigma =N/Lumin
  if( Energy=="3686" && Particle=="psi2S" ){// [Lumin]=picobarns^{-1}
    ApproxXsection.push_back(make_pair(107.0*pow(10,6),161.63*pow(10,12)));  // To print out estimated CS[ee->psi(2S),3686] in 2009
    ApproxXsection.push_back(make_pair(341.1*pow(10,6),506.92*pow(10,12)));  // To print out estimated CS[ee->psi(2S),3686] in 2012
    ApproxXsection.push_back(make_pair(448.1*pow(10,6),668.55*pow(10,12)));  // To print out estimated CS[ee->psi(2S),3686] in 09/12
    ApproxXsection.push_back(make_pair(2.260*pow(10,9),3.21*pow(10,15)));    // To print out estimated CS[ee->psi(2S),3686] in 2021
  }  // Semi-Data Lumin is approximately 485.0538 ~ 2012 lumin
  for( int i=0; i < ApproxXsection.size(); i++ ){
    cout<<"For  [ N , Lumin ]-> Sigma of psi(2S)  =  [ "<<ApproxXsection[i].first<<" , "<<ApproxXsection[i].second<<"]  -> "<< ApproxXsection[i].first/ApproxXsection[i].second << endl;  
  }
  cout<<"So estimating Sigma*Lumin of psi(2S) Semi-Data is  = "<<6.7964767*pow(10,-7)<<" * "<<485053.8*pow(10,9)<<" = "<< 6.7964767*pow(10,-7)*485053.8*pow(10,9) << endl; 
}
//=======================================================================================================
double getINCScaleMode(TString INCMCtag, TString DATAtag="FULL", TString MCMode=""){
  double dataEvents = 1.0;
  double incmcEvents= 1.0;
  //========== FROM CHARM GROUP WEBSITE (for all 3770 7.1.0) ==========
  // e+ e-      =   * 0.5 
  // gammagamma =   * 5
  // mu+ mu-    =   * 15
  // D0D0bar    =   * 80 (probably doesn't matter)
  // All others =   * 40
  if(INCMCtag.Contains("70")&&MCMode.Contains(BAHDecays::getMCDecayParts(ParticlesToIDs("e+ e- gamma")))){return 2.0;}
  if(INCMCtag.Contains("70")&&MCMode.Contains(BAHDecays::getMCDecayParts(ParticlesToIDs("mu+ mu- gamma")))){return 1.0/15.0;}
  if(INCMCtag.Contains("70")&&MCMode.Contains(BAHDecays::getMCDecayParts(ParticlesToIDs("D0bar D0")))){return 1.0/80.0;}
  if(INCMCtag.Contains("70")&&MCMode.Contains(BAHDecays::getMCDecayParts(ParticlesToIDs("tau+ tau-")))){return 1.0/40.0;}
  else if( INCMCtag.Contains("70")){ 
    return 1.0/40.0;  // Since I only have maybe 2/5s of the INCMC
  }
  else{ return 1.0;} // Assume INCMC at scale of Data or whatever...
}
//=======================================================================================================
double getINCScale(TString INCMCtag, TString DATAtag="FULL"){
  double dataEvents = 1.0;
  double incmcEvents= 1.0;
  if(INCMCtag.Contains("70")){ 
    return dataEvents/40.0;
  }
  if(DATAtag==INCMCtag){ return 1.0; }
  //=================================
  if(INCMCtag=="12"){ incmcEvents = 107*pow(10,6);}
  if(INCMCtag=="12"){ incmcEvents = 341*pow(10,6);}
  if(INCMCtag=="21"){ incmcEvents = 2.3*pow(10,9);}
  if(INCMCtag=="FULL"){incmcEvents= 341*pow(10,6)+2.3*pow(10,9)+107.0*pow(10,6);} //
  //=================================
  if( DATAtag=="12"){   dataEvents  = 341*pow(10,6);}
  if( DATAtag=="SEMI"){ dataEvents  = 329.666*pow(10,6);} // Approximation based on ApproxCS() above
  //=================================
  cout << dataEvents/incmcEvents << endl;
  return dataEvents/incmcEvents;
}
//=======================================================================================================
double getCONTScale(TString CONTtag, TString DATAtag="FULL", bool print=false){ // ONLY NEED YEAR. Cyr redundant at this point. NO NEED TO SCALED INDIVIDUAL ASPECTS/MODES
  double LuminD;
  double LuminC;
  double CONTenergy; // in MeV
  double DATAenergy = 3686.0; // in MeV
  double Ndata;
  double Ncont;
  if((CONTtag=="")&&(DATAtag=="")){return 1.0;}
  if(DATAtag=="INC"||DATAtag=="FULL"){LuminD = 3208.5+506.92+161.63; }//
  if(DATAtag=="09"){LuminD = 161.63;}
  if(DATAtag=="12"){LuminD = 506.92;}
  if(DATAtag=="21"){LuminD = 3208.5;}
  if(DATAtag=="SEMI"){LuminD = (48260.4 +  48937.4 + 387856)/1000;}
  //=================================
  // Only using 3770 atm...
  //if(CONTtag.Contains("70")){
  if(CONTtag=="21"||CONTtag=="11"||CONTtag=="FULL70"){
    CONTenergy = 3770.0;
    if(CONTtag=="21"){ LuminC = 4977.0; }
    if(CONTtag=="11"){ LuminC = 2931.8; }
    if(CONTtag=="FULL70"){ LuminC = 4977.0 + 2931.8; }
  }
  //=================================
  //=================================
  if(CONTtag.Contains("3650")){
    CONTenergy = 3650.0;
    if(CONTtag.Contains("2022")){ LuminC = 410.0; }
  }
    Ndata = LuminD/pow(DATAenergy,2);
    Ncont = LuminC/pow(CONTenergy,2); 
  //=================================
  if(print){
  SPACEin();
  cout << "Data-tag= "+DATAtag+"     ,     C-tag= "+CONTtag+"    ,   Continuum Energy = " << CONTenergy << endl;
  cout << DATAenergy << endl;
  cout << LuminD << endl;
  cout << CONTenergy << endl;
  cout << LuminC << endl;
  cout << Ndata << endl;
  cout << Ncont << endl;
  }
  return Ndata/Ncont;
}
//=======================================================================================================
// Used to get the found number of MC signal events generated and the BR associated with the decay mode of interest [useful for getting efficiencies]
vector<double> getSIGValues(TString IntermedState, TString Set){
  // TString DataSetLabel, 
  vector<double> outputvec;
  //TString InputInfo = FSString::parseTString(DataSetLabel,".")[0]; // INC-ntINC or EXC-ntINC [ or INC-ntGEN or EXC-ntGEN]
  double IntermedStateBR;
  double FinalStateBR;
  double SignalGenerated;
  //////////////////////////////////////////////////////////////////
  if(IntermedState.Contains("Xc0")||IntermedState.Contains("chic0")){
    //IntermedStateBR = 0.0968; // psi(2s) to gamma chi_c0  via DECAY.DEC
    IntermedStateBR = 0.0977; // psi(2s) to gamma chi_c0  via PDG value
    // Control Modes
    //if(InputInfo.Contains("INC-nt")){
      if(Set=="gPP" ){ SignalGenerated=500428.0;     FinalStateBR = 0.000223; }   // chi_c0 to proton anti-proton : direct decay , INC
      //if(Set=="gpp" ){ SignalGenerated=500312.0;     FinalStateBR = 0.0057;   } // chi_c0 to pi+ pi-  : direct decay , INC
    //}
    //if(InputInfo.Contains("EXC-nt")){
      //if(Set=="gPP" ){ SignalGenerated=499754.0;     FinalStateBR = 0.000223; }   // chi_c0 to proton anti-proton : direct decay , EXC
      if(Set=="gpp" ){ SignalGenerated=501087.0;     FinalStateBR = 0.0057;   }   // chi_c0 to pi+ pi-  : direct decay , EXC
      if(Set=="gkk" ){ SignalGenerated=499381.0;     FinalStateBR = 0.00606;   }   // chi_c0 to K+ K-  : direct decay , EXC
    //}
    // Signal Modes
    if(Set=="gtm" ){ SignalGenerated=999547.0;     FinalStateBR = 0.000223*0.1739/10.0; }  // chi_c0 to tau mu (as "pbar{p}/10") where tau to e 2nu
    if(Set=="get" ){ SignalGenerated=1000272.0;    FinalStateBR = 0.000223*0.1782/10.0; }  // chi_c0 to tau e  (as "pbar{p}/10") where tau to mu 2nu
    if(Set=="gep" ){ SignalGenerated=999681.0;     FinalStateBR = 0.000223*0.1082/10.0; }  // chi_c0 to tau e  (as "pbar{p}/10") where tau to pi nu
    if(Set=="gepp"){ SignalGenerated=987922.0;     FinalStateBR = 0.000223*0.2549/10.0; }  // chi_c0 to tau e  (as "pbar{p}/10") where tau to pi pi0 nu
   }
  else if(IntermedState.Contains("Xc1")||IntermedState.Contains("chic1")){
    IntermedStateBR = 0.0975; // psi(2s) to gamma chi_c1 
    // Control Modes
    //if(InputInfo.Contains("INC-nt")){
      if(Set=="gPP" ){ SignalGenerated=499575.0;     FinalStateBR = 0.000073; }   // chi_c1 to proton anti-proton , INC
      //if(Set=="gpp" ){ SignalGenerated=1.0;          FinalStateBR = 0.0;      }   // Not seen so set to zero , INC
    //}
    //if(InputInfo.Contains("EXC-nt")){
      //if(Set=="gPP" ){ SignalGenerated=501371.0;     FinalStateBR = 0.000073; }   // chi_c0 to proton anti-proton : direct decay , EXC
    //}
    //  Haven't counted the unphysical gpp and gkk in chi_c1 [Shouldn't need to]
    // Signal Modes
    if(Set=="gtm" ){ SignalGenerated=1001300.0;    FinalStateBR = 0.000073*0.1739/10.0; }  // chi_c1 to tau mu (as "pbar{p}/10") where tau to e 2nu
    if(Set=="get" ){ SignalGenerated=1000259.0;    FinalStateBR = 0.000073*0.1782/10.0; }  // chi_c1 to tau e  (as "pbar{p}/10") where tau to mu 2nu
    if(Set=="gep" ){ SignalGenerated=999423.0;     FinalStateBR = 0.000073*0.1082/10.0; }  // chi_c1 to tau e  (as "pbar{p}/10") where tau to pi nu
    if(Set=="gepp"){ SignalGenerated=987748.0;     FinalStateBR = 0.000073*0.2549/10.0; }  // chi_c1 to tau e  (as "pbar{p}/10") where tau to pi pi0 nu
   }
  else if(IntermedState.Contains("Xc2")||IntermedState.Contains("chic2")){
    //IntermedStateBR = 0.0872; // psi(2s) to gamma chi_c2  via DECAY.DEC
    IntermedStateBR = 0.0936; // psi(2s) to gamma chi_c2  via PDG value
    // Control Modes
    //if(InputInfo.Contains("INC-nt")){
      if(Set=="gPP" ){ SignalGenerated=500733.0;     FinalStateBR = 0.000072; }   // chi_c2 to proton anti-proton : direct decay , INC
      //if(Set=="gpp" ){ SignalGenerated=500503.0;     FinalStateBR = 0.00162;  }   // chi_c2 to pi+ pi-  : direct decay , INC
    //}
    //if(InputInfo.Contains("EXC-nt")){
      if(Set=="gPP" ){ SignalGenerated=500299.0;     FinalStateBR = 0.000072; }   // chi_c0 to proton anti-proton : direct decay , EXC
      if(Set=="gpp" ){ SignalGenerated=499357.0;     FinalStateBR = 0.00162;   }  // chi_c0 to pi+ pi-  : direct decay , EXC
      if(Set=="gkk" ){ SignalGenerated=499338.0;     FinalStateBR = 0.00101;   }  // chi_c0 to K+ K-  : direct decay , EXC
    //}
    // Signal Modes
    if(Set=="gtm" ){ SignalGenerated=999153.0;     FinalStateBR = 0.000072*0.1739/10.0; }  // chi_c2 to tau mu (as "pbar{p}/10") where tau to e 2nu     
    if(Set=="get" ){ SignalGenerated=1000677.0;    FinalStateBR = 0.000072*0.1782/10.0; }  // chi_c2 to tau e  (as "pbar{p}/10") where tau to mu 2nu
    if(Set=="gep" ){ SignalGenerated=1000718.0;    FinalStateBR = 0.000072*0.1082/10.0; }  // chi_c2 to tau e  (as "pbar{p}/10") where tau to pi nu
    if(Set=="gepp"){ SignalGenerated=987361.0;     FinalStateBR = 0.000072*0.2549/10.0; }  // chi_c2 to tau e  (as "pbar{p}/10") where tau to pi pi0 nu
   }
  else if(IntermedState.Contains("Jpsi")||IntermedState.Contains("jpsi")){
    IntermedStateBR = 0.182; // psi(2s) to pi0 pi0 J/psi
    if(Set=="eepp"){ SignalGenerated=487661.0;     FinalStateBR = 0.05971;  }   // J/psi to e+ e- : direct decay , INC
    if(Set=="mmpp"){ SignalGenerated=487193.0;     FinalStateBR = 0.05961;  }  // J/psi to mu+ mu- : direct decay , INC
   }
  else{
    IntermedStateBR = 1.0;
    if(Set=="etgpp"){ SignalGenerated=484355.0;     FinalStateBR = 0.00087;  }   // psi(2S) to gamma eta pi+ pi- : direct decay , EXC
    //if(Set=="tt"){ SignalGenerated=484355.0;      FinalStateBR = 0.00087;  }   // psi(2S) to tau tau (need to edit for e+e- to tau tau)
    else{ 
      cout << "============== DOESNT FIT ANY CRITERIA SO USING ==============" << endl;
      SignalGenerated=500000;     FinalStateBR = 0.01;  
      cout << "=== SigGenerated: " << SignalGenerated << " , FS-BR: "<< FinalStateBR << " ===" << endl;
    }
  }
  //////////////////////////////////////////////////////////////////
  outputvec.push_back(SignalGenerated);
  outputvec.push_back(IntermedStateBR*FinalStateBR);
  cout << "Vector elements:  Signal Generated = " << outputvec[0] << "  ,  Final State BR = " << outputvec[1] << endl;
  return outputvec;
}
//=======================================================================================================
// Normal Total is set to 2012 number of psi(2S) but can be adjusted
// Can pass the Cut or IS Label. Maybe even the simple name
double getSIGScale(bool proper, TString IntermedState, TString Set, TString DATAtag){
  double NormalTotal;
  //=================================
  // Just an initial check as a bandaid at the moment...
  if(DATAtag=="SEMI"){NormalTotal  = 329.666*pow(10,6);} // Approximation based on ApproxCS() above, Lumin abit below 2012's
  if(DATAtag=="09"){  NormalTotal  = 107.0*pow(10,6);}
  if(DATAtag=="12"){  NormalTotal  = 341*pow(10,6);}
  if(DATAtag=="21"){  NormalTotal  = 2.3*pow(10,9);}
  if(DATAtag=="FULL"){NormalTotal = 341*pow(10,6) + 2.3*pow(10,9) + 107.0*pow(10,6);}
  //=================================
  if(!proper){return 0.01;} // Lazy/bad scaling to see Signal if minimal cuts applied
  double scaleoutput;  
  TString ismode;
  //////////////////////////////////////////////////////////////////
  if(IntermedState.Contains("Xc0")||IntermedState.Contains("Xc1")||IntermedState.Contains("Xc2")||IntermedState.Contains("Jpsi")){ ismode = IntermedState; }
  // In case I am using the MC info cuts instead of just the direct name used 
  else if(!(IntermedState.Contains("Xc0")||IntermedState.Contains("Xc1")||IntermedState.Contains("Xc2")||IntermedState.Contains("Jpsi"))){ 
    if( IntermedState.Contains("==10441")){ ismode = "Xc0"; }  // Xc0 
    else if( IntermedState.Contains("==20443")){ ismode = "Xc1"; }  // Xc1 
    else if( IntermedState.Contains("==445")  ){ ismode = "Xc2"; }  // Xc2 
    else if( IntermedState.Contains("==443")  ){ ismode = "Jpsi";}  // J/psi
  }
  else{
    ismode = "NO";
  }
  cout << "Using "+ismode+" as Intermediate State " << endl;
  //////////////////////////////////////////////////////////////////
  vector<double> SignalValues = getSIGValues(ismode,Set);  // Signal Generated and BR used for it.
  scaleoutput = (NormalTotal*SignalValues[1])/SignalValues[0];
  if(false){
    SPACEstr(" Inputs to scaling ");
    cout << Set << "   ,  "  << DATAtag << endl;
    cout << IntermedState << endl;
    SPACEstr(" Outputs from scaling ");
    cout << NormalTotal << endl;
    cout << SignalValues[0] << endl;
    cout << SignalValues[1] << endl;
    cout << scaleoutput << endl;
  }
  //cout << SignalValues[0] << endl;
  if(scaleoutput>100.0){cout << "==== Scaling is greater than 100!!!  Probably WRONG INPUT ====" << endl;}
  if(scaleoutput<0.0000001){cout << "==== Scaling is less than 10^(-7)!!!  Probably WRONG INPUT ====" << endl;}
  return scaleoutput;
}

//=======================================================================================================
// Important: Just a Convenient Pair of Functions for organizing the output ( Decay Mode's Label , # of events from Decay Mode)
vector<pair<TString,double>> getMCSigNums(vector<TString> FNNTvector, BAHDecays DecayInfo, TString Cuts){
  vector<pair<TString,double>> output;
  vector<TString> IS_labels = DecayInfo.getGeneralMCLabels(); // These three string-vectors should be in decay order and related
  vector<TString> IS_cuts   = DecayInfo.getGeneralMCCuts();
  vector<TString> DecayNames= DecayInfo.getSimpleMCNames();
  vector<int> NonSignalCuts;
  TString Category = DecayInfo.getCategory();
  int NumModes = FSModeCollection::modeVectorSize(Category);
  TString Label;
  cout << NumModes << endl;
  for( int i=0 ; i < IS_cuts.size() ; i++){
    // MAKE SURE THIS IS CONSISTENT WITH  BAHDecays::getSetTitle()
    if((IS_labels[i].Contains("Signal"))){
      //cout << "Checking sigmc ["<<i<<"] : " << DecayNames[i] << endl;
      output.push_back(make_pair("SIGMC "+DecayNames[i],counterMode(FNNTvector[0],FNNTvector[1],Category,IS_cuts[i],Cuts)));
    }
    // Take note of any non-signal cuts to remove them to avoid over-complicating things and just call backgrounds "INCMC1,INCMC2,..."
    else{
      //cout << "Store incmc cut ["<<i<<"] : " << DecayNames[i] << endl;
      NonSignalCuts.push_back(i);
    }
  }
  // Removing non-signal cuts (Dont need to worry about other stuff...)
  for( int i=0 ; i < NonSignalCuts.size() ; i++){
      IS_cuts.erase(IS_cuts.begin()+NonSignalCuts[i]);
  }
  //  INCMC, CONT and DATA residual nums
  TString MCChicJCuts = CutsfromCutVec(IS_cuts,"||"); // For removing any "Signal" events from INCMC (and only signal)
  if(FNNTvector[2]!=""){output.push_back(make_pair("INCMC",counterMode(FNNTvector[2],FNNTvector[3],Category,"!("+MCChicJCuts+")",Cuts)));}
  if(FNNTvector[9]!=""){output.push_back(make_pair("INCMC2",counterMode(FNNTvector[8],FNNTvector[9],Category,"!("+MCChicJCuts+")",Cuts)));}
  if(FNNTvector[4]!=""){output.push_back(make_pair( "DATA",counterMode(FNNTvector[4],FNNTvector[5],Category,noCut,Cuts)));}
  if(FNNTvector[7]!=""){output.push_back(make_pair( "CONT",counterMode(FNNTvector[6],FNNTvector[7],Category,noCut,Cuts)));}
  SPACEstr(" FINISHING GETTING LABELS, Resultant events");
  return output;
}
//===============================
// If Ncut found, can print out efficiencies based on final states
// Also returns the scaled total for SIGMC's, INCMC, CONT and DATA as well a label to differentiate 
void printSignalInfo(BAHDecays DecayInfo, vector<pair<TString,double>> ISnums, TString INCMCtag, TString DATAtag,TString CONTtag, bool ControlSample = false){
  SPACEstr(" BEGINNING TO WORK ON/PRINT RESULTS");
  THINLINE();
  TString Set = DecayInfo.getSet();
  vector<int> NonSignalCuts;
  int DecayNameSize = 13;  // For Example, TString "[3770:2021] " is length 12.
  TString StringPad;
  TString INCMCcuts = "";
  int j = 0; // INCMC cut counter
  vector<TString> IS_labels = DecayInfo.getGeneralMCLabels();
  vector<TString> IS_cuts   = DecayInfo.getGeneralMCCuts();
  if(false){
    SPACEstr(" PRINTING labels from decay class");
    for( int i=0 ; i < IS_labels.size() ; i++){
      cout << IS_labels[i] << endl;
    }
    SPACEstr(" PRINTING labels from ISnums");
    for( int i=0 ; i < ISnums.size() ; i++){
      cout << ISnums[i].first << endl;
    }
  }
  bool check=true;
  for( int i=0 ; i < ISnums.size() ; i++ ){
    if(i==0){ SPACEstr(" Efficiency of selection criteria for "+Set+" "); }
    //If doesn't contain SIGMC, Skips getting efficiecies
    if(ISnums[i].first=="INCMC"||ISnums[i].first=="DATA"||ISnums[i].first=="CONT"){
      i = i+10;       // To stop getting efficiencies 
      check = false;  // To stop printing this loop
    }
    if(check&&ISnums[i].first.Contains("SIGMC")) cout<<"+++ "+ISnums[i].first+" efficiency:  "<<std::setprecision(5)<<ISnums[i].second<<" / "<<std::setprecision(5)<<getSIGValues(ISnums[i].first,Set)[0]<<" = "<<std::setprecision(8)<<ISnums[i].second/getSIGValues(ISnums[i].first,Set)[0]*100<<"%"<< endl;
  }
  THINLINE();
  vector<pair<TString,double>> NumsScaled;
  for( int i=0 ; i < IS_labels.size() ; i++){
    if(i==0){ cout << "---- Residual events from criteria for "+Set+" scaled based on DataTag:"+DATAtag+" ----"<< endl;}
    if((IS_labels[i].Contains("Signal"))){//&&getSIGScale(1,IS_labels[i],Set,DATAtag)>0.000001)){
      //cout << "SIGMC selection: " << i << endl;
      cout << "# of Events left in "+ISnums[i].first+" :  "<<std::setprecision(7)<< ISnums[i].second<<" * "<<std::setprecision(5)<<getSIGScale(1,IS_cuts[i],Set,DATAtag)<<" = " <<std::setprecision(8)<< ISnums[i].second*getSIGScale(1,IS_cuts[i],Set,DATAtag) << endl;
      NumsScaled.push_back(make_pair(ISnums[i].first,ISnums[i].second*getSIGScale(1,IS_cuts[i],Set,DATAtag)));
    }
    if(DecayNameSize<IS_labels[i].Sizeof()&&IS_labels[i].Sizeof()<40){DecayNameSize = IS_labels[i].Sizeof(); }
  }
  StringPad = FSString::padTString(" ",round(DecayNameSize/2),"C");
  for( int i=0 ; i < ISnums.size() ; i++ ){
    if(ISnums[i].second>0&&ISnums[i].first=="INCMC"){
      cout<<"# of Events left in  INCMC  "+FSString::padTString("["+INCMCtag+"]",DecayNameSize,"L")+":  "<<ISnums[i].second<<" * "<<std::setprecision(3)<<getINCScale(INCMCtag,DATAtag)<<"  =  "<<std::setprecision(8)<<ISnums[i].second*getINCScale(INCMCtag,DATAtag)<<endl;
      NumsScaled.push_back(make_pair(ISnums[i].first,ISnums[i].second*getINCScale(INCMCtag,DATAtag)));  
    }
    if(ISnums[i].second>0&&ISnums[i].first=="INCMC2"){
      cout<<"# of Events left in  INCMC2 "+FSString::padTString("[3770:21]",DecayNameSize,"L")+":  "<<ISnums[i].second<<" * "<<std::setprecision(3)<<getINCScale("70",DATAtag)<<"*"<<std::setprecision(3)<<getCONTScale("21",DATAtag)<<"  =  "<<std::setprecision(8)<<ISnums[i].second*getINCScale("70",DATAtag)*getCONTScale("21",DATAtag)<<endl;
      NumsScaled.push_back(make_pair(ISnums[i].first,ISnums[i].second*getINCScale("70",DATAtag)*getCONTScale("21",DATAtag)));  
    }
    if(ISnums[i].second>0&&ISnums[i].first=="CONT"){
      cout<<"# of Events left in  CONT   "+FSString::padTString("["+CONTtag+"]",DecayNameSize,"L")+":  "<<ISnums[i].second<<" * "<<std::setprecision(3)<<getCONTScale(CONTtag,DATAtag)<<"  =  "<<std::setprecision(8)<<ISnums[i].second*getCONTScale(CONTtag,DATAtag)<<endl;
      NumsScaled.push_back(make_pair(ISnums[i].first,ISnums[i].second*getCONTScale(CONTtag,DATAtag)));
    }
    if(ISnums[i].second>0&&ISnums[i].first=="DATA"){
      cout<<"# of Events left in  DATA   "+FSString::padTString("["+DATAtag+"]",DecayNameSize,"L")+":  "<<std::setprecision(8)<<ISnums[i].second <<endl;  
      NumsScaled.push_back(make_pair(ISnums[i].first,ISnums[i].second*1.000));
    }
  }
  SPACEin();
  return;
}
//========================================================================
// Important: NO NEED TO EDIT ERROR FUNCTIONS, Just need SIGMC, INCMC and DATA for one Sample. Nothing Complicated....
vector<pair<double,double>> getSimpleErrorNums(BAHDecays DecayInfo, BAHCuts CutInfo, vector<TString> FNNTvec, TString INCMCtag, TString DATAtag, TString Cuts, TString CutToCheck, bool print = false){
  vector<pair<double,double>> output;
  TString category   = DecayInfo.getCategory();
  TString Set     = DecayInfo.getSet();
  TString INCcuts;
  //=====================
  vector<TString> MCDecayLabel = DecayInfo.getGeneralMCLabels();
  vector<TString> MCDecayName  = DecayInfo.getSimpleMCNames();
  vector<TString> MCDecayCut   = DecayInfo.getGeneralMCCuts();
  vector<pair<TString,TString>> MassDecayCut = CutInfo.getMass1Cuts();  // Applying the mass cut even it is redundant. Needed for Modes with multiple resonances.
  double NsigLoose;     double NincLoose;     double NdatLoose;
  double NsigTight;     double NincTight;     double NdatTight;
  double SigScale;
  double IncScale;
  //=====================
  for(int i=0 ; i < MCDecayLabel.size() ; i++){
    if(MCDecayLabel[i].Contains("Signal")){
      SigScale = getSIGScale(1,MCDecayCut[i],Set,DATAtag);
      IncScale = getINCScale(INCMCtag,DATAtag);
      INCcuts = "!("+MCDecayCut[i]+")";  // To remove any signal mc events from the INCMC to avoid double counting
      NsigLoose = counterMode(FNNTvec[0], FNNTvec[1],category,MCDecayCut[i],Cuts+FSAND+MassDecayCut[i].second);//getSIGScale(1,MCDecayCut[i],Set,DATAtag);
      NincLoose = counterMode(FNNTvec[2], FNNTvec[3],category,      INCcuts,Cuts+FSAND+MassDecayCut[i].second);//getINCScale(INCMCtag,DATAtag);
      NdatLoose = counterMode(FNNTvec[4], FNNTvec[5],category,        noCut,Cuts+FSAND+MassDecayCut[i].second);
      //=====================
      NsigTight = counterMode(FNNTvec[0], FNNTvec[1],category,MCDecayCut[i],Cuts+FSAND+MassDecayCut[i].second+FSAND+CutToCheck);//getSIGScale(1,MCDecayCut[i],Set,DATAtag);
      NincTight = counterMode(FNNTvec[2], FNNTvec[3],category,      INCcuts,Cuts+FSAND+MassDecayCut[i].second+FSAND+CutToCheck);//getINCScale(INCMCtag,DATAtag);
      NdatTight = counterMode(FNNTvec[4], FNNTvec[5],category,        noCut,Cuts+FSAND+MassDecayCut[i].second+FSAND+CutToCheck);
      //=====================
      output.push_back(make_pair(NsigLoose,NsigTight));
      output.push_back(make_pair(NincLoose,NincTight));
      output.push_back(make_pair(NdatLoose,NdatTight));
      if(print){
        THINLINE();
        cout << " Purity of Signal "<<i+1<<" ["+MCDecayName[i]+"]: "<<std::setprecision(4)<<(NsigLoose*SigScale/(NsigLoose*SigScale + NincLoose*IncScale))*100<<"%"<< endl;
        THINLINE();
      } 
    }
    else{ 
      THINLINE();
      cout << "Decay Mode " <<MCDecayLabel[i]<< endl << " is NOT signal, SKIPPING" << endl;
      THINLINE();  
    }    
  }
  return output;
}
//===============================
void printSimpleError(BAHDecays DecayInfo , BAHCuts CutInfo, vector<pair<double,double>> ErrorNums, TString CutToCheck, bool printChecks = true){
  vector<TString> MCDecayCut   = DecayInfo.getGeneralMCCuts();
  vector<TString> MCDecayLabel = DecayInfo.getGeneralMCLabels();
  TString MassDecayCut = CutInfo.getMass1Cuts()[0].second;
  double SigEff;    double SigEfferror;    
  double DataEff;    double DataEfferror;    
  double Error;
  double ErrorOnErrorPercent;
  cout << " " << endl;
  int j=0; // Secondary iterator for the vectors
  if(printChecks){
    SPACEin();
    cout << "Number of MCDecayCut Modes: " << MCDecayCut.size() << endl;
  }
  for(int i=0 ; i < MCDecayCut.size() ; i++ ){
    THINLINE();
    cout << " Printing Error for Cut " << endl;   
    cout << CutToCheck << endl; 
    THINLINE();
    if(MCDecayLabel[i].Contains("Signal")){
      if(printChecks){
        cout << "For Decay Mode "+MCDecayLabel[i]+" with additional mode cut(s) applied:" << endl;
        cout << MCDecayCut[i] << endl;
        cout << "-----------To select proper resonance -------------" << endl;
        cout << CutInfo.getMass1Cuts()[i].second << endl;
      }
      SigEff = ErrorNums[j].second/ErrorNums[j].first;
      SigEfferror = FSPhysics::quadraticSum((1.0/sqrt(ErrorNums[j].second)), (1.0/sqrt(ErrorNums[j].first)));
      DataEff= ErrorNums[j+2].second/ErrorNums[j+2].first;
      DataEfferror = FSPhysics::quadraticSum((1.0/sqrt(ErrorNums[j+2].second)), (1.0/sqrt(ErrorNums[j+2].first)));
      Error  = (DataEff/SigEff)-1;
      ErrorOnErrorPercent  = FSPhysics::quadraticSum(SigEfferror,DataEfferror)*100;
      if(!printChecks){cout << "For Decay Mode "+MCDecayLabel[i]+"  :  " << endl; }
      cout << "Events in left in INCMC via  (Loose cut, Tight Cut)  :  ("<<ErrorNums[j+1].first<<" , "<<ErrorNums[j+1].second<<")"<<endl;  
      cout << "-------------------------------------" << endl;
      cout << " Cut Eff for SIGMC : ("<< ErrorNums[j].second <<" +- " << (sqrt(ErrorNums[j].second)) << ")  /  ("<<
                                         ErrorNums[j].first  <<" +- " << (sqrt(ErrorNums[j].first )) << ")    =   "<<
                  std::setprecision(8)<< ErrorNums[j].second/ErrorNums[j].first<<" +- "<< SigEfferror << endl;
      cout << " Cut Eff for DATA  : ("<< ErrorNums[j+2].second <<" +- " << (sqrt(ErrorNums[j+2].second)) << ")  /  ("<<
                                         ErrorNums[j+2].first  <<" +- " << (sqrt(ErrorNums[j+2].first )) << ")    =   "<<
                  std::setprecision(8)<< ErrorNums[j+2].second/ErrorNums[j+2].first<<" +- "<< DataEfferror << endl;
      cout << "-------------------------------------" << endl;
      cout << "Error: |(eff_DATA/eff_MC)-1| = |("<< DataEff <<" +- "<< DataEfferror <<")/("
                                                 << SigEff<<" +- "<< SigEfferror <<")-1|*100% = ("
                       <<std::setprecision(5) << abs(Error)*100<<" +- "<< ErrorOnErrorPercent<<")%"<< endl;
      THINLINE(); 
      cout << " Total Cut Systematic Uncertainty : "<<std::setprecision(5)<<(abs(Error)*100+ErrorOnErrorPercent)<<" %"<< endl;
      THINLINE();  
    }
    else{ 
      cout << "Decay Mode " << MCDecayLabel[i] << endl << " is NOT signal, SKIPPING" << endl;
      THINLINE();  
    }                
    if( i < MCDecayCut.size() )cout << " " << endl;
    j=j+3;
  }
  return;
}
//========================================================================

#endif