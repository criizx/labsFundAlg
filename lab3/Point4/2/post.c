#include "post.h"

#include <stdio.h>  // Для вывода ошибок
#include <stdlib.h>

Post createPost(Address* currentOfficeAddress) {
	Post post;
	post.currentOfficeAddress = currentOfficeAddress;
	post.mails = NULL;
	post.mailCount = 0;
	return post;
}

void deletePost(Post* post) {
	for (int i = 0; i < post->mailCount; i++) {
		deleteMail(&post->mails[i]);
	}
	free(post->mails);
	post->mails = NULL;
	post->mailCount = 0;
}

int addMail(Post* post, Mail mail) {
	Mail* newMails = realloc(post->mails, (post->mailCount + 1) * sizeof(Mail));
	if (!newMails) {
		fprintf(stderr, "Memory allocation failed for adding a new Mail.\n");
		return -1;
	}
	post->mails = newMails;
	post->mails[post->mailCount] = mail;
	post->mailCount++;
	return 0;
}

int compareMails(const void* a, const void* b) { return compareMail((const Mail*)a, (const Mail*)b); }

void sortMails(Post* post) { qsort(post->mails, post->mailCount, sizeof(Mail), compareMails); }
