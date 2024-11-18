#ifndef ENCODER_H
#define ENCODER_H

#include <cstddef>
#include <string>
#include <vector>

using namespace std;

class encoder {
   private:
	vector<byte> key;

   public:
	encoder(const vector<byte>& encryptionKey) : key(encryptionKey) {}

	void setKey(const vector<byte>& newKey) { key = newKey; }

	void encode(const string& inputFile, const string& outputFile, bool encrypt);
};

#endif
