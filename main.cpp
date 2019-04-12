#include <iostream>
#include <bits/stdc++.h>
#include<limits>
#define wrong -1
#define right -2
using namespace std;

void print(vector<vector<int>> Prime_table,vector<vector<int>> PI,vector<pair<int,bool>> mint_cover)
{
    cout<<endl;
    for(unsigned int i=0; i<mint_cover.size(); i++)
    {
        cout<<mint_cover[i].first<<" "<<mint_cover[i].second;
        cout<<endl;
    }
    for(unsigned int i=0; i<PI.size(); i++)
    {
        for(unsigned int j=0; j<PI[i].size(); j++)
        {
            cout<<PI[i][j]<<" ";
        }
        cout<<endl;
    }
    for(unsigned int i=0; i<Prime_table.size(); i++)
    {
        for(unsigned int j=0; j<Prime_table[i].size(); j++)
        {
            cout<<Prime_table[i][j]<<" ";
        }
        cout<<endl;
    }
}

void remove_repetition(vector<int> &essintials)
{
    for(unsigned int i=0; i<essintials.size(); i++)
    {
        for(unsigned int j=0; j<essintials.size(); j++)
        {
            if(i!=j)
            {
                if(essintials[i]==essintials[j])
                {
                    essintials.erase(essintials.begin()+j);
                    j--;
                }
            }
        }
    }
}

string convert_ess(int index,int v,vector<vector<int>> PI)
{
    string binary;
    for(int j=0; j<PI[index].size()-1; j++)
    {
        for(int i=0; i<v; i++)
        {
            if(j==0)
            {
                char z =PI[index][j]%2;
                binary.push_back(z+48);
                PI[index][j]=PI[index][j]/2;
            }

            else
            {
                for(int x=0; x<v; x++)
                {
                    if(PI[index][j]%2==1)
                    {
                        binary[v-x-1]='X';
                    }
                    PI[index][j]=PI[index][j]/2;
                }
            }
        }
        if(j==0)
            reverse(binary.begin(),binary.end());
    }
    string ess;
    for(int i=0; i<binary.size(); i++)
    {
        if(binary[i]=='1')
        {
            char z='A'+i;
            ess.push_back(z);
        }
        else if(binary[i]=='0')
        {
            char z='A'+i;
            ess.push_back(z);
            z='\'';
            ess.push_back(z);
        }
    }
    return ess;
}

bool check_minterms_covered(vector<pair<int,bool>> mint_cover)
{
    for(int i=0; i<mint_cover.size(); i++)
    {
        if(mint_cover[i].second==false)
            return false;
    }
    return true;
}

bool check_complemet_in_essentials(int i,vector<int> essintials,vector<vector<int>> PI,int v)
{

    for(int w=0; w<essintials.size(); w++)
    {
        int index=essintials[w];
        string binary;
        for(int j=0; j<PI[index].size()-1; j++)
        {
            for(int i=0; i<v; i++)
            {
                if(j==0)
                {
                    char z =PI[index][j]%2;
                    binary.push_back(z+48);
                    PI[index][j]=PI[index][j]/2;
                }
                else
                {
                    for(int x=0; x<v; x++)
                    {
                        if(PI[index][j]%2==1)
                        {
                            binary[v-x-1]='X';
                        }
                        PI[index][j]=PI[index][j]/2;
                    }
                }
            }
            if(j==0)
                reverse(binary.begin(),binary.end());
        }
        if(binary[i]=='0')
            return true;
    }
    return false;
}

