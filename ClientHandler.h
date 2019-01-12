#ifndef CLIENT_HANDLER_H
#define CLIENT_HANDLER_H

#include "SockIOS.h"

class ClientHandler {
public:
	virtual void handleClient(SockIS* SockIS, SockOS* SockOS) = 0;
	virtual ~ClientHandler() {}
};

#endif