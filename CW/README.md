# Архиватор

## Вариант - алгоритм LZW

**Задача:** требуется разработать программу, читающую входные данные из стандартного потока ввода и выводящую ответ на стандартный поток вывода.  

Даны входные файлы двух типов.  

**Первый тип:**  
```
compress
<text>
``` 
 
Текст состоит только из малых латинских букв. В ответ на него нужно вывести коды, которыми будет закодирован данный текст.  

**Второй тип:**  
```
decompress
<text>
```   

Даны коды в которые был сжат текст из малых латинских букв, нужно его разжать.  

Начальный словарь состоит выглядит следующим образом:

```
a -> 0
b -> 1
c -> 2
...
x -> 23
y -> 24
z -> 25
EOF -> 26
```
