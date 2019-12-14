#pragma once

#include <iomanip>
#include <iostream>
using namespace std;
#include "Monomial.h"

class Polynomial {
private:
	Monomial* head;
	int maxDegree;

public:
	Polynomial();
	~Polynomial();
	friend ostream& operator<<(ostream&, const Polynomial&);
	friend istream& operator>>(istream&, Polynomial&);
	const Polynomial& operator=(const Polynomial& other);
	Polynomial& operator+(const Polynomial& other) const;
	Polynomial operator+(const Monomial& mon) const;
	Polynomial& operator-(const Polynomial& other) const;
	Polynomial operator-() const;
	const Polynomial& operator+=(const Monomial& mon);
	const double operator[](double num) const;
	//Monomial& operator[](double num);
	const double operator()(int num) const;
	const bool operator==(const Monomial& mon) const;
	const bool operator!=(const Monomial& mon) const;
	void print() const;
	void add(const Monomial& monToAdd);
	void reOrderPoly();
	int const getMaxDegree() const { return maxDegree; };
	void setNewMaxDegree();
	void deletePolynomialNodes();
};
