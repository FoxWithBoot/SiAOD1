// ConsoleApplication3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

class Uzel {
private:
	int value;//значение
	Uzel* left;//указатель на правое дерево
	Uzel* right;//указатель на левое дерево
	int number;//номер узла (послойно)
	int hight;//высота узла
	int children;//кол-во детей

	void sethight(int h) {//устанавливает высоту узла
		hight = h;
		h = hight + 1;
		if (left != NULL) left->sethight(h);
		if (right != NULL) right->sethight(h);
	}

	void numbers() {
		int t = 0;
		for (int i = 1; i < maxh() + 1; i++) {
			t = numberss(i, t);
		}
	}

	int numberss(int n, int t) {//устанавливает послойные номера узлов
		if (hight == n) {
			t++;
			number = t;
		}
		if (left != NULL) t = left->numberss(n, t);
		if (right != NULL) t = right->numberss(n, t);
		return t;
	}

	int maxh() {//находит максимальную высоту дерева
		if ((left == NULL) && (right == NULL)) return hight;
		if ((left != NULL) && (right != NULL)) return max(left->maxh(), right->maxh());
		if ((left != NULL) && (right == NULL)) return left->maxh();
		else return right->maxh();
	}

	int childrenN() {//устанавливает для каждого узла кол-во его детей
		int n = 0;
		if ((left == NULL) && (right == NULL)) n = 0;
		if ((left != NULL) && (right != NULL)) n = left->childrenN() + right->childrenN();
		if ((left == NULL) && (right != NULL)) n = right->childrenN();
		if ((left != NULL) && (right == NULL)) n = left->childrenN();
		children = n;
		n++;
		return n;
	}




	//для 14 варианта
	vector<int> topdown(vector<int> a) {//обход сверху-вниз
		a.push_back(value);
		if (left != NULL) a = left->topdown(a);
		if (right != NULL) a = right->topdown(a);
		return a;
	}

	vector<int> leftright(vector<int> a) {//обход слева-направо
		if (left != NULL) a = left->leftright(a);
		a.push_back(value);
		if (right != NULL) a = right->leftright(a);
		return a;
	}

	vector<int> downtop(vector<int> a) {//обход снизу-вверх
		if (left != NULL) a = left->downtop(a);
		if (right != NULL) a = right->downtop(a);
		a.push_back(value);
		return a;
	}

	vector<int> put(vector<int>p, int a, int b) {//создаёт путь
		vector<int>r;
		bool t = false;
		for (int i = 0; i < p.size(); i++) {
			if ((p[i] == a) || (p[i] == b)) {
				t = !t;
				if (t == false) r.push_back(p[i]);
			}
			if (t) r.push_back(p[i]);
		}
		return r;
	}

	void showtd(vector<int>& a) {
		for (int i = 0; i < a.size(); i++) {
			if (a[i] == value) cout << number << " ";
		}

		if (left != NULL) left->showtd(a);
		if (right != NULL) right->showtd(a);
	}

	void showlr(vector<int>& a) {
		if (left != NULL) left->showlr(a);

		for (int i = 0; i < a.size(); i++) {
			if (a[i] == value) cout << number << " ";
		}

		if (right != NULL) right->showlr(a);
	}

	void showdt(vector<int>& a) {
		if (left != NULL) left->showdt(a);
		if (right != NULL) right->showdt(a);

		for (int i = 0; i < a.size(); i++) {
			if (a[i] == value) cout << number << " ";
		}
	}


public:
	Uzel(int a) {
		value = a;
		left = NULL;
		right = NULL;
		hight = 1;
		children = 0;
		number = 0;
	}

	~Uzel() {
		delete left;
		delete right;
	}

	void show() {//показать дерево по значениям (обход сверху-вниз)
		cout << value <<'\n';
		if (left!=NULL) left->show();
		
		if(right!=NULL)right->show();
		
	}

	void add(int  a) {//добавление узла
			if (a < value) {
				if (left != NULL) left->add(a);
				else left = new Uzel(a);
			}
			if (a > value) {
				if (right != NULL) right->add(a);
				else right = new Uzel(a);
			}
			sethight(hight);
			numbers();
			childrenN();
	}

	void variant8() {//вариант 8
		if ((left == NULL) ^ (right == NULL)) cout << number << " ";
		if ((left != NULL) && (right != NULL)) {
			if (left->children != right->children) cout << number << " ";
		}
		if (left != NULL)left->variant8();
		if (right != NULL)right->variant8();
	}

