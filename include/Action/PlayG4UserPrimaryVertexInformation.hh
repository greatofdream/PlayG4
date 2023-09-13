#ifndef PlayG4PrimaryVertexInformation_h
#define PlayG4PrimaryVertexInformation_h 1

#include "globals.hh"
#include "G4VUserPrimaryVertexInformation.hh"

class PlayG4PrimaryVertexInformation :
	public G4VUserPrimaryVertexInformation
{
public:
	PlayG4PrimaryVertexInformation() : 
		RadZ(0), RadA(0) {}
	PlayG4PrimaryVertexInformation(int z, int a) :
		RadZ(z), RadA(a) {}

	~PlayG4PrimaryVertexInformation() {}

	void Print() const 
	{ G4cout<<"Z: "<<RadZ<<", A: "<<RadA<<G4endl;}

	int GetZ() {return RadZ;}
	int GetA() {return RadA;}


private:
	int RadZ;
	int RadA;








};






#endif
