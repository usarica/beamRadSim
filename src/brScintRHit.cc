/*
 * brScintRHit.cc
 *
 *  Created on: 21.04.2019
 *      Author: schmitz
 */

#include "brScintRHit.hh"

#include <iomanip>

ClassImp(brScintRHit)
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

brScintRHit::brScintRHit():
	trackID(-1), parentID(-1),
	copyNo(-1),
	EDep_MeV(0.),
	//EDepRecoil_keV(0.),
	particleName("")
//	hitPositionX_cm(0.),hitPositionY_cm(0.),hitPositionZ_cm(0.)

{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

brScintRHit::~brScintRHit() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

brScintRHit::brScintRHit(const brScintRHit& right):
		TObject()// inherit from TObject?
{
	trackID         = right.trackID        ;
    parentID        = right.parentID       ;
    copyNo       = right.copyNo       ;
    EDep_MeV            = right.EDep_MeV          ;
    //EDepRecoil_keV      = right.EDepRecoil_keV     ;
    particleName    = right.particleName   ;
    timeOfFirstHit_ns  = right.timeOfFirstHit_ns ;
  //  hitPositionX_cm    = right.hitPositionX_cm   ;
    //hitPositionY_cm    = right.hitPositionY_cm   ;
    //hitPositionZ_cm    = right.hitPositionZ_cm   ;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

const brScintRHit& brScintRHit::operator=(const brScintRHit& right)
{
	trackID         = right.trackID        ;
    parentID        = right.parentID       ;
    copyNo       = right.copyNo       ;
    EDep_MeV            = right.EDep_MeV          ;
    //EDepRecoil_keV      = right.EDepRecoil_keV     ;
    particleName    = right.particleName   ;
    timeOfFirstHit_ns  = right.timeOfFirstHit_ns ;
//    hitPositionX_cm    = right.hitPositionX_cm   ;
//    hitPositionY_cm    = right.hitPositionY_cm   ;
//    hitPositionZ_cm    = right.hitPositionZ_cm   ;

    return *this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

Int_t brScintRHit::operator==(const brScintRHit& right) const
{
  return (this==&right) ? 1 : 0;
}


//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_
bool brScintRHit::compareHits(brScintRHit* const &a, brScintRHit* const &b){
	Double_t aTime = a->timeOfFirstHit_ns;
	Double_t bTime = b->timeOfFirstHit_ns;
	return (aTime < bTime);
}



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......