	void variant14(int a, int b) {//вариант 14
		vector<int>p;
		vector<int>r;
		int s1, s2, s3;
		p = topdown(p);
		r = put(p, a, b);
		s1 = r.size();

		p.resize(0);
		p = leftright(p);
		r = put(p, a, b);
		s2 = r.size();

		p.resize(0);
		p = downtop(p);
		r = put(p, a, b);
		s3 = r.size();

		p.resize(0);
		if (max(s1, max(s2, s3)) == s1) {
			p = topdown(p);
			r = put(p, a, b);
			showtd(r);
			/* путь описанный значениями узлов
			for (int i = 0; i < r.size(); i++) {
				cout << r[i] << " ";
			}
			*/
		}
		
		if (max(s1, max(s2, s3)) == s2) {
			p = leftright(p);
			r = put(p, a, b);
			showlr(r);
			/* путь описанный значениями узлов
			for (int i = 0; i < r.size(); i++) {
				cout << r[i] << " ";
			}
			*/
		}
		if (max(s1, max(s2, s3)) == s3) {
			p = downtop(p);
			r = put(p, a, b);
			showdt(r);
			/* путь описанный значениями узлов
			for (int i = 0; i < r.size(); i++) {
				cout << r[i] << " ";
			}
			*/
		}
	}

	/*
	void variant14B(int a, int b) {
		string pA, pB;
		if ((a < value) && (b < value)) left->variant14B(a, b);
		else 
			if ((a > value) && (b > value)) left->variant14B(a, b);
			else {
				pA=putA(a, pA);
				pA=pA.erase(0, 2);
				pA = rev(pA);//отзеркаливание строки
				pB=putA(b, pB);
				string s = pA + pB;
				cout << s;
			}
	}

private:
	string putA(int a, string pA) {
		pA = pA + to_string(value)+" ";
		if (a < value)pA=left->putA(a, pA);
		if (a > value)pA=right->putA(a, pA);
		return pA;
	}
	*/
};

class FamUzel {
private:
	string name;
	FamUzel* rod;
	vector<FamUzel*> children;


	vector<string> find(string n1, string n2, vector<string>& p) {//ищет указанный узел в дереве
		if (strcmp(name.c_str(), n1.c_str()) == 0) { p = downtop(n2, p); return p; }
		else {
			for (int i = 0; i < children.size(); i++) {
				p = children[i]->find(n1, n2, p);
				//if (p.size() > 0)break;
			}
		}
		return p;
	}

	vector<string>downtop(string n, vector<string>& p) {//строит путь от указанного узла до корня дерева или до второго указанного узла
		p.push_back(name);
		if ((strcmp(name.c_str(), n.c_str()) == 0) || (rod == NULL)) return p;
		else {

			p = rod->downtop(n, p);
		}
		return p;
	}

public:
	FamUzel(string name, FamUzel*a) {
		this->name = name;
		rod = a;
		children.resize(0);
	}
	
	void add(string ch, string rod) {
		if (name == rod) children.push_back(new FamUzel(ch, this));
		else {
			for (int i = 0; i < children.size(); i++) {
				children[i]->add(ch, rod);
			}
		}
	}

	void show() {//показать дерево по значениям (обход сверху-вниз)
		cout << name << " ";
		for (int i = 0; i < children.size(); i++) {
			children[i]->show();
		}
	}

	string variant1(string a, string b) {
		vector<string>aa, bb;
		string s;
		aa = find(a, b, aa);
		bb = find(b, a, bb);
		if (strcmp(aa[aa.size() - 1].c_str(), b.c_str()) == 0) return(b + " предок " + a);
		if (strcmp(bb[bb.size() - 1].c_str(), a.c_str()) == 0) return(a + " предок " + b);

		for (int i = 0; i < aa.size(); i++) {
			for (int j = 0; j < bb.size(); j++) {
				if (strcmp(aa[i].c_str(), bb[j].c_str()) == 0) return("ближайший общий предок " + a + " и " + b + " - " + aa[i]);
			}
		}
	}
};

int main()
{
	setlocale(LC_ALL, "Russian");
	
	//варианты 2, 8 и 14
	Uzel* t = new Uzel(6);
	int a, b;

	t->add(2);
	t->add(8);
	t->add(4);
	t->add(1);
	t->add(3);
	t->add(5);
	t->add(7);
	t->add(9);

	t->variant8();
	cout << '\n';

	cin >> a >> b;
	t->variant14(a, b);
	
	//cin.get();

	cout << '\n';

	//вариант 1
	string c, d;
	FamUzel* tr = new FamUzel("A", NULL);
	tr->add("X", "A");
	tr->add("Z", "A");
	tr->add("Y", "A");

	tr->add("C", "X");
	tr->add("B", "C");
	tr->add("M", "C");
	tr->add("D", "C");
	tr->add("P", "X");

	tr->add("TQ", "Z");
	tr->add("PD", "TQ");
	tr->add("PR", "TQ");

	tr->add("W", "Y");
	tr->add("R", "W");
	tr->add("F", "R");

	//tr->show();
	cout << '\n';

	cin >> c >> d;
	cout << tr->variant1(c, d);

	return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.	UMK
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
