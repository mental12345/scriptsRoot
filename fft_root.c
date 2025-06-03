#include <iostream>
#include <TCanvas.h>
#include <TGraph.h>
#include <TVirtualFFT.h>

void fft_root() {
    const int N = 128;  // Número de puntos
    double x[N], y[N];

    // Generamos una señal de ejemplo: sin(10x) + 0.5cos(20x)
    for (int i = 0; i < N; i++) {
        x[i] = i * 0.1;
        y[i] = sin(10 * x[i]) + 0.5 * cos(20 * x[i]);
    }

    // Crear un gráfico con la señal original
    TGraph *graph = new TGraph(N, x, y);

    // Crear la FFT
    TVirtualFFT *fft = TVirtualFFT::FFT(1, &N, "R2C EX");

    // Insertar los datos en la FFT
    fft->SetPoints(y);
    fft->Transform();

    // Obtener la magnitud de la FFT
    double re, im, magnitude[N/2];
    for (int i = 0; i < N/2; i++) {
        fft->GetPointComplex(i, re, im);
        magnitude[i] = sqrt(re*re + im*im);  // Magnitud de la FFT
    }

    // Crear un gráfico para la FFT
    double freq[N/2];
    for (int i = 0; i < N/2; i++) freq[i] = i;

    TGraph *fftGraph = new TGraph(N/2, freq, magnitude);

    // Dibujar la señal original y su FFT
    TCanvas *canvas = new TCanvas("canvas", "Señal y FFT", 1000, 500);
    canvas->Divide(2, 1);

    // Señal original
    canvas->cd(1);
    graph->SetTitle("Señal original;Tiempo;Amplitud");
    graph->SetLineColor(kBlue);
    graph->Draw("AL");

    // FFT
    canvas->cd(2);
    fftGraph->SetTitle("Transformada Rápida de Fourier (FFT);Frecuencia;Amplitud");
    fftGraph->SetLineColor(kRed);
    fftGraph->Draw("AL");

    // Guardar la imagen
    canvas->SaveAs("fft_result.png");
}
