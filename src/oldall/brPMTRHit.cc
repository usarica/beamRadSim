/*
 * brPMTRHit.cc
 * PMT Hit Class which is compatible to ROOT.
 * It consists of the same methods and variables but does not inherit from G4VHit but from TObject
 * (in order to be able store the information in a TTree).
 *
 *  Created on: 22.04.2019

 *      Author: schmitz
 */

#include "brPMTRHit.hh"

#include <iomanip>

ClassImp(brPMTRHit)
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
brPMTRHit::brPMTRHit()
  :pmtNumber(-1), totalPE(0),
   initalEDep_eV(0.), initialHitTime_ns(0.),
   finalHitTime_ns(0.), hitPosition(),
   trackID(-1), totalEDep_eV(0.),
   parentID(-1), scintToPMT(false)
{}

//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
brPMTRHit::~brPMTRHit()
{}

//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
brPMTRHit::brPMTRHit(const brPMTRHit &right) :
		TObject()
{
	  pmtNumber         = right.pmtNumber      ;
	  totalPE      	    = right.totalPE        ;
	  initalEDep_eV     = right.initalEDep_eV     ;
	  initialHitTime_ns = right.initialHitTime_ns ;
	  finalHitTime_ns   = right.finalHitTime_ns   ;
	  hitPosition       = right.hitPosition    ;
	  totalEDep_eV	    = right.totalEDep_eV   ;
	  trackID           = right.trackID        ;
	  parentID          = right.parentID       ;
	  scintToPMT	    = right.scintToPMT    ;

//G4cout << "hitPosition X " << hitPosition.x() << std::endl;
//G4cout << "hitPosition Y " << hitPosition.y() << std::endl;
//G4cout << "hitPosition Z " << hitPosition.z() << std::endl;
}

//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
const brPMTRHit& brPMTRHit::operator=(const brPMTRHit &right){
	  pmtNumber         = right.pmtNumber      ;
	  totalPE      	    = right.totalPE        ;
	  initalEDep_eV     = right.initalEDep_eV     ;
	  initialHitTime_ns = right.initialHitTime_ns ;
	  finalHitTime_ns   = right.finalHitTime_ns   ;
	  hitPosition       = right.hitPosition    ;
	  totalEDep_eV	    = right.totalEDep_eV   ;
	  trackID           = right.trackID        ;
	  parentID          = right.parentID       ;
	  scintToPMT	    = right.scintToPMT    ;

//G4cout << "hitPosition X " << hitPosition.x() << std::endl;
//G4cout << "hitPosition Y " << hitPosition.y() << std::endl;
//G4cout << "hitPosition Z " << hitPosition.z() << std::endl;
return *this;
}

//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
int brPMTRHit::operator==(const brPMTRHit &right) const{
  return (pmtNumber == right.pmtNumber);

}

//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
bool brPMTRHit::compareHits(brPMTRHit* const &a, brPMTRHit* const &b){
	Double_t aTime = a->GetLastHitTime();
	Double_t bTime = b->GetLastHitTime();
	return (aTime < bTime);
}


//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
//void brPMTRHit::Print(){
//
//	std::cout
//	     << " trackID: " << trackID << " pmtNumber: " << pmtNumber
//	     << " Number of photons: "
//	     << std::setw(7) << nbPhotons
//	     << " Parent ID: "
//	     << std::setw(7) << parentID
//	     << " Hit time: "
//	     << std::setw(7) << initialHitTime
//	     << " Total energy deposit: "
//	     << std::setw(7) << totalEDep
//	     << std::endl;
//
//}


