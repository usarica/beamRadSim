#include "TCanvas.h"
#include "TTree.h"
#include "TFile.h"

void EDepPiProb(TString ene){
    TFile *fpinut = new TFile("/media/schmitz/Storage/computing/beamRadSim/data/pion/nut/"+ene+"/BeamRad.root");
    TFile *fpiAlnut = new TFile("/media/schmitz/Storage/computing/beamRadSim/data/pion/Alnut/"+ene+"/BeamRad.root");
    TFile *fpino = new TFile("/media/schmitz/Storage/computing/beamRadSim/data/pion/nonut/"+ene+"/BeamRad.root");

    TTree *h1 = (TTree*)fpinut->Get("Events");
    TTree *h2 = (TTree*)fpiAlnut->Get("Events");
    TTree *h3 = (TTree*)fpino->Get("Events");

  //TH1F *hMEDep = new TH1F("hMEDep","Final Energy, 10 keV gammas",70,0,3.5);
  //hMEDep->GetXaxis()->SetTitle("Energy Deposited (MeV)");
  //hMEDep->GetYaxis()->SetTitle("Bin Members");

//  TH1F *hp = (TH1F*)gDirectory->Get("htemp1");
  //TH1F *he = (TH1F*)gDirectory->Get("htemp2");
  gStyle->SetOptStat(0);
  TCanvas *c1 = new TCanvas("c1","c1",0,400,600,300);
  h1->Draw("Edep_MeV_Si1>>htemp(10000,0,50)");
  ((TH1F*)(gPad->GetListOfPrimitives()->At(0)))->SetTitle("Energy Deposited, Pions, "+ene+" GeV");
  ((TH1F*)(gPad->GetListOfPrimitives()->At(0)))->GetXaxis()->SetTitle("Energy Deposited (MeV)");
  ((TH1F*)(gPad->GetListOfPrimitives()->At(0)))->GetYaxis()->SetTitle("Probability to Deposit");
//  ((TH1F*)(gPad->GetListOfPrimitives()->At(0)))->SetMinimum(0.5);
  h2->Draw("Edep_MeV_Si1>>htemp2(10000,0,50)","","SAME"); //htemp->SetLineColor(kRed);
  h3->Draw("Edep_MeV_Si1>>htemp3(10000,0,50)","","SAME"); //htemp->SetLineColor(kRed);
  TH1F* hi1 = (TH1F*)((TH1F*)(gPad->GetListOfPrimitives()->At(0)))->GetCumulative();
  TH1F* hi2 = (TH1F*)((TH1F*)(gPad->GetListOfPrimitives()->At(1)))->GetCumulative();
  TH1F* hi3 = (TH1F*)((TH1F*)(gPad->GetListOfPrimitives()->At(2)))->GetCumulative();
  Double_t he1 = hi1->GetMaximum();
  Double_t he2 = hi2->GetMaximum();
  Double_t he3 = hi3->GetMaximum();
  cout << he1 << endl;
  cout << he2 << endl;
  cout << he3 << endl;
  hi1->Scale(1.0/he1);
  hi2->Scale(1.0/he2);
  hi3->Scale(1.0/he3);
///*
  cout << hi1->GetMaximum()<< endl;
  cout << hi2->GetMaximum() << endl;
  cout << hi3->GetMaximum() << endl;
  for(int i=0 ; i<hi1->GetNbinsX()+1 ; i++) {
	  hi1->SetBinContent(i,1-hi1->GetBinContent(i));
	  hi2->SetBinContent(i,1-hi2->GetBinContent(i));
	  hi3->SetBinContent(i,1-hi3->GetBinContent(i));
  }
//*/
  hi1->SetLineColor(kBlack);
  hi2->SetLineColor(kRed);
  hi3->SetLineColor(kBlue);
  hi1->SetLineWidth(2);
  hi2->SetLineWidth(2);
  hi3->SetLineWidth(2);
  c1->SetLogy();
  
  hi1->Draw();
  hi2->Draw("same");
  hi3->Draw("same");
  TLegend* leg = new TLegend(0.1,0.1,0.3,0.3);
  leg->AddEntry(hi1,"Steel Nut");
  leg->AddEntry(hi2,"Al Nut");
  leg->AddEntry(hi3,"No Nut");
  leg->SetBorderSize(0);
  leg->Draw();
}