bool check_cover(vector<vector<int>> PI,vector<vector<int>> Prime_table,int minterm_index,int pi_index,int v )
{
    int minterm=Prime_table[0][minterm_index];
    string minterm_s;
    string binary;
    int index=Prime_table[pi_index][0];
    for(int i=0; i<v; i++)
    {
        char z =minterm%2;
        minterm_s.push_back(z+48);
        minterm=minterm/2;
    }
    reverse(minterm_s.begin(),minterm_s.end());
    for(int j=0; j<PI[index].size()-1; j++)
    {
        for(int i=0; i<v; i++)
        {
            if(j==0)
            {
                char z =PI[index][j]%2;
                binary.push_back(z+48);
                PI[index][j]=PI[index][j]/2;
            }
            else
            {
                for(int x=0; x<v; x++)
                {
                    if(PI[index][j]%2==1)
                    {
                        binary[v-x-1]='X';
                    }
                    PI[index][j]=PI[index][j]/2;
                }
            }
        }
        if(j==0)
            reverse(binary.begin(),binary.end());
    }
    for(int i=0; i<v; i++)
    {
        if(binary[i]!='X')
        {
            if(binary[i]!=minterm_s[i])
                return false;
        }
    }
    return true;
}

int cost(vector<vector<int>> Prime_table,vector<vector<int>> PI,int v,int index,vector<int> essintials)
{
    int cost=0;
    string binary;
    for(int j=0; j<PI[index].size()-1; j++)
    {
        for(int i=0; i<v; i++)
        {
            if(j==0)
            {
                char z =PI[index][j]%2;
                binary.push_back(z+48);
                PI[index][j]=PI[index][j]/2;
            }
            else
            {
                for(int x=0; x<v; x++)
                {
                    if(PI[index][j]%2==1)
                    {
                        binary[v-x-1]='X';
                    }
                    PI[index][j]=PI[index][j]/2;
                }
            }
        }
        if(j==0)
            reverse(binary.begin(),binary.end());
    }
    int counter=0;
    for(int i=0; i<v; i++)
    {
        if(binary[i]=='0'||binary[i]=='1')
            counter++;
        if(binary[i]=='0')
        {
            if(check_complemet_in_essentials(i,essintials,PI,v))
                cost=cost+1;
            else
                cost=cost+2;
        }
        if(binary[i]=='1')
            cost=cost+1;
    }
    if(counter>1)
        cost++;
    return cost;
}

