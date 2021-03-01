#include <iostream>
#include <stdio.h>
#include <math.h>
#include "STOSCHAR.h"
#include "STOSNUM.h"

#define DOT '.'

void skipSpaces();
double getNum();
int isDigit(char c);
char getOper();
int IsOper(char oper);
int Prior(char oper);
double calc(double arg1, double arg2, char cOperator);
double ONP();
using namespace std;

int main(int argc, char* argv[])
{
	printf("Enter :");
	printf("\n\n %g", ONP());

	return 0;
}

//-----------------------
void skipSpaces()
{
	char c;
	while( ( c=getchar() ) == ' ' );
	ungetc( c, stdin );
}
double getNum()
{
	char c;
	double num = 0;
	int sign = 0;
	skipSpaces();

	if((c = getchar()) == '+' || c == '-')
	{
		if(c == '-')
			sign = -1;
	}
	else 
		ungetc(c, stdin);
	
	while(isDigit(c = getchar()))
		num = num * 10 + (c - '0');
	
	if(c == DOT)
	{
		double s = 0.1;
		while(isDigit(c = getchar()))
		{
			num += (c - '0') * s;
			s *= 0.1;
		}
	}
	ungetc(c, stdin);
	return (sign) ? -num : num;
}
int isDigit(char c)
{
	return (c >= '0') && (c <= '9');
}
char getOper()
{
	skipSpaces();
	return getchar();
}
int Prior(char oper)
{
	switch (oper)
	{
	case '(':return 1;
	case '+':
	case '-':
	case ')':return 2;
	case '*':
	case '%':
	case '/':return 3;
	case '^':return 4;
	}
	return 0;
}
int IsOper(char oper)
{

	switch (oper)
	{
	case '+':
	case '-':
	case '*':
	case '%':
	case '^':
	case ')':
	case '(':
	case '/':return 1;
	}
	return 0;
}
double ONP()
{
	char c;
	StackItem* pStack = NULL;
	makeEmptyStack(&pStack);
	StackItemD* pStacknum = NULL;
	makeEmptyStackD(&pStacknum);
	
	/* sprawdzam co jest na poczatku ( lub - +
	moze pojawic sie dalej liczba lub nawias ,jesli nawias to na stos daje -1 i * , 
	gdy liczba licze liczbe i wstawiam na stos , jesli na poczatku pojawi sie sam nawias ignoruje go
	wrzucajac go na strumien wejscia */
	char d = getOper();
	if(d == '-' || d == '+')
	{
		if(( c=getOper() ) == '(')
		{
			pushD(&pStacknum, (d == '-') ? -1 : 1);
			push(&pStack, '*');//dodaje * i -1 lub 1 do stosu 
			ungetc(c, stdin); // przywracam nawias , zeby w petli go odczytac i zobaczyc co jest nastepne
		}
		else
		{
			ungetc(c, stdin); // c moglo byc liczba 
			if(d == '-')
				ungetc(d, stdin); // + nie jest wazny przy liczeniu liczby , tylko minus 
			pushD(&pStacknum, getNum());
		}
	}
	else if(d != '(')
	{
		ungetc(d, stdin); //d moglo byc liczba wiec ja przywracam 
		pushD(&pStacknum, getNum());
	}
	else 
		ungetc(d, stdin);// nawias przywracam i dodaje do stosu w petli 

	while(IsOper(c = getOper()))
	{
		/*w momencie trafienia nawiasu otwierajacego wlozyc go na stos i przejsc dalej tzn znalezc kolejna liczbe i operator  ,
		gdy trafie na nawias zamnkniety wyrzucam wszytko z stosu i licze wynik */
		if(c == '(')
		{
			push(&pStack, c);
			d = getOper();
			if(d == '-' || d == '+')
			{
				if((c = getOper()) == '(')
				{
					pushD(&pStacknum, (d == '-') ? -1 : 1);
					push(&pStack, '*');
					ungetc(c, stdin); // przywracam nawias zeby przy nastepnym przejsciu petli wtedy go dodac do stosu 
				}
				else
				{
					ungetc(c, stdin);      // c mogla byc liczba wiec ja przywracam 
					if(d != '+')ungetc(d, stdin);
					pushD(&pStacknum, getNum());
				}
			}
			else if(d != '(')   
			{
				ungetc(d, stdin);    // d mogla byc liczba wiec ja przywracam 
				pushD(&pStacknum, getNum());
			}
			else 
				ungetc(d, stdin);// w przypadku wiecej niz jednego na raz ( przechodze dalej 
		}
		else if(c == ')')
		{
			while( ( c=pop(&pStack) ) != '(')
			{
				double x = popD(&pStacknum);
				pushD(&pStacknum, calc(popD(&pStacknum), x, c));
			}
			//ominiecie ( 
		}
		else //bez nawiasow 
		{
			/*licze wynik w przypadku gdy trafie operator o mniejszym priorytecie od top stosu,
			robie to dopoki na stosie nie bedzie operatora o mniejszym priorytecie ,
			wynik licze przez uzywanie stosu i funkcji calc ,
			w tym przypadku zawsze bede mial przynajmniej dwie liczby na stosie
			i moge obejsc sie bez dodatkowych warunkow  */
			while(Prior(c) <= Prior(top(pStack)))
			{
				double x = popD(&pStacknum);
				pushD(&pStacknum, calc(popD(&pStacknum), x, pop(&pStack)));
			}
			d = getOper();
			ungetc(d, stdin);
			if((d != '('))          // w razie wystapienia nawiasu po operatorze nie szukac liczby tylko przejsc dalej  
			{
				pushD(&pStacknum, getNum());
			}
			push(&pStack, c);
		}
	}
	while(!isEmpty(pStack)) /* to co zostaje na obu stosach licze do momentu gdy nic nie zostanie */
	{
		double x = popD(&pStacknum);
		pushD(&pStacknum, calc(popD(&pStacknum), x, pop(&pStack)));
	}
	return popD(&pStacknum);
}

double calc(double arg1, double arg2, char cOperator)
{
	switch (cOperator)
	{
	case '+': return arg1 + arg2;
	case '-': return arg1 - arg2;
	case '*': return arg1 * arg2;
	case '/': if (fabs(arg2) > 1e-14) return arg1 / arg2;
		cout << "Error: division by 0!!\n";
		break;
	case '^': return pow(arg1, arg2);
	}
	return 0;
}
