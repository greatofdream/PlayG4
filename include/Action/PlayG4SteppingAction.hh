#ifndef PlayG4SteppingAction_h
#define PlayG4SteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"

class PlayG4EventAction;

class G4LogicalVolume;

/// Stepping action class
/// 

class PlayG4SteppingAction : public G4UserSteppingAction
{
  public:
    PlayG4SteppingAction(PlayG4EventAction* eventAction);
    virtual ~PlayG4SteppingAction();

    // method from the base class
    virtual void UserSteppingAction(const G4Step*);

  private:
    PlayG4EventAction*  fEventAction;
    G4LogicalVolume* fScoringVolume;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
