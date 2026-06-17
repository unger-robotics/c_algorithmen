# C Algorithmen

## Hinweis

Projekt getestet unter Win10 

## PowerShell

<https://github.com/PowerShell/PowerShell/releases>

~~~
  Shell öffnen: 
  PS-Version: $PSVersionTable
~~~

## Editor - Visual Studio Code 

<https://code.visualstudio.com/download>

- Shell öffnen: file Auswahl   <Alt+Strg+O>
- mehrfaches Editieren         <Alt+Mausklick>
- Einzug: 2 (Leerzeichen), Codierung: UTF-8, Zeilenende: LF (Linux)

## C/C++ Compiler & Make

Compiler https://mingw-w64.org/doku.php/download>

Make <http://gnuwin32.sourceforge.net/packages/make.htm>

## Makefile

~~~
  # ju -- https://bw1.eu -- 26-Dez-18  -- Makefile
  # Win10
  # gcc -v // Version 7.1.0
  # 26-Dez-18

  TARGETS=\
    halloC-v01.exe \
    halloC-v02.exe \
    halloC++-v01.exe \
    halloC++-v02.exe \
  # 
  CC:=gcc
  CLIBS=-lz meineFkt.c meineFkt.h -lm
  CFLAGS=-Wall -Wextra -std=c11 -lpthread -pthread -O0 -Wno-missing-field-initializers -g
  CXX:=g++
  CXXLIBS=-lz meineFkt.c meineFkt.h -lm
  CXXFLAGS=-Wall -Wextra -std=c++11 -lpthread -pthread -O0 -Wno-missing-field-initializers -g
  CXX14FLAGS=-Wall -Wextra -std=c++1y -lpthread -pthread -O0 -Wno-missing-field-initializers -g
  CXX17FLAGS=-Wall -Wextra -std=c++17 -lpthread -pthread -O0 -Wno-missing-field-initializers -g

  all: $(TARGETS)

  %.exe: %.cpp
    $(CXX) $(CXX17FLAGS) -o $@ $< $(CXXLIBS)

  %.exe: %.c
    $(CC) $(CFLAGS) -o $@ $< $(CLIBS)

  clean:
    #rm -f *.o 
    rm *.exe
~~~

## Programm erstellen

~~~
  make
  make clean
~~~

## Git - Versionieren

<https://git-scm.com/downloads>

Repository auf GitHub erstellen

**c_algorithmen**

<https://github.com/ju-bw/>

~~~
  # repository auf github notwendig!
  git init
  git add .
  git commit -am "Projekt start"
  git remote add origin https://github.com/ju-bw/c_algorithmen.git
  git push -u origin master 
  git status

  git add .
  git commit -a # vim Texteingabe: <i> / beenden mit <ESC : wq>
  #git commit --amend # letzten Commit rueckgaengig machen
  git pull
  git push
  #git log  # less beenden mit <Shift+q>
  # --global: Datei /C/Users/jan/.gitconfig
  git log --graph --decorate --pretty=oneline --abbrev-commit --all
  git log --graph --decorate --pretty=format:"%ad; %h; %s" --no-merges --date=short > log.txt
~~~
