#include "TCanvas.h"
#include "TTree.h"
#include "TGaxis.h"
#include "TStyle.h"
#include "TFile.h"
#include <iostream>
#include <algorithm>    // std::sort
#include <vector>       // std::vector
#include "TMath.h"
#include "TChain.h"
#include "/media/ryan/Storage/computing/lysoRadSim/include/brROOTEvent.hh"
#include "TGraph.h"
#include "TVector.h"
#include "TVectorF.h"
#include "TH1.h"
#include "TH1F.h"
#include "TH2.h"
#include "TH2D.h"
#include "TString.h"
#include "TChain.h"
using namespace std;


void absorberEvt(){

//retreive file
  gStyle->SetOptStat(0);
  TChain rootEvents("Events");
  TString fileDir = "/media/ryan/Storage/computing/lysoRadSim/data/proton10/";
  TString xTitle = "Number of Gamma-Generated Electrons";
  rootEvents.Add(fileDir+"BeamRad.root");
  std::cout << "Reading file..." << std::endl;
  brROOTEvent* myROOTEvent = new brROOTEvent();
  rootEvents.SetBranchAddress("ROOTEvent", &myROOTEvent);
  Long64_t nentries=rootEvents.GetEntries();

//initialize variables
  double EDep=0;
  double hitTime=0;
  vector<vector<double>> allE;
  vector<vector<double>> allT;
  vector<double> EDeps;
  vector<double> hitTimes;
  double h=4.135668*pow(10,-15);
  double c=3*pow(10,8);
  int eCount=0;
  vector<int> muonHits;
  int count = 0;
  int numLYSOHits=0;
  int copyNo;
  int index=0;
TFile *out = new TFile(fileDir+"occupy10mmEvt.root","RECREATE");
//  TH1I* hEneDeposit = new TH1I("hEneDeposit","",17,-0.5,16.5);
  TGraph* hEneDeposit = new TGraph(17);

  hEneDeposit->SetLineColor(kBlue);
  hEneDeposit->SetMarkerStyle(21);
//  hEneDeposit->SetMarkerSize(9);
  hEneDeposit->GetXaxis()->SetTitle("Hit Time (ps)");
  hEneDeposit->GetYaxis()->SetTitle("Energy Deposited (MeV)");
  hEneDeposit->SetTitle("EDep and timing for events with 6+ occupancy (10mm to Pb)");

  TCanvas *c1 = new TCanvas("c1","c1",0,400,1600,1200);  
  		hEneDeposit->Draw();
		hEneDeposit->GetXaxis()->SetRangeUser(0,0.1);
		hEneDeposit->GetYaxis()->SetRangeUser(0,10);
  TString ts;
  double min;
  //get data in file
//  for (Long64_t i=0;i<nentries/10;i++) {
  for (Long64_t i=0;i<nentries;i++) {
	//my issue may have to do with this
	rootEvents.GetEntry(i);
  
  	numLYSOHits=myROOTEvent->GetScintRHits()->size();
  	for(int s=0;s<16;s++) {EDeps.push_back(0); hitTimes.push_back(10000000);}
	
	for(int h=0;h<numLYSOHits;h++){
		hitTime=myROOTEvent->GetScintRHits()->at(h)->GetInitialHitTime()*1000;
		copyNo=myROOTEvent->GetScintRHits()->at(h)->GetCopyNo();
		EDep=myROOTEvent->GetScintRHits()->at(h)->GetEDep();
		EDeps[copyNo-1]+=EDep;
		if(hitTime<hitTimes[copyNo-1]) hitTimes[copyNo-1]=hitTime;
	}


  	for(int s=0;s<16;s++){
		if(EDeps[s]>4) count++;
	}
	
	min = *min_element(hitTimes.begin(),hitTimes.end());

	if(count>5){
  		for(int s=0;s<16;s++){
			hitTimes[s]=hitTimes[s]-min;
			if(EDeps[s]>0){
				//if(hEneDeposit->GetBinContent(hEneDeposit->FindBin(hitTimes[s]))==0){
				       
				//	cout << hitTimes[s] << " " << hEneDeposit->FindBin(hitTimes[s]) << endl;
				//	cout << EDeps[s] << endl;
					//hEneDeposit->Fill( hEneDeposit->FindBin(hitTimes[s]), EDeps[s]);
					hEneDeposit->SetPoint(index, hitTimes[s], EDeps[s]); index++;
				//}
				//else cout << "overlap bins!" << endl;
			}
		}
		ts="../data/proton10/Event"+to_string(i)+".png";
  		hEneDeposit->Draw("AP");
		//hEneDeposit->GetXaxis()->SetRange(0,0.1);
		//hEneDeposit->GetXaxis()->SetRange(0,0.1);
		hEneDeposit->GetXaxis()->SetLimits(0,100);
		hEneDeposit->SetMinimum(0);
		hEneDeposit->SetMaximum(50);
//		c1->GetYaxis()->SetRangeUser(0,10);
		//c1->Modified();
		c1->SaveAs(ts);
		for(int s=0;s<16;s++) hEneDeposit->SetPoint(s,-1,-1);
//		hEneDeposit->Reset();

//		allE.push_back(EDeps);
//		allT.push_back(minTimes);
	}
	index=0;
	EDeps.clear();
	hitTimes.clear();
	

	//eCount = std::floor(EDep*1000000/10); //convert MeV to eV, then divide by 10 eV per electron-hole pair, then set to integer
	//if(count>0) hEneDeposit->Fill(count);
	count=0;
	if(i%10000==0) cout << "Finished analyzing event number " << i << endl;
  }
	


//for (int j=0; j<muonHits.size(); j++){
//	if(muonHits[j]>0) hEneDeposit->Fill(muonHits[j]);
//}

  out->Write();
}
