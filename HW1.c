#include<stdio.h>
#include<conio.h>
char UpperCase[26][10] = {"Alpha","Bravo","China","Delta","Echo","Foxtrot",
			"Golf","Hotel","India","Juliet","Kilo","Lima","Mary","November",
			"Oscar","Paper","Quebec","Research","Sierra","Tango","Uniform",
			"Victor","Whisky","X-ray","Yankee","Zulu"};
char LowerCase[26][10] = {"alpha","bravo","china","delta","echo","foxtrot",
			"golf","hotel","india","juliet","kilo","lima","mary","november",
			"oscar","paper","quebec","research","sierra","tango","uniform",
			"victor","whisky","x-ray","yankee","zulu"};
char Number[10][10] = {"zero","First","Second","Third","Fourth","Fifth",
			"Sixth","Seventh","Eighth","Ninth"};
int main()
{
	char c;
	while ((c = getch()) != '?')
	{
		if (c >= '0' && c <= '9')
			printf("%s\n", Number[c - '0']);
		else if (c >= 'A' && c <= 'Z')
			printf("%s\n", UpperCase[c - 'A']);
		else if (c >= 'a' && c <= 'z')
			printf("%s\n", LowerCase[c - 'a']);
		else
			printf("*\n");
	}
	return 0;
} 
