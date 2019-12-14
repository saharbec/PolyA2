#include "Polynomial.h"
#include <iomanip>
#include <iostream>
#include "Monomial.h"

using namespace std;

Polynomial::Polynomial() {
	head = NULL;
	//head = new Monomial(0);
	//head->setNext(NULL);
	maxDegree = 0;
}

Polynomial::~Polynomial() {
	Monomial* ptr = head, *toDelete = head;
	while (ptr) {
		ptr = ptr->getNext();
		delete toDelete;
		toDelete = ptr;
	}
}

istream& operator >>(istream& in, Polynomial& p) {
	p.deletePolynomialNodes();
	char flag = '.';
	int counter = 0;
	while (flag != ',') {
		counter++;
		cout << endl << "Insert Monomial number " << counter << ": " << endl;
		Monomial m(0);
		cin >> m;
		p.add(m);
		cout << endl << "Enter ',' to stop or another character to proceed: ";
		cin >> flag;
	}
	return in;
}

ostream& operator<< (ostream& out, const Polynomial& p) {
	p.print();
	cout << endl;
	return out;
}

const Polynomial& Polynomial::operator=(const Polynomial& other) {
	if (this->head->getNext() != NULL) { // if this poly isn't empty then clear its monomials
		this->deletePolynomialNodes();
	}
	if (other.head->getNext() != NULL) { // if other poly isn't empty
		Monomial* ptr = head;
		Monomial* otherPtr = other.head->getNext();
		while (otherPtr != NULL) {
			ptr->setNext(new Monomial(otherPtr->getCoefficient(), otherPtr->getDegree()));
			otherPtr = otherPtr->getNext();
			ptr = ptr->getNext();
		}
		ptr->setNext(NULL);
	}
	return *this;
}


Polynomial& Polynomial::operator+(const Polynomial& other) const {
	Monomial* polyPtr = head;
	Polynomial* newPoly = new Polynomial();
	while (polyPtr != NULL) {
		newPoly->add(*polyPtr);
		polyPtr = polyPtr->getNext();
	}
	polyPtr = other.head;
	while (polyPtr != NULL) {
		newPoly->add(*polyPtr);
		polyPtr = polyPtr->getNext();
	}
	return *newPoly;
}

Polynomial Polynomial::operator+(const Monomial& mon) const {
	Polynomial* temp = new Polynomial(*this);
	temp->add(mon);
	return *temp;
}

Polynomial& Polynomial::operator-(const Polynomial& other) const {
	Monomial* polyPtr = head->getNext();
	Polynomial* newPoly = new Polynomial();
	while (polyPtr != NULL) {
		newPoly->add(Monomial(polyPtr->getCoefficient(), polyPtr->getDegree()));
		polyPtr = polyPtr->getNext();
	}
	polyPtr = other.head->getNext();
	while (polyPtr != NULL) {
		newPoly->add(-(Monomial(polyPtr->getCoefficient(), polyPtr->getDegree())));
		polyPtr = polyPtr->getNext();
	}
	return *newPoly;
}

Polynomial Polynomial::operator-() const {
	Polynomial* temp = new Polynomial;
	Monomial* monPtr = temp->head;
	Monomial* ptr = head->getNext();
	while (ptr != NULL) {
		monPtr->setNext(new Monomial(-ptr->getCoefficient(), ptr->getDegree()));
		monPtr = monPtr->getNext();
		ptr = ptr->getNext();
	}
	return *temp;
}

const Polynomial& Polynomial::operator+=(const Monomial& mon) {
	this->add(mon);
	return *this;
}

const double Polynomial::operator[](double num) const { // Get coefficient where degree=num
	Monomial* current = head;
	if (current == NULL) return 0;
	while (current != NULL) {
		if (current->getDegree() == num) return current->getCoefficient();
		else current = current->getNext();
	}
	return 0;
}

//Monomial& Polynomial::operator[](double num){ // Assign new coefficient where degree=num
//	Monomial* current = head->getNext();
//	while (current != NULL) {
//		if (current->getDegree() == num) return *current;
//		current = current->getNext();
//	}
//	return *current;
//}

const double Polynomial::operator()(const int num) const {
	Monomial* current = head;
	double polyValue = 0;
	while (current != NULL) {
		polyValue += (*current)(num);
		current = current->getNext();
	}
	return polyValue;
}


const bool Polynomial::operator!=(const Monomial& mon) const {
	if (head && head->getCoefficient() == mon.getCoefficient() &&
		head->getDegree() == mon.getDegree() && head->getNext() == NULL)
		return false;
	else return true;
};

const bool Polynomial::operator==(const Monomial& mon) const {
	if (head && head->getCoefficient() == mon.getCoefficient() &&
		head->getDegree() == mon.getDegree() && head->getNext() == NULL)
		return true;
	else return false;
};

