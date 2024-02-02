for %%I in (*.exe) DO (
"C:\Program Files (x86)\IDA Free\idag.exe" -S"N-grammCommandsFunct.idc" %%I
copy e:\temp\commands_from_exe.txt %%I.lst
del *.id0
del *.idb
del *.id1
del *.nam
del *.til
)