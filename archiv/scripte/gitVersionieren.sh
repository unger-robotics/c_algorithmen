#!/bin/bash -e
# chmod a+x
# Copyright Jan Unger, Wuppertal
# erstellt: 22.12.16
# update:   14.1.18
#=============================

## git befehle
#git add -A
#git commit -m 'erste Version'
#git status
#git log
#git log --graph --oneline --decorate HEAD master

# Variablen ANPASSEN
#=============================
info="Info: Git - Projekt versionieren"
# Projektverzeichnis
#work=~/tex/projekt
# Zeit
timestamp=$(date +"%Y-%h-%d_%H:%M")
copyright="Copyright Jan Unger, Wuppertal"
gruss="Hasta la vista Baby"

#=============================
#clear
#cd $work
echo $info

janein=1
while [ "$janein" -eq 1 ]; do
	#clear
	#printf "\n $info \n"
	printf "\n  0) Git-Repository anlegen: .git"
	printf "\n  1) Projektversion 001"
  printf "\n  2) Projektversion 002"
	printf "\n  3) Projektversion 003"
  printf "\n  4) Hat sich Projektverzeichnis geändert? git status & git log"
  printf "\n  5) Unterschiede zum Vorgänger o. zwischen Versionen und Version wechseln"
  printf "\n  6) Paralelle Entwicklung: Master + zweiten Entwicklungszweig erstellen"
	printf "\n  7) Testversion 001"
	printf "\n  8) Testversion 002"
	printf "\n  9) Zusammenarbeit (2 Entwickler), bare = Repository ohne einen Workspace (zentrales Repository)"
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

	if [ $a -eq 0 ]; then
		# Git-Repository anlegen 
		## Git-Repository löschen
		echo "*** Git-Repository löschen ***"
		#echo "Directory prüfen"
		if [ -d .git ]; then sudo rm -r .git ; fi

		## Initialisierte leeres Git-Repository
		echo "*** Git-Repository anlegen ***"
		git init

		## git konfig
		echo "*** git konfig ***"
		git config --global user.name "Jan Unger"
		git config --global user.email "info@bw1.eu"
		git config --global core.editor "vim"
		git config --global color.ui true
		git config diff.renames true
		git config merge.conflictstyle diff3
		git config merge.tool kdiff3

		## .gitignore anlegen
		echo "*** .gitignore anlegen ***"
		echo "# ordner/" > .gitignore
		echo "# !file.md = Ausnahme, wird versioniert" >> .gitignore
		echo ".gitignore" >> .gitignore
		echo "*.exe" >> .gitignore
		echo "*.x" >> .gitignore
    echo "*.pdf" >> .gitignore
    echo "*.jpg" >> .gitignore

    # Dateien oder ganze Verzeichnisse unter Git-Verwaltung stellen
    git add -A
    # Aktuellen Projektstand sichern
		git commit -a -m "Projektstart"
    
	elif [ $a -eq 1 ]; then
		# Projektversion
    #echo "Directory prüfen"
		if [ ! -d .git ]; then Git-Repository anlegen ; break; fi 
		echo "*** Projektversion ***"
		# Dateien oder ganze Verzeichnisse unter Git-Verwaltung stellen
    git add -A
    # Aktuellen Projektstand sichern
		git commit -a -m "Projektversion 001"

	elif [ $a -eq 2 ]; then
		# Projektversion 
    #echo "Directory prüfen"
		if [ ! -d .git ]; then Git-Repository anlegen ; break; fi 
		echo "*** Projektversion ***"
		# Dateien oder ganze Verzeichnisse unter Git-Verwaltung stellen
    git add -A
    # Aktuellen Projektstand sichern
		git commit -a -m "Projektversion 002"

	elif [ $a -eq 3 ]; then
		# Projektversion 
    #echo "Directory prüfen"
		if [ ! -d .git ]; then Git-Repository anlegen ; break; fi 
		echo "*** Projektversion ***"
		# Dateien oder ganze Verzeichnisse unter Git-Verwaltung stellen
    git add -A
    # Aktuellen Projektstand sichern
		git commit -a -m "Projektversion 003"

  elif [ $a -eq 4 ]; then
		# Hat sich Projektverzeichnis geändert? git status & git log
    #echo "Directory prüfen"
		if [ ! -d .git ]; then Git-Repository anlegen ; break; fi 
    echo "*** Hat sich Projektverzeichnis geändert? ***"
    git status
    echo "*** git log ***"
		git log --graph --oneline --decorate HEAD master

  elif [ $a -eq 5 ]; then
		# Unterschiede zum Vorgänger o. zwischen Versionen und Version wechseln
    #echo "Directory prüfen"
		if [ ! -d .git ]; then Git-Repository anlegen ; break; fi 
    git log --graph --oneline --decorate HEAD master
    printf "\n======================================\n"
    echo "*** Unterschiede zum Vorgänger: ^! ***"
		echo "git diff 24ede28^!"
    echo "*** Unterschiede zwischen Commits ***"
    echo "git diff d25a6fb HEAD"
    echo "*** Commit wechseln ***"
    echo "git checkout d25a6fb"
		echo "gitk"
    printf "======================================\n"

  elif [ $a -eq 6 ]; then
      # Paralelle Entwicklung: Master + zweiten Entwicklungszweig erstellen
      #echo "Directory prüfen"
      if [ ! -d .git ]; then Git-Repository anlegen ; break; fi 
      git log --graph --oneline --decorate HEAD master
      printf "\n======================================\n"
      echo "*** Aktiver Branch ***"
      echo "git branch -a"
      echo "***  Vom aktuellen Commit abzweigen ***"
      echo "git branch Entwicklungszweig"
      echo "***  Auf den neuen Branch wechseln ***"
      echo "git checkout Entwicklungszweig"
			echo "Testversion 001 sichern"
      echo "git checkout master"
			echo "*** Merge = Branches zusammenführen  ***"
			echo "git merge --no-ff Entwicklungszweig"
      echo "*** Branch löschen ***"
      echo "git branch -d Entwicklungszweig"
			echo "gitk"
      printf "======================================\n"

			elif [ $a -eq 7 ]; then
				# Testversion 
				#echo "Directory prüfen"
				if [ ! -d .git ]; then Git-Repository anlegen ; break; fi 
				echo "*** Testversion ***"
				# Dateien oder ganze Verzeichnisse unter Git-Verwaltung stellen
				git add -A
				# Aktuellen Projektstand sichern
				git commit -a -m "Testversion 001"

			elif [ $a -eq 8 ]; then
				# Testversion 
				#echo "Directory prüfen"
				if [ ! -d .git ]; then Git-Repository anlegen ; break; fi 
				echo "*** Testversion ***"
				# Dateien oder ganze Verzeichnisse unter Git-Verwaltung stellen
				git add -A
				# Aktuellen Projektstand sichern
				git commit -a -m "Testversion 002"

			elif [ $a -eq 9 ]; then
      # Zusammenarbeit (2 Entwickler), bare = Repository ohne einen Workspace (zentrales Repository)
      #echo "Directory prüfen"
      if [ ! -d .git ]; then Git-Repository anlegen ; break; fi 
      git log --graph --oneline --decorate HEAD master
      printf "\n======================================\n"
			echo "*** Entwickler A:          ./projekt"
			echo "*** Entwickler B:         ../projekt_clone"
			echo "*** zentrales Repository: ../projekt_server.git"                    
			echo "git clone . ../projekt_clone"
			echo "git clone --bare . ../projekt_server.git"
			echo "*** Entwickler A: Übertragen, wenn file geändert wurde"
			echo "git push ../projekt_server.git master"
			echo "*** Entwickler B: update holen"
			echo "git pull ../projekt_server.git master"
			echo "gitk"
      printf "======================================\n"

	else
		printf "$gruss\n\n"; break
	fi
done

