#include "CaseSolver.h"

CaseSolver::CaseSolver( const vector<vector <int>> & chests, const vector<vector<int>> & keys):
    m_chests(chests)
  , m_keys(keys)
  , m_previous_chests(chests.size(), -1)
  , m_last_chest(-1)
  , m_chests_priority(chests.size(), 0)
  , m_needed_keys(keys.size())
{
}

void CaseSolver::solve(const std::shared_ptr<vector<int> > start_keys)
{
    vector<int> current_keys(m_keys.size(), 0);
    for (int i = 0; i < start_keys->size(); ++i){
        current_keys[start_keys->at(i)]++;
    }
    auto all_keys = get_all_keys(current_keys);
    for (int i = 0; i < m_keys.size(); ++i){
        m_needed_keys[i] = m_keys[i].size();
        if (all_keys[i] - m_needed_keys[i] < 0){
            m_last_chest = -1;
            return;
        }
    }


    vector<bool> is_visited(m_chests.size(), false);
    calc_priority();
    m_last_chest = depth_search(current_keys, is_visited);
}

int CaseSolver::depth_search(const vector<int> & current_keys, const vector<bool> & is_visited, int last_chest)
{
    for (int i = 0; i < current_keys.size(); ++i){
        if (current_keys[i] > 0){
            for (int chest: get_openable_chests(i, is_visited)){
                vector<int> new_keys (current_keys);
                --new_keys[i];
                --m_needed_keys[i];

                for (int key: m_chests[chest]){
                    if(new_keys[key] < m_needed_keys[key]){
                        ++new_keys[key];
                    }
                }

                m_previous_chests[chest] = last_chest;
                vector<bool> new_is_visited(is_visited);
                new_is_visited[chest] = true;

                auto result = depth_search(new_keys, new_is_visited, chest);
                if (result != -1){
                    return result;
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

vector<int> CaseSolver::get_openable_chests(int key, const vector<bool> & is_visited)
{
    vector<int> result;
    for (int chest: m_keys[key]){
        if (!is_visited[chest]){
            vector<int>::iterator iter = result.begin();
            while(iter != result.end()
                  && m_chests_priority[*iter] > m_chests_priority[chest]) ++iter;
            result.insert(iter, chest);
        }
    }
    return result;
}

void CaseSolver::calc_priority()
{
    for (int i = 0; i < m_chests.size(); ++i){
        for (int key: m_chests[i]){
            m_chests_priority[i] += m_keys[key].size();
        }
    }
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

std::vector<int> CaseSolver::get_all_keys(const vector<int> & start_keys){
    vector<int> result(start_keys);
    for (auto chest: m_chests){
        for (int key: chest){
            ++result[key];
        }
    }
    return result;
}


