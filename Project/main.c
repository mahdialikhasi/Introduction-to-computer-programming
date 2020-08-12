/*
* Author : Mahdi Alikhasi
* Description: This is a tic tac toe game
* functions::
*	clear:: clear screan after each move. arguman and return is void
*	turn:: choose the move. arguman void. return 1 for computer 0 for guest
*	start:: start the game. clear the page. print the welcome massage. restart the variables. return who start the game and the type of bead.
*	type:: choose the style of bead. return the bead type of guest. 0 for O and 1 for X
*	check:: check if the game is ended or not. return 1 if computer win. return 2 if player win. return 3 if no one wins. return 0 if not ended
*	getmove:: get the next move of player
*	checkmove:: check is the move valid or not. 0 is valid. 1 the number is not valid. 2 is not empty
*	PrintArray:: print the inputed array (specially for status)
*	PrintPage:: print the page with O and X and numbers. arguman the status, the computer type, the player type, the computer score, the player score
*	computerMove:: make a move for computer after each move of player. arguman an type. if type == 1 , that means the first move of game is for computer and computer run a winning sterategy
*	canWinOrLose:: check can we win or Or Lose or not? if we can win or lose, move and return 1. else return 0. Arguman the type. type 1 for check can win. type 2 for check can lose
* Main Variables::
*	starter:: Output of start function. have 2 output. Type of player bead and who start first
*	type_number:: type of player bead. 0 for O and 1 for X
*	turn_start:: who start first? 1 for computer and 0 for player
*	playerScore:: make a score board and store the player score
*	computerScore:: make a score board and store computer score
*	computer_type:: store type of computer bead
*	player_type:: store type of player bead
*	startAgain:: if Y or y, the game starts again
*	name::Store the name of player
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Colorfull text
#define RED   "\x1B[31m"
#define BLU   "\x1B[34m"
#define KCYN  "\x1B[36m"
#define RESET "\x1B[0m"

void clear(void);
int turn(void);
int start(int status[3][3]);
int type(void);
int check(int status[3][3]);
void getmove(int status[3][3]);
int checkmove(int const status[3][3],int);
void printArray(int const status[3][3]);
void printPage(int const status[3][3], char const computer, char const player, int const computerScore, int const playerScore,char const name[15]);
void computerMove(int status[3][3],int first);
int canWinOrLose(int status[3][3],int type);

int main(){
	int status[3][3] = {}; //moshakhas mikonad ke vaziate har noghte az safhe chie. 0 for empty. 1 for computer. 2 for guest.
	int starter = 0, type_number = 0, turn_start = 0, playerScore = 0, computerScore = 0; // first initialization of variables. 
	char computer_type,player_type,startAgain;
	char name[15];
	printf("%s\n","Be Bazi tic tac toe khosh amadid.\nLotfan Ebteda name khod ra vared konid\nLotfan tedad horoofe nametan kamtar az 15 bashad"); //print welcome massage
	int i = 0;
	do{
		scanf("%c", &name[i]);
		i++;
	}while(i < 15 && name[i-1] != '\n');
	char tmp;
	if(i == 15 && name[14] != '\n'){
		do{
			scanf("%c", &tmp);
		}while(tmp != '\n');
	}else
		name[i-1] = '\0';
	do{
		starter = start(status); //start the game. meghdar noe mohre haye karbar ra tooye type zakhire mikone
		computerMove(status,2); //Restart the static variable of function
		type_number = starter % 10; //0 for O and 1 for X. type of player
		turn_start = starter / 10; //who start the game? 1 for computer and 0 for player
		if(type_number == 0){
			player_type = 'O';
			computer_type = 'X';
		}else{
			player_type = 'X';
			computer_type = 'O';
		}
		if(turn_start){
			computerMove(status,1);
		}
		while(!check(status)){
			printPage(status,computer_type,player_type,computerScore,playerScore,name);
			getmove(status);
			if(turn_start)
				computerMove(status,1);
			else
				computerMove(status,0);
		}
		if(check(status) == 2){
			clear();
			playerScore++;
			printPage(status,computer_type,player_type,computerScore,playerScore,name);
			printf(RED "%s%s\n" RESET, name," win");
		}else if(check(status) == 1){
			clear();
			computerScore++;
			printPage(status,computer_type,player_type,computerScore,playerScore,name);
			printf(BLU "%s\n" RESET, "Computer Win");
		}else if(check(status) == 3){
			clear();
			printPage(status,computer_type,player_type,computerScore,playerScore,name);
			printf(KCYN "%s\n" RESET, "No one win");
		}
		printf("%s\n", "Aya mikhahid dobare bazi konid?\nBaraye shoro mojadad Y ra vared konid.");
		scanf(" %c",&startAgain);
		if(startAgain == 'y')
			startAgain = 'Y';
	}while(startAgain == 'Y');
	
	//printArray(status);
	//printf("%d\n", check(status));
	return (EXIT_SUCCESS);
}
void clear(void){
	#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
        system("clear");
    #endif

    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #endif
}
int turn(void){
	srand(time(NULL));
	int a = rand();
	return a % 2;
}
int start(int status[3][3]){
	clear(); //clear the screen
	int i,j;
	for(i = 0; i < 3; i++){ //reset the page
		for (j = 0; j < 3; ++j){
			status[i][j] = 0;
		}
	}
	printf("%s","Ebteda computer tain makone ki aval shoro kone\n");
	int a = turn(); //calculate the turn
	if(a){
		printf("%s\n", "computer shoro mikonad");
	}else{
		printf("%s\n", "shoma shoro mikonid");
	}
	int type_number = type();
	printf("%s\n", "Bazi shoro shod!");
	return (a * 10 + type_number);
}
int type(void){
	printf("%s\n", "Hala entekhab konid doost darid mohre hatoon X bashe ya O ?\nX ya O ra vared konid");
	char type;//get the style of inputs of guest
	int type_number = 2;
	while(type_number == 2){
		scanf(" %c", &type);
		if(type == 'O' || type == 'o'){
			type_number = 0;
			break;
		}else if(type == 'X' || type == 'x'){
			type_number = 1;
			break;
		}
		printf(RED "Error:: " RESET "%s\n", "meghdar na motabar bood.\nX ya O ra vared konid");
	}
	return type_number;
}
void getmove(int status[3][3]){
	printf("%s\n", "Harkat badi khod ra vared konid.\nShomareye khane i ke mikhahid mohretan ra dar an bezarid entekhab konid");
	int move = 0;
	int move_stat;
	do{
		int input = scanf("%d", &move);
		if(input == 1)
			move_stat = checkmove(status, move);
		else{
			move_stat = checkmove(status, 21);
			char tmp;
			scanf(" %c", &tmp);
		}
	}while(move_stat);
	int i = (move - 1) / 3;
	int j = (move - 1) % 3;
	status[i][j] = 2;
}
int checkmove(int const status[3][3], int move){
	if(move > 9 || move < 1){
		printf(RED "Error:: " RESET "%s\n", "Harkate shoma gheyre mojaze.\nYe adade dige vared konid");
		return 1;
	}
	int i = (move - 1) / 3;
	int j = (move - 1) % 3;
	if (status[i][j] != 0){
		printf(RED "Error:: " RESET "%s\n", "Dar in khane nemitooni mohre bezari.\nhamin alan tooye in khunee mohre hast.\nYek khoone ye dige ra entekhab kon.");
		return 2;
	}
	return 0;
}
int check(int status[3][3]){
	int i =0;
	for(i = 0; i< 3; i++){ //check horizonal
		if(status[i][0] == 0 || status[i][1] == 0 || status[i][2] == 0){ //not ended
			continue;
		}
		if(status[i][0] == status[i][1] && status[i][2] == status[i][0]){
			if(status[i][0] == 1)
				return 1;
			else
				return 2;
		}
	}
	for(i = 0; i< 3; i++){ //check vertical
		if(status[0][i] == 0 || status[1][i] == 0 || status[2][i] == 0){ //not ended
			continue;
		}
		if(status[0][i] == status[1][i] && status[2][i] == status[0][i]){
			if(status[0][i] == 1)
				return 1;
			else
				return 2;
		}
	}
	if((status[0][0] == status[1][1]) && (status[0][0] == status[2][2])){
		if (status[0][0] == 1)
			return 1;
		else if(status[0][0] == 2)
			return 2;
	}
	if((status[0][2] == status[1][1]) && (status[1][1] == status[2][0])){
		if (status[1][1] == 1)
			return 1;
		else if(status[1][1] == 2)
			return 2;
	}
	int j = 0;
	for(i = 0; i < 3; i++){
		for(j = 0; j < 3; j++){
			if(status[i][j] == 0)
				return 0;
		}
	}
	return 3;
}
void printArray(int const status[3][3]){
	int i = 0;
	int j = 0;
	for(i = 0;i < 3;i++){
		for(j = 0;j < 3;j++){
			printf("%d,", status[i][j]);
		}
		printf("\n");
	}
}
void printPage(int const status[3][3], char const computer, char const player,int const computerScore, int const playerScore,char const name[15]){
	clear();
	printf(KCYN "%11s%15s %15s\n%11s%15d %15d\n", "Score Board","Computer",name,"",computerScore,playerScore);
	printf(KCYN "%s%c%s\n\n" RESET, "Shoma ", player, " Hastid");
	printf("%s", (status[0][0] == 0) ? RESET : ((status[0][0] == 1) ? BLU : RED));
	printf(" %c " RESET "|",(status[0][0] == 0)? '1' : ((status[0][0] == 1) ? computer : player));
	printf("%s", (status[0][1] == 0) ? RESET : ((status[0][1] == 1) ? BLU : RED));
	printf(" %c " RESET "|",(status[0][1] == 0)? '2' : ((status[0][1] == 1) ? computer : player));
	printf("%s", (status[0][2] == 0) ? RESET : ((status[0][2] == 1) ? BLU : RED));
	printf(" %c " RESET, (status[0][2] == 0)? '3' : ((status[0][2] == 1) ? computer : player));
	printf("%s", "\n---+---+---\n");
	printf("%s", (status[1][0] == 0) ? RESET : ((status[1][0] == 1) ? BLU : RED));
	printf(" %c " RESET "|",(status[1][0] == 0)? '4' : ((status[1][0] == 1) ? computer : player));
	printf("%s", (status[1][1] == 0) ? RESET : ((status[1][1] == 1) ? BLU : RED));
	printf(" %c " RESET "|",(status[1][1] == 0)? '5' : ((status[1][1] == 1) ? computer : player));
	printf("%s", (status[1][2] == 0) ? RESET : ((status[1][2] == 1) ? BLU : RED));
	printf(" %c " RESET, (status[1][2] == 0)? '6' : ((status[1][2] == 1) ? computer : player));
	printf("%s", "\n---+---+---\n");
	printf("%s", (status[2][0] == 0) ? RESET : ((status[2][0] == 1) ? BLU : RED));
	printf(" %c " RESET "|",(status[2][0] == 0)? '7' : ((status[2][0] == 1) ? computer : player));
	printf("%s", (status[2][1] == 0) ? RESET : ((status[2][1] == 1) ? BLU : RED));
	printf(" %c " RESET "|",(status[2][1] == 0)? '8' : ((status[2][1] == 1) ? computer : player));
	printf("%s", (status[2][2] == 0) ? RESET : ((status[2][2] == 1) ? BLU : RED));
	printf(" %c \n" RESET,(status[2][2] == 0)? '9': ((status[2][2] == 1) ? computer : player));
}
void computerMove(int status[3][3], int type){
	static int count = 0; //count player moves.
	static int style = 0;
	static int mode = 0;
	if(type == 1){ //run a winning sterategy. if computer starts the game, he will not lose.
		if(count == 0)
			status[2][2] = 1;
		else if(count == 1){
			if(status[0][2] == 2 || status[0][0] == 2 || status[1][0] == 2 || status[1][2] == 2)
				status[2][0] = 1;
			else if(status[2][0] == 2 || status[2][1] == 2 || status[0][1] == 2)
				status[0][2] = 1;
			else
				status[0][0] = 1;
		}else if(count == 2){
			if(status[2][0] == 1 && status[2][1] == 0)
				status[2][1] = 1;
			else if(status[0][2] == 1 && status[1][2] == 0)
				status[1][2] = 1;
			else if(status[2][0] == 1 && (status[0][2] == 2 || status[1][2] == 2))
				status[0][0] = 1;
			else if(status[2][0] == 1 && (status[0][0] == 2 || status[1][0] == 2))
				status[0][2] = 1;
			else if(status[0][2] == 1 && (status[2][0] == 2 || status[2][1] == 2))
				status[0][0] = 1;
			else if(status[0][2] == 1 && status[0][1] == 2)
				status[2][0] = 1;
			else if(status[1][1] == 2 && status[0][2] == 2)
				status[2][0] = 1;
			else if(status[1][1] == 2 && status[2][0] == 2)
				status[0][2] = 1;
			else if(status[0][1] == 2)
				status[2][1] = 1;
			else if(status[2][1] == 2)
				status[0][1] = 1;
			else if(status[1][0] == 2)
				status[1][2] = 1;
			else if(status[1][2] == 2)
				status[1][0] = 1;
		}else if(count == 3){
			if(status[0][0] == 1 && status[0][2] == 1 && status[0][1] == 0)
				status[0][1] = 1;
			else if(status[0][0] == 1 && status[2][0] == 1 && status[1][0] == 0)
				status[1][0] = 1;
			else if(status[0][2] == 1 && status[2][2] == 1 && status[1][2] == 0)
				status[1][2] = 1;
			else if(status[2][2] == 1 && status[2][0] == 1 && status[2][1] == 0)
				status[2][1] = 1;
			else if((status[0][0] == 1 && status[2][2] == 1 && status[1][1] == 0) || (status[0][2] == 1 && status[2][0] == 1 && status[1][1] == 0))
				status[1][1] = 1;
			else if(status[1][2] == 1 && status[0][2] == 0)
				status[0][2] = 1;
			else if(status[0][0] == 1 && status[1][0] == 1 && status[2][0] == 0)
				status[2][0] = 1;
			else if(status[0][0] == 1 && status[0][1] == 1 && status[0][2] == 0)
				status[0][2] = 1;
			else if(status[2][1] == 1 && status[2][0] == 0)
				status[2][0] = 1;
			else if(status[1][1] == 2){
				if(status[2][1] == 2)
					status[0][1] = 1;
				else if(status[0][2] == 2)
					status[2][0] = 1;
				else if(status[2][0] == 2)
					status[0][2] = 1;
				else if(status[1][2] == 2)
					status[1][0] = 1;
			}
		}else if(count == 4){
			int i = 0;
			int j = 0;
			int done = 0;
			for(i = 0; i< 3; i++){
				for(j = 0; j < 3; j++){
					if(status[i][j] == 0){
						status[i][j] = 1;
						done = 1;
						break;
					}
				}
				if(done)
					break;
			}
		}
		count++;
	}else if(type == 0){ //now it means that the player done the first move. we should try to not lose.
		count++;
		if(count == 1){
			if(status[1][1] == 2){//the player put the first bead in the middle
				status[2][2] = 1;
				mode = 1;
			}else if(status[0][0] == 2 || status[0][2] == 2 || status[2][0] == 2 || status[2][2] == 2){
				status[1][1] = 1;
				mode = 2;
			}else if(status[0][1] == 2 || status[1][2] == 2 || status[2][1] == 2 || status[1][0] == 2){
				status[1][1] = 1;
				mode = 3;
			}
		}else if(count == 2){
			if(mode == 1 && status[0][0] != 2){
				if(status[0][1] == 2){
					status[2][1] = 1;
					style = 4;
				}else if(status[2][1] == 2){
					status[0][1] = 1;
					style = 1;
				}else if(status[1][0] == 2){
					status[1][2] = 1;
					style = 2;
				}else if(status[1][2] == 2){
					status[1][0] = 1;
					style = 3;
				}else if(status[2][0] == 2){
					status[0][2] = 1;
					style = 5;
				}else if(status[0][2] == 2){
					status[2][0] = 1;
					style = 6;
				}
			}else if(mode == 1 && status[0][0] == 2){
				status[2][0] = 1;
				style = 7;
			}else if(mode == 2){
				//Can player win?
				if(canWinOrLose(status,2)){

				}
				//if not, put somewhere else
				else{
					//if player can make 2 way...
					if((status[2][0] == 2 && status[0][1] == 2) || (status[1][0] == 2 && status[0][2] == 2))
						status[0][0] = 1;
					else if((status[0][0] == 2 && status[1][2] == 2) || (status[0][1] == 2 && status[2][2] == 2))
						status[0][2] = 1;
					else if((status[0][2] == 2 && status[2][1] == 2) || (status[2][0] == 2 && status[1][2] == 2))
						status[2][2] = 1;
					else if((status[2][2] == 2 && status[1][0] == 2) ||(status[2][1] == 2 && status[0][0] == 2))
						status[2][0] = 1;
					else if(status[2][1] == 0)
						status[2][1] = 1;
					else
						status[1][2] = 1;
				}
			}else if(mode == 3){
				//Can player win? pretend...
				if(canWinOrLose(status,2)){

				}
				//otherwise
				else if((status[0][1] == 2 && status[1][2] == 2) || (status[0][0] == 2 && status[1][2] == 2) || (status[0][1] == 2 && status[2][2] == 2))
					status[0][2] = 1;
				else if((status[1][2] == 2 && status[2][1] == 2) || (status[0][2] == 2 && status[2][1] == 2) || (status[1][2] == 2 && status[2][0] == 2))
					status[2][2] = 1;
				else if((status[2][1] == 2 && status[1][0] == 2) || (status[2][2] == 2 && status[1][0] == 2) || (status[0][0] == 2 && status[2][1] == 2))
					status[2][0] = 1;
				else if((status[1][0] == 2 && status[0][1] == 2) || (status[1][0] == 2 && status[0][2] == 2) || (status[2][0] == 2 && status[0][1] == 2))
					status[0][0] = 1;
				else if(status[0][1] == 2)
					status[1][0] = 1;
				else if(status[1][0] == 2)
					status[0][1] = 1;
			}
		}else if(count == 3){
			if(mode == 1){
				//Can computer win??
				if(canWinOrLose(status,1)){

				}
				//if not what to do?
				else if(style == 1){
					if(status[2][0] == 2)
						status[0][2] = 1;
					else if(status[0][2] == 2)
						status[2][0] = 1;
					else if(status[1][0] == 2)
						status[1][2] = 1;
					else if(status[1][2] == 2)
						status[1][0] = 1;
					else if(status[0][0] == 2)
						status[1][2] = 1;
				}else if(style == 2){
					status[2][0] = 1;
				}else if(style == 3){
					if(status[2][1] == 2)
						status[0][1] = 1;
					else if(status[0][1] == 2)
						status[2][1] = 1;
					else if(status[2][0] == 2)
						status[0][2] = 1;
					else if(status[0][2] == 2)
						status[2][0] = 1;
					else
						status[2][1] = 1;
				}else if(style == 4){
					status[0][2] = 1;
				}else if(style == 5){
					status[1][0] = 1;
				}else if(style == 6){
					status[0][1] = 1;
				}else if(style == 7){
					status[0][1] = 1;
				}
			}else if(mode == 2){
				//can we win??
				if(canWinOrLose(status,1)){

				}
				//if not, can player win?
				else if(canWinOrLose(status,2)){

				}
				//Otherwise
				else{
					style = 1;
					//can we make a winning situation? 
					if(status[0][0] == 0 && status[2][2] == 0){
						if((status[0][2] == 2 && status[1][0] == 2) || (status[0][1] == 2 && status[2][0] == 2))
							status[0][0] = 1;
						else if((status[2][0] == 2 && status[1][2] == 2) || (status[0][2] == 2 && status[2][1] == 2))
							status[2][2] = 1;
						else
							status[2][2] = 1;
					}else if(status[0][2] == 0 && status[2][0] == 0){
						if((status[0][1] == 2 && status[2][2] == 2) || (status[0][0] == 2 && status[1][2] == 2))
							status[0][2] = 1;
						else if((status[0][0] == 2 && status[2][1] == 2) || (status[1][2] == 2 && status[2][2] == 2))
							status[2][0] = 1;
						else
							status[2][0] = 1;
					}else if(status[0][1] == 0)
						status[0][1] = 1;
					else if(status[1][2] == 0)
						status[1][2] = 1;
					else if(status[2][1] == 0)
						status[2][1] = 1;
					else if(status[1][0] == 0)
						status[1][0] = 1;
				}
			}else if(mode == 3){
				//Can computer win?
				if(canWinOrLose(status,1)){

				}
				//if not, Can player win?
				else if(canWinOrLose(status,2)){

				}
				//if not, put somewhere else
				else{
					if((status[0][1] == 2 && status[1][2] == 2 && status[2][1] == 2) || (status[1][2] == 2 && status[2][1] == 2 && status[1][0] == 2))
						status[2][2] = 1;
					else if((status[2][1] == 2 && status[1][0] == 2 && status[0][1] == 2) || (status[1][0] == 2 && status[0][1] == 2 && status[1][2] == 2))
						status[0][0] = 1;
					//if player can make 2 way...
					else if(((status[2][0] == 2 && status[0][1] == 2) || (status[1][0] == 2 && status[0][2] == 2)) && (status[0][0] == 0))
						status[0][0] = 1;
					else if(((status[0][0] == 2 && status[1][2] == 2) || (status[0][1] == 2 && status[2][2] == 2)) && (status[0][2] == 0))
						status[0][2] = 1;
					else if(((status[0][2] == 2 && status[2][1] == 2) || (status[2][0] == 2 && status[1][2] == 2)) && (status[2][2] == 0))
						status[2][2] = 1;
					else if(((status[2][2] == 2 && status[1][0] == 2) || (status[2][1] == 2 && status[0][0] == 2)) && (status[2][0] == 0))
						status[2][0] = 1;
				}
			}
		}else if(count == 4){
			if(mode == 1){
				//Can we win?
				if(canWinOrLose(status,1)){

				}else
				if(style == 7){
					if(status[1][0] == 2)
						status[1][2] = 1;
					else if(status[1][2] == 2)
						status[1][0] = 1;
					else
						status[1][0] = 1;
				}else if(style == 6){
					if(status[1][0] == 2)
						status[1][2] = 1;
					else if(status[1][2] == 2)
						status[1][0] = 1;
					else
						status[1][0] = 1;
				}else if(style == 5){
					if(status[0][1] == 2)
						status[2][1] = 1;
					else if(status[2][1] == 2)
						status[0][1] = 1;
					else
						status[0][1] = 1;
				}else if(style == 4){
					if(status[1][2] == 0)
						status[1][2] = 1;
					else
						status[1][0] = 1;
				}else if(style == 2){
					if(status[2][1] == 0)
						status[2][1] = 1;
					else
						status[0][1] = 1;
				}else if(style == 3 || style == 1){
					//can we win?
					if(status[0][2] == 0 && status[1][2] == 1)
						status[0][2] = 1;
					else if(status[2][1] == 1 && status[2][0] == 0)
						status[2][0] = 1;
					else if(status[0][2] == 2 && status[2][0] == 0)
						status[2][0] = 1;
					else if(status[0][2] == 0 && status[2][0] == 2)
						status[0][2] = 1;
					else if(status[0][1] == 2 && status[2][1] == 0)
						status[2][1] = 1;
					else if(status[0][1] == 0 && status[2][1] == 2)
						status[0][1] = 1;
					else if(status[1][0] == 2 && status[1][2] == 0)
						status[1][2] = 1;
					else if(status[1][2] == 0 && status[1][2] == 2)
						status[1][2] = 1;
				}
			}else if(mode == 2){
				//Can we win?
				if(canWinOrLose(status,1)){

				}
				//if not, can player win?
				else if(canWinOrLose(status,2)){

				}//otherwise
				else{
					if(status[0][0] == 0)
						status[0][0] = 1;
					else if(status[2][2] == 0)
						status[2][2] = 1;
					else if(status[0][2] == 0)
						status[0][2] = 1;
					else if(status[2][0] == 0)
						status[2][0] = 1;
				}
			}else if(mode == 3){
				//Can computer win?
				if(canWinOrLose(status,1)){

				}
				//if not, Can player win?
				else if(canWinOrLose(status,2)){
					
				}
				//otherwise put somewhere else
				else{
					int i = 0;
					int j = 0;
					int done = 0;
					for(i = 0; i < 3; i++){
						for(j = 0; j < 3; j++){
							if(status[i][j] == 0){
								status[i][j] = 1;
								done = 1;
								break;
							}
						}
						if(done)
							break;
					}
				}
			}
		}
	}else if(type == 2){
		count = 0;
		style = 0;
		mode = 0;
		return;
	}
}
int canWinOrLose(int status[3][3],int type){
	//Can computer win?
	//Orib
	if(status[0][0] == type && status[2][2] == 0 && status[1][1] == type)
		status[2][2] = 1;
	else if(status[2][2] == type && status[0][0] == 0 && status[1][1] == type)
		status[0][0] = 1;
	else if(status[2][2] == type && status[0][0] == type && status[1][1] == 0)
		status[1][1] = 1;
	else if(status[0][2] == type && status[2][0] == 0 && status[1][1] == type)
		status[2][0] = 1;
	else if(status[2][0] == type && status[0][2] == 0 && status[1][1] == type)
		status[0][2] = 1;
	else if(status[2][0] == type && status[0][2] == type && status[1][1] == 0)
		status[1][1] = 1;
	//Plus
	else if(status[1][0] == type && status[1][2] == 0 && status[1][1] == type)
		status[1][2] = 1;
	else if(status[1][2] == type && status[1][0] == 0 && status[1][1] == type)
		status[1][0] = 1;
	else if(status[1][2] == type && status[1][0] == 1 && status[1][1] == 0)
		status[1][1] = 1;
	else if(status[0][1] == type && status[2][1] == 0 && status[1][1] == type)
		status[2][1] = 1;
	else if(status[2][1] == type && status[0][1] == 0 && status[1][1] == type)
		status[0][1] = 1;
	else if(status[2][1] == type && status[0][1] == type && status[1][1] == 0)
		status[1][1] = 1;
	//
	else if(status[0][0] == type && status[0][2] == type && status[0][1] == 0)
		status[0][1] = 1;
	else if(status[0][2] == type && status[2][2] == type && status[1][2] == 0)
		status[1][2] = 1;
	else if(status[2][2] == type && status[2][0] == type && status[2][1] == 0)
		status[2][1] = 1;
	else if(status[2][0] == type && status[0][0] == type && status[1][0] == 0)
		status[1][0] = 1;
	//
	else if(status[0][0] == 0 && ((status[0][1] == type && status[0][2] == type) || (status[1][0] == type && status[2][0] == type)))
		status[0][0] = 1;
	else if(status[0][2] == 0 && ((status[0][1] == type && status[0][0] == type) || (status[1][2] == type && status[2][2] == type)))
		status[0][2] = 1;
	else if(status[2][2] == 0 && ((status[0][2] == type && status[1][2] == type) || (status[2][0] == type && status[2][1] == type)))
		status[2][2] = 1;
	else if(status[2][0] == 0 && ((status[0][0] == type && status[1][0] == type) || (status[2][1] == type && status[2][2] == type)))
		status[2][0] = 1;
	else
		return 0;
	return 1;
}