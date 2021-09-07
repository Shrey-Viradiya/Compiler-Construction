// To Find First and Follow of the given grammar

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

int no_of_terminals;
int no_of_non_terminals;
int no_of_productions;

std::string *terminals;
std::string *non_terminals;
std::string starting_symbol;
std::string *productions;

std::map<std::string, std::vector<std::string>> productions_map;
std::map<std::string, std::set<std::string>> FIRST;
std::map<std::string, std::set<std::string>> FOLLOW;

template <typename T>
std::set<T> getUnion(const std::set<T>& a, const std::set<T>& b)
{
  std::set<T> result = a;
  result.insert(b.begin(), b.end());
  return result;
}

std::string getString(char x)
{
    // string class has a constructor
    // that allows us to specify size of
    // string as first parameter and character
    // to be filled in given size as second
    // parameter.
    std::string s(1, x);
 
    return s;  
}

std::vector<std::string> split_production(std::string input, std::string delimiter){
    size_t pos = 0;
    std::string token;
    std::vector<std::string> prods;
    while ((pos = input.find(delimiter)) != std::string::npos) {
        token = input.substr(0, pos);
        prods.push_back(token);
        input.erase(0, pos + delimiter.length());
    }
    prods.push_back(input);
    return prods;
} 

bool is_in_array(std::string s, std::string *array, int size){   
    for (int i = 0; i < size; i++)
    {
        if (array[i] == s)
            return true;
    }
    return false;    
}

std::set<std::string> first(std::string s){
    using namespace std;

    set<string> first_;

    if (is_in_array(s, non_terminals, no_of_non_terminals)){
        vector<string> alternatives = productions_map[s];

        // vector<string>::iterator alternative;

        // for (alternative = alternatives.begin(); alternative != alternatives.end(); ++alternative)
        // {
        //     string temp = *alternative;
        //     set<string> first_2 = first(temp);
        //     first_ = getUnion(first_, first_2);
        // }
        for (int i = 0; i < alternatives.size(); ++i)
        {
            string temp = alternatives[i];
            set<string> first_2 = first(temp);
            first_ = getUnion(first_, first_2);
        }
        
    }
    else if (is_in_array(s, terminals, no_of_terminals)){
        first_ = {s};
    }
    else if (s == "" || s == "@"){
        first_ = {"@"};
    }
    else{
        set<string> first_2 = first(getString(s[0]));
        if (first_2.find("@") != first_2.end())
        {
            int i = 1;
            while (first_2.find("@") != first_2.end())
            {
                set<string> ne = first_2;
                ne.erase("@");
                first_ = getUnion(first_, ne);

                if (is_in_array(s.substr(i), terminals, no_of_terminals))
                {
                    set<string> t = {s.substr(i)};
                    first_ = getUnion(first_, t);
                    break;
                }
                else if (s.substr(i) == "")
                {
                    set<string> t = {"@"};
                    first_ = getUnion(first_, t);
                    break;
                }

                ne = first(s.substr(i));             
                ne.erase("@");
                first_ = getUnion(first_, ne);
                i++;
            }
        }
        else
        {
            first_ = getUnion(first_, first_2);
        }
    } 
    return first_;
}

std::set<std::string> follow(std::string nT){
    using namespace std;

    set<string> follow_;

    if (nT == starting_symbol)
    {
        set<string> dollar = {"$"};
        follow_ = getUnion(follow_, dollar);
    }

    map<string, vector<string>>::iterator itr;
    for (itr = productions_map.begin(); itr != productions_map.end(); ++itr) {
        string nt = itr->first;
        vector<string> rhs = itr->second;

        for(auto alt = rhs.begin();alt!= rhs.end(); ++alt){
            for (int i = 0; i < (*alt).length(); i++)
            {
                if (nT == getString((*alt)[i]))
                {
                    string following_str = (*alt).substr(i+1);
                    if (following_str == "")
                    {
                        if (nT == nt)
                        {
                            continue;
                        }
                        else{
                            follow_ = getUnion(follow_, follow(nt));
                        }
                    }
                    else
                    {
                        set<string> follow_2 = first(following_str);
                        if (follow_2.find("@") != follow_2.end())
                        {
                            set<string> t = follow_2;
                            t.erase("@");
                            follow_ = getUnion(follow_, t);
                            follow_ = getUnion(follow_, follow(nt));
                        }
                        else
                        {
                            follow_ = getUnion(follow_, follow_2);
                        }                        
                    }
                }
            }
        }
    }
    return follow_;    
}

int main(){
    using namespace std;

    // Getting Information About Grammar

    // Terminals

    cout << "Enter no. of terminals: ";
    cin >> no_of_terminals;

    terminals = new string[no_of_terminals];

    cout << "Enter the terminals :" << endl;
    for (int i = 0; i < no_of_terminals; i++)
    {
        cin >> terminals[i];
    } 

    // Non Terminals

    cout << "Enter no. of non terminals: ";
    cin >> no_of_non_terminals;

    non_terminals = new string[no_of_non_terminals];

    cout << "Enter the non terminals :" << endl;
    for (int i = 0; i < no_of_non_terminals; i++)
    {
        cin >> non_terminals[i];
    }

    // Starting Symbol

    cout << "Enter the starting symbol: ";
    cin >> starting_symbol;

    // No of productions

    cout << "Enter the number of productions: ";
    cin >> no_of_productions;

    productions = new string[no_of_productions];
    
    cout << "Enter the productions: ";

    for (int i = 0; i < no_of_productions; i++)
    {
        cin >> productions[i];
        vector<string> temp = split_production(productions[i],"->");
        vector<string> temp2 = split_production(temp[1],"|");
        productions_map.insert(pair<string, vector<string>>(temp[0], temp2));
    }

    map<string, vector<string>>::iterator itr;
    for (itr = productions_map.begin(); itr != productions_map.end(); ++itr) {
        cout << itr->first << " -> " ;
        vector<string>::iterator i;
        for (i = itr->second.begin(); i != itr->second.end(); ++i)
        {
            cout << *i << " ";
        }
        cout << endl;                
    }

    for (int i = 0; i < no_of_non_terminals; i++)
    {
        FIRST[non_terminals[i]]  = {};
        FOLLOW[non_terminals[i]] = {};
    }

    for (int i = 0; i < no_of_non_terminals; i++)
    {
        FIRST[non_terminals[i]]  = getUnion(FIRST[non_terminals[i]], first(non_terminals[i]));
    }

    set<string> dollar = {"$"};
    FOLLOW[starting_symbol] = getUnion(FOLLOW[starting_symbol], dollar);

    for (int i = 0; i < no_of_non_terminals; i++)
    {
        FOLLOW[non_terminals[i]]  = getUnion(FOLLOW[non_terminals[i]], follow(non_terminals[i]));
    }

    cout << "Non Terminals \t First \t\tFollow" << endl;
    for (int i = 0; i < no_of_non_terminals; i++)
    {
        cout << non_terminals[i] << " \t\t " ;
        for (auto itr = FIRST[non_terminals[i]].begin(); itr != FIRST[non_terminals[i]].end(); ++itr)
        {
            cout << *itr << " " ;
        }
        cout << "\t\t" ;
        for (auto itr = FOLLOW[non_terminals[i]].begin(); itr != FOLLOW[non_terminals[i]].end(); ++itr)
        {
            cout << *itr << " " ;
        }
        cout << endl;
    }

    return 0;
}

// Input to check
// 5
// +
// *
// a
// (
// )
// 5
// E
// B
// T
// Y
// F
// E
// 5
// E->TB
// B->+TB|@
// T->FY
// Y->*FY|@
// F->a|(E)