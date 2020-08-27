set title 'Wykres dla t = 0.748699'
set ylabel 'y'
set xlabel 'x'
set grid 
plot "zadanie2lb2.txt" using 1:2 with lines lc "#ff0000" title "Rozwiązanie analityczne",\
"zadanie2lb2.txt" using 1:3 with points pt 1 lc "#0000ff" title "Klasyczna metoda bezposrednia"

