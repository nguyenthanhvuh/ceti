#ifndef CONCOLIC_SEARCH_H__  
#define CONCOLIC_SEARCH_H__  
                
#include "sym.h"

namespace crest{
  class Search{
  public:
    Search(const string &, const int &);
    virtual ~Search();
    virtual bool run() = 0;

  protected:

    vector<branch_id_t> branches_;
    vector<branch_id_t> paired_branch_;
    vector<function_id_t> branch_function_;
    vector<unsigned int> branch_count_;

    vector<bool> covered_branches_;
    unsigned int n_covered_branches_;

    vector<bool> reached_functions_; 
    unsigned int n_reachable_functions_;
    unsigned int n_reachable_branches_;

    vector<bool> total_covered_branches_;
    unsigned int total_n_covered_branches_;


    void print_protected_members();
    bool SolveAtBranch(const SymExec &, const size_t &, vector<value_t> *);
    bool CheckPrediction(const SymExec &, const SymExec &, const size_t &);

    bool RunProgram(const vector<value_t> &, SymExec *);
    bool UpdateCoverage(const SymExec &);
    bool UpdateCoverage(const SymExec &, set<branch_id_t> *);

  private:
    const string prog_;
    const int max_iters_;
    int num_iters_;
    const string goal = "GOAL!\n";

    void WriteCoverageToFile();
    void WriteInputToFile(const vector<value_t>&);
  };

  class BoundedDepthFirstSearch : public Search{

  public:
    explicit BoundedDepthFirstSearch(const string &, const int &, const int &);
    virtual ~BoundedDepthFirstSearch();
    virtual bool run();

  private:
    int max_depth_;
    bool DFS(const size_t &, int, SymExec &);

  };

}//namespace crest

#endif
