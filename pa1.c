//Programming Assignment 1 for COMP 633 FA 2017
//Luke DiGiacomo
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

double GRAVITY = 0.00000000006673;
int FINAL_TIME = 1;

struct body{
	int id;
	double mass;
	double x_position;
	double y_position;
	double x_velocity;
	double y_velocity;
	double x_acceleration;
	double y_acceleration;
};

typedef struct body Body;

void printBody(Body* body){
	printf("ID: %d\n", body->id);
	printf("Mass: %f\n", body->mass);
	printf("Position: <%f, %f>\n", body->x_position, body->y_position);
	printf("Velocity: <%f, %f>\n\n", body->x_velocity, body->y_velocity);
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

	body->x_acceleration = 0;
	body->y_acceleration = 0;

}

int distance(Body* body1, Body* body2){
	double x_difference = body1->x_position - body2->x_position;
	double y_difference = body1->y_position - body2->y_position;
	double sumSquares = x_difference*x_difference + y_difference*y_difference;
	return sqrt(sumSquares);
}

int magnitude(Body* body1, Body* body2){
	double x_sum = body1->x_position + body2->x_position;
	double y_sum = body1->y_position + body2->y_position;
	return sqrt(x_sum*x_sum + y_sum*y_sum);
}

int main(){
	FILE* csv = fopen("PA1_input1.csv", "r");
	char line[256];

	int num_bodies = atoi(fgets(line, sizeof(line), csv));
	Body bodies[num_bodies];

	//get and ignore 'header' line
	fgets(line, sizeof(line), csv);

	int i = 0;
	while (fgets(line, sizeof(line), csv)) {
		Body body;
		parseFromCsv(line, &body);
		bodies[i] = body;
		i++;
    }

    fclose(csv);

    for(i = 0; i < num_bodies; i++){
    	printBody(&bodies[i]);
    }

    int time = 0;
    while(time < FINAL_TIME){
    	for(i = 0; i < num_bodies; i++){
    		int j = 0;
    		double x_force, y_force = 0;

    		//calculate acceleration
    		for(j = 0; j < num_bodies; j++){
    			if(bodies[i].id == bodies[j].id){
    				continue;
    			}

    			double GM = GRAVITY * bodies[i].mass * bodies[j].mass;
    			double mag = magnitude(&bodies[i], &bodies[j]);
    			x_force += (GM * (bodies[i].x_position - bodies[j].x_position)) / (mag*mag*mag);
    			y_force += (GM * (bodies[i].y_position - bodies[j].y_position)) / (mag*mag*mag);
    		}

    		bodies[i].x_acceleration = x_force / bodies[i].mass;
    		bodies[i].y_acceleration = y_force / bodies[i].mass;

    		for(i = 0; i < num_bodies; i++){
    			bodies[i].x_velocity += bodies[i].x_acceleration;
    			bodies[i].y_velocity += bodies[i].y_acceleration;

    			bodies[i].x_position += bodies[i].x_velocity;
    			bodies[i].y_position += bodies[i].y_velocity;
    		}
    	}

    	time++;
    }

    for(i = 0; i < num_bodies; i++){
    	printBody(&bodies[i]);
    }

    fflush(stdout);

    return 0;
}