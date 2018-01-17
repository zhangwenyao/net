#!/bin/bash
#./gnuplot_eps_pdf.sh graph.plt outfile [...]


if [ $# -lt 2 ];then
  echo "$0 'plt' 'name' [...]"
  exit 1
fi


#gnuplot
plt="$1"
outfile="$2"
shift
shift
gnuplot << EOF
set terminal push
set terminal postscript eps color solid enh lw 1 font "Helvetica, 24"
set out "$outfile.eps"
call "$plt" $@
set output
set terminal pop
EOF

