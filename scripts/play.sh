#!/bin/bash
find cache | while read -r file; do
    clear
    kitty icat $file
done