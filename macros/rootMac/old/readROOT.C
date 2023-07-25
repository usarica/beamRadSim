/*
 * eurOfflineAnalysis.c
 *
 *  Created on: 29.01.2013
 *      Author: heuermann
 */
#include "TH1F.h"
#include "TH1D.h"
#include "TH2F.h"
#include "TH2D.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TH3F.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TStyle.h"
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TMath.h"
//using namespace std;
#include "/home/schmitz/sim/HannahTestStand/include/eurROOTEvent.hh"




using namespace std;

void WriteTree(){

	TFile *f1 = new TFile("fiberScintiPMT.root","RECREATE");

	TChain rootEvents("Events");


	for (Int_t i = 1; i < 101; i++){
		TString file("/home/schmitz/sim/runDir/muon/fullScinti-emission/");

		std::string s;
		std::stringstream out;
		out << i;
		s = out.str();
		file.Append(s);
		file.Append("/EURECA.root");

		rootEvents.Add(file);


	}
	rootEvents.CloneTree(-1,"fast");

	f1->Write();
}

void ReadPMTHits(TString file){

	TChain rootEvents("Events");
	rootEvents.Add(file);
	std::cout << "Reading file ... "  << std::endl;
	eurROOTEvent* myROOTEvent = new eurROOTEvent();
	rootEvents.SetBranchAddress("ROOTEvent", &myROOTEvent);

	Long64_t nentries = rootEvents.GetEntries();
	for (Long64_t i=0;i<nentries;i++) {
		rootEvents.GetEntry(i);
		if (myROOTEvent->GetPMTRHits()->size() > 0){
				for (int chit = 0; chit < myROOTEvent->GetPMTRHits()->size(); chit ++){
					std::cout << "Number of PE in PMT " << chit << ": "
							<< myROOTEvent->GetPMTRHits()->at(chit)->GetPhotonCount()
							<< std::endl;
				}
		}
	}


}

void ReadAPDHits(TString file){

	TChain rootEvents("Events");
	rootEvents.Add(file);
	std::cout << "Reading file ... "  << std::endl;
	eurROOTEvent* myROOTEvent = new eurROOTEvent();
	rootEvents.SetBranchAddress("ROOTEvent", &myROOTEvent);

	Long64_t nentries = rootEvents.GetEntries();
	for (Long64_t i=0;i<nentries;i++) {
		rootEvents.GetEntry(i);
		if (myROOTEvent->GetAPDRHits()->size() > 0){
				for (int chit = 0; chit < myROOTEvent->GetAPDRHits()->size(); chit ++){
					std::cout << "Number of PE in APD " << chit << ": "
						<< myROOTEvent->GetAPDRHits()->at(chit)->GetPhotonCount()
						<< std::endl;
				}
		}
	}


}

void EDepScinti(TString file){



	TH1F *tm      = new TH1F("edepScinti","edep scinti", 500,0.,5.);
	tm->GetXaxis()->SetTitle("E (eV)");	


	TChain rootEvents("Events");
	rootEvents.Add(file);
	std::cout << "Reading file ... "  << std::endl;
	eurROOTEvent* myROOTEvent = new eurROOTEvent();
	rootEvents.SetBranchAddress("ROOTEvent", &myROOTEvent);

	Long64_t nentries = rootEvents.GetEntries();
	for (Long64_t i=0;i<nentries;i++) {
		rootEvents.GetEntry(i);
		if (myROOTEvent->GetPMTRHits()->size() > 0){

				for (int chit = 0; chit < myROOTEvent->GetPMTRHits()->size(); chit ++){
					Double_t edep = myROOTEvent->GetPMTRHits()->at(chit)->GetInitialEDep();

							std::cout << "Initial edep Scinti: " << edep << std::endl;
							tm->Fill(edep);
							
				}
		}
	}



}


