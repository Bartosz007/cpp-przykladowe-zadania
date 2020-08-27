set title 'Wykres zależności błędów bezwzględnych przybliżeń różnicowych f(log10(x))=log10(|błąd|)'
set ylabel 'log10(|błąd|)'
set xlabel 'log10(h)

## Last datafile plotted: "plo.txt"
plot "blad_double.txt" using 1:2 title "Dwupunktowa-progresywna f(0)" with lines,"blad_double.txt" using 1:3 title "Dwupunktowa-progresywna f(PI/4)" with lines,"blad_double.txt" using 1:4 title "Dwupunktowa-centralna f(PI/4)" with lines,"blad_double.txt" using 1:5 title "Dwupunktowa-wsteczna f(PI/4)" with lines,"blad_double.txt" using 1:6 title "Dwupunktowa-wsteczna f(PI/2)" with lines,"blad_double.txt" using 1:7 title "Trzypunktowa-progresywna f(0)" with lines,"blad_double.txt" using 1:8 title "Trzypunktowa-progresywna f(PI/4)" with lines,"blad_double.txt" using 1:9 title "Trzypunktowa-wsteczna f(PI/4)" with lines,"blad_double.txt" using 1:10 title "Trzypunktowa-wsteczna f(PI/2)" with lines
#    EOF
