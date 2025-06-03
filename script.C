void script() {
    TCanvas *c = new TCanvas("c", "3D Canvas", 800, 600);
    
    // Create a 3D histogram
    TH3F *h3 = new TH3F("h3", "3D Histogram", 20, -4, 4, 20, -4, 4, 20, -4, 4);
    h3->FillRandom("gaus", 10000);
    h3->Draw("BOX2");

    // Export the 3D view to a GLTF file
    c->Print("3d_scene.gltf"); // Or use .obj, .vrml, etc.
}
