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
/// \file PlayG4EventAction.hh
/// \brief Definition of the PlayG4EventAction class

#ifndef PlayG4EventAction_h
#define PlayG4EventAction_h 1

#include "G4UserEventAction.hh"

#include "globals.hh"
#include "PlayG4Storage.hh"
#include "PlayG4Struct.hh"
#include <vector>
/// Event action class
#include "PlayG4Msg.hh"
class PlayG4EventAction : public G4UserEventAction
{
  public:
    PlayG4EventAction();
    virtual ~PlayG4EventAction();

    virtual void  BeginOfEventAction(const G4Event* );
    virtual void    EndOfEventAction(const G4Event* );
    G4double nEnergy;
    G4bool nFlag;
    G4double pEnergy;
    G4bool pFlag;
    G4double pAniEnergy;
    G4double proton_x;
    G4double proton_y;
    G4double proton_z;

    std::map<Int_t/*TrackId*/, PlayG4SimTrack_t> fTrackContainer;
    std::map<G4int/*vertex ID*/, PlayG4SimTruthTree_t> fTruthList;
    void SaveTruthInfo(const G4Event* event);
  private:
		clock_t StartTime;
		clock_t EndTime;
		TTree* data;
		TTree* SKG4data;

		PlayG4Msg* fMessage = PlayG4Msg::GetInstance();

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
