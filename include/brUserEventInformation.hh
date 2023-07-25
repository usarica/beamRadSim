/*
 * brUserEventInformation.hh
 *
 *  Created on: 18.09.2012
 *      Author: schmitz
 */

#ifndef BRUSEREVENTINFORMATION_HH_
#define BRUSEREVENTINFORMATION_HH_

#include "G4VUserEventInformation.hh"
#include "brPhotonTrack.hh"
#include "brGammaTrack.hh"
#include "brNeutronTrack.hh"
#include "brMuonTrack.hh"
#include "brPMTHit.hh"
#include "brScintHit.hh"
#include "G4ThreeVector.hh"
#include "globals.hh"
#include "brROOTEvent.hh"

#include <TObject.h>

class brUserEventInformation : public G4VUserEventInformation
{
public:
  brUserEventInformation();
  //virtual
  ~brUserEventInformation();

  inline void Print()const{};

  void Initialize();
  void Reset();
  void Finalize();

  void SetEventID (G4int eventID);
  G4int GetEventID()const;
  void SetRunID (G4int runID);
  G4int GetRunID()const;


  //info about Cherenkov photons and PMT hits
  void IncPhotonCount_Scint(){photonCount_Scint++;}
  void IncPhotonCount(){photonCount++;}
  void IncPhotonCount_Cheren(){photonCount_Cheren++;}
  void IncAbsorption(){absorptionCount++;}
  void IncBoundaryAbsorption(){boundaryAbsorptionCount++;}
  void IncPECountPMT(G4int i=1){peCountPMT+=i;}

  G4int GetPECountPMT()const {return peCountPMT;}
  G4int GetAbsorptionCount()const {return absorptionCount;}
  G4int GetBoundaryAbsorptionCount() const {return boundaryAbsorptionCount;}

  //Gets the total photon count produced

  G4int GetPhotonCount_Scint()const{return photonCount_Scint;}
  G4int GetPhotonCount()const{return photonCount;}
  G4int GetPhotonCount_Cheren()const{return photonCount_Cheren;}
  void IncPMTSAboveThreshold(){pmtsAboveThreshold++;}
  G4int GetPMTSAboveThreshold()const{return pmtsAboveThreshold;}

  //info about primary gamma TODO store in gamma track




  // info about crystals
  void IncCrystalEDep(G4double dep){totalEDepInCrystals+=dep;}
  void IncCrystalENRDep(G4double NRdep){totalNREDepInCrystals+=NRdep;}


  G4double GetCrystalEDep()const {return totalEDepInCrystals;}
  G4double GetCrystalENRDep()const {return totalNREDepInCrystals;}
  
  void SetGammaOutScintillator (bool in){gammaOutScintillator=in;}
  bool GetGammaOutScintillator()const{return gammaOutScintillator;}

  void SetMuonTrigger (bool in){muonTrig=in;}
  bool GetMuonTrigger()const{return muonTrig;}

	void SetScintToPMT (G4bool in){scintToPMT = in;}
	G4bool GetScintToPMT()const{return scintToPMT;}

  void SetEnergyEnterScinti(G4double in){energyEnterScinti_MeV = in;}
  void SetEnergyExitScinti(G4double out){energyExitScinti_MeV = out;}
  G4double GetEnergyEnterScinti()const {return energyEnterScinti_MeV;}
  G4double GetEnergyExitScinti()const {return energyExitScinti_MeV;}

  void SetBarHit(G4int hit){barHit = hit;}
  G4int GetBarHit()const {return barHit;}
  
  void SetProtonScatter(G4double out){protScat = out;}
  G4double GetProtonScatter()const {return protScat;}

  void SetEventEnergyDepositSi1(G4double out){Edep_MeV_Si1 = out;}
  G4double GetEventEnergyDepositSi1()const {return Edep_MeV_Si1;}

  void SetEventEnergyDepositSi2(G4double out){Edep_MeV_Si2 = out;}
  G4double GetEventEnergyDepositSi2()const {return Edep_MeV_Si2;}

  void SetEventEnergyDepositSi3(G4double out){Edep_MeV_Si3 = out;}
  G4double GetEventEnergyDepositSi3()const {return Edep_MeV_Si3;}

  void SetEventEnergyDepositSi4(G4double out){Edep_MeV_Si4 = out;}
  G4double GetEventEnergyDepositSi4()const {return Edep_MeV_Si4;}

  void SetEventEnergyDepositSi5(G4double out){Edep_MeV_Si5 = out;}
  G4double GetEventEnergyDepositSi5()const {return Edep_MeV_Si5;}

  void SetEventEnergyDepositAbs1(G4double out){Edep_MeV_Abs1 = out;}
  G4double GetEventEnergyDepositAbs1()const {return Edep_MeV_Abs1;}

