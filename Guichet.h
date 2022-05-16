#pragma once
#include <fstream>
#include <string>
#include <conio.h>


enum class Operation
{
	depot,
	retrait,
	transfert,
	historique,
	bannir,
	debannir,
	quitter

};
enum class Mouvement
{
	null,
	recus,
	envoyer
};
enum class Status
{
	suspendu,
	utilisateur,
	administrateur
};

struct Usager
{
	std::string nom{};
	std::string prenom{};
};

struct Transactions
{
	
	Operation type{};
	double montant{};
	size_t destinataire{};
	Mouvement affectation{};

};

struct Compte
{
	Status status{};
	static const int CAPACITE{ 300 };
	int compteNum{};
	std::string nip{};
	double balance{};
	Usager usager{};
	Transactions transaction[CAPACITE]{};
	int tailleTrasact{};

};

void chargerTransacts(Compte comptes[], int taille, std::ifstream& fichier);
int chargerFichier(Compte comptes[], int NB_COMPTES_MAX, std::ifstream& fichier);
void chargerStatus(Compte comptes[], std::ifstream& fichier, int pos);
bool validationCompteNum(Compte utilisateurs[], int destinateur, int destinataire, int taille, int& pos);
double retroCalculerBalance(Transactions operations[], int taille, double balance);
std::string toString(Operation operation);
void calculerBalance(Transactions transact, double & balance);
void enregistrerOperation(Transactions& transact, int& taille, Operation type, double montant, size_t destinataire, Mouvement affectation);
int convertirStatus(Status status);
int convertirMouvement(Mouvement affectation);
Operation convertirOperation(int choix);
bool validationCompte(Compte comptes[], int compte, int& pos, int taille);
void changerStatus(Status& status, Operation operation);
int convertirType(Operation type);
