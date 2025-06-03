#include <iostream>
#include <TCanvas.h>
#include <TF1.h>

void integral_root() {
    // Definir la función f(x) = x^2
    TF1 *func = new TF1("func", "x*x", -2, 2);

    // Calcular la integral definida en [-2, 2]
    double result = func->Integral(-2, 2);

    // Mostrar el resultado
    std::cout << "Integral of x^2: values [-2,2]: " << result << std::endl;

    // Dibujar la función para visualizarla
    TCanvas *c1 = new TCanvas("c1", "Integral de x^2", 800, 600);
    func->SetLineColor(kBlue);
    func->Draw();
}
