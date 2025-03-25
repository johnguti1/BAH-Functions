#if !defined(BAHUTILITIES_H)
#define BAHUTILITIES_H

#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <map>
#include<TString.h>

  // Global Shortcut Strings
  TString MOM = "MOMENTUM";
  // Basic non-cut [should be consistent with BAHCuts m_noCut]
  TString noCut="(7==7)";
  TString zS("0.0");  // zero TString
  
  TString Emass("0.0005");      // ENERGY IN GEV
  TString MUmass("0.1057");     // ENERGY IN GEV
  TString TAUmass("1.77686");   // ENERGY IN GEV
  TString PIcmass("0.13957");   
  TString PI0mass("0.13498");
  TString Kcmass("0.4936");
  TString Prmass("0.93827");

/*      Time Stuff from Josh for checking how long shit takes
auto startTime = std::chrono::high_resolution_clock::now();
auto endTime = std::chrono::high_resolution_clock::now();
auto elapsed = std::chrono::duration_cast<std::chrono::minutes>(endTime - startTime);
cout << endl << "The fit took " << elapsed.count() << " minutes." << endl;
*/


//==========================================================================
// Stolen From Ryan. Added some useful options that I personally like...
  // ********************************************************
  // MAKE A LATEX TABLE
  //   pass in a 2d array with tableContents[nrows][ncols]
  //    or pass in a 1d array with tableContents[ncols*nrows]
  //      that fills left to right, top to bottom
  // ********************************************************
void  LatexTable(int nrows, int ncols, TString* tableContents, TString filename, 
                  bool append=true, TString caption="", TString TableOptions="h", TString ArrayStretch = "1.1", TString captionSpacing="0.0cm",TString TableSpacing = "0.0cm"){
  filename = gSystem->ExpandPathName(FSString::TString2string(filename).c_str());
  std::ios_base::openmode mode = ios::out;
  if (append) mode = ios::app;
  ofstream outfile(FSString::TString2string(filename).c_str(),mode);
  outfile << "\\begin{table}["+TableOptions+"]" << endl;
  if (caption != ""){
    outfile << "\\caption{" << caption << "}" << endl;
    outfile << "\\vspace{"+captionSpacing+"}" << endl;
  }
  outfile << "\\renewcommand{\\arraystretch}{"+ArrayStretch+"}" << endl;
  outfile << "\\begin{center}" << endl;
  outfile << "\\begin{tabular}{|"; for (int k = 0; k < ncols; k++){ outfile << "c|"; } outfile << "}" << endl;
  outfile << "\\hline" << endl;
  int i = 0;
  for (int j = 0; j < nrows; j++){
    for (int k = 0; k < ncols; k++){
      outfile << tableContents[i++] << " ";
      if (k != ncols - 1) outfile << "& ";
    }
    outfile << "\\\\" << endl;
    outfile << "\\hline" << endl;
  }
  outfile << "\\end{tabular}" << endl;
  outfile << "\\end{center}" << endl;  
  if (caption != "") outfile << "\\end{table}" << endl;
  //outfile << endl;    //Dont want the extraspace, I can add that...
  outfile.close();
}  
//==========================================================================
// Delete TString input file name  (  .c_str() for string to char[] )
void deleteFile(TString DeletedFile){
  string fileStr = FSString::TString2string(DeletedFile);
  const char* filename = fileStr.c_str();
  //const char* filename = DeletedFile.c_str();
  remove(filename);
  return;
}
//==========================================================================
// Using TString input file name with ofstream defined output. 
// Not closed to enable further writing to file
void copyToFile(TString Input_File, std::ofstream& out_file){ 
    string InputFile = FSString::TString2string(Input_File);
    string line; 
    // For writing text file 
    // Creating ofstream & ifstream class object 
    ifstream ini_file{ 
        InputFile
    }; // This is the original file 
    if (ini_file && out_file) { 
  
        while (getline(ini_file, line)) { 
            out_file << line << "\n"; 
        } 
        cout << "Copy Finished from "+InputFile+" to output-file \n"; 
    } 
    else { 
        // Something went wrong 
        printf("Cannot read File"); 
    } 
  return;
}
//==========================================================================
// TAKEN FROM : https://www.geeksforgeeks.org/different-ways-to-print-elements-of-vector/
// C++ program to print the elements
// of the vector  like cout << vector << endl;
template <typename S>
ostream& operator<<(ostream& os,
                    const vector<S>& vector)
{
    // Printing all the elements
    // using <<
    for (auto element : vector) {
        os << element << " ";
    }
    return os;
}

