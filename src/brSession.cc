#include "brSession.hh"
#include "brSessionMessenger.hh"

brSession::brSession():
logOnOff(false){
	mySessionMessenger = new brSessionMessenger(this);
}

brSession::~brSession() {
	delete mySessionMessenger;
	logFile.close();
}

G4int brSession::ReceiveG4cout(G4String coutString) {
	if (logOnOff) {
		logFile << coutString << std::flush;
	}
	std::cout << coutString;
	return 0;
}

G4int brSession::ReceiveG4cerr(G4String cerrString) {
	if (logOnOff) {
		logFile << "Error!: " << cerrString << std::flush;
	}
	std::cerr << cerrString;
	return 0;
}

void brSession::logOn(G4bool myOnOff) {
	logOnOff = myOnOff;
	reinitFile();
}

void brSession::SetLogFileName(G4String filename) {
	logFileName = filename;
	reinitFile();
}

void brSession::reinitFile() {
	if (logOnOff) {
		logFile.close();
		logFile.open(logFileName);
		// 		G4cout << "   Turn Logfile '" << logFileName << "' on." << G4endl;
	} else {
		logFile.close();
		// 		G4cout << "   Turn Logfile '" << logFileName << "' off." << G4endl;
	}
}

