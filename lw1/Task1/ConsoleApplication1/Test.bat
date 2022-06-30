@echo off

REM ���� � ����������� ��������� ��������� ����� 1-�� �������� ��������� ������
SET MyProgram="%~1"

REM ������ �� ������� ��� ���������, ��������� ���� � ���������
if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)


REM Files given, searching and replaceing string not specifed. Must fail
%MyProgram% empty.txt "%TEMP%\output.txt" && goto err
echo Test 1 passed

REM Files are correct, searching string set, replacing string not specifed. Must fail
%MyProgram% NotEmpty.txt "%TEMP%\output.txt" param && goto err
echo Test 2 passed

REM Replace 1 string in file that consists only of this string.
%MyProgram% Missing.txt "%TEMP%\output.txt" abc x > nul && goto err
echo Test 3 passed

REM Replace 1 string in file that consists not only of this string
%MyProgram% Missing.txt "%TEMP%\output.txt" abc x && goto err
echo Test 4 passed

REM Replace 2 strings
%MyProgram% Missing.txt "%TEMP%\output.txt" ���� ���� && goto err
echo Test 5 passed

REM searching string is empty
%MyProgram% Missing.txt "%TEMP%\output.txt" "" searching && goto err

REM replacing string is empty
%MyProgram% Missing.txt "%TEMP%\output.txt" finding "" && goto err



REM If input and ouput file not specifed, program must fail
%MyProgram% Missing.txt > nul && goto err
echo Test 5 passed

REM If input and ouput file not specifed, program must fail
%MyProgram% > nul && goto err
echo Test 6 passed 


REM ����� ������ �������
echo All test passed succesfully
exit /B 0

REM ���� ����� �������� � ������ ������
:err
echo Test faield
exit /B 1	