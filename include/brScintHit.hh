/*
 * brScintHit.hh
 *
 *  Created on: 22.04.2019
 *      Author: schmitz
 */

#ifndef BRSCINTHIT_HH_
#define BRSCINTHIT_HH_

#include "brScintRHit.hh"

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Track.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4ParticleDefinition.hh"
#include <vector>
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class brScintHit : public G4VHit
{
  public:

    brScintHit();
    ~brScintHit();
    brScintHit(const brScintHit&);
    const brScintHit& operator=(const brScintHit&);
    G4int operator==(const brScintHit&) const;

    inline void* operator new(size_t);
    inline void  operator delete(void*);

    void Draw();
    void Print();

    void SetTrackID(G4int track){ trackID = track; };
    void SetParentID(G4int pid){ parentID  = pid; };

    void SetCopyNo(G4int nb){ copyNo  = nb;   };
    G4int    GetCopyNo()const{ return copyNo; };

    void SetEDep(G4double ed){ EDep    = ed;    };
    void AddEDep(G4double de){ EDep   += de;    };
    
    void SetScatterAngle(G4double ang){ scatterAngle    = ang;    };

    void SetEDepRecoil(G4double er){ EDepRecoil    = er;    };
    void AddEDepRecoil(G4double der){ EDepRecoil   += der;   };

    void SetInitialHitTime(G4double tm){ initialHitTime    = tm;    };
    void SetParticleName(G4String pn){ particleName   = pn;    };

    //void SetScintNb(G4int bn){ scintNb  = bn;    };
    void SetHitPosition     (G4ThreeVector xyz){ hitPosition     = xyz;   };

    G4int    GetTrackID()const{ return trackID; };
    G4int    GetParentID()const{ return parentID; };
    G4double GetEDep()const{ return EDep; };
    G4double GetScatterAngle()const{ return scatterAngle; };
    G4double GetEDepRecoil()const{ return EDepRecoil; };

    G4double GetInitialHitTime()const{ return initialHitTime; };
    G4String GetParticleName()const{ return particleName; };

    //G4int    GetScintNb()const{ return scintNb; };
    G4ThreeVector GetHitPosition()const{ return hitPosition; };


    static bool compareHits(brScintHit* const &a, brScintHit* const &b);
    brScintRHit* ConvertToROOTHit() const;
  private:

    G4int         trackID;
    G4int         parentID;
    G4double      scatterAngle;
    //G4int         scintNb;
    G4double      EDep;
    G4int 	  copyNo;
    G4double      EDepRecoil;
    G4double      initialHitTime;
    G4String      particleName;
    G4ThreeVector hitPosition;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
typedef std::vector<brScintHit*> brScintHitVector;
typedef G4THitsCollection<brScintHit> brScintHitsCollection;

extern G4Allocator<brScintHit> brScintHitAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void* brScintHit::operator new(size_t)
{
  void *aHit;
  aHit = (void *) brScintHitAllocator.MallocSingle();
  return aHit;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void brScintHit::operator delete(void *aHit)
{
	brScintHitAllocator.FreeSingle((brScintHit*) aHit);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......



#endif /* BRSCINTHIT_HH_ */
