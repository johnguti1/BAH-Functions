#if !defined(DRAWRESOUCES_H)
#define DRAWRESOUCES_H

 #include "BAHUtilities.h"
 #include "BAHStrings.h"
 #include "ScalingHelper.h"

  double EPSILON = .000001; 
  double arrow1Size = 0.016;
  double arrow2Size = 1.0;
  double arrow2TipDisplacement = 2.0;
//=======================================================================================================
//=======================================================================================================
// PERSONAL COLORS FOR MAKING HISTOGRAMS:
//=======================================================================================================
// Can get RGB/hexcolor on https://coolors.co/    or     https://color-register.org/color/
//    or even the maybe best      http://medialab.github.io/iwanthue/
  Int_t kkTeaRose       = TColor::GetColor(206,181,183);  
  Int_t kkHonoluluBlue  = TColor::GetColor( 14,121,178);  
  Int_t kkCarrotOrange  = TColor::GetColor(243,146, 55);  
  Int_t kkTiffanyBlue   = TColor::GetColor(154,213,202);  
  Int_t kkRoseRed       = TColor::GetColor(191, 19, 99);  
  Int_t kkSpaceCadet    = TColor::GetColor( 43, 43, 66);  // Near black
  Int_t kkLightCoral    = TColor::GetColor(230,149,151);  
  Int_t kkChiliRed      = TColor::GetColor("#D64933"); 
  Int_t kkDarkSlateGrey = TColor::GetColor("#1C5253");  
  Int_t kkJasmine       = TColor::GetColor("#FFEE88");  // Light Gold-Yellow
  Int_t kkRust          = TColor::GetColor("#BC3908");  
  Int_t kkMint          = TColor::GetColor("#00CC99");  // or new mint #69C9AC
  Int_t kkWintergreen   = TColor::GetColor("#20F986");  
  Int_t kkSalmon        = TColor::GetColor("#FA8072");  
  Int_t kkCheese        = TColor::GetColor("#ffa600");  
  Int_t kkUmber         = TColor::GetColor("#685044"); 
  Int_t kkMelon         = TColor::GetColor("#E9AFA3"); 
  Int_t kkZomp          = TColor::GetColor("#519E8A"); // Dark Mint/Greenish
  Int_t kkSage          = TColor::GetColor("#D6CA98"); // Green
  //----------------
  Int_t kkCoral         = TColor::GetColor("#FF8552"); 
  Int_t kkMyrtleGreen   = TColor::GetColor("#297373"); 
  Int_t kkLemon         = TColor::GetColor("#FBFB23"); 
  Int_t kkSkyMagenta    = TColor::GetColor("#C45BAA"); 
  Int_t kkRobinBlueEgg  = TColor::GetColor("#26CCCF"); 
  //----------------
  Int_t kkEggPlant       = TColor::GetColor("#734B5E"); 
  //----------------
  Int_t kkJimiPurple    = TColor::GetColor("#665191");
  Int_t kkDarkBlue      = TColor::GetColor("#003f5c");
  //----------------
  Int_t kkFaluRed       = TColor::GetColor("#7B2D26");
  Int_t kkHotPink       = TColor::GetColor("#FF5CB3");
  Int_t kkResedaGreen   = TColor::GetColor("#6E9075");
  Int_t kkPersianRed    = TColor::GetColor("#BB443A");
  Int_t kkGamboge       = TColor::GetColor("#EFA00B"); // Gold/Yellow  #9F7E41
  Int_t kkDarkGoldenRod = TColor::GetColor("#9F7E41"); // Dark Gold
  Int_t kkUltraViolet   = TColor::GetColor("#5E6097"); // Dark Pale Purple
