#ifndef PlayG4USEREVENTINFORMATION_HH
#define PlayG4USEREVENTINFORMATION_HH 1
// For Geant4
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4VUserEventInformation.hh"
#include "globals.hh"
#include "TVector3.h"
#include "PlayG4Struct.hh"
using namespace std;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
class PlayG4UserEventInformation : public G4VUserEventInformation
{
	public:
		PlayG4UserEventInformation();
		~PlayG4UserEventInformation();
		inline void Print()const{};
		PlayG4SimTrack_t SimTrack;
		PlayG4SimStep_t SimStep; // Default without the photons
		PlayG4SimTrackStep_t SimTrackStep;
		void StoreStep(const G4Step* step);
		void StoreTrack(const G4Track* track);

	private:
		G4int 			fCeren_PhotonCount;
		vector<G4double>	fCeren_GTime;
		vector<G4double>	fCeren_Wavelength;
		vector<TVector3> 	fCeren_Position;
		vector<TVector3>	fCeren_Direction;

};

#endif
