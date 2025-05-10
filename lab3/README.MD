## ПРАКТИЧНА 3


## Завдання 1

Запустіть Docker-контейнер і поекспериментуйте з максимальним лімітом ресурсів відкритих файлів. Для цього виконайте команди у вказаному порядку:
$ ulimit -n
$ ulimit -aS | grep "open files"
$ ulimit -aH | grep "open files"
$ ulimit -n 3000
$ ulimit -aS | grep "open files"
$ ulimit -aH | grep "open files"
$ ulimit -n 3001
$ ulimit -n 2000
$ ulimit -n
$ ulimit -aS | grep "open files"
$ ulimit -aH | grep "open files"
$ ulimit -n 3000

Як наступне вправу, повторіть перераховані команди з root-правами.

## Результат 
![lab3](lab3_1/3.png)
## Результат з root правами
![lab3](lab3_1/l3.png)


## Опис
Ulimit дозволяє керувати обмеженнями системних ресурсів ,soft limit  можна змінювати в межах hard limit.
Навіть root-користувач у контейнері не може підняти hard limit, якщо його не вказано при запуску.


## Завдання 2 