vector <int > patrick(vector<vector<int>> Prime_table,vector<int> imp,vector<vector<int>> PI,vector<int> essin,int v)
{
    set<int>chosen_pi;
    set<int>ess;
    string esso;
    for(int i=0; i<essin.size(); i++)
    {
        int index=Prime_table[essin[i]][0];
        for(int t=0; t<PI[index].size()-1; t++)
        {
            int pi=PI[index][t];
            for(int y=0; y<v; y++)
            {
                if(t==0)
                {
                    char z =pi%2;
                    esso.push_back(z+48);
                    pi=pi/2;
                }
                else
                {
                    for(int x=0; x<v; x++)
                    {
                        if(pi%2==1)
                        {
                            esso[v-x-1]='X';
                        }
                        pi=pi/2;
                    }
                }
            }
            if(t==0)
                reverse(esso.begin(),esso.end());
        }
        for(int j=0; j<esso.size(); j++)
        {
            if(esso[j]=='0')
                ess.insert(j);
        }
    }

    vector<int>max_pi_for_min;
    max_pi_for_min.push_back(-2);
    int product=1;
    for(int i=1; i<Prime_table[0].size()-1; i++)
    {
        int counter=0;
        for(int j=1; j<Prime_table.size(); j++)
        {
            if(Prime_table[j][i]==right)
            {
                counter++;
            }
        }
        max_pi_for_min.push_back(counter);
        product*=counter;
    }
    vector <int> counter_for_min;
    counter_for_min.push_back(-2);
    for(int i=1; i<Prime_table[0].size()-1; i++)
        counter_for_min.push_back(1);
    int min_cost=INT_MAX;
    imp.clear();
    for(int w=0; w<product; w++)
    {
        int check_taken_comp=0;
        chosen_pi.clear();
        set<int>taken_complement(ess.begin(),ess.end());
        for(int i=1; i<Prime_table[0].size()-1; i++)
        {
            int counter=0;
            for(int j=1; j<Prime_table.size(); j++)
            {
                if(Prime_table[j][i]==right)
                {
                    counter++;
                    if(counter==counter_for_min[i])
                    {
                        int youssef=chosen_pi.size();
                        chosen_pi.insert(j);
                        if(youssef<chosen_pi.size())
                        {

                        string binary;
                        int index=Prime_table[j][0];
                        for(int t=0; t<PI[index].size()-1; t++)
                        {
                            int pi=PI[index][t];
                            for(int y=0; y<v; y++)
                            {
                                if(t==0)
                                {
                                    char z =pi%2;
                                    binary.push_back(z+48);
                                    pi=pi/2;
                                }
                                else
                                {
                                    for(int x=0; x<v; x++)
                                    {
                                        if(pi%2==1)
                                        {
                                            binary[v-x-1]='X';
                                        }
                                        pi=pi/2;
                                    }
                                }
                            }
                            if(t==0)
                                reverse(binary.begin(),binary.end());
                        }
                        for(int t=0; t<binary.size(); t++)
                        {
                            if(binary[t]=='0')
                            {
                                int s=taken_complement.size();
                                taken_complement.insert(t);
                                if(s==taken_complement.size())
                                    check_taken_comp++;
                            }
                        }
                        }

                        if(i==Prime_table[0].size()-2)
                            counter_for_min[i]++;
                        break;
                    }
                }
            }
        }
        int cost=0;
        set<int>::iterator itr=chosen_pi.begin();
        for (itr = chosen_pi.begin(); itr != chosen_pi.end(); itr++)
        {
            cost=cost+Prime_table[ *itr][Prime_table[0].size()-1];
        }
        cost=cost-check_taken_comp;
        if(cost<=min_cost)
        {
            min_cost=cost;
            imp.clear();
            for (itr = chosen_pi.begin(); itr != chosen_pi.end(); itr++)
            {
                imp.push_back(Prime_table[*itr][0]);
            }
        }
        int i=counter_for_min.size()-1;
        while(counter_for_min[i]==max_pi_for_min[i]+1)
        {
            counter_for_min[i]=1;
            i--;
            counter_for_min[i]++;
        }
    }
    return imp;
}

bool column_dominance(vector<vector<int>> Prime_table,vector<pair<int,bool>> &mint_cover)
{
    bool checker=false;
    for(int i=1; i<Prime_table[0].size()-1; i++)
    {
        for(int j=1; j<Prime_table[0].size()-1; j++)
        {
            if(i!=j)
            {
                int counter=0;
                int counter2=0;
                bool check_col_dom=true;
                for(int k=1; k<Prime_table.size(); k++)
                {
                    if(Prime_table[k][j]==right)
                        counter++;
                    if(Prime_table[k][i]==right)
                        counter2++;
                    if(Prime_table[k][j]==right&&Prime_table[k][j]!=Prime_table[k][i])
                    {
                        check_col_dom=false;
                        break;
                    }
                }
                if(check_col_dom)
                {
                    if(counter2>counter)
                    {
                        for(int x=0; x<mint_cover.size(); x++)
                        {
                            if(mint_cover[x].first==Prime_table[0][i])
                            {
                                mint_cover[x].second=true;
                                break;
                            }
                        }
                        checker=true;
                    }
                    else if(counter2==counter&&i<j)
                    {
                        for(int x=0; x<mint_cover.size(); x++)
                        {
                            if(mint_cover[x].first==Prime_table[0][i])
                            {
                                mint_cover[x].second=true;
                                break;
                            }
                        }
                        checker=true;
                    }
                }
            }
        }
    }
    return checker;
}

