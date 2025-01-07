FILES = ./src/admingui.c ./src/boxes.c ./src/file.c ./src/header.c ./src/menu.c ./src/money.c ./src/text.c ./src/usergui.c main.c

build-all:
	gcc -o programma.exe -I./include $(FILES)
	./programma.exe