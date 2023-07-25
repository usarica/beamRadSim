#include "TCanvas.h"
#include "TTree.h"
#include "TFile.h"

void EDepPiSimp(){
    TFile *fproton = new TFile("/media/schmitz/Storage/computing/beamRadSim/data/proton/120/BeamRad.root");
    TFile *fproton10 = new TFile("/media/schmitz/Storage/computing/beamRadSim/data/proton/BeamRad.root");
    TFile *fpi120 = new TFile("/media/schmitz/Storage/computing/beamRadSim/data/pion/120/BeamRad.root");
    TFile *fpi10 = new TFile("/media/schmitz/Storage/computing/beamRadSim/data/pion/1/BeamRad.root");
    TFile *fpi0p5 = new TFile("/media/schmitz/Storage/computing/beamRadSim/data/pion/BeamRad.root");

    TTree *h1 = (TTree*)fproton->Get("Events");
    TTree *h2 = (TTree*)fproton10->Get("Events");
    TTree *h3 = (TTree*)fpi120->Get("Events");
    TTree *h4 = (TTree*)fpi10->Get("Events");
    TTree *h5 = (TTree*)fpi0p5->Get("Events");

  //TH1F *hMEDep = new TH1F("hMEDep","Final Energy, 10 keV gammas",70,0,3.5);
  //hMEDep->GetXaxis()->SetTitle("Energy Deposited (MeV)");
  //hMEDep->GetYaxis()->SetTitle("Bin Members");

//  TH1F *hp = (TH1F*)gDirectory->Get("htemp1");
  //TH1F *he = (TH1F*)gDirectory->Get("htemp2");
  gStyle->SetOptStat(0);
  TCanvas *c1 = new TCanvas("c1","c1",0,400,600,300);
  h1->Draw("Edep_MeV_Si1>>htemp(100,0,100)");
  ((TH1F*)(gPad->GetListOfPrimitives()->At(0)))->SetTitle("Energy Deposited, 50um LGAD, MTD Bulk Stack");
  ((TH1F*)(gPad->GetListOfPrimitives()->At(0)))->GetXaxis()->SetTitle("Energy Deposited (MeV)");
  ((TH1F*)(gPad->GetListOfPrimitives()->At(0)))->GetYaxis()->SetTitle("Probability to Deposit");
  ((TH1F*)(gPad->GetListOfPrimitives()->At(0)))->SetMinimum(0.5);
  h2->Draw("Edep_MeV_Si1>>htemp2(100,0,100)","","SAME"); //htemp->SetLineColor(kRed);
  h3->Draw("Edep_MeV_Si1>>htemp3(100,0,100)","","SAME"); //htemp->SetLineColor(kRed);
  h4->Draw("Edep_MeV_Si1>>htemp4(100,0,100)","","SAME"); //htemp->SetLineColor(kRed);
  h5->Draw("Edep_MeV_Si1>>htemp5(100,0,100)","","SAME"); //htemp->SetLineColor(kRed);
  TH1F* hi1 = (TH1F*)((TH1F*)(gPad->GetListOfPrimitives()->At(0)))->GetCumulative();
  TH1F* hi2 = (TH1F*)((TH1F*)(gPad->GetListOfPrimitives()->At(1)))->GetCumulative();
  TH1F* hi3 = (TH1F*)((TH1F*)(gPad->GetListOfPrimitives()->At(2)))->GetCumulative();
  TH1F* hi4 = (TH1F*)((TH1F*)(gPad->GetListOfPrimitives()->At(3)))->GetCumulative();
  TH1F* hi5 = (TH1F*)((TH1F*)(gPad->GetListOfPrimitives()->At(4)))->GetCumulative();
  Double_t he1 = hi1->GetMaximum();
  Double_t he2 = hi2->GetMaximum();
  Double_t he3 = hi3->GetMaximum();
  Double_t he4 = hi4->GetMaximum();
  Double_t he5 = hi5->GetMaximum();
  cout << he1 << endl;
  cout << he2 << endl;
  cout << he3 << endl;
  cout << he4 << endl;
  cout << he5 << endl;
  hi1->Scale(1.0/he1);
  hi2->Scale(1.0/he2);
  hi3->Scale(1.0/he3);
  hi4->Scale(1.0/he4);
  hi5->Scale(1.0/he5);

  for(int i=0 ; i<hi1->GetNbinsX()+1 ; i++) {
	  hi1->SetBinContent(i,1-hi1->GetBinContent(i));
	  hi2->SetBinContent(i,1-hi2->GetBinContent(i));
	  hi3->SetBinContent(i,1-hi3->GetBinContent(i));
	  hi4->SetBinContent(i,1-hi4->GetBinContent(i));
	  hi5->SetBinContent(i,1-hi5->GetBinContent(i));
  }

  hi1->SetLineColor(kBlack);
  hi2->SetLineColor(kRed);
  hi3->SetLineColor(kGreen+1);
  hi4->SetLineColor(kBlue);
  hi5->SetLineColor(kRed+2);
  hi1->SetLineWidth(2);
  hi2->SetLineWidth(2);
  hi3->SetLineWidth(2);
  hi4->SetLineWidth(2);
  hi5->SetLineWidth(2);
  c1->SetLogy();
  
  hi1->Draw();
  hi2->Draw("same");
  hi3->Draw("same");
  hi4->Draw("same");
  hi5->Draw("same");
  TLegend* leg = new TLegend(0.1,0.1,0.3,0.3);
  leg->AddEntry(hi1,"Proton 120 GeV");
  leg->AddEntry(hi2,"Proton 10 GeV");
  leg->AddEntry(hi3,"Pion 120 GeV");
  leg->AddEntry(hi4,"Pion 1 GeV");
  leg->AddEntry(hi5,"Pion 0.5 GeV");
  leg->SetBorderSize(0);
  leg->Draw();
}
