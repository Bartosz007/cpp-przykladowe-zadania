set xrange [-1 : 1]
set title 'Wykres funkcji (1/(1+10x^6) oraz uzyskanych wielomianów interpolacyjnych'
set ylabel 'f(x)'
set xlabel 'x'
set grid 
plot "wykres.txt" using 1:2 with lines lc "#ff0000" title "Interpolowana funkcja", "wykres.txt" using 1:3 with points pt 1 lc "#0000ff" title "Węzły równoodległe", "wykres.txt" using 1:4 with points pt 2 lc "#0ff00" title "Węzły Czybyszewa"