bool row_dominace(vector<vector<int>> Prime_table,vector <vector<int> > &PI)
{
    bool checker=true;
    bool main_checker=false;
    int couter=0;
    for(int i=1; i<Prime_table.size(); i++)
    {
        for(int j=1; j<Prime_table.size(); j++)
        {
            if(i!=j)
            {
                checker=true;
                couter=0;
                for(int col=1; col<Prime_table[0].size()-1; col++)
                {
                    if(Prime_table[j][col]==right)
                        couter++;
                    if(Prime_table[j][col]==right && Prime_table[i][col]!=Prime_table[j][col])
                    {
                        checker=false;
                        break;
                    }
                }
                if(checker&&(Prime_table[i][Prime_table[0].size()-1]<Prime_table[j][Prime_table[0].size()-1]||couter==0))
                {
                    main_checker=true;
                    PI[Prime_table[j][0]][PI[j].size()-1]=right;
                }
                else if(checker&&(Prime_table[i][Prime_table[0].size()-1]==Prime_table[j][Prime_table[0].size()-1]||couter==0))
                {
                    if(i<j)
                    {
                        main_checker=true;
                        PI[Prime_table[j][0]][PI[j].size()-1]=right;
                    }
                }
            }
        }
    }
    return main_checker;
}

bool remove_essintials(vector<vector<int>> Prime_table,vector<pair<int,bool>> &mint_cover,vector <vector<int> > &PI,vector<int> &essintials)
{
    bool checker=false;
    int counter=0,prime_index;
    for(int i=1; i<Prime_table[0].size(); i++)
    {
        int last_index;
        counter=0;
        for(int j=1; j<Prime_table.size(); j++)
        {
            if(Prime_table[j][i]==right)
            {
                counter++;
                prime_index=Prime_table[j][0];
                last_index=j;
            }
        }
        if(counter==1)
        {
            PI[prime_index][PI[prime_index].size()-1]=right;
            essintials.push_back(prime_index);

            checker=true;
            for(int w=1; w<Prime_table[last_index].size(); w++)
            {

                if(Prime_table[last_index][w]==right)
                {
                    for(int x=0; x<mint_cover.size(); x++)
                    {
                        if(Prime_table[0][w]==mint_cover[x].first)
                        {
                            mint_cover[x].second=true;
                            break;
                        }
                    }
                }
            }
        }
    }
    return checker;
}

vector<vector<int>> get_prime_table(vector <vector<int> > PI,vector<pair<int,bool>>mint_cover,vector<vector<int>> Prime_table,int v,vector<int> essintials)
{
    vector<int> temp;
    temp.push_back(wrong);
    for(int i=0; i<mint_cover.size(); i++)
    {
        if(mint_cover[i].second==false)
            temp.push_back(mint_cover[i].first);
    }
    temp.push_back(-3);
    Prime_table.push_back(temp);
    temp.clear();
    for(int i=0; i<PI.size(); i++)
    {
        if(PI[i][PI[i].size()-1]==wrong)
        {
            temp.push_back(i);
            Prime_table.push_back(temp);
            temp.clear();
        }
    }
    int minterm_index=1,pi_index=1;
    for(minterm_index=1; minterm_index<Prime_table[0].size()-1; minterm_index++)
    {
        for(pi_index=1; pi_index<Prime_table.size(); pi_index++)
        {
            Prime_table[pi_index].push_back(wrong);
            if(check_cover(PI,Prime_table,minterm_index,pi_index,v))
                Prime_table[pi_index][minterm_index]=right;
        }
    }
    pi_index=0;
    for(int i=1; i<Prime_table.size(); i++)
    {
        Prime_table[i].push_back(cost(Prime_table,PI,v,Prime_table[i][0],essintials));
        pi_index++;
    }
    return Prime_table;
}

bool check_existence(vector <int>temp,vector <vector<int> > &minterms)
{
    int col=0,i=minterms[0].size()-1;
    bool exisit=true;
    if(minterms.size()!=temp.size())
        return false;
    while(minterms[temp.size()-1][i]!=-3)
    {
        exisit=true;
        while(minterms[col][i]!=-2&&minterms[col][i]!=-1)
        {
            if(temp[col]!=minterms[col][i])
            {
                exisit=false;
                break;
            }
            col++;
        }
        if(exisit)
            return true;
        i--;
        col=0;
    }
    return false;
}

