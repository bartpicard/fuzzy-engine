#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <memory>

namespace fuzzy {
	typedef std::string Objet;

	enum VarType : int {
		VECTOR,
		TRAPEZE,
		GAUSSIAN
	};
	
	/* ----- Classe LingVar -----
	LingVar représente une variable linguistique floue.
	Celle-ci pouvant être représentée par différent types de données
	(vecteur, trapéze, gaussienne, etc.), l'accès à la valeur d'appartenance
	se fera via une méthode et non un attribut. 
	*/
	class LingVar {
	public:
		std::string 	name;
		std::string 	description;
		VarType 			var_type;
	private:	
		std::vector<float> 	vec_keys;	
		std::vector<float> 	vec_values;

	public:
		LingVar();
		LingVar(std::string n, std::string d, VarType vt);
		LingVar(std::string n, std::string d, std::vector<float> vk, std::vector<float> vv);
		~LingVar();
		float getMembershipValue(float var_val);
	};

	class Fait;
	class Regle {
	public:
		std::string 																nom;
		std::vector<std::pair<Fait, std::shared_ptr<LingVar> > > 	prem;
		std::pair<std::shared_ptr<Fait>, std::shared_ptr<LingVar> >	concl;
		bool 																			flou;
		float 																		coeff;

		Regle(std::string n, std::vector<std::pair<std::string, std::string> > p, std::pair<std::string, std::string> c, bool f, float cf);
		~Regle();
	};

	
	class BaseRegles {
	private:
		std::map<std::string, Regle> 	data;

	public: 
		BaseRegles();
		BaseRegles(std::vector<Regle> regles);
		BaseRegles(const BaseRegles& br);
		BaseRegles& operator=(const BaseRegles& br);
		BaseRegles(BaseRegles&& br);
		BaseRegles& operator=(BaseRegles&& br);
		~BaseRegles();

		void 	addRegles(std::vector<Regle> regles);
		void 	rmRegle(std::string regle);
		Regle get(const std::string& nom) const;
		Regle operator()(const std::string& nom) const;
		std::map<std::string, Regle> getData() const; 
		// std::ostream& operator<<(std::ostream& os, const BaseRegles& br);	
	};


	class Fait {
	public:
		std::string 				nom;
		bool 					flou;
		std::vector<std::shared_ptr<Regle> > 	prem;
		std::vector<std::shared_ptr<Regle> > 	concl;
		std::vector<std::shared_ptr<Regle> > 	metaprem;
		bool 					eval;
		float 					coeff;
		std::string 			        texte;

		Fait(std::string n, bool f, bool e, float c, std::string t);
		~Fait();
	};

	class BaseFaits {
	private:
		std::map<std::string, Fait> data;

	public:
		BaseFaits();
		BaseFaits(std::vector<Fait> faits);
		BaseFaits(const BaseFaits& br);
		BaseFaits& operator=(const BaseFaits& br);
		BaseFaits(BaseRegles&& br);
		BaseFaits& operator=(BaseRegles&& br);
		~BaseFaits();

		void addFaits(std::vector<Fait> faits);
		void rmFait(std::string fait);
		Fait get(const std::string& fait) const;
		Fait operator()(const std::string& fait) const;
		std::map<std::string, Fait> getData() const; 
		// std::ostream& operator<<(std::ostream& os, const BaseFaits& c);	
	};
}
