#include "TCanvas.h"
#include "TTree.h"
#include "TFile.h"

void EDep2(){
    TFile *fproton = new TFile("/media/schmitz/Storage/computing/beamRadSim/data/proton/BeamRad.root");
    TFile *felectron = new TFile("/media/schmitz/Storage/computing/beamRadSim/data/electron/BeamRad.root");
    TFile *fbeta = new TFile("/media/schmitz/Storage/computing/beamRadSim/data/beta/BeamRad.root");

    TTree *h1 = (TTree*)fproton->Get("Events");
    TTree *h2 = (TTree*)felectron->Get("Events");
    TTree *h3 = (TTree*)fbeta->Get("Events");

  //TH1F *hMEDep = new TH1F("hMEDep","Final Energy, 10 keV gammas",70,0,3.5);
  //hMEDep->GetXaxis()->SetTitle("Energy Deposited (MeV)");
  //hMEDep->GetYaxis()->SetTitle("Bin Members");

//  TH1F *hp = (TH1F*)gDirectory->Get("htemp1");
  //TH1F *he = (TH1F*)gDirectory->Get("htemp2");
  gStyle->SetOptStat(0);
  TCanvas *c1 = new TCanvas("c1","c1",0,400,600,300);
  h1->Draw("Edep_MeV_Si2>>htemp(100,0,100)");
  ((TH1F*)(gPad->GetListOfPrimitives()->At(0)))->SetTitle("Energy Deposited in 50um Bulk Layer");
  ((TH1F*)(gPad->GetListOfPrimitives()->At(0)))->GetXaxis()->SetTitle("Energy Deposited (MeV)");
  ((TH1F*)(gPad->GetListOfPrimitives()->At(0)))->SetMinimum(0.5);
  h2->Draw("Edep_MeV_Si2>>htemp2(100,0,100)","","SAME"); //htemp->SetLineColor(kRed);
  h3->Draw("Edep_MeV_Si2>>htemp3(100,0,100)","","SAME"); //htemp->SetLineColor(kRed);
  ((TH1F*)(gPad->GetListOfPrimitives()->At(0)))->SetLineColor(kRed);
  ((TH1F*)(gPad->GetListOfPrimitives()->At(2)))->SetLineColor(kGreen);
  ((TH1F*)(gPad->GetListOfPrimitives()->At(0)))->SetLineWidth(2);
  ((TH1F*)(gPad->GetListOfPrimitives()->At(1)))->SetLineWidth(2);
  ((TH1F*)(gPad->GetListOfPrimitives()->At(2)))->SetLineWidth(2);
  gPad->GetListOfPrimitives()->Print();
  c1->SetLogy();
}
