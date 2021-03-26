#include<bits/stdc++.h>

using namespace std;

/*

S ------> cAd
A ------> ab | a


TESTS
cad
cabd

*/

#define rep(i,a,b) for(i=a;i<b;i++)
#define sz(s) (int)s.size()
#define pb push_back
#define ff first
#define ss second
#define vs vector<string>
#define pcvs pair<char, vector<string>>

#define eps '~'
#define width 15

int r= 5;

class Grammar
{
    public:
    
    vector<char> terminals;
    map< char, vector<string> > g;
    char start;
    char aux; // provide auxiallary terminals
    
    void input()
    {
        cout<<"Give the number of productions --- ";
        int n,i;
        start = eps;
        aux = 'Z';
        cin>>n;
        
        string s;
        getline(cin, s);
        cout<<"Give productions ---\n";
        
        rep(i,0,n)
        {
            string s;
            getline(cin, s);
            pcvs a = decode(s);
            rem_left_recur(a);
        }
    }
    
    pcvs decode(string s)
    {
        vector<string> b;
        char t = eps;
        string temp = "";
        for(auto c : s)
        {
            if (c == ' ') continue;
            if (t == eps) { t = c; if (start == eps) start = t; }
            else if (c == '|' && sz(temp) > 0 ) { b.pb(temp); temp = "";}
            else temp.pb(c);
        }
        if (sz(temp) >0) b.pb(temp);
        return {t,b};
    }
    
    
    void rem_left_recur(pcvs p)
    {
        vector<string> a,b;
        for(auto y : p.ss)
        {
            if ( y[0] == p.ff ) a.pb( string(y.begin()+1,y.end()) );
            else b.pb(y);
        }
        
        if (sz(a) != 0)
        {
            pcvs temp;
            temp.ff = p.ff;
            
            char auxs = aux; aux--;
            
            for(auto x : b )
            {
                string s = x; s.pb(auxs);
                temp.ss.pb(s);
            }

            rem_left_factoring( temp );
            temp.ff = auxs;
            temp.ss.clear();

            for(auto x : a )
            {
                string s = x; s.pb(auxs);
                temp.ss.pb(s);
            }

            temp.ss.pb("~");
            rem_left_factoring( temp );
        }
        else rem_left_factoring( p );
    }
    
    void rem_left_factoring( pcvs p )
    {
        int i,j,k;
        rep(i,0, sz(p.ss) )
        rep(j,i+1,sz(p.ss))
        {
            
            string fx = lar_fx( p.ss[i], p.ss[j] );
            if ( sz(fx) == 0 ) continue;
            
            pcvs a,b;
            a.ff = p.ff;
            rep(k,0,sz(p.ss))
                if (k !=i && k != j )
                    a.ss.pb( p.ss[k] );
            string temp = fx; temp.pb(aux);
            a.ss.pb(temp);
            
            b.ff = aux;
            
            if ( sz(fx) == sz(p.ss[i]) ) b.ss.pb("~");
            else b.ss.pb(  string( p.ss[i].begin()+sz(fx), p.ss[i].end() )  );
            
            if ( sz(fx) == sz(p.ss[j]) ) b.ss.pb("~");
            else b.ss.pb(  string( p.ss[j].begin()+sz(fx), p.ss[j].end() )  );
            
            
            aux--;
            rem_left_factoring(a);
            terminals.pb(b.ff);
            g[b.ff] = b.ss;
            return;
        }
        terminals.pb(p.ff);
        g[p.ff] = p.ss;
        return;
        
    }
    
    string lar_fx( string a, string b )
    {
        string s = "";
        int i,j;
        i = j = 0;
        while( i < sz(a) && j < sz(b) && a[i] == b[j]) 
        { s.pb(a[i]);i++; j++;}
        return s;
    }
    
    void display()
    {
        for( auto x : terminals)
        {
            cout<<x<<" ";
            for(auto y : g[x]) cout<<y<<" ";
            cout<<'\n';
        }
    }

};


class FirstAndFollow: public Grammar
{
    public:
    
    set<char> fstack;
    
    set<char> cal_first(string s)
    {
        set<char> first;
        for(auto c : s)
        {
            first.erase(eps);
            if ( g.find(c) == g.end()  ) first.insert(c);
            else
            {
                for(auto y : g[c] )
                {
                    set<char> temp = cal_first(y);
                    for(auto ele : temp) first.insert( ele );
                }
            }
            if ( first.find(eps) == first.end() ) break;
        }
        return first;
    }
    
