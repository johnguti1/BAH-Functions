#if !defined(BAHDATASETS_H)
#define BAHDATASETS_H

 #include "BAHUtilities.h"
 #include "ScalingHelper.h"

//================================================================================================
// Functions in the file:
//  --------------------------------------------
//  TString getFN(TString Set, TString FullDataSetLabel, bool moreskim = false)
//  --------------------------------------------
//  vector<double> getDataInfo(TString DataSetLabel, TString Set = "", TString IntermedState = "")
//  --------------------------------------------
//  void printDataInfo(TString DataSetLabel, TString Set = "", TString IntermedState = "")
//  --------------------------------------------
//  double getScale( TString DataSetLabel, TString ReferenceDataLabel, TString Set = "", TString IntermedState = "")
//  --------------------------------------------
//  map<TString, list<TString>> HistogramAssociation(TString Set, TString FullDataSetLabel, TString Cut)
//  --------------------------------------------
//  void printDataSets(); Just a book keeping of data sets currently usable.
//================================================================================================


  // declaring private class data members
//private:
  //TString m_Set;
//=========================================================================================



class BAHDecays;

//=========================================================================================
//public:
  // ***************************************************************
  // MAKING FUNCTIONS THAT ARE GENERALLY USEFUL
  // ***************************************************************
  //================================================================================================
  // A nice tool to get all the applicable relevant info (lumonsity,energy,number of events,etc...)
  //  "INC-ntINC.INCMC.3686.2021"
  // SHOULD INCLUDE CUT TO scale based on IS mroe fuildly without DUMB names
  vector<double> getDataInfo(TString DataSetLabel, TString Set = "", TString IntermedState = "", TString MCCut = "", bool checkprint = false){
    if(DataSetLabel==""){ 
      cout << " DataSetLabel is empty so returning Energy=Lumin=Year=Events=0.0, InternalScaling=1.0 " << endl; 
      return {0.0,0.0,0.0,0.0,1.0};
    }
    //------------------------------
    if(checkprint) cout << "Organizing DataSetLabel String for Usage" << endl; 
    vector<TString> InputInfo = FSString::parseTString(DataSetLabel,".");
    if(checkprint) printVector(InputInfo);
    vector<double> OutputInfo;
    //------------------------------
    double Energy=0.0;           // in MeV
    double Luminosity=0.0;       // in pb^{-1}
    double Year=0.0;             // 0.0 signifies SIGMC or ALL of a DATA or INCMC
    double Events=0.0;           // Events Total for Set. In SIGMC case, Generated number of events
    double InternalScaling=1.0;  // Typical doesn't matter unless SIGMC or weird INCMC (3770 is 40x)
    //------------------------------
    if(InputInfo[1]!="SIGMC"){
      if(checkprint) cout << "Is not SIGMC or using INCMC or DATA" << endl; 
      //=================================
      // Checking sqrt(s)=3686 MeV Data/MC Set Info
      if(InputInfo[2]=="3686"){
        if(checkprint) cout << "Energy is 3686, INCMC or DATA" << endl; 
        Energy = 3686.0;
        //------------------------------
        if(InputInfo.size()==3){  // No year so using all files on hand at 3686
          Year = 091221.0; // Abbreviate the year to fit all in. (and everything in 2000s)
          if(InputInfo[1]=="INCMC"){
            if(checkprint) cout << "Using INCMC at 3686" << endl; 
            Events     = 2.3*pow(10,9)  + 341*pow(10,6)  + 106.0*pow(10,6);
            Luminosity = 3414.4  + 506.92  + 161.63;  // Assuming the same luminosity
          }
          if(InputInfo[1]=="DATA" ){ // Not useful atm
            if(checkprint) cout << "Using DATA at 3686" << endl; 
            Events     = 2.26*pow(10,9) + 341.1*pow(10,6) + 107.0*pow(10,6);
            Luminosity = 3414.4  + 506.92  + 161.63;
          }
        }
        //------------------------------
        if(InputInfo.size()>3){ // Assuming same luminosity for simplicity (maybe derive it for 2021)
          if(InputInfo[3]=="2009"){
            Year       = 2009;
            Luminosity = 161.63;
            if(InputInfo[1]=="INCMC"){ Events = 106.0*pow(10,6);}
            if(InputInfo[1]=="DATA" ){ Events = 107.0*pow(10,6);}
          }
          if(InputInfo[3]=="2012"){
            Year       = 2012;
            Luminosity = 506.92;
            if(InputInfo[1]=="INCMC"){ Events = 341*pow(10,6);}
            if(InputInfo[1]=="DATA" ){ Events = 341.1*pow(10,6);}
          }
          if(InputInfo[3]=="2021"){
            Year       = 2021;
            Luminosity = 3414.4;
            if(InputInfo[1]=="INCMC"){ Events = 2.3*pow(10,9);}
            if(InputInfo[1]=="DATA" ){ Events = 2.26*pow(10,9);}
          }
          //------------------------------
        }
        //------------------------------
      }
      //=================================
      // Checking sqrt(s)=3770 MeV Data/MC Set Info
      if(InputInfo[2]=="3770"){
        Energy = 3770.0;
        if(InputInfo[1]=="INCMC"){InternalScaling = 0.025;} // Takes into account 1/40 of most decay modes.
        //------------------------------
        if(InputInfo.size()==3){  // No year so using all files on hand at 3770
          Year = 22.0; // Abbreviate the year to fit all in. (and everything in 2000s)
          if(InputInfo[1]=="INCMC"){
            // Don't have events, just luminosity and energy
            Luminosity = 4977.0  ;//+ 2931.8;  // Assuming the same luminosity (say made 1:1 [x40 generally])
          }
          if(InputInfo[1]=="DATA" ){ // Not useful atm
            // Don't have events, just luminosity and energy
            Luminosity = 4977.0  ;//+ 2931.8;
          }
        }
        //------------------------------
        if(InputInfo.size()>3){ // Assuming same luminosity for simplicity (maybe derive it for 2021)
          //if(InputInfo[3]=="2011"){
          //  Year       = 2011;  // 2010-2011 set
          //  Luminosity = 2931.8;
          //}
          if(InputInfo[3]=="2021"){
            Year       = 2021;
            Luminosity = 4977.0;
          }
        }
      }
      //=================================
      // Checking sqrt(s)=3770 MeV Data/MC Set Info
      if(InputInfo[2]=="3650"){
        Energy = 3650.0;
        //------------------------------
        if(InputInfo.size()==3){  // No year so using all files on hand at 3770
          Year = 22; // Abbreviate the year to fit all in. (and everything in 2000s)
          if(InputInfo[1]=="DATA" ){ // Not useful atm
            // Don't have events, just luminosity and energy
            Luminosity = 410.0;
          }
        }
        //------------------------------
        if(InputInfo.size()>3){ // Assuming same luminosity for simplicity (maybe derive it for 2021)
          //if(InputInfo[2]=="2011"){
          //  Year       = 2011;  // 2010-2011 set
          //  Luminosity = 2931.8;
          //}
          if(InputInfo[3]=="2022"){
            Year       = 2022;
            Luminosity = 410.0;
          }
        }
      //=================================
      }
    }
    vector<double> SignalValues;
    if(InputInfo[1]=="SIGMC"){
      //------------------------------
      //  "INC-ntINC.SIGMC.3686"      SIGMC   gtm  get  gep  geppp    tt (for checking)
      //  "INC-ntGEN.SIGMC.3686"      SIGMC   gtm  get  gep  geppp    tt (for checking)
      //------------------------------
      //  "INC-ntINC.SIGMC.3686"      SIGMC   gpp  gPP  eepp  mmpp
      //  "INC-ntGEN.SIGMC.3686"      SIGMC   gpp  gPP  eepp  mmpp
      //------------------------------
      //  "EXC-ntINC.SIGMC.3686"      SIGMC   gpp  gkk  gPP
      //  "EXC-ntGEN.SIGMC.3686"      SIGMC   gpp  gkk  gPP
      //------------------------------
      Energy=3686; // Assuming since the scaling is done to fit with number of events from psi(2S) at 3686.
      // DataSetLabel can be impletemented into SignalValues to keep track of Number of event made for specific set. 
      // Otherwise, need to manually comment out which one youre using. 
      // Typically okay though since I generate them with around the same amount usually... 
      SignalValues = getSIGValues(IntermedState,Set);
      Events = SignalValues[0];
      InternalScaling = SignalValues[1];  // Gives BR from psi(2S) to any intermed states and then and intermed states to final state
      if(Set=="tt"){
        InternalScaling = InternalScaling * 1.0;  // Need to take into account the e+e- properbly
      }
    }
    OutputInfo = {Energy,Luminosity,Year,Events,InternalScaling};
    return OutputInfo;
  }
  //================================================================================================
  void printDataInfo(TString DataSetLabel, TString Set = "", TString IntermedState = ""){
    vector<double> DataSetInfo = getDataInfo(DataSetLabel,Set,IntermedState);  
    cout << "----   Output for : "+DataSetLabel+"   -----" << endl;
    if(DataSetLabel.Contains("SIGMC")&&(Set!=""||IntermedState!="")){
      cout << "------- with  Set="+Set+"  and  IS="+IntermedState+"  -------" << endl;
    }
    if(!(DataSetLabel.Contains("SIGMC"))){
      cout << "---- Not SIGMC so Set and IS don't matter  -----" << endl;
    }
    cout << "Energy         : " << DataSetInfo[0] <<endl;
    cout << "Luminosity     : " << DataSetInfo[1] <<endl;
    cout << "Year           : " << DataSetInfo[2] <<endl;
    cout << "Events         : " << DataSetInfo[3] <<endl;
    cout << "InternalScaling: " << DataSetInfo[4] <<endl;
    return;
  }
  //================================================================================================
  double getDataSetScale( TString DataSetLabel, TString ReferenceDataLabel, TString Set = "", TString IntermedState = "", bool checkprint = false){
    vector<double> DataSetInfo   = getDataInfo(DataSetLabel      ,Set,IntermedState);
    if(ReferenceDataLabel==""){
      cout << "No Reference Used to defaulting to 'InternalScaling' (usually 1)";
      return DataSetInfo[4]*1;
    }
    vector<double> ReferenceInfo = getDataInfo(ReferenceDataLabel,Set,IntermedState);
    double Energy =DataSetInfo[0];           double EnergyRef  =ReferenceInfo[0];
    double Lumin  =DataSetInfo[1];           double LuminRef   =ReferenceInfo[1];    
    double Year   =DataSetInfo[2];           double YearRef    =ReferenceInfo[2];       
    double Events =DataSetInfo[3];           double EventsRef  =ReferenceInfo[3];        
    double InternalScaling=DataSetInfo[4];   double InternalScalingRef=ReferenceInfo[4];   // Should probably never have Internal scaling of reference
    // ReferenceDataLabel will typically be INCMC or Data and maybe Contintuum (still data) [SIGMC doesn't make sense...]
    //------------------------------
    double ScaleOutput = 1.0;
    double Napprox     = 1.0;        double NapproxRef = 1.0;
    double EnergyScaling=1.0;
    //------------------------------
    SPACEin();
    printDataInfo(DataSetLabel,Set,IntermedState);
    SPACEin();
    printDataInfo(ReferenceDataLabel,Set,IntermedState);
    SPACEin();
    //------------------------------
    // Checking if energies are non-zero and equal (convenient and easy)
    //if((Lumin==0.0&&LuminRef==0.0)&&(!DataSetLabel.Contains("SIGMC"))){
    //  cout << "---- Lumin1==Lumin2 so INCMC or DATA are not Setup, setting Scale = 1----" << endl;
    //  THINLINE();
    //  return 1.0; // crap...
    //}c
    // TRY TO NOT USE EVENTS BECAUSE THAT INFO IS SHAKY AT TIMES
    if((Energy!=0.0&&Energy==EnergyRef)&&(Lumin==LuminRef)&&(!DataSetLabel.Contains("SIGMC"))){
      cout << "---- (Energy1,Lumin1)==(Energy2,Lumin2) where Energy!=0.0, scaling with Scale1/Scale2  ----" << endl;
      return InternalScaling/InternalScalingRef;
    }
    if((Energy==0.0&&EnergyRef==0.0)&&(Lumin==0.0&&LuminRef==0.0)&&(!DataSetLabel.Contains("SIGMC"))){
      cout << "---- Energy1==Energy2==Lumin1==Lumin2==0.0, Not Setup so using 1  ----" << endl;
      return 1;
    }
    if((DataSetLabel.Contains("SIGMC")&&Events==500000.0&&InternalScaling==0.01)){
      cout << "---- Signal not in getSIGValues(), Defaulting to Scale = 1 ----" << endl;
      THINLINE();
      return 1.0; // crap...
    }
    if(Energy!=0.0&&Energy==EnergyRef&&LuminRef!=0.0){
      // (LuminRef/Lumin) is to scale to the reference DataSet, InternalScaling to take into acount the internal sclaing if it is difference.
      ScaleOutput = (LuminRef/Lumin)*(InternalScaling/InternalScalingRef); // InternalScalingRef should usually be 1.
      cout << "---- Good input! ----" << endl;
      THINLINE();
      return ScaleOutput;
    }
    double Ndummy=1.0;
    if(Energy!=EnergyRef&&(LuminRef!=0.0)){
      if(DataSetLabel.Contains("SIGMC")){      
        if(Lumin==0.0){ // Using full 3686 info for SIGMC since its probably excessivly made events
          Lumin = 3414.4+506.92+161.63;
          Ndummy = 2.3*pow(10,9)+341*pow(10,6)+107.0*pow(10,6);
        } 
        Napprox     = Lumin/pow(Energy,2); 
        NapproxRef  = LuminRef/pow(EnergyRef,2); 
        cout << "Napprox = "<<"( "<<Lumin*pow(10,9)<<"/"<<pow(Energy,2)<<")"<<endl; 
        cout << "NapproxRef = "<<"( "<<LuminRef*pow(10,9)<<"/"<<pow(EnergyRef,2)<<")"<<endl; 
        EnergyScaling = NapproxRef/Napprox;
        cout << "Scale = "<<EnergyScaling<<" * "<<"( "<<Ndummy<<"/"<<Events<<")* "<<InternalScaling<<endl; 
        ScaleOutput = EnergyScaling*(Ndummy/Events)*InternalScaling;
      }
      else{
        Napprox     = Lumin/pow(Energy,2); 
        NapproxRef  = LuminRef/pow(EnergyRef,2); 
        cout << "Napprox    = "<<"( "<<Lumin*pow(10,9)<<"/"<<pow(Energy,2)<<")"<<endl; 
        cout << "NapproxRef = "<<"( "<<LuminRef*pow(10,9)<<"/"<<pow(EnergyRef,2)<<")"<<endl; 
        EnergyScaling = NapproxRef/Napprox;
        cout << "Scale = "<<EnergyScaling<<" * "<<InternalScaling<<endl;
        ScaleOutput = EnergyScaling*InternalScaling;
      }
      cout << "---- Good input for scaling! ----" << endl;
      return ScaleOutput;
    }
    cout << "---- Terrible/Shit/Wrong input so output is 711 ----" << endl;
    THINLINE();
    return 711.0; // crap...
  }
  //================================================================================================
  void printDataSets(){
    SPACEin();
    cout << "List of Available Files" << endl;
    SPACEin();
    //========  Main Project  ============   gtm  get  gep  geppp
    cout << "Main Project  (Inclusive) " << endl;
    cout << "For Sets:  gtm , get , gep , gepp  , tt" << endl;
    THINLINE();
    cout << " ->  INC-ntINC.SIGMC.3686"     << endl;
    cout << "   ->  INC-ntGEN.SIGMC.3686"     << endl;
    THINLINE();
    cout << " ->  INC-ntINC.INCMC.3686"     << endl;
    cout << "   ->  INC-ntINC.INCMC.3686.2009"<< endl;
    cout << "   ->  INC-ntINC.INCMC.3686.2012"<< endl;
    cout << "   ->  INC-ntINC.INCMC.3686.2021"<< endl;
    THINLINE();
    cout << " ->  INC-ntINC.INCMC.3770"     << endl;
    cout << "   ->  INC-ntINC.INCMC.3770.2021"<< endl;
    THINLINE();
    cout << " ->  INC-ntINC.INCMC.3650"     << endl;
    cout << "   ->  INC-ntINC.INCMC.3650.2022"<< endl;
    SPACEin();
    //======== EXC Control Samples  ======   gpp  gkk  gPP
    cout << "Control Samples  (Exclusive) " << endl;
    cout << "For Sets:  gpp , gkk , gPP " << endl;
    THINLINE();
    cout << " ->  EXC-ntINC.SIGMC.3686"     << endl;
    cout << "   ->  EXC-ntGEN.SIGMC.3686"     << endl;
    THINLINE();
    cout << " ->  EXC-ntINC.INCMC.3686"     << endl;
    cout << "   ->  EXC-ntINC.INCMC.3686.2012"<< endl;
    THINLINE();
    cout << " ->  EXC-ntINC.DATA.3686"     << endl;
    cout << "   ->  EXC-ntINC.DATA.3686.2012"<< endl;
    SPACEin();
    //====================================
    //===== Old INC Control Samples  =====   gpp  gPP  eepp  mmpp
    cout << "Control Samples  (Inclusive) " << endl;
    cout << "For Sets:  gpp , gPP , eepp , mmpp" << endl;
    THINLINE();
    cout << " ->  INC-ntINC.SIGMC.3686"     << endl;
    cout << "   ->  INC-ntGEN.SIGMC.3686"     << endl;
    THINLINE();
    cout << " ->  INC-ntINC.INCMC.3686"     << endl;
    cout << "   ->  INC-ntINC.INCMC.3686.2012"<< endl;
    THINLINE();
    cout << " ->  INC-ntINC.DATA.3686"     << endl;
    cout << "   ->  INC-ntINC.DATA.3686.2012"<< endl;
    SPACEin();
  }
  //==========================================================================
  // General format should probably be "INC-ntINC.INCMC.3686.2021"  or "INC-ntINC.INCMC.3686" for full 3650"
  // For ntGEN files, note if using exclusively or inclusively reconstructed files.
  // ntGEN should have ntGEN or ntGEN to get correct root file
  //==========================================================================
  TString getDataSetFN(TString Set, TString FullDataSetLabel, bool moreskim = false, bool PrintCheck = false){
    vector<TString> FNvec; // Used for returning the single file or multiple files pushed into it.
    TString DataSet; // Reduced input label (for convienience) 
    TString TypePath;// General Path to directory of interest with the root file
    TString fn;      // output
    TString rootfile;// Root file in directory
    TString ModeName;// For differntiating root files/content inside
    TString SkimTag; // Use SKIM for typical base skim and smaller for futher skimed files.
    if(moreskim){ SkimTag = "smaller"; }
    else{ 
      if(FullDataSetLabel.Contains("INCMC.3770")){ SkimTag = "SKIM.?"; }
      else{ SkimTag = "SKIM"; }
    }
    if(PrintCheck) cout << SkimTag << endl;
    //==========================================================================
    // Setting up the root file name that 'SHOULD' be in side the directory function below.
    if(Set=="eepp"||Set=="mmpp"||Set=="gpp"||Set=="gPP"||Set=="gkk"||Set=="etgpp"){ ModeName = "Control";}
    if(Set=="gep"||Set=="gepp"){ ModeName = "TAUPI";}
    if(Set=="gtm"){ ModeName = "MUTAU";}
    if(Set=="get"){ ModeName = "ETAU";}
    if(FullDataSetLabel.Contains("EXC-ntGEN")){ rootfile = "SKIM.ntGEN.root";  } 
    if(FullDataSetLabel.Contains("INC-ntGEN")){ rootfile = "SKIM.ntGEN_"+ModeName+"_MODECODE.root"; }
    if(FullDataSetLabel.Contains("ntINC")    ){ rootfile = "SKIM.ntINC_"+ModeName+"_MODECODE.root"; }
    if(FullDataSetLabel.Contains("ntEXC")    ){ rootfile = "SKIM.ntEXC_"+ModeName+"_MODECODE.root"; }
    DataSet = CutStringFirst(FullDataSetLabel,".")[1]; // ntINC.INCMC.3686 -> INCMC.3686 i think
    if(PrintCheck) cout << ModeName << endl;
    if(PrintCheck) cout << DataSet << endl;
    if(PrintCheck) cout << rootfile << endl;
    //==========================================================================
    // Main Project SIGMC, INCMC and DATA
    //==========================================================================
    if(FullDataSetLabel.Contains("INC-nt")&&(Set=="gtm"||Set=="get"||Set=="gep"||Set=="gepp")){  // Main Directory for this set of data sets
      TypePath = "/home/johnguti/DATA-D_drive/MainProject/LFV2S";
      if(DataSet.Contains("SIGMC.3686")){
        if(Set!="gtm"){  FNvec.push_back(TypePath+"/SIGMC/SIGMC.12.e/"+ SkimTag+"/"+rootfile);  }
        if(Set=="gtm"){  FNvec.push_back(TypePath+"/SIGMC/SIGMC.12.mu/"+SkimTag+"/"+rootfile);  }
      }
      else if(DataSet.Contains("INCMC.3686")){
        if(DataSet=="INCMC.3686"||DataSet=="INCMC.3686.2009") FNvec.push_back(TypePath+"/INCMC/INCMC.3686/INCMC.3686.2009/"+SkimTag+"/"+rootfile); 
        if(DataSet=="INCMC.3686"||DataSet=="INCMC.3686.2012") FNvec.push_back(TypePath+"/INCMC/INCMC.3686/INCMC.3686.2012/"+SkimTag+"/"+rootfile); 
        if(DataSet=="INCMC.3686"||DataSet=="INCMC.3686.2021") FNvec.push_back(TypePath+"/INCMC/INCMC.3686/INCMC.3686.2021/"+SkimTag+"/"+rootfile); 
      }
      else if(DataSet.Contains("INCMC.3650")){ // Only have 3650.2022 , Other is probably not needed
        //if(DataSet=="INCMC.3650"||DataSet=="INCMC.3650.2009") FNvec.push_back(TypePath+"/INCMC/INCMC.2009/"+SkimTag+"/"+rootfile);  // Not gotten yet. Probably not needed
        if(DataSet=="INCMC.3650"||DataSet=="INCMC.3650.2022") FNvec.push_back(TypePath+"/INCMC/INCMC.3650/INCMC.3650.2022/SKIM/"+rootfile); 
      }
      else if(DataSet.Contains("INCMC.3770")){ // Only have 3770.2021 , Other is probably not needed
        //if(DataSet=="INCMC.3770"||DataSet=="INCMC.3770.2011") FNvec.push_back(TypePath+"/INCMC/INCMC.3770/INCMC.3770.2011/"+SkimTag+"/"+rootfile);
        if(DataSet=="INCMC.3770"||DataSet=="INCMC.3770.2021") FNvec.push_back(TypePath+"/INCMC/INCMC.3770/INCMC.3770.2021/"+SkimTag+"/"+rootfile); 
      }
      else if(DataSet.Contains("DATA.3650")){  // Only have 3650.2022 , Other is probably not needed
        //if(DataSet=="DATA.3650"||DataSet=="DATA.3650.2009") FNvec.push_back(TypePath+"/CONT/CONT.2009/"+SkimTag+"/"+rootfile);  // Not gotten yet. Probably not needed
        if(DataSet=="DATA.3650"||DataSet=="DATA.3650.2022") FNvec.push_back(TypePath+"/CONT/CONT.3650/CONT.3650.2022/SKIM/"+rootfile); 
      }
      else if(DataSet.Contains("DATA.3770")){
        if(DataSet=="DATA.3770"||DataSet=="DATA.3770.2011") FNvec.push_back(TypePath+"/CONT/CONT.3770/CONT.3770.11/"+SkimTag+"/"+rootfile); 
        if(DataSet=="DATA.3770"||DataSet=="DATA.3770.2021") FNvec.push_back(TypePath+"/CONT/CONT.3770/CONT.3770.21/"+SkimTag+"/"+rootfile); 
      }
      //==========================================================================
      if(PrintCheck) cout << FNvec[0] << endl;
      return CombineStringVec(FNvec,",");
    }
    //==========================================================================
    // Control SIGMC, INCMC and DATA (Inclusive and Exclusive checks)
    //==========================================================================
    if(FullDataSetLabel.Contains("EXC-nt")&&(Set=="gpp"||Set=="gPP"||Set=="gkk")){  // Main Directory for this group of data sets
      TypePath = "/home/johnguti/DATA-D_drive/MainProject/LFV2S/control";
      //==========================================================================
      if(DataSet.Contains("SIGMC.3686")){
        FNvec.push_back(TypePath+"/SIGMC.1/SKIM/"+rootfile); 
      }
      else if(DataSet.Contains("INCMC.3686")){
        if(DataSet=="INCMC.3686"||DataSet=="INCMC.3686.2012") FNvec.push_back(TypePath+"/EXCsample/INCMC.3686.12/SKIM/"+rootfile); 
      }
      else if(DataSet.Contains("INCMC.3650")){ // Only have 3650.2022 , Other is probably not needed
        if(DataSet=="INCMC.3650"||DataSet=="INCMC.3650.2022") FNvec.push_back(TypePath+"/EXCsample/INCMC.3650.22/SKIM/"+rootfile); 
      }
      else if(DataSet.Contains("DATA.3686")){  // Only have 3686.2022 , Other is probably not needed
        if(DataSet=="DATA.3686"||DataSet=="DATA.3686.2012")   FNvec.push_back(TypePath+"/EXCsample/DATA.3686.12/SKIM/"+rootfile); 
      }
      //==========================================================================
      if(PrintCheck) cout << FNvec[0] << endl;
      return CombineStringVec(FNvec,",");
    }  
    //==========================================================================
    if(FullDataSetLabel.Contains("INC-nt")&&(Set=="gpp"||Set=="gPP"||Set=="eepp"||Set=="mmpp")){  // Main Directory for this group of data sets
      TypePath = "/home/johnguti/DATA-D_drive/MainProject/Old_LFV2S/control";
      //==========================================================================
      if(DataSet.Contains("SIGMC.3686")){     
        FNvec.push_back(TypePath+"/SIGMC/SKIM/"+rootfile);   
      }
      else if(DataSet.Contains("INCMC.3686")){
        if(DataSet=="INCMC.3686"||DataSet=="INCMC.3686.2012") FNvec.push_back(TypePath+"/INCMC.3686.12/SKIM/"+rootfile); 
      }
      else if(DataSet.Contains("DATA.3686")){  // Only have 3686.2022 , Other is probably not needed
        if(DataSet=="DATA.3686"||DataSet=="DATA.3686.2012")   FNvec.push_back(TypePath+"/DATA.3686.12/SKIM/"+rootfile); 
      }
      //==========================================================================
      return CombineStringVec(FNvec,",");
    }
    //==========================================================================
    return "shit..."; // If all else fails, this pops out...
  }
  //==========================================================================
  // For Getting the N-Tuple which contains the relevant physics info from the root file name
  // Keep simple by using consistent N-tuple names across the data sets of the project
  TString getNTfromFN(TString FN){
    TString nt;
    TString dummy;
    if(FN.Contains("/SKIM.")){
      dummy = FSString::parseTString(FN,".root")[0];
      if(dummy.Contains("/SKIM.")){
        dummy = FSString::parseTString(dummy,"/SKIM.")[1];
        if(dummy.Contains("/SKIM.")){
          dummy = FSString::parseTString(dummy,"/SKIM.")[1];
        }
      }
    }
    return dummy;
  }
  //================================================================================================
  //================================================================================================
