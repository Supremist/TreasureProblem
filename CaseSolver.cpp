#include "CaseSolver.h"

CaseSolver::CaseSolver( const vector<vector <int>> & chests, const vector<vector<int>> & keys):
    m_chests(chests)
  , m_keys(keys)
  , m_previous_chests(chests.size(), -1)
  , m_last_chest(-1)
{
}

void CaseSolver::solve(const std::shared_ptr<vector<int> > start_keys)
{
    vector<int> current_keys(m_keys.size(), 0);
    for (int i = 0; i < start_keys->size(); ++i){
        current_keys[start_keys->at(i)]++;
    }
    vector<bool> is_visited(m_chests.size(), false);
    m_last_chest = depth_search(current_keys, is_visited);
}

int CaseSolver::depth_search(vector<int> & current_keys, vector<bool> & is_visited, int last_chest)
{
    for (int i = 0; i < current_keys.size(); ++i){
        if (current_keys[i] > 0){
            for (int j = 0; j < m_keys[i].size(); ++j){
                int new_chest = m_keys[i][j];
                if (!is_visited[new_chest]){
                    vector<int> new_keys (current_keys);
                    --new_keys[i];
                    for (int key = 0; key < m_chests[new_chest].size(); ++key){
                        ++new_keys[m_chests[new_chest][key]];
                    }

                    m_previous_chests[new_chest] = last_chest;
                    vector<bool> new_is_visited(is_visited);
                    new_is_visited[new_chest] = true;

                    auto result = depth_search(new_keys, new_is_visited, new_chest);
                    if (result != -1){
                        return result;
                    }
                }
            }
        }
    }
    for (int i = 0; i < is_visited.size(); ++i){
        if (!is_visited[i])
            return -1;
    }
    return last_chest;
}

bool CaseSolver::is_posible()
{
    return m_last_chest >= 0;
}

std::shared_ptr<vector<int>> CaseSolver::get_path()
{
    auto result = std::make_shared<vector<int>>();
    if(is_posible()){
        int i = m_last_chest;
        while(i >= 0){
            result->insert(result->begin(), i);
            i = m_previous_chests[i];
        }
    }
    return result;
}


