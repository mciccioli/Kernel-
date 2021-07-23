#include <libc.h>

char* intToBase(int num, char* str, int base) 
{ 
    int i = 0; 
    int isNegative = 0; 
  
    /* Handle 0 explicitely, otherwise empty string is printed for 0 */
    if (num == 0) 
    { 
        if(base == 16){
            str[i++] = '0';
            str[i++] = 'x';
        }
        str[i++] = '0'; 
        str[i] = '\0'; 
        return str; 
    } 
  
    // In standard itoa(), negative numbers are handled only with  
    // base 10. Otherwise numbers are considered unsigned. 
    if (num < 0 && base == 10) 
    { 
        isNegative = 1; 
        num = -num; 
    } 
  
    // Process individual digits 
    while (num != 0) 
    { 
        int rem = num % base; 
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0'; 
        num = num/base; 
    } 
  
    // If number is negative, append '-' 
    if (isNegative) 
        str[i++] = '-'; 
  
      // If base = 16 append 0x
    if (base == 16){
        str[i++] = 'x';
        str[i++] = '0';
    }
    str[i] = '\0'; // Append string terminator 
  
    // Reverse the string 
    reverse(str, i); 
  
    return str; 
} 


void swap ( char *str1, char *str2 ) {
  int tmp;
  tmp = *str1;
  *str1 = *str2;
  *str2 = tmp;
}


void reverse(char str[], int length) 
{ 
    int start = 0; 
    int end = length -1; 
    while (start < end) 
    { 
        swap(str+start, str+end); 
        start++; 
        end--; 
    } 
} 

// convierte string en hexadecimal o decimal a numero
uint64_t atoi(char* s){
    char c = *s++;
    int num = 0;
    if(c == '0' && (*s == 'x' || *s == 'X')){
        s++;
        while(*s != 0){
            num *= 16;
            if(*s >= 'a' && *s <= 'f'){
                num += (*s - 'a' + 10);
            }
            else if(*s >= 'A' && *s <= 'F'){
                num += (*s - 'A' + 10);
            }
            else{
                num += (*s - '0');
            }
            s++;
        }
    }
    else{
        num += (c - '0');
        while(*s != 0){
            num *= 10;
            num += (*s - '0');
            s++;
        }
    }
    return num;
}