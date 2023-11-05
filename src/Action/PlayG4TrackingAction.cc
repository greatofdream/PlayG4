// For Geant4
#include "G4Event.hh"
#include "G4TrackingManager.hh"
#include "G4Track.hh"
#include "G4ParticleTypes.hh"
#include "G4ParticleDefinition.hh"
#include "G4EventManager.hh"
#include "G4SystemOfUnits.hh"
// For PlayG4
#include "PlayG4TrackingAction.hh"
#include "PlayG4Struct.hh"
#include "PlayG4UserEventInformation.hh"

PlayG4TrackingAction::PlayG4TrackingAction()
{
	fMessage->PrintOneLine("Constructor < Tracking Action >");
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
PlayG4TrackingAction::~PlayG4TrackingAction()
{
	fMessage->PrintOneLine("Destructor < Tracking Action >");
}

void PlayG4TrackingAction::PreUserTrackingAction(const G4Track* aTrack)
{
}

void PlayG4TrackingAction::PostUserTrackingAction(const G4Track* aTrack)
{
    PlayG4UserEventInformation *eventInformation
		= (PlayG4UserEventInformation*)G4EventManager::GetEventManager()->GetConstCurrentEvent()->GetUserInformation();
    eventInformation->SimTrack.TrackId.emplace_back(aTrack->GetTrackID());
    eventInformation->SimTrack.ParentTrackId.emplace_back(aTrack->GetParentID());
    eventInformation->SimTrack.PdgId.emplace_back(aTrack->GetDefinition()->GetPDGEncoding());
    eventInformation->SimTrack.TrackLength.emplace_back(aTrack->GetTrackLength());

}
