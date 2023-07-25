/*
 * brPMTRHit.hh
 * PMT Hit Class which is compatible to ROOT.
 * It consists of the same methods and variables but does not inherit from G4VHit but from TObject
 * (in order to be able store the information in a TTree).
 *
 *  Created on: 22.04.2019
 *      Author: schmitz
 */

#ifndef BRPMTRHIT_HH_
#define BRPMTRHIT_HH_

#include <vector>
#include "TObject.h"
#include "TVector3.h"

class brPMTRHit: public TObject
{
public:

  brPMTRHit();

  ~brPMTRHit();

  brPMTRHit(const brPMTRHit &right);

  const brPMTRHit& operator=(const brPMTRHit &right);
  Int_t operator==(const brPMTRHit &right) const;

  //void Print();

  void SetPhotonCount(Int_t photons){totalPE = photons;}
  Int_t GetPhotonCount(){return totalPE;}

  void SetPMTNumber(Int_t n) { pmtNumber = n; }
  Int_t GetPMTNumber() { return pmtNumber; }

  void SetInitialEDep(Double_t E){initalEDep_eV = E;} // Sets energy of first hit
  Double_t GetInitialEDep(){return initalEDep_eV;}

  void SetFirstHitTime(Double_t initialTime){ initialHitTime_ns = initialTime;} // Sets global time of first hit
  Double_t GetFirstHitTime(){return initialHitTime_ns;}

  void SetLastHitTime(Double_t finalTime){finalHitTime_ns = finalTime;}
  Double_t GetLastHitTime(){return finalHitTime_ns;}

  void SetHitPosition(TVector3 position){hitPosition = position;}
  TVector3 GetHitPosition(){return hitPosition;}

  void SetTrackID(Int_t tid){trackID = tid;}
  Int_t GetTrackID(){return trackID;}

  void IncEDep(Double_t Edep){totalEDep_eV += Edep;}

  void SetTotalEDep(Int_t Edep){totalEDep_eV = Edep;}
  Double_t GetEDep(){return totalEDep_eV;}

  void SetParentID(Int_t pid){parentID = pid;}
  Int_t GetParentID(){return parentID;}

  void SetScintToPMT(bool set){scintToPMT = set;}
  bool GetScintToPMT(){return scintToPMT;}

  static bool compareHits(brPMTRHit* const &a, brPMTRHit* const &b);


private:

  Int_t    pmtNumber;
  Int_t    totalPE;
  TVector3 hitPosition;
  Double_t initalEDep_eV;
  Double_t initialHitTime_ns;
  Double_t finalHitTime_ns;
  Int_t    trackID;
  Double_t totalEDep_eV;
  Int_t    parentID;
  bool scintToPMT;
  ClassDef(brPMTRHit,7);

};
typedef std::vector<brPMTRHit*> brPMTRHitVector;

#endif /* BRPMTRHIT_HH_ */
