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
#include "TH1D.h"
#include "TH2.h"
#include "TH2D.h"
#include "TH1F.h"
#include "TString.h"
#include "TChain.h"
#include "TRandom.h"
using namespace std;
  const int NPARTICLEMAX=200;
  const int NPIXEL=13;
  const int NPIXELMAX=NPIXEL*NPIXEL*2+1;

void absorberGrid(){
//retreive file
  gStyle->SetOptStat(0);
  TChain rootEvents("Events");
  //TString fileDir = "/media/ryan/Storage/computing/beamRadSim/data/proton/";
  TString fileDir = "/media/ryan/Storage/computing/beamRadSim/build/";
  TString xTitle = "Number of Gamma-Generated Electrons";
  rootEvents.Add(fileDir+"10cm2.root");
  //rootEvents.Add(fileDir+"50cm.root");
  //rootEvents.Add(fileDir+"BeamRad0p1um.root");
  std::cout << "Reading file..." << std::endl;
  brROOTEvent* myROOTEvent = new brROOTEvent();
  rootEvents.SetBranchAddress("ROOTEvent", &myROOTEvent);
  Long64_t nentries=rootEvents.GetEntries();

//initialize variables
  double EDep=0;
  double EDeps[NPIXELMAX];
  for(int s=0;s<NPIXELMAX;s++) EDeps[s]=0;
  double h=4.135668*pow(10,-15);
  double c=3*pow(10,8);
  int eCount=0;
  vector<int> muonHits;
  int count = 0;
  int numLGADHits=0;
  int copyNo;
  int nbinsx=13;
  int nbinsy=nbinsx;
  TString ts;
  int ss;
  int s;
  int nMIP=0;
  double pi=3.14159265;
  vector<double> temp;
  TCanvas *c0 = new TCanvas("c0","c0",0,400,1600,1200);

  //Double_t scorer[NPIXELMAX][NPARTICLEMAX];
  vector<vector<double> > scorer;
  for(int s=0;s<NPIXELMAX;s++) {
	  for(int k=0;k<NPARTICLEMAX;k++){
		  temp.push_back(0);
	}
	scorer.push_back(temp);
	temp.clear();
  }
  std::cout << "Reading file..." << std::endl;
  double scatter[NPARTICLEMAX];
  double angle;
  int trackID;
  TString particleName;
TFile *out = new TFile(fileDir+"analysis.root","RECREATE");
  TH1D* hNMIP = new TH1D("hNMIP","",20,0,20);
  TH1D* hScatterAngle = new TH1D("hScatterAngle","",100,0,1.57*180.0/pi);
  TH1D* hEDep = new TH1D("hEDep","",100,0.0000001,1);
  TH2D* hEneDeposit = new TH2D("hEneDeposit","",nbinsx,0,nbinsx,nbinsy,0,nbinsy);

  int bincount=(nbinsx+2)*(nbinsx+2);
  int entryCount[bincount];
  for(int ec=0;ec<bincount;ec++){entryCount[ec]=0;}

  int hits=0;
  int ngamma=0;
  bool check=false;
//get data in file
  for (Long64_t i=0;i<nentries;i++) {
//  for (Long64_t i=0;i<10000;i++) {
	//my issue may have to do with this
	rootEvents.GetEntry(i);
	if(myROOTEvent->GetEventEnergyDepositSi3() > 1 && myROOTEvent->GetEventEnergyDepositSi3() < 10){
  		numLGADHits=myROOTEvent->GetScintRHits()->size();
		for(int h=0;h<numLGADHits;h++){
			particleName=myROOTEvent->GetScintRHits()->at(h)->GetParticleName();
			if(particleName!="proton"){
			copyNo=myROOTEvent->GetScintRHits()->at(h)->GetCopyNo()+1-NPIXEL*NPIXEL;
			EDep=myROOTEvent->GetScintRHits()->at(h)->GetEDep();
			trackID=myROOTEvent->GetScintRHits()->at(h)->GetTrackID();
			scorer[copyNo][trackID]+=EDep;
			angle=myROOTEvent->GetScintRHits()->at(h)->GetScatterAngle()*180.0/pi;
			if(angle>0) scatter[trackID]=angle;
			}
	   		//cout << copyNo << " " << EDep << " " << trackID << endl;
		}
		
		for(int a=170;a<NPIXELMAX;a++){
		   for(int k=2;k<NPARTICLEMAX;k++){
			if(scorer[a][k]>0) {
			//	cout << scorer[a][k] << endl;
				hEDep->Fill(scorer[a][k]);
				if(scorer[a][k]<0.1){
					s=a-169;
					if(!check) hits++;
					hScatterAngle->Fill(scatter[k]);
					hEneDeposit->Fill(s/nbinsx,s%nbinsx);
					nMIP++;
				}
			}
		   }
		}/*
		if(nMIP==1){
		for(int h=0;h<numLGADHits;h++){
			particleName=myROOTEvent->GetScintRHits()->at(h)->GetParticleName();
			EDep=myROOTEvent->GetScintRHits()->at(h)->GetEDep();
			cout << particleName << " " << EDep << endl;
			}
		}*/
		/*
		ts="../data/MIP/Event"+to_string(i)+".png";
		c0->Modified();
		hEneDeposit->SetContour(hEneDeposit->GetMaximum()+1);
		hEneDeposit->Draw("colz");
		hEneDeposit->GetZaxis()->SetNdivisions(hEneDeposit->GetMaximum());
		if(hEneDeposit->GetMaximum()>1) c0->SaveAs(ts);
		//if((double)rand()/RAND_MAX<0.1) c0->SaveAs(ts);
		//c0->SaveAs(ts);
		hEneDeposit->Reset();
		*/
		hNMIP->Fill(nMIP);
		nMIP=0;
		check=false;
		//eCount = std::floor(EDep*1000000/10); //convert MeV to eV, then divide by 10 eV per electron-hole pair, then set to integer
	
		for(int k=0;k<NPARTICLEMAX;k++){
		    scatter[k]=0;
	 	    for(int a=0;a<NPIXELMAX;a++){
			scorer[a][k]=0;
		    }
	   	}
	}
		//if(i%1000==0) cout << "Finished analyzing event number " << i << endl;
  }
 if(hits>0){
  	for(int ec=0;ec<bincount;ec++)
	//	  cout << "bin: " << ec << " content: " << hEneDeposit->GetBinContent(ec) << endl;
                  hEneDeposit->SetBinContent(ec,(double)hEneDeposit->GetBinContent(ec)/hits);
                  //hEneDeposit->SetBinContent(ec,(double)hEneDeposit->GetBinContent(ec)/entryCount[ec]);
                  //hEneDeposit->SetBinContent(ec,entryCount[ec]);
	  }
	/*
  hEneDeposit->SetBinContent(127,0);
//for (int j=0; j<muonHits.size(); j++){
//	if(muonHits[j]>0) hEneDeposit->Fill(muonHits[j]);
//}

  //hEneDeposit->SetLineColor(kBlue);
  //hEneDeposit->SetMarkerSize(4);
  hEneDeposit->GetXaxis()->SetTitle("X-coordinate of pixel");
  hEneDeposit->GetYaxis()->SetTitle("Y-coordinate of pixel");
//  hEneDeposit->SetTitle("EDep in 10um pixels (120 GeV protons)");
hEneDeposit->SetTitle("MIPs per pixel per event (50cm)");

*/
  TCanvas *c1 = new TCanvas("c1","c1",0,400,600,300);  
  hEneDeposit->Draw("colz");
  c1->SaveAs("MIPHeatMap.C");
  TCanvas *c2 = new TCanvas("c2","c2",0,400,600,300);  
  hEDep->SetTitle("Energy Deposited in 150 um Si tracker");
  hEDep->GetXaxis()->SetTitle("Energy Deposited (MeV)");
  hEDep->Draw();
  TCanvas *c3 = new TCanvas("c3","c3",0,400,600,300);  
  hNMIP->SetTitle("Number of MIPs, 10cm distance, 6.5cm x 6.5cm square, 1 to 10 MeV Proton EDep");
  hNMIP->GetXaxis()->SetTitle("Number of MIPs");
  hNMIP->Draw();
  TCanvas *c4 = new TCanvas("c4","c4",0,400,600,300);  
  hScatterAngle->SetTitle("Scattering Angle, secondaries");
  hScatterAngle->GetXaxis()->SetTitle("Angle (#theta)");
  hScatterAngle->Draw();
  out->Write();
  }