//===============================================
// Can find hexcolor Palletes on https://www.learnui.design/tools/data-color-picker.html#palette
vector<pair<int,TString>> getColorVec(int pallete){
  vector<pair<int,TString>> outVec;
  if(pallete==1){
    outVec.push_back(make_pair(kkDarkSlateGrey,"kkDarkSlateGrey"));  
    outVec.push_back(make_pair(kkMyrtleGreen,"kkMyrtleGreen"));
    outVec.push_back(make_pair(kkMelon,"kkMelon"));
    outVec.push_back(make_pair(kkEggPlant,"kkEggPlant"));
    outVec.push_back(make_pair(kkCheese,"kkCheese"));  
    outVec.push_back(make_pair(kkRoseRed,"kkRoseRed"));  
    outVec.push_back(make_pair(kkTiffanyBlue,"kkTiffanyBlue"));  
    outVec.push_back(make_pair(kkCarrotOrange,"kkCarrotOrange"));  
    outVec.push_back(make_pair(kkUmber,"kkUmber"));  
    outVec.push_back(make_pair(kkLightCoral,"kkLightCoral"));  
    outVec.push_back(make_pair(kkHonoluluBlue,"kkHonoluluBlue"));  
    outVec.push_back(make_pair(kkSpaceCadet,"kkSpaceCadet"));  
    outVec.push_back(make_pair(kkChiliRed,"kkChiliRed"));  
    outVec.push_back(make_pair(kkTeaRose,"kkTeaRose"));  
    outVec.push_back(make_pair(kkWintergreen,"kkWintergreen"));  
  }
  //===============================================
  else{
    outVec.push_back(make_pair(TColor::GetColor("#665191"),"Jimi-Purple"));  // Jimi-Purple
    outVec.push_back(make_pair(TColor::GetColor("#ffa600"),"Cheese"));  // Cheese
    outVec.push_back(make_pair(TColor::GetColor("#a05195"),"Lighter Jimi-Purple"));  // Lighter Jimi-Purple
    outVec.push_back(make_pair(TColor::GetColor("#d45087"),"Pastel red-pink"));  // Pastel red-pink
    outVec.push_back(make_pair(TColor::GetColor("#ff7c43"),"Lil-bit Darker Orange"));  // Lil-bit Darker Orange
    outVec.push_back(make_pair(TColor::GetColor("#f95d6a"),"Darker Reddish Salmon"));  // Darker Reddish Salmon
    outVec.push_back(make_pair(TColor::GetColor("#003f5c"),"Dark Blue "));  // Dark Blue 
  }
  return outVec;
}
//=======================================================================================================
// USEFUL MACROS FOR MAKING HISTOGRAMS:
//=======================================================================================================
//=======================================================================================================
  // drawTLineUpper is useful for drawing upperbound cut line in 1D histograms
void drawTLineUpper(int kcolor, double xmax, double ymax, double scale, bool mid = true ){
  double ymid;
  if(!mid){ ymid= ymax/2+0.3; }
  if(mid){ ymid= ymax/2; }
  TArrow *UpperA = new TArrow(xmax-1.3*scale,ymid,xmax,ymid,arrow1Size*1.1,"<|");// point to the left
  UpperA->SetLineWidth(2);
  UpperA->SetLineColor(kcolor);
  UpperA->SetFillColor(kcolor);
  UpperA->Draw();
  TLine *Upper= new TLine(xmax,0.0,xmax,ymax);
  Upper->SetLineWidth(3);
  Upper->SetLineStyle(2);
  Upper->SetLineColor(kcolor);
  Upper->Draw("same");
  return;
}
  // drawTLineLower is useful for drawing lowerbound cut line in 1D histograms
void drawTLineLower(int kcolor, double xmin, double ymax, double scale, bool mid = true ){
  double ymid;
  if(!mid){ ymid= ymax/2-0.3; }
  if(mid){ ymid= ymax/2; }
  TArrow *LowerA = new TArrow(xmin,ymid,xmin+1.3*scale,ymid,arrow1Size,"|>");// point to the right
  LowerA->SetLineWidth(2);
  LowerA->SetLineColor(kcolor);
  LowerA->SetFillColor(kcolor);
  LowerA->Draw();
  TLine *Lower = new TLine(xmin,0.0,xmin,ymax);
  Lower->SetLineWidth(3);
  Lower->SetLineStyle(2);
  Lower->SetLineColor(kcolor);
  Lower->Draw("same");
  return;
}
  // drawTLineX is generally draws a red line along input x-value [for 2D]
  // Can't assume bottom is zero since 2D-plot is special.