//==========================================================================
// TAKEN FROM : https://www.geeksforgeeks.org/wildcard-pattern-matching/
// Function that checks if two given strings match.
// The fsecond string may contain wildcard characters.
// Use a more general one later on. 
bool StringPatternMatch( string s,  string p) {
  //dry run this sample case on paper , if unable to understand what soln does
  // p = "a*bc" s = "abcbc"
  int sIdx = 0, pIdx = 0, lastWildcardIdx = -1, sBacktrackIdx = -1, nextToWildcardIdx = -1;
  while (sIdx < s.size()) {
    if (pIdx < p.size() && (p[pIdx] == '?' || p[pIdx] == s[sIdx])) { 
      // chars match
      ++sIdx;
      ++pIdx;
    } else if (pIdx < p.size() && p[pIdx] == '*') { 
      // wildcard, so chars match - store index.
      lastWildcardIdx = pIdx;
      nextToWildcardIdx = ++pIdx;
      sBacktrackIdx = sIdx;
    //storing the pidx+1 as from there I want to match the remaining pattern 
    } else if (lastWildcardIdx == -1) { 
      // no match, and no wildcard has been found.
      return false;
    } else { 
      // backtrack - no match, but a previous wildcard was found.
      pIdx = nextToWildcardIdx;
      sIdx = ++sBacktrackIdx;
      //backtrack string from previousbacktrackidx + 1 index to see if then new pidx and sidx have same chars, if that is the case that means wildcard can absorb the chars in b/w and still further we can run the algo, if at later stage it fails we can backtrack
    }
  }
  for(int i = pIdx; i < p.size(); i++){
    if(p[i] != '*') return false;
  }
  return true;
  // true if every remaining char in p is wildcard
}
//==========================================================================
// DOES NOT WORK IF BOTH STRINGS HAVE WILD CARDS
bool TStrCheck(TString Str1, TString Str2){
  string s1 = FSString::TString2string(Str1);
  string s2 = FSString::TString2string(Str2);
  if(StringPatternMatch(s1,s2)||StringPatternMatch(s2,s1)){return true;}
  else{return false;}
}
//==========================================================================
//==========================================================================
TString StrfromVec( vector<TString> StringVector, TString Spacer){
  TString outString;
  // Incase im passing an empty vector...
  if(StringVector.size()==0){ return "Bad_Input";  }
  for( int i = 0; i < StringVector.size(); i++){
    if(i==0){outString = StringVector[i];}
    if(i!=0){outString = outString+Spacer+StringVector[i];}
  }
  return outString;
}
//==========================================================================
/*
vector<TString> DoubVec2StrVec( vector<double> DoubleVector){
  vector<TString> outString;
  // Incase im passing an empty vector...
  if(DoubleVector.size()==0){ 
    cout << "Bad Input for DoubVec2StrVec" << endl;
    return {""};
  }
  for( int i = 0; i < DoubleVector.size(); i++){
    if(i==0){outString = DoubleVector[i];}
    if(i!=0){outString = outString+Spacer+DoubleVector[i];}
  }
  return outString;
}*/
//==========================================================================
  // Remove a specific TString type from a vector of TStrings
