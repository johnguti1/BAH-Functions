#if !defined(HISTOHELPER_H)
#define HISTOHELPER_H

 #include "DrawResources.h"
 #include "ScalingHelper.h"

//================================================================================================
//TString getLegendLabel(TString FileName, TString NTuple, TString ScaleSize){
//  TString 
//}
//================================================================================================
// For setting up additional (specific) Signal/Backgraound decay modes [Need at least 1 in original]
vector<TH1F*> ModeHistogramSetup(TString Set, vector<TString> ISCuts, vector<TString> ISLabels,vector<TString> FNNTvecINC, TString FNS, TString NTS, 
                                  TString category, TString var, TString bounds, TString cuts, TString INCMCtag, TString DATAtag, bool checkprint = true ){
  vector<TH1F*> histVec;  // Vector for setting max (kinda) and organizing/cleaning up with ryans function
  TH1F* hDummy;
  TString fn;
  bool moreINC = false;
  if(FNNTvecINC.size()>2){ moreINC = true; }
  TString nt;
  int colorIterator = 0;
  TString cuttag;
  double Scale = 1;
  if(checkprint)cout << "Starting 'Signal' loop of CutVecSize " << ISCuts.size() << endl;
  for( int i=0 ; i < ISCuts.size() ; i++ ){
    SPACEin();
    if(checkprint)cout << "Initiating 'Signal' Cut ["+FSString::int2TString(i)+"] :"<< endl;
    if(checkprint)cout << ISLabels[i] << endl;
    if(!ISLabels[i].Contains("INCMC")){
      // Setting and checking properties of SIGMC to correctly apply the checks and setup
      if(checkprint)cout << "Set , Datatag = "+Set+" , "+DATAtag << endl;
      // ONLY USES FN FROM SIGMC
      if(checkprint)cout << " Signal MC Cut " << endl;
      if(ISCuts[i].Contains("MCDecayParticle1==-15 && MCDecayParticle2==15")){
        //if(ISLabels[i].Contains(""))   If I want to switcch between KKMC and EVTGEN [Bad idea probably]
        fn=getFN("tt"+Set,"ntINC","SIGMC",0);
        nt=getNT("tt","ntINC");
        if(fn.Contains("SIGMC.3770.2021.ditau/SKIM.1")){Scale = 1.344086021;}
        if(fn.Contains("SIGMC.12.tauBACK/SKIM")){Scale = 0.25339285;}
        if(DATAtag.Contains("SEMI")){Scale = Scale*getINCScale(INCMCtag,DATAtag);}
      }
      else{
        Scale = getSIGScale(true,ISCuts[i],Set,DATAtag);
        cout << "Not tau+ tau- " << endl;
        fn=FNS; 
        nt=NTS;
      }
      if(checkprint) cout << "Scale used: " << Scale << endl;
    }
    else if(moreINC){
      if(checkprint)cout << " Inclusive MC Cut " << endl;
      // ONLY USES FN FROM INCMC1 or 2   
        // Note: captureParentheses("#splitline{ 'energy' INCMC}{stuf....}")[0] -->  'energy' INCMC
        //       parseTString(" 'energy' INCMC" )[0] --> "'energy'" 
        //   Full energy is written in filenames!  ( as well as last digits like 3686 -> 86 )
      cuttag = FSString::parseTString(  FSString::captureParentheses(ISLabels[i],0,"{","}") )[0];
      if(FNNTvecINC[0].Contains(cuttag)){
        fn=FNNTvecINC[0];
        nt=FNNTvecINC[1];
        Scale = getINCScaleMode(INCMCtag,DATAtag,ISCuts[i]);
        if(checkprint) cout << "Scale used: " << Scale << endl;
      }
      if(FNNTvecINC[2].Contains(cuttag)){
        fn=FNNTvecINC[2];
        nt=FNNTvecINC[3];
        Scale = getINCScaleMode("70",DATAtag,ISCuts[i])*getCONTScale("21",DATAtag);
        if(checkprint)cout << "Scale used: " << Scale << endl;
        if(checkprint)cout << "Cut INC mode ["<<i<< "] scaled with =  "<<getINCScaleMode("70",DATAtag,ISCuts[i])<<" * "<<getCONTScale("21",DATAtag)<<endl;
      }
    }
    else{
      if(checkprint)cout << " Other MC Cut " << endl;
      // ONLY USES FN FROM INCMC or INCMC1 & INCMC2
      fn=FNNTvecINC[0];
      nt=FNNTvecINC[1];
      if(moreINC){
      fn=fn+","+FNNTvecINC[2];
      nt=nt+","+FNNTvecINC[3];
      }
      Scale = getINCScaleMode(INCMCtag,DATAtag,ISCuts[i]);
    } // Assign correct NF,NT based on Signal/Events
    if(checkprint){
      cout << "FN:   " << fn << endl;
      cout << "SCALE FROM OUT: "<< Scale << endl;
      cout << "Scale of Mode["<<i<<"] "+ISLabels[i]+" : " << Scale << endl;
      THINLINE();
      cout << "'Signal' "<< i+1 <<"     : ISLabel and MCModeCut  ["<< i <<"]" << endl;
      cout << ISLabels[i] << endl;
      cout <<  ISCuts[i] << endl;
      THINLINE();
    }
    // To Skip/skip or Remove/remove a histogram   [when is someone gonna have emove or kip in their Label name!?!?! should be okay]
    if(!(ISLabels[i].Contains("emove")||ISLabels[i].Contains("kip"))){
      if(checkprint)cout << " Applying Cuts and Scaling to Histogram and setting Color/Width" << endl;
      if(checkprint)cout << " Total Cuts Applied: " << endl;
      if(checkprint)cout << ISCuts[i]+FSAND+cuts << endl;

      hDummy = FSModeHistogram::getTH1F(fn,nt,category,var,bounds,ISCuts[i]+FSAND+cuts,Scale); 
      if(Scale>0.0000001){
        // Outlining 
        if(!(ISLabels[i].Contains("Signal"))){
          // Signal MC should have prescribed color. If not Signal MC, iterates to new color
          colorIterator= colorIterator +1;
          hDummy->SetLineColor(kBlack);
          hDummy->SetLineWidth(1);
        }
        else{hDummy->SetLineColor(getColorIS(ISCuts[i]+ISLabels[i],colorIterator,1,checkprint));} // SIGMC just gets same color for Line
        hDummy->SetFillColor(getColorIS(ISCuts[i]+ISLabels[i],colorIterator,1,checkprint));
        //cout << "colorIterator used: " <<colorIterator<< "  :  " getColorIS(ISCuts[i]+ISLabels[i],colorIterator,1,checkprint)<<  endl;
      }
      if(checkprint)cout << " Passing Histogram to the Histgram-Vector " << endl;
      histVec.push_back(hDummy);
    }
    else{
      if(checkprint)cout << " Skipping using the current Histgram because emove or kip was in label " << endl;
    }
    // Not Passing The remove
  }
  THINLINE();
  return histVec;
}
//================================================================================================
// Just to orgaize the cuts to be appled to the INCMC sample(s) [only set up for two]
vector<pair<TString, vector<int>>> INCMCCutInfo(vector<TString> ISCuts, vector<TString> ISLabels, TString FNI, TString FNI2="", bool checkprint = false){
  vector<pair<TString, vector<int>>> OutputInfo;
  TString MCSigCuts1 = "";
  TString MCSigCuts2 = "";
  vector<int> INC1cutList; // Just a dummy. Mayyybe eventually useful.
  vector<int> INC2cutList;
  TString cuttag;
  // When using Multiple inclusive MC samples, need to carve out parts of interest from specific MC and check energy to apply carve out correctly. 
  if(checkprint) SPACEin();
  if(checkprint) cout << "Looping over cuts to carve out from INCMC 1 (and 2):" << endl;
  for(int i = 0; i < ISCuts.size(); i++ ){
    // Signal/Background should probably be from SIGMC    :   FSString::parseTString("Signal")[0]     -> "Signal"
    // Can differentiate INCMC by Energy                  :   FSString::parseTString("3770 INCMC")[0] -> "3770"
    // Can Just apply generally to both INC w/o concern...:   FSString::parseTString("Endcap Gap")[0] -> "Endcap"
    cuttag = FSString::parseTString(  FSString::captureParentheses(ISLabels[i],0,"{","}") )[0];
    if(FNI2==""){
      if(i==0){ MCSigCuts1 = ISCuts[i]; }
      else{ MCSigCuts1=MCSigCuts1+FSOR+ISCuts[i];} 
    }    // Only 1 MC? Just carve your Signal out in case
    if(FNI2!=""){                                                // Theres 2 MC? Can Carve Case-by-Case if energy in cut name
      if(FNI.Contains(cuttag)){ 
        if(i==0){ MCSigCuts1 = ISCuts[i]; }     
        else{ MCSigCuts1=MCSigCuts1+FSOR+ISCuts[i];}// Cuttin Inclusive set 1
        if(checkprint)cout << "Adding cut to INC1 :" << ISCuts[i] << endl;
      }
      else if(FNI2.Contains(cuttag)){
        if(i==0){MCSigCuts2=ISCuts[i];}
        else{ MCSigCuts2=MCSigCuts2+FSOR+ISCuts[i];}
        INC2cutList.push_back(i);
        if(checkprint)cout << "Adding cut to INC2 :" << ISCuts[i] << endl;
      }
      else{ // Mainly for SIGMC Cuts that are non-standard... // Might need to rethink eventually...
        if(i==0){ // Cuttin without regard
          MCSigCuts1=ISCuts[i];
          MCSigCuts2=ISCuts[i];
        }
        else{  // Cuttin without regard but with an or to group together.
          MCSigCuts1=MCSigCuts1+FSOR+ISCuts[i];
          MCSigCuts2=MCSigCuts2+FSOR+ISCuts[i];
        }
        if(checkprint)cout << "Adding cut to INC1 and INC2 :" << ISCuts[i] << endl;
      }
    }
  }
  if(checkprint){
    cout << "Cut Signal(s) above out of INCMC(s) to avoid double ploting" << endl;
    THINLINE();
    cout << "INCMC 1 cuts:" <<MCSigCuts1 << endl;
    THINLINE();
    cout << "INCMC 2 cuts:" <<MCSigCuts2 << endl;
    SPACEin();
  }
  OutputInfo.push_back(make_pair(MCSigCuts1,INC1cutList));
  OutputInfo.push_back(make_pair(MCSigCuts2,INC2cutList));
  return OutputInfo;
}
//================================================================================================
// To apply the scaling and cuts to get a vector of the INCMC histograms [only set up for two]
vector<TH1F*> INCMCHistogramSetup(TString Set, vector<TString> DataSetTag, vector<TString> FNNTvecINC, TString category, TString var, TString bounds, TString MCSigCuts1, TString MCSigCuts2, TString cuts, bool checkprint = false){
  vector<TH1F*> outputHists;
  TString INCcuts;   TString INCcuts2;
  TH1F* hbE;         TH1F* hbE2;
  double INC2scale = 1;
  if(FNNTvecINC[0]!=""){
    cout << "INCMC 1" << endl;
    if(MCSigCuts1==noCut){ INCcuts = cuts;}
    if(MCSigCuts1!=noCut){ INCcuts = cuts+FSAND+"!("+MCSigCuts1+")";}
    hbE= FSModeHistogram::getTH1F(FNNTvecINC[0],FNNTvecINC[1],category,var,bounds,INCcuts,getINCScale(DataSetTag[0],DataSetTag[2]));
    if(checkprint)cout << "Scale  INCMC1 : " << getINCScale(DataSetTag[0],DataSetTag[2]) << endl;
    THINLINE();
    hbE->SetFillColor( getColorIS("INC" ,0));  
    hbE->SetLineColor(kBlack);     
    hbE->SetLineWidth(1);
    outputHists.push_back(hbE);
  }
  // THIS SHIT NEEDS WORK...
  if(FNNTvecINC[2]!=""){
    cout << "INCMC 2" << endl;
    if(MCSigCuts2==noCut){ INCcuts2 = cuts;}
    if(MCSigCuts2!=noCut){ INCcuts2 = cuts+FSAND+"!("+MCSigCuts2+")";} 
    // Different Energies might need to be scaled properly to their energies data first,
    //                getINCScale(70)*getCONTScale("70") : (3770INC->70Data)*(2021:3770Data->full:3686data/inc) : (1/40)*(lum3686xCS70/2021lum70xCS86)
    // Very JANKY method at the moment...
    if(Set=="gtm"||Set=="get"||Set=="gep"||Set=="gepp"){
      INC2scale = getINCScale("70")*getCONTScale("21",DataSetTag[2]);
      //INCMC2tag = "2021 3770 INCMC";
      if(checkprint) cout << "Scale of INCMC2 [3770 MC]  (40x of 3770 dat) : " << getINCScale("70")<<" * "<<getCONTScale("21")<<" = "<< getINCScale("70")*getCONTScale("21") << endl;
    }
    if(Set=="gpp"||Set=="gkk"||Set=="gPP"){
      INC2scale = getCONTScale("3650.2022");
      //INCMC2tag = "2022 3650 INCMC";
      if(checkprint) cout << "Scale  INCMC2 [3650.2022]  (1:1 of 3650 dat) : " << INC2scale << endl;
    }
    hbE2= FSModeHistogram::getTH1F(FNNTvecINC[2],FNNTvecINC[3],category,var,bounds,INCcuts2,INC2scale);
    THINLINE();
    hbE2->SetFillColor(getColorIS("INC2",0));  
    hbE2->SetLineColor(kBlack);    
    hbE2->SetLineWidth(1);
    outputHists.push_back(hbE2);
  }
  return outputHists;
}
//================================================================================================
//================================================================================================
//  Typically only need THStack but in the case of only one Data, using the TH1F* Histogram version
void Setup1DAxis(THStack* HistogramStack, TString Bounds, TString xtitle, TString UnitsX){
  //TString = getUnitsY( Bounds, UnitsX );
  HistogramStack->GetXaxis()->SetTitle(xtitle+getUnitsX(UnitsX));
  HistogramStack->GetYaxis()->SetTitle("Events"+getUnitsY( Bounds, UnitsX ));
  HistogramStack->GetYaxis()->SetTitleOffset(1.5);
  HistogramStack->GetXaxis()->SetTitleOffset(1.3);
  if((xtitle.Contains("Events Total"))){HistogramStack->GetXaxis()->SetLabelSize(0);}        
}
void Setup1DAxis(TH1F* Histogram, TString Bounds, TString xtitle, TString UnitsX){
  //TString = getUnitsY( Bounds, UnitsX );
  Histogram->GetXaxis()->SetTitle(xtitle+getUnitsX(UnitsX));
  Histogram->GetYaxis()->SetTitle("Events"+getUnitsY( Bounds, UnitsX ));
  Histogram->GetYaxis()->SetTitleOffset(1.5);
  Histogram->GetXaxis()->SetTitleOffset(1.3);
  if((xtitle.Contains("Events Total"))){Histogram->GetXaxis()->SetLabelSize(0);}        
}
//================================================================================================
//////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////      PLOT FUNCTIONS FOR MC/DATA COMPARISONS       ////////////////////////
  // PLOT DATA, MC MODES AND BACKGROUND in MC
