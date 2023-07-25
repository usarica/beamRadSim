#include "TROOT.h"
#include "TApplication.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TMath.h"
#include "TF1.h"
#include "Math/MinimizerOptions.h"
#include "/home/schmitz/sim/HannahTestStand/include/eurROOTEvent.hh"
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

void wls_trapping_eff_computational(double r1min, double r2min, double r1max, double r2max, int histMax, int bins) {
	gROOT->SetStyle("Plain");
	gStyle->SetOptStat("");
	char temp[200], temp2[200];
	
	const int chanTot = 3;
	const int chanNum = 0;
	const int fileNum = 2;
	
//	int bins = 100;
//	/int histMax = 400;
	double rMin[fileNum] = {r1min,r2min}, rMax[fileNum] = {r1max,r2max}; /////Adjust these parameters for the fits.
	
	TChain ch[fileNum];
	//ch[0].Add("/data/chocula/schmitz/condor_output/HannahTestStand/data/paper/muon6/whole95/EURECA.root/Events");
	ch[1].Add("/data/cdms1/schmitz/gridAttLengTest/R97A2p5/9cm/EURECA.root/Events");
	//ch[1].Add("/data/cdms1/schmitz/attLengTest10mPS/9cm/EURECA.root/Events");
	ch[0].Add("/data/cdms1/schmitz/condor_output/HannahTestStand/data/paper/muon6/whole95/EURECA.root/Events");

	eurROOTEvent* myROOTEvent = new eurROOTEvent();
	ch[1].SetBranchAddress("ROOTEvent", &myROOTEvent);
	Long64_t nentries = ch[1].GetEntries();

	int evTot[fileNum];
	double tempArea[chanTot], tempAreaErr[chanTot], area[fileNum][10000], areaErr[fileNum][10000];
	double pmtPE = 0.0548; //slope: nVs/PE
	TCanvas *c1 = new TCanvas("c1","c1",0,0,1000,500);		c1->cd();
	TH1F *hist[fileNum];
	TF1 *fit[fileNum];
	for(int i=0; i<fileNum; i++) {
		evTot[i] = ch[i].GetEntries();
		sprintf(temp,"hist[%d]",i);
		hist[i] = new TH1F(temp,"", bins, 0, histMax);
		hist[i]->Sumw2();
		hist[i]->GetXaxis()->SetTitle("Photoelectrons Detected [PE]");
		hist[i]->GetYaxis()->SetTitle("Fraction of Counts");
		
		sprintf(temp2,"NbOfPMTHits>>%s",temp);		////NEED CORRECT tBranch NAME (replace only Edep_MeV)
		ch[i].Draw(temp2);	
		
		hist[i]->Scale(1./evTot[i]);
		if(i==0) hist[i]->SetLineColor(kRed);
		if(i==1) hist[i]->SetLineColor(kBlue);
		
		for(int j=0; j<evTot[i]; j++) {
			if(area[i][j] > 5) {
				hist[i]->Fill(area[i][j]);
		}
		}
		
		sprintf(temp,"fit[%d]",i);
		fit[i] = new TF1("temp","gaus");
		fit[i]->SetRange(rMin[i],rMax[i]);
		hist[i]->Fit("temp","r");
		if(i==0) fit[i]->SetLineColor(kRed);
		if(i==1) fit[i]->SetLineColor(kBlue);
	}
	
	hist[1]->Draw("hist e1");
	hist[0]->Draw("hist e1 same");
	fit[0]->Draw("same");
	fit[1]->Draw("same");
	c1->Update();
	
	TLegend *leg = new TLegend(0.6,0.6,0.85,0.85);
	leg->AddEntry(fit[0],"Without foil mask","l");
	leg->AddEntry((TObject*)0, TString::Format("    %.0f #pm %.0f PE",fit[0]->GetParameter(1),fit[0]->GetParameter(2)),"");
	leg->AddEntry(fit[1],"With foil mask","l");
	leg->AddEntry((TObject*)0, TString::Format("    %.0f #pm %.0f PE",fit[1]->GetParameter(1),fit[1]->GetParameter(2)),"");
	leg->Draw("same");
	c1->Update();
	
	cout << "\nPeak location percentage:\n";
	cout << 100*fit[1]->GetParameter(1)/fit[0]->GetParameter(1) << " +/- " << TMath::Power(TMath::Power(fit[0]->GetParameter(2)/fit[0]->GetParameter(1),2)+TMath::Power(fit[1]->GetParameter(2)/fit[1]->GetParameter(1),2),0.5)*100*fit[1]->GetParameter(1)/fit[0]->GetParameter(1) << "\n\n";
}	
	
