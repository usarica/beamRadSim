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
  TString fileDir = "/media/ryan/Storage/computing/lysoRadSim/data/proton/";
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
  int totalCount = 0;
TFile *out = new TFile(fileDir+"occupy100mmEvtNorm.root","RECREATE");
//  TH1I* hEneDeposit = new TH1I("hEneDeposit","",17,-0.5,16.5);
  int nbinsx=25;
  int nbinsy=16;
  TH2D* hEneDeposit = new TH2D("hEneDeposit","",nbinsx,0,100,nbinsy,0,nbinsy);
  cout << hEneDeposit->GetSize() << endl;
  hEneDeposit->SetLineColor(kBlue);
  hEneDeposit->SetMarkerSize(4);
  hEneDeposit->GetXaxis()->SetTitle("Hit Time (ps)");
  hEneDeposit->GetYaxis()->SetTitle("LYSO number");
  hEneDeposit->SetTitle("EDep and timing for events with 6+ occupancy (100mm to Pb)");
  
  int bincount=(nbinsx+2)*(nbinsx*2);
  int entryCount[bincount];
  for(int ec=0;ec<bincount;ec++){entryCount[ec]=0;}

  TCanvas *c1 = new TCanvas("c1","c1",0,400,1600,1200);  
  TString ts;
  double min;
  //get data in file
 // for (Long64_t i=0;i<nentries/10;i++) {
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
		totalCount++;
  		for(int s=0;s<16;s++){
			hitTimes[s]=hitTimes[s]-min;
			if(EDeps[s]>0){
				//if(hEneDeposit->GetBinContent(hEneDeposit->FindBin(hitTimes[s]))==0){
				       
				//	cout << hitTimes[s] << " " << hEneDeposit->FindBin(hitTimes[s]) << endl;
				//	cout << EDeps[s] << endl;
					//hEneDeposit->Fill( hEneDeposit->FindBin(hitTimes[s]), EDeps[s]);
					hEneDeposit->Fill(hitTimes[s], s, EDeps[s]);
					//hEneDeposit->Fill(hitTimes[s], s);
					entryCount[hEneDeposit->FindBin(hitTimes[s], s)]++;
				//}
				//else cout << "overlap bins!" << endl;
			}
		}
//		c1->Modified();
//                ts="../data/proton/zoom20/Event"+to_string(i)+".png";
//  		hEneDeposit->Draw("colz");
//		c1->SaveAs(ts);
//		hEneDeposit->Reset();

//		allE.push_back(EDeps);
//		allT.push_back(minTimes);
	}
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

  for(int ec=0;ec<bincount;ec++)
	  if(entryCount[ec]>0)
		  //hEneDeposit->SetBinContent(ec,(double)hEneDeposit->GetBinContent(ec)/totalCount);
		  hEneDeposit->SetBinContent(ec,(double)hEneDeposit->GetBinContent(ec)/entryCount[ec]);

ts="../data/proton/2dplotv2_pencil_norm.png";
hEneDeposit->GetZaxis()->SetNdivisions(20);
hEneDeposit->SetContour(50);
hEneDeposit->Draw("colz");
c1->SaveAs(ts);
  out->Write();
}

