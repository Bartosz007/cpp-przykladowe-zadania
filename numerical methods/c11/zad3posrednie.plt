set title 'Maksymalna wartość błędu bezwzględnego w funkcji czasu t'
set ylabel 'Błąd'
set xlabel 't'
set grid 
plot "zadanie3lp.txt" using 1:2 with points pt 1 lc "#00ff00" title "Metoda Cranka-Nicolson z algorytmem Thomasa",\
"zadanie3lp.txt" using 1:3 with lines lc "#0000ff" title "Metoda Cranka-Nicolson z iteracyjną metodą Jacobiego",\
"zadanie3lb.txt" using 1:2 with lines lc "#ff0000" title "Klasyczna metoda bezpośrednia"

