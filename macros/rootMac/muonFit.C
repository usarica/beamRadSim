#include "TROOT.h"
#include "TApplication.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TH1F.h"
#include "TMath.h"
#include "TF1.h"
#include "Math/MinimizerOptions.h"
#include "TStyle.h"
#include "TSystem.h"
#include "TString.h"
#include "TLine.h"

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstring>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <cmath>

void muonFit(double rMin, double rMax) {
	gROOT->SetStyle("Plain");
	gStyle->SetOptStat("");
	char temp[200], temp2[200];
	
	const int chanTot = 3;
	const int chanNum = 0;
	const int fileNum = 2;
	
//	int bins = 100;
//	/int histMax = 400;
	TString filePath = "/media/ryan/Storage/computing/mqFullSim/data/R97/muonTriggerCorrected/Close5p7/MilliQanMuonPE.root";	
	//TString filePath = "/media/ryan/Storage/computing/mqFullSim/data/R97/Far54p3/MilliQan.root";	
	TFile *in = new TFile(filePath);
	//TH1F* hist = (TH1F*)in->Get("NbOfPMTHits");
	//TH1I* hist = (TH1I*)in->Get("NbOfPMTHits");
	TH1F* hist = (TH1F*)in->Get("hmphotReal");
	int evTot=hist->GetEntries();
	double tempArea[chanTot], tempAreaErr[chanTot], area[fileNum][10000], areaErr[fileNum][10000];
	double pmtPE = 0.0548; //slope: nVs/PE
	TCanvas *c1 = new TCanvas("c1","c1",0,0,1000,500);		c1->cd();
	TF1 *fit;
///		sprintf(temp,"hist[%d]",i);
		hist->Sumw2();
		hist->GetXaxis()->SetTitle("Photoelectrons Detected [PE]");
		hist->GetYaxis()->SetTitle("Fraction of Counts");
		
//		sprintf(temp2,"NbOfPMTHits>>%s",temp);		////NEED CORRECT tBranch NAME (replace only Edep_MeV)
		hist->Draw("hist e1");
		
//		hist->Scale(1./evTot);
		hist->SetLineColor(kBlue);
		
//		temp="fit";
		fit = new TF1("fit","gaus");
		fit->SetRange(rMin,rMax);
		hist->Fit("fit","r");
		fit->SetLineColor(kRed);
	
//	hist->Draw("hist e1");
	fit->Draw("same");
	c1->Update();
	
	TLegend *leg = new TLegend(0.6,0.6,0.85,0.85);
	leg->AddEntry(fit,"Muon Fit","l");
	leg->AddEntry((TObject*)0, TString::Format("    %.0f #pm %.0f PE",fit->GetParameter(1),fit->GetParameter(2)),"");
//	leg->Draw("same");
	c1->Update();
	
	cout << "\nPeak location percentage:\n";
	cout << fit->GetParameter(1) << " +/- " << TMath::Power(TMath::Power(fit->GetParameter(2)/fit->GetParameter(1),2),0.5)/fit->GetParameter(1) << "\n\n";
}	
	
