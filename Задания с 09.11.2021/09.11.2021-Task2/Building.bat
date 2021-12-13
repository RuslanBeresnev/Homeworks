@echo off

git clean -dfx
for "..\..\..\Homeworks" %%I in (*.sln) do (
if not %%I=="C:\\Users\User\source\repos\Homeworks\Задания с 07.09.2021\ForUniversity.sln" MSBuild
)
for "..\..\..\Homeworks" %%I in (*.exe) do %%I 1

@pause