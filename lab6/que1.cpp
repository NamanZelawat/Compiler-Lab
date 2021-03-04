#include<bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(i=a;i<b;i++)
#define sz(s) (int)s.size()
#define pb push_back
#define ff first
#define ss second
#define vs vector<string>
#define pcvs pair<char, vector<string>>

#define eps '~'
#define width 15

class Grammar
{
    public:
    
    vector<char> terminals;
    map< char, vector<string> > g;
    char start;
    char aux; // provide auxiallary terminals
    
    void input()
    {
        cout<<"Enter the Grammar\n";
        cout<<"Number of productions : ";
        int n,i;
        start = eps;
        aux = 'Z';
        cin>>n;
        
        string s;
        getline(cin, s);
        cout<<"Enter productions ( LHS RHS ):\n";
        
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
    
    
    void rem_left_recur(pcvs p )
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
            for(auto x : b )
            {
                string s = x; s.pb(aux);
                temp.ss.pb(s);
            }
            
            // adding
            terminals.pb(temp.ff);
            g[temp.ff] = temp.ss;
            
            temp.ff = aux;
            temp.ss.clear();
            for(auto x : a )
            {
                string s = x; s.pb(aux);
                temp.ss.pb(s);
            }
            
            temp.ss.pb("~");
            
            //adding
            terminals.pb(temp.ff);
            g[temp.ff] = temp.ss;
            
            aux--; // update aux
        }
        else
        {
            //adding
            terminals.pb(p.ff);
            g[p.ff] = p.ss;
        }
        
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
    
    
    // void rem_left_factoring()
};


class FirstAndFollow: public Grammar
{
    public:
    
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
                        if (i != sz(y)-1) temp = cal_first( string( y.begin()+i+1, y.end() ) );
                        if (i == sz(y)-1 || temp.find(eps)!=temp.end() )
                        {
                            temp.erase(eps);
                            for(auto ele : temp) follow.insert(ele);
                            if ( terminal != x ) temp = cal_follow(x);
                            for(auto ele : temp) follow.insert(ele);
                        }
                        else { for(auto ele : temp) follow.insert(ele); }
                    }
                }
            }
        }
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
        cout<<"\nParser Running ...\n\n";
        
        while(1)
        {
            string s;
            cout<<"Enter String : ";
            cin>>s;
            if ( eval(s) ) cout<<"Successfully Parsed.\n";
            else cout<<"Parsing Failed.\n";
        }
    }
};

int main()
{
    LR1 test;
    test.input();
    test.display();
    test.verify();
    test.build_table();
    test.display_table();
    test.run();
}