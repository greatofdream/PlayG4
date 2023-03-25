#ifndef PlayG4PHYSICSLISTMESSENGER_HH
#define PlayG4PHYSICSLISTMESSENGER_HH 1

#include "G4UImessenger.hh"
#include "globals.hh"

class PlayG4PhysicsList;
class G4UIdirectory;
class G4UIcmdWithAString;

class PlayG4PhysicsListMessenger: public G4UImessenger{
public:
    PlayG4PhysicsListMessenger(PlayG4PhysicsList*);
   ~PlayG4PhysicsListMessenger();

    virtual void SetNewValue(G4UIcommand*, G4String);

private:  
    PlayG4PhysicsList*        fPhysicsList;
    G4UIdirectory*      fPhysDir;
	G4UIcmdWithAString* fEMListCmd;

};
#endif