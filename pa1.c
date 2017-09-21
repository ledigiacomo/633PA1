//Programming Assignment 1 for COMP 633 FA 2017
//Luke DiGiacomo
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct body{
	int id;
	double mass;
	double x_position;
	double y_position;
	double x_velocity;
	double y_velocity;
};

typedef struct body Body;

void printBody(Body* body){
	printf("ID: %d\n", body->id);
	printf("Mass: %f\n", body->mass);
	printf("Position: <%f, %f>\n", body->x_position, body->y_position);
	printf("Acceleration: <%f, %f>\n\n", body->x_velocity, body->y_velocity);
}

int parseFromCsv(char* line, Body* body){
	char* tok = strtok(line, ", ");
	body->id = atoi(tok);
	tok = strtok(NULL, ", ");
	body->mass = atof(tok);
	tok = strtok(NULL, ", ");
	body->x_position = atof(tok);
	tok = strtok(NULL, ", ");
	body->y_position = atof(tok);
	tok = strtok(NULL, ", ");
	body->x_velocity = atof(tok);
	tok = strtok(NULL, ", ");
	body->y_velocity = atof(tok);
}

int main(){
	FILE* csv = fopen("PA1_input1.csv", "r");
	char line[256];

	//get and ignore fist 'header' line
	fgets(line, sizeof(line), csv);
	while (fgets(line, sizeof(line), csv)) {
		Body body;
		parseFromCsv(line, &body);
		printBody(&body);
    }

    fclose(csv);

    return 0;
}