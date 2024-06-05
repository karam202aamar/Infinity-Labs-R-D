CC:=gcc
CFLAGS:=-ansi -pedantic-errors -Wall -Wextra -g -c -fPIC

DS1=Stack
DS2=bit_array
DS3=dynamic_vector
DS4=linked_list
DS5=linked_list_exercises
DS6=queue
DS7=cbuf
DS8=dlist
DS9=sorted_list
DS10=uid
DS11=p_queue
DS12=task
DS13=scheduler
DS14=fsa
DS15=vsa
DS16=sorts
DS17=bst
DS18=calculator
DS19=recursion
DS20=avl
DS21=hash_table
DS22=heap
DS23=pqueue_heap
DS24=bin_trie
DS25=dhcp
DS26=knight_tour

DS=dlist
SHARED := gcc -shared -o
SHARED_OUT := gcc -L/home/karam/Desktop/infintylab/git/ds -Wl,-rpath=/home/karam/Desktop/infintylab/git/ds -I ./include -o
#******************************Stack*******************************************#
$(DS1): $(DS1).o $(DS1)_test.o 
	$(CC) $(DS1).o $(DS1)_test.o -o $(DS1).out
	
$(DS1)_test.o: test/$(DS1)_test.c
	$(CC) $(CFLAGS) test/$(DS1)_test.c -I ./include
	
$(DS1).o: src/$(DS1).c 
	$(CC) $(CFLAGS) src/$(DS1).c -I ./include
	
lib_$(DS1).ar: $(DS1).o $(DS1)_test.o
	ar -rc lib$(DS1).ar $(DS1).o $(DS1)_test.o
	

#******************************BitArray****************************************#
$(DS2): $(DS2).o $(DS2)_test.o 
	$(CC) $(DS2).o $(DS2)_test.o -o $(DS2).out
	
$(DS2)_test.o: test/$(DS2)_test.c
	$(CC) $(CFLAGS) test/$(DS2)_test.c -I ./include
	
$(DS2).o: src/$(DS2).c 
	$(CC) $(CFLAGS) src/$(DS2).c -I ./include
lib_$(DS2).ar: $(DS2).o $(DS2)_test.o
	ar -rc lib$(DS2).ar $(DS2).o $(DS2)_test.o
#******************************Vector******************************************#
$(DS3): $(DS3).o $(DS3)_test.o 
	$(CC) $(DS3).o $(DS3)_test.o -o $(DS3).out
	
$(DS3)_test.o: test/$(DS3)_test.c
	$(CC) $(CFLAGS) test/$(DS3)_test.c -I ./include
	
$(DS3).o: src/$(DS3).c 
	$(CC) $(CFLAGS) src/$(DS3).c -I ./include
lib_$(DS3).ar: $(DS3).o $(DS3)_test.o
	ar -rc lib$(DS3).ar $(DS3).o $(DS3)_test.o
#********************************Linked List***********************************#
$(DS4): $(DS4).o $(DS4)_test.o 
	$(CC) $(DS4).o $(DS4)_test.o -o $(DS4).out
	
$(DS4)_test.o: test/$(DS4)_test.c
	$(CC) $(CFLAGS) test/$(DS4)_test.c -I ./include
	
$(DS4).o: src/$(DS4).c 
	$(CC) $(CFLAGS) src/$(DS4).c -I ./include
lib_$(DS4).ar: $(DS4).o $(DS4)_test.o
	ar -rc lib$(DS4).ar $(DS4).o $(DS4)_test.o
#*****************************LInked LIst exersices****************************#
$(DS5): $(DS5).o 
	$(CC) $(DS5).o  -o $(DS5).out
	
$(DS5).o: src/$(DS5).c 
	$(CC) $(CFLAGS) src/$(DS5).c -I ./include
	
lib_$(DS5).ar: $(DS5).o $(DS5)_test.o
	ar -rc lib$(DS5).ar $(DS5).o $(DS5)_test.o
#***********************************Queue**************************************#
$(DS6): $(DS6).o $(DS4).o $(DS6)_test.o 
	$(CC) $(DS6).o $(DS4).o $(DS6)_test.o -o $(DS6).out
	
$(DS6)_test.o: test/$(DS6)_test.c 
	$(CC) $(CFLAGS) test/$(DS6)_test.c -I ./include
	
$(DS6).o: src/$(DS6).c src/$(DS4).c
	$(CC) $(CFLAGS) src/$(DS6).c src/$(DS4).c -I ./include
lib_$(DS6).ar: $(DS6).o $(DS6)_test.o
	ar -rc lib$(DS6).ar $(DS6).o $(DS4) $(DS6)_test.o
