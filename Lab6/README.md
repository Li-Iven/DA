# Длинная арифметика  

## Вариант 01-Калькулятор  

Необходимо разработать программную библиотеку на языке С или С++, реализующую простейшие арифметические действия и проверку условий над целыми неотрицательными числами. 
На основании этой библиотеки нужно составить программу, выполняющую вычисления над парами десятичных чисел и выводящую результат на стандартный файл вывода.  

Список арифметических операций:  

Сложение (+).  
Вычитание (-).  
Умножение (*).  
Возведение в степень (^).  
Деление (/).  

В случае возникновения переполнения в результате вычислений, попытки вычесть из меньшего числа большее, деления на ноль или возведении нуля в нулевую степень, 
программа должна вывести на экран строку Error.  

Список условий:  

Больше (>).  
Меньше (<).  
Равно (=).  

В случае выполнения условия программа должна вывести на экран строку true, в противном случае — false.  

### Формат входных данных
Входной файл состоит из последовательности заданий, каждое задание состоит из трех строк:  

Первый операнд операции.  
Второй операнд операции.  
Символ арифметической операции или проверки условия (+, -, *, ^, /, >, <, =).  

Числа, поступающие на вход программе, могут иметь «ведущие» нули.  

### Формат результата  

Для каждого задания из выходного файла нужно распечатать результат на отдельной строке в выходном файле:  

Числовой результат для арифметических операций.  
Строку Error в случае возникновения ошибки при выполнении арифметической операции.  
Строку true или false при выполнении проверки условия.  

В выходных данных вывод чисел должен быть нормализован, то есть не содержать в себе «ведущих» нулей.  