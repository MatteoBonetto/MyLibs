set terminal pngcairo
set output 'Plot/std changing X euler angle.png'
set title 'std changing X euler angle'
set xlabel 'X[mm] axis'
set ylabel 'Z[mm] axis'
set key box opaque
set key right top
plot 'Plot/data.dat' with points pt 7 ps 1.5
