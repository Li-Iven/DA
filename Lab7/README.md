# Динамическое программирование  

## Вариант 05 - Обход матрицы  

При помощи метода динамического программирования разработать алгоритм решения задачи, определяемой своим вариантом; 
оценить время выполнения алгоритма и объем затрачиваемой оперативной памяти. 
Перед выполнением задания необходимо обосновать применимость метода динамического программирования.

Разработать программу на языке C или C++, реализующую построенный алгоритм. Формат входных и выходных данных описан в варианте задания:  

Задана матрица натуральных чисел A размерности n × m. Из текущей клетки можно перейти в любую из 3-х соседних, стоящих в строке с номером на единицу больше, 
при этом за каждый проход через клетку (i, j) взымается штраф Ai,j. Необходимо пройти из какой-нибудь клетки верхней строки до любой клетки нижней, 
набрав при проходе по клеткам минимальный штраф.

Необходимо вывести в выходной файл на первой строке минимальный штраф, а на второй — последовательность координат из n ячеек, через которые пролегает маршрут с минимальным штрафом.
