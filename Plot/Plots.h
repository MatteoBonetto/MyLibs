#ifndef PLOTS_H
#define PLOTS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>

void Scatter_Plot(std::vector<double> x, std::vector<double> y, std::string title, std::string data_file = "Plot/data.dat", std::string xlabel = "X[mm] axis", std::string ylabel = "Z[mm] axis");
// in case the target is to plot a line with previous data, just avoid to give data_file as input, 
// otherwise provide a no existing file such as ""
void Plot(double m, double c, std::string title, std::string data_file = "Plot/data.dat", std::string xlabel = "X[mm] axis", std::string ylabel = "Z[mm] axis");

void Plot_Function(std::string title, std::string data_file = "Plot/data.dat", std::string function = "f(x) = x", std::string xlabel = "X[mm] axis", std::string ylabel = "Z[mm] axis"); 

void Scatter_Plot_3D(const std::vector<double>& x, const std::vector<double>& y, const std::vector<double>& z, const std::string title, const std::string data_file = "Plot/data.dat", const std::string xlabel = "X[mm] axis", const std::string ylabel = "Z[mm] axis", const std::string zlabel = "Y[mm] axis", const bool append = false);

#endif