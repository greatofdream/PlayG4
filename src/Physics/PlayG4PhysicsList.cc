#include "PlayG4PhysicsList.hh"
#include "G4DecayPhysics.hh"
#include "G4EmStandardPhysics.hh"
#include "G4EmStandardPhysics_option1.hh"
#include "G4EmLivermorePhysics.hh"
#include "G4EmExtraPhysics.hh"
#include "G4OpticalPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"

// for particle definition
#include "G4BaryonConstructor.hh"	//p,n,lambda,sigma,xi,omega
#include "G4BosonConstructor.hh"	//gamma,photons,geantino
#include "G4IonConstructor.hh"		//alpha,deutron,triron,He3,genericIon
#include "G4MesonConstructor.hh"	//pion,eta,kaon
#include "G4LeptonConstructor.hh"	//e+-,mu+-,tau+-,neutrino
#include "G4ShortLivedConstructor.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PlayG4PhysicsList::PlayG4PhysicsList()
: G4VModularPhysicsList(), fEmName(""),fMessenger(0){
  SetVerboseLevel(1);
    fMessenger = new PlayG4PhysicsListMessenger(this);
    // EM Physics is set in following function
    fEmName = G4String("StandardPhysics");
    fEmPhysicsList = new G4EmStandardPhysics();
    fOpName = G4String("local");
    fOpPhysicsList = new G4OpticalPhysics();//PlayG4OpticalPhysics();
    fDecayName = G4String("on");
    fDePhysicsList = new G4DecayPhysics();
    fExtraEMName = G4String("on");
    fExtraEMPhysicsList = new G4EmExtraPhysics();

  // Radioactive decay
    RegisterPhysics(fEmPhysicsList);
    RegisterPhysics(fOpPhysicsList);
    RegisterPhysics(fDePhysicsList);
    RegisterPhysics(fExtraEMPhysicsList);
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
// Optical physics
void PlayG4PhysicsList::SetPhysicsListOp(const G4String& name){
    if (name == fEmName) return;
    fEmName = name;
    if (name == "optical") {
        ReplacePhysics(new G4OpticalPhysics());
    } else if ( name == "local") {
        //ReplacePhysics(new PlayG4OpticalPhysics());
    } else {
        // fall into standard
        ReplacePhysics(new G4OpticalPhysics());
    }
}
void PlayG4PhysicsList::SetCuts()
{
  G4VUserPhysicsList::SetCuts();
}

void PlayG4PhysicsList::ConstructParticle()
{
	G4BosonConstructor pBosonConstructor;
	pBosonConstructor.ConstructParticle();

	G4LeptonConstructor pLeptonConstructor;
	pLeptonConstructor.ConstructParticle();

	G4BaryonConstructor pBaryonConstructor;
	pBaryonConstructor.ConstructParticle();

	G4MesonConstructor pMesonConstructor;
	pMesonConstructor.ConstructParticle();

	G4IonConstructor pIonConstructor;
	pIonConstructor.ConstructParticle();

	G4ShortLivedConstructor pShortLivedConstructor;
	pShortLivedConstructor.ConstructParticle();
}
