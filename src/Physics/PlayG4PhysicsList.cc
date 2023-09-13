#include "PlayG4PhysicsList.hh"
#include "G4DecayPhysics.hh"
#include "G4EmStandardPhysics.hh"
#include "G4EmStandardPhysics_option1.hh"
#include "G4EmLivermorePhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PlayG4PhysicsList::PlayG4PhysicsList()
: G4VModularPhysicsList(), fEmName(""),fMessenger(0){
  SetVerboseLevel(1);
    fMessenger = new PlayG4PhysicsListMessenger(this);
  // Default physics
    RegisterPhysics(new G4DecayPhysics());
    // EM Physics is set in following function
    fEmName = "StandardPhysics";
    RegisterPhysics(new G4EmStandardPhysics());
  // Radioactive decay
  RegisterPhysics(new G4RadioactiveDecayPhysics());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PlayG4PhysicsList::~PlayG4PhysicsList()
{
    delete fMessenger;
	// delete fEmPhysicsList;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// EM physics
void PlayG4PhysicsList::SetPhysicsListEM(const G4String& name){
    if (name == fEmName) return;
    fEmName = name;
    if (name == "StandardPhysics") {
        ReplacePhysics(new G4EmStandardPhysics());
    } else if ( name == "StandardPhysics_option1") {
        ReplacePhysics(new G4EmStandardPhysics_option1());
    } else if ( name == "LivermorePhysics") {
        ReplacePhysics(new G4EmLivermorePhysics());
    } else {
        // fall into standard
        ReplacePhysics(new G4EmStandardPhysics());
    }
}

void PlayG4PhysicsList::SetCuts()
{
  G4VUserPhysicsList::SetCuts();
}