//map<TString, list<TString>> HistoInfo(TString Set, vector<TString> Vec_FullDataSetLabels, vector<pair<TString,TString>> Vec_NamesAndCuts){
  //map<TString, list<TString>> HistoInfoMap;


  //HistoInfoMap.insert( pair<TString,vector<double>>(FitNames[i],FinFitNums)  );
  //FinFitNums.clear();
  //return 
//}

//================================================================================================
//================================================================================================
//================================================================================================
class BAHDataSets{
private:
  bool m_CheckPrint;  // Set to True to print out ALOT. Useful for debugging or checking inputs.
  bool m_FurtherSkimmed;  // To differentiate file directories (if there is a more-skimmed version)
  TString m_Set;
  TString m_ReferenceDataSet;  // Can use this to fetch the Scaling for a specific DataSet TString 
  vector<TString> m_DataSetKeys; // Need This to keep track of DataSets. Just "DataSetLabel_Tag" so seperated but underscore.
  map<TString, vector<TString>> m_DataSetMap;
  //  OutputMap[Key] -> vector<TString>
  //---------------------------------------------
public:
  // ***************************************************************
  // ***************************************************************
  //---------------------------------------------
  // Finally at the DataSet Constructors
  //---------------------------------------------
  // Constructor with all components so the user can use if info pre-organized 
  /*
  BAHDataSets(TString Set, vector<vector<TString>> DataSetLabels_tag_IS_LegendLabel_Cuts, TString ReferenceDataSetLabel="", bool FurtherSkimmed = false, bool checkprint = false){
    m_Set = Set;
    m_ReferenceDataSet = ReferenceDataSetLabel;
    m_FurtherSkimmed = FurtherSkimmed;
    m_CheckPrint = checkprint;
    // Looping over 'matrix' to fill up
    for(int i = 0; i < DataSetLabels_tag_IS_LegendLabel_Cuts.size(); i++){  // Saving entire vector so I can confirm the DataSetLabel is the same as the Key used. [Possible I fuck up later...]
      // Looping over DataSetLabels so I can use them to retrieve the main issues. 
      m_DataSetKeys.push_back(DataSetLabels_tag_IS_LegendLabel_Cuts[i][0]+"_"+DataSetLabels_tag_IS_LegendLabel_Cuts[i][1]); // Can use vector to loop over the map (as a key) and get the parts.
      // the DataSetMap now uses DataSetLabels_tag as the KEYS. Holds the DataSetLabel, tag, IS, legend label and cuts per single DataSetLabels_tag
      m_DataSetMap.insert( pair<TString,vector<TString>>(DataSetLabels_tag_IS_LegendLabel_Cuts[i][0]+"_"+DataSetLabels_tag_IS_LegendLabel_Cuts[i][1],DataSetLabels_tag_IS_LegendLabel_Cuts[i])  ); 
    }
  }*/
  //---------------------------------------------
  // Constructor with none of the DataSets/components setup but its initiated. Can add parts later.
  BAHDataSets(TString Set, TString ReferenceDataSetLabel="", bool FurtherSkimmed = false, bool checkprint=false){
    m_Set = Set;
    m_ReferenceDataSet = ReferenceDataSetLabel;
    m_FurtherSkimmed = FurtherSkimmed;
    m_CheckPrint = checkprint;
  }
  // ***************************************************************
  // ***************************************************************
  //---------------------------------------------
  // Additional Class Functions to add/remove and retrieve info from the Object
  //---------------------------------------------
  // Because the MC Sets can very different based of of Intermediate states and number of events generated, 
  // have additional scaling input to compensate. CUTS are ALMOST ALWAYS MC based. Maybe can use to get sidbands or something...
  //---------------------------------------------
  void addDataSet(TString DataSetLabels, TString tag, TString IS, TString LegendLabel, TString Cuts){
    vector<TString> dummyVec = {FSString::removeWhiteSpace(DataSetLabels),FSString::removeWhiteSpace(tag),FSString::removeWhiteSpace(IS),LegendLabel,Cuts};
    TString Key = FSString::removeWhiteSpace(DataSetLabels+"_"+tag);
    if((LegendLabel.Contains("emove")||LegendLabel.Contains("kip"))){
      cout << " NOT ADDING [Skip/Remove] "+DataSetLabels+"_"+tag << endl;
    }
    if(!(LegendLabel.Contains("emove")||LegendLabel.Contains("kip"))){
      m_DataSetKeys.push_back(Key);
      m_DataSetMap.insert( pair<TString,vector<TString>>(Key,dummyVec)  ); 
    }
    return;
  }
  //---------------------------------------------
  //void addMCModeDataSet(TString DataSetLabels, TString tag, TString LegendLabel, TString Cuts){
  //  vector<TString> dummyVec = {DataSetLabels,tag,tag,LegendLabel,Cuts};
  //  TString Key = DataSetLabels+"_"+tag;
  //  if((LegendLabel.Contains("emove")||LegendLabel.Contains("kip"))){
  //    cout << " NOT ADDING [Skip/Remove] "+DataSetLabels+"_"+tag << endl;
  //  }
  //  if(!(LegendLabel.Contains("emove")||LegendLabel.Contains("kip"))){
  //    m_DataSetKeys.push_back(Key);
  //    m_DataSetMap.insert( pair<TString,vector<TString>>(Key,dummyVec)  ); 
  //  }
  //}
  //---------------------------------------------
  void eraseDataSet(TString DataSetLabels, TString tag){
    if(m_DataSetMap.size()<1){ SPACEstr(" No Sets in Map, Skipping erasing! ");}
    //------------------------------------------------
      // Now removing the Map of that key  [OVERCOMPLICATED THIS, SIMPLE CORRECT ANSWER AT END]
      //for( int i ; i < m_DataSetMap.size() ; i++ ){
      //  if(m_DataSetKeys[i]==DataSetLabels+"_"+tag){
      //     // erasing key and the key-associated map
      //    cout << "----- erased Data Set : "+DataSetLabels+"_"+tag+" -----" << endl;
      //  }
      //}
    //------------------------------------------------
    // finding the position of the key in the key-vector and removing it
    //TString StringToRemove = DataSetLabels+"_"+tag;
    //auto it = find(m_DataSetKeys.begin(), m_DataSetKeys.end(),StringToRemove);
    //if (it != m_DataSetKeys.end()){ m_DataSetKeys.erase(it);}
    m_DataSetKeys = eraseElement(1,m_DataSetKeys,DataSetLabels+"_"+tag);  // Only removing first since it may cause issuse if I SOMEHOW have multiple
    m_DataSetMap.erase(DataSetLabels+"_"+tag);
    //cout << "----- Fuck... Did not find Data-Set in KeyVec : "+DataSetLabels+"_"+tag+" -----" << endl;
    return;
  }
  //---------------------------------------------
  // Can edit any part of the map (as well as the keys) used to store the information
  void editDataSetComponent(TString DataSetLabel, TString tag, TString ComponentType, TString replacement){
    if(ComponentType.Contains("DataSetLabel")){ 
      m_DataSetMap[DataSetLabel+"_"+tag][0] = FSString::removeWhiteSpace(replacement); 
      m_DataSetKeys = replaceElement(1,m_DataSetKeys,DataSetLabel+"_"+tag,replacement+"_"+tag)
    }
    if(ComponentType.Contains("tag")){          
      m_DataSetMap[DataSetLabel+"_"+tag][1] = FSString::removeWhiteSpace(replacement); 
      m_DataSetKeys = replaceElement(1,m_DataSetKeys,DataSetLabel+"_"+tag,DataSetLabel+"_"+replacement)
  
    }
    if(ComponentType.Contains("IS")){           m_DataSetMap[DataSetLabel+"_"+tag][2] = FSString::removeWhiteSpace(replacement); }
    if(ComponentType.Contains("egend")||ComponentType.Contains("ame")){ m_DataSetMap[DataSetLabel+"_"+tag][3] = replacement; }
    if(ComponentType.Contains("uts")){          m_DataSetMap[DataSetLabel+"_"+tag][4] = replacement; }
    cout << " Bad Component Input [or messed up somewhere else] " << endl;
    return;
  }
  //---------------------------------------------
  // Based on a tags used in the map, can redefine what the DataSetLabels are
  void setDSLfromTag(TString tag, TString newDataSetLabel){
    TString dummyDSLabel;
    TString dummyDSTag;
    for( int i=0 ; i < m_DataSetKeys.size() ; i++ ){
      dummyDSLabel = FSString:: parseTString(m_DataSetKeys,"_")[0];
      dummyDSTag = FSString:: parseTString(m_DataSetKeys,"_")[1];
      if(dummyDSTag==tag){
        editDataSetComponent(dummyDSLabel,tag,"DataSetLabel",newDataSetLabel);
      }
    }
  }
  //---------------------------------------------
  // Defining and using PresetName associations to get data-sets w/ their info immediately/consistently
  void getAnalysisPresets(TString PresetName, BAHDecays DecayInfo, BAHCuts CutInfo){
    TString Energy; // May need, idk...
    TString Year;   // May need, idk...
    TString ntType; 
    bool UsesData = false;
    // "3770check" , "3770checkEVTGEN" , "3770checkEVTGEN" , Can attach "More" to get specific backgrounds
    if(PresetTag.Contains("3770check")){
      DecayInfo.dumpGeneralMC();
      UsesData = true
      ntType ="INC";
      Energy ="3770";
      Year = "2021";
      //---------------------------------------------
      // Setting Up DecayInfo Parts
      if(PresetTag.Contains("EVTGEN")){  // NOT INCMC, but my own generated MC
        DecayInfo.addGeneralMCDecay("","3770 MC","tau+ tau-");    // IF USING, CHANGE FILE HELPER to be set to 3770 di-tau sample!!!!! 
      }
      else if(PresetTag.Contains("More")||PresetTag.Contains("MORE")){
        //---------------------------------------------
        // More complicated 3770 info via INCMC
        DecayInfo.addGeneralMCDecay("e^{+} e^{-} #rightarrow ","3770 INCMC","tau+ tau-");
        DecayInfo.addGeneralMCDecay("e^{+} e^{-} #rightarrow ","3770 INCMC","D0bar D0");
        DecayInfo.addGeneralMCDecay("e^{+} e^{-} #rightarrow ","3770 INCMC","e+ e- Ngamma");
        DecayInfo.addGeneralMCDecay("e^{+} e^{-} #rightarrow ","3770 INCMC","mu+ mu- Ngamma ");
      }
      else{
        //---------------------------------------------
        // Basic 3770check info via INCMC
        DecayInfo.addGeneralMCDecay("e^{+} e^{-} #rightarrow ","3770 INCMC","tau+ tau-");
      }
      //---------------------------------------------
      // Organizing CutInfo for "3770check"  [with any Variable Cuts]
      CutInfo.nullifyCut("Mass1",DecayInfo.getMass1Var());  //  Chi_c0, Chi_c1 or Chi_c2  cuts
      CutInfo.nullifyCut("Mass2",DecayInfo.getMass2Var());  //  Tau cut
      //---------------------------------------------
    }
    //---------------------------------------------

    
    //---------------------------------------------
    // Done Organizing DataSetLabels and Tags, now using them
    vector<TString> MCModeCuts  = DecayInfo.getGeneralMCCuts();
    vector<TString> MCModeTags  = DecayInfo.getGeneralMCTags();
    vector<TString> MCModeLabels= DecayInfo.getGeneralMCLabels();
    //---------------------------------------------
    for( int i=0 ; i < DecayInfo.getGeneralMCCuts().size() ; i++ ){
      if(!(MCModeTags[i].Contains("INCMC"))){
        // To add Specific SIGMC to Histogram 
        DataInfo.addDataSet(ntType"-ntINC.SIGMC."+Energy+"."+Year,MCModeTags[i],MCModeTags[i],MCModeLabels[i],MCModeCuts[i]);
      } // To add Specific INCMC to Histogram
      else{DataInfo.addDataSet(ntType"-ntINC.INCMC."+Energy+"."+Year,MCModeTags[i],MCModeTags[i],MCModeLabels[i],MCModeCuts[i]);}
    }
    //--------------------------------------------------------------
    // To Carve out the Modes used for plotting above from the INCMC sets
    // Needa make it more nuanced eventually
    TString MCModeCarveOut = "(!("+CutsfromCutVec(MCModeCuts,"||")+"))";
    DataInfo.addDataSet(ntType"-ntINC.INCMC."+Energy+"."+Year,Energy+"INCMC","",MCModeCarveOut);
    //--------------------------------------------------------------
    // If the Preset UsesData, can setup here.
    if(UsesData){
      DataInfo.addDataSet(ntType"-ntINC.DATA."+Energy+"."+Year,"3770DATA","",noCuts);
    }


  }
  //---------------------------------------------
  TString getDataSetCut(TString DataSetLabel, TString tag){  
    return m_DataSetMap[DataSetLabel+"_"+tag][4];
  }
  //--------------------------------------------- 
  double getScale(TString DataSetLabel, TString tag = "", double AdditionalScaling = 1.0){  
    if(DataSetLabel.Contains("Data")||DataSetLabel.Contains("DATA")){
      return  getDataSetScale(DataSetLabel,m_ReferenceDataSet,m_Set,"",m_CheckPrint)*AdditionalScaling;
    }
    return  getDataSetScale(DataSetLabel,m_ReferenceDataSet,m_Set,tag,m_CheckPrint)*AdditionalScaling; 
  }
  //---------------------------------------------
  TString getFN(TString DataSetLabel){  
    return getDataSetFN(m_Set,DataSetLabel,m_FurtherSkimmed);
  }
  //---------------------------------------------
  TString getNT(TString DataSetLabel){  
    return getNTfromFN(getDataSetFN(m_Set,DataSetLabel,m_FurtherSkimmed));
  }
  //--------------------------------------------- 
  int numberDataSets(){
    if(m_DataSetMap.size()==m_DataSetKeys.size()) return m_DataSetKeys.size();
    cout << "[ m_DataSetMap.size() , m_DataSetKeys.size() ]   ->   [ "+FSString::int2TString(m_DataSetMap.size())+" , "+FSString::int2TString(m_DataSetKeys.size())+" ]" << endl;
    cout << " Fuck... they are not equal so returning  m_DataSetMap.size()" << endl;
    return m_DataSetMap.size();
  }
  //---------------------------------------------
  // ***************************************************************
  // ***************************************************************
  //---------------------------------------------
  // Prints out ALL useable DataSet currently setup to use on this computer/setup
  void PrintUseableDataSets(){ return printDataSets(); }
  //---------------------------------------------
  // Nice print function for checking the values used int scaling and what is for a specific DataSet
  void PrintDataSetInfo(TString DataSetLabel, TString tag = ""){ 
    vector<TString> dummyVec = m_DataSetMap[DataSetLabel+"_"+tag];
    THINLINE();
    cout << "------   FN :   ------" << endl;
    cout << getFN(DataSetLabel) << endl;
    cout << "------   NT :  " << getNT(DataSetLabel) << endl;
    cout << "---- INFO IN MAP -----" << endl;
    cout << "   DataSetLabel  = " << dummyVec[0] << endl;
    cout << "   tag           = " << dummyVec[1] << endl;
    cout << "   IS            = " << dummyVec[2] << endl;
    cout << "   LegendLabel   = " << dummyVec[3] << endl;
    cout << "   Cuts          = " << dummyVec[4] << endl;
    THINLINE();
    printDataInfo(DataSetLabel,m_Set,dummyVec[2]);  
    dummyVec.clear();
    return;
  }
  //---------------------------------------------
  // Prints out the info from PrintDataSetInfo for every DataSet in the Object.
  void PrintCurrentDataSets(){
    vector<TString> dummyVec;
    if(m_DataSetKeys.size()==0){ cout << "No Data Sets Currently" << endl; return;}
    for( int i=0 ; i < m_DataSetKeys.size() ; i++ ){
      SPACEin();
      cout <<"Input Key-PairVec["+FSString::int2TString(i)+"] :  ( DataSetLabel_Tag ) ->  ( "+m_DataSetKeys[i]+" )" << endl;
      dummyVec = m_DataSetMap[m_DataSetKeys[i]];
      PrintDataSetInfo(dummyVec[0],dummyVec[1]);
      SPACEin();
      dummyVec.clear();
    }
    return;
  }
};






