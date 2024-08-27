set terminal pngcairo size 800,600
set output 'Plot/3D Plot perfect.png'
set title '3D Plot perfect'
set xlabel 'X[mm] axis'
set ylabel 'Z[mm] axis'
set zlabel 'Y[mm] axis'
set ticslevel 0
splot 'Plot/data.dat' using 1:2:3 with points pointtype 7 pointsize 1 lc rgb 'blue' notitle
