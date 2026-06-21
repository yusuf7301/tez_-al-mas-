#include "DetectorConstruction.hh"
#include "TankSD.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Orb.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4SDManager.hh"

G4VPhysicalVolume* DetectorConstruction::Construct() {
    G4NistManager* nist = G4NistManager::Instance();
    
    // --- MALZEMELER ---
    G4Material* air = nist->FindOrBuildMaterial("G4_AIR");
    G4Material* water = nist->FindOrBuildMaterial("G4_WATER");

    // Suyun Optik Özellikleri (Çerenkov için zorunlu)
    const G4int num = 2;
    G4double photonEnergy[num] = {2.034*eV, 4.136*eV}; 
    G4double refractiveIndex[num] = {1.33, 1.34};
    G4double absorptionLength[num] = {3.448*m, 4.082*m};

    G4MaterialPropertiesTable* optikTablo = new G4MaterialPropertiesTable();
    optikTablo->AddProperty("RINDEX", photonEnergy, refractiveIndex, num);
    optikTablo->AddProperty("ABSLENGTH", photonEnergy, absorptionLength, num);
    water->SetMaterialPropertiesTable(optikTablo);

    // --- GEOMETRİ ---
    // 1. Evren (World) - 2x2x2 metrelik küp
    G4Box* solidWorld = new G4Box("World", 2.0*m, 2.0*m, 2.0*m);
    G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, air, "World");
    G4VPhysicalVolume* physWorld = new G4PVPlacement(nullptr, G4ThreeVector(), logicWorld, "World", nullptr, false, 0, true);

    // 2. Çerenkov Su Küresi (Yarıçap: 1 metre)
    G4Orb* solidSphere = new G4Orb("WaterSphere", 1.0*m);
    G4LogicalVolume* logicSphere = new G4LogicalVolume(solidSphere, water, "WaterSphere_Log");
    new G4PVPlacement(nullptr, G4ThreeVector(), logicSphere, "WaterSphere", logicWorld, false, 0, true);

    return physWorld;
}

void DetectorConstruction::ConstructSDandField() {
    // Hassas dedektörü yarat ve küreye bağla
    TankSD* cherenkovDetector = new TankSD("CherenkovTankSD");
    G4SDManager::GetSDMpointer()->AddNewDetector(cherenkovDetector);
    SetSensitiveDetector("WaterSphere_Log", cherenkovDetector);
}