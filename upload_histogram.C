#include <iostream>
#include <fstream>
#include <cstdlib>
#include <TCanvas.h>
#include <TH1F.h>
#include <TRandom.h>

// Función para generar y guardar un histograma
std::string generateHistogram(const std::string& filename) {
    TCanvas *canvas = new TCanvas("canvas", "Histograma", 800, 600);
    TH1F *hist = new TH1F("hist", "Histograma Aleatorio", 50, 0, 100);

    TRandom rnd;
    for (int i = 0; i < 1000; i++) {
        hist->Fill(rnd.Gaus(50, 15)); // Distribución normal centrada en 50
    }

    hist->Draw();
    canvas->SaveAs(filename.c_str());

    std::cout << "Imagen guardada como: " << filename << std::endl;

    delete hist;
    delete canvas;

    return filename;
}

// Función para subir el archivo con curl
void uploadFile(const std::string& filename, const std::string& url) {
    std::string command = "curl -X POST -F \"file=@" + filename + "\" " + url;
    std::cout << "Ejecutando: " << command << std::endl;
    int result = system(command.c_str());  // Ejecuta el comando

    if (result == 0) {
        std::cout << "Archivo subido correctamente." << std::endl;
    } else {
        std::cerr << "Error al subir el archivo." << std::endl;
    }
}

// Función principal
void upload_histogram() {
    std::string filename = "histogram.png";
    std::string upload_url = "https://localhost:8080/upload"; // 🔹 Cambia esto con tu URL

    // Generar histograma y guardarlo como imagen
    generateHistogram(filename);

    // Subir la imagen al servidor
    uploadFile(filename, upload_url);
}