bool ispowerof2(int n)
{
    int i=1;
    while(n>=i)
    {
        if(n==i)
            return true;
        else
            i=i*2;
    }
    return false;
}

vector <vector<int> > get_prime(vector <vector<int> > &minterms,int v,int n,map<int,int> &a,vector <vector<int> > &PI)
{
    int i=0,j=0,counter=0,endv=minterms[0].size();
    int new_index=endv;
    int col=0;
    vector <int> temp;
    vector<int>temp1;
    while(1)
    {
        if(i!=j&& i!=endv)
        {
            if(a[minterms[0][j]]==a[minterms[0][i]]+1 && minterms[0][j]>minterms[0][i])
            {
                if(ispowerof2(minterms[0][j]-minterms[0][i]))
                {
                    bool compare=true;
                    col=1;
                    while(minterms[col][i]!=wrong&&minterms[col][i]!=right)
                    {
                        if(minterms[col][i]!=minterms[col][j])
                        {
                            compare=false;
                            break;
                        }
                        col++;
                    }
                    if(compare)
                    {
                        temp1.clear();
                        col=0;
                        while(minterms[col][i]!=wrong&&minterms[col][i]!=right)
                        {
                            temp1.push_back(minterms[col][i]);
                            col++;
                        }
                        temp1.push_back(minterms[0][j]-minterms[0][i]);
                        temp1.push_back(wrong);
                        sort(temp1.begin()+1,temp1.end()-1);
                        minterms[col][i]=right;
                        minterms[col][j]=right;
                        if(!check_existence(temp1,minterms))
                        {
                            col=0;
                            for(col=0; col<temp1.size()-1; col++)
                            {
                                minterms[col].push_back(temp1[col]);
                            }
                            if(minterms.size()==temp1.size())
                                minterms[col].push_back(temp1[col]);
                            else
                            {
                                for(int x=0; x<minterms[0].size(); x++)
                                {
                                    if(x==minterms[0].size()-1)
                                        temp.push_back(wrong);
                                    else
                                        temp.push_back(-3);
                                }
                                minterms.push_back(temp);
                                temp.clear();
                            }
                        }
                    }
                }
            }
        }
        if(i<=endv-1)
        {
            if(j==endv-1)
            {
                j=counter;
                i++;
            }
            else
                j++;
        }
        else
        {
            counter=endv;
            endv=minterms[0].size();
            j=counter;
            if(i==endv)
                break;
        }
    }
    temp.clear();
    new_index=1;
    for(i=0; i<minterms[0].size(); i++)
    {
        if(minterms[new_index][i]!=-2&&minterms[new_index][i]!=-1&&i!=minterms.size()-1)
        {
            new_index++;
        }
        if(minterms[new_index][i]==-1)
        {
            for(j=new_index-1; j>=0; j--)
            {
                temp.push_back(minterms[j][i]);
            }
            reverse(temp.begin(),temp.end());
            PI.push_back(temp);
            temp.clear();
        }
    }
    for(unsigned int i=0; i<PI.size(); i++)
    {
        PI[i].push_back(wrong);
    }
    return PI;
}

map<int,int> ones_bin(vector <vector<int> > minterms,int v,int n,map<int,int>a)
{
    int y;
    for(int i=0; i<n; i++)
    {
        a[minterms[0][i]]=0;
        y=minterms[0][i];
        for(int j=0; j<v; j++)
        {
            if(y==1)
            {
                a[minterms[0][i]]++;
                break;
            }
            if(y%2!=0)
                a[minterms[0][i]]++;
            y=y/2;
        }
    }
    return a;
}

