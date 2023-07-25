#include "TCanvas.h"
#include "TTree.h"
#include "TFile.h"
#include "TF1.h"

void MuonPMTHit(int nBin, int lowBin, int upBin, int fitLow, int fitHigh){

  TChain ch("Events");
   ch.Add("/media/ryan/Storage/computing/mqFullSim/data/R97/Close5p7/MilliQan.root");

  TH1F *hMECount = new TH1F("hMECount","Photoelectrons Detected Per Incident Muon, FarR97",nBin,lowBin,upBin);
  hMECount->GetXaxis()->SetTitle("Number of Photoelectrons Detected");
  hMECount->GetYaxis()->SetTitle("Bin Members");

  TCanvas *c1 = new TCanvas("c1","c1",0,400,600,300);
  ch.Draw("NbOfPMTHits>>hMECount");
//  TF1 *fit = new TF1("fit","gaus");
//  fit->SetRange(fitLow,fitHigh);
//  hMECount->Fit("fit","r");
//  fit->SetLineColor(kRed);
  
  //fit->Draw("same");
}
