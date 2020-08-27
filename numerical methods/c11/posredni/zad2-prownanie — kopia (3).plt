set title 'Wykres dla t = 0.747734'
set ylabel 'y'
set xlabel 'x'
set grid 
plot "zadanie2lp2.txt" using 1:2 with lines lc "#ff0000" title "Rozwiązanie analityczne",\
"zadanie2lp2.txt" using 1:3 with points pt 1 lc "#00ff00" title "Metoda Cranka-Nicolson z algorytmem Thomasa",\
"zadanie2lp2.txt" using 1:4 with points pt 2 lc "#0000ff" title "Metoda Cranka-Nicolson z metodą iteracyjną Jacobiego"

