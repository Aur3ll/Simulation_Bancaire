#include <iostream>
#include "Guichet.h"
#include <iomanip>

// le compte admin est 121211  Nip : 12121

using namespace std;

static const int NB_COMPTES_MAX{ 10000};
Compte utilisateurs[NB_COMPTES_MAX]{};


void ecrireEntete(string titre, string nom, string session)
{
	for (int i = 0; i < 5; i++)
	{
		cout << setw(25) << setfill(' ') << " ";
		switch (i)
		{
		case 1:
			cout << '*' << right << setw(31) << "Lab  :  " << left << titre << setw(40 - titre.length()) << right << setfill(' ') << '*' << endl;
			break;
		case 2:
			cout << '*' << right << setw(31) << "Étutidant  :  " << left << nom << setw(40 - nom.length()) << right << setfill(' ') << '*' << endl;
			break;
		case 3:
			cout << '*' << right << setw(31) << "Session  :  " << left << session << setw(40 - session.length()) << right << setfill(' ') << '*' << endl;
			break;
		default:
			cout << setw(72) << setfill('#') << '#' << endl;

		}

	}
	cout << endl;
}

bool obtenirCompteNum(int& utilisateur, int taille)
{
	cout << "Entrer votre Numéros de compte: ";
	int entree{};
	cin >> entree;
	cin.clear();
	cin.ignore(100, '\n');
	for (int i{}; i < taille; i++)
	{
		if (entree == utilisateurs[i].compteNum)
		{
			utilisateur = i;
			return true;
		}
	}
	return false;

}

bool obtenirNip(int pos, int taille)
{

	string nip{};
	cout << "Entrer votre nip: ";
	for (int i{}; i < 5; i++)
	{
		nip += _getch();
		cout << '*';

	}
	cout << endl;
	if (nip == utilisateurs[pos].nip)
	{
		return true;
	}
	return false;
}
void indentation(int largeur)
{
	cout << left << setfill(' ') << setw(largeur) << ' ';
}
void affichierligne(int longeur, char c, bool nouvelleligne)
{
	cout << setfill(c) << setw(longeur) << c ;
	if (nouvelleligne)
	{
		cout << endl;
	}
}

void afficherTitre(string choix, char delimitation,  int longeur)
{
	
	cout << delimitation << setfill(' ') << setw(longeur + (choix.length() / 2))  << right << choix << setw(longeur - (choix.length() / 2)-1) << delimitation << endl;
}

void afficherChoix(string choix, char delimitation, int longeur)
{
	cout << delimitation << setfill(' ') << setw(longeur + (choix.length() / 2))  << choix << setw(longeur - (choix.length() / 2) - 1) << right << delimitation << endl;
}


void afficherMenuOperation()
{
	indentation(25);
	affichierligne(40, '=',true);

	for (int i{}; i < 7; i++)
	{
		indentation(25);
		switch (i)
		{
		case 0:
			afficherTitre("Choix des opérations", '|', 20);
			break;
		case 2:
			afficherChoix("   1. Dépôt.", '|', 20);
			break;
		case 3:
			afficherChoix("   2. Retrait.", '|', 20);
			break;
		case 4:
			afficherChoix("   3. Transfert.", '|', 20);
			break;
		case 5: 
			afficherChoix("   4. Historique.", '|', 20);
			break;
		case 6: 
			afficherChoix("   5. Quitter.", '|', 20);
			break;
		default:
			cout << '|';
			affichierligne(38, '=', false);
			cout << '|' << endl;
			
		
		}
	}
	indentation(25);
	affichierligne(40, '=',true);
}
	
	


void affichierBalance(int pos)
{
	cout << fixed << setprecision(2);
	system("cls");
	afficherMenuOperation();
	cout << "Compte : " << utilisateurs[pos].compteNum ;
	indentation(65);
	cout << "Usager : " << utilisateurs[pos].usager.nom << ", " << utilisateurs[pos].usager.prenom << endl ;
	
	cout << "Solde: " << utilisateurs[pos].balance << " $" <<  endl << endl; 

}

