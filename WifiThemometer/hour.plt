set terminal png size 3840,2160
set title "Outside Ambient Temperature"
set ylabel "Degrees Celcius"
set key off

set xdata time
set timefmt "%s"
set format x "%H:%M"

set xrange [ time(0) - (60 * 60) : time(0) ]

plot "./outside-ambient.tsd" using 1:3 smooth bezier
