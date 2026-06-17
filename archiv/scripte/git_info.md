# Git - Info

## Begriffe

* Workspace  = Projektverzeichnis mit einem Repository
* Repository = Historie des Projekts in Form von Commits
* Stage-Bereich = Index von Dateiinhalten
* Branch     = Entwicklungszweig
* Merge      = Branches zusammenführen 
* add        =  geänderten Dateien im Stage-Bereich anmelden.
* commit     = Projektversion
* status     =  zeigt welche Dateien lokal verändert wurden.
* log        = zeigt die Historie der Commits
* diff       = zeigt Änderungen
* clone      = erstellt eine Kopie eines Repositorys
* pull       = Commits von einem anderen Repository holen
* push       = Commits in ein anderes Repository übertragen
* Bare-Repository = Repository ohne einen Workspace (zentrales Repository)
* Checkout   = Wiederherstellen einer Version
* .gitignore = Dateien und Verzeichnisse nicht von Git verwalten lassen
* .git       = Repository
* Tags       = sprechende Namen für Commits
* Commit-Hash = 40 Zeichen langen Code, identifizieren Commits u. dienen als Prüfsumme
* reset      = Stage-Bereich zurücksetzen
* stash      = die aktuellen Änderungen in Workspace und Stage-Bereich zwischenspeichern.
* checkout   = aktiven Branch wechseln.

## install

~~~
	sudo apt -y install git gitk git-gui gitg git-core
	sudo apt -y install tig
	sudo apt -y install meld
	sudo apt -y install kdiff3
~~~

## git konfig

~~~
	git config --global user.name "Jan Unger"
	git config --global user.email "info@bw1.eu"
	git config --global core.editor "vim"
	git config --global color.ui true
	git config diff.renames true
	git config merge.conflictstyle diff3
	git config merge.tool kdiff3
~~~

## vi .gitignore

~~~
	# ordner/
	# !file.md = Ausnahme, wird versioniert
	.gitignore
	*.exe
	*.x
	*.pdf
	*.jpg
~~~

## Befehle

~~~
	git init
	git add -A
	git commit -a -m 'erste Version'
	git status
	git log
	git log --graph --oneline --decorate HEAD master
~~~

<https://github.com/ju-bw>

user: ju-bw
key:

~~~
  Create a new repository
  Repository name
  Createrepository
  Upload files (projekt)
~~~

~~~
	# Klonen
	cd ~/c/c_algorithmen
  git clone https://github.com/ju-bw/c_algorithmen.git github_projekt_clone
  cd github_projekt_clone
  git status
  git add .
  git commit -a -m "Initialisierung"

	git remote add origin https://github.com/ju-bw/c_algorithmen.git
	#git remote add origin git@github.com:ju-bw/c_algorithmen.git
	git push -u origin master
  git log --graph --oneline --decorate HEAD master
	git pull
  git push
~~~

~~~
#or create a new repository on the command line

echo "# c_algorithmen" > README.md
git init
git add README.md
git commit -m "first commit"
git remote add origin git@github.com:ju-bw/c_algorithmen.git
git push -u origin master

#or push an existing repository from the command line

git remote add origin git@github.com:ju-bw/c_algorithmen.git
git push -u origin master

~~~