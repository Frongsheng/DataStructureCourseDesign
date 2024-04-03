#pragma once
#include<iostream>
using namespace std;

template<class T>
struct PolyNode {
	T coef;            //系数
	int expon;         //指数
	PolyNode<T>* next;
	PolyNode() {};
	PolyNode(const T &c, const int e) {
		this->coef = c;
		this->expon = e;
	}
	PolyNode(const T &c,const int e, PolyNode<T>* next) {
		this->coef = c;
		this->expon = e;
		this->next = next;
	}
};
template<class T>
class Polinomial {
public:
	Polinomial();
	Polinomial(Polinomial<T>&b);
	int Degree() { return degree; }							//返回最高阶数
	int Size() { return size; }								//返回项数
	void Input();											//输入多项式
	void Output();											//输出多项式
	void insert(T& c, int e);								//插入新节点
	Polinomial<T>& Add(Polinomial<T>& b);					//相加
	Polinomial<T>& Subtrac(Polinomial<T>& b);				//相减
	Polinomial<T>& Multiply(Polinomial<T>& b);				//相乘
	Polinomial<T>& Divide(Polinomial<T>& b);				//相除
	Polinomial<T>& DivMultiply(const int expon);			//计算除余数
	Polinomial<T>& Derivative();                            //求导
	T Value(const T& x);									//求值
	Polinomial<T>& operator +(Polinomial<T>& b);
	Polinomial<T>& operator -(Polinomial<T>& b);
	Polinomial<T>& operator *(Polinomial<T>& b);
	Polinomial<T>& operator /(Polinomial<T>& b);
	Polinomial<T>& operator %(const T &x);
	T operator ()(const T& x);
protected:
	PolyNode<T>* firstNode; 
	int degree;             //多项式阶数
	int size;               //项数
};

template<class T>
inline Polinomial<T>::Polinomial()
{
	degree = 0;
	firstNode = NULL;
	size = 0;
}

template<class T>
inline Polinomial<T>::Polinomial(Polinomial<T>& b)
{
	this->firstNode = b.firstNode;
	this->degree = b.degree;
	this->size = b.size;
}

template<class T>
inline void Polinomial<T>::Input()
{
	int n;
	cin >> n;
	Polinomial<T> p;//用于记录结果
	for (int i = 0; i < n; i++) {//循环输入各项
		T coef;
		int expon = 0;
		cin >> coef >> expon;
		p.insert(coef, expon);
		*this = p;
	}
}

template<class T>
inline void Polinomial<T>::Output()
{
	PolyNode<T>* p = firstNode;
	if (p->coef == 1) {
		if (p->expon == 1) {
			cout << "x";
		}
		else if (p->expon == 0) {
			cout <<"1";
		}		
		else {
			cout << "x^" << p->expon;
		}
	}
	else if(p->coef == -1) {
		if (p->expon == 1) {
			cout << "-x";
		}
		else if (p->expon == 0) {
			cout << "-1";
		}
		else {
			cout << "-x^" << p->expon;
		}
	}
	else {
		if (p->expon == 1) {
			cout << p->coef << "x";
		}
		else if (p->expon == 0) {
			cout << p->coef;
		}
		else {
			cout << p->coef << "*x^" << p->expon;
		}
	}
	p = p->next;
	while (p) {
		if (p->coef == 1) {
			if (p->expon == 1) {
				cout << "+x";
			}
			else if (p->expon == 0) {
				cout << "+1";
			}
			else {
				cout << "+x^" << p->expon;
			}
		}
		else if (p->coef == -1) {
			if (p->expon == 1) {
				cout << "-x";
			}
			else if (p->expon == 0) {
				cout << "-1";
			}
			else {
				cout << "-x^" << p->expon;
			}
		}
		else {
			if (p->coef > 0) {
				if (p->expon == 1) {
					cout <<"+" << p->coef << "x";
				}
				else if (p->expon == 0) {
					cout <<"+" << p->coef;
				}
				else {
					cout <<"+" << p->coef << "*x^" << p->expon;
				}
			}
			else if (p->coef < 0) {
				if (p->expon == 1) {
					cout << p->coef << "x";
				}
				else if (p->expon == 0) {
					cout << p->coef;
				}
				else {
					cout << p->coef << "*x^" << p->expon;
				}
			}	
		}
		p = p->next;
	}
	cout << endl;
}

template<class T>
inline void Polinomial<T>::insert(T& coef, int expon)
{
	if (coef == 0)return;

	PolyNode<T>* newNode = new PolyNode<T>(coef, expon,NULL);
	if (degree < expon) {//更新多项式阶数
		degree = expon;
	}
	if (firstNode == NULL || firstNode->expon < expon) {
		newNode->next = firstNode;
		firstNode = newNode;
		size++;
	}
	else {
		PolyNode<T>* current = firstNode;
		while (current->next && current->next->expon > expon) {
			current = current->next;
		}
		if (current->next&&current->next->expon == expon) {//使用后继节点判断，否则容易跳过该条件
			current->next->coef += coef;
			if (current->next->coef == 0) {//系数为零，删去节点
				PolyNode<T>* nextNode = current->next->next;
				delete current->next;
				current->next = nextNode;
				size--;
			}
		}
		else {
			newNode->next = current->next;
			current->next = newNode;
			size++;
		}
	}
}

