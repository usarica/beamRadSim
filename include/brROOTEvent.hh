/*
 * brROOTEvent.hh
 *
 *  Created on: 22.04.2019
 *      Author: schmitz
 */

#ifndef BRROOTEVENT_HH_
#define BRROOTEVENT_HH_

// only include classes known to ROOT
#include "brPhotonTrack.hh"
#include "brGammaTrack.hh"
#include "brNeutronTrack.hh"
#include "brMuonTrack.hh"
#include "brPMTRHit.hh"
#include "brScintRHit.hh"



#include <TObject.h>

class brROOTEvent :  public TObject
{
public:
  brROOTEvent();
  //virtual
  ~brROOTEvent();

  inline void Print()const{};

  void Initialize();
  void Reset();
  void Finalize();

  void SetEventID (Int_t eID){ eventID = eID; }
  Int_t GetEventID()const{ return eventID; }

  //virtual void Clear(Option_t* /*option*/ = "");

  //info about Cherenkov photons and PMT hits
  void SetPhotonCountCeren(Int_t photons_Ceren){ this->nbOfCerenkovPhotons = photons_Ceren; }
  void SetPhotonCountScint(Int_t photons_Scint){ this->nbOfScintillationPhotons = photons_Scint; }
  void SetAbsorptionCount(Int_t absCount){ this->absorptionCount = absCount; }
  void SetBoundaryAbsorption(Int_t boundaryAbs){ this->boundaryAbsorptionCount = boundaryAbs; }
  void SetPMTHitCount(Int_t hits){ this->totalNbOfPEPMT = hits; }
  void SetPMTSAboveThreshold(Int_t pmts){this->pmtsAboveTrigger = pmts; }

  Int_t GetPhotonCountCeren()const { return nbOfCerenkovPhotons; }
  Int_t GetPhotonCountScint()const { return nbOfScintillationPhotons; }
  Int_t GetPMTHitCount()const { return totalNbOfPEPMT; }
  Int_t GetAbsorptionCount()const { return absorptionCount; }
  Int_t GetBoundaryAbsorptionCount() const { return boundaryAbsorptionCount; }
  Int_t GetPMTSAboveThreshold()const {return pmtsAboveTrigger;}


  // info about crystal hits
  void SetTotalEDepInCrystals(Double_t edep){this->totalEDepInCrytals = edep;}
  void SetTotalNREDepInCrystals(Double_t edepNR){this->totalNREDepInCrytals = edepNR;}


  Double_t GetTotalEDepInCrystals()const {return totalEDepInCrytals;}
  Double_t GetTotalNREDepInCrystals()const {return totalNREDepInCrytals;}

  //gamma tracking
  void AddGammaTrack (brGammaTrack *track);
  void SetGammaTracks(brGammaTrackVector *trackVec);
  brGammaTrack* GetGammaTrack(Int_t trackID);
  brGammaTrackVector* GetGammaTracks();

  //neutron tracking
  void AddNeutronTrack (brNeutronTrack *track);
  void SetNeutronTracks(brNeutronTrackVector *trackVec);
  brNeutronTrack* GetNeutronTrack(Int_t trackID);
  brNeutronTrackVector* GetNeutronTracks();

  //muon tracking 
  void AddMuonTrack (brMuonTrack *track);
  void SetMuonTracks(brMuonTrackVector *trackVec);
  brMuonTrack* GetMuonTrack(Int_t trackID);
  brMuonTrackVector* GetMuonTracks();


  void SetGammaOutScintillator (bool in) {gammaOutScintillator = in;}
  bool GetGammaOutScintillator() const{return gammaOutScintillator;}

  void SetMuonTrigger (bool in) {muonTrig = in;}
  bool GetMuonTrigger() const{return muonTrig;}

	void SetScintToPMT(bool in) {scintToPMT = in;}
	bool GetScintToPMT()const{return scintToPMT;}

  void SetEnergyEnterScinti (Double_t EkinScinti){ this->energyEnterScinti_MeV = EkinScinti;}
  void SetEnergyExitScinti(Double_t EkinScinti){ this->energyExitScinti_MeV = EkinScinti;}
  Double_t GetEnergyEnterScinti()const{ return energyEnterScinti_MeV;}
  Double_t GetEnergyExitScinti()const{ return energyExitScinti_MeV;}

  void SetBarHit (Int_t hit){ this->barHit = hit;}
  Int_t GetBarHit()const{ return barHit;}

  void SetProtonScatter(Double_t ps){ this->protScat = ps;}
  Double_t GetProtonScatter()const{ return protScat;}
  
