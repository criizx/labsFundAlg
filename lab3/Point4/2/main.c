#include <stdio.h>

#include "post.h"

int main() {
	Address officeAddress = createAddress("Main City", "Central St", 1, "A", 0, "123456");
	Post postOffice = createPost(&officeAddress);

	Address recipient1 = createAddress("City1", "Street1", 10, "", 101, "234567");
	Address recipient2 = createAddress("City2", "Street2", 20, "", 202, "123456");

	Mail mail1 = createMail(recipient1, 1.5, "12345678901234", "01:01:2023 10:10:10", "02:01:2023 15:30:00");
	Mail mail2 = createMail(recipient2, 2.0, "23456789012345", "01:01:2023 11:10:10", "02:01:2023 16:30:00");

	if (addMail(&postOffice, mail1) != 0) {
		fprintf(stderr, "Failed to add mail1 to the post office.\n");
		deleteMail(&mail1);
	}
	if (addMail(&postOffice, mail2) != 0) {
		fprintf(stderr, "Failed to add mail2 to the post office.\n");
		deleteMail(&mail2);
	}

	sortMails(&postOffice);

	for (int i = 0; i < postOffice.mailCount; i++) {
		printf("Mail ID: %s, Recipient Postal Code: %s\n", postOffice.mails[i].mailId.data,
		       postOffice.mails[i].recipient.postalCode.data);
	}

	deletePost(&postOffice);
	deleteAddress(&officeAddress);

	return 0;
}
