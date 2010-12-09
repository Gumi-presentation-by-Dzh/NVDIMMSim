//Block.cpp
//Block functions

#include "Block.h"

using namespace std;
using namespace NVDSim;

Block::Block(uint block){
	block_num = block;
}

Block::Block(){

}

void *Block::read(uint page_num){
	if (pages.find(page_num) == pages.end()){
		DEBUG("Request to read page "<<page_num<<" failed: nothing has been written to that address");
		return (void *)0x0;
	} else if (DEVICE_TYPE == 'PCM'){
	        
	  // pages store words
		return pages[page_num];
	}
}

void Block::write(uint page_num, void *data){
	if (pages.find(page_num) == pages.end()){
		pages[page_num]= data;
	} else{
		/*ERROR("Request to write page "<<page_num<<" failed: page has been written to and not erased"); 
		exit(1);*/
		
		//Until garbage collection is implemented, you can write to pages that have already been written to
		pages[page_num]= data;
	}
}

void Block::erase(){
	pages.clear();
}

