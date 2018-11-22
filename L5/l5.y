%{
    #define YYSTYPE string
    #include <bits/stdc++.h>
    using namespace std;
    #define pb push_back
    void yyerror(string s);
    int yylex(void);
    extern int yydebug;

    map<string, vector<vector<string>>> productions;
    map<string, int> string_to_index;
    vector<string> temp_prod;
    vector<string> index_to_string;
    int num_orig_non_terms;
    int counter;
    vector<vector<string>> temp_prods; 
    set<string> nullables_left;
    map<string, bool> rem_epsilon_done;
    bool is_nullable;
    bool possible;
%}

%start GRAMMAR
%token TERM NON_TERM

%%

GRAMMAR     :   RULES
            ;

RULES   :   RULES RULE
        |   RULE
        ;

RULE    :   NON_TERM ':' PRODUCTIONS ';'
        {
            productions[$1] = temp_prods; 
            rem_epsilon_done[$1] = false;

            if(is_nullable == true)
            {
                nullables_left.insert($1);
                rem_epsilon_done[$1] = true;
            }

            temp_prods.clear(); 
            is_nullable = false;
        }
        ;

PRODUCTIONS :   PRODUCTIONS '|' PRODUCTION  {if(temp_prod[0] != string("$")) temp_prods.pb(temp_prod); temp_prod.clear();}
            |   PRODUCTION                  {if(temp_prod[0] != string("$")) temp_prods.pb(temp_prod); temp_prod.clear();}
            ;

PRODUCTION  :   '$'     {is_nullable = true; temp_prod.pb(string("$"));}
            |   ALPHA
            ;

ALPHA   :   ALPHA NON_TERM      {temp_prod.pb($2);}
        |   ALPHA TERM          {temp_prod.pb($2);}
        |   NON_TERM            {temp_prod.pb($1);}
        |   TERM                {temp_prod.pb($1);}
        ;

%%

void yyerror(string s) {
    fprintf(stdout, "Invalid\n");
    exit(0);
}

void print_productions()
{
    for(auto x : productions)
    {
        cout<<x.first<<" : ";
        for(auto y : productions[x.first])
        {
            for(auto s : y)
                cout<<" "<<s;
            cout<<" |";
        }
        cout<<"\b;\n";
    }
}

void rem_epsilon(string head, string eps)
{
    set<vector<string>> cur_prods;
    vector<vector<string>> giv_prods = productions[head];

    vector<string> temp1, temp2;
    vector<int> locations;
    int i,j,n;

    for(auto prod : giv_prods)
    {
        locations.clear();
        temp1 = prod;
        bool present[temp1.size()];

        for(i=0; i<temp1.size(); i++)
            if(temp1[i] == eps)
                locations.pb(i);

        n = 1 << (locations.size());

        for(i=0; i<n; i++)
        {
            memset(&present, 1, sizeof(present));
            for(j=0; j<locations.size(); j++)
                if((i>>j)%2 == 1)
                    present[locations[j]] = false;
            temp2.clear();

            for(j=0; j<temp1.size(); j++)
                if(present[j])
                    temp2.pb(temp1[j]);

            if(temp2.size() != 0)
            {
                if(!(temp2.size() == 1 && temp2[0] == head))
                    cur_prods.insert(temp2);
            }
            else if(rem_epsilon_done[head] == false)
            {
                rem_epsilon_done[head] = true;
                nullables_left.insert(head);
            }
        }
    }

    giv_prods.clear();
    for(auto v : cur_prods)
        giv_prods.pb(v);
    productions[head] = giv_prods;
}

void rem_epsilon_productions()
{
    string eps;
    while(!nullables_left.empty())
    {
        eps = *nullables_left.begin();
        nullables_left.erase(nullables_left.begin());
        for(auto x : productions)
            rem_epsilon(x.first, eps);
    }

    for(auto x : productions)   // to remove S->S
        rem_epsilon(x.first, string("Seeman"));
}

//////////////////////////////////////////////////////

void init_left_recurse()
{
    for(auto x : productions)
        index_to_string.pb(x.first);
    num_orig_non_terms = index_to_string.size();
    counter = 0;

    cout<<"\n inside init_left_recurse .... printing contents of index_to_string :- \n";
    for(int i=0; i<index_to_string.size(); i++)
        cout<<i<<" "<<index_to_string[i]<<endl;
    cout<<"...\n\n";
}

