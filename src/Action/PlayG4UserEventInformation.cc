// For Geant4
#include "G4Step.hh"

// For PlayG4
#include "PlayG4UserEventInformation.hh"
PlayG4UserEventInformation::PlayG4UserEventInformation()
	:fCeren_PhotonCount(0)
{
    // release the space using swap
    vector<Int_t>().swap(SimTrack.ParentTrackId);

}
PlayG4UserEventInformation::~PlayG4UserEventInformation()
{}

