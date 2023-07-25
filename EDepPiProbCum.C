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
  h1->Draw("Edep_MeV_Si1>>htemp(200,0,100)");
  ((TH1F*)(gPad->GetListOfPrimitives()->At(0)))->SetTitle("Energy Deposited, Pions, with/without metal nut");
  ((TH1F*)(gPad->GetListOfPrimitives()->At(0)))->GetXaxis()->SetTitle("Energy Deposited (MeV)");
  ((TH1F*)(gPad->GetListOfPrimitives()->At(0)))->GetYaxis()->SetTitle("Probability to Deposit");
//  ((TH1F*)(gPad->GetListOfPrimitives()->At(0)))->SetMinimum(0.5);

  h2->Draw("Edep_MeV_Si1>>htemp2(200,0,100)","","SAME"); //htemp->SetLineColor(kRed);
  h3->Draw("Edep_MeV_Si1>>htemp3(200,0,100)","","SAME"); //htemp->SetLineColor(kRed);
  h4->Draw("Edep_MeV_Si1>>htemp4(200,0,100)","","SAME"); //htemp->SetLineColor(kRed);
  h5->Draw("Edep_MeV_Si1>>htemp5(200,0,100)","","SAME"); //htemp->SetLineColor(kRed);
  h6->Draw("Edep_MeV_Si1>>htemp6(200,0,100)","","SAME"); //htemp->SetLineColor(kRed);
  h7->Draw("Edep_MeV_Si1>>htemp7(200,0,100)","","SAME"); //htemp->SetLineColor(kRed);
  h8->Draw("Edep_MeV_Si1>>htemp8(200,0,100)","","SAME"); //htemp->SetLineColor(kRed);
//  TH1F* hi1 = (TH1D*)gDirectory->Get("htemp2");
  TH1F* hi1 = (TH1F*)((TH1F*)(gPad->GetListOfPrimitives()->At(0)))->GetCumulative();
  TH1F* hi2 = (TH1F*)((TH1F*)(gPad->GetListOfPrimitives()->At(1)))->GetCumulative();
  TH1F* hi3 = (TH1F*)((TH1F*)(gPad->GetListOfPrimitives()->At(2)))->GetCumulative();
  TH1F* hi4 = (TH1F*)((TH1F*)(gPad->GetListOfPrimitives()->At(3)))->GetCumulative();
  TH1F* hi5 = (TH1F*)((TH1F*)(gPad->GetListOfPrimitives()->At(4)))->GetCumulative();
  TH1F* hi6 = (TH1F*)((TH1F*)(gPad->GetListOfPrimitives()->At(5)))->GetCumulative();
  TH1F* hi7 = (TH1F*)((TH1F*)(gPad->GetListOfPrimitives()->At(6)))->GetCumulative();
  TH1F* hi8 = (TH1F*)((TH1F*)(gPad->GetListOfPrimitives()->At(7)))->GetCumulative();
  Double_t he1 = hi1->GetMaximum();
  Double_t he2 = hi2->GetMaximum();
  Double_t he3 = hi3->GetMaximum();
  Double_t he4 = hi4->GetMaximum();
  Double_t he5 = hi5->GetMaximum();
  Double_t he6 = hi6->GetMaximum();
  Double_t he7 = hi7->GetMaximum();
  Double_t he8 = hi8->GetMaximum();
  cout << he1 << endl;
  cout << he2 << endl;
  cout << he3 << endl;
  cout << he4 << endl;
  cout << he5 << endl;
  cout << he6 << endl;
  cout << he7 << endl;
  cout << he8 << endl;
  hi1->Scale(1.0/he1);
  hi2->Scale(1.0/he2);
  hi3->Scale(1.0/he3);
  hi4->Scale(1.0/he4);
  hi5->Scale(1.0/he5);
  hi6->Scale(1.0/he6);
  hi7->Scale(1.0/he7);
  hi8->Scale(1.0/he8);
///*
  cout << hi1->GetMaximum()<< endl;
  cout << hi2->GetMaximum() << endl;
  cout << hi3->GetMaximum() << endl;
  cout << hi4->GetMaximum() << endl;
  cout << hi5->GetMaximum() << endl;
  cout << hi6->GetMaximum() << endl;
  cout << hi7->GetMaximum() << endl;
  cout << hi8->GetMaximum() << endl;
  for(int i=1 ; i<hi1->GetNbinsX()+1 ; i++) {
	  hi1->SetBinContent(i,1-hi1->GetBinContent(i));
	  hi2->SetBinContent(i,1-hi2->GetBinContent(i));
	  hi3->SetBinContent(i,1-hi3->GetBinContent(i));
	  hi4->SetBinContent(i,1-hi4->GetBinContent(i));
	  hi5->SetBinContent(i,1-hi5->GetBinContent(i));
	  hi6->SetBinContent(i,1-hi6->GetBinContent(i));
	  hi7->SetBinContent(i,1-hi7->GetBinContent(i));
	  hi8->SetBinContent(i,1-hi8->GetBinContent(i));
  }
//*/
  hi1->SetLineColor(kBlack);
  hi2->SetLineColor(kRed);
  
  hi1->SetLineColor(kBlue-1);
  hi2->SetLineColor(kBlue);
  hi3->SetLineColor(kBlue+1);
  hi4->SetLineColor(kBlue+2);
  hi5->SetLineColor(kRed-1);
  hi6->SetLineColor(kRed);
  hi7->SetLineColor(kRed+1);
  hi8->SetLineColor(kRed+2);

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
