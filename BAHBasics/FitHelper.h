#if !defined(FITHELPER_H)
#define FITHELPER_H

#include "BAHSetup.h"
#include "HistoHelper.h"
#include "DrawResources.h"
#include "VoightFit.h"

//================================================================================================
void PrintUncert(double EffMC, double EfferMC, double EffDat, double EfferDat){
  double Uncert;
  double UncertEr;
  Uncert = EffMC/EffDat-1;
  UncertEr=FSPhysics::quadraticSum(EfferMC/EffMC,EfferDat/EffDat);
  cout << "  Efficiency  [MC]  : " << EffMC  << " \\pm " << EfferMC << endl;
  cout << "  Efficiency [Data] : " << EffDat << " \\pm " << EfferDat << endl;
  THINLINE();
  cout << "  Uncertainty (%) : " << Uncert*100 << " \\pm " << UncertEr*100 << " \\%"<< endl;
  cout << "  Uncert Sum (%)  : " << (abs(Uncert) + UncertEr)*100 << " \\%"<< endl;
  return;
}
//--------------------------------------------
void getErrors(TString Set ,bool raw){
  if(Set=="gPP"){
    if(!raw){
      SPACEstr("chi_{c0}");
      PrintUncert(93.7,1.51, 93.3,3.31);
      SPACEstr("chi_{c1}");
      PrintUncert(96.1,2.33, 94.9,4.96);
      SPACEstr("chi_{c2}");
      PrintUncert(94.9,2.87, 95.9,4.79);
    }
    if(raw){
      SPACEstr("chi_{c0}");
      PrintUncert(90.3,2.07, 91.0,3.40);
      SPACEstr("chi_{c1}");
      PrintUncert(92.7,2.86, 92.6,4.79);
      SPACEstr("chi_{c2}");
      PrintUncert(91.9,3.41, 91.0,5.54);
    }
  }
  if(Set=="gkk"){ 
    if(!raw){             // EffMC, EfferMC, EffDat, EfferDat
      SPACEstr("chi_{c0}");
      PrintUncert(95.5,0.374, 93.7,0.557);
      SPACEstr("chi_{c2}");
      PrintUncert(98.2,0.418, 97.8,1.23);
      SPACEstr("chi_{c1} via chi_{c2} with diff cut-radius TBD");
    }
    if(raw){             // EffMC, EfferMC, EffDat, EfferDat
      SPACEstr("chi_{c0}");
      PrintUncert(96.7,0.381, 93.4,0.555);
      SPACEstr("chi_{c2}");
      PrintUncert(95.8,0.427, 97.3,1.31);
      SPACEstr("chi_{c1} via chi_{c2} with diff cut-radius TBD");
    }
  }
  /*          OLD Fit results
  if(Set=="gkk"){
    if(!raw){
      SPACEstr("chi_{c0}");
      PrintUncert(95.8,0.375, 93.6,0.551);
      SPACEstr("chi_{c2}");
      PrintUncert(96.7,0.411, 97.8,1.22);
      SPACEstr("chi_{c1} via chi_{c2} with diff cut-radius TBD");
    }
    if(raw){
      SPACEstr("chi_{c0}");
      PrintUncert(96.7,0.381, 93.3,0.555);
      SPACEstr("chi_{c2}");
      PrintUncert(94.1,0.431, 97.2,1.30);
      SPACEstr("chi_{c1} via chi_{c2} with diff cut-radius TBD");
    }
  }*/
}
//--------------------------------------------
TString getSimpleNameIS(TString FullDecayName){
  if(FullDecayName.Contains("chi_{c0}")){ return "#chi_{c0}"; }
  if(FullDecayName.Contains("chi_{c1}")){ return "#chi_{c1}"; }
  if(FullDecayName.Contains("chi_{c2}")){ return "#chi_{c2}"; }
  if(FullDecayName.Contains("chi_{cJ}")){ return "#chi_{cJ}"; }
  if(FullDecayName.Contains("J/#psi")){   return "J/#psi";    }
  if(FullDecayName.Contains("#psi(2S)")){ return "#psi(2S)";  }
  return "Mehh, wrong";
}
//--------------------------------------------
bool CheckRangePair( pair<TString,TString> Range, double TestValue){ 
  bool minCheck = FSString::TString2double(Range.first)  < TestValue; 
  bool maxCheck = FSString::TString2double(Range.second) > TestValue; 
  return minCheck&&maxCheck; 
}
//--------------------------------------------
void printNames(TString str1, TString str2){ 
  cout << "------  Adding "+str1+" and "+str2+"  ------" << endl;
}
//--------------------------------------------
vector<double> VecTStringToDoub( vector<TString> TStringVector ){
  vector<double> output;
  output.resize(TStringVector.size());
  for(int i=0; i<TStringVector.size(); i++){  // Filling double-Vec with TString-Vec inputs
    output[i] = FSString::TString2double(TStringVector[i]); 
  }
  return output;
}
//--------------------------------------------
vector<TString> VecDoubToTString( vector<double> DoubleVector ){
  vector<TString> output;
  output.resize(DoubleVector.size());
  for(int i=0; i<DoubleVector.size(); i++){ // Filling TString-Vec with double-Vec inputs
    output[i] = FSString::double2TString(DoubleVector[i]); 
  }
  return output;
}
//================================================================================================
vector<TString> ApplyFit( TH1F* hfit, vector<pair<TString,TString>> FitValues, TString bounds, TString FitTag, TString fitType = "CHI2", bool fixParams = false, bool checkprint = false){
  // Inputs Needed Here:  [Can turn Entire Thing Into One Function with a map output]
  //      vector<pair<TString,TString>>  FitValues, 
  //      TString bounds,      to get [min,max,binsize]
  //      TH1F* hfit   
  double xmin = FSString::parseBoundsLowerX(bounds);
  double xmax = FSString::parseBoundsUpperX(bounds);
  double binsize = FSString::parseBoundsBinSizeX(bounds);
  //---------------------------------------------------
  vector<TString> FitNames;
  TString dumNum;
  vector<TString> dumVec;
  vector<double> InputFitNums;
  TString PolyName;
  if(checkprint)cout << "Setting up N-Distributions to add to fit" << endl;
  for(int i=0 ; i < FitValues.size(); i++){
    dumNum = FSString::int2TString(i);
    dumVec = FSString::parseTString(FSString::captureParentheses(FitValues[i].second,0),",");
    InputFitNums = VecTStringToDoub(dumVec);
    //InputFitNums.resize(dumVec.size());
    //for(int i=0; i<dumVec.size(); i++){ InputFitNums[i] = FSString::TString2double(dumVec[i]); }  // Filling double FitVec Inputs
    //---------------------------------------------------
    if(FitValues[i].first.Contains("Voight")){
      FSFitUtilities::createFunction(new FSFitVOIGT("Voight"+dumNum,xmin,xmax));
      //                           VoightFit Name , Size ,   Sigma [From Gauss]   ,  Mass (on xaxis) ,  Width [from BrietWigner]
      FSFitUtilities::setParameters("Voight"+dumNum, InputFitNums[0], InputFitNums[1], InputFitNums[2]+binsize/2, InputFitNums[3]);
      if(fixParams){
        //FSFitUtilities::fixParameter("Voight"+dumNum+":s");
        //FSFitUtilities::fixParameter("Voight"+dumNum+":M");
        //FSFitUtilities::fixParameter("Voight"+dumNum+":W");
      }
      FitNames.push_back("Voight"+dumNum);
    }
    //---------------------------------------------------
    if(FitValues[i].first.Contains("Poly")){
      FSFitUtilities::createFunction(new FSFitPOLY("Poly"+dumNum,xmin,xmax,InputFitNums[0])); // Set as nth order polynomial
      //                                                  PolyFit Name ,         a     +         b   *x  +      c*x^{2}  +      d*x^{3}   +      e*x^{4}   +      f*x^{5}  
      if(InputFitNums[0]==1)FSFitUtilities::setParameters("Poly"+dumNum, InputFitNums[1], InputFitNums[2]);
      if(InputFitNums[0]==2)FSFitUtilities::setParameters("Poly"+dumNum, InputFitNums[1], InputFitNums[2], InputFitNums[3]);
      if(InputFitNums[0]==3)FSFitUtilities::setParameters("Poly"+dumNum, InputFitNums[1], InputFitNums[2], InputFitNums[3], InputFitNums[4]);
      if(InputFitNums[0]==4)FSFitUtilities::setParameters("Poly"+dumNum, InputFitNums[1], InputFitNums[2], InputFitNums[3], InputFitNums[4],InputFitNums[5]);
      if(InputFitNums[0] >4)FSFitUtilities::setParameters("Poly"+dumNum, InputFitNums[1], InputFitNums[2], InputFitNums[3], InputFitNums[4],InputFitNums[5],InputFitNums[6]);
      FitNames.push_back("Poly"+dumNum);
      PolyName = "Poly"+dumNum;
    }
    //---------------------------------------------------
    dumVec.clear();
    InputFitNums.clear();
  }
  if(checkprint)cout << "Done setting up N-Distributions to add to fit" << endl;
  if(checkprint)THINLINE();
  if(checkprint)cout << "Setting up and Applying Fit Functions" << endl;
  if(checkprint)SPACEin();
  // Now that Functions are set-up, gonna combine them
  if(checkprint){
    SPACEnum(FitNames.size());
    for(int i=0; i<FitNames.size(); i++){  cout << FitNames[i] << endl; }
  }
  TString FinFitName;
  if(FitNames.size()>1){
    printNames(FitNames[1],FitNames[0]); 
    FSFitUtilities::createFunction("Fin1",FitNames[1]+"+"+FitNames[0]);
    if(FitNames.size()>2){
      printNames(FitNames[2],"Fin1"); 
      FSFitUtilities::createFunction("Fin2",FitNames[2]+"+Fin1");
      if(FitNames.size()>3){
        printNames(FitNames[3],"Fin2"); 
        FSFitUtilities::createFunction("Fin3",FitNames[3]+"+Fin2");
        if(FitNames.size()>4){
          printNames(FitNames[4],"Fin3"); 
          FSFitUtilities::createFunction("Fin4",FitNames[4]+"+Fin3");
        }
      }
    }
  }
  // Properly getting correct Fitname of the final composite fit function
  if(FitNames.size()==1){ FinFitName = FitNames[0];}
  if(FitNames.size()==2){ FinFitName = "Fin1";}
  if(FitNames.size()==3){ FinFitName = "Fin2";}
  if(FitNames.size()==4){ FinFitName = "Fin3";}
  if(FitNames.size()==5){ FinFitName = "Fin4";}
  //---------------------------------------------------
  if(checkprint)cout << " Applying Fit to Composite Fit Function and Drawing" << endl;
  //---------------------------------------------------
  // get function before fit [Just to Check for now]
  //TF1* fpre = FSFitUtilities::getTF1(FinFitName); fpre->SetLineStyle(kDashed); fpre->SetLineColor(kBlue);
  // do the fit
  FSFitUtilities::createDataSet(FitTag+".Fit",hfit);   // Associating "Fit" with the histogram hfit;
  FSFitUtilities::createMinuit(FitTag+".minuit",FitTag+".Fit",FinFitName,fitType); // Fitting "Fit"-data-set with the function FinFitName;
  //FSFitUtilities::addFitComponent("minuit","Fit",FinFitName);
  FSFitUtilities::migrad(FitTag+".minuit");
  // draw function after fit
  TF1* FittedFunction = FSFitUtilities::getTF1(FinFitName);
  FittedFunction->SetLineColor(kkSpaceCadet);
  //---------------------------------------------------
  // For drawing the fitted polynomial
  for(int i=0 ; i < FitValues.size(); i++){
    if(FitValues[i].first.Contains("Poly")){
      TF1* FittedPolynomial = FSFitUtilities::getTF1("Poly"+FSString::int2TString(i));
      FittedPolynomial->SetLineColor(kRed);
      FittedPolynomial->Draw("same");
    }
  }
  //---------------------------------------------------
  FittedFunction->Draw("same");
  //---------------------------------------------------
  THINLINE();
  cout << " Fit Likelihood : " << FSFitUtilities::likelihood(FitTag+".minuit") << endl;
  cout << " Fit Chi^2      : " << FSFitUtilities::chisquare(FitTag+".minuit") << endl;
  cout << " Fit nDOF       : " << FSFitUtilities::nDOF(FitTag+".minuit") << endl;
  THINLINE();
  //cout << " Fit Negative LogLikelihood : " << TMath::Log10(-FSFitUtilities::likelihood(FitTag+".minuit")) << endl;
  cout << " Fit Chi^2/DOF      : " << FSFitUtilities::chisquare(FitTag+".minuit")/FSFitUtilities::nDOF(FitTag+".minuit") << endl;
  THINLINE();
  return FitNames;
}
//================================================================================================
map<TString, vector<double>> getFitInfoMap(vector<TString> FitNames, TString bounds, vector<pair<TString,TString>> CutRanges, bool checkprint=false){
  map<TString, vector<double>> FitValueMap; 
  double xmin = FSString::parseBoundsLowerX(bounds);
  double xmax = FSString::parseBoundsUpperX(bounds);
  double binsize = FSString::parseBoundsBinSizeX(bounds);
  // Vector pairs To organize the FitName and Resultant Fit Function [Not useful atm]
  //vector<pair<TString,TF1*>> FitFunctionVec; 
  TF1* dummyFunction;
  double NumDumPre;
  double NumDumPost;
  double MassDummy;
  double ErrorDummy;
  vector<double> FinFitNums;
  // To Supress Integration Tolerance Errors  [Imma just tolerate em]
  //ROOT::Math::IntegratorOneDimOptions::SetDefaultIntegrator("Gauss");
  for(int i=0 ; i < FitNames.size(); i++){  
    //---------------------------------------------------
    // Setting up FitFunctionVec for Plotting  [Not Drawing the individual fuctions at the moment]
    dummyFunction = FSFitUtilities::getTF1(FitNames[i]); 
    if(FitNames[i].Contains("Poly")){
      dummyFunction->SetLineWidth(3);
      dummyFunction->SetLineColor(kBlue);
      //dummyFunction->Draw("same");
    }
    if(i==0) dummyFunction->SetLineColor(kkSpaceCadet); dummyFunction->SetLineStyle(kDotted);        
    if(i==1) dummyFunction->SetLineColor(kkJimiPurple); dummyFunction->SetLineStyle(kDashDotted);        
    if(i==2) dummyFunction->SetLineColor(kkDarkSlateGrey); dummyFunction->SetLineStyle(kDashed);        
    //dummyFunction->Draw("same");
    //FitFunctionVec.push_back(make_pair(FitNames[i],dummyFunction));
    //---------------------------------------------------
    // Setting up map to output resultant fit values
    //    Voight Usually (Total Integral, A_error,M,s,W ,  Cut Integral )
    //    Poly Usually   (Total Integral, a_error, a, b, c ,  Cut Integral_1  Cut Integral_2 ...  )
    //if(checkprint)cout << "---------- Initial Full Integration of : "+FitNames[i]+" ----------" << endl;
    NumDumPre = dummyFunction->Integral(xmin,xmax)/binsize;
    FinFitNums.push_back(NumDumPre); // Regardless of fit, Calculating the total Integrals
    //---------------------------------------------------
    if(FitNames[i].Contains("Voight")){
      if(checkprint)cout << "  Getting Resultant Fit Error and Parameters from: "+FitNames[i] << endl;
      // To get Efficiencies of interest, checking if Mass is in the cut range for Voight Fits
      MassDummy = FSFitUtilities::getParameterValue(FitNames[i]+":M");
      ErrorDummy=FSFitUtilities::getParameterError(FitNames[i]+":A")/binsize;
      //NumDum = dummyFunction->Integral(xmin,xmax)/binsize;
      //FinFitNums.push_back(NumDum);
      FinFitNums.push_back(ErrorDummy);  // Error on Fit  -->  Total Int Error
      FinFitNums.push_back(MassDummy);
      //FinFitNums.push_back(FSFitUtilities::getParameterValue(FitNames[i]+":s"));
      //FinFitNums.push_back(FSFitUtilities::getParameterValue(FitNames[i]+":W"));
      for(int i=0; i < CutRanges.size(); i++){ // Looping Over Mass Ranges
        if(CheckRangePair(CutRanges[i],MassDummy)){  // To only Pick Out the relevant Integral Total based on M.
          NumDumPost = dummyFunction->Integral(FSString::TString2double(CutRanges[i].first),FSString::TString2double(CutRanges[i].second))/binsize;
          FinFitNums.push_back(FSString::TString2double(CutRanges[i].first));
          FinFitNums.push_back(FSString::TString2double(CutRanges[i].second));
          FinFitNums.push_back(NumDumPost);                                // Cut Integral
          FinFitNums.push_back((NumDumPost/NumDumPre)*ErrorDummy);  // Cut error
          FinFitNums.push_back((NumDumPost/NumDumPre)*100);         // Efficiency (%)
          FinFitNums.push_back(FSPhysics::quadraticSum(ErrorDummy/NumDumPre,(1/NumDumPre)*ErrorDummy)*100); // Efficiency error (%)
        }
      }
    }
    //---------------------------------------------------
    if(FitNames[i].Contains("Poly")){ // Assuming second order polynomial again
      if(checkprint)cout << "  Getting Resultant Fit Parameters from: "+FitNames[i] << endl;
      FinFitNums.push_back(sqrt(NumDumPre));
      FinFitNums.push_back(FSFitUtilities::getParameterValue(FitNames[i]+":a"));
      FinFitNums.push_back(FSFitUtilities::getParameterValue(FitNames[i]+":b"));
      FinFitNums.push_back(FSFitUtilities::getParameterValue(FitNames[i]+":c"));
      for(int i=0; i < CutRanges.size(); i++){
        FinFitNums.push_back(dummyFunction->Integral(FSString::TString2double(CutRanges[i].first),FSString::TString2double(CutRanges[i].second))/binsize);
      }
    }
    //---------------------------------------------------
    FitValueMap.insert( pair<TString,vector<double>>(FitNames[i],FinFitNums)  );
    FinFitNums.clear();
  }
  return FitValueMap;
}
//================================================================================================
// Can be used with output of the fitter    SHOULD PROBABLY WRITE RESULTS TO A FILE
void writeFitValueMap( map<TString, vector<double>> OutputMap, int FitNumber, TString OutputFile){
  vector<TString> PrintVec;
  vector<TString> StrVec;
  TString FullString;
  TString DumNum;
  TString VoightStr = "VoightFit Values: "+FSString::padTString("Tot Int",7,"L")
                    +", "+FSString::padTString("A_error",7,"R")
                    +", "+FSString::padTString("Mass",7,"R")
                    //+", "+FSString::padTString("Sigma",7,"R")
                    //+", "+FSString::padTString("Width",7,"R")
                    +", "+FSString::padTString("Cutmin",7,"R")
                    +", "+FSString::padTString("Cutmax",7,"R")
                    +", "+FSString::padTString("Cut Int",7,"R")
                    +", "+FSString::padTString("Cut Err",7,"R")
                    +", "+FSString::padTString("Cut Eff(%)",10,"R")
                    +", "+FSString::padTString("Eff Err(%)",10,"R");
  //---------------------------------------------------
  // Looping over 4 Voight fits arbitrarily
  PrintVec.push_back(VoightStr);
  for(int i = 0; i < FitNumber ; i++ ){
    DumNum = FSString::int2TString(i);
    //---------------------------------------------------
    // Looping over any Voight Fit that has results in it from fits 
    if(OutputMap["Voight"+DumNum].size()>0){
      StrVec = VecDoubToTString(OutputMap["Voight"+DumNum]);
      FullString = FSString::padTString("   VoightFit ["+DumNum+"]: ",11,"L");
      //---------------------------------------------------
      // Looping over the Output from Voight Fits. 
      //  Voight Usually (Total Integral, A_error, M, s, W , Cut Integral )
      //  Poly   Usually (Total Integral, a_error, a, b, c , Cut Integral_1  Cut Integral_2 ...  )
      // Should have: 
      for(int j=0; j<StrVec.size(); j++){
        if(j==0){  FullString = FullString+FSString::padTString(StrVec[j],7,"R"); }
        else if(j>StrVec.size()-3){FullString = FullString+", "+FSString::padTString(StrVec[j],10,"R"); }
        else{ FullString = FullString+", "+FSString::padTString(StrVec[j],7,"R"); }
      }
      PrintVec.push_back(FullString);
      FullString = "";
    }
  }
  TString PolyStr = "Poly Fit Values : "+FSString::padTString("Tot Int",7,"L")
                    +", "+FSString::padTString("sqr(Int)",7,"R")
                    +", "+FSString::padTString("a",7,"C")
                    +", "+FSString::padTString("b",7,"C")
                    +", "+FSString::padTString("c",7,"C")
                    +", "+FSString::padTString("Cut Int 1",7,"R")
                    +", "+FSString::padTString("Cut Int 2",7,"R")
                    +", "+FSString::padTString("Cut Int 3",7,"R");
  //---------------------------------------------------
  // Looping over 4 Poly fits arbitrarily
  PrintVec.push_back("");
  PrintVec.push_back(PolyStr);
  for(int i = 0; i < FitNumber ; i++ ){
    DumNum = FSString::int2TString(i);
    //---------------------------------------------------
    // Looping over any Voight Fit that has results in it from fits 
    if(OutputMap["Poly"+DumNum].size()>0){
      StrVec = VecDoubToTString(OutputMap["Poly"+DumNum]);
      FullString = FSString::padTString("   Poly Fit ["+DumNum+"] : ",13,"L");
      //---------------------------------------------------
      // Looping over the Output from Voight Fits. 
      //  Voight Usually (Total Integral, A_error, M, s, W , Cut Integral )
      //  Poly   Usually (Total Integral, a_error, a, b, c , Cut Integral_1  Cut Integral_2 ...  )
      // Should have: 
      for(int j=0; j<StrVec.size(); j++){
        if(j==0){ FullString = FullString+FSString::padTString(StrVec[j],7,"R"); }
        else{ FullString = FullString+", "+FSString::padTString(StrVec[j],7,"R"); }
      }
      PrintVec.push_back(FullString);
      PrintVec.push_back("");
      FullString = "";
    }
  }
  for (vector<TString>::iterator it = PrintVec.begin(); it != PrintVec.end(); it++){
    cout << *it << endl;
  }
  for (vector<TString>::iterator it = PrintVec.begin(); it != PrintVec.end(); it++){
    FSString::writeTStringToFile(OutputFile,*it,true);
  }
}
//================================================================================================
//================================================================================================
//================================================================================================
map<TString, vector<double>> getGeneralFit(bool MC, TString Set, TString category, vector<TString> DataSetTag, vector<TString> FNNTvec, vector<TString> ISCuts, vector<TString> ISLabels, 
      TString LegendDirection, bool logy, TString var, TString bounds, TString cuts, TString TITLE, TString xtitle,
      TString UnitsX, vector<pair<TString,TString>>  CutRanges, 
      vector<pair<TString,TString>> FitValues, bool backgrounds, TString fitType){
  // Setting up histograms, filenames, n-tuples and the histogram-stack for use
  TString FitTag = ""+xtitle;
  if(MC){ FitTag = FitTag+"MC"; }
  else{ FitTag = FitTag+"DAT"; }
  bool checkprint=true;
  double HistSupress = 0.005;
  TString INCMCyr = DataSetTag[0];
  TString CONTyr  = DataSetTag[1];
  TString DATAyr  = DataSetTag[2];
  int LegendEntries = 0;
  SPACEin();
  cout << "Beginning "+xtitle+" Histograms" << endl;
  TString FNS=FNNTvec[0];   TString NTS=FNNTvec[1]; 
  TString FNI=FNNTvec[2];   TString NTI=FNNTvec[3]; 
  TString FND=FNNTvec[4];   TString NTD=FNNTvec[5];
  TString FNDc=FNNTvec[6];  TString NTDc=FNNTvec[7];
  // For additional INCMC, SIGMC and anything other data types...
  vector<TString> FNNTvecINC = {FNI,NTI};
  TString FNI2;  TString NTI2; 
  // Incase FNNTvec doesn't have the dummy spots for dataC and INCMC2
  if(FNNTvec.size()>8){
    FND=FNNTvec[4];   NTD=FNNTvec[5];
    FNDc="";          NTDc="";
    FNI2=FNNTvec[8];  NTI2=FNNTvec[9]; 
    FNNTvecINC.push_back(FNI2);
    FNNTvecINC.push_back(NTI2);
  }
  TH1F* hbE;   TH1F* hDc;   TH1F* hD;     // INCMC, Continuum data and data of interest histograms
  TH1F* hbE2;
  // Getting the MC data set into a vector to 
  if(MC)cout << "Making specific SIGMC [ and maybe INCMC ] Histograms" << endl;
  //===================================================
  //            SIGMC histograms 
  //===================================================
  // Input Here is :   INCMCyr,CONTyr,DATAyr
  //--------------------
  // Initializing Signal cuts [Exclude from INCMC incase use INCMC info (or replacing it)]
  vector<TH1F*> histVec;  // Vector for setting max (kinda) and organizing/cleaning up with ryans function
  bool INC1cut = false;   bool INC2cut = false; // To reflect the cut in the full incmc plot's legend
    vector<pair<TString, vector<int>>> INCMCinfo;
  int NSpecificModes;
  TString MCSigCuts1="";
  TString MCSigCuts2="";
  TString cuttag;
  vector<int> INC2cutList;
  if(MC){
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
  //===================================================
  //            INCMC histograms 
  //===================================================
  // Input Here is :   INCMCyr,CONTyr,DATAyr
  //--------------------
  TString INCMC2tag = "ooopp";  // Just a place holder incase INCMC2 is used.
  double INCsize = 0;     double INCsize2 = 0;
  TString INCcuts;        TString INCcuts2;
  vector<TH1F*> INCMCHists;
  if(MC){
    INCMCHists = INCMCHistogramSetup(Set,DataSetTag,FNNTvecINC,category,var,bounds,MCSigCuts1,MCSigCuts2,cuts,checkprint);
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
  //===================================================
  //            DATA histograms 
  //===================================================
  // Input Here is :  MC , background ,  FND,NTD,  FNDc,NTDc,  category,var,bounds,cuts,   LegendEntries , INCMCyr,CONTyr,DATAyr
  //--------------------
  if(MC){
    cout << "Making Setting up Continuum Histogram if Needed" << endl;
    if(FNDc!=""){
      cout << "CONTINUUM" << endl; //cout << FNDc << endl << NTDc << endl;
      hDc = FSModeHistogram::getTH1F(FNDc,NTDc,category,var,bounds,cuts,getCONTScale(CONTyr,DATAyr));
      if(checkprint)cout << "Scale  CONT : " << getCONTScale(CONTyr,DATAyr) << endl;
      LegendEntries = LegendEntries + 1 ;
      THINLINE();
    }
  }
  double DataScaling = 1;
  if(!MC){
    if(FND!=""){
      cout << " Seeting up DATA Histogram :" << endl;//cout << FND << endl << NTD << endl;
      if(Set=="gtm"||Set=="get"||Set=="gep"||Set=="gepp"){
        if(FNNTvec.size()>8&&FNNTvec[8]!=""){ DataScaling =  getCONTScale("21",DATAyr);  }
      }
      hD = FSModeHistogram::getTH1F(FND,NTD,category,var,bounds,cuts,DataScaling);
      if(checkprint)cout << " CONTyr VS Conyr(12) =( "<< CONTyr<< " , "<<DATAyr<< " ) : ("<<getCONTScale(CONTyr,DATAyr) << " , "<<getCONTScale("21",DATAyr) << ")" << endl;
      if(checkprint)cout << "DATA Scale Used: " << DataScaling << endl;
      LegendEntries = LegendEntries + 1 ;
      THINLINE();
    }
  }
  cout << "Done getting Histograms. Now other shit... [organizing and plotting]" << endl;
  // Output Here is :     hD , hDc  ,   LegendEntries [Can get from passing a DataHistVec.size() = 2]
  //===================================================
  //       Stacking histograms in Order
  //===================================================
  // Setting up histograms in stack hs (INCNC -> Continuum -> SpecificModeN -> ... -> SpecificMode1)
  THStack* hs = new THStack("hs",TITLE);
  vector<TH1F*> histVecDummy;
  // Input Here is :  MC,checkprint,backgrounds, Title[or hs], HistSupress, ISCuts, INC2cutList, HistVec,INCMCHists,hDc,  FNDc,FNI2,FNI,INCsize2  or    hD  
  if(MC){
    if(backgrounds){
      // Starting from the bottom, Adding Continuum Data and then INCMC2, the INCMC2 Carves-out 
      if(checkprint)cout << "Adding Histograms to TStack" << endl;
      if(FNDc!=""){ hs->Add(hDc);}
      if(FNI2!=""&&INCsize2>HistSupress){ hs->Add(INCMCHists[1]);}
      if(checkprint)cout << "Adding Histograms from INCMC to Vector and TStack for organizing" << endl;
      histVecDummy = histVec;  // Dummy Just made for plotting to canvas in order
      // Using the saved numbers to pick out the specific Histograms from the INCMC FN wanted
      for(int i=0 ; i < INC2cutList.size() ;  i++){      
        hs->Add(histVecDummy[INC2cutList[i]]);
        histVecDummy.erase(histVecDummy.begin()+INC2cutList[i]);
      }
      if(checkprint)cout << "Adding Histograms from SIGMC to Vector and TStack for organizing" << endl;
      if(FNI!=""){  hs->Add(INCMCHists[0]);}
      for( int i=histVecDummy.size()-1 ; i>-1 ; i-- ){
        hs->Add(histVecDummy[i]);
      }
    }
    else{
    //Setting up histograms in stack hs with only Modes in ModeVec (SpecificModeN -> ... -> SpecificMode1)
      if(checkprint)cout << "Adding Histograms to TStack hs" << endl;
      for(int i=0 ; i < histVec.size() ;  i++){  
        hs->Add(histVec[i]);
      }
    }
  }
  if(!MC){  hs->Add(hD); cout << "ADDED SHIT SHIT" << endl;  }
  if(checkprint)cout << "Done Adding Histograms to TStack for Drawing" << endl;
  // Output Here is :   hs  
  //===================================================
  //       Setting Up MC Fit Parts
  //===================================================
  if(checkprint)cout << "Setting up the Fit Parts [Dummy Histogram so should get nothing here] " << endl;
  TH1F* hfit= FSHistogram::getTH1F(FNNTvec[0],FNNTvec[1],var,bounds,"(1==2)");
  // Input Here is :  MC , HistVec , INCMCHists , hDc    or    hD
  if(MC){
    for(int i=0 ; i < histVec.size() ;  i++){  
      hfit->Add(histVec[i]); 
    }
    if(backgrounds){   
      for(int i=0 ; i < INCMCHists.size() ;  i++){ 
        hfit->Add(INCMCHists[i]);  
      }
      if(FNDc!=""){ hfit->Add(hDc); }
    }
  }
  if(!MC){  hfit->Add(hD);  }
  if(checkprint)cout << "Finished Adding Histograms to hFit" << endl;
  // Output Here is :  hfit
  //===================================================
  // Setting up MinMax Consistancy in Signal, INCMMC and Data [histVec no longer only SIGMC]
  //===================================================
  if(checkprint)cout << "Setting Qualitites for INCMC and DATA histograms" << endl;
  // Adding INCMC histograms and Continuum histogram to the vector histVecto use setHistogramMaxMin
  if(MC){
    for(int i=0 ; i<INCMCinfo.size(); i++){ histVec.push_back(INCMCHists[i]); } 
    if(FNDc!=""){ histVec.push_back(hDc );  hDc->SetFillColor( getColorIS("CONT",0));  hDc->SetLineColor(getColorIS("CONT",0)); }
  }
  if(!MC &&FND!=""){  histVec.push_back(hD);}
  FSHistogram::setHistogramMaxMin(histVec,false,"MAX");
  if(checkprint)cout << "Done setting qualitites" << endl;
  if(checkprint)SPACEin();
  //===================================================
  // Setting logY if applicable. If histVec filled totally, could just loop over it.
  //===================================================
  if(checkprint)cout << "Checking/Setting Log qualitites [Not used here]" << endl;
  double Ymaxp;
  double Ymax;
  Ymax = hs->GetMaximum()*(1.1);
  
  if(checkprint)cout << "Finally Drawing Histogram TStack" << endl;
  // Finally drawing 
  if(MC){
    hs->SetMaximum(Ymax);
    hs->Draw("hist");  
  }
  if(!MC){
    hD->SetMaximum(Ymax);
    hD->Draw("same"); 
  }
  //if(!MC &&FND!=""){  hD->Draw("same"); }
  if(checkprint)cout << "Done Drawing Histgrams" << endl;
  if(checkprint)SPACEin();
  ////////////////////////////////////////////////////////////////////
  if(checkprint)cout << "Beginning to Draw Lines" << endl;
  // Can just pass xmin/xmax and use those to check if cut is outside the bounds and get scaling in the lines function...
  //double Xmin = FSString::parseBoundsLowerX(bounds);
  //double Xmax = FSString::parseBoundsUpperX(bounds);
  double binsize = FSString::parseBoundsBinSizeX(bounds);
  SPACEnum(1);
  //double Xmin= hs->GetXaxis()->GetXmin();
  SPACEnum(2);
  drawCutLines(kBlack,CutRanges,Ymax,binsize); // written above (limited to 3 pairs)
  // Drawing lines for control Samples  [Need to Hardcode them in DrawResources.h ]
  //if(NTS.Contains("Control")){ drawControlLines(Set,var,cuts,xtitle,Ymax,Xscale,kBlack); }
  if(checkprint)cout << "Done Drawing Lines" << endl;
  if(checkprint)SPACEin();
  //===================================================
  // Doing FIT Stuff Now
  //===================================================  
  // Inputs Needed Here:  [Can turn Entire Thing Into One Function with a map output]
  //      vector<pair<TString,TString>>  FitValues, 
  //      TString bounds,      to get [min,max,binsize]
  //  hfit   
  vector<TString> FitNames;
  bool fixParams = false;
  if(!MC &&FND!=""){ fixParams = true; }
  FitNames = ApplyFit(hfit,FitValues,bounds,FitTag,fitType,fixParams,checkprint);
  //  Inputs:     hfit    ,   fitType  ,  FitValues  ,  bounds
  //  Outputs:  FitNames
  //===================================================
  // Getting Final Fit Stuff Organized
  //===================================================
  if(checkprint)SPACEin();
  if(checkprint)cout << " Getting Resultant individual Fit Values and Functions " << endl;
  if(checkprint)SPACEin();
  //---------------------------------------------------
  // The main Info I want/need
  map<TString, vector<double>> FitValueMap = getFitInfoMap(FitNames,bounds,CutRanges,checkprint);
  //---------------------------------------------------
  if(checkprint)SPACEin();
  if(checkprint)cout << " Done With Making Fit Map " << endl;
  if(checkprint)SPACEin();
  //---------------------------------------------------
  if(checkprint)cout << " Starting to make Fit Legend " << endl;
  int VoightFits = 0;
  for(int i=0 ; i<FitNames.size(); i++){
    if(FitNames[i].Contains("Voight")) VoightFits++;
  }
  //===================================================
  // Setting up Legend
  //===================================================
  // Maybe Make an Setup Function To just Order the Names on the histogram in the first place.
  TString BaseIncLabel;
  TString BaseIncLabel2;
  if(FNI!=""){ BaseIncLabel = "2012 #psi(2S) INCMC";}
  //ISLabels
    //----------------------------------
  // Maybe Make an Setup/Organize Function for Legend
  TLegend *leg;
  double lxmin; 
  double lxmax;
  double lymin = 0.9-0.067*( LegendEntries + VoightFits );
  if(LegendDirection=="L"){  lxmin= 0.11; lxmax= 0.4; }
  if(LegendDirection=="M"){  lxmin= 0.37; lxmax= 0.63; }
  if(LegendDirection=="R"){  lxmin= 0.64; lxmax= 0.90;}
  if(LegendDirection!="NO"&&LegendEntries!=0){
    leg = new TLegend(lxmin,lymin,lxmax,0.9);
    //if(xtitle.Contains("Events Total")){leg->SetHeader(category,"C");}  // CAN MAKE A LOOP BELOW HERE...
    //----------------------------------
    if(MC){
      for( int i = 0 ; i < histVecDummy.size() ; i++){
        if((getSIGScale(1,ISCuts[i],Set,DATAyr)>0.0000001||getINCScaleMode(INCMCyr,DATAyr,ISCuts[i])>0.0000001)
          &&(ISLabels.size()>0)){
          leg->AddEntry(histVec[i],ISLabels[i],"f");
          if(checkprint)cout << ISLabels[i] << endl;
        }
      }
      if(FNI!=""){  leg->AddEntry(INCMCHists[0],BaseIncLabel,"f");  }    
      if(INC2cutList.size()>0){
        for( int i = 0 ; i < INC2cutList.size() ; i++){
          leg->AddEntry(histVec[INC2cutList[i]],ISLabels[INC2cutList[i]],"f");
        } 
      }
      if(FNI2!=""&&INCsize2>HistSupress){ leg->AddEntry(INCMCHists[1],BaseIncLabel2,"f"); }
      // Probably Useful to make a legend title function or add more options... idk.  Eventually...
      if(FNDc!=""){leg->AddEntry(hDc,"3650 DATA","f");}
    }
    //----------------------------------
    if(!MC){
      if(FND!=""&&(FND.Contains("3686")||FND.Contains("control"))){ leg->AddEntry(hD,"2012 #psi(2S) DATA","lep");}
    }
    //----------------------------------
    vector<TString> StrVec;
    vector<TString> FitLegend;
    TString DumNum;
    //leg->SetTextAlign(12);
    for(int i=0 ; i < FitNames.size() ; i++ ){
      if(FitNames[i].Contains("Voight")){
        DumNum = FSString::int2TString(i);
        StrVec = VecDoubToTString(FitValueMap["Voight"+DumNum]);
        //FitLegend.push_back(getSimpleNameIS(ISLabels[i])+" eff(%)="+StrVec[7]+"#pm"+StrVec[8]);
        leg->AddEntry("",getSimpleNameIS(ISLabels[i])+" eff(%)="+StrVec[7]+"#pm"+StrVec[8],"");
      }
    }
    //if(FitLegend.size()>1){TLegendEntry *le1=leg->AddEntry("",FitLegend[0],""); le1->SetTextAlign(12); }
    //if(FitLegend.size()>2){TLegendEntry *le2=leg->AddEntry("",FitLegend[1],""); le2->SetTextAlign(12); }
    //if(FitLegend.size()>3){TLegendEntry *le3=leg->AddEntry("",FitLegend[2],""); le3->SetTextAlign(12); }
    //if(FitLegend.size()>4){TLegendEntry *le4=leg->AddEntry("",FitLegend[3],""); le4->SetTextAlign(12); }
    //----------------------------------
    leg->SetMargin(0.18);  // To save some space
    leg->SetTextSize(0.025); // works fine
    //leg->SetFillStyle(0);
    //leg->SetBorderSize(0);  //no border for legend [Looks ugly in my case]
    leg->Draw("same");
  }
  //===================================================
  // Finishing Histogram and clearing things
  //===================================================
  // Putting Map Before setting up Canvas because might want to use in legend.
  if(checkprint)SPACEin();
  if(checkprint)cout << " Done Setting up Vector of Functions and Map of Values [A_error, etc...] " << endl;
  
  if(MC){Setup1DAxis(hs,bounds,xtitle,UnitsX);}
  else{Setup1DAxis(hD,bounds,xtitle,UnitsX);}
  THINLINE();
  cout << " Done with "+xtitle+" Histogram" << endl;
  SPACEin();

  if(checkprint)cout << "Fitting Functions: " << endl;
  if(checkprint)THINLINE();
  if(checkprint)FSFitUtilities::showFunctions();
  if(checkprint)SPACEin();
  //cout << "Clearing Functions: " << endl;
  //if(checkprint)SPACEin();
  //FSFitUtilities::clear();
  //if(checkprint)FSFitUtilities::showFunctions();
  //FSFitUtilities::clear(true);
  SPACEin();
  return FitValueMap;
}







#endif