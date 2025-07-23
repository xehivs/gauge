#!/bin/bash
clear
make
rm -f cache/*.bmp
rm -f smooth/*.png
kitty icat docs/foo.bmp
python drivers/$1.py > tracks/$1.txt
./arche $2 < tracks/$1.txt
python analyze.py
# python analyze2.py
./scripts/movie.sh