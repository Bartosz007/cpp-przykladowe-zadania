set title 'Maksymalna wartość błędu bezwzględnego w funkcji czasu t'
set ylabel 'Błąd'
set xlabel 't'
set grid 
plot "zadanie3lb.txt" using 1:2 with lines lc "#ff0000" title "Klasyczna metoda bezpośrednia"
