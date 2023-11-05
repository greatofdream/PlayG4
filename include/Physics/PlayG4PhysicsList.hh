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

    virtual void ConstructParticle();
    void SetPhysicsListEM(const G4String& name);
    //void SetPhysicsListDecay(const G4String& name);
    void SetPhysicsListOp(const G4String& name);
    //void SetPhysicsListExtraEM(const G4String& name);
    virtual void SetCuts();
private:
    G4VPhysicsConstructor*  fEmPhysicsList;	//Electromagnetic
    G4VPhysicsConstructor*  fOpPhysicsList;	//Optical
    G4VPhysicsConstructor*  fDePhysicsList;	//Decay
    G4VPhysicsConstructor*  fExtraEMPhysicsList;//Extra Electromagnetic
    G4String fEmName;
    G4String fOpName;
    G4String fDecayName;
    G4String fExtraEMName;
    PlayG4PhysicsListMessenger*   fMessenger;  
};
#endif
