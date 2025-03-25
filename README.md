## BAH-Functions 

**BESIII Analysis Helper (BAH) Functions is a project created by Johnathan Gutierrez**.
 
The primary use is for working on data anaylses using [ROOT](https://root.cern/) files taken from the Beijing Spectrometer III ([BESIII](http://bes3.ihep.ac.cn/)).

The main function of these utilites was to learn classes, more organization and make my physics analyses for data samples from BESIII far more convienient.

#### Usage

The library is built off of ROOT and [FSRoot](https://github.com/remitche66/FSRoot). 

The primary utilities used in the analysis are in BAHHeaders. The application of the basic utilities are found in the base directory.

Plan to add more descriptions when I have more time later in the year to clean up the functionality... [or not... not sure.]

<!---
The order of dependancy from core to dependant are:
1) **Core:**
   - BAHUtilities
   - PartFunctions [_Convenience_]

2) **Secondary:**
   - FileHelper
   - BAHStrings
   - BAHPhysics

3) **etc:**
   - BAHDecays
   - BAHCuts
   - BAHSetup
   - ScalingHelper
   - DrawResources
   - ntGenHelper  [_Depreciated?_]

4) **Non-Functional:**
   - BAHDataSets
-->
