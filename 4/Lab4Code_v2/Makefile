CC=g++
C_FLAGS=-g -std=c++17 -Wall
APP=poly

custom_tests:
	$(CC) $(C_FLAGS) poly.cpp main.cpp -o $(APP)

valgrind:
	valgrind --leak-check=full ./$(APP) $(TEST)

clean:
	rm -f $(APP)