#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<ctype.h>
void main()
{
	char plain[10],cipher[10];
	int i=0,l=0;
	int key;
	scanf("%s",plain);
	scanf("%d",&key);
	l=strlen(plain);
	printf("C.T: ");
	for(i=0;i<l;i++)
	{
		cipher[i]=plain[i]+key;
		if(isupper(plain[i])&&(cipher[i]>'Z'))
		cipher[i]=cipher[i]-26;
		if(islower(plain[i])&&(cipher[i]>'z'))
		cipher[i]=cipher[i]-26;
		printf("%c",cipher[i]);
	}
	printf("\nafter decryption\n");
	printf("P.T :");
	for(i=0;i<l;i++)
	{
		plain[i]=cipher[i]-key;
		if(isupper(cipher[i])&&(plain[i]<'A'))
		plain[i]=plain[i]+26;
		if(islower(cipher[i])&&(plain[i]<'a'))
		plain[i]=plain[i]+26;
		printf("%c",plain[i]);
	}
	getch();
}