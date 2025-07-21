#!/bin/bash
make
rm -f cache/*.bmp
kitty icat docs/foo.bmp
python drivers/$1.py > tracks/$1.txt
./arche $2 <tracks/$1.txt
./scripts/movie.sh
