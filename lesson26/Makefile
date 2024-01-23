Test:Add.o Div.o Mul.o Sub.o TestMain.o
	gcc -o $@ $^

%.o:%.c
	gcc -c $<

.PHONY:clean
clean:
	rm -f *.o Test
