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
using namespace std;


void SlabEventCut(){

//retreive file

  TChain rootEvents("Events");
  rootEvents.Add("/media/ryan/Storage/computing/experimentalData/far_900v_full_run_muon_bar.root"); //97 refl
  std::cout << "Reading file..." << std::endl;
  Long64_t nentries=rootEvents.GetEntries();

//initialize variables
  double EDep=0;
  double h=4.135668*pow(10,-15);
  double c=3*pow(10,8);
  double slabArea;
  vector<int> nbPMTHits;

cout << "nentries: " << nentries << endl;
//get data in file 
  for (Long64_t i=0;i<nentries;i++) {
		rootEvents.GetEntry(i);
		slabArea=rootEvents.GetBranch("area_CH4")->GetLeaf("area")->GetValue(0);
		if (slabArea<1000)nbPMTHits.push_back(rootEvents.GetBranch("area_CH1")->GetLeaf("area")->GetValue(0));
//		std::cout << "NbPMTHits in entry " << i << ": " << nbPMTHits[i] << std::endl;
		if (i % 100 == 0) cout << "Processing Event Number " << i << endl;
	}

//basic graph
TH1I *hPMT= new TH1I("hPMT","Pulse Area Ch1",300,0,30000);
for(int q=0;q<nbPMTHits.size();q++){
	hPMT->Fill(nbPMTHits[q]);
//	tick++;
//	if (tick==10000){
//		tick=0;
//	}
}	
hPMT->GetXaxis()->SetTitle("Pulse Area (pVs)");
hPMT->GetYaxis()->SetTitle("Bin Members");

TCanvas *c1 = new TCanvas("c1","c1",0,400,600,300);
hPMT->Draw();
}	
