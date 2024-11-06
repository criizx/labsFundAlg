#include "data.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int validateAddress(const char* city, const char* street, unsigned int houseNumber, const char* building,
                    unsigned int apartmentNumber, const char* postalCode) {
	if (!city || city[0] == '\0' || !street || street[0] == '\0') return -1;
	if (apartmentNumber == 0) return -1;

	if (strlen(postalCode) != 6) return -1;
	for (int i = 0; i < 6; i++) {
		if (!isdigit(postalCode[i])) return -1;
	}
	return 0;
}

int validateMail(const Address* recipient, float weight, const char* mailId, const char* creationTime,
                 const char* deliveryTime) {
	if (!recipient || weight < 0) return -1;

	// Валидация mailId: должно быть 14 цифр
	if (strlen(mailId) != 14) return -1;
	for (int i = 0; i < 14; i++) {
		if (!isdigit(mailId[i])) return -1;
	}

	// Формат строки даты и времени
	const char* timeFormat = "%d:%m:%Y %H:%M:%S";
	struct tm creationTm = {0};
	struct tm deliveryTm = {0};

	// Проверка строки даты и времени для creationTime
	if (!strptime(creationTime, timeFormat, &creationTm)) {
		return -1;  // Неверный формат даты и времени
	}

	// Проверка строки даты и времени для deliveryTime
	if (!strptime(deliveryTime, timeFormat, &deliveryTm)) {
		return -1;  // Неверный формат даты и времени
	}

	// Преобразуем в `time_t` для сравнения
	time_t creationEpoch = mktime(&creationTm);
	time_t deliveryEpoch = mktime(&deliveryTm);

	if (creationEpoch == -1 || deliveryEpoch == -1) {
		return -1;  // Ошибка преобразования времени
	}

	// Проверка, что deliveryTime наступает после creationTime
	if (difftime(deliveryEpoch, creationEpoch) < 0) {
		return -1;  // deliveryTime раньше creationTime
	}

	return 0;
}

Address createAddress(const char* city, const char* street, unsigned int houseNumber, const char* building,
                      unsigned int apartmentNumber, const char* postalCode) {
	if (validateAddress(city, street, houseNumber, building, apartmentNumber, postalCode) != 0) {
		fprintf(stderr, "Invalid address data\n");
		exit(EXIT_FAILURE);
	}

	Address address;
	address.city = createString(city);
	address.street = createString(street);
	address.houseNumber = houseNumber;
	address.building = createString(building);
	address.apartmentNumber = apartmentNumber;
	address.postalCode = createString(postalCode);
	return address;
}

void deleteAddress(Address* address) {
	deleteString(&address->city);
	deleteString(&address->street);
	deleteString(&address->building);
	deleteString(&address->postalCode);
}

Mail createMail(Address recipient, float weight, const char* mailId, const char* creationTime,
                const char* deliveryTime) {
	if (validateMail(&recipient, weight, mailId, creationTime, deliveryTime) != 0) {
		fprintf(stderr, "Invalid mail data\n");
		exit(EXIT_FAILURE);
	}

	Mail mail;
	mail.recipient = recipient;
	mail.weight = weight;
	mail.mailId = createString(mailId);
	mail.creationTime = createString(creationTime);
	mail.deliveryTime = createString(deliveryTime);
	return mail;
}

void deleteMail(Mail* mail) {
	deleteAddress(&mail->recipient);
	deleteString(&mail->mailId);
	deleteString(&mail->creationTime);
	deleteString(&mail->deliveryTime);
}

int compareMail(const Mail* m1, const Mail* m2) {
	int result = compareStringLexicographically(&m1->recipient.postalCode, &m2->recipient.postalCode);
	if (result == 0) {
		result = compareStringLexicographically(&m1->mailId, &m2->mailId);
	}
	return result;
}
