static-lib=libmymath.a

$(static-lib):Add.o Div.o Mul.o Sub.o
	ar -rc $@ $^
%.o:%.c
	gcc -c $<

#Test:Add.o Div.o Mul.o Sub.o TestMain.o
#	gcc -o $@ $^

.PHONY:output
output:
	mkdir -p mymath_lib/include
	mkdir -p mymath_lib/lib 
	cp -f *.h mymath_lib/include
	cp -f *.a mymath_lib/lib

.PHONY:clean
clean:
	rm -f *.o *.a mymath_lib
