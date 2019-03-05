//===-- SpecialFunctionHandler.h --------------------------------*- C++ -*-===//
//
//                     The KLEE Symbolic Virtual Machine
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef KLEE_SPECIALFUNCTIONHANDLER_H
#define KLEE_SPECIALFUNCTIONHANDLER_H

#include <iterator>
#include <map>
#include <vector>
#include <string>
#include <deque>

namespace llvm {
class Function;
class Module;
}  // namespace llvm


struct stat;

namespace klee {
class Executor;
class Expr;
class ExecutionState;
struct KInstruction;
template<typename T> class ref;


class SpecialFunctionHandler {
 private:
  //std::deque<ExecutionState&> jump_states;

 public:
  typedef void (SpecialFunctionHandler::*Handler)(
      ExecutionState &state, KInstruction *target,
      std::vector<ref<Expr> > &arguments);
  typedef std::map<const llvm::Function*, std::pair<Handler, bool> > handlers_ty;
  std::vector<uint64_t> fstat_vector;

  handlers_ty handlers;
  class Executor &executor;

  struct HandlerInfo {
    const char *name;
    SpecialFunctionHandler::Handler handler;
    bool doesNotReturn;  /// Intrinsic terminates the process
    bool hasReturnValue;  /// Intrinsic has a return value
    bool doNotOverride;  /// Intrinsic should not be used if already defined
  };

  // const_iterator to iterate over stored HandlerInfo
  // FIXME: Implement >, >=, <=, < operators
  class const_iterator : public std::iterator<std::random_access_iterator_tag,
      HandlerInfo> {
   private:
    value_type* base;
    int index;
   public:
    const_iterator(value_type* hi)
        : base(hi),
          index(0) {
    }
    ;
    const_iterator& operator++();  // pre-fix
    const_iterator operator++(int);  // post-fix
    const value_type& operator*() {
      return base[index];
    }
    const value_type* operator->() {
      return &(base[index]);
    }
    const value_type& operator[](int i) {
      return base[i];
    }
    bool operator==(const_iterator& rhs) {
      return (rhs.base + rhs.index) == (this->base + this->index);
    }
    bool operator!=(const_iterator& rhs) {
      return !(*this == rhs);
    }
  };

  static const_iterator begin();
  static const_iterator end();
  static int size();

 public:
  SpecialFunctionHandler(Executor &_executor);

  /// Perform any modifications on the LLVM module before it is
  /// prepared for execution. At the moment this involves deleting
  /// unused function bodies and marking intrinsics with appropriate
  /// flags for use in optimizations.
  ///
  /// @param preservedFunctions contains all the function names which should
  /// be preserved during optimization
  void prepare(llvm::Module *mod,
               std::vector<const char *> &preservedFunctions);

  /// Initialize the internal handler map after the module has been
  /// prepared for execution.
  void bind(llvm::Module *mod);

  bool handle(ExecutionState &state, llvm::Function *f, KInstruction *target,
              std::vector<ref<Expr> > &arguments);

  /* Convenience routines */

  std::string readStringAtAddress(ExecutionState &state, ref<Expr> address);

  void set_up_fstat_struct(struct stat *info);

  /* Handlers */

#define HANDLER(name) void name(ExecutionState &state, \
                                KInstruction *target, \
                                std::vector< ref<Expr> > &arguments)

  HANDLER(handleAbort);
  HANDLER(handleAssert);
  HANDLER(handleAssertFail);
  HANDLER(handleAssume);
  HANDLER(handleCalloc);
  HANDLER(handleCheckMemoryAccess);
  HANDLER(handleDefineFixedObject);
  HANDLER(handleDelete);
  HANDLER(handleDeleteArray);
  HANDLER(handleExit);
  HANDLER(handleErrnoLocation);
  HANDLER(handleAliasFunction);
  HANDLER(handleFree);
  HANDLER(handleGetErrno);
  HANDLER(handleGetObjSize);
  HANDLER(handleGetValue);
  HANDLER(handleIsSymbolic);
  HANDLER(handleMakeSymbolic);
  HANDLER(handleMalloc);
  HANDLER(handleMemalign);
  HANDLER(handleMarkGlobal);
  HANDLER(handleOpenMerge);
  HANDLER(handleCloseMerge);
  HANDLER(handleNew);
  HANDLER(handleNewArray);
  HANDLER(handlePreferCex);
  HANDLER(handlePosixPreferCex);
  HANDLER(handlePrintExpr);
  HANDLER(handlePrintRange);
  HANDLER(handleRange);
  HANDLER(handleRealloc);
  HANDLER(handleReportError);
  HANDLER(handleRevirtObjects);
  HANDLER(handleSetForking);
  HANDLER(handleSilentExit);
  HANDLER(handleStackTrace);
  HANDLER(handleUnderConstrained);
  HANDLER(handleWarning);
  HANDLER(handleWarningOnce);
  HANDLER(handleAddOverflow);
  HANDLER(handleMulOverflow);
  HANDLER(handleSubOverflow);
  HANDLER(handleDivRemOverflow);

  //additions for remill lifted code
  HANDLER(handle__kleemill_get_lifted_function);
  HANDLER(handle__kleemill_can_write_byte);
  HANDLER(handle__kleemill_can_read_byte);
  HANDLER(handle__kleemill_free_memory);
  HANDLER(handle__kleemill_protect_memory);
  HANDLER(handle__kleemill_allocate_memory);
  HANDLER(handle__kleemill_is_mapped_address);
  HANDLER(handle__kleemill_find_unmapped_address);
  HANDLER(handle__kleemill_log_state);
  
  HANDLER(handle__remill_write_64);
  HANDLER(handle__remill_write_32);
  HANDLER(handle__remill_write_f32);
  HANDLER(handle__remill_write_16);
  HANDLER(handle__remill_write_8);
  HANDLER(handle__remill_read_64);
  HANDLER(handle__remill_read_32);
  HANDLER(handle__remill_read_16);
  HANDLER(handle__remill_read_8);
  
  HANDLER(handle__llvm_ctpop);

  HANDLER(handle__klee_overshift_check);
  HANDLER(handle__fstat64);
  HANDLER(handle__stat64);
  HANDLER(handle_openat64);
  HANDLER(handle_get_fstat_index);

#undef HANDLER
};
}  // End klee namespace

#endif
