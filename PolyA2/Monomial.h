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
	const Monomial& operator=(const Monomial& other);
	const bool operator==(const Monomial& other) const;
	const bool operator!=(const Monomial& other) const;
	Monomial operator+(const Monomial& other) const;
	Monomial operator-(const Monomial& other) const;
	Monomial operator-() const;
	Monomial operator*(const Monomial& other) const;
	const Monomial& operator*=(const Monomial& other);
	const Monomial& operator+=(const Monomial& other);
	const Monomial& operator-=(const Monomial& other);
	const double operator()(const int num) const;
	const bool add(const Monomial& other);
	static int getNumberOfMonomials() { return numberOfMonomials; };
	void print() const;
	const int getDegree() const { return degree; };
	double getCoefficient() const { return coefficient; };
	double& getCoeByRef() { return coefficient; };
	Monomial* getNext() const { return next; };
	void setCoefficient(const double coe) { coefficient = coe; };
	void setDegree(const int deg) { degree = deg; };
	void setNext(Monomial *newNext) { next = newNext; };
	static void ExtractCoeAndDegFromString(char* stringToRead, double& c, int &d);
};

#endif /* Monomial_h */
