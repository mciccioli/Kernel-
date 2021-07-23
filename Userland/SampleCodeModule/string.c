#include <string.h>
uint64_t strlen(const char * s){
	uint64_t size = 0;
	while(*s){
		size++;
		s++;
	}
	
	return size;
}
uint64_t strcmp(const char * s1,const char * s2){
	while (*s1 && *s2) {
		if (*s1 > *s2) return 1;
		if (*s1 < *s2) return -1;
		s1++;
		s2++;
	}
	if (*s1) return 1;
	if (*s2)	return -1;
	return 0;
}