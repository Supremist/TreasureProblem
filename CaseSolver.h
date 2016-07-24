#ifndef CASESOLVER_H
#define CASESOLVER_H

#include <vector>
#include <memory>
#include <iostream>

using std::vector;

class CaseSolver
{
public:
    CaseSolver( const vector<vector <int>> & chests, const vector<vector<int>> & keys);
    void setStartKeys(const vector<int> & start_keys);
    void solve(const std::shared_ptr<vector<int> > start_keys);
    bool is_posible();
    std::shared_ptr<vector<int>> get_path();

private:
    int depth_search(const vector<int> & current_keys, const vector<bool> & is_visited, int last_chest = -2);
    vector<int> get_openable_chests(int key, const vector<bool> & is_visited);
    void calc_priority();
    vector<int> get_all_keys(const vector<int> & start_keys);

    vector<vector <int>> m_chests;
    vector<vector <int>> m_keys;
    vector<int> m_previous_chests;
    int m_last_chest;
    vector<int> m_chests_priority;
    vector<int> m_needed_keys;
};

#endif // CASESOLVER_H