void drawTLineX( double xval, double ymin, double ymax, bool left, double scale){
  double ymid = (ymax+ymin)/2;
  double arrowtip;  
  if(left){ arrowtip = xval + arrow2TipDisplacement*scale; }// left-hand cut so point to the right (adding)
  if(!left){arrowtip = xval - arrow2TipDisplacement*scale; }// right-hand cut so point to the left (subtracting)
  TArrow *Arrow = new TArrow(xval,ymid,arrowtip,ymid,arrow2Size*scale,"|>");
  Arrow->SetLineWidth(2);
  Arrow->SetLineColor(kRed);
  Arrow->SetFillColor(kRed);
  Arrow->Draw();
  TLine *XLine = new TLine(xval,ymin,xval,ymax);
  XLine->SetLineWidth(3);
  XLine->SetLineStyle(2);
  XLine->SetLineColor(kRed);
  XLine->Draw("same");
  return;
}
  // drawTLineY is generally draws a red line along input y-value [for 2D]
  // Can't assume bottom is zero since 2D-plot is special.
void drawTLineY(double yval, double xmin, double xmax, bool left, double scale){
  double xmid = (xmax+xmin)/2;
  double arrowtip;  
  if(left){ arrowtip = yval + arrow2TipDisplacement*scale; }// left-hand cut so point to the top (adding)
  if(!left){arrowtip = yval - arrow2TipDisplacement*scale; }// right-hand cut so point to the bottom (subtracting)
  TArrow *Arrow = new TArrow(xmid,yval,xmid,arrowtip,arrow2Size*scale,"|>");
  Arrow->SetLineWidth(2);
  Arrow->SetLineColor(kRed);
  Arrow->SetFillColor(kRed);
  Arrow->Draw();
  TLine *YLine = new TLine(xmin,yval,xmax,yval);
  YLine->SetLineWidth(3);
  YLine->SetLineStyle(2);
  YLine->SetLineColor(kRed);
  YLine->Draw("same");
  return;
}
  // drawCutLines Gets "pairs" from vector and draws in colors corrsponding to a cut (left,right)
void drawCutLines(int kcolor, vector<pair<TString,TString>> cutpairs, double Ymax, double Xscale){
  vector<double> dummyInts = VPairToVDoub(cutpairs);
  double dummy;
  bool mid;
  for( int i=0; i <dummyInts.size(); i++ ){
    dummy = dummyInts[i];
    mid = true;
    if(i>0){
      mid = true;
      if(( i < dummyInts.size()-1)&&(dummyInts[i]==dummyInts[i+1])){
        dummy = dummy;//-0.001;
        mid = false;
      }
      if((i>0)&&(dummyInts[i]==dummyInts[i-1])){
        dummy = dummy;//+0.001;
        mid = false;
      }
    }
    if(i%2==0){
      if( fabs(dummyInts[i]) > EPSILON ){drawTLineLower(kcolor,dummy,Ymax,Xscale,mid);}
    }
    else{
      if( fabs(dummyInts[i]) > EPSILON ){drawTLineUpper(kcolor,dummy,Ymax,Xscale,mid);}
    }
  }
}
// drawXLines Gets "pairs" from vector and draws them all red along x-values in pairs
void drawXLines(vector<pair<TString,TString>> cutpairs, double Ymin, double Ymax, double Xscale){
  vector<double> dummyInts = VPairToVDoub(cutpairs);
  cout << "X-line:  " << dummyInts[0] << " , " << dummyInts[1] << endl;
  bool left;
  double dummy;
  for( int i=0; i <dummyInts.size(); i++ ){
    if(i%2 == 0){ left = true; }
    if(i%2 != 0){ left = false; }
    dummy = dummyInts[i];
    if(i>0){
      if(dummyInts[i]>dummyInts[i-1]){
        dummy = dummy + 0.001;
      }
    }
    if( fabs(dummyInts[i]) > EPSILON ){drawTLineX(dummy,Ymin,Ymax,left,Xscale); SPACEstr("Drawing X Line");}
  }
}
  // drawYLines Gets "pairs" from vector and draws them all red along y-values in pairs
