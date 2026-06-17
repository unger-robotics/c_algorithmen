#!/bin/bash -e
# chmod a+x
# Copyright Jan Unger, Wuppertal
# erstellt: 1.1.18
# update:   14.1.18
#=============================

# Variablen ANPASSEN
#=============================
info="Info: Backup - Projekt\n Voraussetzung: Laufwerke einhängen\n    * oc\n    * daten\n    * EXBACKUP (Usbstick)"
# Projektverzeichnis
work=~/c
ziel=~/backup-projekte
projekt=c_algorithmen
archiv=ARCHIV
HDDWin10=/media/jan/oc/projekte
HDDDaten=/media/jan/daten/linux/c
USBSTICK=/media/jan/EXBACKUP/backup-projekte

# Zeit
timestamp=$(date +"%Y-%h-%d_%H:%M")
copyright="Copyright Jan Unger, Wuppertal"
gruss="Hasta la vista Baby"

#=============================
#clear
cd $work/$projekt
echo $info

#echo "Directory prüfen"
if [ ! -d $HDDWin10 ]; then echo "Fehler: $HDDWin10 - Laufwerk einhängen" ; exit 1 ; fi
if [ ! -d $HDDDaten ]; then echo "Fehler: $HDDDaten - Laufwerk einhängen" ; exit 1 ; fi
if [ ! -d $USBSTICK ]; then echo "Fehler: $USBSTICK - Laufwerk einhängen" ; exit 1 ; fi

# c/c++ aufräumen
cd projekt
make clean

# rechte
# Berechtigung fuer Dateien & Verzeichnisse setzen
sudo find . -type d -exec chmod -R 775 {} +
sudo find . -type f -exec chmod -R 664 {} +

# execute
sudo find . -name '*.sh' -exec chmod -R 774 {} +
#sudo find . -name '*.py' -exec chmod -R 774 {} +
sudo find . -name '*.x'  -exec chmod -R 774 {} +

## gruppe erstellen
#sudo addgroup hacker  
## Benutzer einer gruppe hinzufügen 
#sudo usermod -aG dialout jan
#sudo usermod -aG hacker jan
#sudo usermod -aG www-data jan

# Gruppe hacker 
sudo find . -type d -exec chown -R jan.hacker {} +
sudo find . -type f -exec chown -R jan.hacker {} +

# Git
### git konfig
## git config --global user.name "Jan Unger"
## git config --global user.email "info@bw1.eu"
## git init
#git add -A
#git commit -m 'Kommentar Version'
#git status
#git log

cd ..

## zip -r /ziel.zip /quelle
## tar -vczf /$(date +'%Y-%h-%d')-ziel.tar.gz /quelle
## rsync -avuch --progress --delete  --exclude-from=./rsync.excludes /quelle /ziel
### rsync - Dateisystem: NTFS (--no-perms --no-owner --no-group)
## rsync -avuch --no-perms --no-owner --no-group --progress --delete  --exclude-from=./rsync.excludes /quelle /ziel

janein=1
while [ "$janein" -eq 1 ]; do
	clear
	printf "\n $info \n"
	printf "\n  1) HDDUbuntu"
	printf "\n  2) Archiv: zip, tar.gz - HDDUbuntu - HDDWin10 - HDDDaten - USBSTICK"
	printf "\n 10) Beenden?"
	a=
	while [ -z "$a" ]; do
		printf "\n\nGeben Sie eine Zahl ein: "
		read a
		# Zeichenketten eliminieren ,die Zeichen ausser 0-9  enthalten
		a=${a##*[^0-9]*}
		if [ -z "$a" ]; then
			echo "Ungueltige Eingabe, bitte wiederholen"
		fi
	done

	echo "==========================="
	printf "\n"

	if [ $a -eq 1 ]; then
		echo "HDDUbuntu"

		# HDDUbuntu: rsync 	
		rsync -avuch --progress --delete  . $ziel/$projekt

	elif [ $a -eq 2 ]; then
		echo "Archiv: zip, tar.gz - HDDUbuntu - HDDWin10 - HDDDaten - USBSTICK"
		# Archiv - zip
		zip -r $ziel/$archiv/$projekt.zip .

		# Archiv - tar.gz
		tar -vczf $ziel/$archiv/$(date +'%Y-%h-%d')-$projekt.tar.gz .

		# HDDUbuntu: rsync 	
		rsync -avuch --progress --delete --exclude-from=./rsync.excludes . $ziel/$projekt

		# HDDWin10: rsync - Dateisystem: NTFS (--no-perms --no-owner --no-group)
		rsync -avuch --no-perms --no-owner --no-group --progress --delete --exclude-from=./rsync.excludes . $HDDWin10/$projekt

		# HDDDaten: rsync - Dateisystem: NTFS (--no-perms --no-owner --no-group)
		rsync -avuch --no-perms --no-owner --no-group --progress --delete --exclude-from=./rsync.excludes . $HDDDaten/$projekt

		# USBSTICK: rsync - Dateisystem: NTFS (--no-perms --no-owner --no-group)
		rsync -avuch --no-perms --no-owner --no-group --progress --delete --exclude-from=./rsync.excludes . $USBSTICK/$projekt

		# mount
		sync

	else
		printf "$gruss\n\n"; break
	fi
done