void left_recurse_helper(string head, string toreplace)
{
    vector<vector<string>> giv_prods = productions[head];
    vector<string> cur_prod, temp;
    int i,j;
    for(i=0; i<giv_prods.size(); i++)
    {
        cur_prod = giv_prods[i];
        
        if(cur_prod[0] == toreplace)
        {
            cur_prod.erase(cur_prod.begin());
            for(auto v : productions[toreplace])
            {
                temp = cur_prod;
                temp.insert(temp.begin(), v.begin(), v.end());
                giv_prods.pb(temp);
            }

            giv_prods.erase(giv_prods.begin()+i);
            i--;
            // break;
        }
    }

    set<vector<string>> tempset;
    for(auto v : giv_prods)
        tempset.insert(v);
    giv_prods.clear();
    for(auto v : tempset)
        giv_prods.pb(v);

    productions[head] = giv_prods;
}

void left_recurse_helper2(string head)
{
    int c1=0, c2=0;
    vector<vector<string>> giv_prods = productions[head];
    vector<vector<string>> cur_prods, new_prods;
    vector<string> temp;

    for(auto v : giv_prods)
    {
        if(v[0] == head)
        {
            if(v.size() != 1)
            c1++;
        }
        else
        c2++;
    }

    // if(c1 == 0 && c2 == 0)
    // {
    //     possible = false;
    //     break;
    // } doubt

    // if(c1 == 0)
    //     return;

    // if(c1 != 0 && c2 == 0)
    // {
    //     possible = false;
    //     return;
    // } 


    counter++;
    string new_term = string("CS16B107") + to_string(counter);

    for(auto v : giv_prods)
    {
        if(v[0] == head)
        {
            if(v.size() != 1)
            {
                temp.assign(v.begin()+1, v.end());
                temp.pb(new_term);
                new_prods.pb(temp);
            }
        }
        else
        {
            temp.assign(v.begin(), v.end());
            temp.pb(new_term);
            cur_prods.pb(temp);
        }
    }
    temp.clear();
    temp.pb(string("$"));
    new_prods.pb(temp);

    productions[head] = cur_prods;
    productions[new_term] = new_prods;

}

void left_recurse_wrapper()
{
    init_left_recurse();

    int i,j;
    for(i=0; i<num_orig_non_terms; i++)
    {
        for(j=0; j<i; j++)
        {
            cout<<"\nleft_recurse_helper(i = "<<i<<" = "<<index_to_string[i]<<" , j = "<<j<<" = "<<index_to_string[j]<<" ) \n";
            left_recurse_helper(index_to_string[i], index_to_string[j]);
            print_productions();
        }
        cout<<"\nleft_recurse_helper2(i = "<<i<<" = "<<index_to_string[i]<<" )\n";
        left_recurse_helper2(index_to_string[i]);
        print_productions();
    }

    //doubt be careful
    for(auto x : productions)   // to remove S->S
        rem_epsilon(x.first, string("Seeman"));

    vector<string> temp;
    vector<vector<string>> cur_prods;
    temp.pb(string("$"));
    if(rem_epsilon_done["S"] == true)
    {
        cur_prods = productions["S"];
        cur_prods.pb(temp);
        productions["S"] = cur_prods;
    }

    cur_prods.clear();
    cur_prods.pb(temp);
    for(auto x : productions)
        if(x.second.size() == 0 && rem_epsilon_done[x.first] == true)
            productions[x.first] = cur_prods;
}

////////////////////////////////////////////

int main(void) 
{
    yydebug = 1;
    is_nullable = false;
    possible = true;
    temp_prods.clear();
    temp_prod.clear();

    yyparse();
    print_productions();

    cout<<"\n-----\n";
    rem_epsilon_productions();
    print_productions();

    cout<<"\n-----\n";
    cout<<"executing left_recurse_wrapper\n";



    cout<<"\n-----\n";
    left_recurse_wrapper();
    print_productions();

    if(possible)
        cout<<"\nPOSSIBLE\n";
    else
        cout<<"\nNOT POSSIBLE\n";

    for(auto s : rem_epsilon_done)
    {
        cout<<s.first<<" "<<s.second<<endl;
    }

    return 0;
}

