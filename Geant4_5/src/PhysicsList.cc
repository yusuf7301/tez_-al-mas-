#include "PhysicsList.hh"
#include "G4EmStandardPhysics.hh"
#include "G4OpticalPhysics.hh"

PhysicsList::PhysicsList() : G4VModularPhysicsList() {
    // Standart Elektron/Foton fiziği
    RegisterPhysics(new G4EmStandardPhysics());
    
    // Çerenkov ışımaları için Optik Fizik Modülü
    RegisterPhysics(new G4OpticalPhysics());
}