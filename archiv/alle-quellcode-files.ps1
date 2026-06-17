# PowerShell Script:  ju -- https://bw1.eu -- 17-Dez-18  -- alle-quellcode-files.ps1
# Shell: Script ausfuehren
# $ ./alle-quellcode-files.ps1

<#
  akt. PowerShell: https://github.com/PowerShell/PowerShell/releases
  PS-Version: $PSVersionTable
#>

<#
  Editor - Visual Studio Code 
    - Shell öffnen: file Auswahl   <Alt+Strg+O>
    - mehrfaches Editieren         <Alt+Mausklick>
    - Einzug: 2 (Leerzeichen), Codierung: UTF-8, Zeilenende: LF (Linux)
#>

<### Git
# repository auf github notwendig!
git init
git add .
git commit -am "Projekt start"
git remote add origin https://github.com/ju-bw/$thema.git
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
#>

Clear-Host # cls

### Projektverzeichnis anpassen
#$work = "C:/projekte/"
#cd $work

### Zeit
#$timestampArchiv = Get-Date -Format 'yyyy-MMM-dd' # 2018-Okt-11
#$timestampArchiv = Get-Date -Format 'yMd'         # 181011
#$timestampFile = Get-Date -Format 'dd-MMM-yyyy'   # 11-Okt-2018
$timestampFile = Get-Date -Format 'd-MMM-y'       # 11-Okt-18

## Projekt anpassen
$save = "alle-quellcode-files.txt" 
$file = "ju -- https://bw1.eu -- $timestampFile -- $save`n`n"
$info = "**Powershellscript** speichert alle c & c++ files in $save.`n`n"
$file
$info

$file += "in Makefile speichern:`n"
$file += "======================`n`n"

## c files
$filter = "*.c"
[array]$array = ls ./ $filter 
## array auslesen
for($n=0; $n -lt $array.length; $n++){   # kleiner
  #$name = "$($array[$n])"               # file.tex
  $basename = "$($array.BaseName[$n])"   # file
  #"$n - $name"
  # Schleife überspringen
  if($basename -eq "meineFkt"){# -eq gleich 
    continue # break und continue
  }
  ## schreibe in datei 
  $file += "$basename.exe \`n"
  $file | Out-File "$save" -Encoding UTF8  
} 

## c++ files
$filter = "*.cpp"
[array]$array = ls ./ $filter 
## array auslesen
for($n=0; $n -lt $array.length; $n++){   # kleiner
  #$name = "$($array[$n])"               # file.tex
  $basename = "$($array.BaseName[$n])"   # file
  #"$n - $name"
  # Schleife überspringen
  if($basename -eq "meineFkt"){# -eq gleich 
    continue # break und continue
  }
  ## schreibe in datei 
  $file += "$basename.exe \`n"
  $file | Out-File "$save" -Encoding UTF8  
}

# abschluss
$file += "`n======================`n"
$file | Out-File "$save" -Encoding UTF8  

