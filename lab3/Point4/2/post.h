#ifndef POST_H
#define POST_H

#include "data.h"

typedef struct {
	Address* currentOfficeAddress;
	Mail* mails;
	int mailCount;
} Post;

Post createPost(Address* currentOfficeAddress);
void deletePost(Post* post);
int addMail(Post* post, Mail mail);
void sortMails(Post* post);

#endif