void DATAplotVEC(TString Set, TString filetag, vector<TString> DataSetTag, vector<TString> FNNTvec, TString LegendDirection, 
      TString var, TString bounds,TString cuts,TString TITLE, TString xtitle,
      vector<pair<TString,TString>> cutvals ,bool logy, TString UnitsX,
      vector<TString> ISCuts, vector<TString> ISLabels, TString category){
  //------------------------------------------
  // Setting up histograms, filenames and the histogram-stack and random stuff for use
  bool checkprint=true,       INC1cut = false,      INC2cut = false;
  int LegendEntries = 0,      NSpecificModes=0;
  double HistSupress=0.005,   INCsize=0,        INCsize2=0;
  double Ymaxp, Ymax, Xmin, Xmax, Xscale, lxmin, lxmax, lymin;
  TString INCMCyr, CONTyr, DATAyr;
  TString FNS, FNI, FND, FNDc, FNI2;
  TString NTS, NTI, NTD, NTDc, NTI2;
  SPACEin();
  TString INCMC2tag = "ooopp";  // Just a place holder incase INCMC2 is used.
  TString MCSigCuts1="",  MCSigCuts2="",  INCcuts="",  INCcuts2="",  cuttag;
  //------------------------------------------
  TH1F* hbE;   TH1F* hDc;   TH1F* hD;     // INCMC, Continuum data and data of interest histograms
  THStack* hs = new THStack("hs",TITLE);
  vector<TH1F*> histVec;      // Vector for setting max (kinda) and organizing/cleaning up with ryans function
  vector<TH1F*> INCMCHists;   // Hist Vector Containing all the INCMC Histograms to add to the stack
  //------------------------------------------
  cout << "Beginning "+xtitle+" Histograms" << endl;
  //------------------------------------------
  INCMCyr = DataSetTag[0];
  CONTyr  = DataSetTag[1];
  DATAyr  = DataSetTag[2];
  FNS =FNNTvec[0];    NTS =FNNTvec[1]; 
  FNI =FNNTvec[2];    NTI =FNNTvec[3]; 
  FND =FNNTvec[4];    NTD =FNNTvec[5];
  FNDc=FNNTvec[6];    NTDc=FNNTvec[7];
  //------------------------------------------
  // For additional INCMC, SIGMC and anything other data types...
  vector<TString> FNNTvecINC = {FNI,NTI};
  vector<pair<TString, vector<int>>> INCMCinfo;
  vector<int> INC2cutList;
  //------------------------------------------
  // Getting the MC data set into a vector to 
  THINLINE();
  cout << "Making specific SIGMC [ and maybe INCMC ] Histograms" << endl;
  THINLINE();
  //===================================================
  //            SIGMC histograms 
  //===================================================
  // Initializing Signal cuts [Exclude from INCMC incase use INCMC info (or replacing it)]
  //------------------------------------------
  // If the FileTag Has noMC, skip filling the SIGMC histograms
  if(filetag.Contains("noMC")){ NSpecificModes=0;}
  else{
    //FSHistogram::enableRDataFrame(false,4);
    if(ISCuts.size()==0){     NSpecificModes=0;     MCSigCuts1=noCut;     }
    if(ISCuts.size()>0){
      histVec = ModeHistogramSetup(Set,ISCuts,ISLabels,FNNTvecINC,FNS,NTS,category,var,bounds,cuts,INCMCyr,DATAyr,checkprint);
      NSpecificModes = histVec.size();  // This is based on number of MC cuts to selection any number of MC decays / types
      INCMCinfo = INCMCCutInfo(ISCuts,ISLabels,FNI,FNI2,checkprint);
      MCSigCuts1 = INCMCinfo[0].first;
      MCSigCuts2 = INCMCinfo[1].first;
      INC2cutList = INCMCinfo[1].second;
      if(MCSigCuts1!=""){ INC1cut = true; }
      if(MCSigCuts2!=""){ INC2cut = true; }
    }
    LegendEntries = LegendEntries + NSpecificModes;
  }
  //------------------------------------------
  //===================================================
  //            INCMC histograms 
  //===================================================
  if(!filetag.Contains("noMC")){ 
    INCMCHists = INCMCHistogramSetup(Set,DataSetTag,FNNTvecINC,category,var,bounds,MCSigCuts1,MCSigCuts2,cuts,checkprint);
    // NOTE: Honestly CAN DEFINITELY COUNT the events in INCMCHistogramSetup and pass out a pair with  vector<pair<TH1F* Hist, TString LegendLabel>>
    if(FNI!=""){
      INCsize = countHIST(INCMCHists[0]);
      LegendEntries = LegendEntries + 1 ;
    }
    if(FNI2!=""){
      INCsize2 = countHIST(INCMCHists[2]);
      if(INCsize2>HistSupress){LegendEntries = LegendEntries + 1 ;}
      if(Set=="gtm"||Set=="get"||Set=="gep"||Set=="gepp"){ INCMC2tag = "2021 3770 INCMC";  }
      if(Set=="gpp"||Set=="gkk"||Set=="gPP"){ INCMC2tag = "2022 3650 INCMC";  }
    }
  }
  //------------------------------------------
  // Typcally only 1*2 SIGMC and 1*2 INCMC root files are used many times. Maximally 2*2 SIGMC and 2*2 INCMC are used.   [assuming charged conjuagate mode]
  //    So probably 4 to 8 Files 
  // while maybe (1-3)*2 SIGMC hists are made, (1-4)*2 INCMC modes hists and then (1-2)*2 INCMC total hists    [assuming charged conjuagate mode]
  //    So probably 6 to 18 histograms
  //===================================================
  //            DATA histograms 
  //===================================================
  if(FNDc!=""){
    cout << "CONTINUUM" << endl; //cout << FNDc << endl << NTDc << endl;
    hDc = FSModeHistogram::getTH1F(FNDc,NTDc,category,var,bounds,cuts,getCONTScale(CONTyr,DATAyr));
    if(checkprint)cout << "Scale  CONT : " << getCONTScale(CONTyr,DATAyr) << endl;
    LegendEntries = LegendEntries + 1 ;
    THINLINE();
  }
  //------------------------------------------
  double DataScaling = 1;
  if(FND!=""){
    cout << "DATA :" << endl;//cout << FND << endl << NTD << endl;
    if(Set=="gtm"||Set=="get"||Set=="gep"||Set=="gepp"){
      if(FNNTvec.size()>8&&(FNNTvec[8]!="")){ DataScaling =  getCONTScale("21",DATAyr);  }
      if(DATAyr.Contains("SEMI")){  DataScaling = 1; }
    }
    hD = FSModeHistogram::getTH1F(FND,NTD,category,var,bounds,cuts,DataScaling);
    //if(checkprint)cout << " CONTyr VS Conyr(12) =( "<< CONTyr<< " , "<<DATAyr<< " ) : ("<<getCONTScale(CONTyr,DATAyr) << " , "<<getCONTScale("21",DATAyr) << ")" << endl;
    if(checkprint)cout << "DATA Scale Used: " << DataScaling << endl;
    LegendEntries = LegendEntries + 1 ;
    THINLINE();
  }
  //------------------------------------------
  //FSHistogram::executeRDataFrame();
  //FSHistogram::disableRDataFrame();
  cout << "Done getting Histograms. Now other shit... [organizing and plotting]" << endl;
  //===================================================
  //       Stacking histograms in Order
  //===================================================
  // Setting up histograms in stack hs (INCNC -> Continuum -> SpecificModeN -> ... -> SpecificMode1)
  if(checkprint)cout << "Adding Histograms to TStack" << endl;
  if(FNDc!=""){ hs->Add(hDc);}
  if(FNI2!=""&&INCsize2>HistSupress){ hs->Add(INCMCHists[1]);}
  if(checkprint)cout << "Adding Histograms from INCMC to Vector and TStack for organizing" << endl;
  vector<TH1F*> histVecDummy = histVec;  // Dummy Just made for plotting to canvas in order
  if(INC2cut){
    for(int i=0 ; i < INC2cutList.size() ;  i++){      
      hs->Add(histVecDummy[INC2cutList[i]]);
      histVecDummy.erase(histVecDummy.begin()+INC2cutList[i]);
    }
  }
  //------------------------------------------
  if(checkprint)cout << "Adding Histograms from SIGMC to Vector and TStack for organizing" << endl;
  if(FNI!=""){  hs->Add(INCMCHists[0]);}
  if(ISCuts.size()>0){
    for( int i=histVecDummy.size()-1 ; i>-1 ; i-- ){
      hs->Add(histVecDummy[i]);
    }
  }
  //------------------------------------------
  if(checkprint)cout << "Done Adding Histograms to Vector and TStack" << endl;
  //===================================================
  // Setting up MinMax Consistancy in Signal, INCMMC and Data [histVec no longer only SIGMC]
  //===================================================
  if(checkprint)cout << "Setting Qualitites for INCMC and DATA histograms" << endl;
  if(FNDc!=""){ histVec.push_back(hDc );  hDc->SetFillColor( getColorIS("CONT",0));  hDc->SetLineColor(getColorIS("CONT",0)); }
  if(FND!=""){  histVec.push_back(hD);}
  FSHistogram::setHistogramMaxMin(histVec,false,"MAX");
  if(checkprint)cout << "Done setting qualitites" << endl;
  if(checkprint)SPACEin();
  //===================================================
  // Setting logY if applicable. If histVec filled totally, could just loop over it.
  //===================================================
  if(checkprint)cout << "Checking/Setting Log qualitites" << endl;
    // logy setup
  if(logy){ 
    double logMIN = 0.01;
    for( int i ; i < histVec.size() ; i++){
      histVec[i]->SetMinimum(logMIN);
    }
    if(FND!=""){hD->SetMinimum(logMIN);}  
    if(FNDc!=""){hDc->SetMinimum(logMIN);}
    if(!filetag.Contains("noMC")){ 
      if(FNI!=""){INCMCHists[0]->SetMinimum(logMIN);}
      if(FNI2!=""){INCMCHists[1]->SetMinimum(logMIN);}
      hs->SetMinimum(logMIN); // Just in case
      if(FND!=""){Ymaxp = max(hs->GetMaximum(),hD->GetMaximum())*(1.1); }
      else{Ymaxp = hs->GetMaximum()*(1.1);}
      Ymax = Ymaxp*3.00417; // e^{1.1} 
      hs->SetMaximum(Ymax); 
    }
    else{
      Ymax = hD->GetMaximum()*(1.1)*3.00417;
      hD->SetMaximum(Ymax); 
    }
  }
  else{
    if(!filetag.Contains("noMC")){ 
      if(FND!=""){Ymax = max(hs->GetMaximum(),histVec[0]->GetMaximum())*(1.1);}
      else{Ymax = hs->GetMaximum()*(1.1);}
      hs->SetMaximum(Ymax);
    }
    else{
      Ymax = hD->GetMaximum()*(2.5);
      hD->SetMaximum(Ymax); 
    }
  }
  //------------------------------------------
  if(checkprint)cout << "Finally Drawing Histogram TStack" << endl;
  // Finally drawing 
  if(!filetag.Contains("noMC")){  
    hs->Draw("hist");  
    if(FND!=""){  hD->Draw("same"); }
  }
  else{ hD->Draw(); }
  //------------------------------------------
  if(checkprint)cout << "Done Drawing Histgrams" << endl;
  if(checkprint)SPACEin();
  ////////////////////////////////////////////////////////////////////
  if(checkprint)cout << "Beginning to Draw Lines" << endl;
  // Can just pass xmin/xmax and use those to check if cut is outside the bounds and get scaling in the lines function...
  Xmin  = FSString::parseBoundsLowerX(bounds);
  Xmax  = FSString::parseBoundsUpperX(bounds);
  Xscale= getDiff(Xmax,Xmin)/100;
  drawCutLines(kBlack,cutvals,Ymax,Xscale); // written above (limited to 3 pairs)
  //------------------------------------------
  // Drawing lines for control Samples  [Need to Hardcode them in DrawResources.h ]
  if(!FNI.Contains("3770"))drawControlLines(TITLE,Set,var,cuts,xtitle,Ymax,Xscale); 
  if(checkprint)cout << "Done Drawing Lines" << endl;
  if(checkprint)SPACEin();
  ////////////////////////////////////////////////////////////////////
  if(checkprint)cout << "Setting up Histogram Legends" << endl;
  TLegend *leg;
  //////////////////////////////////  
  //  Set  LegendDirection  LegendEntries  ISCuts histVecDummy,INCMCHists,hDc,hD, INCMCyr,DATAyr  FNI,FND  INC2cutList [For properly ording the stack on legend], double HistSupress=0.001, bool checkprint=false)
  TString BaseIncLabel;
  TString BaseIncLabel2;
  // Important: NEED TO SET UP A Legend maker that gets proper labels based on FN passed to it...
  if(INCMCyr.Contains("FULL")&&INCMCyr!="FULL"){ BaseIncLabel = "2021 3770 INCMC"; }
  if(!(INCMCyr.Contains("FULL"))){ BaseIncLabel = "20"+INCMCyr+" INCMC"; }
  if(INCMCyr=="FULL"){ BaseIncLabel = "Full #psi(2S) INCMC";}
  if(INCMC2tag.Contains("INCMC")) BaseIncLabel2 = INCMC2tag;
  if(ISCuts.size()>0){
    if(ISLabels[ISLabels.size()-1].Contains("INCMC")){
      if(INC1cut) BaseIncLabel="#splitline{Remaining of}{"+BaseIncLabel+"}";
      if(INC2cut)BaseIncLabel2="#splitline{Remaining of}{"+INCMC2tag+"}";
    }
  }
  //////////////////////////////////
  // Removing MAY NOT WORK ALL THE TIME so should porbably output pair his with label and loop over those...
  lymin = 0.9-0.067*LegendEntries;
  if(LegendDirection=="L"){  lxmin= 0.15; lxmax= 0.42; }
  if(LegendDirection=="M"){  lxmin= 0.36; lxmax= 0.64; }
  if(LegendDirection=="R"){  lxmin= 0.62; lxmax= 0.885;}
  if(LegendDirection!="NO"&&LegendEntries!=0){
    leg = new TLegend(lxmin,lymin,lxmax,0.9);
    if(xtitle.Contains("Events Total")){leg->SetHeader(category,"C");}  // CAN MAKE A LOOP BELOW HERE...
    for( int i = 0 ; i < histVecDummy.size() ; i++){
      //if((getSIGScale(1,ISCuts[i],Set,DATAyr)>0.000000001||getINCScaleMode(INCMCyr,DATAyr,ISCuts[i])>0.000000001)
      //&&(ISLabels.size()>0)){
        if(!(ISLabels[i].Contains("emove")||ISLabels[i].Contains("kip"))){leg->AddEntry(histVec[i],ISLabels[i],"f");}
        if(checkprint)cout << ISLabels[i] << endl;
      //}
    }
    if(FNI!=""){  leg->AddEntry(INCMCHists[0],BaseIncLabel,"f");  }    
    if(INC2cutList.size()>0){
      for( int i = 0 ; i < INC2cutList.size() ; i++){
        leg->AddEntry(histVec[INC2cutList[i]],ISLabels[INC2cutList[i]],"f");
      }
    }
    if(FNI2!=""&&INCsize2>HistSupress){ leg->AddEntry(INCMCHists[1],BaseIncLabel2,"f"); }
    // Probably Useful to make a legend title function or add more options... idk.  Eventually...
    if(FNDc!=""){leg->AddEntry(hDc,"Full 3770 DATA","f");}
    else if(FND!=""&&FND.Contains("CONT.3770")){ leg->AddEntry(hD,"2021 3770 DATA","lep");}
    else if(FND!=""&&FND.Contains("CONT.3650")){ leg->AddEntry(hD,"2022 3650 DATA","lep");}
    else if(FND!=""&&(FND.Contains("Semi"))){ leg->AddEntry(hD,"#psi(2S) Semi-Data","lep");}
    else if(FND!=""&&(FND.Contains("3686")||FND.Contains("control"))){ leg->AddEntry(hD,"2012 #psi(2S) DATA","lep");}
    //----------------------------------
    leg->SetMargin(0.2);  // To save some space
    leg->SetTextSize(0.025); // works fine
    //leg->SetFillStyle(0);
    //leg->SetBorderSize(0);  //no border for legend [Looks ugly in my case]
    leg->Draw("same");
  }
  if(checkprint)cout << "Done with Histogram Legends" << endl;
  if(!filetag.Contains("noMC")){ Setup1DAxis(hs,bounds,xtitle,UnitsX);  }
  else{ 
    hD->SetTitle(TITLE);
    Setup1DAxis(hD,bounds,xtitle,UnitsX);  
  }
  THINLINE();
  cout << "Done with "+xtitle+" Histogram" << endl;
  SPACEin();
}
//====================================================================================
//=========================== 2D HISTOGRAM MAKER =====================================
//====================================================================================
// Can use more polish eventually.
void plot2d(TString LegendDirection, TString LegendLabel, TString FN, TString NT, TString category, TString TITLE,
            TString varX, TString varY, TString boundsXY, TString cuts, TString xtitle, TString ytitle,
            vector<pair<TString,TString>> cutpairsX, vector<pair<TString,TString>> cutpairsY){
  TH2F* h2 = FSModeHistogram::getTH2F(FN,NT,category,varY+":"+varX,boundsXY,cuts,1);
  h2->SetTitle(TITLE);
  h2->SetXTitle(xtitle);    h2->SetYTitle(ytitle);
  gStyle->SetPalette(kCool);
  h2->Draw("COLZ");
  ////////////////////////////////////////////////////////////////////
  double Xmin= h2->GetXaxis()->GetXmin();
  double Ymin= h2->GetYaxis()->GetXmin();
  double Xmax= h2->GetXaxis()->GetXmax();
  double Ymax= h2->GetYaxis()->GetXmax();
  double Xscale= (Xmax-Xmin)/100;
  double Yscale= (Ymax-Ymin)/100;
  // Draw X-axis Cut-value lines
  drawXLines(cutpairsX,Ymin,Ymax,Xscale);
  // Draw Y-axis Cut-value lines
  drawYLines(cutpairsY,Xmin,Xmax,Yscale);
  ////////////////////////////////////////////////////////////////////
  // Setting up Legend Values for 2d-Histogram
  double lxmin;     double lxmax;
  double lymin;     double lymax;
  TLegend *legend;
  // Legend in Top-Left
  if(LegendDirection=="TL"){  
    lxmin= 0.15;  lxmax= 0.45; 
    lymin= 0.80;  lymax= 0.90; 
  }
  // Legend in Bottom-Middle
  if(LegendDirection=="TM"){  
    lxmin= 0.35;  lxmax= 0.65; 
    lymin= 0.80;  lymax= 0.90; 
  }
  // Legend in Top-Right
  if(LegendDirection=="TR"){  
    lxmin= 0.58;  lxmax= 0.88; 
    lymin= 0.80;  lymax= 0.90; 
  }
  // Legend in Bottom-Left  
  if(LegendDirection=="BL"){  
    lxmin= 0.15;  lxmax= 0.45; 
    lymin= 0.16;  lymax= 0.26; 
  }
  // Legend in Bottom-Middle
  if(LegendDirection=="BM"){  
    lxmin= 0.35;  lxmax= 0.65; 
    lymin= 0.16;  lymax= 0.26;  
  }
  // Legend in Bottom-Right
  if(LegendDirection=="BR"){  
    lxmin= 0.58;  lxmax= 0.88; 
    lymin= 0.16;  lymax= 0.26;  
  }
  // if Direction is NO, will not draw a legend
  if(LegendDirection!="NO"){
    legend = new TLegend(lxmin,lymin,lxmax,lymax);
    legend->SetHeader(LegendLabel,"C"); // option "C" allows to center the header
    //legend->AddEntry(h2,LegendLabel,""); // Can use but uneccesary since only ploting one histogram
    legend->SetTextSize(0.031); // works fine
    legend->Draw("same");
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////





//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
  // For Counting Number of chi_cJ from data and comparing to scaled continuum and INCMC
  // If this is messing up, the cuts in the previous section should be the cause
  /*
pair<TH1F,TString> HistModeCounter(TString FN, TString NT, TString category, TString var, TString bounds, TString Cuts, double Scale = 1, TString ModeNames = ""){
  TString ActualBounds;  // Just in case the input is bad
  vector<TString> MCcuts;
  int max;
  if(var.Contains("ChicJ")||var.Contains("chicJ")||var.Contains("XcJ")){
    MCCuts.push_back(BAHDecays::getMCDecayParts({FSPhysics::kpdgGamma,FSPhysics::kpdgChic0}));
    if(Set!="gpp"||Set!="gkk")MCCuts.push_back(BAHDecays::getMCDecayParts({FSPhysics::kpdgGamma,FSPhysics::kpdgChic1}));
    MCCuts.push_back(BAHDecays::getMCDecayParts({FSPhysics::kpdgGamma,FSPhysics::kpdgChic2}));
    ModeNames = "#gamma#chi_{c0};#gamma#chi_{c1};#gamma#chi_{c2}";  // Output names for the bins
  }
  else{
    MCcuts = {noCut};
    ModeNames = "Remaining Events";
  }
  max = FSString::int2TString(MCCuts.size()*2+1); // so 1 gives ( 0  , 1  , 2 )
  ActualBounds = "("+FSString::double2TString(max*2)+",0,"+FSString::double2TString(max)+")";
  //Setting up histograms //////////////////////////////////////////////////
  SPACEin();
    cout << "Setting up and Adding Bin Historgams " << endl << FND << endl << NTD << endl;
  SPACEin();
  TH1F* hnp = new TH1F(var+ModeNames,var+ModeNames, BinNum , max*2 , max );
  TH1F* hOutput = FSHistogram::getTH1F(hnp);
  TH1F* h0= FSModeHistogram::getTH1F(FN,NT,category,"1",ActualBounds,Cuts+FSAND+Cut0);
  TH1F* h1= FSModeHistogram::getTH1F(FN,NT,category,"3",ActualBounds,Cuts+FSAND+Cut1);
  TH1F* h2= FSModeHistogram::getTH1F(FN,NT,category,"5",ActualBounds,Cuts+FSAND+Cut2);
  if( !(FN.Contains()) )
  if(countHIST(hD0)<0.01){
    hD0->SetBinContent(3,0);
    hD0->SetBinError(3,1);
  }
  if(countHIST(hD1)<0.01){
    hD0->SetBinContent(7,0);
    hD0->SetBinError(7,1);
  }
  if(countHIST(hD2)<0.01){
    hD0->SetBinContent(11,0);
    hD0->SetBinError(11,1);
  }
    cout << "Done getting Histograms. Now other shit..." << endl;
  ////////////////////////////////////////////////////////////////////
  /////////////////// FOR COUNTING HISTOGRAMS [Uncomment if concerned]
  vector<TH1F*> histVec;
  histVec.push_back(hbE0);    hbE0->SetLineColor(getColorIS("!"));       hbE0->SetFillColor(getColorIS("!"));
  histVec.push_back(hbE1);    hbE1->SetLineColor(getColorIS("!"));       hbE1->SetFillColor(getColorIS("!"));
  histVec.push_back(hbE2);    hbE2->SetLineColor(getColorIS("!"));       hbE2->SetFillColor(getColorIS("!"));
  //////////////////////////////////
  histVec.push_back(hDc0);    hDc0->SetLineColor(getColorIS(""));        hDc0->SetFillColor(getColorIS("")); 
  histVec.push_back(hDc1);    hDc1->SetLineColor(getColorIS(""));        hDc1->SetFillColor(getColorIS("")); 
  histVec.push_back(hDc2);    hDc2->SetLineColor(getColorIS(""));        hDc2->SetFillColor(getColorIS("")); 
  //////////////////////////////////
  histVec.push_back(hD0);
  histVec.push_back(hD1);
  histVec.push_back(hD2);
  //////////////////////////////////
  FSHistogram::setHistogramMaxMin(histVec,false,"MAX");
  double Ymaxp;
  double Ymax;
  hs0->Add(hDc0); 
  hs0->Add(hbE0); 
  hs1->Add(hDc1); 
  hs1->Add(hbE1); 
  hs2->Add(hDc2);
  hs2->Add(hbE2); 
  //////////////////////////////////
  double YmaxS = max(hs2->GetMaximum(),max(hs0->GetMaximum(),hs1->GetMaximum()));
  double YmaxD =max(hDc2->GetMaximum(),max(hDc0->GetMaximum(),hDc1->GetMaximum()));
  Ymax = max(YmaxS,YmaxD)*1.2;
  hs0->SetMaximum(Ymax);
  hs1->SetMaximum(Ymax);
  hs2->SetMaximum(Ymax);
  //////////////////////////////////
  hs0->Draw("hist");
  hs1->Draw("hist,same");
  hs2->Draw("hist,same");
  hD0->Draw("same");
  hD1->Draw("same");
  hD2->Draw("same");
  //////////////////////////////////
  double lxmin; 
  double lxmax;
  TLegend *leg;
  if(LegendDirection=="L"){  lxmin= 0.15; lxmax= 0.42; }
  if(LegendDirection=="M"){  lxmin= 0.36; lxmax= 0.64; }
  if(LegendDirection=="R"){  lxmin= 0.62; lxmax= 0.885;}
  if(LegendDirection!="NO"){
    leg = new TLegend(lxmin,0.7,lxmax,0.9);
    if(FNI!=""){
      if(year!="INC"){ leg->AddEntry(hbE0,"20"+year+" INCMC");  }
      if(year=="INC"){ leg->AddEntry(hbE0,"Total #psi(2S) INCMC");}
    }
    if(FNDc!=""){leg->AddEntry(hDc0,"3770 CONT DATA");}
    if(FND!=""){ leg->AddEntry(hD0,"2012 #psi(2S) DATA");}
    leg->SetTextSize(0.025); // works fine
    leg->Draw("same");
  }
  TString UNI = getUnitsY( hbE0, UnitsX );
  hs0->GetXaxis()->SetBinLabel(3,"#chi_{c0}");
  hs0->GetXaxis()->SetBinLabel(7,"#chi_{c1}");
  hs0->GetXaxis()->SetBinLabel(11,"#chi_{c2}");
  hs0->GetXaxis()->SetLabelOffset(0.005);
  hs0->GetXaxis()->LabelsOption("h");
  hs0->GetXaxis()->SetTitle(xtitle+getUnitsX(UnitsX));
  hs0->GetYaxis()->SetTitle("Events"+UNI);
  hs0->GetYaxis()->SetTitleOffset(1.25);
  hs0->GetXaxis()->SetTitleOffset(1.5);
  //hs0->GetXaxis()->CenterTitle(true);
  //hs0->GetYaxis()->CenterTitle(true);
  hs0->GetXaxis()->SetLabelSize(0.07);
}
*/
//////////////////////////////////////////////////////////////////////////////////////////////////


#endif