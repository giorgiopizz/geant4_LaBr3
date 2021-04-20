#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4SystemofUnits.hh"
#include <fstream>


class G4VPrimaryGenerator;

class PrimaryGeneratorAction: public G4VUserPrimaryGeneratorAction{
public:
    PrimaryGeneratorAction();
    ~PrimaryGeneratorAction();

    void GeneratePrimaries(G4Event *);

private:
    G4VPrimaryGenerator * InitializeGPS();
    G4VPrimaryGenerator * gun;
    std::ofstream * outfile;
};
