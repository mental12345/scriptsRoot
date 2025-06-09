void advanced_integrals() {
    gROOT->Reset();

    // Integral 1: Polynomial (already known)
    TF1 *f1 = new TF1("f1", "x*x", 0, 3);
    double i1 = f1->Integral(0, 3);
    std::cout << "∫ x^2 dx from 0 to 3 = " << i1 << std::endl;

    // Integral 2: sin(x)
    TF1 *f2 = new TF1("f2", "sin(x)", 0, TMath::Pi());
    double i2 = f2->Integral(0, TMath::Pi());
    std::cout << "∫ sin(x) dx from 0 to pi = " << i2 << std::endl;

    // Integral 3: exp(-x^2)
    TF1 *f3 = new TF1("f3", "exp(-x*x)", -2, 2);
    double i3 = f3->Integral(-2, 2);
    std::cout << "∫ exp(-x^2) dx from -2 to 2 = " << i3 << std::endl;

    // Integral 4: 1 / (1 + x^4)
    TF1 *f4 = new TF1("f4", "1.0 / (1 + pow(x,4))", 0, 5);
    double i4 = f4->Integral(0, 5);
    std::cout << "∫ 1 / (1 + x^4) dx from 0 to 5 = " << i4 << std::endl;

    // Integral 5: log(x)
    TF1 *f5 = new TF1("f5", "log(x)", 1, 10);  // domain must avoid 0
    double i5 = f5->Integral(1, 10);
    std::cout << "∫ log(x) dx from 1 to 10 = " << i5 << std::endl;

    // Integral 6: sin(x)/x (sinc function)
    TF1 *f6 = new TF1("f6", "x==0 ? 1 : sin(x)/x", -10, 10);  // handle x=0
    double i6 = f6->Integral(-10, 10);
    std::cout << "∫ sin(x)/x dx from -10 to 10 = " << i6 << std::endl;

    // Integral 7: Custom user-defined C++ function: f(x) = sqrt(x) * cos(x)
    auto myfunc = [](double *x, double *) {
        return std::sqrt(x[0]) * std::cos(x[0]);
    };
    TF1 *f7 = new TF1("f7", myfunc, 0, 5, 0);
    double i7 = f7->Integral(0, 5);
    std::cout << "∫ sqrt(x) * cos(x) dx from 0 to 5 = " << i7 << std::endl;

    // Optional: Plot all functions
    f1->SetLineColor(kBlue);      f2->SetLineColor(kRed);
    f3->SetLineColor(kGreen+2);   f4->SetLineColor(kMagenta);
    f5->SetLineColor(kOrange);    f6->SetLineColor(kCyan+2);
    f7->SetLineColor(kBlack);

    f1->Draw();
    f2->Draw("SAME"); f3->Draw("SAME"); f4->Draw("SAME");
    f5->Draw("SAME"); f6->Draw("SAME"); f7->Draw("SAME");

    auto legend = new TLegend(0.55,0.5,0.88,0.88);
    legend->AddEntry(f1, "x^{2}", "l");
    legend->AddEntry(f2, "sin(x)", "l");
    legend->AddEntry(f3, "exp(-x^{2})", "l");
    legend->AddEntry(f4, "1 / (1 + x^{4})", "l");
    legend->AddEntry(f5, "log(x)", "l");
    legend->AddEntry(f6, "sin(x)/x", "l");
    legend->AddEntry(f7, "sqrt(x) * cos(x)", "l");
    legend->Draw();
}
