#ifndef FTL_H
#define FTL_H
//Ftl.h
//header file for the ftl

#include "SimObj.h"
#include "FlashConfiguration.h"
#include "ChannelPacket.h"
#include "FlashTransaction.h"
#include "Controller.h"

namespace NVDSim{
	class Controller;
	class Ftl : public SimObj{
		public:
			Ftl(Controller *c);
			ChannelPacket *translate(ChannelPacketType type, uint64_t addr);
			bool addTransaction(FlashTransaction &t);
			void update(void);
			bool checkGC(void); 
			void runGC(void); 
			uint64_t get_ptr(void); 
			void inc_ptr(void); 
			Controller *controller;
		private:
			uint offset, wordBitWidth, pageBitWidth, blockBitWidth, planeBitWidth, dieBitWidth, packageBitWidth;
			uint channel, die, plane, lookupCounter;
			uint64_t used_page_count;
			FlashTransaction currentTransaction;
			uint busy;
			std::unordered_map<uint64_t,uint64_t> addressMap;
			std::vector<vector<vector<bool>>> dirty;
			std::vector<vector<vector<bool>>> used;
			std::list<FlashTransaction> transactionQueue;
			std::unordered_map<uint64_t,uint64_t> erase_counter;
	};
}
#endif
