#!/bin/bash
make
rm -f foo.bmp
./arche
kitty icat foo.bmp
