#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool initialze(char* startCmd[],int *initialze_x_ptr,int *initialze_y_ptr,int *face_ptr) {          //function for getting starting point of robot
	char*ptr;																					    //return 0 if the command is invalid. Otherwise, return 1
	char*x;
	char*y;
	char*direct;

	ptr = strtok(startCmd, " ");
	if ((ptr == NULL)||(strcmp(ptr, "PLACE")!=0)){       //PLACE command
		return 0;										 //if the first command is not PLACE or is NULL, return 0					
	}
	else {
		x= strtok(NULL, ",");                            //processing the location that user had entered
		if ((x == NULL)) {								 //if x is NULL, return 0               
			return 0;
		}
		else
		{
			*initialze_x_ptr = atoi(x);
			if (*initialze_x_ptr < 0 || *initialze_x_ptr>5) {  //if out of bound, return 0
				return 0;
			}
		}
		y = strtok(NULL, ",");
		if ((y == NULL)) {       //check y
			return 0;
		}
		else
		{
			*initialze_y_ptr = atoi(y);
			if (*initialze_y_ptr < 0 || *initialze_y_ptr>5) {
				return 0;
			}
		}
		direct = strtok(NULL, ",");
		if ((direct == NULL)) {       //check face
			return 0;
		}
		else {
			if (strcmp(direct, "NORTH") == 0){
				*face_ptr = 1;                          //transform the string in to face code: NORTH:1,EAST:2,SOUTH:3,WEST:4
				return 1;
			}
			else if (strcmp(direct, "EAST") == 0) {
				*face_ptr = 2;
				return 1;
			}
			else if (strcmp(direct, "SOUTH") == 0) {
				*face_ptr = 3;
				return 1;
			}
			else if (strcmp(direct, "WEST") == 0) {
				*face_ptr = 4;
				return 1;
			}
			else {                                       
				return 0;
			}

		}
	}
}

int main() {
	char startCmd[20];                                    //the command should be PLACE in order to start the program
	char cmd[20];										  //the command to control the toy robot, including REPORT to show the robot location.
	char place[6] = "";
	int initialze_x;									  //location on x axis
	int initialze_y;									  //location on y axis				
	int initialze_face;                                   //the direction of robot.(NORTH:1,EAST:2,SOUTH:3,WEST:4)
	char final_face[10];                                  //direction of robot in string
	char cmd_2[20];                                       //copy string
	bool a;
	do {
		printf("Please place the robot\n");                        //keep asking user to enter the PLACE command 
		gets(startCmd);
		a = initialze(startCmd, &initialze_x, &initialze_y,&initialze_face);   //process the command and get the starting point of robot
	} while (a==0);

	printf("Please enter commands:\n");
	gets(cmd);                                                               //getting commmand from user 
	while (strcmp(cmd, "REPORT") != 0) {								     //keeping aksing for command until receiving REPORT command
		if (strcmp(cmd, "MOVE")==0) {									     //move command
			switch (initialze_face) {
				case 1:                                                      // if the face code is 1:NORTH
					initialze_y += 1;                                        // add y axis
					if (initialze_y > 7) {                                   // if out of bound
						initialze_y = 5;
						printf("Out of bound!!!\n");
					}
					break;
				case 2:
					initialze_x += 1;
					if (initialze_x > 7) {
						initialze_x = 5;
						printf("Out of bound!!!\n");
					}
					break;
				case 3:
					initialze_y -= 1;
					if (initialze_y < 0) {
						initialze_y = 0;
						printf("Out of bound!!!\n");
					}
					break;
				case 4:
					initialze_x -= 1;
					if (initialze_x < 0) {
						initialze_x = 0;
						printf("Out of bound!!!\n");
					}
					break;
			}
		}
		else if (strcmp(cmd, "LEFT")==0) {                     // turn left
			switch (initialze_face) {
			case 1:                          
				initialze_face += 3;                           //manipulate the face code to change the direction
				break;
			case 2:
				initialze_face -= 1;
				break;
			case 3:
				initialze_face -= 1;
				break;
			case 4:
				initialze_face -= 1;
				break;
			}
		}
		else if (strcmp(cmd, "RIGHT")==0) {
			switch (initialze_face) {
			case 1:
				initialze_face += 1;
				break;
			case 2:
				initialze_face += 1;
				break;
			case 3:
				initialze_face += 1;
				break;
			case 4:
				initialze_face -= 3;
				break;
			}
		}
		else if (strcmp(cmd, "REPORT")==0) {                //show the current location and end up the program
		}
		else
		{
			strcpy(cmd_2, cmd);                             
			strtok(cmd_2, " ");
			if (strcmp(cmd_2, "PLACE")==0) {                 //if receiveing the PLACE command
				initialze(cmd, &initialze_x, &initialze_y, &initialze_face);    //place the robot to the new location 
			}
			else {
				printf("invalid input!\n");                  //warning message for invalid input
			}
		}
		gets(cmd);
	}
	switch (initialze_face) {
		case 1:                                             //decode the face code to show the resulte on report
			strcpy(final_face, "NORTH");
			break;
		case 2:
			strcpy(final_face, "EAST");
			break;
		case 3:
			strcpy(final_face, "SOUTH");
			break;
		case 4:
			strcpy(final_face, "WEST");
			break;
	}
	printf("OUTPUT: %d,%d,%s\n", initialze_x, initialze_y, final_face);     //print out the result

	system("pause");
	return 0;
}
