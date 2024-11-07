#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../string/string.h"
#include "data.h"
#include "post.h"

void printMail(const Mail* mail) {
    printf("Mail ID: %s\n", mail->mailId.data);
    printf("Recipient: %s, %s, House: %u, Building: %s, Apartment: %u, Postal Code: %s\n",
           mail->recipient.city.data, mail->recipient.street.data, mail->recipient.houseNumber,
           mail->recipient.building.data, mail->recipient.apartmentNumber, mail->recipient.postalCode.data);
    printf("Weight: %.2f\n", mail->weight);
    printf("Creation Time: %s\n", mail->creationTime.data);
    printf("Delivery Time: %s\n", mail->deliveryTime.data);
}

void addMailInteractive(Post* post) {
    char *city, *street, *building, *postalCode, *mailId, *creationTime, *deliveryTime;
    unsigned int houseNumber, apartmentNumber;
    float weight;

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
    scanf("%ms", &mailId);
    printf("Enter creation time (dd:MM:yyyy hh:mm:ss): ");
    scanf("%ms", &creationTime);
    printf("Enter delivery time (dd:MM:yyyy hh:mm:ss): ");
    scanf("%ms", &deliveryTime);

    Address recipient = createAddress(city, street, houseNumber, building, apartmentNumber, postalCode);
    Mail mail = createMail(recipient, weight, mailId, creationTime, deliveryTime);
    addMail(post, mail);

    free(city);
    free(street);
    free(building);
    free(postalCode);
    free(mailId);
    free(creationTime);
    free(deliveryTime);
}

void searchMailById(Post* post) {
    char *mailId;
    printf("Enter mail ID to search: ");
    scanf("%ms", &mailId);

    for (int i = 0; i < post->mailCount; i++) {
        if (areStringsEqual(&post->mails[i].mailId, &(String){mailId, 14})) {
            printMail(&post->mails[i]);
            free(mailId);
            return;
        }
    }
    printf("Mail with ID %s not found.\n", mailId);
    free(mailId);
}

void printDeliveredMails(Post* post) {
    time_t currentTime = time(NULL);

    for (int i = 0; i < post->mailCount; i++) {
        struct tm deliveryTm = {0};
        strptime(post->mails[i].deliveryTime.data, "%d:%m:%Y %H:%M:%S", &deliveryTm);
        time_t deliveryTime = mktime(&deliveryTm);
        if (difftime(currentTime, deliveryTime) >= 0) {
            printMail(&post->mails[i]);
        }
    }
}

void printExpiredMails(Post* post) {
    time_t currentTime = time(NULL);

    for (int i = 0; i < post->mailCount; i++) {
        struct tm deliveryTm = {0};
        strptime(post->mails[i].deliveryTime.data, "%d:%m:%Y %H:%M:%S", &deliveryTm);
        time_t deliveryTime = mktime(&deliveryTm);
        if (difftime(currentTime, deliveryTime) > 0) {
            printMail(&post->mails[i]);
        }
    }
}

int main() {
    Address officeAddress = createAddress("City", "Street", 1, "Building", 1, "123456");
    Post post = createPost(&officeAddress);

    int choice;
    while (1) {
        printf("1. Add Mail\n2. Search Mail by ID\n3. Show Delivered Mails\n4. Show Expired Mails\n5. Exit\nEnter choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                addMailInteractive(&post);
                sortMails(&post);
                break;
            case 2:
                searchMailById(&post);
                break;
            case 3:
                printDeliveredMails(&post);
                break;
            case 4:
                printExpiredMails(&post);
                break;
            case 5:
                deletePost(&post);
                deleteAddress(&officeAddress);
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}
