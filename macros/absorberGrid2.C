#include "TCanvas.h"
#include "TTree.h"
#include "TGaxis.h"
#include "TStyle.h"
#include "TFile.h"
#include <iostream>
#include "TMath.h"
#include "TChain.h"
#include "/media/ryan/Storage/computing/lysoRadSim/include/brROOTEvent.hh"
#include "TGraph.h"
#include "TVector.h"
#include "TVectorF.h"
#include "TH1.h"
#include "TH1F.h"
#include "TString.h"
#include "TChain.h"
using namespace std;


void absorberEnergy(){

//retreive file
  gStyle->SetOptStat(0);
  TChain rootEvents("Events");
  TString fileDir = "/media/ryan/Storage/computing/beamRadSim/data/zhit/";
  TString xTitle = "Number of Gamma-Generated Electrons";
  rootEvents.Add(fileDir+"BeamRad.root");
  std::cout << "Reading file..." << std::endl;
  brROOTEvent* myROOTEvent = new brROOTEvent();
  rootEvents.SetBranchAddress("ROOTEvent", &myROOTEvent);
  Long64_t nentries=rootEvents.GetEntries();

//initialize variables
  double EDep=0;
  double EDeps[1200];
  for(int s=0;s<1200;s++) EDeps[s]=0;
  double h=4.135668*pow(10,-15);
  double c=3*pow(10,8);
  int eCount=0;
  vector<int> muonHits;
  int count = 0;
  int numLGADHits=0;
  int copyNo;
  int NLAYERS=10;
  double totalEDep=0;
TFile *out = new TFile(fileDir+"occupy.root","RECREATE");
  TH1D* hEneDeposit = new TH1D("hEneDeposit","",20,0,20);

//get data in file
  for (Long64_t i=0;i<nentries;i++) {
//  for (Long64_t i=0;i<nentries;i++) {
	//my issue may have to do with this
	rootEvents.GetEntry(i);
  
  	numLGADHits=myROOTEvent->GetScintRHits()->size();
	for(int h=0;h<numLGADHits;h++){
		copyNo=myROOTEvent->GetScintRHits()->at(h)->GetCopyNo();
		EDep=myROOTEvent->GetScintRHits()->at(h)->GetEDep();
		EDeps[(copyNo-100)/100]+=EDep;
		totalEDep+=EDep;
	}

  	for(int s=0;s<NLAYERS*2;s++){
		if(totalEDep>1){
			count++;
			if(s<NLAYERS) hEneDeposit->Fill(s, EDeps[s]/(0.1*0.1*0.1));
			else hEneDeposit->Fill(s, EDeps[s]/(0.1*0.1*4.9));
			//if(s<NLAYERS) hEneDeposit->Fill(s, EDeps[s]);
			//else hEneDeposit->Fill(s, EDeps[s]);
		}
		EDeps[s]=0;
	}
	

	//eCount = std::floor(EDep*1000000/10); //convert MeV to eV, then divide by 10 eV per electron-hole pair, then set to integer
	totalEDep=0;
	if(i%10000==0) cout << "Finished analyzing event number " << i << endl;
  }

//  	for(int s=0;s<NLAYERS*2;s++) hEneDeposit->SetBinContent(s, hEneDeposit->GetBinContent(s));

  hEneDeposit->Scale((double)1/count);

//for (int j=0; j<muonHits.size(); j++){
//	if(muonHits[j]>0) hEneDeposit->Fill(muonHits[j]);
//}

hEneDeposit->SetLineColor(kBlue);
hEneDeposit->GetXaxis()->SetTitle("Z depth (100nm first 10, 5um last 10)");
hEneDeposit->GetYaxis()->SetTitle("Average Energy Density (MeV/(um^3))");
hEneDeposit->SetTitle("Energy Density vs Z");

  TCanvas *c1 = new TCanvas("c1","c1",0,400,600,300);  
  hEneDeposit->Draw();
  out->Write();
}
