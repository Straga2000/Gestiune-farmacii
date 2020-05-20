#include<iostream>
#include<vector>
#include<string.h>

#define NAMELENGTH 100

#define NEGATIVEERROR 0
#define PERCENTAGEERROR 1
#define RTTIERROR 2

using namespace std;

class ShowAll{};
class ShowVisitors{};

class PharmacyTemplate
{
private:
    const char *name;
    int employees;
    vector <float> revenue;

    const int id;
    static int counter;

public:

    PharmacyTemplate(const char*, int, vector <float>);
    PharmacyTemplate();
    PharmacyTemplate(const PharmacyTemplate&);

    operator =(const PharmacyTemplate&);

    void set_name(char* newName)
    {
        name = newName;
    }

    void set_employees(int employ)
    {
        employees = employ;
    }

    void set_revenue(vector <float> income)
    {
        revenue = income;
    }

    void update_revenue(float value)
    {
        revenue.push_back(value);
    }

    const char *get_name()
    {
        return name;
    }

    int get_employees()
    {
        return employees;
    }

    vector<float> get_revenue()
    {
        return revenue;
    }

    int get_id()
    {
        return id;
    }

    static int get_next_id()
    {
        return counter;
    }

    virtual void print_pharmacy(ostream &) = 0;

    friend ostream& operator <<(ostream &output, PharmacyTemplate& p)
    {
        p.print_pharmacy(output);
        return output;
    }


    friend istream& operator >>(istream &input, PharmacyTemplate& p)
    {
        char *name = new char[NAMELENGTH];
        int employees;

        input.get(name, NAMELENGTH);
        input>>employees;


        p.set_name(name);
        p.set_employees(employees);

        int n; input>>n;

        try
        {
            if(n == 0)
                throw(NEGATIVEERROR);

            float value = 0;
            for(int i = 0; i < n; i++)
            {
                input>>value;
                p.update_revenue(value);
            }
        }
        catch(int a)
        {
            throw(a);
        }

        return input;
    }

    virtual ~PharmacyTemplate()
    {
        counter--;
    }
};
int PharmacyTemplate::counter = 0;

void PharmacyTemplate::print_pharmacy(ostream &output)
{
    output<<"Farmaciei este "<<get_name()<<". ";
    output<<"Are "<<get_employees()<<" angajati. ";
    output<<"Venituri lunare ale companiei sunt: ";

    vector <float> income = get_revenue();
    for(int i = 0; i < income.size(); i++)
        output<<income[i]<<" lei ";
    output<<"\n";
}


PharmacyTemplate::PharmacyTemplate(const char* newName, int employ, vector <float> income) : name(newName), employees(employ), revenue(income), id(counter)
{
    counter++;
}

PharmacyTemplate::PharmacyTemplate() : id(counter)
{
    counter++;
}

PharmacyTemplate::PharmacyTemplate(const PharmacyTemplate &p) : id(counter)
{
    *this = p;
}

PharmacyTemplate::operator =(const PharmacyTemplate &p)
{
    *this = p;
}

class Pharmacy : public PharmacyTemplate
{
public:
    Pharmacy(char*, int, vector<float>);
    Pharmacy();
    operator =(const Pharmacy&);

    void print_pharmacy(ostream &);

    friend istream& operator >>(istream &input, Pharmacy& p)
    {
        ///upcasting
        PharmacyTemplate *base = dynamic_cast<PharmacyTemplate *>(&p);
        input>>*base;
    }


};

Pharmacy::Pharmacy(char* newName, int employ, vector<float> income) : PharmacyTemplate(newName, employ, income){}

Pharmacy::Pharmacy() : PharmacyTemplate(){}

Pharmacy::operator =(const Pharmacy &p)
{
    *this = p;
}

void Pharmacy::print_pharmacy(ostream &output)
{
    PharmacyTemplate::print_pharmacy(output);
}


template <class newClass>
class PharmacyOnline : public PharmacyTemplate
{
private:
    int visitors;
    float discount;

public:

    PharmacyOnline(const char*, int, vector<float>, int, float);
    PharmacyOnline();
    operator =(const PharmacyOnline &);

    void set_visitors(int visit)
    {
        visitors = visit;
    }

    void set_discount(float disc)
    {
        discount = disc;
    }

    int get_visitors()
    {
        return visitors;
    }

    float set_discount()
    {
        return discount;
    }

    void print_pharmacy(ostream&);

    friend istream& operator >>(istream& input, PharmacyOnline &p)
    {
        ///upcasting
        PharmacyTemplate *base = dynamic_cast<PharmacyTemplate *>(&p);
        input>>*base;


        try
        {
            int visitors;
            float discount;

            input>>visitors>>discount;

            if(visitors < 0)
                throw(NEGATIVEERROR);

            if(discount >= 100 || discount <= 0)
                throw(PERCENTAGEERROR);

            p.set_visitors(visitors);
            p.set_discount(discount);
        }
        catch(int a)
        {
            throw(a);
        }
    }
};

template <class newClass>
PharmacyOnline<newClass>::PharmacyOnline(const char* newName, int employ, vector<float> income, int visit, float disc)
    : PharmacyTemplate(newName, employ, income), visitors(visit), discount(disc){}

