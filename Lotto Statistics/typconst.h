#pragma once

#define MAX_VALUE_BETS 49

#define MAX_BETS 6 
#define ALLOC_PLAYER 4 
#define ALLOC_BET 2 

#define MAX_NAME 32
#define PESEL_LENGTH 11

#define CLIENT_LENGTH 16
#define BANK_LENGTH 8
#define CONTROL_LENGTH 2
#define LOCATION_LENGTH 2

#define BRANCH_LENGTH 3
#define BANKCODE_LENGTH 4

typedef enum { MALE, FEMALE } sexType;
typedef enum { MON=1 , TUE, WED, THU, FRI, SAT, SUN=0 }weekDay;
typedef enum { JAN=1, FEB, MAR, APR=8, MAY, JUN, JUL,AUG, SEP, OCT, NOV, DEC }month;

typedef struct 
{
	int day;
	month month;
	int year;
	weekDay week_day;
}date;

typedef struct                      
{
	char country[ LOCATION_LENGTH ];	//PL
	char control_sum[ CONTROL_LENGTH ]; //61
	char bank[ BANK_LENGTH ];			//12340011
	char client[ CLIENT_LENGTH ];		//0011000012300678
}ibanInfo;

typedef struct                      
{
	char bank[ BANKCODE_LENGTH ];	 //BPHK
	char country[ LOCATION_LENGTH ]; //PL
	char location[ LOCATION_LENGTH ];//PK
	char branch[ BRANCH_LENGTH ];	 //XXX
}swiftInfo;

typedef struct
{
	swiftInfo swift;//BPHK PL PK XXX
	ibanInfo iban;  //PL 61 12340011 0011000012300678
}bankInfo;

typedef struct
{
	int min;
	int hour;
}Time;

typedef struct
{
	char name_first[ MAX_NAME ];
	char name_last[ MAX_NAME ];
	sexType sex;
	bankInfo bank_info;
	Time time;
	date date;
	char PESEL[ PESEL_LENGTH ];
	int** bets;
	int no_bets;
}player;
