#include "TROOT.h"
#include "TApplication.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TH1I.h"
#include "TMath.h"
#include "TF1.h"
#include "Math/MinimizerOptions.h"
#include "/media/ryan/Storage/computing/mqTestStand/include/mqROOTEvent.hh"
#include "TStyle.h"
#include "TSystem.h"
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

void fitMacro(TH1I* hist, double rMin, double rMax) {
	gROOT->SetStyle("Plain");
	gStyle->SetOptStat("");
	char temp[200], temp2[200];
	
//	const int chanTot = 3;
//	const int chanNum = 0;
//	const int fileNum = 2;
	
//	int bins = 100;
//	/int histMax = 400;
//	double rMin[fileNum] = {r1min,r2min}, rMax[fileNum] = {r1max,r2max}; /////Adjust these parameters for the fits.
	
//	TChain ch[fileNum];
	//eurROOTEvent* myROOTEvent = new eurROOTEvent();
	//ch[1].SetBranchAddress("ROOTEvent", &myROOTEvent);
	Long64_t nentries = hist->GetEntries();

//	int evTot[fileNum];
//	double tempArea[chanTot], tempAreaErr[chanTot], area[fileNum][10000], areaErr[fileNum][10000];
	double pmtPE = 0.0548; //slope: nVs/PE
	//TCanvas *c1 = new TCanvas("c1","c1",0,0,1000,500);		c1->cd();
//	TH1F *hist[fileNum];
	TF1 *fit;
//	for(int i=0; i<fileNum; i++) {
//		sprintf(temp,"hist[%d]",0);
//		hist[i] = new TH1F(temp,"", bins, 0, histMax);
		hist->Sumw2();
		hist->GetXaxis()->SetTitle("Photoelectrons Detected [PE]");
		hist->GetYaxis()->SetTitle("Fraction of Counts");
		
		hist->Scale(1./nentries);
		hist->SetLineColor(kRed);
		
		sprintf(temp,"fit");
		fit = new TF1("temp","gaus");
		fit->SetRange(rMin,rMax);
		hist->Fit("temp","r");
		fit->SetLineColor(kRed);
//	}
	
//	hist[1]->Draw("hist e1");
	//hist->Draw("hist e1 same");
	fit->Draw("same");
//	fit[1]->Draw("same");
	//hist->Update();
	
	TLegend *leg = new TLegend(0.6,0.6,0.85,0.85);
	leg->AddEntry(fit,"Muon Triggers","l");
	leg->AddEntry((TObject*)0, TString::Format("    %.0f #pm %.0f PE",fit->GetParameter(1),fit->GetParameter(2)),"");
	//leg->AddEntry(fit[1],"With foil mask","l");
	//leg->AddEntry((TObject*)0, TString::Format("    %.0f #pm %.0f PE",fit[1]->GetParameter(1),fit[1]->GetParameter(2)),"");
	leg->Draw("same");
	//c1->Update();
	
//	cout << "\nPeak location percentage:\n";
	cout << /*fit[1]->GetParameter(1)*/fit->GetParameter(1) << " +/- " << TMath::Power(TMath::Power(fit->GetParameter(2)/fit->GetParameter(1),2)/*+TMath::Power(fit[1]->GetParameter(2)/fit[1]->GetParameter(1),2)*/,0.5)*100* /*fit[1]->GetParameter(1)*/fit->GetParameter(1) << "\n\n";
}	
	