#*******************************circular buffer********************************#
$(DS7): $(DS7).o $(DS7)_test.o 
	$(CC) $(DS7).o $(DS7)_test.o -o $(DS7).out
	
$(DS7)_test.o: test/$(DS7)_test.c
	$(CC) $(CFLAGS) test/$(DS7)_test.c -I ./include
	
$(DS7).o: src/$(DS7).c 
	$(CC) $(CFLAGS) src/$(DS7).c -I ./include
lib_$(DS7).ar: $(DS7).o $(DS7)_test.o
	ar -rc lib$(DS7).ar $(DS7).o $(DS7)_test.o
#****************************doubly linked list********************************#
$(DS8): $(DS8).o $(DS8)_test.o 
	$(CC) $(DS8).o $(DS8)_test.o -o $(DS8).out
	
$(DS8)_test.o: test/$(DS8)_test.c
	$(CC) $(CFLAGS) test/$(DS8)_test.c -I ./include
	
$(DS8).o: src/$(DS8).c 
	$(CC) $(CFLAGS) src/$(DS8).c -I ./include
lib_$(DS8).ar: $(DS8).o $(DS8)_test.o
	ar -rc lib$(DS8).ar $(DS8).o $(DS8)_test.o
#****************************sorted linked list********************************#
$(DS9): $(DS9).o $(DS8).o $(DS9)_test.o 
	$(CC) $(DS9).o $(DS8).o $(DS9)_test.o -o $(DS9).out
	
$(DS9)_test.o: test/$(DS9)_test.c
	$(CC) $(CFLAGS) test/$(DS9)_test.c -I ./include
	
$(DS9).o: src/$(DS9).c src/$(DS8).c
	$(CC) $(CFLAGS) src/$(DS9).c src/$(DS8).c -I ./include
lib_$(DS9).ar: $(DS9).o $(DS9)_test.o
	ar -rc lib$(DS9).ar $(DS9).o $(DS9)_test.o
#*************************************UID**************************************#
$(DS10): $(DS10).o $(DS10)_test.o 
	$(CC) $(DS10).o $(DS10)_test.o -o $(DS10).out
	
$(DS10)_test.o: test/$(DS10)_test.c
	$(CC) $(CFLAGS) test/$(DS10)_test.c -I ./include
	
$(DS10).o: src/$(DS10).c 
	$(CC) $(CFLAGS) src/$(DS10).c -I ./include
lib_$(DS10).ar: $(DS10).o $(DS10)_test.o
	ar -rc lib$(DS10).ar $(DS10).o $(DS10)_test.o	

#********************************priority queue********************************#
$(DS11): $(DS11).o $(DS9).o $(DS11)_test.o $(DS8).o
	$(CC) $(DS11).o $(DS9).o $(DS11)_test.o $(DS8).o -o $(DS11).out
	
$(DS11)_test.o: test/$(DS11)_test.c 
	$(CC) $(CFLAGS) test/$(DS11)_test.c -I ./include
	
$(DS11).o: src/$(DS11).c 
	$(CC) $(CFLAGS) src/$(DS11).c -I ./include
lib_$(DS11).ar: $(DS11).o $(DS19).o $(DS11)_test.o 
	ar -rc lib$(DS11).ar $(DS11).o $(DS9).o $(DS11)_test.o
#*************************************task*************************************#
$(DS12): $(DS12).o $(DS10).o $(DS12)_test.o 
	$(CC) $(DS12).o $(DS10).o $(DS12)_test.o -o $(DS12).out
	
$(DS12)_test.o: test/$(DS12)_test.c
	$(CC) $(CFLAGS) test/$(DS12)_test.c -I ./include
	
$(DS12).o: src/$(DS12).c 
	$(CC) $(CFLAGS) src/$(DS12).c -I ./include
lib_$(DS12).ar: $(DS12).o $(DS12)_test.o
	ar -rc lib$(DS12).ar $(DS12).o $(DS12)_test.o
#***********************************scheduler**********************************#
$(DS13): $(DS13).o $(DS13)_test.o $(DS12).o $(DS11).o $(DS10).o $(DS9).o $(DS8).o
	$(CC)  $(DS13).o $(DS13)_test.o $(DS12).o $(DS11).o $(DS10).o $(DS9).o $(DS8).o -o $(DS13).out
	
$(DS13)_test.o: test/$(DS13)_test.c 
	$(CC) $(CFLAGS) test/$(DS13)_test.c -I ./include
	
$(DS13).o: src/$(DS13).c 
	$(CC) $(CFLAGS) src/$(DS13).c -I ./include	
	
$(DS13).so.out: lib$(DS13).so test/$(DS13)_test.c
	$(SHARED_OUT) $(DS13).so.out test/$(DS13)_test.c -l$(DS13)
