#include <stdio.h>
#include <string.h>
#include <libc.h>
#include <callSyscall.h>
#include <soundModule.h>


void putchar(char c){
	if(c!= 0){
	callSyscall(WRITE,(void*) 1,(void*)&c,(void*)1,(void*)0,(void*)0,(void*)0);
	}
	
}
char getchar(){
	char c = 0;


	callSyscall(READ,(void*)0,(void*)&c,(void*)1,(void*)0,(void*)0,(void*)0);
	return c;
}

void printf(const char* format, ...){
  va_list arg;
  va_start(arg, format);
  int i;
  char* s;
  for(; *format != 0; format++){
    if(*format == '%'){
      format++;
      switch(*format){
            case 'c' :
              i = va_arg(arg,int);
              putchar(i);
              break;

            case 'd' :
              i = va_arg(arg,int);
              printDec(i);
             break;

            case 's':
              s = va_arg(arg,char*);
              while(*s){
                putchar(*s);
                s++;
              }
              break;
      }
    }else{
      putchar(*format);
    }
  }
}

int scanf(char*format,...){
	char c;
	int j = 0;
	char buffer[MAX_LENGHT];
	while((c = getchar()) != '\n' && j <MAX_LENGHT){
		
		if(c != 0){
			if(c != '\b'){
					buffer[j] = c;
					putchar(c);
				
					j++;
			}else{
				if(j > 0){
					j--;
					putchar(c);
				}else{
					beep(1,9500);
				}
					
			}
				
		}
			
	}
	buffer[j] = '\0';

	 va_list arg;
  va_start(arg, format);
  int i = 0;
  void * parameter;
  int parametersLoaded = 0;
  int number = 0;
  for(int k = 0; (c = buffer[k]) != '\0';k++){
 
	 if(format[i++] == '%'){
        parameter = va_arg(arg,void *);
        switch(format[i]){
            case 'c' :
              *(char *)parameter = c;
              break;
            case 'd' :
              do{
                number *= 10;
                number += (c - '0');
		
              }while((c = buffer[++k]) >= '0' && c <= '9');

              *(int *)parameter = number;
			   i++;
              number = 0;
              break;
            case 's':
              do{
                *(char *)parameter = c;
                parameter++;
			
              }while((c = buffer[++k]) != ' ' && c != '\n');
			  *(char *)parameter = '\0';
			  i++;
              break;
        }//switch
        parametersLoaded++;

      }else if(c != format[i]){
		break;
	  }
	  i++;
	
  }
  return parametersLoaded;
}

void perror(const char * buffer){
	callSyscall(WRITE,(void*)2,(void*)buffer,(void*)strlen(buffer),(void*)0,(void*)0,(void*)0);
}


void printDec(uint64_t value){
	printBase(value, 10);
}

void printHexa(uint64_t value){
	printBase(value, 16);
}

void printBin(uint64_t value){
	printBase(value, 2);
}

void printBase(uint64_t value, uint64_t base){
	static char buffer[64] = { '0' };
    intToBase(value, buffer, base);
    printf(buffer);
}