bool obtenirOperation(Operation& operation)
{
	for (int i{}; i < 5; i++)
	{

		cout << "choisir une opération: ";
		int choix{};
		cin >> choix;
		cin.clear();
		cin.ignore(100, '\n');
		switch (choix)
		{
		case 1: 
			operation = Operation::depot;
			return true;
		case 2:
			operation = Operation::retrait;
				return true;
		case 3: 
			operation = Operation::transfert;
				return true;
		case 4: 
			operation = Operation::historique;
				return true;
		case 5:
			operation = Operation::quitter;
				return true;
		

		}
		cout << "Entrer le numéro de l'opération." << endl;
	}
	
	return false;
}

bool obtenirDepot(int utilisateur, double& montant )
{
	cout << "Entrer le montant à déposer: ";
	cin >> montant;
	cin.clear();
	cin.ignore(100, '\n');
	if (montant > 0)
	{
		return true;
	}
	return false;	
}

bool obtenirRetrait(int utilisateur, double& montant)
{
	cout << "Entrer le montant à retirer: ";
	cin >> montant;
	cin.clear();
	cin.ignore(100, '\n');
	if(montant > 0 and montant < utilisateurs[utilisateur].balance)
	{
		return true;
	}
	return false;
}


bool obtenirDestinataire(int utilisateur, int taille, int& pos, size_t& destinataire)
{
	cout << "Entrer le numero de compte du destinataire: ";
	cin >> destinataire;
	cin.clear();
	cin.ignore(100, '\n');
	if (destinataire)
	{
		if (validationCompteNum(utilisateurs, utilisateurs[utilisateur].compteNum, destinataire, taille, pos))
		{

			return true;
		}
	}
	return false;
	
}

bool obtenirMontantTransfert(double balance, double & montant)
{
	cout << "Entrer le montant à transferer: ";
	cin >> montant;
	cin.clear();
	cin.ignore(100, '\n');
	if (montant > 0 and montant < balance)
	{
		return true;
	}
	return false;
}

void obtenirTransfert(int utilisateur, int taille)
{
	int posDestinataire{};
	size_t destinataire{};
	while (!obtenirDestinataire(utilisateur, taille, posDestinataire, destinataire))
	{
		cout << "Entrée invalide!" << endl;
	}
	double montant{};
	while(!obtenirMontantTransfert(utilisateurs[utilisateur].balance, montant))
	{
		cout << "Entrée invalide!" << endl;
	}
	utilisateurs[utilisateur].balance -= montant;
	enregistrerOperation(utilisateurs[utilisateur].transaction[utilisateurs[utilisateur].tailleTrasact], utilisateurs[utilisateur].tailleTrasact, Operation::transfert, montant, destinataire, Mouvement::envoyer);
	utilisateurs[posDestinataire].balance += montant;
	enregistrerOperation(utilisateurs[posDestinataire].transaction[utilisateurs[posDestinataire].tailleTrasact], utilisateurs[posDestinataire].tailleTrasact, Operation::transfert, montant, utilisateurs[utilisateur].compteNum, Mouvement::recus);
}

