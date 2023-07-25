#include "TCanvas.h"
#include "TTree.h"
#include "TFile.h"

void EDep4(){
    TFile *fproton = new TFile("/media/ryan/Storage/computing/beamRadSim/data/electron/BeamRad1mm.root");
    TFile *felectron = new TFile("/media/ryan/Storage/computing/beamRadSim/data/electron/BeamRad.root");

    TTree *h1 = (TTree*)fproton->Get("Events");
    TTree *h2 = (TTree*)felectron->Get("Events");

  //TH1F *hMEDep = new TH1F("hMEDep","Final Energy, 10 keV gammas",70,0,3.5);
  //hMEDep->GetXaxis()->SetTitle("Energy Deposited (MeV)");
  //hMEDep->GetYaxis()->SetTitle("Bin Members");

//  TH1F *hp = (TH1F*)gDirectory->Get("htemp1");
  //TH1F *he = (TH1F*)gDirectory->Get("htemp2");
  TCanvas *c1 = new TCanvas("c1","c1",0,400,600,300);
  h1->Draw("Edep_MeV_Si2>>htemp(100,0,2)");
  h2->Draw("Edep_MeV_Si2>>htemp2(100,0,2)","","SAME"); //htemp->SetLineColor(kRed);
  ((TH1F*)(gPad->GetListOfPrimitives()->At(0)))->SetLineColor(kRed);
  gPad->GetListOfPrimitives()->Print();
  c1->SetLogy();
}
