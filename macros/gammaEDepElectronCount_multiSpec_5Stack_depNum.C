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

TH1I* gammaEDepElectronCount(TString,TString, int, int);
void plotAbs(TCanvas*, TString, int, int);

void plotAll(){

  TCanvas *c1 = new TCanvas("c1","c1",0,400,600,300);  
//  TCanvas *c2 = new TCanvas("c2","c2",0,400,600,300);  
//  TCanvas *c3 = new TCanvas("c3","c3",0,400,600,300);  
//  TCanvas *c4 = new TCanvas("c4","c4",0,400,600,300);  
//  TCanvas *c5 = new TCanvas("c5","c5",0,400,600,300);  

  plotAbs(c1,"50um", 500, 1000);
//  plotAbs(c2,"500um");
//  plotAbs(c3,"200um");
//  plotAbs(c4,"50um");
//  plotAbs(c5,"no");

}

void plotAbs(TCanvas *c1, TString absThickness, int noise, int thresh){

//  TString absThickness = "2000um";
//  TCanvas *c1 = new TCanvas("c1","c1",0,400,600,300);  
 
  TCanvas *c = c1;
  TH1I* high = gammaEDepElectronCount("500keV",absThickness, noise, thresh);
//  high->SetTitle("Gamma-Generated Electron Pairs in Si, "+absThickness+" Absorber");
  high->SetLineColor(kBlue);
  high->Draw();
  TH1I* midhigh = gammaEDepElectronCount("200keV",absThickness, noise, thresh);
  midhigh->SetLineColor(kMagenta);
  midhigh->Draw("same");
  TH1I* mid = gammaEDepElectronCount("60keV",absThickness, noise, thresh);
  mid->SetLineColor(kGreen);
  mid->Draw("same");
  TH1I* Am241 = gammaEDepElectronCount("Am241",absThickness, noise, thresh);
  Am241->SetLineColor(kBlack);
  Am241->Draw("same");
  TH1I* lowmid = gammaEDepElectronCount("25keV",absThickness, noise, thresh);
  lowmid->SetLineColor(kOrange);
  lowmid->Draw("same");
  TH1I* low = gammaEDepElectronCount("10keV",absThickness, noise, thresh);
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

TH1I* gammaEDepElectronCount(TString ene,TString absThick, int noise, int thresh){

//retreive file
  
  TChain rootEvents("Events");
  TString fileDir = "/media/ryan/Storage/computing/beamRadSim/data/";
  TString xTitle = "Number of Gamma-Generated Electrons";
//  TString absThick = "50um";
  rootEvents.Add(fileDir+ene+"_"+absThick+"AbsScint_5stack/BeamRad.root");
  std::cout << "Reading file..." << std::endl;
  brROOTEvent* myROOTEvent = new brROOTEvent();
  rootEvents.SetBranchAddress("ROOTEvent", &myROOTEvent);
  Long64_t nentries=rootEvents.GetEntries();

//initialize variables
  double EDep1=0;
  double EDep2=0;
  double EDep3=0;
  double EDep4=0;
  double EDep5=0;
  double h=4.135668*pow(10,-15);
  double c=3*pow(10,8);
  int eCount1=0;
  int eCount2=0;
  int eCount3=0;
  int eCount4=0;
  int eCount5=0;
  int eCount1smear=0;
  int eCount2smear=0;
  int eCount3smear=0;
  int eCount4smear=0;
  int eCount5smear=0;
  double smearCount=0;
  double smearElec=0;
  vector<int> muonHits;
  int count = 0;
//  int noise = 400;
//  int thresh = 1000;
TFile *out = new TFile(fileDir+"GammaECount"+ene+".root","RECREATE");
  TH1I* hEneDepositCount = new TH1I("hEneDepositCount","",6,0,5.99);

//get data in file
  for (Long64_t i=0;i<nentries;i++) {
	//my issue may have to do with this
	rootEvents.GetEntry(i);
	EDep1 = myROOTEvent->GetEventEnergyDepositSi1();
	EDep2 = myROOTEvent->GetEventEnergyDepositSi2();
	EDep3 = myROOTEvent->GetEventEnergyDepositSi3();
	EDep4 = myROOTEvent->GetEventEnergyDepositSi4();
	EDep5 = myROOTEvent->GetEventEnergyDepositSi5();
	eCount1 = std::floor(EDep1*1000000/10); //convert MeV to eV, then divide by 10 eV per electron-hole pair, then set to integer
	eCount2 = std::floor(EDep2*1000000/10); //convert MeV to eV, then divide by 10 eV per electron-hole pair, then set to integer
	eCount3 = std::floor(EDep3*1000000/10); //convert MeV to eV, then divide by 10 eV per electron-hole pair, then set to integer
	eCount4 = std::floor(EDep4*1000000/10); //convert MeV to eV, then divide by 10 eV per electron-hole pair, then set to integer
	eCount5 = std::floor(EDep5*1000000/10); //convert MeV to eV, then divide by 10 eV per electron-hole pair, then set to integer

        TRandom *g1 = new TRandom();
        g1->SetSeed();
        if(eCount1>0 || g1->Uniform()<1){
        smearCount = (int)g1->Gaus((double)eCount1,sqrt((double)eCount1));
        smearElec = (int)g1->Gaus(0,noise);
        } else {smearCount = 0; smearElec = 0;}

        if(i % 100000 == 0) std::cout << "eCount: " << eCount1 << " smear: " << smearCount+smearElec << std::endl;
        if((smearCount+smearElec)<0) eCount1smear = 0;
        else eCount1smear = smearCount+smearElec;

        if(eCount2>0 || g1->Uniform()<1){
        smearCount = (int)g1->Gaus((double)eCount2,sqrt((double)eCount2));
        smearElec = (int)g1->Gaus(0,noise);
        } else {smearCount = 0; smearElec = 0;}
        if((smearCount+smearElec)<0) eCount2smear = 0;
        else eCount2smear = smearCount+smearElec;

        if(eCount3>0 || g1->Uniform()<1){
        smearCount = (int)g1->Gaus((double)eCount3,sqrt((double)eCount3));
        smearElec = (int)g1->Gaus(0,noise);
        } else {smearCount = 0; smearElec = 0;}
        if((smearCount+smearElec)<0) eCount3smear = 0;
        else eCount3smear = smearCount+smearElec;

        if(eCount4>0 || g1->Uniform()<1){
        smearCount = (int)g1->Gaus((double)eCount4,sqrt((double)eCount4));
        smearElec = (int)g1->Gaus(0,noise);
        } else {smearCount = 0; smearElec = 0;}
        if((smearCount+smearElec)<0) eCount4smear = 0;
        else eCount4smear = smearCount+smearElec;

        if(eCount5>0 || g1->Uniform()<1){
        smearCount = (int)g1->Gaus((double)eCount5,sqrt((double)eCount5));
        smearElec = (int)g1->Gaus(0,noise);
        } else {smearCount = 0; smearElec = 0;}
        if((smearCount+smearElec)<0) eCount5smear = 0;
        else eCount5smear = smearCount+smearElec;

//	if(eCount1smear > thresh) count++;
//	if(eCount2smear > thresh) count++;
	if(eCount3smear > thresh) count++;
//	if(eCount4smear > thresh) count++;
//	if(eCount5smear > thresh) count++;

	hEneDepositCount->Fill(count);
	count=0;
  }

hEneDepositCount->SetLineColor(kBlue);
hEneDepositCount->GetXaxis()->SetTitle(xTitle);
hEneDepositCount->GetYaxis()->SetTitle("Bin Members");
hEneDepositCount->SetTitle("L3 only, Number of interactions, "+absThick+" absorber, " + ene + ", " + std::to_string(thresh) + "threshold, " + std::to_string(noise) + " eNoise");
//  TCanvas *c1 = new TCanvas("c1","c1",0,400,600,300);  

//  hEneDepositCount->Draw();
  //out->Write();

  return hEneDepositCount;
  }
