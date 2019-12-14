#include "Polynomial.h"
#include <iomanip>
#include <iostream>
#include "Monomial.h"

using namespace std;

Polynomial::Polynomial() {
	head = NULL;
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
	if (this->head != NULL) { // if this poly isn't empty then clear its monomials
		this->deletePolynomialNodes();
	}
	if (other.head != NULL) { // if other poly isn't empty
		Monomial* ptr = head;
		Monomial* otherPtr = other.head;
		while (otherPtr != NULL) {
			ptr->setNext(new Monomial(*otherPtr));
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

void Polynomial::add(const Monomial& monToAdd) {
	if (head == NULL) {
		head = new Monomial(monToAdd);
		return;
	}

	Monomial *monomsPtr = head, *prev = NULL;

	while (monomsPtr) {
		if (monomsPtr->add(monToAdd)) { // Found monomial with same degree
			if (monomsPtr->getCoefficient() == 0) { // if monomial coe is 0 need to vanish
				if (prev) {
					prev->setNext(monomsPtr->getNext());
				}
				else {
					head = monomsPtr->getNext();
				}
				delete monomsPtr;
			}
			return;
		}
		else if (monToAdd.getDegree() > monomsPtr->getDegree()) { // Need to insert before monomsptr
			Monomial* newMonToAdd = new Monomial(monToAdd);
			newMonToAdd->setNext(monomsPtr);
			if (prev) {
				prev->setNext(newMonToAdd);
			}
			else {
				head = newMonToAdd;
			}
			return;
		}
		prev = monomsPtr;
		monomsPtr = monomsPtr->getNext();
	}

	// If reached so far need to add the end of the list
	Monomial* newMonToAdd = new Monomial(monToAdd);
	prev->setNext(newMonToAdd);
}