void Polynomial::deletePolynomialNodes() {
	Monomial* ptr = head, *toDelete = head;
	while (ptr != NULL) {
		ptr = ptr->getNext();
		delete toDelete;
		toDelete = ptr;
	}
	head = NULL;
	maxDegree = 0;
}

void Polynomial::reOrderPoly() {
	Monomial *monomsPtr = head;
	/*if (monomsPtr->getNext() != NULL) {
		monomsPtr = monomsPtr->getNext();
	}
	else
		return;*/
	if (head == NULL) return;

	if (monomsPtr->getCoefficient() == 0) {
		head->setNext(monomsPtr->getNext());
	}
	while (monomsPtr->getNext() != NULL) {
		if (monomsPtr->getNext()->getCoefficient() == 0) {
			monomsPtr->setNext(monomsPtr->getNext()->getNext());
		}
		monomsPtr = monomsPtr->getNext();
	}
	if (monomsPtr->getNext() && monomsPtr->getNext()->getCoefficient() == 0) {
		monomsPtr->setNext(NULL);
	}
	this->setNewMaxDegree();
}

void Polynomial::print() const {
	Monomial *monomsPtr = head;
	if (monomsPtr == NULL) {
		cout << 0;
		return;
	}

	while (monomsPtr != NULL) {
		if (monomsPtr->getCoefficient() != 0) monomsPtr->print();
		if (
			monomsPtr->getNext() != NULL &&
			monomsPtr->getNext()->getCoefficient() > 0
			)
			cout << "+";
		monomsPtr = monomsPtr->getNext();
	}
}

void Polynomial::setNewMaxDegree() {
	Monomial *monomsPtr = head;
	if (monomsPtr->getNext() != NULL) {
		monomsPtr = monomsPtr->getNext();
	}
	else {
		maxDegree = 0;
		return;
	}
	int tempMaxDegree = monomsPtr->getDegree();
	while (monomsPtr != NULL) {
		if (monomsPtr->getDegree() > tempMaxDegree)
			tempMaxDegree = monomsPtr->getDegree();
		monomsPtr = monomsPtr->getNext();
	}
	maxDegree = tempMaxDegree;
}

void Polynomial::add(const Monomial& monToAdd) {

	if (head == NULL) {
		head = new Monomial(monToAdd);
		maxDegree = monToAdd.getDegree();
		return;
	}

	Monomial *monomsPtr = head, *prev = NULL;

	while (monomsPtr) {
		if (monomsPtr->add(monToAdd)) {
			if (monomsPtr->getCoefficient() == 0) {
				if (prev) {
					prev->setNext(monomsPtr->getNext());
				}
				else {
					head = monomsPtr->getNext();
				}
				delete monomsPtr;
			}
			this->reOrderPoly();
			return;
		}
		/*else if (monomsPtr->getDegree() < monToAdd.getDegree()) {
			Monomial* newMonToAdd = new Monomial(monToAdd);
			newMonToAdd->setNext(monomsPtr);
			//monomsPtr->setNext(newMonToAdd);
			return;
		}*/
		prev = monomsPtr;
		monomsPtr = monomsPtr->getNext();
	}

	Monomial* newMonToAdd = new Monomial(monToAdd);
	newMonToAdd->setNext(head);
	head = newMonToAdd;

	this->reOrderPoly();




	/*else if (monToAdd.getDegree() > maxDegree || head->getNext() == NULL)
	{
		Monomial* newMonToAdd = new Monomial(monToAdd.getCoefficient(), monToAdd.getDegree());
		newMonToAdd->setNext(head->getNext());
		head->setNext(newMonToAdd);
		maxDegree = monToAdd.getDegree();
		return;
	}*/

	//Monomial *monomsPtr = head, *prev = head;

	/*while(monomsPtr) {
		if(monomsPtr->add(monToAdd)) {
			if (monomsPtr->getCoefficient() == 0) {
				prev->setNext(monomsPtr->getNext());
				delete monomsPtr;
			}
			//monToAdd.~Monomial();
			this->reOrderPoly();
			return;
		}
		else if (monomsPtr->getDegree() < monToAdd.getDegree()) {
			Monomial* newMonToAdd = new Monomial(monToAdd);
			newMonToAdd->setNext(monomsPtr);
			//monomsPtr->setNext(newMonToAdd);
			return;
		}
		prev = monomsPtr;
		monomsPtr = monomsPtr->getNext();
	}
	if(monomsPtr->add(monToAdd)) {
		//monToAdd.~Monomial();
		this->reOrderPoly();
		return;
	}
	// If reached so far, need to add the monomial to the end of the polynomial
	Monomial* newMonToAdd = new Monomial(monToAdd.getCoefficient(), monToAdd.getDegree());
	monomsPtr->setNext(newMonToAdd);
	newMonToAdd->setNext(NULL);*/
}