void CHECKDataSets(TString Set){  
  // creating object of class for decay mode
  BAHDecays DecayInfo(Set);
  // creating object of class for Data Sets
  //                 Set, reference(forscaling),MoreSkimmedFN?,print?);
  BAHDataSets DataInfo(Set,"INC-ntINC.INCMC.3686",false,true);
  DecayInfo.addGeneralMCDecay("e^{+} e^{-} #rightarrow ","3770 INCMC","tau+ tau-");
  vector<TString> MCModeCuts  = DecayInfo.getGeneralMCCuts();
  vector<TString> MCModeTags  = DecayInfo.getGeneralMCTags();
  vector<TString> MCModeLabels= DecayInfo.getGeneralMCLabels();
  //--------------------------------------------------------------
  for( int i=0 ; i < DecayInfo.getGeneralMCCuts().size() ; i++ ){
    DataInfo.addDataSet("INC-ntINC.SIGMC.3686",MCModeTags[i],MCModeTags[i],MCModeLabels[i],MCModeCuts[i]);
  }
  //--------------------------------------------------------------
  int InitialModes = DataInfo.numberDataSets();
  //DataInfo.addDataSet("INC-ntINC.SIGMC.3686","3686.INCMC","tau+ tau-","3686 Inclusive MC",noCut);
  //--------------------------------------------------------------
  DataInfo.PrintCurrentDataSets();
  //--------------------------------------------------------------
  cout << InitialModes << endl;
  cout << DataInfo.numberDataSets() << endl;
}
//=========================================================================================
//=========================================================================================
#endif