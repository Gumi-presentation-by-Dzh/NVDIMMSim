#!/bin/sh

emacs TraceBasedSim.cpp SimObj.cpp SmallAccessFtl.cpp Plane.cpp Page.cpp NVDIMM.cpp Init.cpp Ftl.cpp FlashTransaction.cpp  Die.cpp Controller.cpp ChannelPacket.cpp Channel.cpp Block.cpp --eval '(delete-other-windows)'&

emacs TraceBasedSim.h SimObj.h SmallAccessFtl.h Plane.h Page.h NVDIMM.h Init.h Ftl.h FlashTransaction.h FlashConfiguration.h Die.h Controller.h ChannelPacket.h Channel.h Callbacks.h  Block.h --eval '(delete-other-windows)'&

echo opening files
