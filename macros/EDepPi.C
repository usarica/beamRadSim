#include "TCanvas.h"
#include "TTree.h"
#include "TFile.h"

void EDepPi(){
    TFile *fproton = new TFile("/media/schmitz/Storage/computing/beamRadSim/data/proton/BeamRad.root");
    TFile *fpi0p1 = new TFile("/media/schmitz/Storage/computing/beamRadSim/data/pion/0p1/BeamRad.root");
    TFile *fpi0p2 = new TFile("/media/schmitz/Storage/computing/beamRadSim/data/pion/0p2/BeamRad.root");
    TFile *fpi0p5 = new TFile("/media/schmitz/Storage/computing/beamRadSim/data/pion/0p5/BeamRad.root");
    TFile *fpi1 = new TFile("/media/schmitz/Storage/computing/beamRadSim/data/pion/1/BeamRad.root");
    //TFile *fpi2 = new TFile("/media/schmitz/Storage/computing/beamRadSim/data/pion/2/BeamRad.root");
    TFile *fpi5 = new TFile("/media/schmitz/Storage/computing/beamRadSim/data/pion/5/BeamRad.root");
    //TFile *fpi10 = new TFile("/media/schmitz/Storage/computing/beamRadSim/data/pion/10/BeamRad.root");
    TFile *fpi25 = new TFile("/media/schmitz/Storage/computing/beamRadSim/data/pion/25/BeamRad.root");
    //TFile *fpi50 = new TFile("/media/schmitz/Storage/computing/beamRadSim/data/pion/50/BeamRad.root");
    TFile *fpi120 = new TFile("/media/schmitz/Storage/computing/beamRadSim/data/pion/120/BeamRad.root");

    TTree *h1 = (TTree*)fproton->Get("Events");
    TTree *h2 = (TTree*)fpi0p1->Get("Events");
    TTree *h3 = (TTree*)fpi0p2->Get("Events");
    TTree *h4 = (TTree*)fpi0p5->Get("Events");
    TTree *h5 = (TTree*)fpi1->Get("Events");
//    TTree *h6 = (TTree*)fpi2->Get("Events");
    TTree *h7 = (TTree*)fpi5->Get("Events");
//    TTree *h8 = (TTree*)fpi10->Get("Events");
    TTree *h9 = (TTree*)fpi25->Get("Events");
//    TTree *h10 = (TTree*)fpi50->Get("Events");
    TTree *h11 = (TTree*)fpi120->Get("Events");

  //TH1F *hMEDep = new TH1F("hMEDep","Final Energy, 10 keV gammas",70,0,3.5);
  //hMEDep->GetXaxis()->SetTitle("Energy Deposited (MeV)");
  //hMEDep->GetYaxis()->SetTitle("Bin Members");

//  TH1F *hp = (TH1F*)gDirectory->Get("htemp1");
  //TH1F *he = (TH1F*)gDirectory->Get("htemp2");
  gStyle->SetOptStat(0);
  TCanvas *c1 = new TCanvas("c1","c1",0,400,600,300);
  h1->Draw("Edep_MeV_Si1>>htemp(50,0,100)");
  ((TH1F*)(gPad->GetListOfPrimitives()->At(0)))->SetTitle("Energy Deposited in 50um Bulk Layer");
  ((TH1F*)(gPad->GetListOfPrimitives()->At(0)))->GetXaxis()->SetTitle("Energy Deposited (MeV)");
  ((TH1F*)(gPad->GetListOfPrimitives()->At(0)))->SetMinimum(0.5);
  ((TH1F*)(gPad->GetListOfPrimitives()->At(0)))->SetLineColor(kRed);
  h2->Draw("Edep_MeV_Si1>>htemp2(50,0,100)","","SAME"); //htemp->SetLineColor(kRed);
  ((TH1F*)(gPad->GetListOfPrimitives()->At(1)))->SetLineColor(kBlue);
  h3->Draw("Edep_MeV_Si1>>htemp3(50,0,100)","","SAME"); //htemp->SetLineColor(kRed);
  ((TH1F*)(gPad->GetListOfPrimitives()->At(2)))->SetLineColor(kGreen+1);
  h4->Draw("Edep_MeV_Si1>>htemp4(50,0,100)","","SAME"); //htemp->SetLineColor(kRed);
  gPad->GetListOfPrimitives()->Print();
  ((TH1F*)(gPad->GetListOfPrimitives()->At(3)))->SetLineColor(kBlack);
  h5->Draw("Edep_MeV_Si1>>htemp5(50,0,100)","","SAME"); //htemp->SetLineColor(kRed);
//  h6->Draw("Edep_MeV_Si1>>htemp6(50,0,100)","","SAME"); //htemp->SetLineColor(kRed);
  h7->Draw("Edep_MeV_Si1>>htemp7(50,0,100)","","SAME"); //htemp->SetLineColor(kRed);
//  h8->Draw("Edep_MeV_Si1>>htemp8(50,0,100)","","SAME"); //htemp->SetLineColor(kRed);
  h9->Draw("Edep_MeV_Si1>>htemp9(50,0,100)","","SAME"); //htemp->SetLineColor(kRed);
//  h10->Draw("Edep_MeV_Si1>>htemp10(50,0,100)","","SAME"); //htemp->SetLineColor(kRed);
  h11->Draw("Edep_MeV_Si1>>htemp11(50,0,100)","","SAME"); //htemp->SetLineColor(kRed);
  ((TH1F*)(gPad->GetListOfPrimitives()->At(4)))->SetLineColor(kRed+2);
  ((TH1F*)(gPad->GetListOfPrimitives()->At(5)))->SetLineColor(kAzure+2);
  ((TH1F*)(gPad->GetListOfPrimitives()->At(6)))->SetLineColor(kCyan);
  ((TH1F*)(gPad->GetListOfPrimitives()->At(7)))->SetLineColor(kCyan+2);
  ((TH1F*)(gPad->GetListOfPrimitives()->At(0)))->SetLineWidth(2);
  ((TH1F*)(gPad->GetListOfPrimitives()->At(1)))->SetLineWidth(2);
  ((TH1F*)(gPad->GetListOfPrimitives()->At(2)))->SetLineWidth(2);
  ((TH1F*)(gPad->GetListOfPrimitives()->At(3)))->SetLineWidth(2);
  ((TH1F*)(gPad->GetListOfPrimitives()->At(4)))->SetLineWidth(2);
  ((TH1F*)(gPad->GetListOfPrimitives()->At(5)))->SetLineWidth(2);
  ((TH1F*)(gPad->GetListOfPrimitives()->At(6)))->SetLineWidth(2);
  ((TH1F*)(gPad->GetListOfPrimitives()->At(7)))->SetLineWidth(2);
  TLegend* leg = new TLegend(0.1,0.1,0.3,0.3);
  leg->AddEntry(((TH1F*)(gPad->GetListOfPrimitives()->At(0))),"Proton 120 GeV");
  leg->AddEntry(((TH1F*)(gPad->GetListOfPrimitives()->At(1))),"Pion 120 GeV");
//  leg->AddEntry(((TH1F*)(gPad->GetListOfPrimitives()->At(2))),"Pion 50 GeV");
  leg->AddEntry(((TH1F*)(gPad->GetListOfPrimitives()->At(2))),"Pion 25 GeV");
//  leg->AddEntry(((TH1F*)(gPad->GetListOfPrimitives()->At(4))),"Pion 10 GeV");
  leg->AddEntry(((TH1F*)(gPad->GetListOfPrimitives()->At(3))),"Pion 5 GeV");
//  leg->AddEntry(((TH1F*)(gPad->GetListOfPrimitives()->At(6))),"Pion 2 GeV");
  leg->AddEntry(((TH1F*)(gPad->GetListOfPrimitives()->At(4))),"Pion 1 GeV");
  leg->AddEntry(((TH1F*)(gPad->GetListOfPrimitives()->At(5))),"Pion 0.5 GeV");
  leg->AddEntry(((TH1F*)(gPad->GetListOfPrimitives()->At(6))),"Pion 0.2 GeV");
  leg->AddEntry(((TH1F*)(gPad->GetListOfPrimitives()->At(7))),"Pion 0.1 GeV");
  c1->SetLogy();
  leg->Draw();
}
