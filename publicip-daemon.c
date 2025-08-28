#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

// defines
#define OFFLINE_CYCLE 60*5 // offline cycle time
#define ONLINE_CYCLE 60*10 // online cycle time

#define SIZE 3
#define IP_SIZE 16

// prototypes
int internet_access();
void ip_checker();
void mail_sender(char*);
int curl_ip(char*);
void ip_file_creator();

int main(int argc, char* argv[]){
	if(argc != 2) return 0;
	argv[1][strcspn(argv[1], "\n")] = '\0';
    FILE *file = fopen(argv[1], "r");
    if(!file) return 0;

    char * state = (char *) malloc(sizeof(char)*SIZE);
    while(sleep(1), 1){ // wating for the 'up' interface state
        if(!fgets(state, SIZE, file)) return 0;
		rewind(file);
        if(!strcmp(state, "up")){ // state is 'up'
        	free(state);
        	fclose(file);   
            while (!internet_access()) sleep(5); // this while waits for internet access
			// the second while checks for the public IP and waits if there's no internet access
            while(ip_checker(), sleep(ONLINE_CYCLE), 1) if(!internet_access()) while(sleep(OFFLINE_CYCLE), 1) if(internet_access()) break; 
        }
    }
}

void ip_checker(){    
    char ip[IP_SIZE];
    if(!curl_ip(ip)) return; // gets the current IP

	// old IP from the ip.txt file
	FILE* fileIP = fopen("ip.txt", "r");
	if(!fileIP) {
		ip_file_creator();
		fileIP = fopen("ip.txt", "r");
	}
    
    char oldip[IP_SIZE];
    fgets(oldip, IP_SIZE, fileIP); // this line reads the ip.txt file
    fclose(fileIP);

    ip[strcspn(ip, "\n")] = '\0';
    oldip[strcspn(oldip, "\n")] = '\0';

    if(strcmp(ip, oldip)) mail_sender(ip); // if the IPs are different, call the mail_sender() function
}
void mail_sender(char* ip){
    char command[64];
    snprintf(command, sizeof(command), "sh ./sendmail.sh %s", ip);
    if(system(command)) return; // this line runs the script

    // ip.txt update
    FILE *fileIP = fopen("ip.txt", "w");
    if (!fileIP) return;
    fprintf(fileIP, "%s", ip);
    fclose(fileIP);
}


// other functions
int internet_access(){
	return !system("ping -c 1 -W 1 1.1.1.1");
}
int curl_ip(char* ip){
	FILE* curl = popen("curl -s ident.me", "r");
	if(!curl) return 0;
	if(fgets(ip, IP_SIZE, curl)) {
		pclose(curl);
		return 1;
	}
	pclose(curl);
	return 0;
}
void ip_file_creator(){
	FILE* file = fopen("ip.txt", "w");
	if(file) fclose(file);
}
