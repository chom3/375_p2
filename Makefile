all: submission bruteforce extracredit
submission: submission.cpp
extracredit: extracredit.cpp
bruteforce: bruteforce.cpp

%: %.cpp
	g++ -std=c++11 $< -o $@ -g

%: %.c
	gcc $< -o $@

clean:
	rm -f *.o $(EXECUTABLE)