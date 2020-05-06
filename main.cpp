#include<iostream>
#include<string.h>
#include<vector>
#include<tuple>
#include<typeinfo>

using namespace std;


template <class unknown>
class pharmacy_template
{
    protected:
        tuple <const char *, int, unknown> info;

    public:
        pharmacy_template(tuple<const char *, int, unknown> inputInfo) : info(inputInfo){}

        pharmacy_template(const pharmacy_template &p)
        {
            this = p;
        }

        tuple <const char *, int, unknown> getObject()
        {
            return info;
        }

        const char* get_name()
        {
            return get<0>(info);
        }

        void set_name(const char* newName)
        {
            get<0>(info) = newName;
        }

        void set_number(int number)
        {
            get<1>(info) = number;
        }

        int get_number()
        {
            return get<1>(info);
        }


        /*friend ostream& operator <<(ostream &output, pharmacy_template& p)
        {
            output<<get<0>(p.info)<<" "<<get<1>(p.info);
        }*/
};

class pharmacy : public pharmacy_template<vector<float>>
{
    public:
        pharmacy(tuple<const char *, int, vector<float>> inputInfo) : pharmacy_template<vector<float>>(inputInfo){}

        vector<float> get_monthly_income()
        {
            return get<2>(info);
        }

        void set_monthly_income(vector<float> income)
        {
            get<2>(info) = income;
        }

        float sum(vector<float> vec)
        {
            int s = 0;
            for(int i = 0; i < vec.size(); i++)
                s += vec[i];
            return s;
        }

        friend ostream& operator <<(ostream &output, pharmacy& p)
        {
            output<<"Farmacia "<<p.get_name()<<" are "<<p.get_number()<<" angajati si un venit mediu lunar de "<< p.sum(p.get_monthly_income())<<" de lei.\n";
        }
};

class pharmacyOnline : public pharmacy_template<float>
{
    public:
        pharmacyOnline(tuple<const char *, int, float> inputInfo) : pharmacy_template<float>(inputInfo){}

        get_discount()
        {
            return get<2>(info);
        }

        void set_discount(float discount)
        {
            get<2>(info) = discount;
        }

        friend ostream& operator <<(ostream &output, pharmacyOnline& p)
        {
            output<<"Farmacia online "<<p.get_name()<<" are "<<p.get_number()<<" vizitatori si un discount de "<<p.get_discount()<<"%.\n";
        }
};

template <class F>
class manager
{
    protected:
        vector <F> pharmacyList;
        const char *chainName;
    public:
        manager(const char *name)
        {
            chainName = name;
        }

        void operator +=(F object)
        {
            pharmacyList.push_back(object);
        }

        int get_size()
        {
            return pharmacyList.size();
        }

        F& operator [](int ItemKey)
        {
            return pharmacyList[ItemKey];
        }

        friend ostream& operator <<(ostream &output, manager<F> &m)
        {
            output<<m.chainName<<"\n";
            for(int i = 0; i < m.get_size(); i++)
                output<<m.pharmacyList[i]<<" ";
            return output;
        }
};

int main()
{
    /*manager<float> g("numele meu");*/
    //g += 2.132;
    //g += 7.32544;
    //g += 10.11;

    //cout<<g;

    /*char *s = new char[20];
    for(int i = 0; i < 20; i++)
        s[i] = 97 + i;
    s[20] = 0;

    tuple<const char*, int, float> tuple1;

    const char *web = "eu sunt numele";
    int viz = 333;
    float discount = 20.13;

    tuple1 = make_tuple(s, 332, 20.13);

    tie(web, viz, discount) = tuple1;

    get<0>(tuple1) = "nu";

    cout<<tuple_size<decltype(tuple1)>::value;*/

    /*vector <float> values;

    values.push_back(10);
    values.push_back(20);

    tuple <const char*, int, vector<float>> input;

    input = make_tuple("sunt o vaca", 20, values);

    pharmacy F(input);

    cout<<F.get_number()<<" ";
    F.set_number(12);
    cout<<F.get_number()<<"\n";
    cout<<F;*/

    /*tuple <const char*, int, float> input("ONLINE", 60, 20);*/
    /*pharmacyOnline F(input);
    cout<<F;*/

    //pharmacy_template<float> newPharma(input);

    //cout<<newPharma;

    //cout<<newPharma.get_name();

    //cout<<get<0>(newPharma.getObject());

}
