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
    int depth_search(vector<int> & current_keys, vector<bool> & is_visited, int last_chest = -2);
    vector<vector <int>> m_chests;
    vector<vector <int>> m_keys;
    vector<int> m_previous_chests;
    int m_last_chest;
};

#endif // CASESOLVER_H
