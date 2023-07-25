#include "TCanvas.h"
#include "TTree.h"
#include "TFile.h"

void EDepPiProbAll(){
    TFile *fpinut100 = new TFile("/media/schmitz/Storage/computing/beamRadSim/data/pion/nut/100/BeamRad.root");
    TFile *fpinut10 = new TFile("/media/schmitz/Storage/computing/beamRadSim/data/pion/nut/10/BeamRad.root");
    TFile *fpinut1 = new TFile("/media/schmitz/Storage/computing/beamRadSim/data/pion/nut/1/BeamRad.root");
    TFile *fpinut0p1 = new TFile("/media/schmitz/Storage/computing/beamRadSim/data/pion/nut/0p1/BeamRad.root");
    TFile *fpino100 = new TFile("/media/schmitz/Storage/computing/beamRadSim/data/pion/nonut/100/BeamRad.root");
    TFile *fpino10 = new TFile("/media/schmitz/Storage/computing/beamRadSim/data/pion/nonut/10/BeamRad.root");
    TFile *fpino1 = new TFile("/media/schmitz/Storage/computing/beamRadSim/data/pion/nonut/1/BeamRad.root");
    TFile *fpino0p1 = new TFile("/media/schmitz/Storage/computing/beamRadSim/data/pion/nonut/0p1/BeamRad.root");

    TTree *h1 = (TTree*)fpinut100->Get("Events");
    TTree *h2 = (TTree*)fpinut10->Get("Events");
    TTree *h3 = (TTree*)fpinut1->Get("Events");
    TTree *h4 = (TTree*)fpinut0p1->Get("Events");
    TTree *h5 = (TTree*)fpino100->Get("Events");
    TTree *h6 = (TTree*)fpino10->Get("Events");
    TTree *h7 = (TTree*)fpino1->Get("Events");
    TTree *h8 = (TTree*)fpino0p1->Get("Events");

  //TH1F *hMEDep = new TH1F("hMEDep","Final Energy, 10 keV gammas",70,0,3.5);
  //hMEDep->GetXaxis()->SetTitle("Energy Deposited (MeV)");
  //hMEDep->GetYaxis()->SetTitle("Bin Members");

//  TH1F *hp = (TH1F*)gDirectory->Get("htemp1");
  //TH1F *he = (TH1F*)gDirectory->Get("htemp2");
  gStyle->SetOptStat(0);
  TCanvas *c1 = new TCanvas("c1","c1",0,400,600,300);
  h1->Draw("Edep_MeV_Si1>>htemp(50,0,100)");
  ((TH1F*)(gPad->GetListOfPrimitives()->At(0)))->SetTitle("Energy Deposited, Pions, with/without metal nut");
  ((TH1F*)(gPad->GetListOfPrimitives()->At(0)))->GetXaxis()->SetTitle("Energy Deposited (MeV)");
  ((TH1F*)(gPad->GetListOfPrimitives()->At(0)))->GetYaxis()->SetTitle("Probability to Deposit");
//  ((TH1F*)(gPad->GetListOfPrimitives()->At(0)))->SetMinimum(0.5);

  h2->Draw("Edep_MeV_Si1>>htemp2(50,0,100)","","SAME"); //htemp->SetLineColor(kRed);
  h3->Draw("Edep_MeV_Si1>>htemp3(50,0,100)","","SAME"); //htemp->SetLineColor(kRed);
  h4->Draw("Edep_MeV_Si1>>htemp4(50,0,100)","","SAME"); //htemp->SetLineColor(kRed);
  h5->Draw("Edep_MeV_Si1>>htemp5(50,0,100)","","SAME"); //htemp->SetLineColor(kRed);
  h6->Draw("Edep_MeV_Si1>>htemp6(50,0,100)","","SAME"); //htemp->SetLineColor(kRed);
  h7->Draw("Edep_MeV_Si1>>htemp7(50,0,100)","","SAME"); //htemp->SetLineColor(kRed);
  h8->Draw("Edep_MeV_Si1>>htemp8(50,0,100)","","SAME"); //htemp->SetLineColor(kRed);
  TH1D* hi1 = (TH1D*)gDirectory->Get("htemp");
  TH1D* hi2 = (TH1D*)gDirectory->Get("htemp2");
  TH1D* hi3 = (TH1D*)gDirectory->Get("htemp3");
  TH1D* hi4 = (TH1D*)gDirectory->Get("htemp4");
  TH1D* hi5 = (TH1D*)gDirectory->Get("htemp5");
  TH1D* hi6 = (TH1D*)gDirectory->Get("htemp6");
  TH1D* hi7 = (TH1D*)gDirectory->Get("htemp7");
  TH1D* hi8 = (TH1D*)gDirectory->Get("htemp8");
///*
  hi1->SetLineColor(kBlack);
  hi2->SetLineColor(kRed);
  
  hi1->SetLineColor(kBlue);
  hi2->SetLineColor(kBlue+1);
  hi3->SetLineColor(kBlue+2);
  hi4->SetLineColor(kBlue+3);
  hi5->SetLineColor(kRed);
  hi6->SetLineColor(kRed+1);
  hi7->SetLineColor(kRed+2);
  hi8->SetLineColor(kRed+3);

  hi1->SetLineWidth(2);
  hi2->SetLineWidth(2);
  hi3->SetLineWidth(2);
  hi4->SetLineWidth(2);
  hi5->SetLineWidth(2);
  hi6->SetLineWidth(2);
  hi7->SetLineWidth(2);
  hi8->SetLineWidth(2);
  c1->SetLogy();
  
  hi1->Draw();
  hi2->Draw("same");
  hi3->Draw("same");
  hi4->Draw("same");
  hi5->Draw("same");
  hi6->Draw("same");
  hi7->Draw("same");
  hi8->Draw("same");
  TLegend* leg = new TLegend(0.1,0.1,0.3,0.3);
  leg->AddEntry(hi1,"With Nut");
  leg->AddEntry(hi2,"No Nut");
  leg->SetBorderSize(0);
  leg->Draw();
}
