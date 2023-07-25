#include "TCanvas.h"
#include "TTree.h"
#include "TGaxis.h"
#include "TStyle.h"
#include "TFile.h"
#include <iostream>
#include "TMath.h"
#include "TChain.h"
#include "/home/schmitz/sim/HannahTestStand/include/eurROOTEvent.hh"
#include "TGraph.h"
double PhotonWLSEff(int);


void WLSEfficiencyCurves(){
	int colors = 6;
	double* EffCurve = new double[colors];
	for (int i=0;i<colors;i++){
		EffCurve[i]=PhotonWLSEff(i);
	}
	double colorCount[6]={1,2,3,4,5,6};
	TGraph *gr = new TGraph(6,colorCount,EffCurve);
	TCanvas *c1 = new TCanvas("c1","c1",0,400,600,300);
	gr->Draw("AB");
}
double PhotonWLSEff(int colorNum){

  TChain rootEvents("Events");
  rootEvents.Add("/data/chocula/schmitz/condor_output/HannahTestStand/data/4GeV_muon_fiber_photonRun.root");
  std::cout << "Reading file..." << std::endl;


  eurROOTEvent* myROOTEvent = new eurROOTEvent();
  rootEvents.SetBranchAddress("ROOTEvent", &myROOTEvent);
//  double threshold=inputThreshold;
  Long64_t nentries=rootEvents.GetEntries();
  int colors = 6;
  double num[6];
  num={0,0,0,0,0,0};
  double EDep=0;
  double h=4.135668*pow(10,-15);
  double c=3*pow(10,8);
  double count[6];
  double wavelength=0;
  count={0,0,0,0,0,0};
  for (Long64_t i=0;i<nentries;i++) {
	rootEvents.GetEntry(i);
	if (myROOTEvent->GetPMTRHits()->size()>0){
		for (int chit = 0; chit < myROOTEvent->GetPMTRHits()->size(); chit++) {
			EDep=myROOTEvent->GetPMTRHits()->at(chit)->GetInitialEDep();
			wavelength=h*c/(EDep)*pow(10,9);
//			if (i%100000==0) std::cout << "Energy: " << EDep << std::endl << "wavelength: " << wavelength << std::endl;
			//wavelength will be in nm
			//0,violet is 380 nm to 450 nm
			//1,blue is 450 nm to 495 nm
			//2,green is 495 nm to 570 nm
			//3,yellow is 570 nm to 590 nm
			//4,orange is 590 nm to 620 nm
			//5,red is 620 nm to 750 nm
								
				if (wavelength > 380 && wavelength < 450){
					if (myROOTEvent->GetPMTRHits()->at(chit)->GetFiberToPMT()) {
						count[0]=count[0]+1; }	
						num[0]=num[0]+1;}
				else if (wavelength > 450 && wavelength < 495){
					if (myROOTEvent->GetPMTRHits()->at(chit)->GetFiberToPMT()) {
						count[1]=count[1]+1; }
						num[1]=num[1]+1;}
				else if (wavelength > 495 && wavelength < 570){
					if (myROOTEvent->GetPMTRHits()->at(chit)->GetFiberToPMT()) {
						count[2]=count[2]+1; }
						num[2]=num[2]+1;}
				else if (wavelength > 570 && wavelength < 590){
					if (myROOTEvent->GetPMTRHits()->at(chit)->GetFiberToPMT()) {
						count[3]=count[3]+1; }
						num[3]=num[3]+1;}
				else if (wavelength > 590 && wavelength < 620){
					if (myROOTEvent->GetPMTRHits()->at(chit)->GetFiberToPMT()) {
						count[4]=count[4]+1; } 
						num[4]=num[4]+1;}
				else if (wavelength > 620 && wavelength < 750){
					if (myROOTEvent->GetPMTRHits()->at(chit)->GetFiberToPMT()) {
						count[5]=count[5]+1; } 
						num[5]=num[5]+1;}	
	
			}
			//if (count==100000){ 
			//	std::cout << "Photon Energy at index " << chit << " is " << myROOTEvent->GetPMTRHits()->at(chit)->GetInitialEDep() << std::endl;
			//	count=0; }
			//count++;
		}
	}

  double WLSEff[6];
  for(int j=0;j<colors;j++) {
  	WLSEff[j]=count[j]/num[j]; }
std::cout << "WLS fiber efficency: " << WLSEff[colorNum] << std::endl << "color: " << colorNum << std::endl << "WLS Fiber counts: " << count[colorNum] << std:: endl << "counts overall in color: " << num[colorNum] << std::endl;
  
  return WLSEff[colorNum];


  //TH1F *hEDep = new TH1F("hAPD","Initial Energy Deposition",100,0,);
  //hEDep->GetXaxis()->SetTitle("Initial Energy Deposition (eV)");
  //hEDep->GetYaxis()->SetTitle("Bin Members");

  //TCanvas *c1 = new TCanvas("c1","c1",0,400,600,300);
  //ch.Draw("PMTHits->initalEDep_eV>>hEDep");
}
	
