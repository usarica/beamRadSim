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
  double countStat1,countStat2,countStat3,countStat4,countStat5;
  double h=4.135668*pow(10,-15);
  double c=3*pow(10,8);
  int eCount1=0;
  int eCount2=0;
  int eCount3=0;
  int eCount4=0;
  int eCount5=0;
  vector<int> muonHits;
  int count = 0;
  int smearCount = 0;
  int smearElec = 0;
  double noise = 500;
  int nbins = 500;
TFile *out = new TFile(fileDir+"GammaECount"+ene+".root","RECREATE");
  TH1I* hEneDeposit1 = new TH1I("hEneDeposit1","",nbins,0,50001);
  TH1I* hEneDeposit2 = new TH1I("hEneDeposit2","",nbins,0,50001);
  TH1I* hEneDeposit3 = new TH1I("hEneDeposit3","",nbins,0,50001);
  TH1I* hEneDeposit4 = new TH1I("hEneDeposit3","",nbins,0,50001);
  TH1I* hEneDeposit5 = new TH1I("hEneDeposit3","",nbins,0,50001);

//get data in file
  for (Long64_t i=0;i<nentries;i++) {
  //for (Long64_t i=0;i<1000000;i++) {//nentries;i++) {
	//my issue may have to do with this
	rootEvents.GetEntry(i);
    if(myROOTEvent->GetEventEnergyDepositScintVeto() == 0 ){
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
	if((smearCount+smearElec)<0) hEneDeposit1->Fill(0);
	else hEneDeposit1->Fill(smearCount+smearElec);

	if(eCount2>0 || g1->Uniform()<1){
	smearCount = (int)g1->Gaus((double)eCount2,sqrt((double)eCount2));
	smearElec = (int)g1->Gaus(0,noise);
	} else {smearCount = 0; smearElec = 0;}
	if((smearCount+smearElec)<0) hEneDeposit2->Fill(0);
	else hEneDeposit2->Fill(smearCount+smearElec);

	if(eCount3>0 || g1->Uniform()<1){
	smearCount = (int)g1->Gaus((double)eCount3,sqrt((double)eCount3));
	smearElec = (int)g1->Gaus(0,noise);
	} else {smearCount = 0; smearElec = 0;}
	if((smearCount+smearElec)<0) hEneDeposit3->Fill(0);
	else hEneDeposit3->Fill(smearCount+smearElec);

	if(eCount4>0 || g1->Uniform()<1){
	smearCount = (int)g1->Gaus((double)eCount4,sqrt((double)eCount4));
	smearElec = (int)g1->Gaus(0,noise);
	} else {smearCount = 0; smearElec = 0;}
	if((smearCount+smearElec)<0) hEneDeposit4->Fill(0);
	else hEneDeposit4->Fill(smearCount+smearElec);

	if(eCount5>0 || g1->Uniform()<1){
	smearCount = (int)g1->Gaus((double)eCount5,sqrt((double)eCount5));
	smearElec = (int)g1->Gaus(0,noise);
	} else {smearCount = 0; smearElec = 0;}
	if((smearCount+smearElec)<0) hEneDeposit5->Fill(0);
	else hEneDeposit5->Fill(smearCount+smearElec);
    }
  }


  double brmin = 4000;
  double brmax = 30000;
  double rmin = 15000;
  double rmax = 30000;
  //double rmin = 7000;
  //double rmax = 20000;
