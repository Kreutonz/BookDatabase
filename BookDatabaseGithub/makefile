

# Set the C++ compiler options:
#   -std=c++14 compiles using the C++14 standard (or at least as
#    much as is implemented by the compiler, e.g. for g++ see
#    http://gcc.gnu.org/projects/cxx0x.html)
#   -Wall turns on all warnings
#   -Wextra turns on even more warnings
#   -Werror causes warnings to be errors
#   -Wfatal-errors stops the compiler after the first error
#   -Wno-sign-compare turns off warnings for comparing signed and
#    unsigned numbers
#   -Wnon-virtual-dtor warns about non-virtual destructors
#   -g puts debugging info into the executables (makes them larger)


project: operation.o book.o database.o menu.o
	g++ -o project book.o database.o menu.o operation.o

#only need to link if operation.cpp has changed
operation: operation.cpp
	g++ -c operation.cpp

#only compile if book.h or book.cpp has changed since last compilation
Book: book.h book.cpp
	g++ -c book.cpp

#only compile if database.h or database.cpp has changed since last compilation
database: database.h database.cpp
	g++ -c database.cpp

#only compile if menu.h or menu.cpp has changed since last compilation
menu: menu.h menu.cpp
	g++ -c menu.cpp

clean:
	rm -f project operation.o book.o database.o menu.o

CPPFLAGS = -std=c++14 -Wall -Wextra -Werror -Wfatal-errors -Wno-sign-compare -Wnon-virtual-dtor -g