lib$(DS13).so: $(DS13).o $(DS12).o $(DS11).o $(DS10).o $(DS9).o $(DS8).o
	$(SHARED) lib$(DS13).so $(DS13).o $(DS12).o $(DS11).o $(DS10).o $(DS9).o $(DS8).o
	rm  $(DS13).o $(DS12).o $(DS11).o $(DS10).o $(DS9).o $(DS8).o

#************************************* fsa ************************************#
$(DS14): $(DS14).o $(DS14)_test.o 
	$(CC) $(DS14).o $(DS14)_test.o -o $(DS14).out
	
$(DS14)_test.o: test/$(DS14)_test.c
	$(CC) $(CFLAGS) test/$(DS14)_test.c -I ./include
	
$(DS14).o: src/$(DS14).c 
	$(CC) $(CFLAGS) src/$(DS14).c -I ./include
lib_$(DS14).ar: $(DS14).o $(DS14)_test.o
	ar -rc lib$(DS14).ar $(DS14).o $(DS14)_test.o
#************************************* vsa ************************************#
$(DS15): $(DS15).o $(DS15)_test.o 
	$(CC) $(DS15).o $(DS15)_test.o -o $(DS15).out
	
$(DS15)_test.o: test/$(DS15)_test.c
	$(CC) $(CFLAGS) test/$(DS15)_test.c -I ./include
	
$(DS15).o: src/$(DS15).c 
	$(CC) $(CFLAGS) src/$(DS15).c -I ./include
lib_$(DS15).ar: $(DS15).o $(DS15)_test.o
	ar -rc lib$(DS15).ar $(DS15).o $(DS15)_test.o
#********************************comparsion sort*******************************#	
$(DS16): $(DS16).o $(DS16)_test.o 
	$(CC) $(DS16).o $(DS16)_test.o -o $(DS16).out
	
$(DS16)_test.o: test/$(DS16)_test.c
	$(CC) $(CFLAGS) test/$(DS16)_test.c -I ./include
	
$(DS16).o: src/$(DS16).c 
	$(CC) $(CFLAGS) src/$(DS16).c -I ./include
lib_$(DS16).ar: $(DS16).o $(DS16)_test.o
	ar -rc lib$(DS16).ar $(DS16).o $(DS16)_test.o
#****************************binary search tree********************************#	
$(DS17): $(DS17).o $(DS17)_test.o 
	$(CC) $(DS17).o $(DS17)_test.o -o $(DS17).out
	
$(DS17)_test.o: test/$(DS17)_test.c
	$(CC) $(CFLAGS) test/$(DS17)_test.c -I ./include
	
$(DS17).o: src/$(DS17).c 
	$(CC) $(CFLAGS) src/$(DS17).c -I ./include
lib_$(DS17).ar: $(DS17).o $(DS17)_test.o
	ar -rc lib$(DS17).ar $(DS17).o $(DS17)_test.o
#**********************************calcultor***********************************#
$(DS18): $(DS18).o $(DS1).o $(DS18)_test.o 
	$(CC) $(DS18).o $(DS1).o $(DS18)_test.o -o $(DS18).out
	
$(DS18)_test.o: test/$(DS18)_test.c
	$(CC) $(CFLAGS) test/$(DS18)_test.c -I ./include
	
$(DS18).o: src/$(DS18).c 
	$(CC) $(CFLAGS) src/$(DS18).c -I ./include
lib_$(DS18).ar: $(DS18).o $(DS18)_test.o
	ar -rc lib$(DS18).ar $(DS18).o $(DS18)_test.o
#**********************************recursion***********************************#
$(DS19): $(DS19).o $(DS1).o $(DS19)_test.o 
	$(CC) $(DS19).o $(DS1).o $(DS19)_test.o -o $(DS19).out
	
$(DS19)_test.o: test/$(DS19)_test.c
	$(CC) $(CFLAGS) test/$(DS19)_test.c -I ./include
	
$(DS19).o: src/$(DS19).c 
	$(CC) $(CFLAGS) src/$(DS19).c -I ./include
lib_$(DS19).ar: $(DS19).o $(DS19)_test.o
	ar -rc lib$(DS19).ar $(DS19).o $(DS19)_test.o
#************************************avl***************************************#	
$(DS20): $(DS20).o $(DS20)_test.o 
	$(CC) $(DS20).o $(DS20)_test.o -o $(DS20).out
	
$(DS20)_test.o: test/$(DS20)_test.c
	$(CC) $(CFLAGS) test/$(DS20)_test.c -I ./include
	
$(DS20).o: src/$(DS20).c 
	$(CC) $(CFLAGS) src/$(DS20).c -I ./include
