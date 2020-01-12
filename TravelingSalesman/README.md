Автор: Клюенков Владимир vaklyuenkov@gmail.com
Дата: 20.12.19

«Приближенное решение метрической неориентированной задачи коммивояжера». Найдите приближенное решение метрической неориентированной задачи коммивояжера в полном графе (на плоскости) с помощью минимального остовного дерева.
Оцените качество приближения на случайном наборе точек, нормально распределенном на плоскости с дисперсией 1. Нормально распределенный набор точек получайте с помощью преобразования Бокса-Мюллера.
При фиксированном N, количестве вершин графа, несколько раз запустите оценку качества приближения. Вычислите среднее значение и среднеквадратичное отклонение качества приближения для данного N.
Запустите данный эксперимент для всех N в некотором диапазоне, например, [2, 10].
Автоматизируйте запуск экспериментов.
В решении требуется разумно разделить код на файлы. Каждому классу - свой заголовочный файл и файл с реализацией.

```
N: 2: average ratio aproximate/accurate decisions: 1 Standart deviation:0
N: 3: average ratio aproximate/accurate decisions: 1 Standart deviation:7.022e-17
N: 4: average ratio aproximate/accurate decisions: 1.031 Standart deviation:0.0406
N: 5: average ratio aproximate/accurate decisions: 1.038 Standart deviation:0.06828
N: 6: average ratio aproximate/accurate decisions: 1.124 Standart deviation:0.05681
N: 7: average ratio aproximate/accurate decisions: 1.108 Standart deviation:0.08859
N: 8: average ratio aproximate/accurate decisions: 1.106 Standart deviation:0.05206
N: 9: average ratio aproximate/accurate decisions: 1.169 Standart deviation:0.09664
N: 10: average ratio aproximate/accurate decisions: 1.159 Standart deviation:0.07855
```