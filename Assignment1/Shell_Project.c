#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

char isbg; //flag to detect wether it is background or foreground process

// function parse is to separate arguments
int parse( char *line,char **argv)
{
char i,firstquote;
while(*line != '\0') //loop if we don't reach the end of statement
	{
	//if there are space or tab ,replace it with null character
	while(*line == ' ' || *line == '\t'){*line = '\0';line++;}
   //condition to check if there are quotes or not ,it is used in commands as echo and gedit
    if(*line=='"') 
    {
   *line='\0'; //replace quote with null 
    line++;
    *argv = line;
    argv++;
i++;
    while(*line!='"' && *line != '\n' ) line++; // search for the second quote or the enter character
    *line='\0'; //replace quote with null 
line++; 
   }
else{
 *argv = line; //if there is no quotes it will assign argument to the current address to the array
    argv++;
i++;
}   

//if no space , tab , null increment line 
     while(*line != ' ' && *line != '\t' && *line != '\0'){
     if (*line =='\n')*line = '\0';  //indication for the end of statement
     line++;
}
    
   
    }
if(i==1&&**(argv-1)=='\0'){*(argv-1)=='\0';return 0;}
if(**(argv-1)=='\0')argv--; 	
	//to test if last argument equal & or not example "gedit &"
	if(strcmp(*(argv-1), "&") == 0){
	*(argv-1) = '\0';
	isbg=1;
}
	else{
	line=*(argv-1);
	i=strlen(line);
	//to test if the last argument contains & at the end or not example "gedit&"
   if(*(line+i-1)=='&'){
	*(line+i-1) = '\0';
	isbg=1;
	*argv = '\0';
	}
	else{
	isbg=0;
	*argv = '\0';
	}
   }

}
int execute(char **argv)
// Forks a child process to run execvp
{
	pid_t pid;
	pid = fork();
	if(pid < 0)
	// Fork failed
	{
		//can't fork 
		perror("Error");
	}
	else if (pid == 0)
	// In child process
	{
         if (*argv[0]=='\0'){return 0;} 

else if (execvp(argv[0], argv) == -1) 
  { perror("Can't excute"); }
		

	}

	else if(isbg==0)
	// In parent process wait if foreground
	{
		wait(NULL);
return 0;
	}
         // In parent process ,don't wait if background
	else{
return 0;
	}

}
int main()
{   char *ptr;
	char line[512];
	char *argv[128];


	int num;
	while(1)
	// Main loop
	{  num=0;
		printf("Shell@project> ");
           //get the command and the statement
		while((line[num++]=fgetc(stdin))!='\n'){
                 if(num==512){   while(fgetc(stdin)!='\n');  break;}
                       //if it is equal EOF error happened
                        // if it exceeds 512 i don't care with the other characters more than 512   
                  

                       }                         
                     
line[num]='\0'; // put the null character at end of array
if(num==512) // if exceed 512 print message
		{printf("it exceeds limits\n");
          continue;
		}
		parse(line,argv);
   if(strcmp(argv[0], "cd") == 0) // cd is built-in function
    {	

if (chdir(argv[1]) == -1)
   perror("Error:");

		}

else if(strcmp(argv[0], "exit") == 0) // if exit the return and terminate the program
{return 0;

}		
else{
                    
execute(argv);//execute the command

	}


}
	return 0;
}
