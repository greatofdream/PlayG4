#ifndef PlayG4TRACKINGACTION_HH
#define PlayG4TRACKINGACTION_HH 1

// For C++
#include <iostream>

// For Geant4
#include "G4UserTrackingAction.hh"
#include "globals.hh"

// For PlayG4
#include "PlayG4Msg.hh"
#include "PlayG4Storage.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
class PlayG4TrackingAction : public G4UserTrackingAction {

	public:  
		PlayG4TrackingAction();
		~PlayG4TrackingAction();

		void PreUserTrackingAction(const G4Track*);
		void PostUserTrackingAction(const G4Track*);

	private:
		PlayG4Msg* fMessage = PlayG4Msg::GetInstance();
		PlayG4Storage* RootFile = PlayG4Storage::GetInstance();
};
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
