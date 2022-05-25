#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include <sys/stat.h> 
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>

void Openwriting();
void Openreading(int, float, int);
char* GenerateSpaceMemory(int, int); 

int main()
{
    // FIFO
	int fd;
	if (mkfifo("myfifo", 0777) == -1){  // creating fifo file 
		if (errno != EEXIST){
			printf("Could not create fifo file\n");
			return 1;
		}
	}

    char* data; //char for send
    int kbNum = 1; //amount
    int space = 59999;
    data = GenerateSpaceMemory(kbNum, space); //Generate space of 10*kbNum and fill it with a's
    Openwriting(fd, data, space*kbNum); //Writing and sending  //100kb-tope funcional
    //999999
	return 0;
}


char* GenerateSpaceMemory(int kbNum, int space){

    int bytes = space*kbNum;
    char *data = malloc(bytes);
    //Filling with a's
    for (int i=0; i<bytes; i++){
        data[i]= 'a';
    }
    //filling verification
    for (int i=0; i<bytes; i++){
        if(data[i] != 'a'){
            printf("It is not complete");
        }
    }
    return data;    
}


void Openwriting(int fd, char* arrSend, int size ){
    fd = open("myfifo", O_WRONLY); // open pipe for writing
    if (fd == -1){
        printf("Error al abrir la tuberia");// can't open pipe
    }
    if (write(fd, arrSend, size) == -1){ // writing datas of send
        printf("Error al escribir"); // can't write from pipe
    }
    close(fd); //close pipe
}

void Openreading(int fd, float avg_travel_time, int size ){
    fd = open("myfifo", O_RDONLY); // open pipe for reading
    if (fd == -1){
        printf("Error al abrir la tuberia"); // can't open pipe
    }
    if (read(fd, &avg_travel_time, size) == -1){ 
        printf("Error al leer"); // can't read from pipe
    } else {
        if(avg_travel_time == -1.00){
            printf("NA.\n");
        } else {
            printf("El tiempo medio de viaje es: %0.2f.\n", avg_travel_time);
        }
    }
    close(fd); //close pipe
}
