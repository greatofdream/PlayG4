#ifndef SKG4ROOTFILE_HH
#define SKG4ROOTFILE_HH 1

// For C++
#include <vector>

// For Geant4
#include "globals.hh"

// For ROOT 
#include "TFile.h"
#include "TTree.h"
#include "TList.h"
#include "TBranch.h"
// DataType
#include "PlayG4Struct.hh"
class PlayG4Storage{
public:
    static PlayG4Storage* GetInstance();
    PlayG4Storage();
    ~PlayG4Storage();
    void CreateFile(G4String fname);
    void CreateBranchesForTruthRoot();
    void CreateBranchesForSensorRoot();
    void FillMCTruth(const PlayG4SimTruthTree_t &truth);
	void WriteData();
    G4String fileName;

private:
    TFile* fPlayG4File;
    TTree* truthTree;
    static PlayG4Storage* instance;
    PlayG4SimTruthTree_t SimTruth;
    std::vector<int> testarray;
    // PlayG4SimTrackTree_t SimTrack;
};
#endif
