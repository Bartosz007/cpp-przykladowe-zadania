set title 'Metoda pośrednia trapezów'
set ylabel 'y(t)'
set xlabel 't'


plot "wyniki_stabilne.txt" using 1:2 title "Rozwiązanie Analityczne" with lines lc "#ff0000","wyniki_stabilne.txt" using 1:5 title "Rozwiązanie analityczne" with points lc "#0000ff" pt 1
#    EOF
