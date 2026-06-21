#ifndef TankSD_h
#define TankSD_h 1

#include "G4VSensitiveDetector.hh"
#include "G4Step.hh"

class TankSD : public G4VSensitiveDetector {
  public:
    TankSD(const G4String& name);
    virtual ~TankSD() = default;

    virtual G4bool ProcessHits(G4Step* aStep, G4TouchableHistory* ROhist) override;
};

#endif