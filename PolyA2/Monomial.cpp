#include <iomanip>
#include <assert.h>
#include <iostream>
using namespace std;
#include "Monomial.h"

const double getPow(double base, int exponent) {
	double ans = 1;
	for (int i = 0; i < exponent; i++)
		ans *= base;
	return ans;
}

int Monomial::numberOfMonomials = 0;

Monomial::Monomial(double coe, int deg) : coefficient(coe), degree(deg), next(NULL) {
	assert(deg >= 0);
	if (deg < 0)
		cout << "ERROR! Invalid exponent value entered";
	else {
		numberOfMonomials++;
	}

}

Monomial::Monomial(const Monomial& other)
	: coefficient(other.coefficient), degree(other.degree) {
	numberOfMonomials++;
}

Monomial::~Monomial() {
	numberOfMonomials--;
}

istream& operator>>(istream& in, Monomial& m) {
	int c, d;
	cout << "Insert Monomial coefficient: ";
	in >> c;
	cout << "Insert Monomial degree: ";
	in >> d;
	m.setCoefficient(c);
	m.setDegree(d);
	return in;
}

ostream& operator<<(ostream& out, const Monomial& m) {
	m.print();
	return out;
}

const Monomial& Monomial::operator=(const Monomial& other) {
	coefficient = other.coefficient;
	degree = other.degree;
	return *this;
};

const bool Monomial::operator==(const Monomial& other) const {
	if (coefficient == other.coefficient && degree == other.degree) return true;
	else return false;
}

const bool Monomial::operator!=(const Monomial& other) const {
	if (coefficient == other.coefficient && degree == other.degree) return false;
	else return true;
}

Monomial Monomial::operator+(const Monomial& other) const {
	if (degree == other.degree) return Monomial(coefficient + other.coefficient, degree);
	else return Monomial(coefficient, degree);
}

Monomial Monomial::operator-(const Monomial& other) const {
	if (degree == other.degree) return Monomial(coefficient - other.coefficient, degree);
	else return Monomial(coefficient, degree);
}

Monomial Monomial::operator-() const {
	return Monomial(-coefficient, degree);
}


Monomial Monomial::operator*(const Monomial& other) const {
	return Monomial(coefficient * other.coefficient, degree + other.degree);
}

const Monomial& Monomial::operator*=(const Monomial& other) {
	coefficient *= other.coefficient;
	degree += other.degree;
	return *this;
}

const Monomial& Monomial::operator+=(const Monomial& other) {
	if (degree == other.degree) {
		coefficient += other.coefficient;
	}
	return *this;
}

const Monomial& Monomial::operator-=(const Monomial& other) {
	if (degree == other.degree) {
		coefficient -= other.coefficient;
	}
	return *this;
}


const double Monomial::operator()(const int num) const {
	return coefficient * getPow(num, degree);
}

void Monomial::print() const {
	if (coefficient == 0)
		cout << 0;
	else if (degree == 0) {
		cout << coefficient;
	}
	else if (coefficient == 1 && degree == 1) {
		cout << "x";
	}
	else if (coefficient == 1 && degree > 1) {
		cout << "x^" << degree;
	}
	else if (degree == 1) { // coefficient != 1
		cout << coefficient << "*x";
	}
	else { // coefficient !=1 AND degree != 1
		cout << coefficient << "*x^" << degree;
	}
}

const bool Monomial::add(const Monomial& other) {
	if (degree != other.degree)
		return false;
	else {
		coefficient += other.coefficient;
		return true;
	}
};
