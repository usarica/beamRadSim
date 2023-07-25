#include "TCanvas.h"
#include "TTree.h"
#include "TFile.h"

void EDepPiProb(){
    TFile *fpi120 = new TFile("/media/schmitz/Storage/computing/beamRadSim/data/pion/120/BeamRad.root");
    TFile *fpi50 = new TFile("/media/schmitz/Storage/computing/beamRadSim/data/pion/50/BeamRad.root");
    TFile *fpi10 = new TFile("/media/schmitz/Storage/computing/beamRadSim/data/pion/10/BeamRad.root");
    TFile *fpi2 = new TFile("/media/schmitz/Storage/computing/beamRadSim/data/proton/120/BeamRad.root");
    TFile *fpi0p5 = new TFile("/media/schmitz/Storage/computing/beamRadSim/data/old/proton/BeamRad.root");
//    TFile *fpi0p1 = new TFile("/media/schmitz/Storage/computing/beamRadSim/data/old/electron/BeamRad.root");
//    TFile *fpi2 = new TFile("/media/schmitz/Storage/computing/beamRadSim/data/pion/2/BeamRad.root");
//    TFile *fpi0p5 = new TFile("/media/schmitz/Storage/computing/beamRadSim/data/pion/0p5/BeamRad.root");
//    TFile *fpi0p1 = new TFile("/media/schmitz/Storage/computing/beamRadSim/data/pion/0p1/BeamRad.root");

    TTree *h1 = (TTree*)fpi120->Get("Events");
    TTree *h2 = (TTree*)fpi50->Get("Events");
    TTree *h3 = (TTree*)fpi10->Get("Events");
    TTree *h4 = (TTree*)fpi2->Get("Events");
    TTree *h5 = (TTree*)fpi0p5->Get("Events");
    TTree *h6 = (TTree*)fpi0p1->Get("Events");

  //TH1F *hMEDep = new TH1F("hMEDep","Final Energy, 10 keV gammas",70,0,3.5);
  //hMEDep->GetXaxis()->SetTitle("Energy Deposited (MeV)");
  //hMEDep->GetYaxis()->SetTitle("Bin Members");

//  TH1F *hp = (TH1F*)gDirectory->Get("htemp1");
  //TH1F *he = (TH1F*)gDirectory->Get("htemp2");
  gStyle->SetOptStat(0);
  TCanvas *c1 = new TCanvas("c1","c1",0,400,600,300);
  h1->Draw("Edep_MeV_Si1>>htemp(200,0,100)");
  ((TH1F*)(gPad->GetListOfPrimitives()->At(0)))->SetTitle("Energy Deposited, Pions, 50um LGAD, MTD Bulk Stack");
  ((TH1F*)(gPad->GetListOfPrimitives()->At(0)))->GetXaxis()->SetTitle("Energy Deposited (MeV)");
  ((TH1F*)(gPad->GetListOfPrimitives()->At(0)))->GetYaxis()->SetTitle("Probability to Deposit");
//  ((TH1F*)(gPad->GetListOfPrimitives()->At(0)))->SetMinimum(0.5);
  h2->Draw("Edep_MeV_Si1>>htemp2(200,0,100)","","SAME"); //htemp->SetLineColor(kRed);
  h3->Draw("Edep_MeV_Si1>>htemp3(200,0,100)","","SAME"); //htemp->SetLineColor(kRed);
  h4->Draw("Edep_MeV_Si1>>htemp4(200,0,100)","","SAME"); //htemp->SetLineColor(kRed);
  h5->Draw("Edep_MeV_Si2>>htemp5(200,0,100)","","SAME"); //htemp->SetLineColor(kRed);
  h6->Draw("Edep_MeV_Si2>>htemp6(200,0,100)","","SAME"); //htemp->SetLineColor(kRed);
  TH1F* hi1 = (TH1F*)((TH1F*)(gPad->GetListOfPrimitives()->At(0)))->GetCumulative();
  TH1F* hi2 = (TH1F*)((TH1F*)(gPad->GetListOfPrimitives()->At(1)))->GetCumulative();
  TH1F* hi3 = (TH1F*)((TH1F*)(gPad->GetListOfPrimitives()->At(2)))->GetCumulative();
  TH1F* hi4 = (TH1F*)((TH1F*)(gPad->GetListOfPrimitives()->At(3)))->GetCumulative();
  TH1F* hi5 = (TH1F*)((TH1F*)(gPad->GetListOfPrimitives()->At(4)))->GetCumulative();
  TH1F* hi6 = (TH1F*)((TH1F*)(gPad->GetListOfPrimitives()->At(5)))->GetCumulative();
  Double_t he1 = hi1->GetMaximum();
  Double_t he2 = hi2->GetMaximum();
  Double_t he3 = hi3->GetMaximum();
  Double_t he4 = hi4->GetMaximum();
  Double_t he5 = hi5->GetMaximum();
  Double_t he6 = hi6->GetMaximum();
  cout << he1 << endl;
  cout << he2 << endl;
  cout << he3 << endl;
  cout << he4 << endl;
  cout << he5 << endl;
  cout << he6 << endl;
  hi1->Scale(1.0/he1);
  hi2->Scale(1.0/he2);
  hi3->Scale(1.0/he3);
  hi4->Scale(1.0/he4);
  hi5->Scale(1.0/he5);
  hi6->Scale(1.0/he6);
///*
  cout << hi1->GetMaximum()<< endl;
  cout << hi2->GetMaximum() << endl;
  cout << hi3->GetMaximum() << endl;
  cout << hi4->GetMaximum() << endl;
  cout << hi5->GetMaximum() << endl;
  cout << hi6->GetMaximum() << endl;
  for(int i=1 ; i<hi1->GetNbinsX()+1 ; i++) {
	  hi1->SetBinContent(i,1-hi1->GetBinContent(i));
	  hi2->SetBinContent(i,1-hi2->GetBinContent(i));
	  hi3->SetBinContent(i,1-hi3->GetBinContent(i));
	  hi4->SetBinContent(i,1-hi4->GetBinContent(i));
	  hi5->SetBinContent(i,1-hi5->GetBinContent(i));
	  hi6->SetBinContent(i,1-hi6->GetBinContent(i));
  }
//*/
  hi1->SetLineColor(kBlack);
  hi2->SetLineColor(kRed);
  hi3->SetLineColor(kGreen+1);
  hi4->SetLineColor(kBlue);
  hi5->SetLineColor(kRed+2);
  hi6->SetLineColor(kCyan+2);
  hi1->SetLineWidth(2);
  hi2->SetLineWidth(2);
  hi3->SetLineWidth(2);
  hi4->SetLineWidth(2);
  hi5->SetLineWidth(2);
  hi6->SetLineWidth(2);
  c1->SetLogy();
  
  hi1->Draw();
  hi2->Draw("same");
  hi3->Draw("same");
  hi4->Draw("same");
  hi5->Draw("same");
  hi6->Draw("same");
  TLegend* leg = new TLegend(0.1,0.1,0.3,0.3);
  leg->AddEntry(hi1,"120 GeV");
  leg->AddEntry(hi2,"50 GeV");
  leg->AddEntry(hi3,"10 GeV");
  leg->AddEntry(hi4,"2 GeV");
  leg->AddEntry(hi5,"0.5 GeV");
  leg->AddEntry(hi6,"0.1 GeV");
  leg->SetBorderSize(0);
  leg->Draw();
}
