set title 'Wykres zależności maksymalnych błędów bezwzględnych przybliżeń rozwiązań'
set ylabel 'log10(|błąd|)'
set xlabel 'log10(h)
set xrange [-0.2 : 1.2]
set yrange [-0.2 : 1.2]

plot "wykres.txt" using 1:2 title "Rozwiązanie Analityczne" with lines lc "#ff0000","wykres.txt" using 1:3 title "Dyskretyzacja konwekcjonalna trzypunktowa" with points lc "#00ff00" pt 2,"wykres.txt" using 1:4 title "Dyskretyzacja Numerowa" with points lc "#0000ff" pt 1
#    EOF