lib_$(DS20).ar: $(DS20).o $(DS20)_test.o
	ar -rc lib$(DS20).ar $(DS20).o $(DS20)_test.o
#***********************************hash table*********************************#	
$(DS21): $(DS21).o $(DS8).o  $(DS21)_test.o 
	$(CC) $(DS21).o $(DS8).o $(DS21)_test.o -o $(DS21).out
	
$(DS21)_test.o: test/$(DS21)_test.c
	$(CC) $(CFLAGS) test/$(DS21)_test.c -I ./include
	
$(DS21).o: src/$(DS21).c 
	$(CC) $(CFLAGS) src/$(DS21).c -I ./include
lib_$(DS21).ar: $(DS21).o $(DS21)_test.o
	ar -rc lib$(DS21).ar $(DS21).o $(DS21)_test.o
#*************************************heap*************************************#	
$(DS22): $(DS22).o $(DS3).o  $(DS22)_test.o 
	$(CC) $(DS22).o $(DS3).o $(DS22)_test.o -o $(DS22).out
	
$(DS22)_test.o: test/$(DS22)_test.c
	$(CC) $(CFLAGS) test/$(DS22)_test.c -I ./include
	
$(DS22).o: src/$(DS22).c 
	$(CC) $(CFLAGS) src/$(DS22).c -I ./include
lib_$(DS22).ar: $(DS22).o $(DS22)_test.o
	ar -rc lib$(DS22).ar $(DS22).o $(DS22)_test.o
#********************************pqueue heap***********************************#	
$(DS23): $(DS23).o $(DS22).o $(DS3).o $(DS23)_test.o 
	$(CC) $(DS23).o $(DS22).o $(DS3).o $(DS23)_test.o -o $(DS23).out
	
$(DS23)_test.o: test/$(DS23)_test.c
	$(CC) $(CFLAGS) test/$(DS23)_test.c -I ./include
	
$(DS23).o: src/$(DS23).c 
	$(CC) $(CFLAGS) src/$(DS23).c -I ./include
lib_$(DS23).ar: $(DS23).o $(DS23)_test.o
	ar -rc lib$(DS23).ar $(DS23).o $(DS23)_test.o
#**********************************bin trie************************************#	
$(DS24): $(DS24).o $(DS24)_test.o 
	$(CC) $(DS24).o $(DS24)_test.o -o $(DS24).out
	
$(DS24)_test.o: test/$(DS24)_test.c
	$(CC) $(CFLAGS) test/$(DS24)_test.c -I ./include
	
$(DS24).o: src/$(DS24).c 
	$(CC) $(CFLAGS) src/$(DS24).c -I ./include
lib_$(DS24).ar: $(DS24).o $(DS24)_test.o
	ar -rc lib$(DS24).ar $(DS24).o $(DS24)_test.o
#************************************dhcp**************************************#	knight_tour
$(DS25): $(DS25).o $(DS24).o $(DS25)_test.o 
	$(CC) $(DS25).o $(DS24).o $(DS25)_test.o -o $(DS25).out
	
$(DS25)_test.o: test/$(DS25)_test.c
	$(CC) $(CFLAGS) test/$(DS25)_test.c -I ./include
	
$(DS25).o: src/$(DS25).c 
	$(CC) $(CFLAGS) src/$(DS25).c -I ./include
lib_$(DS25).ar: $(DS25).o $(DS25)_test.o
	ar -rc lib$(DS25).ar $(DS25).o $(DS25)_test.o
#*********************************knight_tour**********************************#	
$(DS26): $(DS26).o $(DS2).o $(DS26)_test.o 
	$(CC) $(DS26).o $(DS2).o $(DS26)_test.o -o $(DS26).out
	
$(DS26)_test.o: test/$(DS26)_test.c
	$(CC) $(CFLAGS) test/$(DS26)_test.c -I ./include
	
$(DS26).o: src/$(DS26).c 
	$(CC) $(CFLAGS) src/$(DS26).c -I ./include
lib_$(DS26).ar: $(DS26).o $(DS26)_test.o
	ar -rc lib$(DS26).ar $(DS26).o $(DS26)_test.o
#******************************************************************************#	
.PHONY: clean
clean:
	rm *.o *.out
#********************************makefile SO dlist*****************************#
$(DS)_exe: test/$(DS)_test.c lib$(DS).so
	$(CC) $(CFLAGS) -o $@ $< -I ./include -Wl,-rpath=. -L. -l $(DS) 

lib$(DS).so: src/$(DS).c
	$(CC) $(CFLAGS) -shared $< -I ./include -o $@

#******************************makefile SO scheduler***************************#


