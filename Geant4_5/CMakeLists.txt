cmake_minimum_required(VERSION 3.16...3.27)
project(CherenkovML)

# Geant4 kütüphanelerini bul (Görselleştirme ve Arayüz modülleri ile birlikte)
find_package(Geant4 REQUIRED ui_all vis_all)

# Geant4'ün standart CMake ayarlarını projeye dahil et
include(${Geant4_USE_FILE})

# include klasöründeki başlık dosyalarını yola ekle
include_directories(${PROJECT_SOURCE_DIR}/include)

# src klasöründeki tüm .cc kaynak dosyalarını topla
file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB HEADERS ${PROJECT_SOURCE_DIR}/include/*.hh)

# Çalıştırılabilir ana dosyayı (main) oluştur
add_executable(CherenkovApp main.cc ${SOURCES} ${HEADERS})

# Geant4 kütüphanelerini bizim projemize bağla
target_link_libraries(CherenkovApp ${Geant4_LIBRARIES})

# Eğer makro dosyaların varsa, build klasörüne kopyalanmasını sağla
file(COPY vis.mac DESTINATION ${CMAKE_CURRENT_BINARY_DIR})