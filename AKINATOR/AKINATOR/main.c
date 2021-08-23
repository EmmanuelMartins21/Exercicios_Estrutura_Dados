#include<locale.h>
#include "ABD.h"

int main() 
{
	setlocale(LC_ALL, "PORTUGUESE");
	system("mode con: cols=100 lines=25");
	
	bool b = true;
	TREE *abd = createTree();
	
	while(b){
		system("cls");
		b = menu(abd);
	}
	
	system("cls");
	printf("\n\n\t\t\t\tGOOD BYE! :)\n\n");
	return 0;
}
