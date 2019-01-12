#include "TcpSocket.h"

using namespace std;

TcpSocket::TcpSocket(): _os(nullptr), _is(nullptr) {
	_socketID = socket(AF_INET, SOCK_STREAM, 0);
	if (_socketID < 0) {
		perror("Could not open socket");
		exit(1);
	}
	cout << "Socket is now open" << endl;
}

void TcpSocket::bindSocket(string address, int port) {
	bzero((char *) &_serv_addr, sizeof(_serv_addr));
	_serv_addr.sin_family = AF_INET;
	if (address.compare("") == 0)
		_serv_addr.sin_addr.s_addr = INADDR_ANY;
	else {
		inet_aton(address.c_str(), &_serv_addr.sin_addr);
	}
	_serv_addr.sin_port = htons(port);

	if (bind(_socketID, (struct sockaddr *) &_serv_addr, sizeof(_serv_addr)) < 0) {
    	perror("ERROR while binding");
    	exit(1);
	}
	cout << "Server is now binded to (" << inet_ntoa(_serv_addr.sin_addr) << ", " << port << ")" << endl;
}

int TcpSocket::acceptClient() {
	int clilen = sizeof(_cli_addr);
	int newSocket = accept(_socketID, (struct sockaddr*) &_cli_addr, (socklen_t*) &clilen);
	if (newSocket < 0) {
		perror("Could not accept a client");
		exit(1);
	}
	cout << "Accepted the client: " << inet_ntoa(_cli_addr.sin_addr) << ", " << _cli_addr.sin_port << endl;
	streambuf* socketBuffer = new SocketBuffer(newSocket);
	_os = new SockOS(socketBuffer);
	_is = new SockIS(socketBuffer);
	return newSocket;
}

void TcpSocket::listenToClients(unsigned int clientNumber) const {
	if (listen(_socketID, clientNumber) < 0) {
		perror("Socket could not listen");
		exit(1);
	}
	cout << "Server is now listenting to " << clientNumber << " clients" << endl;
}

void TcpSocket::closeSocket() {
	if (_socketID == -1)
		return;
	if (close(_socketID) < 0) {
		perror("Could not close the socket" + _socketID);
		exit(1);
	}
	_socketID = -1;
}

TcpSocket::~TcpSocket() {
	if (_os != nullptr) {
		delete _os->rdbuf(); // deleting the streambuf we gave _os in c'tor
		delete _os;
	}
	if (_is != nullptr)
		delete _is;
	this->closeSocket();
}