#ifndef PlayG4PhysicsList_hh
#define PlayG4PhysicsList_hh

#include <string>
#include "G4VModularPhysicsList.hh"
#include "globals.hh"
#include "PlayG4PhysicsListMessenger.hh"

class PlayG4PhysicsList: public G4VModularPhysicsList{
public:
    PlayG4PhysicsList();
    virtual ~PlayG4PhysicsList();

    // virtual void ConstructParticle();
    // virtual void ConstructProcess();
    void SetPhysicsListEM(const G4String& name);
    virtual void SetCuts();
private:
    G4String fEmName;
    PlayG4PhysicsListMessenger*   fMessenger;  
};
#endif