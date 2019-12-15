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

Polynomial::Polynomial(const Polynomial& other) {
	head = NULL;
	Monomial* ptr = head,*otherPtr = other.head;
	if (!other.head) return;
	else {
		head = new Monomial(otherPtr->getCoefficient(),otherPtr->getDegree());
		ptr = head;
		otherPtr = otherPtr->getNext();
		while (otherPtr) {
			ptr->setNext(new Monomial(otherPtr->getCoefficient(), otherPtr->getDegree()));
			ptr = ptr->getNext();
			otherPtr = otherPtr->getNext();
		}
	}
}

istream& operator>>(istream& in, Polynomial& p) {
	if (p.head) {
		p.deletePolynomialNodes(); // Empty the polynomial
	}
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

ostream& operator<<(ostream& out, const Polynomial& p) {
	p.print();
	cout << endl;
	return out;
}

const Polynomial& Polynomial::operator=(const Polynomial& other) {
	if (*this == other) return *this;
	if (head) { // if this poly isn't empty then clear its monomials
		this->deletePolynomialNodes();
	}
	if (other.head) { // if other poly isn't empty
		Monomial* otherPtr = other.head;
		while (otherPtr != NULL) {
			this->add(*otherPtr);
			otherPtr = otherPtr->getNext();
		}
	}
	return *this;
}


Polynomial Polynomial::operator+(const Polynomial& other) const {
	Monomial* polyPtr = head;
	Polynomial newPoly;
	while (polyPtr != NULL) {
		newPoly.add(*polyPtr);
		polyPtr = polyPtr->getNext();
	}
	polyPtr = other.head;
	while (polyPtr != NULL) {
		newPoly.add(*polyPtr);
		polyPtr = polyPtr->getNext();
	}
	return newPoly;
}

Polynomial Polynomial::operator+(const Monomial& mon) const {
	Polynomial temp = *this;
	temp.add(mon);
	return temp;
}

Polynomial Polynomial::operator-(const Polynomial& other) const {
	Monomial* polyPtr = head;
	Polynomial newPoly;
	while (polyPtr != NULL) {
		newPoly.add(Monomial(*polyPtr));
		polyPtr = polyPtr->getNext();
	}
	polyPtr = other.head;
	while (polyPtr != NULL) {
		newPoly.add(-(Monomial(*polyPtr)));
		polyPtr = polyPtr->getNext();
	}
	return newPoly;
}

Polynomial Polynomial::operator-(const Monomial& mon) const {
	Polynomial temp = *this;
	temp.add(-mon);
	return temp;
}


Polynomial Polynomial::operator-() const {
	if (!head) return Polynomial();
	Polynomial temp;
	Monomial* monPtr = head;
	Monomial* ptr = head;
	if (head) {
		temp.head = new Monomial(-head->getCoefficient(),head->getDegree());
		monPtr = temp.head;
		ptr = head->getNext();
	}
	while (ptr != NULL) {
		monPtr->setNext(new Monomial(-(ptr->getCoefficient()), ptr->getDegree()));
		monPtr = monPtr->getNext();
		ptr = ptr->getNext();
	}
	return temp;
}

const Polynomial& Polynomial::operator+=(const Monomial& mon) {
	this->add(mon);
	return *this;
}

double& Polynomial::operator[](int num) const { // Get coefficient where degree=num
	Monomial* current = head;
	double x = 0;
	if (head == NULL) return x; // list is empty, returning 0
	while (current != NULL) {
		if (current->getDegree() == num) {
			return (current->getCoeByRef()); //  Get the coefficient by ref to read/re-assign
		}
		else current = current->getNext();
	}
	// If reached so far the degree hasn't been found so returning 0
	return x; // Returning 0
}

const double Polynomial::operator()(const int num) const {
	Monomial* current = head;
	double polyValue = 0;
	while (current != NULL) {
		polyValue += (*current)(num);
		current = current->getNext();
	}
	return polyValue;
}

const bool Polynomial::operator==(const Polynomial& other) const {
	if (!head || !other.head) return false;
	Monomial* monPtr = head;
	Monomial* otherPtr = other.head;
	while (monPtr && otherPtr) {
		if (monPtr->getCoefficient() == otherPtr->getCoefficient() &&
			monPtr->getDegree() == otherPtr->getDegree())
		{
			monPtr = monPtr->getNext();
			otherPtr = otherPtr->getNext();
		}
		else return false;
	}
	if (otherPtr || monPtr) return false; // didn't reach the end of one of the polynomials
	else return true; // They are equal
};

const bool Polynomial::operator==(const Monomial& mon) const {
	if (head && head->getCoefficient() == mon.getCoefficient() &&
		head->getDegree() == mon.getDegree() && head->getNext() == NULL)
		return true;
	else return false;
};

const bool Polynomial::operator!=(const Monomial& mon) const {
	if (head && head->getCoefficient() == mon.getCoefficient() &&
		head->getDegree() == mon.getDegree() && head->getNext() == NULL)
		return false;
	else return true;
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
	// list is empty or filled only by zero
	if (head == NULL || (head->getCoefficient() == 0 && head->getNext() == NULL)) { 
		cout << 0;
		return;
	}
	else {
		Monomial *monomsPtr = head;
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
}

void Polynomial::add(const Monomial& monToAdd) {
	if (head == NULL) {
		head = new Monomial(monToAdd);
		return;
	}
	else if (monToAdd.getCoefficient() == 0)
	{
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

	// If reached so far need to add to the end of the list
	Monomial* newMonToAdd = new Monomial(monToAdd);
	prev->setNext(newMonToAdd);
}

