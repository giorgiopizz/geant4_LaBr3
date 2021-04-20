#include <string>
#include <TTree.h>
#include <TFile.h>
#include "G4UnitsTable.hh"
#include "Hit.hh"
#include "TrackParticle.hh"
#include "SensitiveDetector.hh"
#include "EventAction.hh"
#include "TrackParentParticle.hh"
#include "G4Types.hh"

class TFile;

class RootSaver
{
public:
    RootSaver();
    ~RootSaver();

    typedef std::map<G4int, TrackParticle*> trackMap_t;

    void CreateTree (const std::string& filename = "tree", const std::string& treeName = "Tree");

    void CloseTree();

    void AddEvent(trackMap_t tMap, G4int evID);

    TFile * rootFile;

    TTree * rootTree;

    unsigned int runCounter;

    Int_t Tot_Tracks;

    Int_t * PartID;
    Int_ * Part_Moth_ID;

    Int_t * PartType;
    Int_t * MothPartType;
    Float_t * Part_EnDep;
    Float_t * MothPart_EnDep;

    Float_t * Part_zStart;
    Float_t * MothPart_zStart;

    Float_t * Part_tStart;
    Float_t * MothPart_tStart;

    Int_t Event_ID;

    typedef std::map<G4int, TrackParentParticle*> trackParentMap_t;

    trackParentMap_t GetParentProperties(trackMap_t TParticleMap);

};
