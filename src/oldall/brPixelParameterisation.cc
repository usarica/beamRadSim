//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
/// \file brPixelParameterisation.cc
/// \brief Implementation of the brPixelParameterisation class

#include "brPixelParameterisation.hh"

#include "G4VPhysicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4Box.hh"
#include "G4SystemOfUnits.hh"
#include <math.h>
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

brPixelParameterisation::brPixelParameterisation(  
        G4int    nPixelY,
        G4int    nPixelZ,
        G4double startX,          //  Z of center of grid. Always set to zero for now
        G4double YZspacing,        //  spacing of axis centers of bars
        G4double halfWidthPixel,       //bars are square in cross-section, this gives length
        G4double halfLengthPixel)      //bar length
 : G4VPVParameterisation()
{
   fnPixels =  nPixelZ*nPixelY;
   fnPixelsY = nPixelY;
   fnPixelsZ = nPixelZ;
   fStartX     =  startX; 
   fYZSpacing    =  YZspacing;
   fHalfWidth  =  halfWidthPixel;
   fHalfLength =  halfLengthPixel;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

brPixelParameterisation::~brPixelParameterisation()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void brPixelParameterisation::ComputeTransformation
(const G4int copyNo, G4VPhysicalVolume* physVol) const
{
  // Note: copyNo will start with zero!
  G4double Yposition = (copyNo/fnPixelsZ)*fYZSpacing   - (fnPixelsY-1)*fYZSpacing/2;
  G4double Zposition = (copyNo % fnPixelsY)*fYZSpacing - (fnPixelsZ-1)*fYZSpacing/2;
  //G4double Yposition = ((copyNo/fnPixelsX) % fnPixelsX)*fYZSpacing   - (fnPixelsX-1)*fYZSpacing/2;
  G4int nPixelsPerLayer = fnPixelsY*fnPixelsZ;
  //G4double Zposition = fStartZ+(copyNo/nPixelsPerLayer)*fZSpacing - (fnLayers-1)*fZSpacing/2;
  G4double Xposition = fStartX;
  G4ThreeVector origin(Xposition,Yposition,Zposition);
  physVol->SetTranslation(origin);
  physVol->SetRotation(0);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void brPixelParameterisation::ComputeDimensions
(G4Box& brPixel, const G4int copyNo, const G4VPhysicalVolume*) const
{
  // Note: copyNo will start with zero! and for now, we don't change our geom size for each copy
  //brPixel.SetXHalfLength(fHalfWidth);
  //brPixel.SetYHalfLength(fHalfWidth);
  //brPixel.SetZHalfLength(fHalfLength);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
