#include "Century.h"

int main() {

	int choice, players;

	try {
		cout << "Choose from following\n";
		cout << "\t\t\t\t1. Start Game\n";
		cout << "\t\t\t\t2. Save Game\n";
		cout << "\t\t\t\t<press any key to exit>\n";

		cout << "\n\nYour choice <1 - 3>\t:\t";
		cin >> choice;



		if (choice == 1) {
			system("cls");
			cout << "---------------------------------------------In Game--------------------------------------------------\n";


			Game G;

			G.play();
		}
	}
	catch (exception ex) {
		cout << ex.what() << endl;
	}

}