    set<char> cal_follow(char terminal)
    {
        fstack.insert(terminal);
        
        set<char> follow;
        int i;
        if (terminal == start) follow.insert('$');
        for(auto x : terminals )
        {
            for(auto y : g[x])
            {
                rep(i,0,sz(y))
                {
                    set<char> temp;
                    if ( y[i] == terminal )
                    {
                        if (i != sz(y)-1)
                        temp = cal_first( string( y.begin()+i+1, y.end() ) );
                        if (i == sz(y)-1 || temp.find(eps)!=temp.end() )
                        {
                            temp.erase(eps);
                            for(auto ele : temp) follow.insert(ele);
                            if ( fstack.find(x) == fstack.end() ) temp = cal_follow(x);
                            for(auto ele : temp) follow.insert(ele);
                        }
                        else { for(auto ele : temp) follow.insert(ele); }
                    }
                }
            }
        }
        fstack.erase(terminal);
        return follow;
    }
    
    void verify()
    {
        cout<<"\nFirst : \n";
        for(auto x : terminals)
        {
            string t; t.pb(x);
            set<char> s = cal_first(t);
            cout<<x<<": ";
            for(auto ele : s) cout<<ele<<" ";
            cout<<'\n';
        }
        
        cout<<"\nFollow : \n";
        for(auto x : terminals)
        {
            string t; t.pb(x);
            set<char> s = cal_follow(x);
            cout<<x<<": ";
            for(auto ele : s) cout<<ele<<" ";
            cout<<'\n';
        }
    }
};

class LR1: public FirstAndFollow
{
    public:
    
    vector<char> non_ts;
    map< char, map<char,string> > table;
    
    void build_table()
    {
        for(auto x : terminals)
        {
            for(auto y : g[x])
            {
                set<char> first = cal_first(y);
                for(auto nt : first)
                {
                    if (nt == eps)
                    {
                        set<char> follow = cal_follow(x);
                        for(auto nt2:follow)
                        {
                            if ( sz(table[x][nt2]) != 0 )
                            {
                                cout<<"Not LL1 Grammar\n";
                                exit(1);
                            }
                            table[x][nt2] = y; 
                        }
                    }
                    else
                    {
                        if( sz(table[x][nt]) != 0 )
                        {
                            cout<<"Not LL1 Grammar\n";
                            exit(1);
                        }
                        table[x][nt] = y; 
                    }
                }
                
            }
        }
    }
    
    void cal_non_ts()
    {
        for(auto x : terminals)
        for(auto y : g[x])
        for(auto ele : y)
            if ( g.find(ele) == g.end() && ele != eps )
                non_ts.pb(ele);
        non_ts.pb('$');
        set<char> s;
        for(auto x : non_ts)
        {
            s.insert(x);
        }
        non_ts.clear();
        for(auto x : s)
        {
            non_ts.push_back(x);
        }
        sort(non_ts.rbegin(),non_ts.rend());
    }
    
    void display_table()
    {
        cal_non_ts();
        cout<<"\nTable : \n";
        cout << left << setw(width) << " ";

        for(auto x : non_ts) cout << left << setw(width) <<x;
        cout<<'\n';
        for(auto x : terminals)
        {
            cout << left << setw(width) <<x;
            for(auto y : non_ts)
            {
                if (sz(table[x][y]) == 0 ) 
                { cout << left << setw(width)<<""; continue; }
                string temp; temp.pb(x);
                temp += " -> " + table[x][y];
                cout << left << setw(width)<<temp;
            }
            cout<<'\n';
        }
    }
    
    bool eval(string s)
    {
        s.pb('$');
        stack<char> st;
        st.push('$'); st.push(start);
        
        int i = 0;
        
        while( sz(st) > 1 )
        {
            if ( st.top() == s[i] )
            {
                st.pop();
                i++;
            }
            else
            {
                string temp = table[ st.top() ][ s[i] ];
                if ( sz(temp)==0 ) return false;
                string temp2; temp2.pb( st.top() );
                temp2 += " -> " + temp;
                cout << temp2 << '\n';
                st.pop();
                if ( temp[0] != eps )
                    for(int j = sz(temp)-1; j>=0;j--)
                        st.push(temp[j]);
            }
        }
        return true;
    }
    
    void run()
    {   
        while(1)
        {
            string s;
            cout<<"\nEnter String : ";
            cin>>s;
            if ( eval(s) ) cout<<"Parsed.\n";
            else cout<<"Failed.\n";
        }
    }
};

int main()
{
    LR1 test;
    test.input();
    test.build_table();
    test.run();
}





//test.display();
// test.verify();
//test.display_table();