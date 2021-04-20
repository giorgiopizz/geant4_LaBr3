#include "Hit.hh"
#include "G4UnitsTable.hh"

G4Allocator<Hit> HitAllocator;

Hit::Hit(const G4int layer):
        layerNumber(layer),
        eDep(0)
{
}

Hit::~Hit()
{
}

void Hit::Print()
{
    G4double edep = this.GetEdep();
    G4int layern = this.GetLayerNumber();

    G4cout << " HIT >>>>>>> Energy Deposited : " << G4BestUnit(edep,"Energy")
    << " in laer " << layern << G4endl;
}
