#ifndef DATA_H
#define DATA_H

#include "../string/string.h"

typedef struct {
	String city;
	String street;
	unsigned int houseNumber;
	String building;
	unsigned int apartmentNumber;
	String postalCode;
} Address;

Address createAddress(const char* city, const char* street, unsigned int houseNumber, const char* building,
                      unsigned int apartmentNumber, const char* postalCode);
void deleteAddress(Address* address);

typedef struct {
	Address recipient;
	float weight;
	String mailId;
	String creationTime;
	String deliveryTime;
} Mail;

Mail createMail(Address recipient, float weight, const char* mailId, const char* creationTime,
                const char* deliveryTime);
void deleteMail(Mail* mail);
int compareMail(const Mail* m1, const Mail* m2);
int validateAddress(const char* city, const char* street, unsigned int houseNumber, const char* building,
                    unsigned int apartmentNumber, const char* postalCode);
int validateMail(const Address* recipient, float weight, const char* mailId, const char* creationTime,
                 const char* deliveryTime);

#endif