  void SetEventEnergyDepositSi1(Double_t edep){ this->Edep_MeV_Si1 = edep;}
  Double_t GetEventEnergyDepositSi1()const{ return Edep_MeV_Si1;}

  void SetEventEnergyDepositSi2(Double_t edep){ this->Edep_MeV_Si2 = edep;}
  Double_t GetEventEnergyDepositSi2()const{ return Edep_MeV_Si2;}

  void SetEventEnergyDepositSi3(Double_t edep){ this->Edep_MeV_Si3 = edep;}
  Double_t GetEventEnergyDepositSi3()const{ return Edep_MeV_Si3;}

  void SetEventEnergyDepositSi4(Double_t edep){ this->Edep_MeV_Si4 = edep;}
  Double_t GetEventEnergyDepositSi4()const{ return Edep_MeV_Si4;}

  void SetEventEnergyDepositSi5(Double_t edep){ this->Edep_MeV_Si5 = edep;}
  Double_t GetEventEnergyDepositSi5()const{ return Edep_MeV_Si5;}

  void SetEventEnergyDepositAbs1(Double_t edep){ this->Edep_MeV_Abs1 = edep;}
  Double_t GetEventEnergyDepositAbs1()const{ return Edep_MeV_Abs1;}

  void SetEventEnergyDepositAbs2(Double_t edep){ this->Edep_MeV_Abs2 = edep;}
  Double_t GetEventEnergyDepositAbs2()const{ return Edep_MeV_Abs2;}

  void SetEventEnergyDepositAbs3(Double_t edep){ this->Edep_MeV_Abs3 = edep;}
  Double_t GetEventEnergyDepositAbs3()const{ return Edep_MeV_Abs3;}

  void SetEventEnergyDepositAbs4(Double_t edep){ this->Edep_MeV_Abs4 = edep;}
  Double_t GetEventEnergyDepositAbs4()const{ return Edep_MeV_Abs4;}

  void SetEventEnergyDepositScintVeto(Double_t edep){ this->Edep_MeV_ScintVeto = edep;}
  Double_t GetEventEnergyDepositScintVeto()const{ return Edep_MeV_ScintVeto;}

  //photon tracking
  void AddPhotonTrack (brPhotonTrack *track);
  void SetPhotonTracks(brPhotonTrackVector *trackVec);
  brPhotonTrack* GetPhotonTrack(Int_t trackID);
  brPhotonTrackVector* GetPhotonTracks();

  //PMT Hits
  void AddPMTRHit(brPMTRHit *hit);
  void SetPMTRHits(brPMTRHitVector *hitVec);
  brPMTRHitVector* GetPMTRHits();

  //Scint Hits
  void AddScintRHit(brScintRHit *hit);
  brScintRHitVector* GetScintRHits();

  friend std::ostream & operator<<(std::ostream &o, brROOTEvent const &event);

  //std::vector<unsigned long> Seeds;//Seeds of the random number generator for the current event
private:

  Int_t eventID;

  brGammaTrackVector GammaTracks;
  Int_t NbOfGammaTracks;

  brNeutronTrackVector NeutronTracks;
  Int_t NbOfNeutronTracks;

  brPhotonTrackVector PhotonTracks;
  Int_t NbOfPhotonTracks;

  brMuonTrackVector MuonTracks;
  Int_t NbOfMuonTracks;

  brPMTRHitVector PMTHits;
  Int_t NbOfPMTHits;

  brScintRHitVector ScintRHits;
  Int_t NbOfScintRHits;

  Int_t nbOfCerenkovPhotons;
  Int_t nbOfScintillationPhotons;
  Int_t absorptionCount;
  Int_t boundaryAbsorptionCount;

  Int_t totalNbOfPEPMT;
  Int_t pmtsAboveTrigger;

  Double_t totalEDepInCrytals;
  Double_t totalNREDepInCrytals;

  Double_t energyEnterScinti_MeV;
  Double_t energyExitScinti_MeV;
  Double_t protScat;
  Double_t Edep_MeV_Si1;
  Double_t Edep_MeV_Si2;
  Double_t Edep_MeV_Si3;
  Double_t Edep_MeV_Si4;
  Double_t Edep_MeV_Si5;
  Double_t Edep_MeV_Abs1;
  Double_t Edep_MeV_Abs2;
  Double_t Edep_MeV_Abs3;
  Double_t Edep_MeV_Abs4;
  Double_t Edep_MeV_ScintVeto;
  Int_t barHit;

  bool gammaOutScintillator;
  bool muonTrig;
	bool scintToPMT;
  ClassDef(brROOTEvent,8);

};


#endif /* BRROOTEVENT_HH_ */
