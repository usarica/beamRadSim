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


void PECountSpectrum(){

//retreive file

  TChain rootEvents("Events");
  rootEvents.Add("/data/chocula/schmitz/condor_output/HannahTestStand/data/paper/muon5/wholeR99/EURECA.root");
  std::cout << "Reading file..." << std::endl;
  eurROOTEvent* myROOTEvent = new eurROOTEvent();
  rootEvents.SetBranchAddress("ROOTEvent", &myROOTEvent);
  Long64_t nentries=rootEvents.GetEntries();

//initialize variables
  double EDep=0;
  double h=4.135668*pow(10,-15);
  double c=3*pow(10,8);
  double wavelength;
  double final_z=0;
  double final_x=0;
  double final_y=0;
  double XYMag=0;
  int fiberInc=0;
  int under=0;
  int PECount=0;
vector<double> wave;
int pmtCount=0;
int photonCount=0;
int numPhotonTracks=0;
//get data in file
  for (Long64_t i=0;i<nentries;i++) {
	//my issue may have to do with this
	rootEvents.GetEntry(i);
	PECount = myROOTEvent->GetPECountPMT();
	if (PECount<100) {
	cout << "PECount for low-count event: " << PECount << endl;
	under++;
	}
   }
cout << "Total low-count PE detection events: " << under << endl;

}
	
