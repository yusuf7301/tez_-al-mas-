#include "RunAction.hh"
#include "G4AnalysisManager.hh"

RunAction::RunAction() {
    auto analysisManager = G4AnalysisManager::Instance();
    analysisManager->SetDefaultFileType("csv");

    // ML modeli için sütunları tanımla
    analysisManager->CreateNtuple("CherenkovData", "Photon Hits");
    analysisManager->CreateNtupleDColumn("Hit_X");
    analysisManager->CreateNtupleDColumn("Hit_Y");
    analysisManager->CreateNtupleDColumn("Hit_Z");
    analysisManager->CreateNtupleDColumn("Hit_Time");
    analysisManager->CreateNtupleDColumn("Photon_Energy");
    analysisManager->FinishNtuple();
}

void RunAction::BeginOfRunAction(const G4Run*) {
    auto analysisManager = G4AnalysisManager::Instance();
    // Simülasyon başlayınca CherenkovData.csv dosyasını aç
    analysisManager->OpenFile("CherenkovData.csv");
}

void RunAction::EndOfRunAction(const G4Run*) {
    auto analysisManager = G4AnalysisManager::Instance();
    // Simülasyon bitince verileri kaydet ve kapat
    analysisManager->Write();
    analysisManager->CloseFile();
}