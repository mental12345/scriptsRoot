#include <TApplication.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TMatrixD.h>
#include <TVectorD.h>
#include <iostream>

void fea() {
    // Stiffness matrix for a simple 2D truss with 2 nodes
    TMatrixD K(4, 4); 

    // Material properties
    double E = 210e9; // Young's modulus (Pa)
    double A = 0.01;  // Cross-sectional area (m^2)
    double L = 1.0;   // Length of the truss element (m)

    // Stiffness coefficient
    double k = (E * A) / L;

    // Element stiffness matrix (global coordinates)
    K(0,0) = k; K(0,2) = -k;
    K(2,0) = -k; K(2,2) = k;
    K(1,1) = 1e30; // Fixed node (large value simulating constraint)
    K(3,3) = 1e30;

    // Force vector (force of 1000 N at node 2 in x direction)
    TVectorD F(4);
    F(2) = 1000;

    // Solve for displacements
    K.Invert();
    TVectorD u = K * F;

    // Original positions of nodes (Node 1 at (0,0), Node 2 at (L,0))
    double x1 = 0.0, y1 = 0.0;
    double x2 = L, y2 = 0.0;

    // Deformed positions
    double scale = 1e5; // Scaling factor for visualization
    double dx2 = u(2) * scale; // x displacement of node 2
    double dy2 = u(3) * scale; // y displacement of node 2

    // Set up ROOT plot
    TApplication app("app", nullptr, nullptr);
    TCanvas *c = new TCanvas("c", "2D Truss FEA", 800, 600);
    
    // Original truss (blue line)
    TGraph *original = new TGraph(2);
    original->SetPoint(0, x1, y1);
    original->SetPoint(1, x2, y2);
    original->SetLineColor(kBlue);
    original->SetLineWidth(2);
    original->SetTitle("Truss FEA: Original and Deformed Shapes;X (m);Y (m)");
    original->Draw("AL");

    // Deformed truss (red line)
    TGraph *deformed = new TGraph(2);
    deformed->SetPoint(0, x1, y1);
    deformed->SetPoint(1, x2 + dx2, y2 + dy2);
    deformed->SetLineColor(kRed);
    deformed->SetLineWidth(2);
   
}