vector<TString> eraseStrfromVec( vector<TString> StrVec, TString StringEx ){
  vector<TString> dummyVec;
  if(StrVec.size()>0){
    for (unsigned int i = 0; i < StrVec.size(); i++){
      if(StrVec[i]!=StringEx){ dummyVec.push_back(StrVec[i]);}
    }
  }
  return dummyVec;
}
//==========================================================================
// A more specific version of the function above
vector<TString> eraseElement(bool OnlyFirst, vector<TString> inputVector, TString eraseTarget){
  for (int i = 0; i < inputVector.size(); i++){
    if (*(inputVector.begin()+i)==eraseTarget){  
      inputVector.erase(inputVector.begin()+(i--));  
      if(OnlyFirst){return inputVector;}
    }
  }
  return inputVector;
}
vector<int> eraseElement(bool OnlyFirst, vector<int> inputVector, int eraseTarget){
  for (int i = 0; i < inputVector.size(); i++){
    if( *(inputVector.begin()+i)==eraseTarget){  
      inputVector.erase(inputVector.begin()+i); 
      if(OnlyFirst){return inputVector;}
    }
  }
  return inputVector;
}
//==========================================================================
vector<TString> replaceElement(bool OnlyFirst, vector<TString> inputVector, TString replaceTarget, TString replacement){
  for (int i = 0; i < inputVector.size(); i++){
    if( *(inputVector.begin()+i)==replaceTarget){ 
      inputVector[i] = replacement; 
      if(OnlyFirst){return inputVector;}
    }
  }
  return inputVector;
}
vector<int> replaceElement(bool OnlyFirst, vector<int> inputVector, int replaceTarget, int replacement){
  for (int i = 0; i < inputVector.size(); i++){
    if( *(inputVector.begin()+i)==replaceTarget){ 
      inputVector[i] = replacement; 
      if(OnlyFirst){return inputVector;}
    }
  }
  return inputVector;
}
//==========================================================================
TString replaceTString(TString inputTString, TString replaceTarget, TString replacement, bool OnlyFirst = false ){
  vector<TString> parsedTString;
  vector<TString> replacementVec;
  TString outputTString;
  // vector<TString> parseTString(TString input, TString spacer = " ",  bool recordSpacers = false, bool display = false);
  parsedTString = FSString::parseTString(inputTString);
  replacementVec = replaceElement(OnlyFirst,parsedTString,replaceTarget,replacement);
  outputTString = StrfromVec(replacementVec," ");
  return outputTString;
}
//==========================================================================
vector<TString> BoundVec(TString str){
  vector<TString> vec;
  TString STR0 = str( 1 , str.First(",")-1 );     // From After '(' to before first ',' WORKING
  vec.push_back(STR0);
  // The ROOT TSTRING takes the difference from initial spot ','  to final spot ')'
  TString str0 = str(  str.First(",")+1  ,  str.First(")")-str.First(",")-1  );      // PUTS OUT MIN,MAX
  TString str1 = str0(0,str0.First(","));
  vec.push_back(str1);
  TString str2 = str0(str0.First(",")+1,str.First(")")-str.First(",")-1 );      // PUTS OUT MAX
  vec.push_back(str2);
  return vec;
}
//=========================================================================
void WRONGin(){ 
  cout << "============= WRONG INPUT =============" << endl;
}
void SPACEin(){
  cout << "=======================================================" << endl;
}
void SPACEstr(TString in){ 
  cout << "=================== "+in+" ====================" << endl;
}
void SPACEnum(double in){
  cout << "================== "<<in<<" ===================" << endl;
}
void THINLINE(){
  cout << "----------------------------------------"<< endl;
}
//========================================================================
// If the cache has already been read, can use this
void SimpleClearCacheRange(int lowerIndex, int upperIndex){
  for( int i = lowerIndex ; i < upperIndex+1 ; i++ ){
    FSHistogram::clearHistogramCache(i);
  }
}
//========================================================================
// If the cache has not been read, can use this. Stand alone function for clearing cache parts.
void ClearCacheRange(TString cacheName, int lowerIndex, int upperIndex){
  FSHistogram::readHistogramCache(cacheName);
  SimpleClearCacheRange(lowerIndex,upperIndex);
  FSHistogram::dumpHistogramCache(cacheName);
}
//========================================================================
// For simple, quick and dirty counting 
double counter(TString FN, TString NT, TString MODE, TString cuts){
  TH1F* hc= FSHistogram::getTH1F(FN,NT,"1","(2,0,2)",MODE+FSAND+cuts);
  double NUM = hc->TH1::Integral(0,2);
  return NUM;
}
//========================================================================
// General Mode Counter
double counterMode(TString FN, TString NT, TString category, TString MODE, TString cuts){
  TH1F* hc = FSModeHistogram::getTH1F(FN,NT,category,"1","(2,0,2)",MODE+FSAND+cuts);
  double NUM = hc->TH1::Integral(0,2);
  return NUM;
}
//========================================================================
double countHIST(TH1F* hc){
  double xminBIN;  double xmaxBIN;
  xminBIN = hc->GetXaxis()->FindBin(hc->GetXaxis()->GetXmin());
  xmaxBIN = hc->GetXaxis()->FindBin(hc->GetXaxis()->GetXmax());
  //cout <<  xminBIN << endl;
  //cout <<  xmaxBIN << endl;
  double NUM = hc->TH1::Integral(xminBIN,xmaxBIN);
  return NUM;
}
//========================================================================
std::string pad_left(std::string const& str, size_t s)
{
    if ( str.size() < s )
        return std::string(s-str.size(), ' ') + str;
    else
        return str;
}
//========================================================================
std::string pad_right(std::string const& str, size_t s)
{
    if ( str.size() < s )
        return  str + std::string(s-str.size(), ' ') ;
    else
        return str;
}
//========================================================================
double precision(double Number ,int decP){
  double T = floor( Number*pow(10,decP) );
  return T/pow(10,decP);
}
//========================================================================
vector<TString> getSUBvec(vector<vector<TString>> inputvec, int vecplace){
    vector<TString> outputvec;
    //SPACEin();
    // j-loop runs over each sub-vector's elements (i)[a,b,c,d,...] and pushes them into a single string vector.
    for (int j=0; j<inputvec[vecplace].size(); j++) {
    //cout<< inputvector[vecplace][j] << endl;
    //SPACEin();  
    outputvec.push_back(inputvec[vecplace][j]);
    }
    //SPACEin();
    return outputvec;
}
//========================================================================
vector<TString> CutStringFirst(TString string, TString split ){
  int StringSize = string.Length();
  int SplitPlace = string.First(split);
  TString str1 = FSString::subString(string,0,SplitPlace);
  TString str2 = FSString::subString(string,SplitPlace+1,StringSize);
  vector<TString> outputvec = {str1,str2}; 
  return outputvec;
}
//========================================================================
TString CombineStringVec( vector<TString> TStringVector, TString spacer){
  // Incase im passing an empty vector...
  if(TStringVector.size()==0){ 
    SPACEstr("Shit... Bad Vector so using nothing...");
    return "";
  }
  TString outString;
  for( int i = 0; i < TStringVector.size(); i++){
    if(i==0){outString = TStringVector[i];}
    if(i!=0){outString = outString+spacer+TStringVector[i];}
  }
  return outString;
}
//========================================================================
void printVecPairs( vector<pair<TString,TString>> Vpairs ){
  cout << "VecPair Size: " << Vpairs.size() << endl;
  for(int j=0; j < Vpairs.size(); j++){
  cout << "Pair Set ["+FSString::int2TString(j)+"]  :  ( "+Vpairs[j].first+" , "+Vpairs[j].second+" ) "<< endl;
  }
}
//========================================================================
void printVector( vector<TString> Vector ){
  THINLINE();
  cout << "Vector Size: " << Vector.size() << endl;
  for(int j=0; j < Vector.size(); j++){
  cout << "Element ["+FSString::int2TString(j)+"]  :  " << Vector[j] << endl;
  }
  THINLINE();
}
void printVector( vector<int> Vector ){
  THINLINE();
  cout << "Vector Size: " << Vector.size() << endl;
  for(int j=0; j < Vector.size(); j++){
  cout << "Element ["+FSString::int2TString(j)+"]  :  " << Vector[j] << endl;
  }
  THINLINE();
}
void printVector( vector<double> Vector ){
  THINLINE();
  cout << "Vector Size: " << Vector.size() << endl;
  for(int j=0; j < Vector.size(); j++){
  cout << "Element ["+FSString::int2TString(j)+"]  :  " << Vector[j] << endl;
  }
  THINLINE();
}
//========================================================================
vector<double> VPairToVDoub(vector<pair<TString,TString>> inputpairs){
  vector<double> outputdubs;
  for(int j=0; j < inputpairs.size(); j++){
    outputdubs.push_back(inputpairs[j].first.TString::Atof());
    outputdubs.push_back(inputpairs[j].second.TString::Atof());
  }
  return outputdubs;
}
//========================================================================
void checkdoub(){
  vector<pair<TString,TString>> inputpairs;
  inputpairs.push_back(make_pair("3.38","0.0"));
  inputpairs.push_back(make_pair("3.49","3.5"));
  vector<double> ints= VPairToVDoub(inputpairs);
  for(int j=0; j < ints.size(); j++){
  cout << ints[j] << endl;
  }
}
//========================================================================
double getDiff(double num1, double num2){
  if(num1==num2){ return 0.0;}  // No difference...
  double large = max(num1,num2);
  double small = min(num1,num2);
  // getting differences
  if( large <= 0.0 ){
    return abs(large-small);
  }
  return large - small;
}
//========================================================================
void TeXMCComponentsAndSizes(vector< pair<TString, float> > components, bool TeXReady, bool printAll = false){  //if (show){   Display is set to false to show events in LaTeX form here
  int printNum;
  vector<TString> VecForTeX;
  if( (components.size()>20)&&(!printAll) ){ printNum = 20; }
    else{ printNum = components.size(); }
    cout << "****************" << endl;
    cout << "MC Components:     [Number of Decay Modes: " << components.size() << "]" << endl;
    cout << "****************" << endl;
    for (unsigned int i = 0; i < printNum; i++){
      VecForTeX = CutStringFirst(FSModeHistogram::formatMCComponent(components[i].first,components[i].second),")");
      //cout << VecForTeX[0] << " " << VecForTeX[1] << endl;
      if(TeXReady){
        cout << FSModeString::latexSymbols(VecForTeX[1]).TString::ReplaceAll("->","\\rightarrow")  << " &  \\\\"<< endl;
        cout << "\\hline" << endl;
        }
      else{cout << VecForTeX[0].TString::ReplaceAll("(","") << "  " << VecForTeX[1].TString::ReplaceAll("->","  ->  ") << endl;}
      VecForTeX.clear();
    }
    cout << "****************" << endl;
    cout << "****************" << endl;
  //}
  return;
}
//========================================================================
vector<pair<TString,float>> TeXMCComponentsAndSizes(TString fileName,TString ntName,TString category,TString cuts, bool TeXReady=false, bool Print=false){
  vector<pair<TString,float>> components=FSModeHistogram::getMCComponentsAndSizes(fileName,ntName,category,"2","(20,0,5)",cuts,true,true,0);
  if(Print){TeXMCComponentsAndSizes(components,TeXReady);}
  return components;
}
//========================================================================
vector<TString> VecOutTeXMCComponentsAndSizes(bool limitoutput, TString FN, vector< pair<TString, float> > components,  bool TeXReady, int TotalN = 100){
  int printNum;
  int printSum = 0;
  TString NEvents;
  vector<TString> printvec;
  vector<TString> VecForTeX;
  if( limitoutput && (components.size() > 20) ){ printNum = 20; }
    else{ printNum = components.size(); }
    printvec.push_back("****************");
    printvec.push_back("MC Components:     [  Number of Decay Modes: "+FSString::int2TString(components.size())+"  ,  NTotal: "+FSString::int2TString(TotalN)+"   ]");
    printvec.push_back(" for  File Name :");
    printvec.push_back(FN);
    printvec.push_back("****************");
    for (unsigned int i = 0; i < printNum; i++){
      VecForTeX = CutStringFirst(FSModeHistogram::formatMCComponent(components[i].first,components[i].second),")");
      if(TeXReady){
        NEvents = FSString::double2TString(round(components[i].second*TotalN));
        printSum = printSum + round(components[i].second*TotalN);
        printvec.push_back("$"+FSModeString::latexSymbols(VecForTeX[1]).TString::ReplaceAll("->","$&\\hspace{-0.35cm}$\\rightarrow")+"$ &  "+FSString::parseTString(NEvents,".")[0]+"\\\\");
        printvec.push_back("\\hline");
        cout << FSModeString::latexSymbols(VecForTeX[1]).TString::ReplaceAll("->","\\rightarrow")+" &  "+FSString::parseTString(NEvents,".")[0] << endl;
        }
      else{printvec.push_back(FSString::parseTString(VecForTeX[0],"(")[0]+" "+VecForTeX[1].TString::ReplaceAll("->"," -> "));}
      VecForTeX.clear();
    }
  if(TeXReady){
    printvec.push_back("\\Xhline{3\\arrayrulewidth}");
    printvec.push_back("&  Total &  "+FSString::int2TString(printSum)+"\\\\");
    printvec.push_back("\\hline");
  }
  printvec.push_back("****************");
  printvec.push_back("****************");
  return printvec;
}
//========================================================================
//========================================================================
//========================================================================
void writeComponents(bool limitoutput, TString OutputFile, TString FN, vector<pair<TString,float>> ComponentsSizes, int NTotal = 100, bool append=false){
  time_t _tm =time(NULL );
  struct tm * curtime = localtime ( &_tm );
  TString outputTime = asctime(curtime);
  // Writing Time to Top of File (or later if appending)
  FSString::writeTStringToFile(OutputFile,outputTime,append);
  //=========================================================
  // Setting up and writing to file in LaTex form / printing in simple form with percentages [base FSRoot way]
  vector<TString> writevector = VecOutTeXMCComponentsAndSizes(limitoutput,FN,ComponentsSizes,true,NTotal);
  vector<TString> printvector = VecOutTeXMCComponentsAndSizes(limitoutput,FN,ComponentsSizes,false,NTotal);
  for(int i = 0; i < writevector.size(); i++){
    FSString::writeTStringToFile(OutputFile,writevector[i],true); // Writing out results to OutputFile
  }
  for(int i = 0; i < printvector.size(); i++){
    cout << printvector[i] << endl;  // Printing out results
  }
  return;
}
//========================================================================
//========================================================================
//========================================================================
void printCutVecExcept( vector<pair<TString,TString>> StrVec, TString Excluded1, TString Excluded2 = "", TString Excluded3 = "" ){
  if(Excluded2==""){
    if(StrVec.size()>0){
      for (unsigned int i = 0; i < StrVec.size(); i++){
        if(!(StrVec[i].second.Contains(Excluded1))){
          cout << StrVec[i].second << endl;
        }
      }
      cout<<"----------------------------------------------------------"<<endl;
    }
  }
  if(Excluded2!=""&&Excluded3==""){
    if(StrVec.size()>0){
      for (unsigned int i = 0; i < StrVec.size(); i++){
        if(!(StrVec[i].second.Contains(Excluded1))){
          if(!(StrVec[i].second.Contains(Excluded2))){
            cout << StrVec[i].second << endl;
          }
        }
      }
      cout<<"----------------------------------------------------------"<<endl;
    }
  }
  if(Excluded3!=""){
    if(StrVec.size()>0){
      for (unsigned int i = 0; i < StrVec.size(); i++){
        if(!(StrVec[i].second.Contains(Excluded1))){
          if(!(StrVec[i].second.Contains(Excluded2))){
            if(!(StrVec[i].second.Contains(Excluded3))){
              cout << StrVec[i].second << endl;
            }
          }
        }
      }
      cout<<"----------------------------------------------------------"<<endl;
    }
  }
}



#endif