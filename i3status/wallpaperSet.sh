n=`shuf -i 1-17 -n 1`

swww img ~/.config/wallpapers/$n.jpg \
  --transition-angle 225             \
  --transition-type grow             \
  --transition-step 10               \
  --transition-pos 1.0,1.0           \
  --transition-fps 60
