@echo off
cd /d "%~dp0"
git pull
git add .
git commit -m "def"
git push