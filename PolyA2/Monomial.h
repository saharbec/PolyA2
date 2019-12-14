#ifndef Monomial_h
#define Monomial_h

#include <iomanip>
#include <iostream>
using namespace std;

class Monomial {
private:
	double coefficient;
	int degree;
	static int numberOfMonomials;
	Monomial* next;

public:
	Monomial(double coe = 1, const int deg = 0);
	Monomial(const Monomial& other);
	~Monomial();
	friend ostream& operator <<(ostream&, const Monomial&);
	friend istream& operator >>(istream&, Monomial&);
	Monomial& operator=(int coe);
	const bool operator==(const Monomial& other) const;
	const bool operator!=(const Monomial& other) const;
	Monomial operator+(const Monomial& other) const;
	Monomial operator-(const Monomial& other) const;
	Monomial operator-() const;
	Monomial operator*(const Monomial& other) const;
	const Monomial& operator*=(const int numToMul);
	const Monomial& operator+=(const Monomial& other);
	const Monomial& operator-=(const Monomial& other);
	const double operator()(const int num) const;
	const bool operator!=(const int numToCompare) const;
	const bool add(const Monomial& other);
	static int getNumberOfMonomials() { return numberOfMonomials; };
	void print() const;
	const int getDegree() const { return degree; };
	double getCoefficient() const { return coefficient; };
	double& getCoeByRef() { return coefficient; };
	Monomial* getNext() const { return next; };
	void setCoefficient(const int coe) { coefficient = coe; };
	void setDegree(const int deg) { degree = deg; };
	void setNext(Monomial *newNext) { next = newNext; };
};

#endif /* Monomial_h */
