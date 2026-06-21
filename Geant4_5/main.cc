#include "G4RunManagerFactory.hh"
#include "G4UImanager.hh"
#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"

// Kendi yazdığımız sınıfları dahil ediyoruz
#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "ActionInitialization.hh"

int main(int argc, char** argv) {
    // 1. Kullanıcı Arayüzünü Başlat
    G4UIExecutive* ui = nullptr;
    if (argc == 1) {
        ui = new G4UIExecutive(argc, argv);
    }

    // 2. Run Manager (Simülasyon Yöneticisi) Oluştur
    auto* runManager = G4RunManagerFactory::CreateRunManager();

    // 3. Zorunlu Sınıfları Run Manager'a Tanıt
    runManager->SetUserInitialization(new DetectorConstruction());
    runManager->SetUserInitialization(new PhysicsList());
    runManager->SetUserInitialization(new ActionInitialization());

    // 4. Görselleştirme Yöneticisini Başlat
    G4VisManager* visManager = new G4VisExecutive;
    visManager->Initialize();

    // 5. Arayüz Komut Yöneticisini Al
    G4UImanager* UImanager = G4UImanager::GetUIpointer();

    // 6. Simülasyonu Çalıştır (Arayüzlü veya Arayüzsüz)
    if (ui) {
        // Eğer argüman yoksa görsel arayüzü aç ve vis.mac dosyasını çalıştır
        UImanager->ApplyCommand("/control/execute vis.mac");
        ui->SessionStart();
        delete ui;
    } else {
        // Eğer dışarıdan makro dosyası verildiyse (Batch mode) onu çalıştır
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command + fileName);
    }

    // Belleği temizle ve çık
    delete visManager;
    delete runManager;

    return 0;
}