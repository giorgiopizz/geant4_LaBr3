#include "PrimaryGeneratorAction.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4GeneralParticleSource.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"


PrimaryGeneratorAction::PrimaryGeneratorAction()
    : outfile(0),
{
    gun = InitializeGPS();
}
PrimaryGeneratorAction:~PrimaryGeneratorAction()
{
    delete gun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event * anEvent)
{
    gun->GeneratePrimaryVertex(anEvent);
}

//la funzione più importante è initialize gps
G4VPrimaryGenerator * PrimaryGeneratorAction::InitializeGPS()
{
    G4GeneralParticleSource * gps = new G4GeneralParticleSource();

    //particle type
    G4ParticleTable * particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition * gamma = particleTable->FindParticle("gamma");

    gps->GetCurrentSource()->SetParticleDefinition(gamma);

    //set energy distrib.
    G4SPSEnergyDistribution * eneDist = gps->GetCurrentSource()->GetEneDist();
    eneDist->SetEnergyDisType("mono"); // può essere anche gauss
    eneDist->SetMonoEnergy(1.0*MeV);

    //set position distribution
    G4SPSPositionDistribution * posDist = GPS->GetCurrentSource()->GetPosDist();
    posDist->SetPosDisType("Beam"); // può essere point, plane, volume
    posDist->SetCenterCoords(G4ThreeVector(0.0*cm, 0.0*cm, -5.0*m));
    posDist->SetBeamSigmaInX(0.001*mm);
    posDist->SetBeamSigmaInY(0.001*mm);


    //set angular dist.
    G4SPSAnDistribution* andDist = gps->GetCurrentSource->GetAngDist();
    angDist->SetParticleMomentumDirection( G4ThreeVector(0,0,1))); //dir. pos in z
    angDist->SetAngDistType("beam2d");
    angDist->SetBeamSigmaInAngX(0.001*mrad);
    angDist->SetBeamSigmaInAngY(0.001*mrad);
    angDist->DefineAngRefAxes("angref1", G4ThreeVector(-1,0,0));

    return gps;
}
