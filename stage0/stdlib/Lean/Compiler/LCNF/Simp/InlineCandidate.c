// Lean compiler output
// Module: Lean.Compiler.LCNF.Simp.InlineCandidate
// Imports: public import Lean.Compiler.LCNF.Simp.SimpM
#include <lean/lean.h>
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wunused-parameter"
#pragma clang diagnostic ignored "-Wunused-label"
#elif defined(__GNUC__) && !defined(__CLANG__)
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-label"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#endif
#ifdef __cplusplus
extern "C" {
#endif
lean_object* lean_array_get_size(lean_object*);
LEAN_EXPORT lean_object* l_Lean_Compiler_LCNF_Simp_InlineCandidateInfo_arity(lean_object*);
LEAN_EXPORT lean_object* l_Lean_Compiler_LCNF_Simp_InlineCandidateInfo_arity___boxed(lean_object*);
lean_object* l_Lean_PersistentHashMap_mkEmptyEntriesArray(lean_object*, lean_object*);
static lean_once_cell_t l_Lean_throwError___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__1___redArg___closed__0_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* l_Lean_throwError___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__1___redArg___closed__0;
static lean_once_cell_t l_Lean_throwError___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__1___redArg___closed__1_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* l_Lean_throwError___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__1___redArg___closed__1;
static lean_once_cell_t l_Lean_throwError___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__1___redArg___closed__2_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* l_Lean_throwError___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__1___redArg___closed__2;
lean_object* lean_st_ref_get(lean_object*);
lean_object* l_Lean_Compiler_LCNF_getPurity___redArg(lean_object*);
lean_object* l_Lean_Compiler_LCNF_LCtx_toLocalContext(lean_object*, uint8_t);
LEAN_EXPORT lean_object* l_Lean_throwError___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__1___redArg(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* l_Lean_throwError___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__1___redArg___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* l_Lean_throwError___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__1(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* l_Lean_throwError___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__1___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
lean_object* l_instMonadEST(lean_object*, lean_object*);
static lean_once_cell_t l_panic___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__2___closed__0_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* l_panic___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__2___closed__0;
lean_object* l_Lean_Core_instMonadCoreM___lam__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
static const lean_closure_object l_panic___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__2___closed__1_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)l_Lean_Core_instMonadCoreM___lam__0___boxed, .m_arity = 5, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* l_panic___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__2___closed__1 = (const lean_object*)&l_panic___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__2___closed__1_value;
lean_object* l_Lean_Core_instMonadCoreM___lam__1___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
static const lean_closure_object l_panic___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__2___closed__2_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)l_Lean_Core_instMonadCoreM___lam__1___boxed, .m_arity = 7, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* l_panic___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__2___closed__2 = (const lean_object*)&l_panic___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__2___closed__2_value;
lean_object* l_Lean_Compiler_LCNF_instMonadCompilerM___lam__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
static const lean_closure_object l_panic___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__2___closed__3_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)l_Lean_Compiler_LCNF_instMonadCompilerM___lam__0___boxed, .m_arity = 7, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* l_panic___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__2___closed__3 = (const lean_object*)&l_panic___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__2___closed__3_value;
lean_object* l_Lean_Compiler_LCNF_instMonadCompilerM___lam__1___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
static const lean_closure_object l_panic___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__2___closed__4_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)l_Lean_Compiler_LCNF_instMonadCompilerM___lam__1___boxed, .m_arity = 9, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* l_panic___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__2___closed__4 = (const lean_object*)&l_panic___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__2___closed__4_value;
lean_object* l_ReaderT_instMonad___redArg(lean_object*);
lean_object* l_ReaderT_instFunctorOfMonad___redArg___lam__0(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
lean_object* l_ReaderT_instFunctorOfMonad___redArg___lam__1(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
lean_object* l_ReaderT_instApplicativeOfMonad___redArg___lam__1(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
lean_object* l_ReaderT_instApplicativeOfMonad___redArg___lam__3(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
lean_object* l_ReaderT_instApplicativeOfMonad___redArg___lam__4(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
lean_object* l_instInhabitedOfMonad___redArg(lean_object*, lean_object*);
lean_object* l_instInhabitedForall___redArg___lam__0___boxed(lean_object*, lean_object*);
lean_object* lean_panic_fn(lean_object*, lean_object*);
LEAN_EXPORT lean_object* l_panic___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__2(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* l_panic___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__2___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
uint8_t l_Lean_Compiler_LCNF_Decl_noinlineAttr___redArg(lean_object*);
lean_object* l_Lean_Compiler_LCNF_Simp_isSmall___redArg(lean_object*, lean_object*);
uint8_t l_Lean_Compiler_LCNF_Decl_alwaysInlineAttr___redArg(lean_object*);
uint8_t l_Lean_Compiler_LCNF_Decl_inlineAttr___redArg(lean_object*);
uint8_t l_Lean_Compiler_LCNF_Decl_inlineIfReduceAttr___redArg(lean_object*);
LEAN_EXPORT lean_object* l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f___lam__0(lean_object*, lean_object*, uint8_t, uint8_t, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f___lam__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
lean_object* l_Lean_Compiler_LCNF_Simp_instMonadSimpM___lam__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
static const lean_closure_object l_panic___at___00Lean_isCtor_x3f___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__0_spec__0___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)l_Lean_Compiler_LCNF_Simp_instMonadSimpM___lam__0___boxed, .m_arity = 10, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* l_panic___at___00Lean_isCtor_x3f___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__0_spec__0___closed__0 = (const lean_object*)&l_panic___at___00Lean_isCtor_x3f___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__0_spec__0___closed__0_value;
lean_object* l_Lean_Compiler_LCNF_Simp_instMonadSimpM___lam__1___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
static const lean_closure_object l_panic___at___00Lean_isCtor_x3f___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__0_spec__0___closed__1_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)l_Lean_Compiler_LCNF_Simp_instMonadSimpM___lam__1___boxed, .m_arity = 12, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* l_panic___at___00Lean_isCtor_x3f___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__0_spec__0___closed__1 = (const lean_object*)&l_panic___at___00Lean_isCtor_x3f___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__0_spec__0___closed__1_value;
LEAN_EXPORT lean_object* l_panic___at___00Lean_isCtor_x3f___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__0_spec__0(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* l_panic___at___00Lean_isCtor_x3f___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__0_spec__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
static const lean_string_object l_Lean_isCtor_x3f___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__0___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 14, .m_capacity = 14, .m_length = 13, .m_data = "Lean.MonadEnv"};
static const lean_object* l_Lean_isCtor_x3f___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__0___closed__0 = (const lean_object*)&l_Lean_isCtor_x3f___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__0___closed__0_value;
static const lean_string_object l_Lean_isCtor_x3f___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__0___closed__1_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 13, .m_capacity = 13, .m_length = 12, .m_data = "Lean.isCtor\?"};
static const lean_object* l_Lean_isCtor_x3f___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__0___closed__1 = (const lean_object*)&l_Lean_isCtor_x3f___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__0___closed__1_value;
static const lean_string_object l_Lean_isCtor_x3f___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__0___closed__2_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 34, .m_capacity = 34, .m_length = 33, .m_data = "unreachable code has been reached"};
static const lean_object* l_Lean_isCtor_x3f___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__0___closed__2 = (const lean_object*)&l_Lean_isCtor_x3f___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__0___closed__2_value;
lean_object* l_mkPanicMessageWithDecl(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
static lean_once_cell_t l_Lean_isCtor_x3f___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__0___closed__3_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* l_Lean_isCtor_x3f___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__0___closed__3;
lean_object* l_Lean_Environment_findAsync_x3f(lean_object*, lean_object*, uint8_t);
lean_object* l_Lean_AsyncConstantInfo_toConstantInfo(lean_object*);
LEAN_EXPORT lean_object* l_Lean_isCtor_x3f___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__0(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* l_Lean_isCtor_x3f___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
static const lean_string_object l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 10, .m_capacity = 10, .m_length = 9, .m_data = "_override"};
static const lean_object* l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f___closed__0 = (const lean_object*)&l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f___closed__0_value;
static const lean_string_object l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f___closed__1_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 7, .m_capacity = 7, .m_length = 6, .m_data = "inline"};
static const lean_object* l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f___closed__1 = (const lean_object*)&l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f___closed__1_value;
lean_object* lean_mk_empty_array_with_capacity(lean_object*);
static const lean_array_object l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f___closed__2_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_array_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 246}, .m_size = 0, .m_capacity = 0, .m_data = {}};
static const lean_object* l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f___closed__2 = (const lean_object*)&l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f___closed__2_value;
static const lean_string_object l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f___closed__3_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 44, .m_capacity = 44, .m_length = 43, .m_data = "`inline` applied to non-local declaration '"};
static const lean_object* l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f___closed__3 = (const lean_object*)&l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f___closed__3_value;
lean_object* l_Lean_stringToMessageData(lean_object*);
static lean_once_cell_t l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f___closed__4_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f___closed__4;
static const lean_string_object l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f___closed__5_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 13, .m_capacity = 13, .m_length = 12, .m_data = "' is invalid"};
static const lean_object* l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f___closed__5 = (const lean_object*)&l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f___closed__5_value;
static lean_once_cell_t l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f___closed__6_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f___closed__6;
static const lean_string_object l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f___closed__7_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 34, .m_capacity = 34, .m_length = 33, .m_data = "`inline` applied to constructor '"};
static const lean_object* l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f___closed__7 = (const lean_object*)&l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f___closed__7_value;
static lean_once_cell_t l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f___closed__8_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f___closed__8;
static const lean_string_object l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f___closed__9_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 40, .m_capacity = 40, .m_length = 39, .m_data = "Lean.Compiler.LCNF.Simp.InlineCandidate"};
static const lean_object* l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f___closed__9 = (const lean_object*)&l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f___closed__9_value;
static const lean_string_object l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f___closed__10_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 41, .m_capacity = 41, .m_length = 40, .m_data = "Lean.Compiler.LCNF.Simp.inlineCandidate\?"};
static const lean_object* l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f___closed__10 = (const lean_object*)&l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f___closed__10_value;
static const lean_string_object l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f___closed__11_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 120, .m_capacity = 120, .m_length = 119, .m_data = "assertion violation: ( __do_lift._@.Lean.Compiler.LCNF.Simp.InlineCandidate.450150219._hygCtx._hyg.53.0 ).isSome\n      "};
static const lean_object* l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f___closed__11 = (const lean_object*)&l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f___closed__11_value;
static lean_once_cell_t l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f___closed__12_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f___closed__12;
static const lean_string_object l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f___closed__13_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 42, .m_capacity = 42, .m_length = 41, .m_data = "`inline` applied to parameters is invalid"};
static const lean_object* l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f___closed__13 = (const lean_object*)&l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f___closed__13_value;
static lean_once_cell_t l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f___closed__14_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f___closed__14;
lean_object* l_Lean_Compiler_LCNF_Simp_incInline___redArg(lean_object*);
lean_object* l_Lean_Compiler_LCNF_Decl_instantiateParamsLevelParams(uint8_t, lean_object*, lean_object*);
lean_object* l_Lean_Compiler_LCNF_Code_instantiateValueLevelParams(lean_object*, lean_object*, lean_object*);
lean_object* l_Lean_Compiler_LCNF_Decl_instantiateTypeLevelParams___redArg(lean_object*, lean_object*);
lean_object* l_Lean_Compiler_LCNF_Decl_isCasesOnParam_x3f___redArg(lean_object*);
uint8_t lean_nat_dec_lt(lean_object*, lean_object*);
lean_object* lean_array_get_borrowed(lean_object*, lean_object*, lean_object*);
lean_object* l_Lean_Compiler_LCNF_Arg_isConstructorApp___redArg(lean_object*, lean_object*, lean_object*);
lean_object* l_Lean_Compiler_LCNF_Decl_getArity___redArg(lean_object*);
lean_object* l_Lean_Compiler_LCNF_inBasePhase___redArg(lean_object*);
lean_object* l_Lean_Meta_isInstance___redArg(lean_object*, lean_object*);
uint8_t lean_string_dec_eq(lean_object*, lean_object*);
lean_object* l_Lean_Compiler_LCNF_getPhase___redArg(lean_object*);
lean_object* l_Lean_Compiler_LCNF_getDeclAt_x3f(lean_object*, uint8_t, lean_object*, lean_object*);
uint8_t l_Lean_Compiler_LCNF_Phase_toPurity(uint8_t);
lean_object* l_Lean_Compiler_LCNF_Simp_incInlineLocal___redArg(lean_object*);
lean_object* lean_st_ref_take(lean_object*);
lean_object* lean_nat_add(lean_object*, lean_object*);
lean_object* lean_st_ref_set(lean_object*, lean_object*);
lean_object* l_Lean_Compiler_LCNF_getType(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
lean_object* l_Lean_Compiler_LCNF_Simp_shouldInlineLocal___redArg(lean_object*, lean_object*, lean_object*);
lean_object* l_Lean_Compiler_LCNF_Simp_findFunDecl_x27_x3f___redArg(uint8_t, lean_object*, lean_object*);
uint8_t lean_nat_dec_eq(lean_object*, lean_object*);
lean_object* lean_array_fget_borrowed(lean_object*, lean_object*);
lean_object* l_Lean_Compiler_LCNF_findLetDecl_x3f___redArg(uint8_t, lean_object*, lean_object*);
lean_object* l_Lean_Compiler_LCNF_getLocalDeclAt_x3f___redArg(lean_object*, uint8_t, lean_object*);
lean_object* l_Lean_MessageData_ofName(lean_object*);
lean_object* l_Lean_Compiler_LCNF_findParam_x3f___redArg(uint8_t, lean_object*, lean_object*);
LEAN_EXPORT lean_object* l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
static const lean_string_object l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__0_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 9, .m_capacity = 9, .m_length = 8, .m_data = "Compiler"};
static const lean_object* l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__0_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2_ = (const lean_object*)&l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__0_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value;
static const lean_string_object l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__1_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 5, .m_capacity = 5, .m_length = 4, .m_data = "simp"};
static const lean_object* l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__1_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2_ = (const lean_object*)&l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__1_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value;
lean_object* l_Lean_Name_mkStr3(lean_object*, lean_object*, lean_object*);
static const lean_ctor_object l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__2_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value_aux_0 = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)(((size_t)(0) << 1) | 1)),((lean_object*)&l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__0_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value),LEAN_SCALAR_PTR_LITERAL(253, 55, 142, 128, 91, 63, 88, 28)}};
static const lean_ctor_object l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__2_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value_aux_1 = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)&l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__2_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value_aux_0),((lean_object*)&l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__1_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value),LEAN_SCALAR_PTR_LITERAL(5, 122, 96, 221, 209, 205, 68, 156)}};
static const lean_ctor_object l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__2_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)&l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__2_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value_aux_1),((lean_object*)&l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f___closed__1_value),LEAN_SCALAR_PTR_LITERAL(186, 182, 14, 42, 67, 101, 187, 98)}};
static const lean_object* l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__2_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2_ = (const lean_object*)&l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__2_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value;
static const lean_string_object l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__3_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 9, .m_capacity = 9, .m_length = 8, .m_data = "_private"};
static const lean_object* l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__3_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2_ = (const lean_object*)&l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__3_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value;
lean_object* l_Lean_Name_str___override(lean_object*, lean_object*);
static const lean_ctor_object l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__4_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)(((size_t)(0) << 1) | 1)),((lean_object*)&l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__3_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value),LEAN_SCALAR_PTR_LITERAL(103, 214, 75, 80, 34, 198, 193, 153)}};
static const lean_object* l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__4_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2_ = (const lean_object*)&l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__4_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value;
static const lean_string_object l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__5_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 5, .m_capacity = 5, .m_length = 4, .m_data = "Lean"};
static const lean_object* l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__5_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2_ = (const lean_object*)&l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__5_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value;
static const lean_ctor_object l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__6_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)&l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__4_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value),((lean_object*)&l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__5_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value),LEAN_SCALAR_PTR_LITERAL(90, 18, 126, 130, 18, 214, 172, 143)}};
static const lean_object* l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__6_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2_ = (const lean_object*)&l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__6_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value;
static const lean_ctor_object l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__7_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)&l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__6_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value),((lean_object*)&l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__0_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value),LEAN_SCALAR_PTR_LITERAL(72, 245, 227, 28, 172, 102, 215, 20)}};
static const lean_object* l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__7_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2_ = (const lean_object*)&l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__7_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value;
static const lean_string_object l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__8_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 5, .m_capacity = 5, .m_length = 4, .m_data = "LCNF"};
static const lean_object* l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__8_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2_ = (const lean_object*)&l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__8_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value;
static const lean_ctor_object l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__9_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)&l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__7_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value),((lean_object*)&l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__8_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value),LEAN_SCALAR_PTR_LITERAL(225, 25, 15, 1, 146, 18, 87, 58)}};
static const lean_object* l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__9_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2_ = (const lean_object*)&l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__9_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value;
static const lean_string_object l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__10_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 5, .m_capacity = 5, .m_length = 4, .m_data = "Simp"};
static const lean_object* l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__10_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2_ = (const lean_object*)&l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__10_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value;
static const lean_ctor_object l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__11_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)&l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__9_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value),((lean_object*)&l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__10_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value),LEAN_SCALAR_PTR_LITERAL(65, 104, 221, 94, 203, 189, 176, 167)}};
static const lean_object* l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__11_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2_ = (const lean_object*)&l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__11_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value;
static const lean_string_object l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__12_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 16, .m_capacity = 16, .m_length = 15, .m_data = "InlineCandidate"};
static const lean_object* l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__12_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2_ = (const lean_object*)&l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__12_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value;
static const lean_ctor_object l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__13_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)&l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__11_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value),((lean_object*)&l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__12_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value),LEAN_SCALAR_PTR_LITERAL(204, 189, 245, 204, 189, 57, 91, 44)}};
static const lean_object* l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__13_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2_ = (const lean_object*)&l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__13_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value;
lean_object* l_Lean_Name_num___override(lean_object*, lean_object*);
static const lean_ctor_object l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__14_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 2}, .m_objs = {((lean_object*)&l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__13_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value),((lean_object*)(((size_t)(0) << 1) | 1)),LEAN_SCALAR_PTR_LITERAL(205, 24, 147, 136, 109, 69, 105, 125)}};
static const lean_object* l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__14_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2_ = (const lean_object*)&l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__14_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value;
static const lean_ctor_object l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__15_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)&l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__14_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value),((lean_object*)&l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__5_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value),LEAN_SCALAR_PTR_LITERAL(184, 141, 161, 237, 187, 152, 47, 223)}};
static const lean_object* l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__15_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2_ = (const lean_object*)&l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__15_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value;
static const lean_ctor_object l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__16_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)&l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__15_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value),((lean_object*)&l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__0_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value),LEAN_SCALAR_PTR_LITERAL(146, 100, 105, 35, 144, 92, 153, 253)}};
static const lean_object* l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__16_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2_ = (const lean_object*)&l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__16_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value;
static const lean_ctor_object l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__17_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)&l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__16_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value),((lean_object*)&l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__8_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value),LEAN_SCALAR_PTR_LITERAL(211, 251, 144, 255, 136, 239, 26, 27)}};
static const lean_object* l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__17_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2_ = (const lean_object*)&l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__17_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value;
static const lean_ctor_object l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__18_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)&l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__17_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value),((lean_object*)&l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__10_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value),LEAN_SCALAR_PTR_LITERAL(123, 121, 5, 69, 12, 122, 72, 166)}};
static const lean_object* l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__18_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2_ = (const lean_object*)&l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__18_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value;
static const lean_string_object l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__19_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 7, .m_capacity = 7, .m_length = 6, .m_data = "initFn"};
static const lean_object* l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__19_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2_ = (const lean_object*)&l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__19_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value;
static const lean_ctor_object l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__20_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)&l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__18_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value),((lean_object*)&l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__19_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value),LEAN_SCALAR_PTR_LITERAL(202, 124, 205, 76, 48, 189, 94, 107)}};
static const lean_object* l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__20_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2_ = (const lean_object*)&l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__20_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value;
static const lean_string_object l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__21_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 3, .m_capacity = 3, .m_length = 2, .m_data = "_@"};
static const lean_object* l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__21_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2_ = (const lean_object*)&l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__21_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value;
static const lean_ctor_object l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__22_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)&l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__20_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value),((lean_object*)&l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__21_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value),LEAN_SCALAR_PTR_LITERAL(35, 5, 164, 203, 90, 240, 32, 95)}};
static const lean_object* l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__22_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2_ = (const lean_object*)&l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__22_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value;
static const lean_ctor_object l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__23_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)&l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__22_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value),((lean_object*)&l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__5_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value),LEAN_SCALAR_PTR_LITERAL(110, 174, 208, 245, 188, 159, 42, 16)}};
static const lean_object* l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__23_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2_ = (const lean_object*)&l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__23_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value;
static const lean_ctor_object l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__24_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)&l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__23_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value),((lean_object*)&l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__0_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value),LEAN_SCALAR_PTR_LITERAL(76, 214, 115, 185, 35, 209, 42, 75)}};
static const lean_object* l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__24_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2_ = (const lean_object*)&l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__24_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value;
static const lean_ctor_object l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__25_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)&l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__24_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value),((lean_object*)&l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__8_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value),LEAN_SCALAR_PTR_LITERAL(141, 210, 134, 178, 101, 107, 79, 160)}};
static const lean_object* l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__25_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2_ = (const lean_object*)&l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__25_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value;
static const lean_ctor_object l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__26_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)&l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__25_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value),((lean_object*)&l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__10_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value),LEAN_SCALAR_PTR_LITERAL(101, 132, 0, 16, 135, 249, 121, 4)}};
static const lean_object* l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__26_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2_ = (const lean_object*)&l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__26_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value;
static const lean_ctor_object l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__27_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)&l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__26_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value),((lean_object*)&l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__12_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value),LEAN_SCALAR_PTR_LITERAL(24, 86, 216, 181, 78, 83, 157, 191)}};
static const lean_object* l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__27_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2_ = (const lean_object*)&l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__27_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value;
static const lean_ctor_object l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__28_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 2}, .m_objs = {((lean_object*)&l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__27_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value),((lean_object*)(((size_t)(1449551352) << 1) | 1)),LEAN_SCALAR_PTR_LITERAL(40, 111, 212, 97, 188, 2, 254, 12)}};
static const lean_object* l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__28_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2_ = (const lean_object*)&l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__28_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value;
static const lean_string_object l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__29_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 8, .m_capacity = 8, .m_length = 7, .m_data = "_hygCtx"};
static const lean_object* l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__29_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2_ = (const lean_object*)&l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__29_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value;
static const lean_ctor_object l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__30_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)&l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__28_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value),((lean_object*)&l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__29_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value),LEAN_SCALAR_PTR_LITERAL(143, 181, 10, 223, 32, 170, 74, 213)}};
static const lean_object* l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__30_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2_ = (const lean_object*)&l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__30_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value;
static const lean_string_object l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__31_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 5, .m_capacity = 5, .m_length = 4, .m_data = "_hyg"};
static const lean_object* l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__31_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2_ = (const lean_object*)&l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__31_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value;
static const lean_ctor_object l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__32_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)&l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__30_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value),((lean_object*)&l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__31_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value),LEAN_SCALAR_PTR_LITERAL(119, 22, 140, 58, 145, 25, 234, 208)}};
static const lean_object* l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__32_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2_ = (const lean_object*)&l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__32_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value;
static const lean_ctor_object l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__33_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 8, .m_other = 2, .m_tag = 2}, .m_objs = {((lean_object*)&l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__32_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value),((lean_object*)(((size_t)(2) << 1) | 1)),LEAN_SCALAR_PTR_LITERAL(98, 140, 124, 200, 122, 12, 67, 204)}};
static const lean_object* l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__33_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2_ = (const lean_object*)&l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__33_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2__value;
lean_object* l_Lean_registerTraceClass(lean_object*, uint8_t, lean_object*);
LEAN_EXPORT lean_object* l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2_();
LEAN_EXPORT lean_object* l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2____boxed(lean_object*);
LEAN_EXPORT lean_object* l_Lean_Compiler_LCNF_Simp_InlineCandidateInfo_arity(lean_object* x_1) {
_start:
{
lean_object* x_2; lean_object* x_3; 
x_2 = lean_ctor_get(x_1, 0);
x_3 = lean_array_get_size(x_2);
return x_3;
}
}
LEAN_EXPORT lean_object* l_Lean_Compiler_LCNF_Simp_InlineCandidateInfo_arity___boxed(lean_object* x_1) {
_start:
{
lean_object* x_2; 
x_2 = l_Lean_Compiler_LCNF_Simp_InlineCandidateInfo_arity(x_1);
lean_dec_ref(x_1);
return x_2;
}
}
static lean_object* _init_l_Lean_throwError___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__1___redArg___closed__0(void) {
_start:
{
lean_object* x_1; 
x_1 = l_Lean_PersistentHashMap_mkEmptyEntriesArray(lean_box(0), lean_box(0));
return x_1;
}
}
static lean_object* _init_l_Lean_throwError___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__1___redArg___closed__1(void) {
_start:
{
lean_object* x_1; lean_object* x_2; 
x_1 = lean_obj_once(&l_Lean_throwError___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__1___redArg___closed__0, &l_Lean_throwError___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__1___redArg___closed__0_once, _init_l_Lean_throwError___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__1___redArg___closed__0);
x_2 = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(x_2, 0, x_1);
return x_2;
}
}
static lean_object* _init_l_Lean_throwError___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__1___redArg___closed__2(void) {
_start:
{
lean_object* x_1; lean_object* x_2; lean_object* x_3; 
x_1 = lean_obj_once(&l_Lean_throwError___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__1___redArg___closed__1, &l_Lean_throwError___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__1___redArg___closed__1_once, _init_l_Lean_throwError___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__1___redArg___closed__1);
x_2 = lean_unsigned_to_nat(0u);
x_3 = lean_alloc_ctor(0, 9, 0);
lean_ctor_set(x_3, 0, x_2);
lean_ctor_set(x_3, 1, x_2);
lean_ctor_set(x_3, 2, x_2);
lean_ctor_set(x_3, 3, x_1);
lean_ctor_set(x_3, 4, x_1);
lean_ctor_set(x_3, 5, x_1);
lean_ctor_set(x_3, 6, x_1);
lean_ctor_set(x_3, 7, x_1);
lean_ctor_set(x_3, 8, x_1);
return x_3;
}
}
LEAN_EXPORT lean_object* l_Lean_throwError___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__1___redArg(lean_object* x_1, lean_object* x_2, lean_object* x_3, lean_object* x_4, lean_object* x_5) {
_start:
{
lean_object* x_7; lean_object* x_8; lean_object* x_9; lean_object* x_10; lean_object* x_11; 
x_7 = lean_ctor_get(x_4, 2);
x_8 = lean_ctor_get(x_4, 5);
x_9 = lean_st_ref_get(x_5);
x_10 = lean_st_ref_get(x_3);
x_11 = l_Lean_Compiler_LCNF_getPurity___redArg(x_2);
if (lean_obj_tag(x_11) == 0)
{
lean_object* x_12; lean_object* x_13; uint8_t x_14; uint8_t x_34; 
x_12 = lean_ctor_get(x_11, 0);
x_34 = !lean_is_exclusive(x_11);
if (x_34 == 0)
{
x_13 = x_11;
x_14 = x_34;
goto block_33;
}
else
{
lean_inc(x_12);
lean_dec(x_11);
x_13 = lean_box(0);
x_14 = x_34;
goto block_33;
}
block_33:
{
lean_object* x_15; lean_object* x_16; lean_object* x_17; uint8_t x_18; uint8_t x_31; 
x_15 = lean_ctor_get(x_9, 0);
lean_inc_ref(x_15);
lean_dec(x_9);
x_16 = lean_ctor_get(x_10, 0);
x_31 = !lean_is_exclusive(x_10);
if (x_31 == 0)
{
lean_object* x_32; 
x_32 = lean_ctor_get(x_10, 1);
lean_dec(x_32);
x_17 = x_10;
x_18 = x_31;
goto block_30;
}
else
{
lean_inc(x_16);
lean_dec(x_10);
x_17 = lean_box(0);
x_18 = x_31;
goto block_30;
}
block_30:
{
uint8_t x_19; lean_object* x_20; lean_object* x_21; lean_object* x_22; lean_object* x_23; 
x_19 = lean_unbox(x_12);
lean_dec(x_12);
x_20 = l_Lean_Compiler_LCNF_LCtx_toLocalContext(x_16, x_19);
lean_dec_ref(x_16);
x_21 = lean_obj_once(&l_Lean_throwError___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__1___redArg___closed__2, &l_Lean_throwError___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__1___redArg___closed__2_once, _init_l_Lean_throwError___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__1___redArg___closed__2);
lean_inc_ref(x_7);
x_22 = lean_alloc_ctor(0, 4, 0);
lean_ctor_set(x_22, 0, x_15);
lean_ctor_set(x_22, 1, x_21);
lean_ctor_set(x_22, 2, x_20);
lean_ctor_set(x_22, 3, x_7);
if (x_18 == 0)
{
lean_ctor_set_tag(x_17, 3);
lean_ctor_set(x_17, 1, x_1);
lean_ctor_set(x_17, 0, x_22);
x_23 = x_17;
goto block_28;
}
else
{
lean_object* x_29; 
x_29 = lean_alloc_ctor(3, 2, 0);
lean_ctor_set(x_29, 0, x_22);
lean_ctor_set(x_29, 1, x_1);
x_23 = x_29;
goto block_28;
}
block_28:
{
lean_object* x_24; lean_object* x_25; 
lean_inc(x_8);
x_24 = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(x_24, 0, x_8);
lean_ctor_set(x_24, 1, x_23);
if (x_14 == 0)
{
lean_ctor_set_tag(x_13, 1);
lean_ctor_set(x_13, 0, x_24);
x_25 = x_13;
goto block_26;
}
else
{
lean_object* x_27; 
x_27 = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(x_27, 0, x_24);
x_25 = x_27;
goto block_26;
}
block_26:
{
return x_25;
}
}
}
}
}
else
{
lean_object* x_35; lean_object* x_36; uint8_t x_37; uint8_t x_42; 
lean_dec(x_10);
lean_dec(x_9);
lean_dec_ref(x_1);
x_35 = lean_ctor_get(x_11, 0);
x_42 = !lean_is_exclusive(x_11);
if (x_42 == 0)
{
x_36 = x_11;
x_37 = x_42;
goto block_41;
}
else
{
lean_inc(x_35);
lean_dec(x_11);
x_36 = lean_box(0);
x_37 = x_42;
goto block_41;
}
block_41:
{
lean_object* x_38; 
if (x_37 == 0)
{
x_38 = x_36;
goto block_39;
}
else
{
lean_object* x_40; 
x_40 = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(x_40, 0, x_35);
x_38 = x_40;
goto block_39;
}
block_39:
{
return x_38;
}
}
}
}
}
LEAN_EXPORT lean_object* l_Lean_throwError___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__1___redArg___boxed(lean_object* x_1, lean_object* x_2, lean_object* x_3, lean_object* x_4, lean_object* x_5, lean_object* x_6) {
_start:
{
lean_object* x_7; 
x_7 = l_Lean_throwError___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__1___redArg(x_1, x_2, x_3, x_4, x_5);
lean_dec(x_5);
lean_dec_ref(x_4);
lean_dec(x_3);
lean_dec_ref(x_2);
return x_7;
}
}
LEAN_EXPORT lean_object* l_Lean_throwError___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__1(lean_object* x_1, lean_object* x_2, lean_object* x_3, lean_object* x_4, lean_object* x_5, lean_object* x_6, lean_object* x_7, lean_object* x_8, lean_object* x_9) {
_start:
{
lean_object* x_11; 
x_11 = l_Lean_throwError___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__1___redArg(x_2, x_6, x_7, x_8, x_9);
return x_11;
}
}
LEAN_EXPORT lean_object* l_Lean_throwError___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__1___boxed(lean_object* x_1, lean_object* x_2, lean_object* x_3, lean_object* x_4, lean_object* x_5, lean_object* x_6, lean_object* x_7, lean_object* x_8, lean_object* x_9, lean_object* x_10) {
_start:
{
lean_object* x_11; 
x_11 = l_Lean_throwError___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__1(x_1, x_2, x_3, x_4, x_5, x_6, x_7, x_8, x_9);
lean_dec(x_9);
lean_dec_ref(x_8);
lean_dec(x_7);
lean_dec_ref(x_6);
lean_dec_ref(x_5);
lean_dec(x_4);
lean_dec_ref(x_3);
return x_11;
}
}
static lean_object* _init_l_panic___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__2___closed__0(void) {
_start:
{
lean_object* x_1; 
x_1 = l_instMonadEST(lean_box(0), lean_box(0));
return x_1;
}
}
LEAN_EXPORT lean_object* l_panic___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__2(lean_object* x_1, lean_object* x_2, lean_object* x_3, lean_object* x_4, lean_object* x_5, lean_object* x_6, lean_object* x_7, lean_object* x_8) {
_start:
{
lean_object* x_10; lean_object* x_11; lean_object* x_12; lean_object* x_13; uint8_t x_14; uint8_t x_76; 
x_10 = lean_obj_once(&l_panic___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__2___closed__0, &l_panic___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__2___closed__0_once, _init_l_panic___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__2___closed__0);
x_11 = l_ReaderT_instMonad___redArg(x_10);
x_12 = lean_ctor_get(x_11, 0);
x_76 = !lean_is_exclusive(x_11);
if (x_76 == 0)
{
lean_object* x_77; 
x_77 = lean_ctor_get(x_11, 1);
lean_dec(x_77);
x_13 = x_11;
x_14 = x_76;
goto block_75;
}
else
{
lean_inc(x_12);
lean_dec(x_11);
x_13 = lean_box(0);
x_14 = x_76;
goto block_75;
}
block_75:
{
lean_object* x_15; lean_object* x_16; lean_object* x_17; lean_object* x_18; lean_object* x_19; uint8_t x_20; uint8_t x_73; 
x_15 = lean_ctor_get(x_12, 0);
x_16 = lean_ctor_get(x_12, 2);
x_17 = lean_ctor_get(x_12, 3);
x_18 = lean_ctor_get(x_12, 4);
x_73 = !lean_is_exclusive(x_12);
if (x_73 == 0)
{
lean_object* x_74; 
x_74 = lean_ctor_get(x_12, 1);
lean_dec(x_74);
x_19 = x_12;
x_20 = x_73;
goto block_72;
}
else
{
lean_inc(x_18);
lean_inc(x_17);
lean_inc(x_16);
lean_inc(x_15);
lean_dec(x_12);
x_19 = lean_box(0);
x_20 = x_73;
goto block_72;
}
block_72:
{
lean_object* x_21; lean_object* x_22; lean_object* x_23; lean_object* x_24; lean_object* x_25; lean_object* x_26; lean_object* x_27; lean_object* x_28; lean_object* x_29; 
x_21 = ((lean_object*)(l_panic___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__2___closed__1));
x_22 = ((lean_object*)(l_panic___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__2___closed__2));
lean_inc_ref(x_15);
x_23 = lean_alloc_closure((void*)(l_ReaderT_instFunctorOfMonad___redArg___lam__0), 6, 1);
lean_closure_set(x_23, 0, x_15);
x_24 = lean_alloc_closure((void*)(l_ReaderT_instFunctorOfMonad___redArg___lam__1), 6, 1);
lean_closure_set(x_24, 0, x_15);
x_25 = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(x_25, 0, x_23);
lean_ctor_set(x_25, 1, x_24);
x_26 = lean_alloc_closure((void*)(l_ReaderT_instApplicativeOfMonad___redArg___lam__1), 6, 1);
lean_closure_set(x_26, 0, x_18);
x_27 = lean_alloc_closure((void*)(l_ReaderT_instApplicativeOfMonad___redArg___lam__3), 6, 1);
lean_closure_set(x_27, 0, x_17);
x_28 = lean_alloc_closure((void*)(l_ReaderT_instApplicativeOfMonad___redArg___lam__4), 6, 1);
lean_closure_set(x_28, 0, x_16);
if (x_20 == 0)
{
lean_ctor_set(x_19, 4, x_26);
lean_ctor_set(x_19, 3, x_27);
lean_ctor_set(x_19, 2, x_28);
lean_ctor_set(x_19, 1, x_21);
lean_ctor_set(x_19, 0, x_25);
x_29 = x_19;
goto block_70;
}
else
{
lean_object* x_71; 
x_71 = lean_alloc_ctor(0, 5, 0);
lean_ctor_set(x_71, 0, x_25);
lean_ctor_set(x_71, 1, x_21);
lean_ctor_set(x_71, 2, x_28);
lean_ctor_set(x_71, 3, x_27);
lean_ctor_set(x_71, 4, x_26);
x_29 = x_71;
goto block_70;
}
block_70:
{
lean_object* x_30; 
if (x_14 == 0)
{
lean_ctor_set(x_13, 1, x_22);
lean_ctor_set(x_13, 0, x_29);
x_30 = x_13;
goto block_68;
}
else
{
lean_object* x_69; 
x_69 = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(x_69, 0, x_29);
lean_ctor_set(x_69, 1, x_22);
x_30 = x_69;
goto block_68;
}
block_68:
{
lean_object* x_31; lean_object* x_32; lean_object* x_33; uint8_t x_34; uint8_t x_66; 
x_31 = l_ReaderT_instMonad___redArg(x_30);
x_32 = lean_ctor_get(x_31, 0);
x_66 = !lean_is_exclusive(x_31);
if (x_66 == 0)
{
lean_object* x_67; 
x_67 = lean_ctor_get(x_31, 1);
lean_dec(x_67);
x_33 = x_31;
x_34 = x_66;
goto block_65;
}
else
{
lean_inc(x_32);
lean_dec(x_31);
x_33 = lean_box(0);
x_34 = x_66;
goto block_65;
}
block_65:
{
lean_object* x_35; lean_object* x_36; lean_object* x_37; lean_object* x_38; lean_object* x_39; uint8_t x_40; uint8_t x_63; 
x_35 = lean_ctor_get(x_32, 0);
x_36 = lean_ctor_get(x_32, 2);
x_37 = lean_ctor_get(x_32, 3);
x_38 = lean_ctor_get(x_32, 4);
x_63 = !lean_is_exclusive(x_32);
if (x_63 == 0)
{
lean_object* x_64; 
x_64 = lean_ctor_get(x_32, 1);
lean_dec(x_64);
x_39 = x_32;
x_40 = x_63;
goto block_62;
}
else
{
lean_inc(x_38);
lean_inc(x_37);
lean_inc(x_36);
lean_inc(x_35);
lean_dec(x_32);
x_39 = lean_box(0);
x_40 = x_63;
goto block_62;
}
block_62:
{
lean_object* x_41; lean_object* x_42; lean_object* x_43; lean_object* x_44; lean_object* x_45; lean_object* x_46; lean_object* x_47; lean_object* x_48; lean_object* x_49; 
x_41 = ((lean_object*)(l_panic___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__2___closed__3));
x_42 = ((lean_object*)(l_panic___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__2___closed__4));
lean_inc_ref(x_35);
x_43 = lean_alloc_closure((void*)(l_ReaderT_instFunctorOfMonad___redArg___lam__0), 6, 1);
lean_closure_set(x_43, 0, x_35);
x_44 = lean_alloc_closure((void*)(l_ReaderT_instFunctorOfMonad___redArg___lam__1), 6, 1);
lean_closure_set(x_44, 0, x_35);
x_45 = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(x_45, 0, x_43);
lean_ctor_set(x_45, 1, x_44);
x_46 = lean_alloc_closure((void*)(l_ReaderT_instApplicativeOfMonad___redArg___lam__1), 6, 1);
lean_closure_set(x_46, 0, x_38);
x_47 = lean_alloc_closure((void*)(l_ReaderT_instApplicativeOfMonad___redArg___lam__3), 6, 1);
lean_closure_set(x_47, 0, x_37);
x_48 = lean_alloc_closure((void*)(l_ReaderT_instApplicativeOfMonad___redArg___lam__4), 6, 1);
lean_closure_set(x_48, 0, x_36);
if (x_40 == 0)
{
lean_ctor_set(x_39, 4, x_46);
lean_ctor_set(x_39, 3, x_47);
lean_ctor_set(x_39, 2, x_48);
lean_ctor_set(x_39, 1, x_41);
lean_ctor_set(x_39, 0, x_45);
x_49 = x_39;
goto block_60;
}
else
{
lean_object* x_61; 
x_61 = lean_alloc_ctor(0, 5, 0);
lean_ctor_set(x_61, 0, x_45);
lean_ctor_set(x_61, 1, x_41);
lean_ctor_set(x_61, 2, x_48);
lean_ctor_set(x_61, 3, x_47);
lean_ctor_set(x_61, 4, x_46);
x_49 = x_61;
goto block_60;
}
block_60:
{
lean_object* x_50; 
if (x_34 == 0)
{
lean_ctor_set(x_33, 1, x_42);
lean_ctor_set(x_33, 0, x_49);
x_50 = x_33;
goto block_58;
}
else
{
lean_object* x_59; 
x_59 = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(x_59, 0, x_49);
lean_ctor_set(x_59, 1, x_42);
x_50 = x_59;
goto block_58;
}
block_58:
{
lean_object* x_51; lean_object* x_52; lean_object* x_53; lean_object* x_54; lean_object* x_55; lean_object* x_56; lean_object* x_57; 
x_51 = l_ReaderT_instMonad___redArg(x_50);
x_52 = l_ReaderT_instMonad___redArg(x_51);
x_53 = lean_box(0);
x_54 = l_instInhabitedOfMonad___redArg(x_52, x_53);
x_55 = lean_alloc_closure((void*)(l_instInhabitedForall___redArg___lam__0___boxed), 2, 1);
lean_closure_set(x_55, 0, x_54);
x_56 = lean_panic_fn(x_55, x_1);
x_57 = lean_apply_8(x_56, x_2, x_3, x_4, x_5, x_6, x_7, x_8, lean_box(0));
return x_57;
}
}
}
}
}
}
}
}
}
}
LEAN_EXPORT lean_object* l_panic___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__2___boxed(lean_object* x_1, lean_object* x_2, lean_object* x_3, lean_object* x_4, lean_object* x_5, lean_object* x_6, lean_object* x_7, lean_object* x_8, lean_object* x_9) {
_start:
{
lean_object* x_10; 
x_10 = l_panic___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__2(x_1, x_2, x_3, x_4, x_5, x_6, x_7, x_8);
return x_10;
}
}
LEAN_EXPORT lean_object* l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f___lam__0(lean_object* x_1, lean_object* x_2, uint8_t x_3, uint8_t x_4, lean_object* x_5, lean_object* x_6, lean_object* x_7, lean_object* x_8, lean_object* x_9, lean_object* x_10, lean_object* x_11, lean_object* x_12) {
_start:
{
uint8_t x_14; uint8_t x_22; 
x_22 = l_Lean_Compiler_LCNF_Decl_alwaysInlineAttr___redArg(x_1);
if (x_22 == 0)
{
uint8_t x_23; 
x_23 = l_Lean_Compiler_LCNF_Decl_inlineAttr___redArg(x_1);
if (x_23 == 0)
{
uint8_t x_24; 
x_24 = l_Lean_Compiler_LCNF_Decl_inlineIfReduceAttr___redArg(x_1);
x_14 = x_24;
goto block_21;
}
else
{
x_14 = x_23;
goto block_21;
}
}
else
{
lean_object* x_25; lean_object* x_26; 
x_25 = lean_box(x_4);
x_26 = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(x_26, 0, x_25);
return x_26;
}
block_21:
{
if (x_14 == 0)
{
uint8_t x_15; 
x_15 = l_Lean_Compiler_LCNF_Decl_noinlineAttr___redArg(x_1);
if (x_15 == 0)
{
lean_object* x_16; 
x_16 = l_Lean_Compiler_LCNF_Simp_isSmall___redArg(x_2, x_9);
return x_16;
}
else
{
lean_object* x_17; lean_object* x_18; 
x_17 = lean_box(x_3);
x_18 = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(x_18, 0, x_17);
return x_18;
}
}
else
{
lean_object* x_19; lean_object* x_20; 
x_19 = lean_box(x_4);
x_20 = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(x_20, 0, x_19);
return x_20;
}
}
}
}
LEAN_EXPORT lean_object* l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f___lam__0___boxed(lean_object* x_1, lean_object* x_2, lean_object* x_3, lean_object* x_4, lean_object* x_5, lean_object* x_6, lean_object* x_7, lean_object* x_8, lean_object* x_9, lean_object* x_10, lean_object* x_11, lean_object* x_12, lean_object* x_13) {
_start:
{
uint8_t x_14; uint8_t x_15; lean_object* x_16; 
x_14 = lean_unbox(x_3);
x_15 = lean_unbox(x_4);
x_16 = l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f___lam__0(x_1, x_2, x_14, x_15, x_5, x_6, x_7, x_8, x_9, x_10, x_11, x_12);
lean_dec(x_12);
lean_dec_ref(x_11);
lean_dec(x_10);
lean_dec_ref(x_9);
lean_dec_ref(x_8);
lean_dec(x_7);
lean_dec_ref(x_6);
lean_dec_ref(x_2);
lean_dec_ref(x_1);
return x_16;
}
}
LEAN_EXPORT lean_object* l_panic___at___00Lean_isCtor_x3f___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__0_spec__0(lean_object* x_1, lean_object* x_2, lean_object* x_3, lean_object* x_4, lean_object* x_5, lean_object* x_6, lean_object* x_7, lean_object* x_8) {
_start:
{
lean_object* x_10; lean_object* x_11; lean_object* x_12; lean_object* x_13; uint8_t x_14; uint8_t x_104; 
x_10 = lean_obj_once(&l_panic___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__2___closed__0, &l_panic___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__2___closed__0_once, _init_l_panic___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__2___closed__0);
x_11 = l_ReaderT_instMonad___redArg(x_10);
x_12 = lean_ctor_get(x_11, 0);
x_104 = !lean_is_exclusive(x_11);
if (x_104 == 0)
{
lean_object* x_105; 
x_105 = lean_ctor_get(x_11, 1);
lean_dec(x_105);
x_13 = x_11;
x_14 = x_104;
goto block_103;
}
else
{
lean_inc(x_12);
lean_dec(x_11);
x_13 = lean_box(0);
x_14 = x_104;
goto block_103;
}
block_103:
{
lean_object* x_15; lean_object* x_16; lean_object* x_17; lean_object* x_18; lean_object* x_19; uint8_t x_20; uint8_t x_101; 
x_15 = lean_ctor_get(x_12, 0);
x_16 = lean_ctor_get(x_12, 2);
x_17 = lean_ctor_get(x_12, 3);
x_18 = lean_ctor_get(x_12, 4);
x_101 = !lean_is_exclusive(x_12);
if (x_101 == 0)
{
lean_object* x_102; 
x_102 = lean_ctor_get(x_12, 1);
lean_dec(x_102);
x_19 = x_12;
x_20 = x_101;
goto block_100;
}
else
{
lean_inc(x_18);
lean_inc(x_17);
lean_inc(x_16);
lean_inc(x_15);
lean_dec(x_12);
x_19 = lean_box(0);
x_20 = x_101;
goto block_100;
}
block_100:
{
lean_object* x_21; lean_object* x_22; lean_object* x_23; lean_object* x_24; lean_object* x_25; lean_object* x_26; lean_object* x_27; lean_object* x_28; lean_object* x_29; 
x_21 = ((lean_object*)(l_panic___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__2___closed__1));
x_22 = ((lean_object*)(l_panic___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__2___closed__2));
lean_inc_ref(x_15);
x_23 = lean_alloc_closure((void*)(l_ReaderT_instFunctorOfMonad___redArg___lam__0), 6, 1);
lean_closure_set(x_23, 0, x_15);
x_24 = lean_alloc_closure((void*)(l_ReaderT_instFunctorOfMonad___redArg___lam__1), 6, 1);
lean_closure_set(x_24, 0, x_15);
x_25 = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(x_25, 0, x_23);
lean_ctor_set(x_25, 1, x_24);
x_26 = lean_alloc_closure((void*)(l_ReaderT_instApplicativeOfMonad___redArg___lam__1), 6, 1);
lean_closure_set(x_26, 0, x_18);
x_27 = lean_alloc_closure((void*)(l_ReaderT_instApplicativeOfMonad___redArg___lam__3), 6, 1);
lean_closure_set(x_27, 0, x_17);
x_28 = lean_alloc_closure((void*)(l_ReaderT_instApplicativeOfMonad___redArg___lam__4), 6, 1);
lean_closure_set(x_28, 0, x_16);
if (x_20 == 0)
{
lean_ctor_set(x_19, 4, x_26);
lean_ctor_set(x_19, 3, x_27);
lean_ctor_set(x_19, 2, x_28);
lean_ctor_set(x_19, 1, x_21);
lean_ctor_set(x_19, 0, x_25);
x_29 = x_19;
goto block_98;
}
else
{
lean_object* x_99; 
x_99 = lean_alloc_ctor(0, 5, 0);
lean_ctor_set(x_99, 0, x_25);
lean_ctor_set(x_99, 1, x_21);
lean_ctor_set(x_99, 2, x_28);
lean_ctor_set(x_99, 3, x_27);
lean_ctor_set(x_99, 4, x_26);
x_29 = x_99;
goto block_98;
}
block_98:
{
lean_object* x_30; 
if (x_14 == 0)
{
lean_ctor_set(x_13, 1, x_22);
lean_ctor_set(x_13, 0, x_29);
x_30 = x_13;
goto block_96;
}
else
{
lean_object* x_97; 
x_97 = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(x_97, 0, x_29);
lean_ctor_set(x_97, 1, x_22);
x_30 = x_97;
goto block_96;
}
block_96:
{
lean_object* x_31; lean_object* x_32; lean_object* x_33; uint8_t x_34; uint8_t x_94; 
x_31 = l_ReaderT_instMonad___redArg(x_30);
x_32 = lean_ctor_get(x_31, 0);
x_94 = !lean_is_exclusive(x_31);
if (x_94 == 0)
{
lean_object* x_95; 
x_95 = lean_ctor_get(x_31, 1);
lean_dec(x_95);
x_33 = x_31;
x_34 = x_94;
goto block_93;
}
else
{
lean_inc(x_32);
lean_dec(x_31);
x_33 = lean_box(0);
x_34 = x_94;
goto block_93;
}
block_93:
{
lean_object* x_35; lean_object* x_36; lean_object* x_37; lean_object* x_38; lean_object* x_39; uint8_t x_40; uint8_t x_91; 
x_35 = lean_ctor_get(x_32, 0);
x_36 = lean_ctor_get(x_32, 2);
x_37 = lean_ctor_get(x_32, 3);
x_38 = lean_ctor_get(x_32, 4);
x_91 = !lean_is_exclusive(x_32);
if (x_91 == 0)
{
lean_object* x_92; 
x_92 = lean_ctor_get(x_32, 1);
lean_dec(x_92);
x_39 = x_32;
x_40 = x_91;
goto block_90;
}
else
{
lean_inc(x_38);
lean_inc(x_37);
lean_inc(x_36);
lean_inc(x_35);
lean_dec(x_32);
x_39 = lean_box(0);
x_40 = x_91;
goto block_90;
}
block_90:
{
lean_object* x_41; lean_object* x_42; lean_object* x_43; lean_object* x_44; lean_object* x_45; lean_object* x_46; lean_object* x_47; lean_object* x_48; lean_object* x_49; 
x_41 = ((lean_object*)(l_panic___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__2___closed__3));
x_42 = ((lean_object*)(l_panic___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__2___closed__4));
lean_inc_ref(x_35);
x_43 = lean_alloc_closure((void*)(l_ReaderT_instFunctorOfMonad___redArg___lam__0), 6, 1);
lean_closure_set(x_43, 0, x_35);
x_44 = lean_alloc_closure((void*)(l_ReaderT_instFunctorOfMonad___redArg___lam__1), 6, 1);
lean_closure_set(x_44, 0, x_35);
x_45 = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(x_45, 0, x_43);
lean_ctor_set(x_45, 1, x_44);
x_46 = lean_alloc_closure((void*)(l_ReaderT_instApplicativeOfMonad___redArg___lam__1), 6, 1);
lean_closure_set(x_46, 0, x_38);
x_47 = lean_alloc_closure((void*)(l_ReaderT_instApplicativeOfMonad___redArg___lam__3), 6, 1);
lean_closure_set(x_47, 0, x_37);
x_48 = lean_alloc_closure((void*)(l_ReaderT_instApplicativeOfMonad___redArg___lam__4), 6, 1);
lean_closure_set(x_48, 0, x_36);
if (x_40 == 0)
{
lean_ctor_set(x_39, 4, x_46);
lean_ctor_set(x_39, 3, x_47);
lean_ctor_set(x_39, 2, x_48);
lean_ctor_set(x_39, 1, x_41);
lean_ctor_set(x_39, 0, x_45);
x_49 = x_39;
goto block_88;
}
else
{
lean_object* x_89; 
x_89 = lean_alloc_ctor(0, 5, 0);
lean_ctor_set(x_89, 0, x_45);
lean_ctor_set(x_89, 1, x_41);
lean_ctor_set(x_89, 2, x_48);
lean_ctor_set(x_89, 3, x_47);
lean_ctor_set(x_89, 4, x_46);
x_49 = x_89;
goto block_88;
}
block_88:
{
lean_object* x_50; 
if (x_34 == 0)
{
lean_ctor_set(x_33, 1, x_42);
lean_ctor_set(x_33, 0, x_49);
x_50 = x_33;
goto block_86;
}
else
{
lean_object* x_87; 
x_87 = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(x_87, 0, x_49);
lean_ctor_set(x_87, 1, x_42);
x_50 = x_87;
goto block_86;
}
block_86:
{
lean_object* x_51; lean_object* x_52; lean_object* x_53; lean_object* x_54; uint8_t x_55; uint8_t x_84; 
x_51 = l_ReaderT_instMonad___redArg(x_50);
x_52 = l_ReaderT_instMonad___redArg(x_51);
x_53 = lean_ctor_get(x_52, 0);
x_84 = !lean_is_exclusive(x_52);
if (x_84 == 0)
{
lean_object* x_85; 
x_85 = lean_ctor_get(x_52, 1);
lean_dec(x_85);
x_54 = x_52;
x_55 = x_84;
goto block_83;
}
else
{
lean_inc(x_53);
lean_dec(x_52);
x_54 = lean_box(0);
x_55 = x_84;
goto block_83;
}
block_83:
{
lean_object* x_56; lean_object* x_57; lean_object* x_58; lean_object* x_59; lean_object* x_60; uint8_t x_61; uint8_t x_81; 
x_56 = lean_ctor_get(x_53, 0);
x_57 = lean_ctor_get(x_53, 2);
x_58 = lean_ctor_get(x_53, 3);
x_59 = lean_ctor_get(x_53, 4);
x_81 = !lean_is_exclusive(x_53);
if (x_81 == 0)
{
lean_object* x_82; 
x_82 = lean_ctor_get(x_53, 1);
lean_dec(x_82);
x_60 = x_53;
x_61 = x_81;
goto block_80;
}
else
{
lean_inc(x_59);
lean_inc(x_58);
lean_inc(x_57);
lean_inc(x_56);
lean_dec(x_53);
x_60 = lean_box(0);
x_61 = x_81;
goto block_80;
}
block_80:
{
lean_object* x_62; lean_object* x_63; lean_object* x_64; lean_object* x_65; lean_object* x_66; lean_object* x_67; lean_object* x_68; lean_object* x_69; lean_object* x_70; 
x_62 = ((lean_object*)(l_panic___at___00Lean_isCtor_x3f___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__0_spec__0___closed__0));
x_63 = ((lean_object*)(l_panic___at___00Lean_isCtor_x3f___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__0_spec__0___closed__1));
lean_inc_ref(x_56);
x_64 = lean_alloc_closure((void*)(l_ReaderT_instFunctorOfMonad___redArg___lam__0), 6, 1);
lean_closure_set(x_64, 0, x_56);
x_65 = lean_alloc_closure((void*)(l_ReaderT_instFunctorOfMonad___redArg___lam__1), 6, 1);
lean_closure_set(x_65, 0, x_56);
x_66 = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(x_66, 0, x_64);
lean_ctor_set(x_66, 1, x_65);
x_67 = lean_alloc_closure((void*)(l_ReaderT_instApplicativeOfMonad___redArg___lam__1), 6, 1);
lean_closure_set(x_67, 0, x_59);
x_68 = lean_alloc_closure((void*)(l_ReaderT_instApplicativeOfMonad___redArg___lam__3), 6, 1);
lean_closure_set(x_68, 0, x_58);
x_69 = lean_alloc_closure((void*)(l_ReaderT_instApplicativeOfMonad___redArg___lam__4), 6, 1);
lean_closure_set(x_69, 0, x_57);
if (x_61 == 0)
{
lean_ctor_set(x_60, 4, x_67);
lean_ctor_set(x_60, 3, x_68);
lean_ctor_set(x_60, 2, x_69);
lean_ctor_set(x_60, 1, x_62);
lean_ctor_set(x_60, 0, x_66);
x_70 = x_60;
goto block_78;
}
else
{
lean_object* x_79; 
x_79 = lean_alloc_ctor(0, 5, 0);
lean_ctor_set(x_79, 0, x_66);
lean_ctor_set(x_79, 1, x_62);
lean_ctor_set(x_79, 2, x_69);
lean_ctor_set(x_79, 3, x_68);
lean_ctor_set(x_79, 4, x_67);
x_70 = x_79;
goto block_78;
}
block_78:
{
lean_object* x_71; 
if (x_55 == 0)
{
lean_ctor_set(x_54, 1, x_63);
lean_ctor_set(x_54, 0, x_70);
x_71 = x_54;
goto block_76;
}
else
{
lean_object* x_77; 
x_77 = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(x_77, 0, x_70);
lean_ctor_set(x_77, 1, x_63);
x_71 = x_77;
goto block_76;
}
block_76:
{
lean_object* x_72; lean_object* x_73; lean_object* x_74; lean_object* x_75; 
x_72 = lean_box(0);
x_73 = l_instInhabitedOfMonad___redArg(x_71, x_72);
x_74 = lean_panic_fn(x_73, x_1);
x_75 = lean_apply_8(x_74, x_2, x_3, x_4, x_5, x_6, x_7, x_8, lean_box(0));
return x_75;
}
}
}
}
}
}
}
}
}
}
}
}
}
}
LEAN_EXPORT lean_object* l_panic___at___00Lean_isCtor_x3f___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__0_spec__0___boxed(lean_object* x_1, lean_object* x_2, lean_object* x_3, lean_object* x_4, lean_object* x_5, lean_object* x_6, lean_object* x_7, lean_object* x_8, lean_object* x_9) {
_start:
{
lean_object* x_10; 
x_10 = l_panic___at___00Lean_isCtor_x3f___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__0_spec__0(x_1, x_2, x_3, x_4, x_5, x_6, x_7, x_8);
return x_10;
}
}
static lean_object* _init_l_Lean_isCtor_x3f___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__0___closed__3(void) {
_start:
{
lean_object* x_1; lean_object* x_2; lean_object* x_3; lean_object* x_4; lean_object* x_5; lean_object* x_6; 
x_1 = ((lean_object*)(l_Lean_isCtor_x3f___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__0___closed__2));
x_2 = lean_unsigned_to_nat(11u);
x_3 = lean_unsigned_to_nat(121u);
x_4 = ((lean_object*)(l_Lean_isCtor_x3f___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__0___closed__1));
x_5 = ((lean_object*)(l_Lean_isCtor_x3f___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__0___closed__0));
x_6 = l_mkPanicMessageWithDecl(x_5, x_4, x_3, x_2, x_1);
return x_6;
}
}
LEAN_EXPORT lean_object* l_Lean_isCtor_x3f___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__0(lean_object* x_1, lean_object* x_2, lean_object* x_3, lean_object* x_4, lean_object* x_5, lean_object* x_6, lean_object* x_7, lean_object* x_8) {
_start:
{
lean_object* x_10; lean_object* x_14; uint8_t x_15; lean_object* x_16; 
x_10 = lean_st_ref_get(x_8);
x_14 = lean_ctor_get(x_10, 0);
lean_inc_ref(x_14);
lean_dec(x_10);
x_15 = 0;
x_16 = l_Lean_Environment_findAsync_x3f(x_14, x_1, x_15);
if (lean_obj_tag(x_16) == 1)
{
lean_object* x_17; lean_object* x_18; uint8_t x_19; uint8_t x_36; 
x_17 = lean_ctor_get(x_16, 0);
x_36 = !lean_is_exclusive(x_16);
if (x_36 == 0)
{
x_18 = x_16;
x_19 = x_36;
goto block_35;
}
else
{
lean_inc(x_17);
lean_dec(x_16);
x_18 = lean_box(0);
x_19 = x_36;
goto block_35;
}
block_35:
{
uint8_t x_20; 
x_20 = lean_ctor_get_uint8(x_17, sizeof(void*)*3);
if (x_20 == 6)
{
lean_object* x_21; 
x_21 = l_Lean_AsyncConstantInfo_toConstantInfo(x_17);
if (lean_obj_tag(x_21) == 6)
{
lean_object* x_22; lean_object* x_23; uint8_t x_24; uint8_t x_32; 
lean_dec(x_8);
lean_dec_ref(x_7);
lean_dec(x_6);
lean_dec_ref(x_5);
lean_dec_ref(x_4);
lean_dec(x_3);
lean_dec_ref(x_2);
x_22 = lean_ctor_get(x_21, 0);
x_32 = !lean_is_exclusive(x_21);
if (x_32 == 0)
{
x_23 = x_21;
x_24 = x_32;
goto block_31;
}
else
{
lean_inc(x_22);
lean_dec(x_21);
x_23 = lean_box(0);
x_24 = x_32;
goto block_31;
}
block_31:
{
lean_object* x_25; 
if (x_19 == 0)
{
lean_ctor_set(x_18, 0, x_22);
x_25 = x_18;
goto block_29;
}
else
{
lean_object* x_30; 
x_30 = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(x_30, 0, x_22);
x_25 = x_30;
goto block_29;
}
block_29:
{
lean_object* x_26; 
if (x_24 == 0)
{
lean_ctor_set_tag(x_23, 0);
lean_ctor_set(x_23, 0, x_25);
x_26 = x_23;
goto block_27;
}
else
{
lean_object* x_28; 
x_28 = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(x_28, 0, x_25);
x_26 = x_28;
goto block_27;
}
block_27:
{
return x_26;
}
}
}
}
else
{
lean_object* x_33; lean_object* x_34; 
lean_dec_ref(x_21);
lean_del_object(x_18);
x_33 = lean_obj_once(&l_Lean_isCtor_x3f___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__0___closed__3, &l_Lean_isCtor_x3f___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__0___closed__3_once, _init_l_Lean_isCtor_x3f___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__0___closed__3);
x_34 = l_panic___at___00Lean_isCtor_x3f___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__0_spec__0(x_33, x_2, x_3, x_4, x_5, x_6, x_7, x_8);
return x_34;
}
}
else
{
lean_del_object(x_18);
lean_dec(x_17);
lean_dec(x_8);
lean_dec_ref(x_7);
lean_dec(x_6);
lean_dec_ref(x_5);
lean_dec_ref(x_4);
lean_dec(x_3);
lean_dec_ref(x_2);
goto block_13;
}
}
}
else
{
lean_dec(x_16);
lean_dec(x_8);
lean_dec_ref(x_7);
lean_dec(x_6);
lean_dec_ref(x_5);
lean_dec_ref(x_4);
lean_dec(x_3);
lean_dec_ref(x_2);
goto block_13;
}
block_13:
{
lean_object* x_11; lean_object* x_12; 
x_11 = lean_box(0);
x_12 = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(x_12, 0, x_11);
return x_12;
}
}
}
LEAN_EXPORT lean_object* l_Lean_isCtor_x3f___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__0___boxed(lean_object* x_1, lean_object* x_2, lean_object* x_3, lean_object* x_4, lean_object* x_5, lean_object* x_6, lean_object* x_7, lean_object* x_8, lean_object* x_9) {
_start:
{
lean_object* x_10; 
x_10 = l_Lean_isCtor_x3f___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__0(x_1, x_2, x_3, x_4, x_5, x_6, x_7, x_8);
return x_10;
}
}
static lean_object* _init_l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f___closed__4(void) {
_start:
{
lean_object* x_1; lean_object* x_2; 
x_1 = ((lean_object*)(l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f___closed__3));
x_2 = l_Lean_stringToMessageData(x_1);
return x_2;
}
}
static lean_object* _init_l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f___closed__6(void) {
_start:
{
lean_object* x_1; lean_object* x_2; 
x_1 = ((lean_object*)(l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f___closed__5));
x_2 = l_Lean_stringToMessageData(x_1);
return x_2;
}
}
static lean_object* _init_l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f___closed__8(void) {
_start:
{
lean_object* x_1; lean_object* x_2; 
x_1 = ((lean_object*)(l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f___closed__7));
x_2 = l_Lean_stringToMessageData(x_1);
return x_2;
}
}
static lean_object* _init_l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f___closed__12(void) {
_start:
{
lean_object* x_1; lean_object* x_2; lean_object* x_3; lean_object* x_4; lean_object* x_5; lean_object* x_6; 
x_1 = ((lean_object*)(l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f___closed__11));
x_2 = lean_unsigned_to_nat(6u);
x_3 = lean_unsigned_to_nat(54u);
x_4 = ((lean_object*)(l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f___closed__10));
x_5 = ((lean_object*)(l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f___closed__9));
x_6 = l_mkPanicMessageWithDecl(x_5, x_4, x_3, x_2, x_1);
return x_6;
}
}
static lean_object* _init_l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f___closed__14(void) {
_start:
{
lean_object* x_1; lean_object* x_2; 
x_1 = ((lean_object*)(l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f___closed__13));
x_2 = l_Lean_stringToMessageData(x_1);
return x_2;
}
}
LEAN_EXPORT lean_object* l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f(lean_object* x_1, lean_object* x_2, lean_object* x_3, lean_object* x_4, lean_object* x_5, lean_object* x_6, lean_object* x_7, lean_object* x_8) {
_start:
{
uint8_t x_16; uint8_t x_17; uint8_t x_18; lean_object* x_19; lean_object* x_20; lean_object* x_21; lean_object* x_22; uint8_t x_23; lean_object* x_24; lean_object* x_25; lean_object* x_50; uint8_t x_51; uint8_t x_52; lean_object* x_53; lean_object* x_54; lean_object* x_55; lean_object* x_56; lean_object* x_57; uint8_t x_58; lean_object* x_59; lean_object* x_60; lean_object* x_97; uint8_t x_98; lean_object* x_99; lean_object* x_100; lean_object* x_101; uint8_t x_102; lean_object* x_103; uint8_t x_104; uint8_t x_105; lean_object* x_106; lean_object* x_107; uint8_t x_108; lean_object* x_109; lean_object* x_110; lean_object* x_133; uint8_t x_134; lean_object* x_135; lean_object* x_136; lean_object* x_137; lean_object* x_138; lean_object* x_139; lean_object* x_140; uint8_t x_141; lean_object* x_142; uint8_t x_143; uint8_t x_144; lean_object* x_145; lean_object* x_146; lean_object* x_147; uint8_t x_148; lean_object* x_149; lean_object* x_150; lean_object* x_154; uint8_t x_155; lean_object* x_156; lean_object* x_157; lean_object* x_158; lean_object* x_159; lean_object* x_160; lean_object* x_161; uint8_t x_162; lean_object* x_163; uint8_t x_164; uint8_t x_165; lean_object* x_166; lean_object* x_167; lean_object* x_168; lean_object* x_169; uint8_t x_170; lean_object* x_171; lean_object* x_185; lean_object* x_186; lean_object* x_187; uint8_t x_188; lean_object* x_189; lean_object* x_190; lean_object* x_191; lean_object* x_192; lean_object* x_193; lean_object* x_194; lean_object* x_195; lean_object* x_242; lean_object* x_243; lean_object* x_244; lean_object* x_245; lean_object* x_246; lean_object* x_247; lean_object* x_248; lean_object* x_249; uint8_t x_250; lean_object* x_301; lean_object* x_302; lean_object* x_303; lean_object* x_304; uint8_t x_305; lean_object* x_306; lean_object* x_307; lean_object* x_308; lean_object* x_309; lean_object* x_331; lean_object* x_332; uint8_t x_333; lean_object* x_334; lean_object* x_335; lean_object* x_336; lean_object* x_337; lean_object* x_338; lean_object* x_368; uint8_t x_369; lean_object* x_370; lean_object* x_371; lean_object* x_372; lean_object* x_373; lean_object* x_374; lean_object* x_375; lean_object* x_376; 
x_16 = 0;
if (lean_obj_tag(x_1) == 3)
{
lean_object* x_385; 
x_385 = lean_ctor_get(x_1, 0);
lean_inc(x_385);
if (lean_obj_tag(x_385) == 1)
{
lean_object* x_386; 
x_386 = lean_ctor_get(x_385, 0);
if (lean_obj_tag(x_386) == 0)
{
lean_object* x_387; lean_object* x_388; lean_object* x_389; lean_object* x_390; uint8_t x_391; 
x_387 = lean_ctor_get(x_1, 1);
lean_inc(x_387);
x_388 = lean_ctor_get(x_1, 2);
lean_inc_ref(x_388);
lean_dec_ref(x_1);
x_389 = lean_ctor_get(x_385, 1);
x_390 = ((lean_object*)(l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f___closed__1));
x_391 = lean_string_dec_eq(x_389, x_390);
if (x_391 == 0)
{
x_185 = x_385;
x_186 = x_387;
x_187 = x_388;
x_188 = x_16;
x_189 = x_2;
x_190 = x_3;
x_191 = x_4;
x_192 = x_5;
x_193 = x_6;
x_194 = x_7;
x_195 = x_8;
goto block_241;
}
else
{
lean_object* x_392; lean_object* x_393; uint8_t x_394; 
x_392 = lean_array_get_size(x_388);
x_393 = lean_unsigned_to_nat(2u);
x_394 = lean_nat_dec_eq(x_392, x_393);
if (x_394 == 0)
{
x_185 = x_385;
x_186 = x_387;
x_187 = x_388;
x_188 = x_16;
x_189 = x_2;
x_190 = x_3;
x_191 = x_4;
x_192 = x_5;
x_193 = x_6;
x_194 = x_7;
x_195 = x_8;
goto block_241;
}
else
{
lean_object* x_395; lean_object* x_396; 
x_395 = lean_unsigned_to_nat(1u);
x_396 = lean_array_fget_borrowed(x_388, x_395);
if (lean_obj_tag(x_396) == 1)
{
lean_object* x_397; uint8_t x_398; lean_object* x_399; 
lean_inc_ref(x_396);
lean_dec_ref(x_388);
lean_dec(x_387);
lean_dec_ref(x_385);
x_397 = lean_ctor_get(x_396, 0);
lean_inc(x_397);
lean_dec_ref(x_396);
x_398 = 0;
lean_inc(x_397);
x_399 = l_Lean_Compiler_LCNF_Simp_findFunDecl_x27_x3f___redArg(x_398, x_397, x_6);
if (lean_obj_tag(x_399) == 0)
{
lean_object* x_400; 
x_400 = lean_ctor_get(x_399, 0);
lean_inc(x_400);
lean_dec_ref(x_399);
if (lean_obj_tag(x_400) == 1)
{
lean_object* x_401; lean_object* x_402; lean_object* x_403; 
lean_dec(x_397);
lean_dec_ref(x_4);
lean_dec_ref(x_2);
x_401 = lean_ctor_get(x_400, 0);
lean_inc(x_401);
lean_dec_ref(x_400);
x_402 = lean_ctor_get(x_401, 0);
lean_inc(x_402);
lean_dec(x_401);
x_403 = ((lean_object*)(l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f___closed__2));
x_331 = x_402;
x_332 = x_403;
x_333 = x_394;
x_334 = x_3;
x_335 = x_5;
x_336 = x_6;
x_337 = x_7;
x_338 = x_8;
goto block_367;
}
else
{
lean_object* x_404; 
lean_dec(x_400);
x_404 = l_Lean_Compiler_LCNF_findLetDecl_x3f___redArg(x_398, x_397, x_6);
if (lean_obj_tag(x_404) == 0)
{
lean_object* x_405; 
x_405 = lean_ctor_get(x_404, 0);
lean_inc(x_405);
lean_dec_ref(x_404);
if (lean_obj_tag(x_405) == 1)
{
lean_object* x_406; lean_object* x_407; 
lean_dec(x_397);
x_406 = lean_ctor_get(x_405, 0);
lean_inc(x_406);
lean_dec_ref(x_405);
x_407 = lean_ctor_get(x_406, 3);
lean_inc(x_407);
lean_dec(x_406);
if (lean_obj_tag(x_407) == 3)
{
lean_object* x_408; lean_object* x_409; lean_object* x_410; lean_object* x_411; 
x_408 = lean_ctor_get(x_407, 0);
lean_inc(x_408);
x_409 = lean_ctor_get(x_407, 1);
lean_inc(x_409);
x_410 = lean_ctor_get(x_407, 2);
lean_inc_ref(x_410);
lean_dec_ref(x_407);
lean_inc(x_8);
lean_inc_ref(x_7);
lean_inc(x_6);
lean_inc_ref(x_5);
lean_inc_ref(x_4);
lean_inc(x_3);
lean_inc_ref(x_2);
lean_inc(x_408);
x_411 = l_Lean_isCtor_x3f___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__0(x_408, x_2, x_3, x_4, x_5, x_6, x_7, x_8);
if (lean_obj_tag(x_411) == 0)
{
lean_object* x_412; 
x_412 = lean_ctor_get(x_411, 0);
lean_inc(x_412);
lean_dec_ref(x_411);
if (lean_obj_tag(x_412) == 0)
{
lean_object* x_413; 
x_413 = l_Lean_Compiler_LCNF_getPhase___redArg(x_5);
if (lean_obj_tag(x_413) == 0)
{
lean_object* x_414; uint8_t x_415; lean_object* x_416; 
x_414 = lean_ctor_get(x_413, 0);
lean_inc(x_414);
lean_dec_ref(x_413);
x_415 = lean_unbox(x_414);
lean_dec(x_414);
x_416 = l_Lean_Compiler_LCNF_getLocalDeclAt_x3f___redArg(x_408, x_415, x_8);
if (lean_obj_tag(x_416) == 0)
{
lean_object* x_417; 
x_417 = lean_ctor_get(x_416, 0);
lean_inc(x_417);
lean_dec_ref(x_416);
if (lean_obj_tag(x_417) == 1)
{
lean_dec_ref(x_417);
x_185 = x_408;
x_186 = x_409;
x_187 = x_410;
x_188 = x_394;
x_189 = x_2;
x_190 = x_3;
x_191 = x_4;
x_192 = x_5;
x_193 = x_6;
x_194 = x_7;
x_195 = x_8;
goto block_241;
}
else
{
lean_object* x_418; lean_object* x_419; lean_object* x_420; lean_object* x_421; lean_object* x_422; lean_object* x_423; lean_object* x_424; lean_object* x_425; uint8_t x_426; uint8_t x_431; 
lean_dec(x_417);
lean_dec_ref(x_410);
lean_dec(x_409);
lean_dec_ref(x_4);
lean_dec(x_3);
lean_dec_ref(x_2);
x_418 = lean_obj_once(&l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f___closed__4, &l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f___closed__4_once, _init_l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f___closed__4);
x_419 = l_Lean_MessageData_ofName(x_408);
x_420 = lean_alloc_ctor(7, 2, 0);
lean_ctor_set(x_420, 0, x_418);
lean_ctor_set(x_420, 1, x_419);
x_421 = lean_obj_once(&l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f___closed__6, &l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f___closed__6_once, _init_l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f___closed__6);
x_422 = lean_alloc_ctor(7, 2, 0);
lean_ctor_set(x_422, 0, x_420);
lean_ctor_set(x_422, 1, x_421);
x_423 = l_Lean_throwError___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__1___redArg(x_422, x_5, x_6, x_7, x_8);
lean_dec(x_8);
lean_dec_ref(x_7);
lean_dec(x_6);
lean_dec_ref(x_5);
x_424 = lean_ctor_get(x_423, 0);
x_431 = !lean_is_exclusive(x_423);
if (x_431 == 0)
{
x_425 = x_423;
x_426 = x_431;
goto block_430;
}
else
{
lean_inc(x_424);
lean_dec(x_423);
x_425 = lean_box(0);
x_426 = x_431;
goto block_430;
}
block_430:
{
lean_object* x_427; 
if (x_426 == 0)
{
x_427 = x_425;
goto block_428;
}
else
{
lean_object* x_429; 
x_429 = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(x_429, 0, x_424);
x_427 = x_429;
goto block_428;
}
block_428:
{
return x_427;
}
}
}
}
else
{
lean_object* x_432; lean_object* x_433; uint8_t x_434; uint8_t x_439; 
lean_dec_ref(x_410);
lean_dec(x_409);
lean_dec(x_408);
lean_dec(x_8);
lean_dec_ref(x_7);
lean_dec(x_6);
lean_dec_ref(x_5);
lean_dec_ref(x_4);
lean_dec(x_3);
lean_dec_ref(x_2);
x_432 = lean_ctor_get(x_416, 0);
x_439 = !lean_is_exclusive(x_416);
if (x_439 == 0)
{
x_433 = x_416;
x_434 = x_439;
goto block_438;
}
else
{
lean_inc(x_432);
lean_dec(x_416);
x_433 = lean_box(0);
x_434 = x_439;
goto block_438;
}
block_438:
{
lean_object* x_435; 
if (x_434 == 0)
{
x_435 = x_433;
goto block_436;
}
else
{
lean_object* x_437; 
x_437 = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(x_437, 0, x_432);
x_435 = x_437;
goto block_436;
}
block_436:
{
return x_435;
}
}
}
}
else
{
lean_object* x_440; lean_object* x_441; uint8_t x_442; uint8_t x_447; 
lean_dec_ref(x_410);
lean_dec(x_409);
lean_dec(x_408);
lean_dec(x_8);
lean_dec_ref(x_7);
lean_dec(x_6);
lean_dec_ref(x_5);
lean_dec_ref(x_4);
lean_dec(x_3);
lean_dec_ref(x_2);
x_440 = lean_ctor_get(x_413, 0);
x_447 = !lean_is_exclusive(x_413);
if (x_447 == 0)
{
x_441 = x_413;
x_442 = x_447;
goto block_446;
}
else
{
lean_inc(x_440);
lean_dec(x_413);
x_441 = lean_box(0);
x_442 = x_447;
goto block_446;
}
block_446:
{
lean_object* x_443; 
if (x_442 == 0)
{
x_443 = x_441;
goto block_444;
}
else
{
lean_object* x_445; 
x_445 = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(x_445, 0, x_440);
x_443 = x_445;
goto block_444;
}
block_444:
{
return x_443;
}
}
}
}
else
{
lean_object* x_448; lean_object* x_449; lean_object* x_450; lean_object* x_451; lean_object* x_452; lean_object* x_453; lean_object* x_454; lean_object* x_455; uint8_t x_456; uint8_t x_461; 
lean_dec_ref(x_412);
lean_dec_ref(x_410);
lean_dec(x_409);
lean_dec_ref(x_4);
lean_dec(x_3);
lean_dec_ref(x_2);
x_448 = lean_obj_once(&l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f___closed__8, &l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f___closed__8_once, _init_l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f___closed__8);
x_449 = l_Lean_MessageData_ofName(x_408);
x_450 = lean_alloc_ctor(7, 2, 0);
lean_ctor_set(x_450, 0, x_448);
lean_ctor_set(x_450, 1, x_449);
x_451 = lean_obj_once(&l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f___closed__6, &l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f___closed__6_once, _init_l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f___closed__6);
x_452 = lean_alloc_ctor(7, 2, 0);
lean_ctor_set(x_452, 0, x_450);
lean_ctor_set(x_452, 1, x_451);
x_453 = l_Lean_throwError___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__1___redArg(x_452, x_5, x_6, x_7, x_8);
lean_dec(x_8);
lean_dec_ref(x_7);
lean_dec(x_6);
lean_dec_ref(x_5);
x_454 = lean_ctor_get(x_453, 0);
x_461 = !lean_is_exclusive(x_453);
if (x_461 == 0)
{
x_455 = x_453;
x_456 = x_461;
goto block_460;
}
else
{
lean_inc(x_454);
lean_dec(x_453);
x_455 = lean_box(0);
x_456 = x_461;
goto block_460;
}
block_460:
{
lean_object* x_457; 
if (x_456 == 0)
{
x_457 = x_455;
goto block_458;
}
else
{
lean_object* x_459; 
x_459 = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(x_459, 0, x_454);
x_457 = x_459;
goto block_458;
}
block_458:
{
return x_457;
}
}
}
}
else
{
lean_object* x_462; lean_object* x_463; uint8_t x_464; uint8_t x_469; 
lean_dec_ref(x_410);
lean_dec(x_409);
lean_dec(x_408);
lean_dec(x_8);
lean_dec_ref(x_7);
lean_dec(x_6);
lean_dec_ref(x_5);
lean_dec_ref(x_4);
lean_dec(x_3);
lean_dec_ref(x_2);
x_462 = lean_ctor_get(x_411, 0);
x_469 = !lean_is_exclusive(x_411);
if (x_469 == 0)
{
x_463 = x_411;
x_464 = x_469;
goto block_468;
}
else
{
lean_inc(x_462);
lean_dec(x_411);
x_463 = lean_box(0);
x_464 = x_469;
goto block_468;
}
block_468:
{
lean_object* x_465; 
if (x_464 == 0)
{
x_465 = x_463;
goto block_466;
}
else
{
lean_object* x_467; 
x_467 = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(x_467, 0, x_462);
x_465 = x_467;
goto block_466;
}
block_466:
{
return x_465;
}
}
}
}
else
{
x_368 = x_407;
x_369 = x_394;
x_370 = x_2;
x_371 = x_3;
x_372 = x_4;
x_373 = x_5;
x_374 = x_6;
x_375 = x_7;
x_376 = x_8;
goto block_384;
}
}
else
{
lean_object* x_470; 
lean_dec(x_405);
x_470 = l_Lean_Compiler_LCNF_findParam_x3f___redArg(x_398, x_397, x_6);
lean_dec(x_397);
if (lean_obj_tag(x_470) == 0)
{
lean_object* x_471; 
x_471 = lean_ctor_get(x_470, 0);
lean_inc(x_471);
lean_dec_ref(x_470);
if (lean_obj_tag(x_471) == 0)
{
lean_object* x_472; lean_object* x_473; 
x_472 = lean_obj_once(&l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f___closed__12, &l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f___closed__12_once, _init_l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f___closed__12);
x_473 = l_panic___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__2(x_472, x_2, x_3, x_4, x_5, x_6, x_7, x_8);
return x_473;
}
else
{
lean_object* x_474; lean_object* x_475; lean_object* x_476; lean_object* x_477; uint8_t x_478; uint8_t x_483; 
lean_dec_ref(x_471);
lean_dec_ref(x_4);
lean_dec(x_3);
lean_dec_ref(x_2);
x_474 = lean_obj_once(&l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f___closed__14, &l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f___closed__14_once, _init_l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f___closed__14);
x_475 = l_Lean_throwError___at___00Lean_Compiler_LCNF_Simp_inlineCandidate_x3f_spec__1___redArg(x_474, x_5, x_6, x_7, x_8);
lean_dec(x_8);
lean_dec_ref(x_7);
lean_dec(x_6);
lean_dec_ref(x_5);
x_476 = lean_ctor_get(x_475, 0);
x_483 = !lean_is_exclusive(x_475);
if (x_483 == 0)
{
x_477 = x_475;
x_478 = x_483;
goto block_482;
}
else
{
lean_inc(x_476);
lean_dec(x_475);
x_477 = lean_box(0);
x_478 = x_483;
goto block_482;
}
block_482:
{
lean_object* x_479; 
if (x_478 == 0)
{
x_479 = x_477;
goto block_480;
}
else
{
lean_object* x_481; 
x_481 = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(x_481, 0, x_476);
x_479 = x_481;
goto block_480;
}
block_480:
{
return x_479;
}
}
}
}
else
{
lean_object* x_484; lean_object* x_485; uint8_t x_486; uint8_t x_491; 
lean_dec(x_8);
lean_dec_ref(x_7);
lean_dec(x_6);
lean_dec_ref(x_5);
lean_dec_ref(x_4);
lean_dec(x_3);
lean_dec_ref(x_2);
x_484 = lean_ctor_get(x_470, 0);
x_491 = !lean_is_exclusive(x_470);
if (x_491 == 0)
{
x_485 = x_470;
x_486 = x_491;
goto block_490;
}
else
{
lean_inc(x_484);
lean_dec(x_470);
x_485 = lean_box(0);
x_486 = x_491;
goto block_490;
}
block_490:
{
lean_object* x_487; 
if (x_486 == 0)
{
x_487 = x_485;
goto block_488;
}
else
{
lean_object* x_489; 
x_489 = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(x_489, 0, x_484);
x_487 = x_489;
goto block_488;
}
block_488:
{
return x_487;
}
}
}
}
}
else
{
lean_object* x_492; lean_object* x_493; uint8_t x_494; uint8_t x_499; 
lean_dec(x_397);
lean_dec(x_8);
lean_dec_ref(x_7);
lean_dec(x_6);
lean_dec_ref(x_5);
lean_dec_ref(x_4);
lean_dec(x_3);
lean_dec_ref(x_2);
x_492 = lean_ctor_get(x_404, 0);
x_499 = !lean_is_exclusive(x_404);
if (x_499 == 0)
{
x_493 = x_404;
x_494 = x_499;
goto block_498;
}
else
{
lean_inc(x_492);
lean_dec(x_404);
x_493 = lean_box(0);
x_494 = x_499;
goto block_498;
}
block_498:
{
lean_object* x_495; 
if (x_494 == 0)
{
x_495 = x_493;
goto block_496;
}
else
{
lean_object* x_497; 
x_497 = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(x_497, 0, x_492);
x_495 = x_497;
goto block_496;
}
block_496:
{
return x_495;
}
}
}
}
}
else
{
lean_object* x_500; lean_object* x_501; uint8_t x_502; uint8_t x_507; 
lean_dec(x_397);
lean_dec(x_8);
lean_dec_ref(x_7);
lean_dec(x_6);
lean_dec_ref(x_5);
lean_dec_ref(x_4);
lean_dec(x_3);
lean_dec_ref(x_2);
x_500 = lean_ctor_get(x_399, 0);
x_507 = !lean_is_exclusive(x_399);
if (x_507 == 0)
{
x_501 = x_399;
x_502 = x_507;
goto block_506;
}
else
{
lean_inc(x_500);
lean_dec(x_399);
x_501 = lean_box(0);
x_502 = x_507;
goto block_506;
}
block_506:
{
lean_object* x_503; 
if (x_502 == 0)
{
x_503 = x_501;
goto block_504;
}
else
{
lean_object* x_505; 
x_505 = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(x_505, 0, x_500);
x_503 = x_505;
goto block_504;
}
block_504:
{
return x_503;
}
}
}
}
else
{
x_185 = x_385;
x_186 = x_387;
x_187 = x_388;
x_188 = x_16;
x_189 = x_2;
x_190 = x_3;
x_191 = x_4;
x_192 = x_5;
x_193 = x_6;
x_194 = x_7;
x_195 = x_8;
goto block_241;
}
}
}
}
else
{
lean_object* x_508; lean_object* x_509; 
x_508 = lean_ctor_get(x_1, 1);
lean_inc(x_508);
x_509 = lean_ctor_get(x_1, 2);
lean_inc_ref(x_509);
lean_dec_ref(x_1);
x_185 = x_385;
x_186 = x_508;
x_187 = x_509;
x_188 = x_16;
x_189 = x_2;
x_190 = x_3;
x_191 = x_4;
x_192 = x_5;
x_193 = x_6;
x_194 = x_7;
x_195 = x_8;
goto block_241;
}
}
else
{
lean_object* x_510; lean_object* x_511; 
x_510 = lean_ctor_get(x_1, 1);
lean_inc(x_510);
x_511 = lean_ctor_get(x_1, 2);
lean_inc_ref(x_511);
lean_dec_ref(x_1);
x_185 = x_385;
x_186 = x_510;
x_187 = x_511;
x_188 = x_16;
x_189 = x_2;
x_190 = x_3;
x_191 = x_4;
x_192 = x_5;
x_193 = x_6;
x_194 = x_7;
x_195 = x_8;
goto block_241;
}
}
else
{
x_368 = x_1;
x_369 = x_16;
x_370 = x_2;
x_371 = x_3;
x_372 = x_4;
x_373 = x_5;
x_374 = x_6;
x_375 = x_7;
x_376 = x_8;
goto block_384;
}
block_12:
{
lean_object* x_10; lean_object* x_11; 
x_10 = lean_box(0);
x_11 = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(x_11, 0, x_10);
return x_11;
}
block_15:
{
lean_object* x_13; lean_object* x_14; 
x_13 = lean_box(0);
x_14 = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(x_14, 0, x_13);
return x_14;
}
block_49:
{
lean_object* x_26; 
x_26 = l_Lean_Compiler_LCNF_Simp_incInline___redArg(x_25);
lean_dec(x_25);
if (lean_obj_tag(x_26) == 0)
{
lean_object* x_27; uint8_t x_28; uint8_t x_39; 
x_39 = !lean_is_exclusive(x_26);
if (x_39 == 0)
{
lean_object* x_40; 
x_40 = lean_ctor_get(x_26, 0);
lean_dec(x_40);
x_27 = x_26;
x_28 = x_39;
goto block_38;
}
else
{
lean_dec(x_26);
x_27 = lean_box(0);
x_28 = x_39;
goto block_38;
}
block_38:
{
lean_object* x_29; lean_object* x_30; lean_object* x_31; lean_object* x_32; lean_object* x_33; lean_object* x_34; lean_object* x_35; 
x_29 = lean_ctor_get(x_20, 1);
lean_inc(x_29);
lean_dec_ref(x_20);
lean_inc(x_22);
lean_inc_ref(x_19);
x_30 = l_Lean_Compiler_LCNF_Decl_instantiateParamsLevelParams(x_23, x_19, x_22);
lean_inc(x_22);
x_31 = l_Lean_Compiler_LCNF_Code_instantiateValueLevelParams(x_21, x_29, x_22);
x_32 = l_Lean_Compiler_LCNF_Decl_instantiateTypeLevelParams___redArg(x_19, x_22);
x_33 = lean_alloc_ctor(0, 4, 3);
lean_ctor_set(x_33, 0, x_30);
lean_ctor_set(x_33, 1, x_31);
lean_ctor_set(x_33, 2, x_32);
lean_ctor_set(x_33, 3, x_24);
lean_ctor_set_uint8(x_33, sizeof(void*)*4, x_16);
lean_ctor_set_uint8(x_33, sizeof(void*)*4 + 1, x_18);
lean_ctor_set_uint8(x_33, sizeof(void*)*4 + 2, x_17);
x_34 = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(x_34, 0, x_33);
if (x_28 == 0)
{
lean_ctor_set(x_27, 0, x_34);
x_35 = x_27;
goto block_36;
}
else
{
lean_object* x_37; 
x_37 = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(x_37, 0, x_34);
x_35 = x_37;
goto block_36;
}
block_36:
{
return x_35;
}
}
}
else
{
lean_object* x_41; lean_object* x_42; uint8_t x_43; uint8_t x_48; 
lean_dec_ref(x_24);
lean_dec(x_22);
lean_dec_ref(x_21);
lean_dec_ref(x_20);
lean_dec_ref(x_19);
x_41 = lean_ctor_get(x_26, 0);
x_48 = !lean_is_exclusive(x_26);
if (x_48 == 0)
{
x_42 = x_26;
x_43 = x_48;
goto block_47;
}
else
{
lean_inc(x_41);
lean_dec(x_26);
x_42 = lean_box(0);
x_43 = x_48;
goto block_47;
}
block_47:
{
lean_object* x_44; 
if (x_43 == 0)
{
x_44 = x_42;
goto block_45;
}
else
{
lean_object* x_46; 
x_46 = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(x_46, 0, x_41);
x_44 = x_46;
goto block_45;
}
block_45:
{
return x_44;
}
}
}
}
block_96:
{
if (x_52 == 0)
{
lean_dec(x_56);
lean_dec(x_54);
x_17 = x_51;
x_18 = x_52;
x_19 = x_50;
x_20 = x_53;
x_21 = x_55;
x_22 = x_57;
x_23 = x_58;
x_24 = x_59;
x_25 = x_60;
goto block_49;
}
else
{
lean_object* x_61; 
lean_inc_ref(x_50);
x_61 = l_Lean_Compiler_LCNF_Decl_isCasesOnParam_x3f___redArg(x_50);
if (lean_obj_tag(x_61) == 1)
{
lean_object* x_62; lean_object* x_63; uint8_t x_64; uint8_t x_93; 
x_62 = lean_ctor_get(x_61, 0);
x_93 = !lean_is_exclusive(x_61);
if (x_93 == 0)
{
x_63 = x_61;
x_64 = x_93;
goto block_92;
}
else
{
lean_inc(x_62);
lean_dec(x_61);
x_63 = lean_box(0);
x_64 = x_93;
goto block_92;
}
block_92:
{
lean_object* x_65; uint8_t x_66; 
x_65 = lean_array_get_size(x_59);
x_66 = lean_nat_dec_lt(x_62, x_65);
if (x_66 == 0)
{
lean_object* x_67; lean_object* x_68; 
lean_dec(x_62);
lean_dec(x_60);
lean_dec_ref(x_59);
lean_dec(x_57);
lean_dec(x_56);
lean_dec_ref(x_55);
lean_dec(x_54);
lean_dec_ref(x_53);
lean_dec_ref(x_50);
x_67 = lean_box(0);
if (x_64 == 0)
{
lean_ctor_set_tag(x_63, 0);
lean_ctor_set(x_63, 0, x_67);
x_68 = x_63;
goto block_69;
}
else
{
lean_object* x_70; 
x_70 = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(x_70, 0, x_67);
x_68 = x_70;
goto block_69;
}
block_69:
{
return x_68;
}
}
else
{
lean_object* x_71; lean_object* x_72; lean_object* x_73; 
lean_del_object(x_63);
x_71 = lean_box(0);
x_72 = lean_array_get_borrowed(x_71, x_59, x_62);
lean_dec(x_62);
x_73 = l_Lean_Compiler_LCNF_Arg_isConstructorApp___redArg(x_72, x_54, x_56);
lean_dec(x_56);
lean_dec(x_54);
if (lean_obj_tag(x_73) == 0)
{
lean_object* x_74; lean_object* x_75; uint8_t x_76; uint8_t x_83; 
x_74 = lean_ctor_get(x_73, 0);
x_83 = !lean_is_exclusive(x_73);
if (x_83 == 0)
{
x_75 = x_73;
x_76 = x_83;
goto block_82;
}
else
{
lean_inc(x_74);
lean_dec(x_73);
x_75 = lean_box(0);
x_76 = x_83;
goto block_82;
}
block_82:
{
uint8_t x_77; 
x_77 = lean_unbox(x_74);
lean_dec(x_74);
if (x_77 == 0)
{
lean_object* x_78; lean_object* x_79; 
lean_dec(x_60);
lean_dec_ref(x_59);
lean_dec(x_57);
lean_dec_ref(x_55);
lean_dec_ref(x_53);
lean_dec_ref(x_50);
x_78 = lean_box(0);
if (x_76 == 0)
{
lean_ctor_set(x_75, 0, x_78);
x_79 = x_75;
goto block_80;
}
else
{
lean_object* x_81; 
x_81 = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(x_81, 0, x_78);
x_79 = x_81;
goto block_80;
}
block_80:
{
return x_79;
}
}
else
{
lean_del_object(x_75);
x_17 = x_51;
x_18 = x_52;
x_19 = x_50;
x_20 = x_53;
x_21 = x_55;
x_22 = x_57;
x_23 = x_58;
x_24 = x_59;
x_25 = x_60;
goto block_49;
}
}
}
else
{
lean_object* x_84; lean_object* x_85; uint8_t x_86; uint8_t x_91; 
lean_dec(x_60);
lean_dec_ref(x_59);
lean_dec(x_57);
lean_dec_ref(x_55);
lean_dec_ref(x_53);
lean_dec_ref(x_50);
x_84 = lean_ctor_get(x_73, 0);
x_91 = !lean_is_exclusive(x_73);
if (x_91 == 0)
{
x_85 = x_73;
x_86 = x_91;
goto block_90;
}
else
{
lean_inc(x_84);
lean_dec(x_73);
x_85 = lean_box(0);
x_86 = x_91;
goto block_90;
}
block_90:
{
lean_object* x_87; 
if (x_86 == 0)
{
x_87 = x_85;
goto block_88;
}
else
{
lean_object* x_89; 
x_89 = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(x_89, 0, x_84);
x_87 = x_89;
goto block_88;
}
block_88:
{
return x_87;
}
}
}
}
}
}
else
{
lean_object* x_94; lean_object* x_95; 
lean_dec(x_61);
lean_dec(x_60);
lean_dec_ref(x_59);
lean_dec(x_57);
lean_dec(x_56);
lean_dec_ref(x_55);
lean_dec(x_54);
lean_dec_ref(x_53);
lean_dec_ref(x_50);
x_94 = lean_box(0);
x_95 = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(x_95, 0, x_94);
return x_95;
}
}
}
block_132:
{
if (lean_obj_tag(x_110) == 0)
{
lean_object* x_111; lean_object* x_112; uint8_t x_113; uint8_t x_123; 
x_111 = lean_ctor_get(x_110, 0);
x_123 = !lean_is_exclusive(x_110);
if (x_123 == 0)
{
x_112 = x_110;
x_113 = x_123;
goto block_122;
}
else
{
lean_inc(x_111);
lean_dec(x_110);
x_112 = lean_box(0);
x_113 = x_123;
goto block_122;
}
block_122:
{
uint8_t x_114; 
x_114 = lean_unbox(x_111);
lean_dec(x_111);
if (x_114 == 0)
{
lean_del_object(x_112);
lean_dec(x_109);
lean_dec_ref(x_107);
lean_dec(x_106);
lean_dec_ref(x_103);
lean_dec(x_101);
lean_dec(x_100);
lean_dec_ref(x_99);
lean_dec_ref(x_97);
goto block_12;
}
else
{
if (x_108 == 0)
{
if (x_105 == 0)
{
lean_object* x_115; lean_object* x_116; uint8_t x_117; 
x_115 = l_Lean_Compiler_LCNF_Decl_getArity___redArg(x_97);
x_116 = lean_array_get_size(x_103);
x_117 = lean_nat_dec_lt(x_116, x_115);
lean_dec(x_115);
if (x_117 == 0)
{
lean_del_object(x_112);
x_50 = x_97;
x_51 = x_104;
x_52 = x_98;
x_53 = x_99;
x_54 = x_106;
x_55 = x_107;
x_56 = x_100;
x_57 = x_101;
x_58 = x_102;
x_59 = x_103;
x_60 = x_109;
goto block_96;
}
else
{
lean_object* x_118; lean_object* x_119; 
lean_dec(x_109);
lean_dec_ref(x_107);
lean_dec(x_106);
lean_dec_ref(x_103);
lean_dec(x_101);
lean_dec(x_100);
lean_dec_ref(x_99);
lean_dec_ref(x_97);
x_118 = lean_box(0);
if (x_113 == 0)
{
lean_ctor_set(x_112, 0, x_118);
x_119 = x_112;
goto block_120;
}
else
{
lean_object* x_121; 
x_121 = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(x_121, 0, x_118);
x_119 = x_121;
goto block_120;
}
block_120:
{
return x_119;
}
}
}
else
{
lean_del_object(x_112);
x_50 = x_97;
x_51 = x_104;
x_52 = x_98;
x_53 = x_99;
x_54 = x_106;
x_55 = x_107;
x_56 = x_100;
x_57 = x_101;
x_58 = x_102;
x_59 = x_103;
x_60 = x_109;
goto block_96;
}
}
else
{
lean_del_object(x_112);
x_50 = x_97;
x_51 = x_104;
x_52 = x_98;
x_53 = x_99;
x_54 = x_106;
x_55 = x_107;
x_56 = x_100;
x_57 = x_101;
x_58 = x_102;
x_59 = x_103;
x_60 = x_109;
goto block_96;
}
}
}
}
else
{
lean_object* x_124; lean_object* x_125; uint8_t x_126; uint8_t x_131; 
lean_dec(x_109);
lean_dec_ref(x_107);
lean_dec(x_106);
lean_dec_ref(x_103);
lean_dec(x_101);
lean_dec(x_100);
lean_dec_ref(x_99);
lean_dec_ref(x_97);
x_124 = lean_ctor_get(x_110, 0);
x_131 = !lean_is_exclusive(x_110);
if (x_131 == 0)
{
x_125 = x_110;
x_126 = x_131;
goto block_130;
}
else
{
lean_inc(x_124);
lean_dec(x_110);
x_125 = lean_box(0);
x_126 = x_131;
goto block_130;
}
block_130:
{
lean_object* x_127; 
if (x_126 == 0)
{
x_127 = x_125;
goto block_128;
}
else
{
lean_object* x_129; 
x_129 = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(x_129, 0, x_124);
x_127 = x_129;
goto block_128;
}
block_128:
{
return x_127;
}
}
}
}
block_153:
{
lean_object* x_151; lean_object* x_152; 
x_151 = lean_box(0);
lean_inc(x_139);
lean_inc(x_146);
lean_inc(x_150);
x_152 = lean_apply_9(x_138, x_151, x_145, x_150, x_137, x_149, x_146, x_136, x_139, lean_box(0));
x_97 = x_133;
x_98 = x_134;
x_99 = x_135;
x_100 = x_139;
x_101 = x_140;
x_102 = x_141;
x_103 = x_142;
x_104 = x_143;
x_105 = x_144;
x_106 = x_146;
x_107 = x_147;
x_108 = x_148;
x_109 = x_150;
x_110 = x_152;
goto block_132;
}
block_184:
{
if (x_170 == 0)
{
lean_object* x_172; 
x_172 = l_Lean_Compiler_LCNF_inBasePhase___redArg(x_169);
if (lean_obj_tag(x_172) == 0)
{
lean_object* x_173; uint8_t x_174; 
x_173 = lean_ctor_get(x_172, 0);
lean_inc(x_173);
lean_dec_ref(x_172);
x_174 = lean_unbox(x_173);
lean_dec(x_173);
if (x_174 == 0)
{
lean_object* x_175; lean_object* x_176; 
x_175 = lean_box(0);
lean_inc(x_160);
lean_inc(x_167);
lean_inc(x_171);
x_176 = lean_apply_9(x_159, x_175, x_166, x_171, x_158, x_169, x_167, x_157, x_160, lean_box(0));
x_97 = x_154;
x_98 = x_155;
x_99 = x_156;
x_100 = x_160;
x_101 = x_161;
x_102 = x_162;
x_103 = x_163;
x_104 = x_164;
x_105 = x_165;
x_106 = x_167;
x_107 = x_168;
x_108 = x_170;
x_109 = x_171;
x_110 = x_176;
goto block_132;
}
else
{
lean_object* x_177; lean_object* x_178; 
x_177 = lean_ctor_get(x_156, 0);
x_178 = l_Lean_Meta_isInstance___redArg(x_177, x_160);
if (lean_obj_tag(x_178) == 0)
{
lean_object* x_179; uint8_t x_180; 
x_179 = lean_ctor_get(x_178, 0);
lean_inc(x_179);
lean_dec_ref(x_178);
x_180 = lean_unbox(x_179);
lean_dec(x_179);
if (x_180 == 0)
{
if (lean_obj_tag(x_177) == 1)
{
lean_object* x_181; lean_object* x_182; uint8_t x_183; 
x_181 = lean_ctor_get(x_177, 1);
x_182 = ((lean_object*)(l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f___closed__0));
x_183 = lean_string_dec_eq(x_181, x_182);
if (x_183 == 0)
{
x_133 = x_154;
x_134 = x_155;
x_135 = x_156;
x_136 = x_157;
x_137 = x_158;
x_138 = x_159;
x_139 = x_160;
x_140 = x_161;
x_141 = x_162;
x_142 = x_163;
x_143 = x_164;
x_144 = x_165;
x_145 = x_166;
x_146 = x_167;
x_147 = x_168;
x_148 = x_170;
x_149 = x_169;
x_150 = x_171;
goto block_153;
}
else
{
lean_dec(x_171);
lean_dec_ref(x_169);
lean_dec_ref(x_168);
lean_dec(x_167);
lean_dec_ref(x_166);
lean_dec_ref(x_163);
lean_dec(x_161);
lean_dec(x_160);
lean_dec_ref(x_159);
lean_dec_ref(x_158);
lean_dec_ref(x_157);
lean_dec_ref(x_156);
lean_dec_ref(x_154);
goto block_12;
}
}
else
{
x_133 = x_154;
x_134 = x_155;
x_135 = x_156;
x_136 = x_157;
x_137 = x_158;
x_138 = x_159;
x_139 = x_160;
x_140 = x_161;
x_141 = x_162;
x_142 = x_163;
x_143 = x_164;
x_144 = x_165;
x_145 = x_166;
x_146 = x_167;
x_147 = x_168;
x_148 = x_170;
x_149 = x_169;
x_150 = x_171;
goto block_153;
}
}
else
{
lean_dec(x_171);
lean_dec_ref(x_169);
lean_dec_ref(x_168);
lean_dec(x_167);
lean_dec_ref(x_166);
lean_dec_ref(x_163);
lean_dec(x_161);
lean_dec(x_160);
lean_dec_ref(x_159);
lean_dec_ref(x_158);
lean_dec_ref(x_157);
lean_dec_ref(x_156);
lean_dec_ref(x_154);
goto block_12;
}
}
else
{
lean_dec_ref(x_169);
lean_dec_ref(x_166);
lean_dec_ref(x_159);
lean_dec_ref(x_158);
lean_dec_ref(x_157);
x_97 = x_154;
x_98 = x_155;
x_99 = x_156;
x_100 = x_160;
x_101 = x_161;
x_102 = x_162;
x_103 = x_163;
x_104 = x_164;
x_105 = x_165;
x_106 = x_167;
x_107 = x_168;
x_108 = x_170;
x_109 = x_171;
x_110 = x_178;
goto block_132;
}
}
}
else
{
lean_dec_ref(x_169);
lean_dec_ref(x_166);
lean_dec_ref(x_159);
lean_dec_ref(x_158);
lean_dec_ref(x_157);
x_97 = x_154;
x_98 = x_155;
x_99 = x_156;
x_100 = x_160;
x_101 = x_161;
x_102 = x_162;
x_103 = x_163;
x_104 = x_164;
x_105 = x_165;
x_106 = x_167;
x_107 = x_168;
x_108 = x_170;
x_109 = x_171;
x_110 = x_172;
goto block_132;
}
}
else
{
lean_dec_ref(x_169);
lean_dec_ref(x_166);
lean_dec_ref(x_159);
lean_dec_ref(x_158);
lean_dec_ref(x_157);
x_50 = x_154;
x_51 = x_164;
x_52 = x_155;
x_53 = x_156;
x_54 = x_167;
x_55 = x_168;
x_56 = x_160;
x_57 = x_161;
x_58 = x_162;
x_59 = x_163;
x_60 = x_171;
goto block_96;
}
}
block_241:
{
lean_object* x_196; uint8_t x_197; 
x_196 = lean_ctor_get(x_189, 1);
x_197 = lean_ctor_get_uint8(x_196, 3);
if (x_197 == 0)
{
lean_object* x_198; lean_object* x_199; 
lean_dec(x_195);
lean_dec_ref(x_194);
lean_dec(x_193);
lean_dec_ref(x_192);
lean_dec_ref(x_191);
lean_dec(x_190);
lean_dec_ref(x_189);
lean_dec_ref(x_187);
lean_dec(x_186);
lean_dec(x_185);
x_198 = lean_box(0);
x_199 = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(x_199, 0, x_198);
return x_199;
}
else
{
uint8_t x_200; lean_object* x_201; 
x_200 = lean_ctor_get_uint8(x_196, 1);
x_201 = l_Lean_Compiler_LCNF_getPhase___redArg(x_192);
if (lean_obj_tag(x_201) == 0)
{
lean_object* x_202; uint8_t x_203; lean_object* x_204; 
x_202 = lean_ctor_get(x_201, 0);
lean_inc(x_202);
lean_dec_ref(x_201);
x_203 = lean_unbox(x_202);
x_204 = l_Lean_Compiler_LCNF_getDeclAt_x3f(x_185, x_203, x_194, x_195);
if (lean_obj_tag(x_204) == 0)
{
lean_object* x_205; lean_object* x_206; uint8_t x_207; uint8_t x_224; 
x_205 = lean_ctor_get(x_204, 0);
x_224 = !lean_is_exclusive(x_204);
if (x_224 == 0)
{
x_206 = x_204;
x_207 = x_224;
goto block_223;
}
else
{
lean_inc(x_205);
lean_dec(x_204);
x_206 = lean_box(0);
x_207 = x_224;
goto block_223;
}
block_223:
{
if (lean_obj_tag(x_205) == 1)
{
lean_object* x_208; uint8_t x_209; uint8_t x_210; 
x_208 = lean_ctor_get(x_205, 0);
lean_inc(x_208);
lean_dec_ref(x_205);
x_209 = lean_unbox(x_202);
lean_dec(x_202);
x_210 = l_Lean_Compiler_LCNF_Phase_toPurity(x_209);
if (x_210 == 0)
{
lean_object* x_211; 
x_211 = lean_ctor_get(x_208, 1);
if (lean_obj_tag(x_211) == 0)
{
lean_object* x_212; uint8_t x_213; lean_object* x_214; lean_object* x_215; lean_object* x_216; lean_object* x_217; uint8_t x_218; 
lean_del_object(x_206);
x_212 = lean_ctor_get(x_208, 0);
lean_inc_ref(x_212);
x_213 = lean_ctor_get_uint8(x_208, sizeof(void*)*3);
x_214 = lean_ctor_get(x_211, 0);
lean_inc_ref(x_214);
x_215 = lean_box(x_16);
x_216 = lean_box(x_197);
lean_inc_ref(x_214);
lean_inc(x_208);
x_217 = lean_alloc_closure((void*)(l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f___lam__0___boxed), 13, 4);
lean_closure_set(x_217, 0, x_208);
lean_closure_set(x_217, 1, x_214);
lean_closure_set(x_217, 2, x_215);
lean_closure_set(x_217, 3, x_216);
x_218 = l_Lean_Compiler_LCNF_Decl_inlineIfReduceAttr___redArg(x_208);
if (x_218 == 0)
{
if (x_213 == 0)
{
x_154 = x_208;
x_155 = x_218;
x_156 = x_212;
x_157 = x_194;
x_158 = x_191;
x_159 = x_217;
x_160 = x_195;
x_161 = x_186;
x_162 = x_210;
x_163 = x_187;
x_164 = x_213;
x_165 = x_200;
x_166 = x_189;
x_167 = x_193;
x_168 = x_214;
x_169 = x_192;
x_170 = x_188;
x_171 = x_190;
goto block_184;
}
else
{
lean_dec_ref(x_217);
lean_dec_ref(x_214);
lean_dec_ref(x_212);
lean_dec(x_208);
lean_dec(x_195);
lean_dec_ref(x_194);
lean_dec(x_193);
lean_dec_ref(x_192);
lean_dec_ref(x_191);
lean_dec(x_190);
lean_dec_ref(x_189);
lean_dec_ref(x_187);
lean_dec(x_186);
goto block_12;
}
}
else
{
x_154 = x_208;
x_155 = x_218;
x_156 = x_212;
x_157 = x_194;
x_158 = x_191;
x_159 = x_217;
x_160 = x_195;
x_161 = x_186;
x_162 = x_210;
x_163 = x_187;
x_164 = x_213;
x_165 = x_200;
x_166 = x_189;
x_167 = x_193;
x_168 = x_214;
x_169 = x_192;
x_170 = x_188;
x_171 = x_190;
goto block_184;
}
}
else
{
lean_object* x_219; lean_object* x_220; 
lean_dec(x_208);
lean_dec(x_195);
lean_dec_ref(x_194);
lean_dec(x_193);
lean_dec_ref(x_192);
lean_dec_ref(x_191);
lean_dec(x_190);
lean_dec_ref(x_189);
lean_dec_ref(x_187);
lean_dec(x_186);
x_219 = lean_box(0);
if (x_207 == 0)
{
lean_ctor_set(x_206, 0, x_219);
x_220 = x_206;
goto block_221;
}
else
{
lean_object* x_222; 
x_222 = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(x_222, 0, x_219);
x_220 = x_222;
goto block_221;
}
block_221:
{
return x_220;
}
}
}
else
{
lean_dec(x_208);
lean_del_object(x_206);
lean_dec(x_195);
lean_dec_ref(x_194);
lean_dec(x_193);
lean_dec_ref(x_192);
lean_dec_ref(x_191);
lean_dec(x_190);
lean_dec_ref(x_189);
lean_dec_ref(x_187);
lean_dec(x_186);
goto block_15;
}
}
else
{
lean_del_object(x_206);
lean_dec(x_205);
lean_dec(x_202);
lean_dec(x_195);
lean_dec_ref(x_194);
lean_dec(x_193);
lean_dec_ref(x_192);
lean_dec_ref(x_191);
lean_dec(x_190);
lean_dec_ref(x_189);
lean_dec_ref(x_187);
lean_dec(x_186);
goto block_15;
}
}
}
else
{
lean_object* x_225; lean_object* x_226; uint8_t x_227; uint8_t x_232; 
lean_dec(x_202);
lean_dec(x_195);
lean_dec_ref(x_194);
lean_dec(x_193);
lean_dec_ref(x_192);
lean_dec_ref(x_191);
lean_dec(x_190);
lean_dec_ref(x_189);
lean_dec_ref(x_187);
lean_dec(x_186);
x_225 = lean_ctor_get(x_204, 0);
x_232 = !lean_is_exclusive(x_204);
if (x_232 == 0)
{
x_226 = x_204;
x_227 = x_232;
goto block_231;
}
else
{
lean_inc(x_225);
lean_dec(x_204);
x_226 = lean_box(0);
x_227 = x_232;
goto block_231;
}
block_231:
{
lean_object* x_228; 
if (x_227 == 0)
{
x_228 = x_226;
goto block_229;
}
else
{
lean_object* x_230; 
x_230 = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(x_230, 0, x_225);
x_228 = x_230;
goto block_229;
}
block_229:
{
return x_228;
}
}
}
}
else
{
lean_object* x_233; lean_object* x_234; uint8_t x_235; uint8_t x_240; 
lean_dec(x_195);
lean_dec_ref(x_194);
lean_dec(x_193);
lean_dec_ref(x_192);
lean_dec_ref(x_191);
lean_dec(x_190);
lean_dec_ref(x_189);
lean_dec_ref(x_187);
lean_dec(x_186);
lean_dec(x_185);
x_233 = lean_ctor_get(x_201, 0);
x_240 = !lean_is_exclusive(x_201);
if (x_240 == 0)
{
x_234 = x_201;
x_235 = x_240;
goto block_239;
}
else
{
lean_inc(x_233);
lean_dec(x_201);
x_234 = lean_box(0);
x_235 = x_240;
goto block_239;
}
block_239:
{
lean_object* x_236; 
if (x_235 == 0)
{
x_236 = x_234;
goto block_237;
}
else
{
lean_object* x_238; 
x_238 = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(x_238, 0, x_233);
x_236 = x_238;
goto block_237;
}
block_237:
{
return x_236;
}
}
}
}
}
block_300:
{
lean_object* x_251; 
x_251 = l_Lean_Compiler_LCNF_Simp_incInlineLocal___redArg(x_248);
if (lean_obj_tag(x_251) == 0)
{
lean_object* x_252; lean_object* x_253; lean_object* x_254; lean_object* x_255; lean_object* x_256; uint8_t x_257; lean_object* x_258; lean_object* x_259; lean_object* x_260; lean_object* x_261; uint8_t x_262; uint8_t x_291; 
lean_dec_ref(x_251);
x_252 = lean_st_ref_take(x_248);
x_253 = lean_ctor_get(x_252, 0);
x_254 = lean_ctor_get(x_252, 1);
x_255 = lean_ctor_get(x_252, 2);
x_256 = lean_ctor_get(x_252, 3);
x_257 = lean_ctor_get_uint8(x_252, sizeof(void*)*7);
x_258 = lean_ctor_get(x_252, 4);
x_259 = lean_ctor_get(x_252, 5);
x_260 = lean_ctor_get(x_252, 6);
x_291 = !lean_is_exclusive(x_252);
if (x_291 == 0)
{
x_261 = x_252;
x_262 = x_291;
goto block_290;
}
else
{
lean_inc(x_260);
lean_inc(x_259);
lean_inc(x_258);
lean_inc(x_256);
lean_inc(x_255);
lean_inc(x_254);
lean_inc(x_253);
lean_dec(x_252);
x_261 = lean_box(0);
x_262 = x_291;
goto block_290;
}
block_290:
{
lean_object* x_263; lean_object* x_264; lean_object* x_265; 
x_263 = lean_unsigned_to_nat(1u);
x_264 = lean_nat_add(x_260, x_263);
lean_dec(x_260);
if (x_262 == 0)
{
lean_ctor_set(x_261, 6, x_264);
x_265 = x_261;
goto block_288;
}
else
{
lean_object* x_289; 
x_289 = lean_alloc_ctor(0, 7, 1);
lean_ctor_set(x_289, 0, x_253);
lean_ctor_set(x_289, 1, x_254);
lean_ctor_set(x_289, 2, x_255);
lean_ctor_set(x_289, 3, x_256);
lean_ctor_set(x_289, 4, x_258);
lean_ctor_set(x_289, 5, x_259);
lean_ctor_set(x_289, 6, x_264);
lean_ctor_set_uint8(x_289, sizeof(void*)*7, x_257);
x_265 = x_289;
goto block_288;
}
block_288:
{
lean_object* x_266; lean_object* x_267; 
x_266 = lean_st_ref_set(x_248, x_265);
lean_dec(x_248);
x_267 = l_Lean_Compiler_LCNF_getType(x_244, x_243, x_246, x_242, x_245);
lean_dec(x_245);
lean_dec_ref(x_242);
lean_dec(x_246);
lean_dec_ref(x_243);
if (lean_obj_tag(x_267) == 0)
{
lean_object* x_268; lean_object* x_269; uint8_t x_270; uint8_t x_279; 
x_268 = lean_ctor_get(x_267, 0);
x_279 = !lean_is_exclusive(x_267);
if (x_279 == 0)
{
x_269 = x_267;
x_270 = x_279;
goto block_278;
}
else
{
lean_inc(x_268);
lean_dec(x_267);
x_269 = lean_box(0);
x_270 = x_279;
goto block_278;
}
block_278:
{
lean_object* x_271; lean_object* x_272; lean_object* x_273; lean_object* x_274; lean_object* x_275; 
x_271 = lean_ctor_get(x_249, 2);
lean_inc_ref(x_271);
x_272 = lean_ctor_get(x_249, 4);
lean_inc_ref(x_272);
lean_dec_ref(x_249);
x_273 = lean_alloc_ctor(0, 4, 3);
lean_ctor_set(x_273, 0, x_271);
lean_ctor_set(x_273, 1, x_272);
lean_ctor_set(x_273, 2, x_268);
lean_ctor_set(x_273, 3, x_247);
lean_ctor_set_uint8(x_273, sizeof(void*)*4, x_250);
lean_ctor_set_uint8(x_273, sizeof(void*)*4 + 1, x_16);
lean_ctor_set_uint8(x_273, sizeof(void*)*4 + 2, x_16);
x_274 = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(x_274, 0, x_273);
if (x_270 == 0)
{
lean_ctor_set(x_269, 0, x_274);
x_275 = x_269;
goto block_276;
}
else
{
lean_object* x_277; 
x_277 = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(x_277, 0, x_274);
x_275 = x_277;
goto block_276;
}
block_276:
{
return x_275;
}
}
}
else
{
lean_object* x_280; lean_object* x_281; uint8_t x_282; uint8_t x_287; 
lean_dec_ref(x_249);
lean_dec_ref(x_247);
x_280 = lean_ctor_get(x_267, 0);
x_287 = !lean_is_exclusive(x_267);
if (x_287 == 0)
{
x_281 = x_267;
x_282 = x_287;
goto block_286;
}
else
{
lean_inc(x_280);
lean_dec(x_267);
x_281 = lean_box(0);
x_282 = x_287;
goto block_286;
}
block_286:
{
lean_object* x_283; 
if (x_282 == 0)
{
x_283 = x_281;
goto block_284;
}
else
{
lean_object* x_285; 
x_285 = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(x_285, 0, x_280);
x_283 = x_285;
goto block_284;
}
block_284:
{
return x_283;
}
}
}
}
}
}
else
{
lean_object* x_292; lean_object* x_293; uint8_t x_294; uint8_t x_299; 
lean_dec_ref(x_249);
lean_dec(x_248);
lean_dec_ref(x_247);
lean_dec(x_246);
lean_dec(x_245);
lean_dec(x_244);
lean_dec_ref(x_243);
lean_dec_ref(x_242);
x_292 = lean_ctor_get(x_251, 0);
x_299 = !lean_is_exclusive(x_251);
if (x_299 == 0)
{
x_293 = x_251;
x_294 = x_299;
goto block_298;
}
else
{
lean_inc(x_292);
lean_dec(x_251);
x_293 = lean_box(0);
x_294 = x_299;
goto block_298;
}
block_298:
{
lean_object* x_295; 
if (x_294 == 0)
{
x_295 = x_293;
goto block_296;
}
else
{
lean_object* x_297; 
x_297 = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(x_297, 0, x_292);
x_295 = x_297;
goto block_296;
}
block_296:
{
return x_295;
}
}
}
}
block_330:
{
lean_object* x_310; 
x_310 = l_Lean_Compiler_LCNF_Simp_shouldInlineLocal___redArg(x_309, x_308, x_302);
if (lean_obj_tag(x_310) == 0)
{
if (x_305 == 0)
{
lean_object* x_311; lean_object* x_312; uint8_t x_313; uint8_t x_321; 
x_311 = lean_ctor_get(x_310, 0);
x_321 = !lean_is_exclusive(x_310);
if (x_321 == 0)
{
x_312 = x_310;
x_313 = x_321;
goto block_320;
}
else
{
lean_inc(x_311);
lean_dec(x_310);
x_312 = lean_box(0);
x_313 = x_321;
goto block_320;
}
block_320:
{
uint8_t x_314; 
x_314 = lean_unbox(x_311);
if (x_314 == 0)
{
lean_object* x_315; lean_object* x_316; 
lean_dec(x_311);
lean_dec_ref(x_309);
lean_dec(x_308);
lean_dec_ref(x_307);
lean_dec(x_306);
lean_dec(x_304);
lean_dec(x_303);
lean_dec_ref(x_302);
lean_dec_ref(x_301);
x_315 = lean_box(0);
if (x_313 == 0)
{
lean_ctor_set(x_312, 0, x_315);
x_316 = x_312;
goto block_317;
}
else
{
lean_object* x_318; 
x_318 = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(x_318, 0, x_315);
x_316 = x_318;
goto block_317;
}
block_317:
{
return x_316;
}
}
else
{
uint8_t x_319; 
lean_del_object(x_312);
x_319 = lean_unbox(x_311);
lean_dec(x_311);
x_242 = x_301;
x_243 = x_302;
x_244 = x_303;
x_245 = x_304;
x_246 = x_306;
x_247 = x_307;
x_248 = x_308;
x_249 = x_309;
x_250 = x_319;
goto block_300;
}
}
}
else
{
lean_dec_ref(x_310);
x_242 = x_301;
x_243 = x_302;
x_244 = x_303;
x_245 = x_304;
x_246 = x_306;
x_247 = x_307;
x_248 = x_308;
x_249 = x_309;
x_250 = x_305;
goto block_300;
}
}
else
{
lean_object* x_322; lean_object* x_323; uint8_t x_324; uint8_t x_329; 
lean_dec_ref(x_309);
lean_dec(x_308);
lean_dec_ref(x_307);
lean_dec(x_306);
lean_dec(x_304);
lean_dec(x_303);
lean_dec_ref(x_302);
lean_dec_ref(x_301);
x_322 = lean_ctor_get(x_310, 0);
x_329 = !lean_is_exclusive(x_310);
if (x_329 == 0)
{
x_323 = x_310;
x_324 = x_329;
goto block_328;
}
else
{
lean_inc(x_322);
lean_dec(x_310);
x_323 = lean_box(0);
x_324 = x_329;
goto block_328;
}
block_328:
{
lean_object* x_325; 
if (x_324 == 0)
{
x_325 = x_323;
goto block_326;
}
else
{
lean_object* x_327; 
x_327 = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(x_327, 0, x_322);
x_325 = x_327;
goto block_326;
}
block_326:
{
return x_325;
}
}
}
}
block_367:
{
uint8_t x_339; lean_object* x_340; 
x_339 = 0;
lean_inc(x_331);
x_340 = l_Lean_Compiler_LCNF_Simp_findFunDecl_x27_x3f___redArg(x_339, x_331, x_336);
if (lean_obj_tag(x_340) == 0)
{
lean_object* x_341; lean_object* x_342; uint8_t x_343; uint8_t x_358; 
x_341 = lean_ctor_get(x_340, 0);
x_358 = !lean_is_exclusive(x_340);
if (x_358 == 0)
{
x_342 = x_340;
x_343 = x_358;
goto block_357;
}
else
{
lean_inc(x_341);
lean_dec(x_340);
x_342 = lean_box(0);
x_343 = x_358;
goto block_357;
}
block_357:
{
if (lean_obj_tag(x_341) == 1)
{
if (x_333 == 0)
{
lean_object* x_344; lean_object* x_345; lean_object* x_346; uint8_t x_347; 
x_344 = lean_ctor_get(x_341, 0);
lean_inc(x_344);
lean_dec_ref(x_341);
x_345 = lean_unsigned_to_nat(0u);
x_346 = lean_array_get_size(x_332);
x_347 = lean_nat_dec_lt(x_345, x_346);
if (x_347 == 0)
{
lean_object* x_348; lean_object* x_349; 
lean_dec(x_344);
lean_dec(x_338);
lean_dec_ref(x_337);
lean_dec(x_336);
lean_dec_ref(x_335);
lean_dec(x_334);
lean_dec_ref(x_332);
lean_dec(x_331);
x_348 = lean_box(0);
if (x_343 == 0)
{
lean_ctor_set(x_342, 0, x_348);
x_349 = x_342;
goto block_350;
}
else
{
lean_object* x_351; 
x_351 = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(x_351, 0, x_348);
x_349 = x_351;
goto block_350;
}
block_350:
{
return x_349;
}
}
else
{
lean_del_object(x_342);
x_301 = x_337;
x_302 = x_335;
x_303 = x_331;
x_304 = x_338;
x_305 = x_333;
x_306 = x_336;
x_307 = x_332;
x_308 = x_334;
x_309 = x_344;
goto block_330;
}
}
else
{
lean_object* x_352; 
lean_del_object(x_342);
x_352 = lean_ctor_get(x_341, 0);
lean_inc(x_352);
lean_dec_ref(x_341);
x_301 = x_337;
x_302 = x_335;
x_303 = x_331;
x_304 = x_338;
x_305 = x_333;
x_306 = x_336;
x_307 = x_332;
x_308 = x_334;
x_309 = x_352;
goto block_330;
}
}
else
{
lean_object* x_353; lean_object* x_354; 
lean_dec(x_341);
lean_dec(x_338);
lean_dec_ref(x_337);
lean_dec(x_336);
lean_dec_ref(x_335);
lean_dec(x_334);
lean_dec_ref(x_332);
lean_dec(x_331);
x_353 = lean_box(0);
if (x_343 == 0)
{
lean_ctor_set(x_342, 0, x_353);
x_354 = x_342;
goto block_355;
}
else
{
lean_object* x_356; 
x_356 = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(x_356, 0, x_353);
x_354 = x_356;
goto block_355;
}
block_355:
{
return x_354;
}
}
}
}
else
{
lean_object* x_359; lean_object* x_360; uint8_t x_361; uint8_t x_366; 
lean_dec(x_338);
lean_dec_ref(x_337);
lean_dec(x_336);
lean_dec_ref(x_335);
lean_dec(x_334);
lean_dec_ref(x_332);
lean_dec(x_331);
x_359 = lean_ctor_get(x_340, 0);
x_366 = !lean_is_exclusive(x_340);
if (x_366 == 0)
{
x_360 = x_340;
x_361 = x_366;
goto block_365;
}
else
{
lean_inc(x_359);
lean_dec(x_340);
x_360 = lean_box(0);
x_361 = x_366;
goto block_365;
}
block_365:
{
lean_object* x_362; 
if (x_361 == 0)
{
x_362 = x_360;
goto block_363;
}
else
{
lean_object* x_364; 
x_364 = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(x_364, 0, x_359);
x_362 = x_364;
goto block_363;
}
block_363:
{
return x_362;
}
}
}
}
block_384:
{
if (lean_obj_tag(x_368) == 3)
{
lean_object* x_377; lean_object* x_378; lean_object* x_379; 
x_377 = lean_ctor_get(x_368, 0);
lean_inc(x_377);
x_378 = lean_ctor_get(x_368, 1);
lean_inc(x_378);
x_379 = lean_ctor_get(x_368, 2);
lean_inc_ref(x_379);
lean_dec_ref(x_368);
x_185 = x_377;
x_186 = x_378;
x_187 = x_379;
x_188 = x_369;
x_189 = x_370;
x_190 = x_371;
x_191 = x_372;
x_192 = x_373;
x_193 = x_374;
x_194 = x_375;
x_195 = x_376;
goto block_241;
}
else
{
lean_dec_ref(x_372);
lean_dec_ref(x_370);
if (lean_obj_tag(x_368) == 4)
{
lean_object* x_380; lean_object* x_381; 
x_380 = lean_ctor_get(x_368, 0);
lean_inc(x_380);
x_381 = lean_ctor_get(x_368, 1);
lean_inc_ref(x_381);
lean_dec_ref(x_368);
x_331 = x_380;
x_332 = x_381;
x_333 = x_369;
x_334 = x_371;
x_335 = x_373;
x_336 = x_374;
x_337 = x_375;
x_338 = x_376;
goto block_367;
}
else
{
lean_object* x_382; lean_object* x_383; 
lean_dec(x_376);
lean_dec_ref(x_375);
lean_dec(x_374);
lean_dec_ref(x_373);
lean_dec(x_371);
lean_dec(x_368);
x_382 = lean_box(0);
x_383 = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(x_383, 0, x_382);
return x_383;
}
}
}
}
}
LEAN_EXPORT lean_object* l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f___boxed(lean_object* x_1, lean_object* x_2, lean_object* x_3, lean_object* x_4, lean_object* x_5, lean_object* x_6, lean_object* x_7, lean_object* x_8, lean_object* x_9) {
_start:
{
lean_object* x_10; 
x_10 = l_Lean_Compiler_LCNF_Simp_inlineCandidate_x3f(x_1, x_2, x_3, x_4, x_5, x_6, x_7, x_8);
return x_10;
}
}
LEAN_EXPORT lean_object* l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2_() {
_start:
{
lean_object* x_2; uint8_t x_3; lean_object* x_4; lean_object* x_5; 
x_2 = ((lean_object*)(l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__2_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2_));
x_3 = 0;
x_4 = ((lean_object*)(l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn___closed__33_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2_));
x_5 = l_Lean_registerTraceClass(x_2, x_3, x_4);
return x_5;
}
}
LEAN_EXPORT lean_object* l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2____boxed(lean_object* x_1) {
_start:
{
lean_object* x_2; 
x_2 = l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2_();
return x_2;
}
}
lean_object* runtime_initialize_Lean_Compiler_LCNF_Simp_SimpM(uint8_t builtin);
static bool _G_runtime_initialized = false;
LEAN_EXPORT lean_object* runtime_initialize_Lean_Compiler_LCNF_Simp_InlineCandidate(uint8_t builtin) {
lean_object * res;
if (_G_runtime_initialized) return lean_io_result_mk_ok(lean_box(0));
_G_runtime_initialized = true;
res = runtime_initialize_Lean_Compiler_LCNF_Simp_SimpM(builtin)
;
if (lean_io_result_is_error(res)) return res;
lean_dec_ref(res);
res = l___private_Lean_Compiler_LCNF_Simp_InlineCandidate_0__Lean_Compiler_LCNF_Simp_initFn_00___x40_Lean_Compiler_LCNF_Simp_InlineCandidate_1449551352____hygCtx___hyg_2_()
;
if (lean_io_result_is_error(res)) return res;
lean_dec_ref(res);
return lean_io_result_mk_ok(lean_box(0));
}
static bool _G_meta_initialized = false;
LEAN_EXPORT lean_object* meta_initialize_Lean_Compiler_LCNF_Simp_InlineCandidate(uint8_t builtin) {
lean_object * res;
if (_G_meta_initialized) return lean_io_result_mk_ok(lean_box(0));
_G_meta_initialized = true;
return lean_io_result_mk_ok(lean_box(0));
}
lean_object* initialize_Lean_Compiler_LCNF_Simp_SimpM(uint8_t builtin);
static bool _G_initialized = false;
LEAN_EXPORT lean_object* initialize_Lean_Compiler_LCNF_Simp_InlineCandidate(uint8_t builtin) {
lean_object * res;
if (_G_initialized) return lean_io_result_mk_ok(lean_box(0));
_G_initialized = true;
res = initialize_Lean_Compiler_LCNF_Simp_SimpM(builtin)
;
if (lean_io_result_is_error(res)) return res;
lean_dec_ref(res);
res = runtime_initialize_Lean_Compiler_LCNF_Simp_InlineCandidate(builtin)
;
if (lean_io_result_is_error(res)) return res;
lean_dec_ref(res);
res = meta_initialize_Lean_Compiler_LCNF_Simp_InlineCandidate(builtin)
;
if (lean_io_result_is_error(res)) return res;
lean_dec_ref(res);
return initialize_Lean_Compiler_LCNF_Simp_InlineCandidate(builtin);
}
#ifdef __cplusplus
}
#endif
