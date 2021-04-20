#include "RootSaver.hh"
#include "Hit.hh"
#include "TTree.h"
#include "TFile.h"
#include "TMath.h"
#include <sstream>
#include <iostream>
#include <cassert>
#include "G4Types.hh"
#include "TrackParentParticle.hh"
#include "G4UnitsTable.hh"

RootSaver::RootSaver():
    rootFile(0),
    rootTree(0),
    runCounter(0),
    Tot_Tracks(0)
{
    PartID = new Int_t[10000];
    Part_Moth_ID = new Int_t[10000];
    ...
    ...
    ...
}

RootSaver::~RootSaver()
{
    if(rootTree)
    {
        CloseTree();
    }
}
void RootSaver::CreateTree(const std::string & filename, const std::string & treeName)
{
    if(rootTree)
    {
        std::cerr << "TTree already created, first close tree" << std::endl;
    }
    std::ostringstream fn;
    fn << fileName << "_run" << runCounter++ << ".root";
    rootFile = TFile::Open(fn.str().data(), "recreate");
    if(rootFile = 0 || rootFile ->isZombie())
    {
        G4cerr << "error opening the file" << fn.str() << "Ttree will not be saved" << G4endl;
        return;
    }
    else
    {
        G4cout << "rootFile correctly opened " << G4endl;
        G4cout << "Name of the File: " << rootFile -> GetName() << G4endl;
    }
    rootTree = new TTree (treeName.data(), treeName.data);

    //define the branches

    rootTree -> Branch("ntracks", &Tot_Tracks, "ntracks/I2");
    rootTree->Branch("id", PartID, "id[ntracks]/I2");
    ...

    rootTree->Branch("edep", Part_EnDep, "edep[ntracks]/F");

}


void RootSaver::CloseTree()
{
    if(rootTree)
    {
        G4cout << "Writing ROOT tree: " << rootTree -> GetName() << G4endl;
        rootTree->Print();

        rootFile->ReOpen("update");
        if(rootTree->Write() != 0) G4cout << "Tree correctly written in the file " << G4endl;

        else G4cout << "Problem writing the tree" << G4endl;

        rootFile->Close();
        delete[] PartID;
        ...
    }
}
void RootSaver::AddEvent( trackMap_t trackMap, G4int evID)
{
    if(rootTree ==0) return;
    Event_ID = evID;
    trackParentMap_t trackParentMap = this->GetParentProperties(trackMap);

    Tot_Tracks = trackParentMap.size();
    trackParentMap_t::iterator itt = trackParentMap.begin();
    trackParentMap_t::iterator end = trackParentMap.end();
    Int_t i = 0;
    if (Tot_Tracks<10000)
    {
        for(; itt!=end; itt++)
        {
            PartID[i] = itt->first();
            Part_Moth_ID[i] = (itt->second) -> GetMothPartID();
            ...
        }
        if(Tot_Tracks>0) rootTree->Fill();
    }
}
