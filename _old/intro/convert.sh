for entry in "."/*.jpg
do
  convert $entry -resize 1920x1080 $entry
done
echo "DONE"