/*
  TF1 *fit5 = new TF1("fit5","expo");
  fit5->SetRange(brmin,brmax);
  hEneDeposit5->Fit("fit5","r");
  TF1 *fit5e = new TF1("fit5e","TMath::Exp([0]+[1]*x)");
  fit5e->SetLineColor(kMagenta);
  fit5e->SetRange(0,brmax);
  fit5e->SetParameter(0,fit5->GetParameter(0));
  fit5e->SetParameter(1,fit5->GetParameter(1));


  TF1 *fit4 = new TF1("fit4","expo");
  fit4->SetRange(rmin,rmax);
  hEneDeposit4->Fit("fit4","r");
  TF1 *fit4e = new TF1("fit4e","TMath::Exp([0]+[1]*x)");
  fit4e->SetLineColor(kBlue);
  fit4e->SetRange(0,brmax);
  fit4e->SetParameter(0,fit4->GetParameter(0));
  fit4e->SetParameter(1,fit4->GetParameter(1));

  TF1 *fit3 = new TF1("fit3","expo");
  fit3->SetRange(rmin,rmax);
  hEneDeposit3->Fit("fit3","r");
  TF1 *fit3e = new TF1("fit3e","TMath::Exp([0]+[1]*x)");
  fit3e->SetLineColor(kGreen);
  fit3e->SetRange(0,brmax);
  fit3e->SetParameter(0,fit3->GetParameter(0));
  fit3e->SetParameter(1,fit3->GetParameter(1));

  TF1 *fit2 = new TF1("fit2","expo");
  fit2->SetRange(rmin,rmax);
  hEneDeposit2->Fit("fit2","r");
  TF1 *fit2e = new TF1("fit2e","TMath::Exp([0]+[1]*x)");
  fit2e->SetLineColor(kRed);
  fit2e->SetRange(0,brmax);
  fit2e->SetParameter(0,fit2->GetParameter(0));
  fit2e->SetParameter(1,fit2->GetParameter(1));

  TF1 *fit1 = new TF1("fit1","expo");
  fit1->SetRange(rmin,rmax);
  hEneDeposit1->Fit("fit1","r");
  TF1 *fit1e = new TF1("fit1e","TMath::Exp([0]+[1]*x)");
  fit1e->SetLineColor(kBlack);
  fit1e->SetRange(0,brmax);
  fit1e->SetParameter(0,fit1->GetParameter(0));
  fit1e->SetParameter(1,fit1->GetParameter(1));

  double bincon;
  double bincen;
  double fitcon;
  for(int m=400;m<nbins;m++){
  	bincon = hEneDeposit5->GetBinContent(m);
	bincen = (double)hEneDeposit5->GetBinCenter(m);
	fitcon = TMath::Exp(fit5->GetParameter(0)+fit5->GetParameter(1)*bincen);
	if(bincon < fitcon){
		cout << "bin5 drops below fit5 at " << bincen*10/1000 << " keV" << endl;
		cout << "bin5 content: " << bincon << ", fit5 content: " << fitcon << endl;
		break;
	}
  }
  for(int m=400;m<nbins;m++){
  	bincon = hEneDeposit4->GetBinContent(m);
	bincen = (double)hEneDeposit4->GetBinCenter(m);
	fitcon = TMath::Exp(fit4->GetParameter(0)+fit4->GetParameter(1)*bincen);
	if(bincon < fitcon){
		cout << "bin4 drops below fit4 at " << bincen*10/1000 << " keV" << endl;
		cout << "bin4 content: " << bincon << ", fit4 content: " << fitcon << endl;
		break;
	}
  }
  for(int m=400;m<nbins;m++){
  	bincon = hEneDeposit3->GetBinContent(m);
	bincen = (double)hEneDeposit3->GetBinCenter(m);
	fitcon = TMath::Exp(fit3->GetParameter(0)+fit3->GetParameter(1)*bincen);
	if(bincon < fitcon){
		cout << "bin3 drops below fit3 at " << bincen*10/1000 << " keV" << endl;
		cout << "bin3 content: " << bincon << ", fit3 content: " << fitcon << endl;
		break;
	}
  }
  for(int m=400;m<nbins;m++){
  	bincon = hEneDeposit2->GetBinContent(m);
	bincen = (double)hEneDeposit2->GetBinCenter(m);
	fitcon = TMath::Exp(fit2->GetParameter(0)+fit2->GetParameter(1)*bincen);
	if(bincon < fitcon){
		cout << "bin2 drops below fit2 at " << bincen*10/1000 << " keV" << endl;
		cout << "bin2 content: " << bincon << ", fit2 content: " << fitcon << endl;
		break;
	}
  }
  for(int m=400;m<nbins;m++){
  	bincon = hEneDeposit1->GetBinContent(m);
	bincen = (double)hEneDeposit1->GetBinCenter(m);
	fitcon = TMath::Exp(fit1->GetParameter(0)+fit1->GetParameter(1)*bincen);
	if(bincon < fitcon){
		cout << "bin1 drops below fit1 at " << bincen*10/1000 << " keV" << endl;
		cout << "bin1 content: " << bincon << ", fit1 content: " << fitcon << endl;
		break;
	}
  }
*/
  hEneDeposit5->SetLineColor(kMagenta);
  hEneDeposit5->GetXaxis()->SetTitle(xTitle);
  hEneDeposit5->GetYaxis()->SetTitle("Bin Members");
  hEneDeposit5->SetTitle("Electron-Hole Pairs Generated in 5-layer Si stack, "+absThick+" absorber, " + ene);

  hEneDeposit4->SetLineColor(kBlue);
  hEneDeposit3->SetLineColor(kGreen);
  hEneDeposit2->SetLineColor(kRed);
  hEneDeposit1->SetLineColor(kBlack);

  TCanvas *c1 = new TCanvas("c1","c1",0,400,600,300);  

  hEneDeposit5->Draw();
  hEneDeposit4->Draw("same");
  hEneDeposit3->Draw("same");
  hEneDeposit2->Draw("same");
  hEneDeposit1->Draw("same");
//  fit5e->Draw("same");  
//  fit4e->Draw("same");  
//  fit3e->Draw("same");  
//  fit2e->Draw("same");  
//  fit1e->Draw("same");  

  TLegend *leg = new TLegend(0.6,0.6,0.85,0.85);
  leg->AddEntry(hEneDeposit1,"Layer 1","l");
  leg->AddEntry(hEneDeposit2,"Layer 2","l");
  leg->AddEntry(hEneDeposit3,"Layer 3","l");
  leg->AddEntry(hEneDeposit4,"Layer 4","l");
  leg->AddEntry(hEneDeposit5,"Layer 5","l");
//  leg->AddEntry(fit1e, "Background Fit, L1","l");
//  leg->AddEntry(fit2e, "Background Fit, L2","l");
//  leg->AddEntry(fit3e, "Background Fit, L3","l");
//  leg->AddEntry(fit4e, "Background Fit, L4","l");
//  leg->AddEntry(fit5e, "Background Fit, L5","l");
  leg->Draw("same");

  c1->Update();
  
  out->Write();

  return hEneDeposit5;
  }
