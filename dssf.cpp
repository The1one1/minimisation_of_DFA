#include <bits/stdc++.h>
using namespace std;

#define N_state 100
class DFA_inputs
{
public:
    int no_of_states, no_of_inputs, no_of_final_states;
    char start_state;
    vector<char> final_states;
    vector<char> inputs;
    vector<char> states;
    map<char, map<char, char>> dfa;
    DFA_inputs(int n, int m) //constructor
    {
        no_of_states = n;
        no_of_inputs = m;
    }

    vector<vector<char>> equilance_sets; //set of non-final states and final states
    map<char, int> state_to_index;       // map of state to index
    void NonFinal_States()               //set of non-final states
    {
        vector<char> non_final_states;
        for (auto it : states)
        {
            if (find(final_states.begin(), final_states.end(), it) == final_states.end())
            {
                non_final_states.push_back(it);
            }
        }
        equilance_sets.push_back(non_final_states); //push set of non-final states
        equilance_sets.push_back(final_states);     // push set of final states
        for (int i = 0; i < no_of_states; i++)      // map of state to index
        {
            state_to_index[states[i]] = i;
        }
    }

    void add_transition(char s, char i, char d) //add transition
    {
        dfa[s][i] = d;
    }

    void print_dfa() //print dfa
    {
        for (auto i : inputs)
        {
            cout << "   |" << i;
        }
        cout << "\n--------------\n";
        for (auto i : dfa)
        {
            cout << i.first << " ";
            for (auto j : i.second)
            {
                cout << " |" << j.second << "  ";
            }
            cout << "\n--------------\n";
        }
    }
};

class DFA_minimisation : public DFA_inputs
{
public:
    DFA_minimisation(int n, int m) : DFA_inputs(n, m) {}

