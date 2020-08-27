set title 'Błedy względne dla x = 3, stosując kwadratury prostokątów'
set ylabel 'log10("błędu")'
set xlabel 'log10(h)'
set grid 
plot "blad.txt" using 1:2 with lines lc "#ff0000" title "Kwadratura prostokątów - interpolacja po lewej stronie",\
"blad.txt" using 1:3 with points pt 1 lc "#0000ff" title "Kwadratura prostokątów - interpolacja po prawej stronie",\
"blad.txt" using 1:4 with lines lc "#00ff00" title "Kwadratura prostokątów - interpolacja po srodku stronie",\
"blad.txt" using 1:5 with lines lc "#00ffff" title "Kwadratura trapezów",\
"blad.txt" using 1:6 with lines lc "#ff00ff" title "Kwadratura parabol"
