#include "Plots.h"

void Plot(double m, double c, std::string title, std::string data_file, std::string xlabel, std::string ylabel) {
    // Create gnuplot script
    std::ofstream scriptFile("Plot/plot_script.gp");
    scriptFile << "set terminal pngcairo\n";
    scriptFile << "set output 'Plot/Figures/" << title << ".png'\n";
    scriptFile << "set title '" << title << "'\n";
    scriptFile << "set xlabel '" << xlabel << "'\n";
    scriptFile << "set ylabel '" << ylabel << "'\n";
    scriptFile << "set key box opaque\n";  // Add an opaque box around the legend
    scriptFile << "set key right top\n";  // Position the legend box at the top right

    scriptFile << "f(x) = " << m << " * x + " << c << "\n";

    if (data_file != "" && std::filesystem::exists(data_file)) {
        // If data file is provided and exists, plot both scatter and line
        scriptFile << "plot '" << data_file << "' with points pt 7 ps 1.5, \\\n";
        scriptFile << "     f(x) with lines lw 2\n";
    } else {
        // If no data file, just plot the line
        scriptFile << "plot f(x) with lines lw 2\n";
    }
    
    scriptFile.close();

    // Run gnuplot with the script
    system("gnuplot Plot/plot_script.gp");

    std::cout << "Plot created as " << title << ".png\n";
}

void Plot_Function(std::string title, std::string data_file, std::string function, std::string xlabel, std::string ylabel) {
    // Create gnuplot script
    std::ofstream scriptFile("Plot/plot_script.gp");
    scriptFile << "set terminal pngcairo\n";
    scriptFile << "set output 'Plot/Figures/" << title << ".png'\n";
    scriptFile << "set title '" << title << "'\n";
    scriptFile << "set xlabel '" << xlabel << "'\n";
    scriptFile << "set ylabel '" << ylabel << "'\n";
    scriptFile << "set key box opaque\n";  // Add an opaque box around the legend
    scriptFile << "set key right top\n";  // Position the legend box at the top right

    scriptFile << function << "\n";

    if (data_file != "" && std::filesystem::exists(data_file)) {
        // If data file is provided and exists, plot both scatter and line
        scriptFile << "plot '" << data_file << "' with points pt 7 ps 1.5, \\\n";
        scriptFile << "     f(x) with lines lw 2\n";
    } else {
        // If no data file, just plot the line
        scriptFile << "plot f(x) with lines lw 2\n";
    }
    
    scriptFile.close();

    // Run gnuplot with the script
    system("gnuplot Plot/plot_script.gp");

    std::cout << "Plot created as " << title << ".png\n";
}

void Scatter_Plot(std::vector<double> x, std::vector<double> y, std::string title, std::string data_file, std::string xlabel, std::string ylabel) {

    // Write data to a temporary file
    std::ofstream dataFile("Plot/data.dat");
    for (size_t i = 0; i < x.size(); ++i) {
        dataFile << x[i] << " " << y[i] << "\n";
    }
    dataFile.close();

    // Create gnuplot script
    std::ofstream scriptFile("Plot/plot_script.gp");
    scriptFile << "set terminal pngcairo\n";
    scriptFile << "set output 'Plot/Figures/" << title << ".png'\n" ;
    scriptFile << "set title '" << title << "'\n";
    scriptFile << "set xlabel '" << xlabel << "'\n";
    scriptFile << "set ylabel '" << ylabel << "'\n";
    //scriptFile << "set xrange [" << -24 << ":" << -4 << "]\n";
    //scriptFile << "set yrange [" <<  << ":" << -4 << "]\n";
    scriptFile << "set key box opaque\n";  // Add an opaque box around the legend
    scriptFile << "set key right top\n";  // Position the legend box at the top right
    scriptFile << "plot '" << data_file << "' with points pt 7 ps 1.5\n";
    scriptFile.close();

    // Run gnuplot with the script
    system("gnuplot Plot/plot_script.gp");

    std::cout << "Scatter Plot created as " << title << ".png\n";
}

void Scatter_Plot_3D(const std::vector<double>& x, const std::vector<double>& y, const std::vector<double>& z, const std::string title, const std::string data_file, const std::string xlabel, const std::string ylabel, const std::string zlabel, const bool append){
    // Write data to a temporary file
    std::ofstream dataFile;
    if (append) {
        dataFile.open(data_file, std::ios_base::app);
    }
    else {
        dataFile.open(data_file);
    }

    for (size_t i = 0; i < x.size(); ++i) {
        dataFile << x[i] << " " << y[i] << " " << z[i] << "\n";
    }
    dataFile.close();

    // Create gnuplot script
    std::ofstream scriptFile("Plot/plot_script_3d.gp");
    scriptFile << "set terminal pngcairo size 800,600\n";
    scriptFile << "set output 'Plot/Figures/" << title << ".png'\n";
    scriptFile << "set title '" << title << "'\n";
    scriptFile << "set xlabel '" << xlabel << "'\n";
    scriptFile << "set ylabel '" << ylabel << "'\n";
    scriptFile << "set zlabel '" << zlabel << "'\n";
    scriptFile << "set ticslevel 0\n";
    scriptFile << "splot '" << data_file << "' using 1:2:3 with points pointtype 7 pointsize 1 lc rgb 'blue' notitle\n";
    scriptFile.close();

    // Run gnuplot with the script
    system("gnuplot Plot/plot_script_3d.gp");

    std::cout << "3D Scatter Plot created as Plot/" << title << ".png\n";
}