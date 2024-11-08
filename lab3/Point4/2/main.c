#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../string/string.h"
#include "data.h"
#include "post.h"

void printMail(const Mail* mail) {
	printf("Mail ID: %s\n", mail->mailId.data);
	printf("Recipient: %s, %s, House: %u, Building: %s, Apartment: %u, Postal Code: %s\n", mail->recipient.city.data,
	       mail->recipient.street.data, mail->recipient.houseNumber, mail->recipient.building.data,
	       mail->recipient.apartmentNumber, mail->recipient.postalCode.data);
	printf("Weight: %.2f\n", mail->weight);
	printf("Creation Time: %s\n", mail->creationTime.data);
	printf("Delivery Time: %s\n", mail->deliveryTime.data);
}

void addMailInteractive(Post* post) {
	char *city, *street, *building, *postalCode;
	unsigned int houseNumber, apartmentNumber;
	float weight;
	char creationTime[20], deliveryTime[20], mailId[15];

	printf("Enter recipient city: ");
	scanf("%ms", &city);
	printf("Enter recipient street: ");
	scanf("%ms", &street);
	printf("Enter house number: ");
	scanf("%u", &houseNumber);
	printf("Enter building: ");
	scanf("%ms", &building);
	printf("Enter apartment number: ");
	scanf("%u", &apartmentNumber);
	printf("Enter postal code: ");
	scanf("%ms", &postalCode);

	printf("Enter mail weight: ");
	scanf("%f", &weight);
	printf("Enter mail ID (14 digits): ");
	scanf("%14s", mailId);
	getchar();
	printf("Enter creation time (dd:MM:yyyy hh:mm:ss): ");

	if (fgets(creationTime, sizeof(creationTime), stdin) == NULL) {
		fprintf(stderr, "Error reading creation time.\n");
		exit(EXIT_FAILURE);
	}
	Address recipient = createAddress(city, street, houseNumber, building, apartmentNumber, postalCode);
	Mail mail = createMail(recipient, weight, mailId, creationTime);
	addMail(post, mail);

	free(city);
	free(street);
	free(building);
	free(postalCode);
}

void deleteMailById(Post* post) {
	char* mailId;
	printf("Enter mail ID to delete: ");
	scanf("%ms", &mailId);

	int index = -1;
	for (int i = 0; i < post->mailCount; i++) {
		if (areStringsEqual(&post->mails[i].mailId, &(String){mailId, 14})) {
			index = i;
			break;
		}
	}

	if (index != -1) {
		deleteMail(&post->mails[index]);

		for (int i = index; i < post->mailCount - 1; i++) {
			post->mails[i] = post->mails[i + 1];
		}

		post->mailCount--;
		post->mails = realloc(post->mails, post->mailCount * sizeof(Mail));
		printf("Mail with ID %s deleted successfully.\n", mailId);
	} else {
		printf("Mail with ID %s not found.\n", mailId);
	}

	free(mailId);
}

Mail* searchMailById(Post* post) {
	char* mailId;
	printf("Enter mail ID to search: ");
	scanf("%ms", &mailId);

	for (int i = 0; i < post->mailCount; i++) {
		if (areStringsEqual(&post->mails[i].mailId, &(String){mailId, 14})) {
			return &post->mails[i];
		}
	}
	printf("Mail with ID %s not found.\n", mailId);
	free(mailId);
}

void printDeliveredMails(Post* post) {
	time_t currentTime = time(NULL);
	for (int i = 0; i < post->mailCount; i++) {
		struct tm deliveryTm = {0};
		if (!strcmp(post->mails[i].deliveryTime.data, "")) {
			strptime(post->mails[i].deliveryTime.data, "%d:%m:%Y %H:%M:%S", &deliveryTm);
			time_t deliveryTime = mktime(&deliveryTm);
			if (difftime(currentTime, deliveryTime) >= 0) {
				printMail(&post->mails[i]);
			}
		}
	}
}

void printExpiredMails(Post* post) {
	time_t currentTime = time(NULL);
	int diff = 180 * 60 * 60 * 24;
	for (int i = 0; i < post->mailCount; i++) {
		struct tm createTm = {0};
		strptime(post->mails[i].creationTime.data, "%d:%m:%Y %H:%M:%S", &createTm);
		time_t creationTime = mktime(&createTm);
		if (difftime(currentTime, creationTime) > diff) {
			printMail(&post->mails[i]);
		}
	}
}

int main() {
	Address officeAddress = createAddress("City", "Street", 1, "Building", 1, "123456");
	Post post = createPost(&officeAddress);

	int choice;
	while (1) {
		printf(
		    "1. Add Mail\n2. Delete Mail by ID\n3. Search Mail by ID\n4. Show Delivered Mails\n5. Show Expired "
		    "Mails\n6. Add Delivery time\n0. Exit\nEnter choice: ");
		scanf("%d", &choice);
		switch (choice) {
			case 1:
				addMailInteractive(&post);
				sortMails(&post);
				break;
			case 2:
				deleteMailById(&post);
				break;
			case 3:
				printMail(searchMailById(&post));
				break;
			case 4:
				printDeliveredMails(&post);
				break;
			case 5:
				printExpiredMails(&post);
				break;
			case 6:
				char* deliveryTime;
				Mail* mail = searchMailById(&post);
				getchar();
				printf("Enter creation time (dd:MM:yyyy hh:mm:ss): ");
				fgets(deliveryTime, sizeof(deliveryTime), stdin);
				setDeliveryTime(mail, deliveryTime);
			case 0:
				deletePost(&post);
				deleteAddress(&officeAddress);
				return 0;
			default:
				printf("Invalid choice. Please try again.\n");
		}
	}
	return 0;
}
