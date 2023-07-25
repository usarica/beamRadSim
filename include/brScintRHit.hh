/*
 * brScintRHit.hh
 *
 *  Created on: 22.04.2019
 *      Author: schmitz
 */

#ifndef BRSCINTRHIT_HH_
#define BRSCINTRHIT_HH_

#include "TObject.h"
#include "TString.h"
#include <vector>
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class brScintRHit : public TObject
{
  public:

    brScintRHit();
    ~brScintRHit();
    brScintRHit(const brScintRHit&);
    const brScintRHit& operator=(const brScintRHit&);
    Int_t operator==(const brScintRHit&) const;


    void SetTrackID(Int_t track){ trackID = track; };
    void SetParentID(Int_t pid){ parentID  = pid; };

    void SetCopyNo(Int_t nb){ copyNo  = nb;   };
    Int_t    GetCopyNo()const{ return copyNo; };

    void SetEDep(Double_t ed){ EDep_MeV    = ed;    };
    void SetScatterAngle(Double_t sca){ scatterAngle    = sca;    };
    void AddEDep(Double_t de){ EDep_MeV   += de;    };
    //void SetEDepRecoil(Double_t er){ EDepRecoil_keV    = er;    };
    //void AddEDepRecoil(Double_t der){ EDepRecoil_keV   += der;   };
    void SetInitialHitTime(Double_t tm){ timeOfFirstHit_ns    = tm;    };
    void SetParticleName(TString pn){ particleName   = pn;    };
    //void SetScintNb(Int_t bn){ scintNb  = bn;    };
    void SetHitPositionX(Double_t x){ hitPositionX_cm     =  x;   };
    void SetHitPositionY(Double_t y){ hitPositionY_cm     =  y;   };
    void SetHitPositionZ(Double_t z){ hitPositionZ_cm     =  z;   };

    Int_t    GetTrackID()const{ return trackID; };
    Int_t    GetParentID()const{ return parentID; };
    Double_t GetEDep()const{ return EDep_MeV; };
    Double_t GetScatterAngle()const{ return scatterAngle; };
    //Double_t GetEDepRecoil()const{ return EDepRecoil_keV; };

    Double_t GetInitialHitTime()const{ return timeOfFirstHit_ns; };
    TString GetParticleName(){ return particleName; };

    //Int_t    GetScintNb()const{ return scintNb; };
    Double_t GetHitPositionX()const{ return hitPositionX_cm; };
    Double_t GetHitPositionY()const{ return hitPositionY_cm; };
    Double_t GetHitPositionZ()const{ return hitPositionZ_cm; };


    static bool compareHits(brScintRHit* const &a, brScintRHit* const &b);

  private:

    Int_t    trackID;
    Int_t    parentID;
    Int_t    copyNo;
    //Int_t    scintNb;
    Double_t EDep_MeV;
    Double_t scatterAngle;
    //Double_t EDepRecoil_keV;
    Double_t timeOfFirstHit_ns;
    TString  particleName;
    Double_t hitPositionX_cm;
    Double_t hitPositionY_cm;
    Double_t hitPositionZ_cm;

    ClassDef(brScintRHit,8);

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
typedef std::vector<brScintRHit*> brScintRHitVector;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......



#endif /* BRSCINTRHIT_HH_ */
