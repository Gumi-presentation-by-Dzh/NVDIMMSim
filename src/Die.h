#ifndef DIE_H
#define DIE_H
//Die.h
//header file for the Die class

#include "SimObj.h"
#include "FlashConfiguration.h"
#include "ChannelPacket.h"
#include "Plane.h"

namespace NVDSim{

	class Channel;
	class Controller;
	class FlashDIMM;
	class Die : public SimObj{
		public:
			Die(FlashDIMM *parent, uint id);
			void attachToChannel(Channel *chan);
			void receiveFromChannel(ChannelPacket *busPacket);
			int isDieBusy(void);
			void update(void);
		private:
			uint id;
			FlashDIMM *parentFlashDIMM;
			Channel *channel;
			uint dataCyclesLeft;
			//std::vector<uint> controlCyclesLeft;//since separate planes can theoretically read, write, and erase at the same time
			std::queue<ChannelPacket *> returnDataPackets;
			std::vector<Plane> planes;
			ChannelPacket *currentCommand;

			//for first implementation without contention
			std::queue<ChannelPacket *> commands;
			uint controlCyclesLeft;
	};
}
#endif
