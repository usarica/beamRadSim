#include "TCanvas.h"
#include "TTree.h"
#include "TGaxis.h"
#include "TStyle.h"
#include "TFile.h"
#include <iostream>
#include "TMath.h"
#include "TChain.h"
#include "TGraph.h"
#include "TGraph2D.h"
#include "TVector.h"
#include "TVectorF.h"
#include "TH1.h"
#include "TH1F.h"
#include "TH3.h"
#include "TH3D.h"
#include <set>
#include "/media/ryan/Storage/computing/mqFullSim/include/mqROOTEvent.hh"
using namespace std;


void LowTailPhotonYield(){

//retreive file

  TChain rootEvents("Events");
  rootEvents.Add("/media/ryan/Storage/computing/mqFullSim/data/R97/Far54p3/MilliQan.root"); //97 refl
  std::cout << "Reading file..." << std::endl;
  Long64_t nentries=rootEvents.GetEntries();
  mqROOTEvent* myROOTEvent = new mqROOTEvent();
  rootEvents.SetBranchAddress("ROOTEvent", &myROOTEvent);

//initialize variables
  double EDep=0;
  double h=4.135668*pow(10,-15);
  double c=3*pow(10,8);
  vector<int> nbPMTHits;
  int PECount =0;
  int photonYield=0;
cout << "nentries: " << nentries << endl;

//get data in file 
  for (Long64_t i=0;i<nentries;i++) {
		rootEvents.GetEntry(i);
		PECount = myROOTEvent->GetPMTRHits()->size();
		if (PECount<8000) photonYield=myROOTEvent->GetPhotonTracks()->size();
		nbPMTHits.push_back(photonYield);
//		std::cout << "NbPMTHits in entry " << i << ": " << nbPMTHits[i] << std::endl;
		if (i % 100 == 0) cout << "Processing Event Number " << i << endl;
	}

//basic graph
TH1I *hPMT= new TH1I("hPMT","Num. of PMT Hits",500,0,290000);
for(int q=0;q<nbPMTHits.size();q++){
	hPMT->Fill(nbPMTHits[q]);
//	tick++;
//	if (tick==10000){
//		tick=0;
//	}
}	
hPMT->GetXaxis()->SetTitle("Total Photon Yield");
//hPMT->GetXaxis()->SetTitle("Number of PE Counts");
hPMT->GetYaxis()->SetTitle("Bin Members");

TCanvas *c1 = new TCanvas("c1","c1",0,400,600,300);
hPMT->Draw();
}	
