#include <iostream>
#include <fstream>
#include <conio.h>
#include <string.h>

using namespace std;

void bt(int k,int i,int j,int l,char *string,int nr_stari_finale,int nr_simboluri,char *v_simb,int ***m,int *F)
{
    if(l==(strlen(string)-1))
    {
        for(k=0; k<3; k++)
            if(m[k][i][j]!=-1)
                for(int p=0; p<nr_stari_finale; p++)
                    if(m[k][i][j]==F[p])
                    {
                        cout<<"acceptat";
                        return;
                    }


                    else
                    {
                        cout<<"neacceptat";
                        return;
                    }
    }
	
    if(m[k][i][j]==-1 && k<2)
    {
        cout<<"k="<<k<<endl;
        bt(k+1, i, j, l, string, nr_stari_finale, nr_simboluri, v_simb, m, F);
    }
    else if(m[k][i][j]!=-1)
    {
        for(j=0; j<nr_simboluri; j++)
            if(v_simb[j]==string[l+1])
                break;

        if(j==nr_simboluri)
        {
            cout<<"neacceptat";
            return;
        }
        int i2=m[k][i][j];
        if(m[k][i2][j]!=-1)
            bt(k, m[k][i2][j], j, l+1, string, nr_stari_finale, nr_simboluri, v_simb, m, F);
        else
        {
            static int n=0;
            ++n;
            if(n<=l && k<2)
            {
                for(j=0; j<nr_simboluri; j++)
                    if(v_simb[j]==string[l-n])
                        break;
                bt(1, i, j, l-n, string, nr_stari_finale, nr_simboluri, v_simb, m, F);
                bt(2, i, j, l-n, string, nr_stari_finale, nr_simboluri, v_simb, m, F);


            }
        }
    }
    else cout<<"neacceptat";
}

int main()
{
    ifstream f("AFN.in");
    int k, i, j, nr_stari, nr_simboluri, nr_stari_finale, nr, q0;
    int *v_stari, *F;
    char *v_simb;

    f>>nr_stari;
    v_stari= new int[nr_stari];
    for(i=0; i<nr_stari; i++)
        f>>v_stari[i];
    f>>nr_simboluri;
    v_simb= new char[nr_simboluri];
    for(i=0; i<nr_simboluri; i++)
        f>>v_simb[i];
    f>>q0;
    f>>nr_stari_finale;
    F= new int[nr_stari_finale];
    for(i=0; i<nr_stari_finale; i++)
        f>>F[i];
    f>>nr;

    int ***m;
    m=new int**[3];
    for(k=0; k<3; k++)
        m[k]= new int*[nr_stari];

    for(k=0; k<3; k++)
        for(i=0; i<nr_stari; i++)
        {
            m[k][i]= new int[nr_simboluri];
            for(j=0; j<nr_simboluri; j++)
                m[k][i][j]=-1;
        }

    int s;
    char c;
    while(nr)
    {
        f>>i>>c>>s;
        for(j=0; j<nr_simboluri; j++)
            if(v_simb[j]==c)
                break;
        for(k=0; k<3; k++)
            if(m[k][i][j]==-1)
            {
                m[k][i][j]=s;
                break;
            }
        nr--;
    }

    for(k=0; k<3; k++)
    {
        for(i=0; i<nr_stari; i++)
        {
            for(j=0; j<nr_simboluri; j++)
                cout<<m[k][i][j]<<" ";
            cout<<endl;
        }
        cout<<"//////////////////"<<endl;
    }

    cout<<"Introduce cuvantul: ";
    char string[20];
    gets(string);
    cout<<"Cuvantul "<<string<<" este ";

    bt(0,0,0,0,string,nr_stari_finale,nr_simboluri,v_simb,m,F);
    //elibereaza memoria
    return 0;
}
