//NVDIMM.cpp
//Class file for nonvolatile memory dimm system wrapper

#include "NVDIMM.h"
#include "Init.h"

using namespace NVDSim;
using namespace std;

NVDIMM::NVDIMM(uint id, string deviceFile, string sysFile, string pwd, string trc) :
	dev(deviceFile),
	sys(sysFile),
	cDirectory(pwd)
	{
	uint i, j;
	systemID = id;
	
	 if (cDirectory.length() > 0)
	 {
		 //ignore the pwd argument if the argument is an absolute path
		 if (dev[0] != '/')
		 {
		 dev = pwd + "/" + dev;
		 }
		 
		if (sys[0] != '/')
		 {
		 sys = pwd + "/" + sys;
		 }
	}
	Init::ReadIniFile(dev, false);
	//Init::ReadIniFile(sys, true);

	 if (!Init::CheckIfAllSet())
	 {
		 exit(-1);
	 }
	
	PRINT("\nDevice Information:\n");
	PRINT("Device Type: "<<DEVICE_TYPE);
	PRINT("Size (GB): "<<TOTAL_SIZE/(1024*1024));
	PRINT("Packages/Channels: "<<NUM_PACKAGES);
	PRINT("Page size (KB): "<<FLASH_PAGE_SIZE);
	PRINT("\nTiming Info:\n");
	PRINT("Read time: "<<READ_TIME);
	PRINT("Write Time: "<<WRITE_TIME);
	PRINT("Erase time: "<<ERASE_TIME);
	PRINT("Channel latency for data: "<<DATA_TIME);
	PRINT("Channel latency for a command: "<<COMMAND_TIME);
	PRINT("");

	controller= new Controller(this);
	packages= new vector<Package>();

	if (DIES_PER_PACKAGE > INT_MAX){
		ERROR("Too many dies.");
		exit(1);
	}

	for (i= 0; i < NUM_PACKAGES; i++){
		Package pack = {new Channel(), vector<Die *>()};
		//pack.channel= new Channel();
		pack.channel->attachController(controller);
		for (j= 0; j < DIES_PER_PACKAGE; j++){
			Die *die= new Die(this, j);
			die->attachToChannel(pack.channel);
			pack.channel->attachDie(die);
			pack.dies.push_back(die);
		}
		packages->push_back(pack);
	}
	controller->attachPackages(packages);
	ftl = new Ftl(controller);
	
	ReturnReadData= NULL;
	WriteDataDone= NULL;

	numReads= 0;
	numWrites= 0;
	numErases= 0;
	currentClockCycle= 0;
}

bool NVDIMM::add(FlashTransaction &trans){
	return ftl->addTransaction(trans);
}

bool NVDIMM::addTransaction(bool isWrite, uint64_t addr){
	TransactionType type = isWrite ? DATA_WRITE : DATA_READ;
	FlashTransaction trans = FlashTransaction(type, addr, NULL);
	return controller->addTransaction(trans);
}

string NVDIMM::SetOutputFileName(string tracefilename){
	return "";
}

void NVDIMM::RegisterCallbacks(Callback_t *readCB, Callback_t *writeCB){
	ReturnReadData = readCB;
	WriteDataDone = writeCB;
}

void NVDIMM::printStats(void){
}

void NVDIMM::update(void){
	uint i, j;
	Package package;
	
	for (i= 0; i < packages->size(); i++){
		package= (*packages)[i];
		for (j= 0; j < package.dies.size() ; j++){
			package.dies[j]->update();
			package.dies[j]->step();
		}
	}
		
	ftl->update();
	ftl->step();
	controller->update();
	controller->step();

	step();
}
