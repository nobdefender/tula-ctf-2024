# Мой первый пряник

Не так давно, на дне города, я увидел мастер-класс по созданию тульских пряников. 
Естественно, я захотел сделать его своими руками. Мой любимый тульский пряник, сам!

Фотографию прилагаю, вот такой он получился. Правда есть сразу не стал, хотел показать друзьям.
Но вот незадача, я забыл, что положил в качестве начинки. Можете помочь узнать, что у него внутри?

Формат флага: ```TulaCTF{flag}```

## Подсказка 1

А вы точно всё **посмотрели**?

## Подсказка 2

Мой любимый цвет - **синий**!


# Решение

Смотрим программой stegsolve. Можно и zsteg и т.п., но явного там ничего не получится увидеть.

Листая разные биты цветов, можно заметить интересную картину на Blue 0. Посреди картинки стоят точки и тире.
Логично предположить, что это код Морзе. Дешифруем любым удобным способом, хоть ручным.

В репозитории приведены программы на python для создания этого таска и для его решения. (hide_text.py и show_lsb.py соответственно)
Так же вторая программа покажет, как выглядят младшие биты синего цвета.

## flag

```TulaCTF{PRYANIK_HAS_UNTRULY_FILLING}```

