#include "TCanvas.h"
#include "TRandom.h"
#include "TTree.h"
#include "TGaxis.h"
#include "TStyle.h"
#include "TFile.h"
#include <iostream>
#include "TMath.h"
#include "TChain.h"
#include "/media/ryan/Storage/computing/beamRadSim/include/brROOTEvent.hh"
#include "TGraph.h"
#include "TVector.h"
#include "TVectorF.h"
#include "TH1.h"
#include "TF1.h"
#include "TH1F.h"
#include "TString.h"
#include "TChain.h"
using namespace std;

void gammaFinalEnergy(Double_t thickness){

//retreive file

  TChain rootEvents("Events");
  TString absThick;
  if(thickness==0.5) absThick = "0p5";
  if(thickness==1) absThick = "1";
  if(thickness==2) absThick = "2";
  if(thickness==3) absThick = "3";
  TString fileDir = "/media/ryan/Storage/computing/beamRadSim/data/eBremData/gammaDepositPreSteel"+absThick+"cm/";
  TString xTitle = "Number of Gamma-Generated Electrons";
//  TString absThick = "50um";
  rootEvents.Add(fileDir+"BeamRad.root");
  std::cout << "Reading file..." << std::endl;
  brROOTEvent* myROOTEvent = new brROOTEvent();
  rootEvents.SetBranchAddress("ROOTEvent", &myROOTEvent);
  Long64_t nentries=rootEvents.GetEntries();

//initialize variables
  double h=4.135668*pow(10,-15);
  double c=3*pow(10,8);
  int count = 0;
  int nbins = 200;
  int nGamma=0;
 TFile *out = new TFile(fileDir+"GammaEDepPre.root","RECREATE");
  TH1F* hFinalEne = new TH1F("hFinalEne","",nbins,0,0.1);

  double finalX,finalY,finalZ,finalMag,initX,initY,initMag;
  double outerSteel = 0.1+thickness/100; //10 cm inner radius, outer radius as argument in cm converted to m
//get data in file
  for (Long64_t i=0;i<nentries;i++) {
//  for (Long64_t i=0;i<100000;i++) {//nentries;i++) {
	//my issue may have to do with this
	rootEvents.GetEntry(i);
	nGamma = myROOTEvent->GetGammaTracks()->size();
//	cout << "gammas: " << nGamma << endl;
	for(int h=0;h<nGamma;h++){
		initX = myROOTEvent->GetGammaTracks()->at(h)->GetFirstPositionX();
		initY = myROOTEvent->GetGammaTracks()->at(h)->GetFirstPositionY();
		finalX = myROOTEvent->GetGammaTracks()->at(h)->GetLastPositionX();
		finalY = myROOTEvent->GetGammaTracks()->at(h)->GetLastPositionY();
		finalZ = myROOTEvent->GetGammaTracks()->at(h)->GetLastPositionZ();
		initMag = std::sqrt(std::pow(initX-0.12,2)+std::pow(initY,2));
		finalMag = std::sqrt(std::pow(finalX-0.12,2)+std::pow(finalY,2));
		if(finalMag>outerSteel && initMag<outerSteel && std::abs(finalZ) < 9){ //started inside steel, ended outside steel, didn't go down ends
			hFinalEne->Fill(myROOTEvent->GetGammaTracks()->at(h)->GetFinalEnergy());
		}
	}
  if (i % (nentries/100) == 0) cout << (double)i*100/nentries << "% complete" << endl;
  }

  TCanvas *c1 = new TCanvas("c1","c1",0,400,600,300);  
  hFinalEne->GetXaxis()->SetTitle("Gamma Final Energy");
  hFinalEne->GetYaxis()->SetTitle("Bin Members");
  hFinalEne->Draw();

  out->Write();
  out->Close();
}
