#include "SocketBuffer.h"

using namespace std;

// sending with \r\n at the end of the string we received
streamsize SocketBuffer::xsputn(const char* s, streamsize n) {
	void* pointer;
	char* str = (char*) malloc(n + 1); // allocating memory so str can hold the address;
	if (str == NULL) {
		perror("Failed to allocate space for xsputn");
		exit(1);
	}
	strncpy(str, s, n); // now str contains the address off the string we want to send
	str[n] = 0;
	string strCopy = string(str);
	stringstream ss(strCopy); // adding str to the string stream
	ss >> pointer; // now pointer has the adress of the string we need to send
	char* stringPointer = (char*) pointer; // now stringPointer is the
	int len = strlen(stringPointer) + 3; // the length of the string we send + 2 bytes for '\r\n' + another byte for '\0'
	str = (char*) realloc(str, len);
	if (str == NULL) {
		perror("Failed to allocate space for xsputn");
		exit(1);
	}
	strcpy(str, stringPointer); // copying the string we want to send
	strcat(str, "\r\n"); // adding '\r\n' at the end of the string we send
	int bytesSent = send(_sockID, str, len, 0);
	free(str); // freeing allocated memory
	return bytesSent;
}