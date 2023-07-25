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
//void plotAbs(TCanvas*, TString);
/*
void plotAll(){

  TCanvas *c1 = new TCanvas("c1","c1",0,400,600,300);  
  TCanvas *c2 = new TCanvas("c2","c2",0,400,600,300);  
  TCanvas *c3 = new TCanvas("c3","c3",0,400,600,300);  
  TCanvas *c4 = new TCanvas("c4","c4",0,400,600,300);  
  TCanvas *c5 = new TCanvas("c5","c5",0,400,600,300);  

  plotAbs(c1,"2000um");
  plotAbs(c2,"500um");
  plotAbs(c3,"200um");
  plotAbs(c4,"50um");
  plotAbs(c5,"no");

}


void plotAbs(TCanvas *c1, TString absThickness){

//  TString absThickness = "2000um";
//  TCanvas *c1 = new TCanvas("c1","c1",0,400,600,300);  
 
  TCanvas *c = c1;	
  TH1I* low = gammaEDepElectronCount("10keV_"+absThickness+"Abs");
  low->SetTitle("Gamma-Generated Electron Pairs in Si, "+absThickness+" Absorber");
  low->SetLineColor(kRed);
  low->Draw();
  TH1I* lowmid = gammaEDepElectronCount("25keV_"+absThickness+"Abs");
  lowmid->SetLineColor(kOrange);
  lowmid->Draw("same");
  TH1I* Am241 = gammaEDepElectronCount("Am241_"+absThickness+"Abs");
  Am241->SetLineColor(kBlack);
  Am241->Draw("same");
  TH1I* mid = gammaEDepElectronCount("60keV_"+absThickness+"Abs");
  mid->SetLineColor(kGreen);
  mid->Draw("same");
  TH1I* midhigh = gammaEDepElectronCount("200keV_"+absThickness+"Abs");
  midhigh->SetLineColor(kMagenta);
  midhigh->Draw("same");
  TH1I* high = gammaEDepElectronCount("500keV_"+absThickness+"Abs");
  high->SetLineColor(kBlue);
  high->Draw("same");
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
*/
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
  TH1I* hEneDeposit1 = new TH1I("hEneDeposit1","",1000,0,50001);
  TH1I* hEneDeposit2 = new TH1I("hEneDeposit2","",1000,0,50001);
  TH1I* hEneDeposit3 = new TH1I("hEneDeposit3","",1000,0,50001);

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
	hEneDeposit1->Fill(eCount1);
	hEneDeposit2->Fill(eCount2);
	hEneDeposit3->Fill(eCount3);
  }

hEneDeposit3->SetLineColor(kBlue);
hEneDeposit3->GetXaxis()->SetTitle(xTitle);
hEneDeposit3->GetYaxis()->SetTitle("Bin Members");
hEneDeposit3->SetTitle("Electron-Hole Pairs Generated in 3-layer Si stack, "+absThick+" absorber, " + ene);

hEneDeposit2->SetLineColor(kGreen);
hEneDeposit1->SetLineColor(kRed);

  TCanvas *c1 = new TCanvas("c1","c1",0,400,600,300);  

  hEneDeposit3->Draw();
  hEneDeposit2->Draw("same");
  hEneDeposit1->Draw("same");
  
  TLegend *leg = new TLegend(0.6,0.6,0.85,0.85);
  leg->AddEntry(hEneDeposit1,"Upper Si Layer","l");
  leg->AddEntry(hEneDeposit2,"Middle Si Layer","l");
  leg->AddEntry(hEneDeposit3,"Lower Si Layer","l");
  leg->Draw("same");
  
  c1->Update();
  
  out->Write();

  return hEneDeposit3;
  }