int main(int argc, char const *argv[])
{
    int v,n,temp;
    cout << "Enter number of varibales:";
    cin >> v;
    cout << "Enter number of minterms:";
    cin >> n;
    vector <vector<int> > minterms;
    vector <vector<int> > PI;
    vector<int>imp;
    cout << "Enter the minterms:";
    vector<pair<int,bool>>mint_cover;
    for(int i=0; i<n; i++)
    {
        cin >> temp;
        mint_cover.push_back(make_pair(temp,false));
        imp.push_back(temp);
    }
    int d;
    cout << "Enter numbers of don't care:";
    cin>>d;
    if(d!=0)
    {
        cout << "Enter the don't care:";
        for(int  i=0; i<d; i++)
        {
            cin>>temp;
            imp.push_back(temp);
        }
    }
    minterms.push_back(imp);
    imp.clear();
    for(int i=0; i<n+d; i++)
        imp.push_back(wrong);
    minterms.push_back(imp);
    imp.clear();
    map<int,int> ones_in_bin;
    ones_in_bin=ones_bin(minterms,v,n+d,ones_in_bin);
    PI=get_prime(minterms,v,n,ones_in_bin,PI);
    cout<<endl;
    vector<vector<int>> Prime_table;
    vector<int> essintials;
    Prime_table=get_prime_table(PI,mint_cover,Prime_table,v,essintials);
    //print(Prime_table,PI,mint_cover);
    while(1)
    {
        if(remove_essintials(Prime_table,mint_cover,PI,essintials))
        {
            Prime_table.clear();
            Prime_table=get_prime_table(PI,mint_cover,Prime_table,v,essintials);
            //print(Prime_table,PI,mint_cover);
        }
        if(check_minterms_covered(mint_cover))
            break;
        while(row_dominace(Prime_table,PI))
        {
            Prime_table.clear();
            Prime_table=get_prime_table(PI,mint_cover,Prime_table,v,essintials);
            //print(Prime_table,PI,mint_cover);
            if(remove_essintials(Prime_table,mint_cover,PI,essintials))
            {
                Prime_table.clear();
                Prime_table=get_prime_table(PI,mint_cover,Prime_table,v,essintials);
                //  print(Prime_table,PI,mint_cover);
            }
            else
                break;
        }
        if(check_minterms_covered(mint_cover))
            break;
        while(column_dominance(Prime_table,mint_cover))
        {
            Prime_table.clear();
            Prime_table=get_prime_table(PI,mint_cover,Prime_table,v,essintials);
            //print(Prime_table,PI,mint_cover);
            if(remove_essintials(Prime_table,mint_cover,PI,essintials))
            {
                Prime_table.clear();
                Prime_table=get_prime_table(PI,mint_cover,Prime_table,v,essintials);
                //  print(Prime_table,PI,mint_cover);
            }
            while(row_dominace(Prime_table,PI))
            {
                Prime_table.clear();
                Prime_table=get_prime_table(PI,mint_cover,Prime_table,v,essintials);
                //print(Prime_table,PI,mint_cover);
                if(remove_essintials(Prime_table,mint_cover,PI,essintials))
                {
                    Prime_table.clear();
                    Prime_table=get_prime_table(PI,mint_cover,Prime_table,v,essintials);
                    //  print(Prime_table,PI,mint_cover);
                }
                else
                    break;
            }
        }
        if(check_minterms_covered(mint_cover))
            break;
        cout<<endl;
        Prime_table.clear();
        Prime_table=get_prime_table(PI,mint_cover,Prime_table,v,essintials);
        //print(Prime_table,PI,mint_cover);
        imp.clear();
        imp=patrick(Prime_table,imp,PI,essintials,v);
        for(unsigned int i=0; i<imp.size(); i++)
            essintials.push_back(imp[i]);
        break;
    }
    remove_repetition(essintials);
    cout<<"F(";
    for(int i=0; i<v; i++)
    {
        char z=65+i;
        if(i==v-1)
        {
            cout<<z;
            break;
        }
        cout<<z<<",";
    }
    cout<<")=";
    for(unsigned int i=0; i<essintials.size(); i++)
    {
        if(i==essintials.size()-1)
        {
            cout<<convert_ess(essintials[i],v,PI);
            break;
        }
        cout<<convert_ess(essintials[i],v,PI)<<" + ";
    }
    cout<<endl;
    cout<<endl;
    cout<<"to Exit enter 0:";
    cin>>d;
    return 0;
}
