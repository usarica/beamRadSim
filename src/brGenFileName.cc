#include "brGenFileName.hh"
#include <ctime>

char brGenFileName::prefix[24] = "";

brGenFileName::brGenFileName() {
	time_t myTime; //retrieves date and time
	myTime = time(NULL);
	struct tm* myBrokenTime; //Broken-down Time
	myBrokenTime = localtime(&myTime);
	strftime(prefix, 24, "%Y-%m-%d--%H-%M-%S", myBrokenTime);
}

brGenFileName::~brGenFileName() {

}

G4String brGenFileName::genFileName(char postfix[6]) {
	char final[24] = "";
	strcat(final, prefix);
	strcat(final, postfix);
	G4String tmp = final;
	return tmp;
}
