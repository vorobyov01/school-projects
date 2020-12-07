# import modules
import pygame
import sys
import serial
import sqlite3
from pygame.locals import *

# Serial port settings
serial = serial.Serial("/dev/ttyACM0")
serial.baudrate = 9600
#инициальзация модуля
pygame.init()
#Настройки окна
screen = pygame.display.set_mode((400, 400), 0, 32)
pygame.display.set_caption("LineTimer")
(x, y, fontSize) = (10, 40, 100)
myFont = pygame.font.SysFont("None", fontSize)
secondFont = pygame.font.SysFont("None", 40)
fontColor = (255, 0, 0)
bgColor = (255, 255, 255)


line = "foo"
#Чтение базы
conn = sqlite3.connect('db.sqlite3')
cursor = conn.cursor()
cursor.execute("SELECT * FROM comp")
result = cursor.fetchall()
conn.close()
#Счетчик списка команд
i = len(result)
#Я не знаю зачем этот костыль
textinput = "null"

while True:
    #БезЭтогоНеРаботает
    if textinput == "null":
        textinput = input()
    #Проверяет выход из окна
    for event in pygame.event.get():
        if event.type == QUIT:
            pygame.quit()
            sys.exit()
    #И без этого нормально не работает
    last_line = line
    line = serial.readline()
    try:
        screen.fill(bgColor)
        fontImage = myFont.render(str(float(line)), 0, (fontColor))
        #КостыльАЗвхзпах
        if str(float(line)) == "-1.0":
            conn = sqlite3.connect('db.sqlite3')
            cursor = conn.cursor()
            ###ЗАПИСЬ
            ###В БД

            i += 1
            cur = "INSERT INTO comp VALUES (" + str(i) + ", '" + textinput + "'," + str(float(last_line)) + ")"
            text_input = "null"
            print(cur)
            cursor.execute(cur)
            #Сохранение изменений
            conn.commit()

            conn.close()
            print(str(float(last_line)))
    except ValueError:
        print(str(line) + " - this is error!!!")

    ###Очередное чтение

    conn = sqlite3.connect('db.sqlite3')
    cursor = conn.cursor()

    cursor.execute("SELECT * FROM comp")

    result = cursor.fetchall()
    #Вывод всего, что было в базе
    for q in range(len(result)):
        stringR = str(result[q][0]) + " " + str(result[q][1]) + "  -  " + str(result[q][2])
        secondFontR = secondFont.render(stringR, 0, (0, 0, 0))
        screen.blit(secondFontR, (x, y+q*25+70))
        pygame.display.update()

    conn.close()

    ###
    #Досвидули
    screen.blit(fontImage, (x, y))
    pygame.display.update()
pygame.quit()