#include "Guichet.h"



void chargerTransacts(Compte comptes[], int taille, std::ifstream& fichier)
{
	int tailleTransact{};
	for (;fichier.peek() != '\n' and !fichier.eof();tailleTransact++)
	{
		int temp{};
		fichier >> temp;
		switch (temp)
		{
		case 0:
			comptes[taille].transaction[tailleTransact].type = Operation::depot;
			break;
		case 1:
			comptes[taille].transaction[tailleTransact].type = Operation::retrait;
			break;
		default:
			comptes[taille].transaction[tailleTransact].type = Operation::transfert;

		}
		fichier >> comptes[taille].transaction[tailleTransact].montant;
		fichier >> comptes[taille].transaction[tailleTransact].destinataire;
		fichier >> temp;
		switch (temp)
		{
		case 0:
			comptes[taille].transaction[tailleTransact].affectation = Mouvement::null;
			break;
		case 1:
			comptes[taille].transaction[tailleTransact].affectation = Mouvement::recus;
			break;
		case 2:
			comptes[taille].transaction[tailleTransact].affectation = Mouvement::envoyer;
			break;
		}
		
	}
	comptes[taille].tailleTrasact = tailleTransact;
}

void chargerStatus(Compte comptes[], std::ifstream& fichier, int pos)
{
	int temp{};
	fichier >> temp;
	switch (temp)
	{
	case 0:
		comptes[pos].status = Status::suspendu;
		break;
	case 1:
		comptes[pos].status = Status::utilisateur;
		break;
	default :
		comptes[pos].status = Status::administrateur;
	}
}
int chargerFichier(Compte comptes[], int NB_COMPTES_MAX, std::ifstream& fichier)
{
	int tailleComptes{};
	for (; fichier.peek() != '\0' and !fichier.eof() and tailleComptes < NB_COMPTES_MAX; ++tailleComptes)
	{
		chargerStatus(comptes, fichier, tailleComptes);
		fichier >> comptes[tailleComptes].usager.prenom;
		fichier >> comptes[tailleComptes].usager.nom;
		fichier >> comptes[tailleComptes].compteNum;
		fichier >> comptes[tailleComptes].nip;
		fichier >> comptes[tailleComptes].balance;
		chargerTransacts(comptes, tailleComptes, fichier);
	}
	return tailleComptes; 
}

bool validationCompteNum(Compte utilisateurs[], int destinateur, int destinataire, int taille, int& pos)
{
	if (destinateur == destinataire)
		{}
	else
	{
		for (int i{}; i < taille; i++)
		{
			if (utilisateurs[i].compteNum == destinataire)
			{
				pos = i;
				return true;
			}
		}
	}
	return false;

}



std::string toString(Operation operation)
{
	switch (operation)
	{
	case Operation::depot:
		return "Dépôt";
	case Operation::retrait:
		return "Retrait";
	case Operation::transfert:
		return "Transfert";
	case Operation::historique:
		return "Historique";
	case Operation::quitter:
		return "Quitter";
	default:
		return"Erreur";
			
	}
}
void enregistrerOperation(Transactions& transact, int& taille, Operation type, double montant, size_t destinataire, Mouvement affectation)
{
	switch (type)
	{
	case Operation::depot:
		transact = { type,{montant}, {destinataire}, {affectation} };
		break;
	case Operation::retrait:
		transact = { type,{montant}, {destinataire}, {affectation} };
		break;
	case Operation::transfert:
		transact = { type,{montant}, {destinataire}, {affectation} };
		break;


	}
	taille += 1;
}
void calculerBalance(Transactions transact, double&  balance)
{
	if (transact.type == Operation::depot or (transact.type == Operation::transfert and transact.affectation == Mouvement::recus))
	{
		balance -= transact.montant;
	}
	else
	{
		 balance += transact.montant;
	}
}

int convertirStatus(Status status)
{
	switch (status)
	{
	case Status::suspendu:
		return 0;
	case Status::utilisateur:
		return 1;
	case Status::administrateur:
		return 2;

	}

}

int convertirType(Operation type)
{
	switch (type)
	{
	case Operation::depot:
		return 0;
	case Operation:: retrait:
		return 1;
	case Operation:: transfert:
		return 2;

	}
}

int convertirMouvement(Mouvement affectation)
{
	switch (affectation)
	{
	case Mouvement::null:
		return 0;
	case Mouvement::recus:
		return 1;
	case Mouvement::envoyer:
		return 2;
	}
}



Operation convertirOperation(int choix)
{
	switch (choix)
	{
	case 1:
		return Operation::debannir;
	case 2:
		return Operation::bannir;
	default:
		return Operation::quitter;
	}
}

bool validationCompte(Compte comptes[], int compte, int& pos, int taille)
{
	for (int i{}; i < 10000; i++)
	{
		if (comptes[i].compteNum == compte and comptes[i].status != Status::administrateur)
		{
			pos = i;
			return true;
		}
	}
	return false;
}

void changerStatus(Status& status, Operation operation)
{
	switch (operation)
	{
	case Operation::bannir:
		status = Status::suspendu;
		break;
	default:
		status = Status::utilisateur;
	}

}