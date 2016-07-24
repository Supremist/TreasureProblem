#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <CaseSolver.h>

using std::vector;

std::shared_ptr<vector<int> > inputStartKeys(std::istream & input, int start_key_count)
{
    auto start_keys = std::make_shared <std::vector<int>>(start_key_count);
    for (int i = 0; i<start_key_count; ++i){
        int key;
        input >> key;
        start_keys->at(i) = key - 1;
    }
    return start_keys;
}

std::shared_ptr<CaseSolver> create_solver(std::istream & input, int chest_count){
    vector<vector <int> > chests (chest_count);
    vector<vector <int> > keys;

    for (int i = 0; i<chest_count; ++i){
        int key_type, key_count;
        input >> key_type >> key_count;
        key_type -= 1;
        if(key_type >= keys.size()){
            keys.resize(key_type+1);
        }
        keys[key_type].push_back(i);
        for (int j = 0; j<key_count; ++j){
            int key;
            input >> key;
            chests[i].push_back(key-1);
        }
    }
    return std::make_shared<CaseSolver>(chests, keys);
}


void solve_case(std::istream &input, std::ostream &out)
{
    int start_key_count, chest_count;
    input >> start_key_count >> chest_count;
    auto start_keys = inputStartKeys(input, start_key_count);
    auto solver = create_solver(input, chest_count);
    solver->solve(start_keys);
    if (solver->is_posible()){
        auto path = solver->get_path();
        for (int i = 0; i < path->size(); ++i){
            out << " "<< path->at(i) + 1;
        }
    }
    else{
        out << " IMPOSSIBLE";
    }
}

int main(int argc, char *argv[])
{
    std::ifstream input;
    std::ofstream out;
    input.open("large.txt");
    out.open("output.txt");
    int case_count;
    input >> case_count;
    for (int i = 0; i<case_count; ++i){
        out << "Case #" << i+1 <<":";
        solve_case(input, out);
        out << std::endl;
        out.flush();
    }
    input.close();
    out.close();
    return 0;
}
