#include "TCanvas.h"
#include "TTree.h"
#include "TGaxis.h"
#include "TStyle.h"
#include "TFile.h"
#include <iostream>
#include "TMath.h"
#include "TChain.h"
#include "/home/schmitz/sim/HannahTestStand/include/eurROOTEvent.hh"
#include "TGraph.h"
#include "TVector.h"
#include "TVectorF.h"
#include "TH1.h"
#include "TH1F.h"
using namespace std;

//b==0 looks at pre detection; b==1 looks at post detection
void nCaptureCount(){

//retreive file

  TChain rootEvents("Events");
  rootEvents.Add("/data/chocula/schmitz/condor_output/HannahTestStand/data/EURECA.root");
  std::cout << "Reading file..." << std::endl;
  eurROOTEvent* myROOTEvent = new eurROOTEvent();
  rootEvents.SetBranchAddress("ROOTEvent", &myROOTEvent);
  Long64_t nentries=rootEvents.GetEntries();

//initialize variables
  double EDep=0;
  double h=4.135668*pow(10,-15);
  double c=3*pow(10,8);
  int nCapNum;

vector<double> nCap;
int index=0;
int numNeutronTracks=0;
int numNeutrons=0;
//get data in file
  for (Long64_t i=0;i<nentries;i++) {
	index=0;
	//my issue may have to do with this
	rootEvents.GetEntry(i);

	//Photon Energies (before detection). size() evaluates to 100; each photon track seems to "contain" many smaller ones.
		numNeutronTracks = myROOTEvent->GetNeutronTracks()->size();
		if (numNeutronTracks>0){
			for (int k = 0; k < numNeutronTracks; k++) {
				numNeutrons++;
				nCapNum=myROOTEvent->GetNeutronTracks()->at(k)->GetCaptureAtomicNum();
				if (nCapNum>0) nCap.push_back(nCapNum);
				}
			}
		}
  std::cout << "Number of incident neutrons: " << nentries << endl;
  std::cout << "Number of captured neutrons: " << nCap.size() << endl;
  std::cout << "Capture efficiency: " << (double)nCap.size()/nentries << endl;
}
