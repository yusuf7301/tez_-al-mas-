#include "PrimaryGeneratorAction.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction() {
    fParticleGun = new G4ParticleGun(1); // 1 mermi
    
    // Mermiyi elektron olarak ayarla
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition* particle = particleTable->FindParticle("e-");
    fParticleGun->SetParticleDefinition(particle);
    
    // Enerji ve Yön ayarları
    fParticleGun->SetParticleEnergy(500. * MeV);
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(1., 0., 0.)); // X yönünde
    fParticleGun->SetParticlePosition(G4ThreeVector(0., 0., 0.)); // Tam merkezden
}

PrimaryGeneratorAction::~PrimaryGeneratorAction() {
    delete fParticleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) {
    fParticleGun->GeneratePrimaryVertex(anEvent);
}