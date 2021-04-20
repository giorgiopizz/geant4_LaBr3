#include "G4VHit.hh"
#include "G4Allocator.hh"
#include "G4THitsCollection.hh"
#include "TFile.h"
#include "TH1F.h"


class Hit: public G4VHit
{
public:
    //const
    Hit(const G4int layer);

    ~Hit();

    //print hit on a screen
    void Print();
public:
    inline void * operator new(size_t);
    inline void * operator delete(void aHit);

public:
    void AddEdep(const double e) {edep += e;}
    G4double GetEdep () const { return eDep;}
    G4int GetLayerNumber () const {return layerNumber;}

private:
    const G4int layerNumber;
    G4double eDep;
};

typedef G4THitsCollection<Hit> HitCollection;

// new and delete operators

extern G4Allocator<Hit> HitAllocator

inline void Hit::operator new (size_t)
{
    void *aHit;
    aHit = ( void * ) HitAllocator.MallocSingle();
    return aHit;
}

inline void Hit:operator delete (void *aHit)
{
    HitAllocator.FreeSingle((Hit * ) aHit);
}
