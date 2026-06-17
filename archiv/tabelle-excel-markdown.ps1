# PowerShell Script:  ju -- https://bw1.eu -- 26-Dez-18  -- tabelle-excel-markdown.ps1
# Shell: Script ausfuehren
# $ ./tabelle-excel-markdown.ps1

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

<## Git
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
##>

Clear-Host # cls

## Projektverzeichnis anpassen
#$work = "C:/projekte/"
#cd $work
$file     = "bitweisesODER-v02.txt"
$file_md  = "bitweisesODER-v02.md"  # Latex
$file_csv = "bitweisesODER-v02.csv" # Excel/daten/aus Text importieren/    Trennzeichen: ;

$info = "**Powershellscript** erstellt Tabellen in Excel und Markdown.`n"
$info += "`n+++ Hinweis: Tabellenspalte = zwei Leerzeichen +++`n"

## Zeit
#$timestampArchiv = Get-Date -Format 'yyyy-MMM-dd' # 2018-Okt-11
#$timestampArchiv = Get-Date -Format 'yMd'         # 181011
#$timestampFile = Get-Date -Format 'dd-MMM-yyyy'   # 11-Okt-2018
$timestampFile = Get-Date -Format 'd-MMM-y'       # 11-Okt-18

$autor = "ju -- https://bw1.eu -- $timestampFile -- $file`n"
$autor
$info

## suchen und ersetzen
## Excel:    ;
(Get-content $file -Encoding UTF8) -replace '  ',';' | Out-File $file_csv -Encoding UTF8
## Markdown: |
(Get-content $file -Encoding UTF8) -replace '  ','|' | Out-File $file_md -Encoding UTF8


## win-explorer öffnen
#& explorer $save

## PowerShell Fenster offen halten
#Read-Host "`nweiter... [Enter]"
#return 0 #kein Fehler