    bool DFA_Equivalent_States(char s, char i) //check if two states are equivalent
    {

        if (find(equilance_sets[0].begin(), equilance_sets[0].end(), s) == equilance_sets[0].end() && find(equilance_sets[1].begin(), equilance_sets[1].end(), i) == equilance_sets[1].end())
        {
            return true;
        }
        else if (find(equilance_sets[0].begin(), equilance_sets[0].end(), i) == equilance_sets[0].end() && find(equilance_sets[1].begin(), equilance_sets[1].end(), s) == equilance_sets[1].end())
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool matrix[N_state][N_state];                  //matrix of equivalence
    int no_of_false_blocks;                         //number of false blocks
    void get_equilance_classes(vector<char> states) //get equivalence classes
    {
        no_of_false_blocks = 0;
        for (int i = 0; i < states.size(); i++) //initialise matrix
        {
            for (int j = 0; j < states.size(); j++)
            {
                matrix[i][j] = false;
                no_of_false_blocks++;
            }
        }
        no_of_false_blocks = no_of_false_blocks - states.size();
        for (int i = 0; i < states.size(); i++) //add transitions
        {
            for (int j = 0; j < states.size(); j++)
            {
                if (i == j)
                {
                    continue;
                }
                else
                {
                    //check if two states are equivalent so that we can add true or false in matrix
                    matrix[i][j] = DFA_Equivalent_States(states[i], states[j]);
                    if (matrix[i][j] == true)
                    {
                        no_of_false_blocks--;
                    }
                }
            }
        }
        no_of_false_blocks /= 2;
        int y = 0;
        while (no_of_false_blocks > 0)
        {
            int x = no_of_false_blocks;
            for (int i = 0; i < states.size(); i++)
            {
                for (int j = 0; j < states.size(); j++)
                {
                    if (i >= j)
                    {
                        continue;
                    }
                    else
                    {
                        for (int k = 0; k < inputs.size(); k++)
                        {
                            if (matrix[i][j] == false)
                            {
                                matrix[i][j] = matrix[i][j] || matrix[state_to_index[dfa[states[i]][inputs[k]]]][state_to_index[dfa[states[j]][inputs[k]]]];
                                if (matrix[i][j] == true)
                                {
                                    matrix[j][i] = true;
                                    no_of_false_blocks--;
                                }
                            }
                        }
                    }
                }
            }
            if (x == no_of_false_blocks)
            {
                y++;
                if (y >= states.size())
                {
                    break;
                }
            }
        }
        cout<<"no_of_false:"<<no_of_false_blocks<<endl;
    }

    set<string> optimise_states;
    vector<string> s2;
    void optimize_states()
    {
        string kl, kl1;
        for (int i = 0; i < states.size(); i++)
        {
            for (int j = 0; j < states.size(); j++)
            {
                if (i >= j)
                {
                    continue;
                }
                else if (matrix[i][j] == false)
                {
                    string s;
                    s += states[i];
                    s += states[j];
                    optimise_states.insert(s);
                    s.clear();
                }
            }
        }
        for (auto it : optimise_states)
        {
            s2.push_back(it);
        }
    }
    vector<string> union_of_dfa_minimised;
    set<char> s;
    void union_of_optimise_states()    //union to merge equivalent states
    {
        if (optimise_states.size() >= 3)
        {
            for (auto i = 0; i < optimise_states.size() - 2; i++)
            {
                for (int j = i + 1; j < optimise_states.size() - 1; j++)
                {
                    for (int k = j + 1; k < optimise_states.size(); k++)
                    {
                        for (int kll = 0; kll < s2[i].size(); kll++)
                        {
                            s.insert(s2[i][kll]);
                        }
                        for (int kll = 0; kll < s2[j].size(); kll++)
                        {
                            s.insert(s2[j][kll]);
                        }
                        for (int kll = 0; kll < s2[k].size(); kll++)
                        {
                            s.insert(s2[k][kll]);
                        }
                        if (s.size() == 3)
                        {
                            string s1;

                            for (auto it : s)
                            {
                                s1 += it;
                            }
                            union_of_dfa_minimised.push_back(s1);
                            s.clear();
                        }
                        s.clear();
                    }
                }
            }
        }
        else
        {
            for (auto i = 0; i < optimise_states.size(); i++)
            {
                union_of_dfa_minimised.push_back(s2[i]);
            }
        }
    }

    void final_minimised_dfa()
    {
        int x = optimise_states.size();
        if (union_of_dfa_minimised.empty())
        {
            for (auto it : s2)
            {
                union_of_dfa_minimised.push_back(it);
            }
        }
        else
        {
            for (auto it : s2)
            {
                if (find(union_of_dfa_minimised[0].begin(), union_of_dfa_minimised[0].end(), it[0]) == union_of_dfa_minimised[0].end())
                {
                    union_of_dfa_minimised.push_back(it);
                }
            }
        }
    }
    void final_minimised_dfa2()    //for printing the final dfa
    { 
        int t = 0;
        int x = union_of_dfa_minimised.size();
        for (auto it : states)
        {
            t = 0;
            for (int i = 0; i < x; i++)
            {
                string sl = union_of_dfa_minimised[i];
                auto kll = find(sl.begin(), sl.end(), it);
                if (kll == sl.end())
                {
                    t++;
                }
            }
            if (t == x)
            {
                string kk;
                kk += it;
                union_of_dfa_minimised.push_back(kk);
                t = 0;
            }
        }
    }

    void print_union_of_dfa_minimised() //for printing the minimise final dfa
    {
        cout << "\n-------------------------------------------" << endl;
        cout << "states of DFA after minimisation:: ";
        for (auto i = 0; i < union_of_dfa_minimised.size(); i++)
        {
            cout << union_of_dfa_minimised[i] << " , ";
        }
        cout << endl;
        cout << "-------------------------------------------" << endl;
    }

    void final_minimised_transition_table()       //for printing the final transition table
    { 
        map<string, map<char, string>> dfa_minimised_2_map;
        for (int i = 0; i < union_of_dfa_minimised.size(); i++)
        {
            for (auto ii : inputs)
            {
                auto temp = union_of_dfa_minimised[i][0];
                auto it = dfa[temp][ii];
                for (auto itt : union_of_dfa_minimised)
                {
                    string sl = itt;
                    auto kll = find(sl.begin(), sl.end(), it);
                    if (kll != sl.end())
                    {
                        dfa_minimised_2_map[union_of_dfa_minimised[i]][ii] = sl;
                        break;
                    }
                }
            }
        }

        cout << "\nTransition table:\n";
        cout << setw(11) << " | ";
        for (auto it : inputs)
        {
            cout << setw(8) << it << " | ";
        }
        cout << endl;
        cout << "-------------------------------------------" << endl;
        for (auto it : dfa_minimised_2_map)
        {
            cout << setw(8) << it.first << " | ";
            for (auto i : it.second)
                cout << setw(8) << i.second << " | ";
            cout << endl;
            cout << "-------------------------------------------" << endl;
        }
    }

    void print_final_states()
    {
        set<string> ss;
        cout << "\n-------------------------------------------" << endl;
        cout << "Final State of DFA after minimisation:: ";
        for (auto it : final_states)
        {
            for (auto i : union_of_dfa_minimised)
            {
                auto kll = find(i.begin(), i.end(), it);
                if (kll != i.end())
                {
                    ss.insert(i);
                }
            }
        }
        for (auto it : ss)
        {
            cout << it << " , ";
        }
        cout << "\n-------------------------------------------" << endl;
    }
};

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n, m;
    cout << "Enter the number of states: ";
    cin >> n;
    cout << "\nEnter the number of inputs: ";
    cin >> m;
    cout << "\nEnter the states: ";
    DFA_minimisation dfa(n, m);
    for (int i = 0; i < n; i++) //enter states
    {
        char c;
        cin >> c;
        dfa.states.push_back(c);
    }
    cout << "\nEnter the inputs: ";
    for (int i = 0; i < m; i++) // enter inputs
    {
        char c;
        cin >> c;
        dfa.inputs.push_back(c);
    }
    cout << "\nEnter the start state: ";
    cin >> dfa.start_state;
    cout << "\nEnter the number of final states: ";
    cin >> dfa.no_of_final_states;

    cout << "\nEnter the final states: ";
    for (int i = 0; i < dfa.no_of_final_states; i++) // enter final states
    {
        char c;
        cin >> c;
        dfa.final_states.push_back(c);
    }

    cout << "\nEnter the transitions:\n";
    for (int i = 0; i < n; i++) // add transitions
    {
        for (int j = 0; j < m; j++)
        {
            char d;
            cin >> d;
            dfa.add_transition(dfa.states[i], dfa.inputs[j], d);
        }
    }
    dfa.NonFinal_States();
    dfa.print_dfa();
    dfa.get_equilance_classes(dfa.states);
    dfa.optimize_states();
    dfa.union_of_optimise_states();
    dfa.final_minimised_dfa();
    dfa.final_minimised_dfa2();
    dfa.print_union_of_dfa_minimised();
    dfa.final_minimised_transition_table();
    dfa.print_final_states();
    return 0;
}
