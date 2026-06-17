#!/bin/bash -e
# chmod a+x
# Copyright Jan Unger, Wuppertal
# erstellt: 22.12.16
# update:   14.1.18
#=============================

# Variablen ANPASSEN
#=============================
info="Info: Suchen und Ersetzen - Umlaute, Unterstrich, Leerzeichen, Img"
# Projektverzeichnis
work=~/tex/projekt
# Zeit
timestamp=$(date +"%Y-%h-%d_%H:%M")
copyright="Copyright Jan Unger, Wuppertal"

#=============================
#clear
#cd $work
echo $info

# 's/suchen/ersetzen/g'
echo "  * Umlaute"
find ./ -name "*"  -exec rename 's/ü/ue/g' {} +
find ./ -name "*"  -exec rename 's/ä/ae/g' {} +
find ./ -name "*"  -exec rename 's/ö/oe/g' {} +
find ./ -name "*"  -exec rename 's/Ü/ue/g' {} +
find ./ -name "*"  -exec rename 's/Ä/ae/g' {} +
find ./ -name "*"  -exec rename 's/Ö/oe/g' {} +
find ./ -name "*"  -exec rename 's/ß/ss/g' {} +
echo "  * Unterstrich"
find ./ -name "*"  -exec rename 's/-/_/g'  {} +
echo "  * Leerzeichen"
find ./ -name "*"  -exec rename 's/ //g'   {} +
echo "  * Img"
find ./ -name "*.JPG"  -exec rename 's/.JPG/.jpg/g'  {} +
find ./ -name "*.jpeg" -exec rename 's/.jpeg/.jpg/g' {} +

printf "\n\n"
