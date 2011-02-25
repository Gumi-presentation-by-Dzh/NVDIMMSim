#ifndef PCMGCFTL_H
#define PCMGCFTL_H
//PCMFtl.h
//header file for the ftl with PCM power stuff

#include <iostream>
#include <fstream>
#include "SimObj.h"
#include "FlashConfiguration.h"
#include "ChannelPacket.h"
#include "FlashTransaction.h"
#include "Controller.h"
#include "GCFtl.h"

namespace NVDSim{
	class PCMGCFtl : public GCFtl{
		public:
			PCMGCFtl(Controller *c);
			void update(void);

			void saveStats(uint64_t cycle, uint64_t reads, uint64_t writes, uint64_t erases);
			void printStats(uint64_t cycle, uint64_t reads, uint64_t writes, uint64_t erases);
			void powerCallback(void);

			//Accessors for power data
			//Writing correct object oriented code up in this piece, what now?
			vector<double> getVppIdleEnergy(void);
			vector<double> getVppAccessEnergy(void);
			vector<double> getVppEraseEnergy(void);

                protected:
			// Power Stuff
			// This is computed per package
			std::vector<double> vpp_idle_energy;
			std::vector<double> vpp_access_energy;
			std::vector<double> vpp_erase_energy;
	};
}
#endif