void EPhotonWLSScinti(){

	TH1F *tm      = new TH1F("edepScinti","edep scinti", 350,350,700.);
	tm->GetXaxis()->SetTitle("E (nm)");	

	TH1F *twls      = new TH1F("edepWls","edep wls", 350,350.,700.);
	twls->GetXaxis()->SetTitle("E (nm)");	

	TChain rootEvents("Events");
	rootEvents.Add("/home/schmitz/build/HannahTestStand-build/EURECA.root");
	std::cout << "Reading file ... "  << std::endl;
	eurROOTEvent* myROOTEvent = new eurROOTEvent();
	rootEvents.SetBranchAddress("ROOTEvent", &myROOTEvent);
	std::cout << "entries: " <<  rootEvents.GetEntries() << std::endl;
	Long64_t nentries = 4000;//rootEvents.GetEntries();
	for (Long64_t i=0;i<nentries;i++) {
		rootEvents.GetEntry(i);
		if (myROOTEvent->GetAPDRHits()->size() > 0){

				for (int chit = 0; chit < myROOTEvent->GetAPDRHits()->size(); chit ++){
					Double_t edep = myROOTEvent->GetAPDRHits()->at(chit)->GetInitialEDep();
					Double_t enm = 1240./edep;
					if (edep > 1.908 && edep < 3.059 ){ //std::cout << "Initial edep Scinti: " << enm << std::endl;
							tm->Fill(enm);
							//
						}
				}
		}
	}

	///////////////////I commented out the section below, up to the bracket above Tfile f(......);, not Geertje

	//TChain rootEvents2("Events"); //originally the file extension below was different than that used in the above tree
	//rootEvents2.Add("/home/schmitz/build/HannahTestStand-build/EURECA.root");
	//std::cout << "Reading file ... "  << std::endl;
	//eurROOTEvent* myROOTEvent2 = new eurROOTEvent();
	//rootEvents2.SetBranchAddress("ROOTEvent", &myROOTEvent2);
	//std::cout << "entries2: " <<  rootEvents2.GetEntries() << std::endl;
	//Long64_t nentries2 = 10000;//rootEvents2.GetEntries();
	//for (Long64_t i=0;i<nentries2;i++) {
	//	rootEvents2.GetEntry(i);
	//	
	//	if (myROOTEvent2->GetAPDRHits()->size() > 0){
	//			for (int chit = 0; chit < myROOTEvent2->GetAPDRHits()->size(); chit ++){
	//				Double_t edepWLS = myROOTEvent2->GetAPDRHits()->at(chit)->GetInitialEDep();	
	//				Double_t enmWLS = 1240./edepWLS;
	//				if (edepWLS > 1.908 && edepWLS < 3.059 ){//std::cout << "Initial edep WLS: " << enmWLS << std::endl;
	//						twls->Fill(enmWLS);
	//						//
	//				}
	//			}
	//	}
	//}

	//TFile f("WLS-Scinti-0.99-alex.root");
	TCanvas *t1 = new TCanvas();

	std::cout << "Integral full scinti: " << tm->Integral()  << std::endl;
	std::cout << "Integral WLS " << twls->Integral()  << std::endl;	
	std::cout << "ratio " << Double_t(twls->Integral())/Double_t(tm->Integral())  << std::endl;
	tm->Draw();
	twls->Draw("same");


	t1->SaveAs("WLS-Scinti.root");
}




void TestStandnbPE(TString file){

	TChain rootEvents("Events");
	rootEvents.Add(file);
	std::cout << "Reading file ... "  << std::endl;
	eurROOTEvent* myROOTEvent = new eurROOTEvent();
	//TFile *f1 = new TFile("out.root","RECREATE");
	rootEvents.SetBranchAddress("ROOTEvent", &myROOTEvent);
	TH1F *PMT0      = new TH1F("PMT0"," Number of PE", 1000,0.5,1000.5);



	Long64_t nentries = rootEvents.GetEntries();
	for (Long64_t i=0;i<nentries;i++) {
		rootEvents.GetEntry(i);
		//int count= 0;

		if (myROOTEvent->GetPMTRHits()->size() > 0){

			PMT0->Fill(myROOTEvent->GetPMTRHits()->size());

		}
	}
	//PMT0->Scale(1./PMT0->GetEntries());
	PMT0->Draw("");
}





