GPP = g++ -std=c++14 -pedantic-errors -Wall -Wextra -g -I include

thread_pool: test/thread_pool_test.cpp src/thread_pool.cpp include/thread_pool.hpp include/Itask.hpp src/Itask.cpp
	$(GPP) test/$@_test.cpp src/$@.cpp src/Itask.cpp -pthread
	
pnp: test/pnp_test.cpp src/pnp.cpp include/pnp.hpp include/Itask.hpp src/Itask.cpp
	$(GPP) test/$@_test.cpp src/$@.cpp src/Itask.cpp -pthread


%: test/%_test.cpp include/%.hpp
	$(GPP) test/$@_test.cpp 

clean:
	rm -f *.out
	reset

