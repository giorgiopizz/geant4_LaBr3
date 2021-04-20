#include "G4VUserDetectorConstruction.hh"
#include "G4ThreeVector.hh"
#include "G4SystemOfUnits.hh"

 class G4LogicalVolume;
 class G4VPhysicalVolume;
 class G4Material;
 class DetectorMessenger;

 class DetectorConstruction: public G4VUserDetectorConstruction{
 public:
     DetectorConstruction();
     ~DetectorConstruction();
     // construct geometry of the setup
     G4VPhysicalVolume * Construct();

     //update geometry
     void UpdateGeometry();

 private:
     //define needed Materials
     void DefineMaterials();

     //Initialize geometry paramters
     void ComputerParameters();

     //construct the full geometry of the LaBr3 detector

    G4VPhysicalVolume * Construct_LaBr3Detector(); // è uno scintillatore al bromuro di lantasio

    //materials
    G4Material * vacuum;
    G4Material * LaBr3_Mat;
    // logical volumes
    G4LogicalVolume * logicWorld;
    G4LogicalVolume * logicLaBr3;
    //physical volumes
    G4VPhysicalVolume* physiLaBr3;

    //World
    G4double halfWorldLength;

    //LaBr3 detector
    G4double halfLaBr3Det_x;
    G4double halfLaBr3Det_y;
    G4double halfLaBr3Det_z;

    DetectorMessenger * messenger;
};
