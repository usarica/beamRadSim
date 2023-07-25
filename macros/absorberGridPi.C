#include "TCanvas.h"
#include "TTree.h"
#include "TGaxis.h"
#include "TStyle.h"
#include "TFile.h"
#include <iostream>
#include "TMath.h"
#include "TChain.h"
#include "/media/schmitz/Storage/computing/beamRadSim/include/brROOTEvent.hh"
#include "TGraph.h"
#include "TVector.h"
#include "TVectorF.h"
#include "TH1.h"
#include "TH1F.h"
#include "TString.h"
#include "TChain.h"
using namespace std;


void absorberGridPi(){

//retreive file
  gStyle->SetOptStat(0);
  TChain rootEvents("Events");
  TString fileDir = "/media/schmitz/Storage/computing/beamRadSim/data/pion/5/";
  TString xTitle = "Number of Gamma-Generated Electrons";
  rootEvents.Add(fileDir+"BeamRad.root");
  std::cout << "Reading file..." << std::endl;
  brROOTEvent* myROOTEvent = new brROOTEvent();
  rootEvents.SetBranchAddress("ROOTEvent", &myROOTEvent);
  Long64_t nentries=rootEvents.GetEntries();

//initialize variables
  double EDep=0;
  int l1=0;
  int l2=0;
  int l3=0;
  double scorer[400];
  int occupy[400];
  //vector<> EDeps;
  for(int s=0;s<400;s++) {scorer[s]=0; occupy[s]=0;}
  double h=4.135668*pow(10,-15);
  double c=3*pow(10,8);
  int eCount=0;
  vector<int> muonHits;
  int count = 0;
  int numLGADHits=0;
  int copyNo;
  int NLAYERS=10;
  int parentID=0;
  double totalEDep=0;
TFile *out = new TFile(fileDir+"occupy05.root","RECREATE");
  TH1D* hEneDeposit = new TH1D("hEneDeposit","",100,0,100);
  TH1D* hOccupy = new TH1D("hOccupy","",399,1,400);

  // want to plot: bar occupancy with energy deposit over 1 keV
// so for each run, just sum energy deposits, then increment the
// counter for all bars with over 1 keV in total
// then we can plot the histogram of all such cases
// as well as the energy deposit plot overall
//get data in file
  for (Long64_t i=0;i<nentries;i++) {
//  for (Long64_t i=0;i<nentries;i++) {
	//my issue may have to do with this
	rootEvents.GetEntry(i);
  
  	numLGADHits=myROOTEvent->GetScintRHits()->size();
	for(int h=0;h<numLGADHits;h++){
		copyNo=myROOTEvent->GetScintRHits()->at(h)->GetCopyNo();
		parentID=myROOTEvent->GetScintRHits()->at(h)->GetParentID();
		if(parentID>0) EDep=myROOTEvent->GetScintRHits()->at(h)->GetEDep()*1000;
		scorer[copyNo]+=EDep;
		}
  	for(int s=0;s<400;s++) {
		if(scorer[s]>0) hEneDeposit->Fill(scorer[s]);
		if(scorer[s]>0.1) {
			hOccupy->Fill(s);
			if(s<150) l1++;
			else if(s<250) l2++;
			else if(s>250) l3++;
		}
		scorer[s]=0;
	}
	if(i%10000==0) cout << "Finished analyzing event number " << i << endl;
  }

hEneDeposit->SetLineColor(kBlue);
hEneDeposit->GetXaxis()->SetTitle("Energy Deposit (keV)");
hEneDeposit->GetYaxis()->SetTitle("Bin Members");
hEneDeposit->SetTitle("Energy Deposit Distribution, single cell, no primaries");

hOccupy->GetXaxis()->SetTitle("Cell Number");
hOccupy->GetYaxis()->SetTitle("Number of Occupied Cells (E>1keV)");
hOccupy->SetTitle("Cell Occupancy, 5 GeV Pion");
cout << "layer 1 hits: " << l1 << endl;
cout << "layer 2 hits: " << l2 << endl;
cout << "layer 3 hits: " << l3 << endl;

  TCanvas *c1 = new TCanvas("c1","c1",0,400,600,300);  
  hEneDeposit->Draw();
  hOccupy->Draw();
  out->Write();
}
