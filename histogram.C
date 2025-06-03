void histogram() {
    TH1F *h = new TH1F("h", "Example Histogram;X-axis;Y-axis", 100, -4, 4);
    for (int i = 0; i < 10000; i++) {
        h->Fill(gRandom->Gaus(0, 1));
    }
    h->Draw();
    gPad->SaveAs("histogram.png");
} 