template <class newClass>
PharmacyOnline<newClass>::PharmacyOnline() : PharmacyTemplate(){}

template <class newClass>
PharmacyOnline<newClass>::operator =(const PharmacyOnline &p)
{
    *this = p;
}

template <class newClass>
void PharmacyOnline<newClass>::print_pharmacy(ostream &output)
{
    PharmacyTemplate::print_pharmacy(output);
}

template <>
void PharmacyOnline<ShowVisitors>::print_pharmacy(ostream &output)
{
    output<<"Un numar de "<<get_visitors()<<" vizitatori au ajuns pe pagina "<<get_name()<<"\n";
}

template <class F, class D0, class D1>
class Manager
{
private:
    vector <F*> pharmacyList;
    const char *chainName;
public:
    Manager(const char *name)
    {
        chainName = name;
    }

    Manager(const Manager &m)
    {
        *this = m;
    }

    void operator =(const Manager &m)
    {
        *this = m;
    }

    void set_name(const char *name)
    {
        chainName = name;
    }

    void operator +=(F *object)
    {
        ///RTTI
        D0 *test0 = dynamic_cast<D0*>(object);
        D1 *test1 = dynamic_cast<D1*>(object);

        if(test0 != 0)
            pharmacyList.push_back(test0);
        if(test1 != 0)
            pharmacyList.push_back(test1);

        if(test1 == 0 && test0 == 0)
            throw(RTTIERROR);
    }

    int get_size()
    {
        return pharmacyList.size();
    }

    const char *get_name()
    {
        return chainName;
    }

    F& operator [](int ItemKey)
    {
        return pharmacyList[ItemKey];
    }

    friend ostream& operator <<(ostream &output, Manager<F, D0, D1> &m)
    {

        output<<m.get_name()<<"\n";
        for(int i = 0; i < m.get_size(); i++)
        {
            ///RTTI
            D0 *test0 = dynamic_cast<D0*>(m.pharmacyList[i]);
            D1 *test1 = dynamic_cast<D1*>(m.pharmacyList[i]);

            if(test1 == 0 && test0 == 0)
            throw(RTTIERROR);

            if(test0 != 0)
                output<<*test0;
            if(test1 != 0)
                output<<*test1;
        }
        return output;
    }

    ~Manager()
    {
        for(int i = 0; i < pharmacyList.size(); i++)
            delete pharmacyList[i];
    }
};

int main()
{
    try
    {
        int choice = -1;
        Manager<PharmacyTemplate, Pharmacy, PharmacyOnline<ShowVisitors>> *m = new Manager<PharmacyTemplate, Pharmacy, PharmacyOnline<ShowVisitors>>("Lantul meu");

        cout<<"Apasa:\n1. Introducere farmacie fizica\n2. Introducere farmacie online\n3. Afiseaza toate farmaciile\n4. Afiseaza marimea lantului\n0. Iesire\n\n";

        while(choice)
        {
            cin>>choice;
            cin.get();
            if(choice == 1)
            {
                cout<<"Introduceti numele | nr de angajati | nr de luni | venitul pe fiecare luna\n";
                Pharmacy *F = new Pharmacy();
                cin>>*F;
                *m += F;
            }

            if(choice == 2)
            {
                cout<<"Introduceti numele | nr de angajati | nr de luni | venitul pe fiecare luna | vizitatori | discount\n";
                PharmacyOnline<ShowVisitors> *F = new PharmacyOnline<ShowVisitors>();
                cin>>*F;
                *m += F;
            }

            if(choice == 3)
            {
                cout<<*m;
            }

            if(choice == 4)
            {
                cout<<"Lantul contine "<<m->get_size()<<" farmacii\n";
            }
        }
    }
    catch(int a)
    {
        if(a == NEGATIVEERROR)
            cout<<"Valoarea nu e valida. Numarul nu trebuie sa fie negativ.\n";
        if(a == PERCENTAGEERROR)
            cout<<"Valoarea trebuie sa fie intre 0 si 100.";
        if(a == RTTIERROR)
            cout<<"Nu s-a putut face conversia la tipul de date";
    }
}

//cin>>*F;
        //cout<<*F;
        /*char *s = "bella dona";
        vector<float>input(3);

        input[0] = 1;
        input[1] = 2;
        input[2] = 3;

        Pharmacy *F = new Pharmacy(s, 12, vector<float>(3));
        Pharmacy *F2 = new Pharmacy(s, 10, input);
        PharmacyOnline<ShowVisitors> *FO = new PharmacyOnline<ShowVisitors>(s, 12, vector<float>(3), 300, 20);
        F = F2;

        Manager<PharmacyTemplate, Pharmacy, PharmacyOnline<ShowVisitors>> *m = new Manager<PharmacyTemplate, Pharmacy, PharmacyOnline<ShowVisitors>>("Lantul meu");
        *m += F;
        *m += FO;
        cout<<*m;
        //cout<<*F;*/

        /*PharmacyOnline<ShowVisitors> *FO = new PharmacyOnline<ShowVisitors>(s, 12, vector<float>(3), 12, 20);
        cout<<*FO;
        cin>>*FO;
        cout<<*FO;
        cout<<FO->get_next_id();
        cin>>*F;*/
