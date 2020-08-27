
set title 'Wykres maksymalnej zależności wartości bezwzględnej dla tmax=1 o kroku h'
set ylabel 'log10(|blad|)'
set xlabel 'log10(h)'
set grid 
plot "zadanie1lb.txt" using 1:2 with lines lc "#ff0000" title "Klasyczna Metoda bezpośrednia",\
"zadanie1lp1.txt" using 1:2 with points pt 2 lc "#00ff00" title "Metoda Cranka-Nicolson z algorytmem Thomasa",\
"zadanie1lp2.txt" using 1:2 with points pt 1 lc "#0000ff" title "Metoda Cranka-Nicolson z Metodą iteracyjną Jakobiego"
