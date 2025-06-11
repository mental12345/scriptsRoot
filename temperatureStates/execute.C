{
    // Open the CSV file
    std::ifstream file("temperaturestates-2023.csv");
    if (!file.is_open()) {
        std::cerr << "Failed to open file!" << std::endl;
        return;
    }

    // Read the header line
    std::string line;
    std::getline(file, line); // Skip header line

    // Months for labeling
    std::vector<std::string> months = {"Ene", "Feb", "Mar", "Abr", "May", "Jun", 
                                       "Jul", "Ago", "Sep", "Oct", "Nov", "Dic"};

    // Data containers
    std::map<std::string, std::vector<double>> stateTemperatures; // Stores temperatures for each state
    std::vector<double> nationalAverage(months.size(), 0.0); // Monthly national averages
    int stateCount = 0;

    // Process the data
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string state, value;
        std::vector<double> temperatures;

        // Get the state name
        if (!std::getline(ss, state, ',')) {
            std::cerr << "Error: Missing state name in line: " << line << std::endl;
            continue;
        }

        // Get the monthly temperatures (ignoring the annual average)
        while (std::getline(ss, value, ',')) {
            try {
                temperatures.push_back(std::stod(value));
            } catch (const std::invalid_argument &e) {
                std::cerr << "Error processing value '" << value << "' in line: " << line << std::endl;
                continue;
            }
        }

        // Check if there are enough values (12 months + annual)
        if (temperatures.size() != months.size() + 1) {
            std::cerr << "Error: Incomplete data for state '" << state << "' in line: " << line << std::endl;
            continue;
        }

        // Remove the annual average
        temperatures.pop_back();

        // Add to state data
        stateTemperatures[state] = temperatures;

        // Update national average
        for (size_t i = 0; i < months.size(); ++i) {
            nationalAverage[i] += temperatures[i];
        }
        stateCount++;
    }
    file.close();

    // Finalize the national average
    for (size_t i = 0; i < nationalAverage.size(); ++i) {
        nationalAverage[i] /= stateCount;
    }

    // Plot data
    TCanvas *canvas = new TCanvas("canvas", "State Temperatures", 1200, 800);
    canvas->Divide(2, 3);

    int pad = 1;
    for (const auto &entry : stateTemperatures) {
        canvas->cd(pad++);
        const auto &state = entry.first;
        const auto &temps = entry.second;

        // Create a TGraph for the state
        TGraph *graph = new TGraph(months.size());
        for (size_t i = 0; i < months.size(); ++i) {
            graph->SetPoint(i, i + 1, temps[i]);
        }

        graph->SetTitle((state + ";Month;Temperature (°C)").c_str());
        graph->SetMarkerStyle(20);
        graph->SetMarkerColor(kBlue);
        graph->Draw("APC");

        // Label x-axis with months
        graph->GetXaxis()->SetNdivisions(months.size());
        
        for (size_t i = 0; i < months.size(); i++) {
            graph->GetXaxis()->SetBinLabel(i+12, months[i].c_str());    
        }

        if (pad > 6) break; // Limit to 9 states per canvas
    }

    // Plot national average temperatures
    TCanvas *canvasNational = new TCanvas("canvasNational", "National Average Temperatures", 800, 600);
    TGraph *nationalGraph = new TGraph(months.size());
    for (size_t i = 0; i < months.size(); ++i) {
        nationalGraph->SetPoint(i, i + 1, nationalAverage[i]);
    }

    nationalGraph->SetTitle("National Average Temperatures;Month;Temperature (°C)");
    nationalGraph->SetMarkerStyle(21);
    nationalGraph->SetMarkerColor(kRed);
    nationalGraph->Draw("AP");

    // Label x-axis with months
    nationalGraph->GetXaxis()->SetNdivisions(months.size());
    for (size_t i = 0; i < months.size(); ++i) {
        nationalGraph->GetXaxis()->SetBinLabel(i + 1, months[i].c_str());
    }

    // Save plots
    canvas->SaveAs("state_temperatures.png");
    canvasNational->SaveAs("national_average_temperatures.png");
}
