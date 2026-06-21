#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"

class DetectorConstruction : public G4VUserDetectorConstruction {
  public:
    DetectorConstruction() = default;
    virtual ~DetectorConstruction() = default;

    virtual G4VPhysicalVolume* Construct() override;
    virtual void ConstructSDandField() override;
};

#endif