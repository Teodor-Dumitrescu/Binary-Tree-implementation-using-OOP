#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <fstream>

using namespace std;

class arbore;
class nod
{
    friend class arbore;
    friend ostream &operator<<(ostream &output, arbore &arb);
private:
    int cheie;
    nod *st,*dr;
    int h;
public:
    nod()
    {
        h=-1;
    }
};

class arbore
{
    friend arbore operator+(arbore arb, int x);
    friend ostream &operator<<(ostream &output, arbore &arb);
    friend istream &operator>>(istream &input, arbore &arb);
private:
    nod *radacina;
public:
    arbore()
    {
        radacina=NULL;
    }
    nod* get_radacina();  ///nu o folosesc deloc, dar sta si ea aici frumos
    void inserare(nod *&p, int x);
    void inordine(nod *p,char *s);
    void afisare();
    void afisare_frunze(nod *p);
    void stergere(int x);
    void stergere_nod(int x, nod *&p);
    int inaltime();
    void set_inaltime_noduri(nod *&p);
};

nod* arbore::get_radacina()
{
    return radacina;
}

void arbore::inordine(nod *p,char *s)
{
    if(p!=NULL)
    {
        inordine(p->st,s);
        strcat(s," ");
        char c[100];
        itoa(p->cheie,c,10);
        strcat(s,c);
        inordine(p->dr,s);
    }
}

void arbore::inserare(nod *&p, int x)
{
    if(p==NULL)
    {
        p=new nod;
        p->cheie=x;
        p->st=NULL;
        p->dr=NULL;
    }
    else
    {
        if(x < p->cheie)
            inserare(p->st,x);
        if(x > p->cheie)
            inserare(p->dr,x);
    }
}

void arbore::stergere(int x)
{
    stergere_nod(x,radacina);
}

void arbore::stergere_nod(int x, nod *&p)
{
    if(p==NULL)
    {
        cout<<"Arborele NU contine nodul cu valoarea "<<x<<endl;
        return;
    }
    if(x < p->cheie)
        stergere_nod(x,p->st);
    else if(x > p->cheie)
        stergere_nod(x,p->dr);
    else if(x == p->cheie)
    {
        if(p->st==NULL && p->dr==NULL)
            {
                p=NULL;
                cout<<"Nodul cu cheia "<<x<<" a fost sters"<<endl;
            }
        else if(p->st!=NULL && p->dr==NULL)
        {
            p->cheie=p->st->cheie;
            p->st->cheie=x;
            stergere_nod(x,p->st);
        }
        else if(p->st==NULL && p->dr!=NULL)
        {
            p->cheie=p->dr->cheie;
            p->dr->cheie=x;
            stergere_nod(x,p->dr);
        }
        else if(p->st!=NULL && p->dr!=NULL)
        {
            nod *q=p->st;
            while(q->dr!=NULL)
                q=q->dr;
            p->cheie=q->cheie;
            q->cheie=x;
            stergere_nod(x,q);
        }
    }
}

int arbore::inaltime()
{
    if(radacina==NULL)
        return -1;
    set_inaltime_noduri(radacina);
    return radacina->h;
}

void arbore::set_inaltime_noduri(nod *&p)
{
    if(p==NULL)
        return;
    if(p->st==NULL && p->dr==NULL)
        p->h=0;
    set_inaltime_noduri(p->st);
    set_inaltime_noduri(p->dr);
    if(p->st!=NULL && p->dr!=NULL)
    {
        p->h= p->st->h + p->dr->h + abs(p->st->h - p->dr->h);
        p->h=(p->h)/2 + 1;
    }
    else if(p->st!=NULL && p->dr==NULL)
    {
        p->h = p->st->h + 1;
    }
    else if(p->st==NULL && p->dr!=NULL)
    {
        p->h = p->dr->h + 1;
    }
}

void arbore::afisare()
{
    cout<<"Lista frunzelor: ";
    afisare_frunze(radacina);
    cout<<endl;
}

void arbore::afisare_frunze(nod *p)
{
    if(p==NULL)
        return;
    if(p->st==NULL && p->dr==NULL)
        cout<<p->cheie<<" ";
    afisare_frunze(p->st);
    afisare_frunze(p->dr);
}

arbore operator+(arbore arb, int x)
{
    arbore arb2;
    arb2=arb;
    arb2.inserare(arb2.radacina,x);
    return arb2;
}

ostream &operator<<(ostream &output, arbore &arb)
{
    char s[1000];
    strcpy(s,"Inordine: ");
    arb.inordine(arb.radacina,s);
    output<<s;
    return output;
}

istream &operator>>(istream &input, arbore &arb)
{
    int x;
    cout<<"Cheia nodului: ";
    input>>x;
    arb.inserare(arb.radacina,x);
    return input;
}

int main()
{
    ///am facut meniu si nu puteam pune inserari succesive in el (cin>>arb>>arb>>arb), dar merge ca instructiune scrisa separat
    ///la fel arb=arb1+3+5+7; etc.
    ///pot fi declarate mai multe obiecte de tip arbore si lucrat cu fiecare separat, dar pentru ca am facut cu meniu, am creeat un singur obiect
    ///in loc de cin si cout se pot folosi "in" si "out" pentru citire/afisare din/in fisier, dar am facut cu meniu(stiu ca am zis de 3 ori) si am lasat cin/cout
    ifstream in("fisier.in");
    ofstream out("fisier.out");
    /*int x=5;
    arbore bst;
    bst=bst+3+x+4+2+1+6;//+7;
    in>>bst>>bst>>bst;
    out<<bst<<endl;
    //bst.afisare();
    bst.stergere(8);
    cout<<bst<<endl;
    cout<<"Inaltimea arborelui (primul nivel este 0) este: "<<bst.inaltime()<<endl;
    //cin>>x;
    //bst>>x;
    arbore arb;
    cin>>arb>>arb>>arb;
    arb=arb+8+9+5;
    cout<<arb;*/
    cout<<"MENIU"<<endl;
    cout<<"1.inserare element(+)"<<endl;
    cout<<"2.inserare element(>>)"<<endl;
    cout<<"3.afisare inordine"<<endl;
    cout<<"4.stergere element"<<endl;
    cout<<"5.afisare inaltime arbore"<<endl;
    cout<<"6.afisare lista frunze"<<endl;
    int option,val;
    arbore arb1;
    while(1)
    {
        cout<<"Alegeti"<<endl;
        cin>>option;
        switch(option)
        {
            case 1:
            {
                cout<<"Alegeti valoarea elementului"<<endl;
                cin>>val;
                arb1=arb1+val;
                break;
            }
            case 2:
            {
                cin>>arb1;
                break;
            }
            case 3:
            {
                cout<<arb1<<endl;
                break;
            }
            case 4:
            {
                cout<<"Alegeti valoarea elementului care va fi sters"<<endl;
                cin>>val;
                arb1.stergere(val);
                break;
            }
            case 5:
            {
                if(arb1.inaltime()!=-1)
                    cout<<"Inaltimea arborelui (primul nivel este 0) este: "<<arb1.inaltime()<<endl;
                else
                    cout<<"Arborele este gol"<<endl;
                break;
            }
            case 6:
            {
                arb1.afisare();
                break;
            }
        }
    }
    return 0;
}
