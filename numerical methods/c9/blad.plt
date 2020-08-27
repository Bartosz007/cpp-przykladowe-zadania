set title 'Wykres zależności maksymalnych błędów bezwzględnych przybliżeń rozwiązań'
set ylabel 'log10(|błąd|)'
set xlabel 'log10(h)
set xrange [-7 : 0]
set yrange [-16 : -1]

plot "blad.txt" using 1:2 title "Dyskretyzacja kowekcjonalna trzypunktowa" with lines,"blad.txt" using 1:3 title "Dyskretyzacja Numerowa" with lines
#    EOF
