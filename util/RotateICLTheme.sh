#!/bin/sh
#―――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――
# Name: RotateICLTheme.sh
# Desc: Creates vertical images from the horizontal versions of a theme's
#	controls (for orientable controls).
# Reqs: ImageMagick
# Date: 2022-06
#―――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――

ORIENTABLES="Button SliderThumb SliderTriangle"

THEME_ROOT="$1"
if test -z "$THEME_ROOT" -o ! -d "$THEME_ROOT/Horizontal"; then
	echo "Usage: $(basename $0) theme_root"
	if test -n "$THEME_ROOT"; then
		echo ""
		echo "There is no 'Horizontal' directory under the given theme root, $THEME_ROOT."
		echo "Please make sure you have your theme in the proper format."
	fi
	exit 2
fi

for orientable in $ORIENTABLES; do
	mkdir -p "$THEME_ROOT/Vertical/$orientable"
	for file in $THEME_ROOT/Horizontal/$orientable/*; do
		convert -rotate "90" "$file" "$THEME_ROOT/Vertical/$orientable/$(basename "$file")"
	done
done
