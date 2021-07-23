#include <shell.h>
#include <stdio.h>
#include <string.h>
#include <commands.h>
#include <graphics.h>

static void clearBuffer(char * buffer);
static void commandDispacher(char* command,char*parameter);
static void commandNotFound();
static int64_t getCommandId(char * buffer);
static void help();

static struct commandStruct commands[] = {{C_TIME,"time","Displays current date and time",0},
										{C_PRINTMEM,"printmem","Performs a 32-byte memory dump from the address received as an argument",1},
										{C_INFOREG,"inforeg","Prints the value of all the registers",0},
										{C_ARACNOID,"aracnoid","Iniciates aracnoid, press F1 to save game",0},
										{C_OPCODEEX,"opcodeex","Executes Invalid OP Code Interruption",0},
										{C_ZERODIVEX,"zerodivex","Executes Zero Division Interruption",0},
										{C_HELP,"help","Shows all available commands",0},
										{C_CLEAR,"clear","Clears the screen"},
										{0,"","",0}};

void initShell(){

	char command[MAX_LENGHT] ={0};
	char parameter[MAX_LENGHT] = {0};

 printf("\nTerminal:\n\nPlease type 'help' to find out about our commands\n\n\n");
	while(1){
	
		printf("$> ");
		clearBuffer(command);
		clearBuffer(parameter);
		scanf("%s %s",command,parameter);
		putchar('\n');
		commandDispacher(command,parameter);
	}
		
}

static void commandDispacher(char* command,char*parameter){

	

	uint64_t id = getCommandId(command);
	switch(id){

		case C_HELP:
			help();
		break;

		case C_TIME:
			time();
		break;

		case C_PRINTMEM:
			printMem(parameter);
		break;

		case C_INFOREG:
			infoReg();
		break;

		case C_ARACNOID:
			aracnoid();
	
		break;

		case C_OPCODEEX:
			invalidopCodeException();
		break;

		case C_ZERODIVEX:
			zeroDivException();
		break;

		case C_CLEAR:
			clear();
		break;

		default:
		commandNotFound();
		break;
		
		
	}
	
	
}

static int64_t getCommandId(char * buffer){
	
	for(int i = 0; strcmp(commands[i].name,"") != 0;i++){
		
		if(strcmp(commands[i].name,buffer) == 0){
			return commands[i].id;

		}
	}
	return -1;
	
}	

static void help(){
	for(int i = 0; *commands[i].name != 0;i++){
		printf("%s   :   %s\n",commands[i].name,commands[i].desc);
	}
}


static void commandNotFound(){
	perror("shell: command not found\n");
}



static void clearBuffer(char * buffer){
	while(*buffer){
		*buffer = 0;
		buffer++;
	}
}
