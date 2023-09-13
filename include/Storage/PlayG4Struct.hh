#ifndef PlayG4Struct_H
#define PlayG4Struct_H 1
#include "TFile.h"
#include "TTree.h"
#include "globals.hh"

struct PlayG4SimStepPoint_t
{
	Int_t nProcessType;
	Int_t nProcessSubType;
	Double_t fX;
	Double_t fY;
	Double_t fZ;
	Double_t fPx;
	Double_t fPy;
	Double_t fPz;
	Double_t fEk;
	Double_t fdE;
	Double_t fTime;
	Int_t nTargetZ;
	Int_t nTargetA;
	std::vector<Int_t> nSecondaryPdgId;
	PlayG4SimStepPoint_t() {nTargetZ=-1; nTargetA=-1;}
};

struct PlayG4SimTrack_t
{
	Int_t nParentTrackId;
	Int_t nTrackId;
	Int_t nPrimaryId;
	Int_t nPdgId;
	std::vector<PlayG4SimStepPoint_t> StepPoints;
	PlayG4SimTrack_t() {}
};

struct PlayG4SimTruthTree_t {
	Int_t RunId;
	Int_t EventId;		// The ID of Event
	Int_t VertexId;
	Int_t VertexRadZ;
	Int_t VertexRadA;
	Int_t nParticle;
	
	Double_t x;
	Double_t y;
	Double_t z;
	Int_t Sec;
	Int_t NanoSec;
	Double_t EkMerged;
	std::vector<Double_t> dEList;	// Energy deposit in tagged volumes
	std::vector<PlayG4SimTrack_t> trackList;
	PlayG4SimTruthTree_t()
	{
		EkMerged = 0;
	}

};
struct PlayG4PrimaryParticle_t {
        Int_t TrackId;
        Int_t PdgId;
        Double_t px;
        Double_t py;
        Double_t pz;
        Double_t Ek;
    PlayG4PrimaryParticle_t()
    {
        TrackId = 0;
        PdgId = 0;
        px = 0;
        py = 0;
        pz = 0;
        Ek = 0;
    }
};

#endif