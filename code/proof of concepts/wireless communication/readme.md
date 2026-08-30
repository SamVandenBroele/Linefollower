# Draadloze communicatie proof of concept

Voor dit project was een proof of concept voor draadloze communicatie voorzien met behulp van een HM-10 Bluetoothmodule.

De HM-10 Bluetoothmodule is fysiek voorzien in het elektronische ontwerp en aangesloten op de STM32 via USART2:

- STM32 PA2 (USART2_TX) → HM-10 RX
- STM32 PA3 (USART2_RX) ← HM-10 TX

Een werkende proof of concept voor draadloze communicatie werd niet gerealiseerd voor het uiteindelijke Plan-B-prototype.

Draadloze communicatie wordt daarom niet gebruikt door de huidige finale lijnvolgsoftware.
