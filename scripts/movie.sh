#!/bin/bash
rm -f arche.mp4
# ffmpeg -framerate 30 -pattern_type glob -i 'cache/*.bmp' \
#  -c:v mpeg4 -qscale:v 1 -pix_fmt yuv420p arche.mp4
ffmpeg -framerate 60 -pattern_type glob -i 'smooth/*.png' \
  -c:v mpeg4 -qscale:v 1 -pix_fmt yuv420p arche.mp4
# ffmpeg -framerate 60 -pattern_type glob -i 'gear/*.png' \
#   -c:v mpeg4 -qscale:v 1 -pix_fmt yuv420p gear.mp4
vlc arche.mp4 --loop