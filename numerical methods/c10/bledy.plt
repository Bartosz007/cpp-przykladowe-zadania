set title 'Wykres makrymalnych błędów bezwzględnych rozwiązań różnicowych'
set ylabel 'log10(|błędu|)'
set xlabel 'log10(delta t)'
set xrange [-15 : 0]

plot "bledy.txt" using 1:2 title "Metoda bezpośrednia Eulera" with lines lc "#ff0000","bledy.txt" using 1:3 title "Metoda pośrednia Eulera" with lines lc "#0000ff","bledy.txt" using 1:4 title "Metoda pośrednia trapezów" with lines lc "#ff7700"
#    EOF
