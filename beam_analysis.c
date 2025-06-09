void beam_analysis() {
    const double E = 29000.0;  // ksi
    const double I = 184.0;    // in^4
    const double delta_x = 0.005;
    const int N = static_cast<int>(8.0 / delta_x) + 1;

    std::vector<double> x(N), M(N), V(N), y(N);

    for (int i = 0; i < N; ++i) {
        x[i] = i * delta_x;
        M[i] = -9.40 * x[i] + 75.2;
        V[i] = -9.40;
        y[i] = (-1.56 * std::pow(x[i], 3)) + (37.6 * std::pow(x[i], 2)) - (200.96 * x[i]);

        // Apply condition at x = 8
        if (std::abs(x[i] - 8.0) < 1e-6) {
            M[i] += 9.40 * (x[i] - 8);
            V[i] += 9.40;
            y[i] += 1.56 * std::pow((x[i] - 8), 3);
        }
    }

    // Normalize y by (E * I)
    for (int i = 0; i < N; ++i) {
        y[i] /= (E * I);
    }

    // Output the first few values for inspection
    std::cout << "x\tM(x)\tV(x)\ty(x)\n";
    for (int i = 0; i < N; i += 100) {  // change the step if you want more or fewer outputs
        printf("%.3f\t%.3f\t%.3f\t%.6f\n", x[i], M[i], V[i], y[i]);
    }

    // Optional: export to text files or further use in ROOT (e.g., for plotting)
}
