cd..
cd..
git clean -dfx
for /r %%I in (*.sln) do (
if not "%%I"=="..\..\Задания с 07.09.2021\ForUniversity.sln" MSBuild "%%I"
)
for /r %%I in (*.exe) do %%I 1