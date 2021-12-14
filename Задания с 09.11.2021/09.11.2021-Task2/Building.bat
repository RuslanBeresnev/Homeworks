cd..
cd..
git clean -dfx
for /r . %%I in (*.sln) do (
if not %%I=="C:\\Users\User\source\repos\Homeworks\Задания с 07.09.2021\ForUniversity.sln" MSBuild "%%I"
)
for /r "Homeworks" %%I in (*.exe) do %%I 1