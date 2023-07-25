#include "TCanvas.h"
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
#include "TH1F.h"
#include "TString.h"
#include "TChain.h"
using namespace std;

TH1I* gammaEDepElectronCount(TString,TString);
void plotAbs(TCanvas*, TString);

void plotAll(){

  TCanvas *c1 = new TCanvas("c1","c1",0,400,600,300);  
//  TCanvas *c2 = new TCanvas("c2","c2",0,400,600,300);  
//  TCanvas *c3 = new TCanvas("c3","c3",0,400,600,300);  
//  TCanvas *c4 = new TCanvas("c4","c4",0,400,600,300);  
//  TCanvas *c5 = new TCanvas("c5","c5",0,400,600,300);  

  plotAbs(c1,"500um");
//  plotAbs(c2,"500um");
//  plotAbs(c3,"200um");
//  plotAbs(c4,"50um");
//  plotAbs(c5,"no");

}

void plotAbs(TCanvas *c1, TString absThickness){

//  TString absThickness = "2000um";
//  TCanvas *c1 = new TCanvas("c1","c1",0,400,600,300);  
 
  TCanvas *c = c1;	
  TH1I* high = gammaEDepElectronCount("500keV",absThickness);
//  high->SetTitle("Gamma-Generated Electron Pairs in Si, "+absThickness+" Absorber");
  high->SetLineColor(kBlue);
  high->Draw();
  TH1I* midhigh = gammaEDepElectronCount("200keV",absThickness);
  midhigh->SetLineColor(kMagenta);
  midhigh->Draw("same");
  TH1I* mid = gammaEDepElectronCount("60keV",absThickness);
  mid->SetLineColor(kGreen);
  mid->Draw("same");
  TH1I* Am241 = gammaEDepElectronCount("Am241",absThickness);
  Am241->SetLineColor(kBlack);
  Am241->Draw("same");
  TH1I* lowmid = gammaEDepElectronCount("25keV",absThickness);
  lowmid->SetLineColor(kOrange);
  lowmid->Draw("same");
  TH1I* low = gammaEDepElectronCount("10keV",absThickness);
  low->SetLineColor(kRed);
  low->Draw("same");
  
  TLegend *leg = new TLegend(0.6,0.6,0.85,0.85);
  leg->AddEntry(low,"10 keV","l");
  leg->AddEntry(lowmid,"25 keV","l");
  leg->AddEntry(mid,"60 keV","l");
  leg->AddEntry(midhigh,"200 keV","l");
  leg->AddEntry(high,"500 keV","l");
  leg->AddEntry(Am241,"Am241","l");
  leg->Draw("same");
  c1->Update();
}

TH1I* gammaEDepElectronCount(TString ene,TString absThick){

//retreive file

  TChain rootEvents("Events");
  TString fileDir = "/media/ryan/Storage/computing/beamRadSim/data/";
  TString xTitle = "Number of Gamma-Generated Electrons";
//  TString absThick = "50um";
  rootEvents.Add(fileDir+ene+"_"+absThick+"Abs_3stack/BeamRad.root");
  std::cout << "Reading file..." << std::endl;
  brROOTEvent* myROOTEvent = new brROOTEvent();
  rootEvents.SetBranchAddress("ROOTEvent", &myROOTEvent);
  Long64_t nentries=rootEvents.GetEntries();

//initialize variables
  double EDep1=0;
  double EDep2=0;
  double EDep3=0;
  double h=4.135668*pow(10,-15);
  double c=3*pow(10,8);
  int eCount1=0;
  int eCount2=0;
  int eCount3=0;
  vector<int> muonHits;
  int count = 0;


TFile *out = new TFile(fileDir+"GammaECount"+ene+".root","RECREATE");
  TH1I* hEneDepositCount = new TH1I("hEneDepositCount","",4,0,3.99);

//get data in file
  for (Long64_t i=0;i<nentries;i++) {
	//my issue may have to do with this
	rootEvents.GetEntry(i);
	EDep1 = myROOTEvent->GetEventEnergyDepositSi1();
	EDep2 = myROOTEvent->GetEventEnergyDepositSi2();
	EDep3 = myROOTEvent->GetEventEnergyDepositSi3();
	eCount1 = std::floor(EDep1*1000000/10); //convert MeV to eV, then divide by 10 eV per electron-hole pair, then set to integer
	eCount2 = std::floor(EDep2*1000000/10); //convert MeV to eV, then divide by 10 eV per electron-hole pair, then set to integer
	eCount3 = std::floor(EDep3*1000000/10); //convert MeV to eV, then divide by 10 eV per electron-hole pair, then set to integer
	if(eCount1 > 0) count++;
	if(eCount2 > 0) count++;
	if(eCount3 > 0) count++;

	hEneDepositCount->Fill(count);
	count=0;
  }

hEneDepositCount->SetLineColor(kBlue);
hEneDepositCount->GetXaxis()->SetTitle(xTitle);
hEneDepositCount->GetYaxis()->SetTitle("Bin Members");
hEneDepositCount->SetTitle("Number of interactions, "+absThick+" absorber, " + ene);
//  TCanvas *c1 = new TCanvas("c1","c1",0,400,600,300);  

//  hEneDepositCount->Draw();
  //out->Write();

  return hEneDepositCount;
  }