  void SetEventEnergyDepositAbs2(G4double out){Edep_MeV_Abs2 = out;}
  G4double GetEventEnergyDepositAbs2()const {return Edep_MeV_Abs2;}

  void SetEventEnergyDepositAbs3(G4double out){Edep_MeV_Abs3 = out;}
  G4double GetEventEnergyDepositAbs3()const {return Edep_MeV_Abs3;}

  void SetEventEnergyDepositAbs4(G4double out){Edep_MeV_Abs4 = out;}
  G4double GetEventEnergyDepositAbs4()const {return Edep_MeV_Abs4;}

  void SetEventEnergyDepositScintVeto(G4double out){Edep_MeV_ScintVeto = out;}
  G4double GetEventEnergyDepositScintVeto()const {return Edep_MeV_ScintVeto;}

  /*It's necessary to reset the lastTrackID for tracking, because for example there is mostly only 1 gamma (the primary id=1) per event
   * In the second event per run, the primary has again id=1, but tmLastTrackID is already 1 from the previous events
   * -> no new GammaTrack is created and the following step method try to access this non existing object -> core dump
   */
  void SetPhotonLastTrackID(G4int tpLastTrackID){ photonLastTrackID = tpLastTrackID ;}
  G4int GetPhotonLastTrackID()const{return photonLastTrackID;}

  void SetGammaLastTrackID(G4int tmLastTrackID){gammaLastTrackID = tmLastTrackID ;}
  G4int GetGammaLastTrackID()const{return gammaLastTrackID;}

  void SetNeutronLastTrackID(G4int tnLastTrackID){neutronLastTrackID = tnLastTrackID ;}
  G4int GetNeutronLastTrackID()const{return neutronLastTrackID;}

  void SetMuonLastTrackID(G4int tnLastTrackID){muonLastTrackID = tnLastTrackID ;}
  G4int GetMuonLastTrackID()const{return muonLastTrackID;}

  //gamma tracking
  void AddGammaTrack (brGammaTrack *track);
  brGammaTrack* GetGammaTrack (G4int trackID);
  brGammaTrackVector* GetGammaTracks();


  //neutron tracking
  void AddNeutronTrack (brNeutronTrack *track);
  brNeutronTrack* GetNeutronTrack(G4int trackID);
  brNeutronTrackVector* GetNeutronTracks();

  //muon tracking
  void AddMuonTrack (brMuonTrack *track);
  brMuonTrack* GetMuonTrack(G4int trackID);
  brMuonTrackVector* GetMuonTracks();

  //photon tracking
  void AddPhotonTrack (brPhotonTrack *track);
  brPhotonTrack* GetPhotonTrack(G4int trackID);
  brPhotonTrackVector* GetPhotonTracks();

  //PMT Hits
  void AddPMTHit(brPMTHit *hit);
  brPMTHitVector* GetPMTHits();


  //Scint Hits
  void AddScintHit(brScintHit *hit);
  brScintHitVector* GetScintHits();

  friend std::ostream & operator<<(std::ostream &o, brUserEventInformation const &event);

  brROOTEvent* ConvertToROOTEvent();

  //std::vector<unsigned long> Seeds;//Seeds of the random number generator for the current event
private:
  brGammaTrackVector GammaTracks;
  G4int NbOfGammaTracks;

  brNeutronTrackVector NeutronTracks;
  G4int NbOfNeutronTracks;

  brPhotonTrackVector PhotonTracks;
  G4int NbOfPhotonTracks;

  brMuonTrackVector MuonTracks;
  G4int NbOfMuonTracks;

  brPMTHitVector PMTHits;
  G4int NbOfPMTHits;

  brScintHitVector ScintHits;
  G4int NbOfScintHits;

  G4int barHit;
  G4int peCountPMT;
  G4int photonCount_Scint;
  G4int photonCount_Cheren;
  G4int photonCount;
  G4int absorptionCount;
  G4int boundaryAbsorptionCount;

  G4double totalEDepInCrystals;
  G4double totalNREDepInCrystals;

  G4int pmtsAboveThreshold;
  G4double protScat;
  G4double Edep_MeV_Si1;
  G4double Edep_MeV_Si2;
  G4double Edep_MeV_Si3;
  G4double Edep_MeV_Si4;
  G4double Edep_MeV_Si5;
  G4double Edep_MeV_Abs1;
  G4double Edep_MeV_Abs2;
  G4double Edep_MeV_Abs3;
  G4double Edep_MeV_Abs4;
  G4double Edep_MeV_ScintVeto;
  G4int runID;
  G4int eventID;
  G4int photonLastTrackID;
  G4int gammaLastTrackID;
  G4int neutronLastTrackID;
  G4int muonLastTrackID;
  G4double energyEnterScinti_MeV;
  G4double energyExitScinti_MeV;
  bool gammaOutScintillator;
  bool muonTrig;
	G4bool scintToPMT;
};


#endif /* BRUSEREVENTINFORMATION_HH_ */
