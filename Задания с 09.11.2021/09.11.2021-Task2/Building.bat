@echo off
cd..
cd..
git clean -dfx
for /r %%I in (*.sln) do MSBuild "%%I"
for /r %%I in (*.exe) do "%%I" 1