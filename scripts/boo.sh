#!/bin/bash
clear
make
rm -f cache/*.bmp
rm -f smooth/*.png
rm -f gear/*.png
kitty icat docs/foo.bmp
python drivers/$1.py $2 > tracks/$1.txt
./arche $2 < tracks/$1.txt
python scripts/analyze.py
# python scripts/analyze2.py
python scripts/plot_foo.py
./scripts/movie.sh