void afficherHistorique(int utilisateur)
{
	string titre{ "Historique des Transactions"};
	cout << endl << setfill(' ') << right << setw(30 + (titre.length() / 2)) << titre << endl;
	affichierligne(69, '_', 1);
	cout << setfill(' ') << left << setw(29) << " Descriptif" << '|' << setw(13) << right << setw(13) << "Retrait |" << setw(13) << "Dépôt |" << setw(13)  <<"Solde |" << endl;
	affichierligne(29, '/', 0);
	cout << '|';
	affichierligne(12, '/', 0);
	cout << '|';
	affichierligne(12, '/', 0);
	cout << '|';
	affichierligne(12, '/', 0);
	cout << '|' << endl;
	cout << setfill(' ') << right;
	double balance{ utilisateurs[utilisateur].balance };
	double balanceRetro{ balance };
	for(int i{ utilisateurs[utilisateur].tailleTrasact -1 }; i >= 0 ; i--)
	{
		
		
		calculerBalance(utilisateurs[utilisateur].transaction[i], balanceRetro);
		
		switch(utilisateurs[utilisateur].transaction[i].type)
		{
		case Operation::transfert:
			cout <<" virement " << (utilisateurs[utilisateur].transaction[i].affectation == Mouvement::envoyer ? "vers " : "de ") << setw((utilisateurs[utilisateur].transaction[i].affectation == Mouvement::envoyer ? 14 : 16 )) << left << utilisateurs[utilisateur].transaction[i].destinataire << '|';
			if (utilisateurs[utilisateur].transaction[i].affectation == Mouvement::envoyer )
			{
				cout << setw(11) << right << utilisateurs[utilisateur].transaction[i].montant << "$|";
				indentation(12);
				cout << '|';
			}
			else
			{
				cout << setw(13) << right << '|' << setw(11) << utilisateurs[utilisateur].transaction[i].montant << "$|";
			}
			break;
		case Operation::depot:
			cout <<" Dépôt compant" << setw(16) << right << '|' << setw(13) << '|' << setw(11) << utilisateurs[utilisateur].transaction[i].montant << "$|";
			break;
		case Operation::retrait:
			cout << " Retrait au guichet"<< setw(11) << right << '|' << setw(11) << utilisateurs[utilisateur].transaction[i].montant << "$|" << setw(13) << '|';
			break;
		}
		cout << setw(11) << right << balance << "$|" << endl;
		balance = balanceRetro;

	}
	affichierligne(69, '"', 1);

	
}

void afficherOptionAdmin()
{
	indentation(25);
	affichierligne(40, '=', true);

	for (int i{}; i < 5; i++)
	{
		indentation(25);
		switch (i)
		{
		case 0:
			afficherTitre("Choix des operations", '|', 20);
			break;
		case 2:
			afficherChoix("   1. Débannir.", '|', 20);
			break;
		case 3:
			afficherChoix("   2. Bannir.", '|', 20);
			break;
		case 4:
			afficherChoix("   3. Quitter.", '|', 20);
			break;
		default:
			cout << '|';
			affichierligne(38, '=', false);
			cout << '|' << endl;


		}
	}
	indentation(25);
	affichierligne(40, '=', true);
}

bool obtenirOperationAdmin(Operation & operation)
{
	cout << "Entrer votre choix: ";
	int choix{};
	cin >> choix;
	cin.clear();
	cin.ignore(100, '\n');
	if (choix >= 1 and choix < 4)
	{
		operation = convertirOperation(choix);
		return true;
	}
	return false;



}

bool obtenirCompte(int& comptePos, int taille)
{
	cout << "Entrer le numéro de compte : ";
	string compte{};
	getline(cin, compte);
	if (compte.size() == 6)
	{
		for (int i{}; i < 6; i++)
		{
			if (!isdigit(compte[i]))
			{
				return false;
			}
			
		}
		if (validationCompte(utilisateurs, stoi(compte), comptePos, taille))
		{
			return true;
		}
	}
	return false;
	
}

void sauvegarderTransactions(Transactions transact[], std::ofstream& fichier, int taille)
{
	for (int i{}; i < taille; i++)
	{
		fichier << convertirType(transact[i].type) << ' ';
		fichier << transact[i].montant << ' ';
		fichier << transact[i].destinataire << ' ';
		fichier << convertirMouvement(transact[i].affectation);
		if (i != taille - 1)
		{
			fichier << ' ';
		}

	}

}

void sauvegarder(Compte utilisateurs[], std::ofstream& fichier, int taille)
{
	fichier << setprecision(3) << fixed;
		for (int i{}; i < taille; i++)
		{
			fichier << convertirStatus(utilisateurs[i].status) << ' ';
			fichier << utilisateurs[i].usager.prenom << ' ';
			fichier << utilisateurs[i].usager.nom << ' ';
			fichier << utilisateurs[i].compteNum << ' ';
			fichier << utilisateurs[i].nip << ' ';
			fichier << utilisateurs[i].balance << ' ';
			sauvegarderTransactions(utilisateurs[i].transaction, fichier, utilisateurs[i].tailleTrasact);
			if (i != taille - 1)
			{
				fichier << '\n';
			}



		}
}