void drawYLines(vector<pair<TString,TString>> cutpairs, double Xmin, double Xmax, double Yscale){
  vector<double> dummyInts = VPairToVDoub(cutpairs);
  cout << "Y-line:  " << dummyInts[0] << " , " << dummyInts[1] << endl;
  bool left;
  double dummy;
  for( int i=0; i <dummyInts.size(); i++ ){
    if(i%2 == 0){ left = true; }
    if(i%2 != 0){ left = false; }
    dummy = dummyInts[i];
    if(i>0){
      if(dummyInts[i]>dummyInts[i-1]){
        dummy = dummy + 0.001;
      }
    }
    if( fabs(dummyInts[i]) > EPSILON ){drawTLineY(dummy,Xmin,Xmax,left,Yscale); SPACEstr("Drawing Y Line");}
  }
}
  // Just organized the units to use on x-axis label.
TString getUnitsX( TString UnitsX ){
  TString UnitsX_t;
  if(UnitsX == "" || UnitsX == " " || UnitsX == "NO"){
    UnitsX_t="";
  }
  else{ UnitsX_t = " ["+UnitsX+"]"; }
  return UnitsX_t;
}
  // Uses the x-axis bins and unit label and properly outputs y-axis label  
TString getUnitsY( TString Bounds, TString UnitsX ){
  double binsize = FSString::parseBoundsBinSizeX(Bounds);
  TString YvalS;
  TString UnitsY;
  if((UnitsX=="")||(UnitsX==" ")){
    UnitsY = "/Bin";
    return UnitsY;
  }
  if((UnitsX=="NO")){
    UnitsY = "";
    return UnitsY;
  }
  if(UnitsX == "GeV"){ 
    YvalS = FSString::double2TString(binsize*1000);
    UnitsY = "/"+YvalS+"MeV"; 
  }
  if(UnitsX != "GeV"){ 
    YvalS = FSString::double2TString(binsize);
    UnitsY = "/"+YvalS+UnitsX; 
  }
  return UnitsY;
}
//================================================================================================
// For color coordination amoung histograms, Can have some j++ over the MC Decay Modes for different colored backgrounds
int getColorIS( TString IScutString, int colorIterator, int pallete = 1, bool printcheck = false){
  int colorOut;
  //-----------------------------------------
  // for chi_cJs
  bool LFVsignal;
  if(IScutString.Contains("=10441")&&(!IScutString.Contains("!"))&&(IScutString.Contains("Signal"))){ return kOrange-3; }  // chi_c0 
  if(IScutString.Contains("=20443")&&(!IScutString.Contains("!"))&&(IScutString.Contains("Signal"))){ return kGreen+1;  }  // chi_c1 
  if(IScutString.Contains("=445"  )&&(!IScutString.Contains("!"))&&(IScutString.Contains("Signal"))){ return kMagenta-3;}  // chi_c2 
  //-----------------------------------------
  // for J/psi
  if(IScutString.Contains("=443")&&IScutString.Contains("MCDecayCode2==11000)")&&(IScutString.Contains("Signal"))){  return kViolet-3;}  // J/psi -> ee
  if(IScutString.Contains("=443")&&IScutString.Contains("MCDecayCode2==1100000)")&&(IScutString.Contains("Signal"))){return kViolet;  }  // J/psi -> mm
  //-----------------------------------------
  // for Random Specific Decays (!!!!!!!!!!!!!)
  if(IScutString.Contains("MCDecayCode1==1000110 && MCDecayCode2==1")&&(IScutString.Contains("Signal"))){  return kkCoral;}  // eta gamma pi+pi-
  //-----------------------------------------
  // for Tau Tau Decays
  //if((IScutString.Contains(BAHDecays::getMCDecayParts(ParticlesToIDs("tau+ tau-")))){  return kkMyrtleGreen;}  // tau+ tau-
  //-----------------------------------------
  // for INCMC omitting signal
  if(IScutString=="INC" ){    return kCyan; }  //INCMC back  
  if(IScutString=="INC2"){    return kkWintergreen; }  //INCMC back  
  //-----------------------------------------
  // for data with no MC cut;
  if(IScutString=="CONT"){   return kRed-7; }  //Continuum back  
  //-----------------------------------------
  colorOut = getColorVec(pallete)[colorIterator].first;
  if(printcheck){
    THINLINE();
    cout << "Color Int retrieved from vector:" << endl;
    cout << "[" << colorIterator << "]" << IScutString << " -> color output/Name = " << colorOut << " / "+getColorVec(pallete)[colorIterator].second<< endl; 
    THINLINE();
  }
  return colorOut;
}
//================================================================================================
                        //   TITLE,Set,var,cuts,xtitle,Ymax,Xscale
