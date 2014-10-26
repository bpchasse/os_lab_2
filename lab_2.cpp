//============================================================================
// Name        : lab_2.cpp
// Author      : Brenton Chasse, Alex Nichols
// Version     :
// Copyright   : 2014
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <iostream>
#include <deque>

using namespace std;

class Reducers {
	private:
		pthread_t *reducers;
		deque<string> *buffers;

		static void *consume(void *buffer) {
			//dummy
			return (void *)3;
		}
	public:
		Reducers(int num) {
			reducers = new pthread_t[num];
			buffers = new deque<string>[num];

			for (int i = 0; i < num; i++) {
				pthread_create(&reducers[i], NULL, Reducers::consume, (void *)&buffers[i]);
			}
		};

		~Reducers() {
			delete reducers;
			delete buffers;
		};

		string result() {
			//wait for everything to be done with condition variable
			return "";
		};
};

class Mappers {
	private:
		pthread_t *mappers;
		string *files;
		Reducers *reducers;

		static void* produce(void *file) {

			//dummy
			return (void *)3;
		}
	public:
		Mappers(int num, Reducers *red) {
			files = new string[num];
			mappers = new pthread_t[num];
			reducers = red;

			for (int i = 0; i < num; i++) {
				stringstream os;
				os << "foo" << i << ".txt";
				files[i] = string(os.str().c_str());
			}

			for (int i = 0; i < num; i++) {
				pthread_create(&mappers[i], NULL, Mappers::produce, (void *)&files[i]);
			}
		};

		~Mappers() {
			delete files;
			delete mappers;
		};
};

int main(int argc, char *argv[]) {

	if (argc != 3) {
		cout << "Error - Please enter two arguments: <number of mappers> <number of reducers>" << endl;
		return -1;
	}

	int num_mappers  = strtol(argv[1], NULL, 10);
	int num_reducers = strtol(argv[2], NULL, 10);

	Reducers reducers = Reducers(num_reducers);
	Mappers  mappers  = Mappers(num_mappers, &reducers);

	cout << reducers.result() << endl;

	return 0;
}
