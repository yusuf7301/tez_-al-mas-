#include "TankSD.hh"
#include "G4OpticalPhoton.hh"
#include "G4AnalysisManager.hh"
#include "G4Track.hh"
#include "G4StepPoint.hh"

TankSD::TankSD(const G4String& name) : G4VSensitiveDetector(name) {}

G4bool TankSD::ProcessHits(G4Step* aStep, G4TouchableHistory*) {
    G4Track* track = aStep->GetTrack();

    // 1. Sadece optik fotonları filtrele
    if (track->GetDefinition() != G4OpticalPhoton::OpticalPhotonDefinition()) {
        return false; 
    }

    // 2. Foton sınır yüzeyine (kürenin duvarına) çarptı mı?
    G4StepPoint* postStep = aStep->GetPostStepPoint();
    if (postStep->GetStepStatus() == fGeomBoundary) {
        
        // ML için gerekli verileri çek
        G4ThreeVector hitPos = postStep->GetPosition();
        G4double hitTime = postStep->GetGlobalTime();
        G4double energy = track->GetTotalEnergy();
        
        // Verileri CSV tablosuna yaz
        auto analysisManager = G4AnalysisManager::Instance();
        analysisManager->FillNtupleDColumn(0, hitPos.x());
        analysisManager->FillNtupleDColumn(1, hitPos.y());
        analysisManager->FillNtupleDColumn(2, hitPos.z());
        analysisManager->FillNtupleDColumn(3, hitTime);
        analysisManager->FillNtupleDColumn(4, energy);
        analysisManager->AddNtupleRow();
        
        // Duvara çarpan fotonu öldür (simülasyonu hızlandırır)
        track->SetTrackStatus(fStopAndKill);
    }
    return true;
}