void drawControlLines(TString Tag, TString Set, TString var, TString cuts, TString xtitle, double Ymax, double Xscale, int Color = kRed ){
  //if(xtitle.Contains("-m_{")){drawTLineUpper(kRed,0.04,Ymax,Xscale);}
  //---------------------------------
  if(Set=="eepp"||Set=="mmpp"){
    if(var=="TkEPP1"&&Set=="eepp"){
      drawTLineLower(kRed,0.925,Ymax,Xscale);
      drawTLineUpper(kRed,1.04,Ymax,Xscale);
    }
    if(var=="Chi2DOF"){drawTLineUpper(kRed,10.0,Ymax,Xscale);}
    if(var.Contains("EMCEnergy")){drawTLineUpper(kRed,0.15,Ymax,Xscale);}
    if(var.Contains("EMCEnergy")){drawTLineUpper(kRed,0.2,Ymax,Xscale);}
    if((var.Contains("COSINE("))&&(var.Contains(";3)")||var.Contains(";4)"))){
      drawTLineUpper(kRed,0.9,Ymax,Xscale);
      //if(var.Contains("+];3)")){drawTLineUpper(kRed,0.09,Ymax,Xscale);}
      //if(var.Contains("+];3)")){drawTLineUpper(kRed,0.09,Ymax,Xscale);}
      //if(var.Contains("+];3)")){drawTLineUpper(kRed,0.09,Ymax,Xscale);}
    }
  }
  //---------------------------------
  if(Set=="gkk"){
    //if(var.Contains("EMCEnergy")){drawTLineUpper(kRed,0.2,Ymax,Xscale);}
    //---------------------------------
    if(var.Contains("RM()")){drawTLineUpper(kRed,0.2,Ymax,Xscale);}
    //---------------------------------
    if(!cuts.Contains("(MOMENTUM(2,3)<0.17)")){
      if(xtitle==RM_t(Set,"XcJ")){drawTLineLower(kRed,3.38,Ymax,Xscale);}
      if(xtitle==RM_t(Set,"XcJ")){drawTLineUpper(kRed,3.47,Ymax,Xscale);}
     }
    //---------------------------------
    if(!cuts.Contains("(0.19<MOMENTUM(2,3))")){
      if(xtitle==RM_t(Set,"XcJ")){drawTLineLower(kRed,3.54,Ymax,Xscale);}
      if(xtitle==RM_t(Set,"XcJ")){drawTLineUpper(kRed,3.59,Ymax,Xscale);}
    }
  }
  //---------------------------------
  if(Set=="gtm"||Set=="get"||Set=="gep"||Set=="gepp"){
    if(Tag.Contains("chi_{c0}")||Tag.Contains("chi_{c1}")||Tag.Contains("chi_{c2}")){
      //--------------------------------- 
      drawTLineLower(kRed,1.73,Ymax,Xscale);
      drawTLineUpper(kRed,1.87,Ymax,Xscale);
      //---------------------------------
      drawTLineLower(kBlue,1.67,Ymax,Xscale);
      drawTLineUpper(kBlue,1.93,Ymax,Xscale);
      //---------------------------------
    }
  }
  //---------------------------------
}


#endif