CROSS_COMPILE = arm-linux-gnueabihf
CC = $(CROSS_COMPILE)-gcc -static

app: tictactoe_app.c
	$(CC) -o tictactoe_app tictactoe_app.c
clean:
	rm -rf tictactoe_app
