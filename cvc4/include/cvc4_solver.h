#ifndef SMT_CVC4_SOLVER_H
#define SMT_CVC4_SOLVER_H

/* #include <memory> */
/* #include <string> */
/* #include <vector> */

#include "api/cvc4cpp.h"

#include "exceptions.h"
#include "fun.h"
#include "result.h"
#include "smt.h"
#include "solver.h"
#include "sort.h"
#include "term.h"

namespace smt {
  /**
     CVC4 implementation of abstract solver class
  */
  class CVC4Solver : public AbsSmtSolver
  {
  public:
    CVC4Solver()
    {
      // require the solver to use smt-lib format
      solver.setOption("lang", "smt2");
    };
    ~CVC4Solver() = default;
    void set_opt(const std::string option, bool value) const override;
    void set_opt(const std::string option,
                 const std::string value) const override;
    void set_logic(const std::string logic) const override;
    Sort declare_sort(const std::string name,
                      unsigned int arity) const override;
    Term declare_const(const std::string name, Sort sort) const override;
    Fun declare_fun(const std::string name,
                          const std::vector<Sort>& sorts,
                          Sort sort) const override;
    Term make_const(unsigned int i, Sort sort) const override;
    Term make_const(std::string val, Sort sort) const override;
    /**
       Helper function for creating an OpTerm from an Op
       Preconditions: op must be indexed, i.e. op.num_idx > 0
    */
    ::CVC4::api::OpTerm make_op_term(Op op) const;
    Fun make_fun(Op op) const override;
    void assert_formula(const Term& t) const override;
    Result check_sat() const override;
    Term get_value(Term& t) const override;
    Sort make_sort(SortCon sc) const override;
    Sort make_sort(SortCon sc, unsigned int size) const override;
    Sort make_sort(SortCon sc, Sort idxsort, Sort elemsort) const override;
    Sort make_sort(SortCon sc, std::vector<Sort> sorts, Sort sort) const override;
    Term apply(Op op, Term t) const override;
    Term apply(Op op, Term t0, Term t1) const override;
    Term apply(Op op, Term t0, Term t1, Term t2) const override;
    Term apply(Op op, std::vector<Term> terms) const override;
    Term apply(Fun fun, Term t) const override;
    Term apply(Fun fun, Term t0, Term t1) const override;
    Term apply(Fun fun, Term t0, Term t1, Term t2) const override;
    Term apply(Fun fun, std::vector<Term> terms) const override;
  protected:
    ::CVC4::api::Solver solver;
  };

}

#endif
