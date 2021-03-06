#ifndef SMT_MSAT_TERM_H
#define SMT_MSAT_TERM_H

#include "term.h"
#include "utils.h"

#include "mathsat.h"

namespace smt {

// forward declaration
class MsatSolver;
class MsatInterpolatingSolver;

class MsatTermIter : public TermIterBase
{
 public:
  // TODO: consider making env const everywhere
  MsatTermIter(msat_env e, const msat_term t, uint32_t p)
      : env(e), term(t), pos(p){};
  MsatTermIter(const MsatTermIter & it);
  ~MsatTermIter(){};
  MsatTermIter & operator=(const MsatTermIter & it);
  void operator++() override;
  const Term operator*() override;
  bool operator==(const MsatTermIter & it);
  bool operator!=(const MsatTermIter & it);

 protected:
  bool equal(const TermIterBase & other) const override;

 private:
  msat_env env;
  msat_term term;
  uint32_t pos;
};

class MsatTerm : public AbsTerm
{
 public:
  MsatTerm(msat_env e, msat_term t) : env(e), term(t), is_uf(false){};
  MsatTerm(msat_env e, msat_decl d) : env(e), decl(d), is_uf(true){};
  ~MsatTerm(){};
  std::size_t hash() const override;
  bool compare(const Term & absterm) const override;
  Op get_op() const override;
  Sort get_sort() const override;
  bool is_symbolic_const() const override;
  bool is_value() const override;
  virtual std::string to_string() const override;
  uint64_t to_int() const override;
  /** Iterators for traversing the children
   */
  TermIter begin() override;
  TermIter end() override;

 protected:
  msat_env env;
  msat_term term;
  msat_decl decl;
  bool is_uf;

  friend class MsatSolver;
  friend class MsatInterpolatingSolver;
};

}  // namespace smt

#endif
