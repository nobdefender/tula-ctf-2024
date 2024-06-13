# Сапёр 2

## Условие

Мне друг сказал, что вышел Сапёр 2 и скинул его. Правда у меня только чёрное окно. Поможешь?

Формат флага: ```TulaCTF{flag}```

> Ссылка на задание: https://disk.yandex.ru/d/ku4Y0TaIW2dsFg

> Пароль: `TulaCTF2024`

Рекомендуемое ПО: volatility3

## Флаг

```TulaCTF{1_sEe_yU0_BuT_Yu0_d0nT}```

## Решение

Среди запущенных процессов есть нечто ссылающееся на папку с играми. Выгружаем файл `LookAtMe.bat`.

```batch
set /p "flag=KR2WYYKDKRDHWMK7ONCWKX3ZKUYF6QTVKRPVS5JQL5SDA3SUPU======"
pause >nul
```

Строка `KR2WYYKDKRDHWMK7ONCWKX3ZKUYF6QTVKRPVS5JQL5SDA3SUPU======` является закодированным флагом с помощью Base32
