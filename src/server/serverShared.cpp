#include "serverShared.hpp"

sClient::~sClient() {
	// Make sure thread gets stopped
	thr.request_stop();
	thr.join();
	//delete thr;
}

// To be run in parallel by each client's thread; listens to
// their packets and responds accordingly.
inline void sClient::serve() {
	comm::read<(sSock)
}