int main()
{
	setlocale(LC_ALL, "");
	ifstream fichier("accounts.guichet");
	if (!fichier)
	{
		cout << "le fichier est invalide!" << endl;
		return -1;
	}
	int taille{ chargerFichier(utilisateurs,NB_COMPTES_MAX,fichier) };
	fichier.close();
	int utilisateur{};
	ecrireEntete("Guichet Bancaire", "Marc-André Couturier", "Hiver 2021");
	for (int i{}; !obtenirCompteNum(utilisateur, taille) and i < 5; i++)
	{

		
		cout << "Le numeros de compte est inexistant!" << endl;
		if (i == 4)
		{
			cout << "appeller au 1-800-224-7737 et il nous fera plaisir de vous aider." << endl;
			return -2;
		}
	}

	for (int i{}; !obtenirNip(utilisateur, taille) and i < 5; i++)
	{
		if (i == 4)
		{
			utilisateurs[utilisateur].status = Status::suspendu;
			break;
		}
		cout << "Nip erroné, il vous reste " << 4 - i << " essaie" << (i < 3 ? 's' : '\0') << '.' << endl;

	}
	if (utilisateurs[utilisateur].status == Status::suspendu)
	{
		ofstream sauvegarde("accounts.guichet");
		sauvegarder(utilisateurs, sauvegarde, taille);

		cout << "Votre compte à été suspendu appeller au 1-800-224-7737 et il nous fera plaisir de vous aider." << endl;
		return -3;
	}
	else if(utilisateurs[utilisateur].status == Status::utilisateur)
	{
		double montant{};
		Operation operation{ };
		do
		{
			system("cls");
			affichierBalance(utilisateur);
			if (!obtenirOperation(operation))
			{
				cout << "Apeller le service à la clientèle" << endl;
				return -5;
			}
			switch (operation)
			{
			case Operation::depot:
				
				while (!obtenirDepot(utilisateur, montant))
				{
					cout << "Entrée invalide" << endl;
				}
				utilisateurs[utilisateur].balance += montant;
				enregistrerOperation(utilisateurs[utilisateur].transaction[utilisateurs[utilisateur].tailleTrasact], utilisateurs[utilisateur].tailleTrasact, operation, montant, -1, Mouvement::null);
				break;
			case Operation::retrait:
				while (!obtenirRetrait(utilisateur, montant))
				{
					cout << "Entrée invalide!" << endl;
				}
				utilisateurs[utilisateur].balance -= montant;
				enregistrerOperation(utilisateurs[utilisateur].transaction[utilisateurs[utilisateur].tailleTrasact], utilisateurs[utilisateur].tailleTrasact, operation, montant, -1, Mouvement::null);
				break;
			case Operation::transfert:
				obtenirTransfert(utilisateur, taille);
				break;
			case Operation::historique:
				afficherHistorique(utilisateur);
				cin.get();
				break;
			case Operation::quitter:
			
				break;

			}



		} while (operation != Operation::quitter);
	}
	else
	{
		Operation operation{};
		do
		{
			system("cls");
			afficherOptionAdmin();
			while (!obtenirOperationAdmin(operation))
			{
				cout << "Entrée invalide!" << endl;
			}
			
			if (operation != Operation::quitter)
			{
				int compte{};
				while (!obtenirCompte(compte, taille))
				{
					cout << "Entrée invalide!" << endl;
				}
				changerStatus(utilisateurs[compte].status, operation);
			
			}

		} while (operation != Operation::quitter);
		
	}
	ofstream sauvegarde("accounts.guichet");
	sauvegarder(utilisateurs, sauvegarde, taille);
	
	return 0;
}