template<class T>
Polinomial<T>& Polinomial<T>::Add(Polinomial<T>& b)
{
	PolyNode<T>* p = firstNode;
	while (p) {
		PolyNode<T>* q = b.firstNode;
		while (q) {
			if (p->expon == q->expon) {
				p->coef = p->coef + q->coef;
				break;
			}
			q = q->next;
		}
		p = p->next;
	}
	return *this;
}

template<class T>
Polinomial<T>& Polinomial<T>::Subtrac(Polinomial<T>& b)
{
	PolyNode<T>* p = firstNode;
	while (p) {
		PolyNode<T>* q = b.firstNode;
		while (q) {
			if (p->expon == q->expon) {
				p->coef = p->coef - q->coef;
				break;
			}
			q = q->next;
		}
		p = p->next;
	}
	return *this;
}

template<class T>
Polinomial<T>& Polinomial<T>::Multiply(Polinomial<T>& b)
{
	Polinomial<T> p;                   //p用来记录最终结果
	PolyNode<T>* p1 = this->firstNode; //p1指向a式
	PolyNode<T>* p2 = b.firstNode;     //p2指向b式           
	while (p1) {
		p2 = b.firstNode;
		while (p2) {
			int mulExpon = p1->expon + p2->expon;
			T muLCoef = p1->coef * p2->coef;
			p.insert(muLCoef, mulExpon);
			p2 = p2->next;
		}
		p1 = p1->next;
	}
	return p;
}

template<class T>
Polinomial<T>& Polinomial<T>::Divide(Polinomial<T>& b)
{
	Polinomial<T> p;                   //p用来记录最终结果
	PolyNode<T>* p1 = this->firstNode; //p1指向a式
	PolyNode<T>* p2 = b.firstNode;     //p2指向b式  
	Polinomial<T> quo;                 //记录商数
	Polinomial<T> ram;				   //记录余数
	while (p1) {
		int divExpon = p1->expon - p2->expon;
		T divCoef = p1->coef / p2->coef;

		quo.insert(divCoef, divExpon);

		Polinomial temp = *this;
		temp.firstNode = p1->next;             //过掉被除数已经处理掉的最高次项
		ram = temp - (b.DivMultiply(divCoef)); //更新余数=被除数-除数*商的系数
		*this = ram;						   //被除数更新为余数
		p1 = this->firstNode;				   //p1继续指向被除数最高次项
	}
	return quo;  //返回商
}

template<class T>
inline Polinomial<T>& Polinomial<T>::DivMultiply(const int divCoef)
{
	PolyNode<T>* p = firstNode;
	while (p) {
		p->coef = p->coef * divCoef;
		p = p->next;
	}
	firstNode = p;
	return *this;
}

template<class T>
inline Polinomial<T>& Polinomial<T>::Derivative()
{
	Polinomial<T>p;
	PolyNode<T>* current = this->firstNode;
	while (current) {
		T derCoef = current->coef * current->expon;
		int derExpon = current->expon - 1;
		p.insert(derCoef, derExpon);
		current = current->next;
	}
	return p;
}

template<class T>
inline T Polinomial<T>::Value(const T& x)
{
	T sum{};
	PolyNode<T>* p = firstNode;
	while (p ) {
		sum += p->coef * pow(x, p->expon);
		p = p->next;
	}
	return sum;
}

template<class T>
inline Polinomial<T>& Polinomial<T>::operator+(Polinomial<T>& b)
{
	Polinomial<T> p = Add(b);
	return p;
}

template<class T>
inline Polinomial<T>& Polinomial<T>::operator-(Polinomial<T>& b)
{
	Polinomial<T> p = Subtrac(b);
	return p;
}

template<class T>
inline Polinomial<T>& Polinomial<T>::operator*(Polinomial<T>& b)
{
	Polinomial<T> p = Multiply(b);
	return p;
}

template<class T>
inline Polinomial<T>& Polinomial<T>::operator/(Polinomial<T>& b)
{
	Polinomial<T> p = Divide(b);
	return p;
}

template<class T>
inline Polinomial<T>& Polinomial<T>::operator%(const T& MOD)
{
	Polinomial<T>p;
	PolyNode<T>* current = this->firstNode;
	while (current) {
		T derCoef = current->coef % MOD;
		int derExpon = current->expon;
		p.insert(derCoef, derExpon);
		current = current->next;
	}
	return p;

}

template<class T>
inline T Polinomial<T>::operator()(const T& x)
{
	return Value(x);
}
