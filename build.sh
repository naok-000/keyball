ln -s $(pwd)/qmk_firmware/keyboards/keyball ../__qmk__/keyboards/keyball
qmk compile -j 4 -kb keyball/keyball39 -km my_keymap
mkdir -p tmp
cp ../__qmk__/keyball_keyball39_my_keymap.hex tmp/keyball39.hex
