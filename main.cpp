#include <iostream>
#include <cmath>

using namespace std;

class Nod;
class Lista;
class Polinom_dinamic;

class Pereche
{
private:
    friend class Nod;
    friend class Lista;
    friend class Polinom_dinamic;
    double coef;
    int exp;
public:
    Pereche()
    {
        coef = 0;
        exp = 0;

    }
    Pereche(double c, int e)
    {
        coef = c;
        exp = e;

    }
    Pereche( const Pereche& p)
    {
        this->coef = p.coef;
        this->exp = p.exp;

    }
    ~Pereche()
    {
        cout<<"S-a apelat destructorul"<<endl;
    }
};

class Nod
{
    friend class Lista;
    friend class Polinom_dinamic;
    Pereche p;
    Nod* prev;
    Nod* next;

public:
    Nod()
    {
        next = NULL;
        prev = NULL;
    }
    Nod(double coef, int exp)
    {
        p.coef = coef;
        p.exp = exp;
        next = NULL;
        prev = NULL;
    }
    ~Nod()
    {
        next = NULL;
        prev = NULL;
    }
};

class Lista
{
    friend class Nod;
    friend class Polinom_dinamic;
    Nod* primul;
    Nod* ultimul;
    int marime;

public:
    Lista()
    {
        marime = 0;
        primul = NULL;
        ultimul = NULL;
    }
    ~Lista()
    {
        for(int i = 0; i < marime; i++) {
            Nod* ptr = primul->next;
            delete primul;
            primul = ptr;
        }
    }

    void add(Pereche p)
    {
        if(ultimul == NULL)
        {
            ultimul = new Nod;
            ultimul->p = p;
            primul = ultimul;
            marime++;
            return;
        }

        Nod* elem = new Nod;
        ultimul->next = elem;
        elem->prev = ultimul;
        elem->p = p;
        ultimul = elem;
        marime++;
    }

    inline int get_marime() const{
        return marime;
    }

    inline Nod* get_primul() const {
        return primul;
    }
};

class Polinom_dinamic
{
    Lista perechi;

public:
    Polinom_dinamic() = default;
    Polinom_dinamic(Lista& l) /// Daca nu e referinta apeleaza copy-constructorul pe care nu l-am implementat
    {
        Nod* ptr = l.get_primul();
        for(int i = 0; i < l.get_marime(); i++) {
            perechi.add(ptr->p);
            ptr = ptr->next;
        }
    }
    ~Polinom_dinamic() = default;

    double valoare(int x)
    {
        double suma = 0.0;
        Nod* ptr = perechi.primul;
        for(int i = 0; i < perechi.marime; i++) {
            suma += ptr->p.coef * (pow(x, ptr->p.exp));
            ptr = ptr->next;
        }
        return suma;
    }

    inline int grad() const
    {
        if(perechi.ultimul == NULL) {
            return -1;
        }

        return perechi.ultimul->p.exp;
    }

    friend Polinom_dinamic operator+(Polinom_dinamic&, Polinom_dinamic&);
    friend Polinom_dinamic operator-(Polinom_dinamic&, Polinom_dinamic&);
    friend Polinom_dinamic operator*(Polinom_dinamic&, Polinom_dinamic&);

};

 Polinom_dinamic operator+(Polinom_dinamic& p1, Polinom_dinamic& p2)
{
    //nu am stiut sa fac supraincarcarea
}

Polinom_dinamic operator-(Polinom_dinamic& p1, Polinom_dinamic& p2)
{
    //nu am stiut sa fac supraincarcarea
}
Polinom_dinamic operator*(Polinom_dinamic& p1, Polinom_dinamic& p2)
{
    //nu am stiut sa fac supraincarcarea
}


int main()
{
    Lista l;
    l.add(Pereche(3, 2));
    l.add(Pereche(5, 7));
    Polinom_dinamic p(l);
    cout << p.valoare(2) << endl;
    cout << p.grad() << endl;
}
