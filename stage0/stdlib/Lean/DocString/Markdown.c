// Lean compiler output
// Module: Lean.DocString.Markdown
// Imports: public import Lean.DocString.Types public import Init.Data.String.TakeDrop public import Init.Data.String.Search import Init.Data.ToString.Macro import Init.While
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
lean_object* l_Id_instMonad___lam__6(lean_object*, lean_object*, lean_object*, lean_object*);
lean_object* l_Id_instMonad___lam__5___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
lean_object* l_Id_instMonad___lam__4___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
lean_object* l_Id_instMonad___lam__3(lean_object*, lean_object*, lean_object*, lean_object*);
lean_object* l_Id_instMonad___lam__2___boxed(lean_object*, lean_object*);
lean_object* l_Id_instMonad___lam__1___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
lean_object* l_Id_instMonad___lam__0(lean_object*, lean_object*, lean_object*, lean_object*);
lean_object* l_StateT_instMonad___redArg___lam__9(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
lean_object* l_StateT_instMonad___redArg___lam__7(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
lean_object* l_StateT_instMonad___redArg___lam__4(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
lean_object* l_StateT_pure(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
lean_object* l_StateT_instMonad___redArg___lam__1(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
lean_object* l_StateT_map(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
lean_object* lean_string_utf8_byte_size(lean_object*);
lean_object* lean_nat_add(lean_object*, lean_object*);
lean_object* lean_nat_sub(lean_object*, lean_object*);
uint8_t lean_nat_dec_eq(lean_object*, lean_object*);
lean_object* l_String_Slice_posLE(lean_object*, lean_object*);
uint32_t lean_string_utf8_get_fast(lean_object*, lean_object*);
uint8_t lean_uint32_dec_eq(uint32_t, uint32_t);
uint8_t lean_nat_dec_lt(lean_object*, lean_object*);
lean_object* lean_string_utf8_extract(lean_object*, lean_object*, lean_object*);
size_t lean_array_size(lean_object*);
uint8_t lean_usize_dec_lt(size_t, size_t);
lean_object* lean_array_uget(lean_object*, size_t);
lean_object* lean_array_uset(lean_object*, size_t, lean_object*);
size_t lean_usize_add(size_t, size_t);
lean_object* lean_string_append(lean_object*, lean_object*);
lean_object* lean_string_utf8_next_fast(lean_object*, lean_object*);
lean_object* lean_string_push(lean_object*, uint32_t);
uint8_t lean_nat_dec_le(lean_object*, lean_object*);
uint8_t lean_string_memcmp(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
uint8_t lean_usize_dec_eq(size_t, size_t);
lean_object* lean_array_uget_borrowed(lean_object*, size_t);
lean_object* lean_array_get_size(lean_object*);
lean_object* lean_array_fget_borrowed(lean_object*, lean_object*);
lean_object* lean_array_fset(lean_object*, lean_object*, lean_object*);
lean_object* l_Array_extract___redArg(lean_object*, lean_object*, lean_object*);
lean_object* l_Array_append___redArg(lean_object*, lean_object*);
uint8_t lean_uint32_dec_le(uint32_t, uint32_t);
lean_object* lean_mk_empty_array_with_capacity(lean_object*);
size_t lean_usize_of_nat(lean_object*);
lean_object* lean_array_fget(lean_object*, lean_object*);
lean_object* lean_array_pop(lean_object*);
lean_object* lean_array_push(lean_object*, lean_object*);
lean_object* l_Lean_Doc_Inline_empty(lean_object*);
lean_object* l_String_Slice_subslice_x21(lean_object*, lean_object*, lean_object*);
lean_object* l_StateT_bind(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
lean_object* lean_string_length(lean_object*);
lean_object* l_String_Slice_Pos_nextn(lean_object*, lean_object*, lean_object*);
lean_object* lean_array_mk(lean_object*);
lean_object* lean_array_to_list(lean_object*);
lean_object* l_List_appendTR___redArg(lean_object*, lean_object*);
lean_object* l___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, size_t, size_t, lean_object*);
lean_object* l_String_intercalate(lean_object*, lean_object*);
lean_object* lean_array_get(lean_object*, lean_object*, lean_object*);
lean_object* lean_mk_empty_array_with_capacity(lean_object*);
lean_object* l_Nat_reprFast(lean_object*);
lean_object* l___private_Init_Data_Nat_Basic_0__Nat_repeatTR_loop(lean_object*, lean_object*, lean_object*, lean_object*);
lean_object* l___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, size_t, size_t, lean_object*);
lean_object* l_Int_toNat(lean_object*);
lean_object* l_List_reverse___redArg(lean_object*);
static const lean_ctor_object l_Lean_Doc_MarkdownM_instInhabitedInlineCtx_default___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*0 + 8, .m_other = 0, .m_tag = 0}, .m_objs = {LEAN_SCALAR_PTR_LITERAL(0, 0, 0, 0, 0, 0, 0, 0)}};
static const lean_object* l_Lean_Doc_MarkdownM_instInhabitedInlineCtx_default___closed__0 = (const lean_object*)&l_Lean_Doc_MarkdownM_instInhabitedInlineCtx_default___closed__0_value;
LEAN_EXPORT const lean_object* l_Lean_Doc_MarkdownM_instInhabitedInlineCtx_default = (const lean_object*)&l_Lean_Doc_MarkdownM_instInhabitedInlineCtx_default___closed__0_value;
LEAN_EXPORT const lean_object* l_Lean_Doc_MarkdownM_instInhabitedInlineCtx = (const lean_object*)&l_Lean_Doc_MarkdownM_instInhabitedInlineCtx_default___closed__0_value;
static const lean_string_object l_List_mapTR_loop___at___00Lean_Doc_MarkdownM_run_x27_spec__0___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 3, .m_capacity = 3, .m_length = 2, .m_data = "[^"};
static const lean_object* l_List_mapTR_loop___at___00Lean_Doc_MarkdownM_run_x27_spec__0___closed__0 = (const lean_object*)&l_List_mapTR_loop___at___00Lean_Doc_MarkdownM_run_x27_spec__0___closed__0_value;
static const lean_string_object l_List_mapTR_loop___at___00Lean_Doc_MarkdownM_run_x27_spec__0___closed__1_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 3, .m_capacity = 3, .m_length = 2, .m_data = "]:"};
static const lean_object* l_List_mapTR_loop___at___00Lean_Doc_MarkdownM_run_x27_spec__0___closed__1 = (const lean_object*)&l_List_mapTR_loop___at___00Lean_Doc_MarkdownM_run_x27_spec__0___closed__1_value;
LEAN_EXPORT lean_object* l_List_mapTR_loop___at___00Lean_Doc_MarkdownM_run_x27_spec__0(lean_object*, lean_object*);
static const lean_array_object l_Lean_Doc_MarkdownM_run_x27___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_array_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 246}, .m_size = 0, .m_capacity = 0, .m_data = {}};
static const lean_object* l_Lean_Doc_MarkdownM_run_x27___closed__0 = (const lean_object*)&l_Lean_Doc_MarkdownM_run_x27___closed__0_value;
static const lean_string_object l_Lean_Doc_MarkdownM_run_x27___closed__1_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 2, .m_capacity = 2, .m_length = 1, .m_data = "\n"};
static const lean_object* l_Lean_Doc_MarkdownM_run_x27___closed__1 = (const lean_object*)&l_Lean_Doc_MarkdownM_run_x27___closed__1_value;
static const lean_string_object l_Lean_Doc_MarkdownM_run_x27___closed__2_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 3, .m_capacity = 3, .m_length = 2, .m_data = "\n\n"};
static const lean_object* l_Lean_Doc_MarkdownM_run_x27___closed__2 = (const lean_object*)&l_Lean_Doc_MarkdownM_run_x27___closed__2_value;
LEAN_EXPORT lean_object* l_Lean_Doc_MarkdownM_run_x27(lean_object*);
LEAN_EXPORT lean_object* l_String_Slice_Pos_revSkipWhile___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_trimEndSpaces_spec__0(lean_object*, lean_object*);
LEAN_EXPORT lean_object* l_String_Slice_Pos_revSkipWhile___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_trimEndSpaces_spec__0___boxed(lean_object*, lean_object*);
LEAN_EXPORT lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_trimEndSpaces(lean_object*);
LEAN_EXPORT lean_object* l___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Lean_Doc_prefixLines_spec__0(lean_object*, lean_object*, size_t, size_t, lean_object*);
LEAN_EXPORT lean_object* l___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Lean_Doc_prefixLines_spec__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* l_Lean_Doc_prefixLines(lean_object*, lean_object*);
LEAN_EXPORT lean_object* l_Array_mapFinIdxM_map___at___00Lean_Doc_prefixListLines_spec__0___redArg(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* l_Array_mapFinIdxM_map___at___00Lean_Doc_prefixListLines_spec__0___redArg___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* l_Lean_Doc_prefixListLines(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* l_Lean_Doc_prefixListLines___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* l_Array_mapFinIdxM_map___at___00Lean_Doc_prefixListLines_spec__0(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* l_Array_mapFinIdxM_map___at___00Lean_Doc_prefixListLines_spec__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
static const lean_string_object l___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Lean_Doc_joinBlocks_spec__0___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 1, .m_capacity = 1, .m_length = 0, .m_data = ""};
static const lean_object* l___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Lean_Doc_joinBlocks_spec__0___closed__0 = (const lean_object*)&l___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Lean_Doc_joinBlocks_spec__0___closed__0_value;
LEAN_EXPORT lean_object* l___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Lean_Doc_joinBlocks_spec__0(lean_object*, size_t, size_t, lean_object*);
LEAN_EXPORT lean_object* l___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Lean_Doc_joinBlocks_spec__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
static const lean_array_object l_Lean_Doc_joinBlocks___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_array_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 246}, .m_size = 0, .m_capacity = 0, .m_data = {}};
static const lean_object* l_Lean_Doc_joinBlocks___closed__0 = (const lean_object*)&l_Lean_Doc_joinBlocks___closed__0_value;
LEAN_EXPORT lean_object* l_Lean_Doc_joinBlocks(lean_object*);
LEAN_EXPORT lean_object* l_Lean_Doc_joinBlocks___boxed(lean_object*);
static const lean_string_object l___private_Lean_DocString_Markdown_0__Lean_Doc_glueInlineBoundary___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 2, .m_capacity = 2, .m_length = 1, .m_data = "`"};
static const lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_glueInlineBoundary___closed__0 = (const lean_object*)&l___private_Lean_DocString_Markdown_0__Lean_Doc_glueInlineBoundary___closed__0_value;
static lean_once_cell_t l___private_Lean_DocString_Markdown_0__Lean_Doc_glueInlineBoundary___closed__1_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_glueInlineBoundary___closed__1;
static const lean_string_object l___private_Lean_DocString_Markdown_0__Lean_Doc_glueInlineBoundary___closed__2_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 4, .m_capacity = 4, .m_length = 1, .m_data = "​"};
static const lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_glueInlineBoundary___closed__2 = (const lean_object*)&l___private_Lean_DocString_Markdown_0__Lean_Doc_glueInlineBoundary___closed__2_value;
LEAN_EXPORT lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_glueInlineBoundary(lean_object*, lean_object*);
LEAN_EXPORT lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_glueInlineBoundary___boxed(lean_object*, lean_object*);
LEAN_EXPORT lean_object* l___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Lean_Doc_joinInlines_spec__0(lean_object*, size_t, size_t, lean_object*);
LEAN_EXPORT lean_object* l___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Lean_Doc_joinInlines_spec__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* l_Lean_Doc_joinInlines(lean_object*);
LEAN_EXPORT lean_object* l_Lean_Doc_joinInlines___boxed(lean_object*);
LEAN_EXPORT lean_object* l_Lean_Doc_instMarkdownInlineEmpty___lam__0(lean_object*, uint8_t, lean_object*, lean_object*);
LEAN_EXPORT lean_object* l_Lean_Doc_instMarkdownInlineEmpty___lam__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
static const lean_closure_object l_Lean_Doc_instMarkdownInlineEmpty___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)l_Lean_Doc_instMarkdownInlineEmpty___lam__0___boxed, .m_arity = 4, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* l_Lean_Doc_instMarkdownInlineEmpty___closed__0 = (const lean_object*)&l_Lean_Doc_instMarkdownInlineEmpty___closed__0_value;
LEAN_EXPORT const lean_object* l_Lean_Doc_instMarkdownInlineEmpty = (const lean_object*)&l_Lean_Doc_instMarkdownInlineEmpty___closed__0_value;
LEAN_EXPORT lean_object* l_Lean_Doc_instMarkdownBlockEmpty___lam__0(lean_object*, lean_object*, uint8_t, lean_object*, lean_object*);
LEAN_EXPORT lean_object* l_Lean_Doc_instMarkdownBlockEmpty___lam__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
static const lean_closure_object l_Lean_Doc_instMarkdownBlockEmpty___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)l_Lean_Doc_instMarkdownBlockEmpty___lam__0___boxed, .m_arity = 5, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* l_Lean_Doc_instMarkdownBlockEmpty___closed__0 = (const lean_object*)&l_Lean_Doc_instMarkdownBlockEmpty___closed__0_value;
LEAN_EXPORT lean_object* l_Lean_Doc_instMarkdownBlockEmpty(lean_object*);
LEAN_EXPORT uint8_t l_Option_instBEq_beq___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_midLineSpecial_spec__1(lean_object*, lean_object*);
LEAN_EXPORT lean_object* l_Option_instBEq_beq___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_midLineSpecial_spec__1___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint8_t l_WellFounded_opaqueFix_u2083___at___00String_Slice_contains___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_midLineSpecial_spec__0_spec__0___redArg(lean_object*, uint32_t, lean_object*, uint8_t);
LEAN_EXPORT lean_object* l_WellFounded_opaqueFix_u2083___at___00String_Slice_contains___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_midLineSpecial_spec__0_spec__0___redArg___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint8_t l_String_Slice_contains___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_midLineSpecial_spec__0(uint32_t, lean_object*);
LEAN_EXPORT lean_object* l_String_Slice_contains___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_midLineSpecial_spec__0___boxed(lean_object*, lean_object*);
static const lean_string_object l___private_Lean_DocString_Markdown_0__Lean_Doc_midLineSpecial___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 12, .m_capacity = 12, .m_length = 11, .m_data = "*_`<[]{}()#"};
static const lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_midLineSpecial___closed__0 = (const lean_object*)&l___private_Lean_DocString_Markdown_0__Lean_Doc_midLineSpecial___closed__0_value;
static lean_once_cell_t l___private_Lean_DocString_Markdown_0__Lean_Doc_midLineSpecial___closed__1_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_midLineSpecial___closed__1;
static lean_once_cell_t l___private_Lean_DocString_Markdown_0__Lean_Doc_midLineSpecial___closed__2_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_midLineSpecial___closed__2;
LEAN_EXPORT lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_midLineSpecial___closed__3___boxed__const__1;
static lean_once_cell_t l___private_Lean_DocString_Markdown_0__Lean_Doc_midLineSpecial___closed__3_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_midLineSpecial___closed__3;
LEAN_EXPORT uint8_t l___private_Lean_DocString_Markdown_0__Lean_Doc_midLineSpecial(uint32_t, lean_object*);
LEAN_EXPORT lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_midLineSpecial___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint8_t l_WellFounded_opaqueFix_u2083___at___00String_Slice_contains___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_midLineSpecial_spec__0_spec__0(lean_object*, uint32_t, lean_object*, lean_object*, lean_object*, uint8_t, lean_object*);
LEAN_EXPORT lean_object* l_WellFounded_opaqueFix_u2083___at___00String_Slice_contains___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_midLineSpecial_spec__0_spec__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_markerPrefixSpecial___closed__0___boxed__const__1;
static lean_once_cell_t l___private_Lean_DocString_Markdown_0__Lean_Doc_markerPrefixSpecial___closed__0_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_markerPrefixSpecial___closed__0;
LEAN_EXPORT uint8_t l___private_Lean_DocString_Markdown_0__Lean_Doc_markerPrefixSpecial(lean_object*, uint32_t, lean_object*);
LEAN_EXPORT lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_markerPrefixSpecial___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* l___private_Init_While_0__Lean_Loop_forIn_loop___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_escape_spec__1(lean_object*, lean_object*);
LEAN_EXPORT lean_object* l___private_Init_While_0__Lean_Loop_forIn_loop___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_escape_spec__1___boxed(lean_object*, lean_object*);
static const lean_string_object l___private_Init_While_0__Lean_Loop_forIn_loop___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_escape_spec__0___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 8, .m_capacity = 8, .m_length = 7, .m_data = "> -+. \t"};
static const lean_object* l___private_Init_While_0__Lean_Loop_forIn_loop___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_escape_spec__0___closed__0 = (const lean_object*)&l___private_Init_While_0__Lean_Loop_forIn_loop___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_escape_spec__0___closed__0_value;
static lean_once_cell_t l___private_Init_While_0__Lean_Loop_forIn_loop___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_escape_spec__0___closed__1_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* l___private_Init_While_0__Lean_Loop_forIn_loop___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_escape_spec__0___closed__1;
static lean_once_cell_t l___private_Init_While_0__Lean_Loop_forIn_loop___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_escape_spec__0___closed__2_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* l___private_Init_While_0__Lean_Loop_forIn_loop___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_escape_spec__0___closed__2;
LEAN_EXPORT lean_object* l___private_Init_While_0__Lean_Loop_forIn_loop___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_escape_spec__0(lean_object*, lean_object*);
LEAN_EXPORT lean_object* l___private_Init_While_0__Lean_Loop_forIn_loop___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_escape_spec__0___boxed(lean_object*, lean_object*);
static const lean_ctor_object l___private_Lean_DocString_Markdown_0__Lean_Doc_escape___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 0, .m_other = 2, .m_tag = 0}, .m_objs = {((lean_object*)(((size_t)(0) << 1) | 1)),((lean_object*)(((size_t)(0) << 1) | 1))}};
static const lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_escape___closed__0 = (const lean_object*)&l___private_Lean_DocString_Markdown_0__Lean_Doc_escape___closed__0_value;
static const lean_ctor_object l___private_Lean_DocString_Markdown_0__Lean_Doc_escape___closed__1_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 0, .m_other = 2, .m_tag = 0}, .m_objs = {((lean_object*)&l___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Lean_Doc_joinBlocks_spec__0___closed__0_value),((lean_object*)&l___private_Lean_DocString_Markdown_0__Lean_Doc_escape___closed__0_value)}};
static const lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_escape___closed__1 = (const lean_object*)&l___private_Lean_DocString_Markdown_0__Lean_Doc_escape___closed__1_value;
LEAN_EXPORT lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_escape(lean_object*);
LEAN_EXPORT lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_escape___boxed(lean_object*);
LEAN_EXPORT lean_object* l___private_Init_While_0__Lean_Loop_forIn_loop___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_longestBacktickRun_spec__0(lean_object*, lean_object*);
LEAN_EXPORT lean_object* l___private_Init_While_0__Lean_Loop_forIn_loop___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_longestBacktickRun_spec__0___boxed(lean_object*, lean_object*);
static const lean_ctor_object l___private_Lean_DocString_Markdown_0__Lean_Doc_longestBacktickRun___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 0, .m_other = 2, .m_tag = 0}, .m_objs = {((lean_object*)(((size_t)(0) << 1) | 1)),((lean_object*)(((size_t)(0) << 1) | 1))}};
static const lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_longestBacktickRun___closed__0 = (const lean_object*)&l___private_Lean_DocString_Markdown_0__Lean_Doc_longestBacktickRun___closed__0_value;
static const lean_ctor_object l___private_Lean_DocString_Markdown_0__Lean_Doc_longestBacktickRun___closed__1_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 0, .m_other = 2, .m_tag = 0}, .m_objs = {((lean_object*)(((size_t)(0) << 1) | 1)),((lean_object*)&l___private_Lean_DocString_Markdown_0__Lean_Doc_longestBacktickRun___closed__0_value)}};
static const lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_longestBacktickRun___closed__1 = (const lean_object*)&l___private_Lean_DocString_Markdown_0__Lean_Doc_longestBacktickRun___closed__1_value;
LEAN_EXPORT lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_longestBacktickRun(lean_object*);
LEAN_EXPORT lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_longestBacktickRun___boxed(lean_object*);
LEAN_EXPORT lean_object* l___private_Init_Data_Nat_Basic_0__Nat_repeatTR_loop___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_fenceFor_spec__0(lean_object*, lean_object*);
LEAN_EXPORT lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_fenceFor(lean_object*, lean_object*);
LEAN_EXPORT lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_fenceFor___boxed(lean_object*, lean_object*);
static const lean_string_object l___private_Lean_DocString_Markdown_0__Lean_Doc_quoteCode___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 2, .m_capacity = 2, .m_length = 1, .m_data = " "};
static const lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_quoteCode___closed__0 = (const lean_object*)&l___private_Lean_DocString_Markdown_0__Lean_Doc_quoteCode___closed__0_value;
LEAN_EXPORT lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_quoteCode(lean_object*);
static const lean_ctor_object l_String_Slice_splitToSubslice___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_splitNewlines_spec__0___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 0, .m_other = 2, .m_tag = 0}, .m_objs = {((lean_object*)(((size_t)(0) << 1) | 1)),((lean_object*)(((size_t)(0) << 1) | 1))}};
static const lean_object* l_String_Slice_splitToSubslice___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_splitNewlines_spec__0___closed__0 = (const lean_object*)&l_String_Slice_splitToSubslice___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_splitNewlines_spec__0___closed__0_value;
LEAN_EXPORT lean_object* l_String_Slice_splitToSubslice___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_splitNewlines_spec__0(lean_object*);
LEAN_EXPORT lean_object* l_String_Slice_splitToSubslice___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_splitNewlines_spec__0___boxed(lean_object*);
LEAN_EXPORT lean_object* l___private_Init_WFExtrinsicFix_0__WellFounded_opaqueFix_u2082___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_splitNewlines_spec__1___redArg(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* l___private_Init_WFExtrinsicFix_0__WellFounded_opaqueFix_u2082___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_splitNewlines_spec__1___redArg___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_splitNewlines(lean_object*);
LEAN_EXPORT lean_object* l___private_Init_WFExtrinsicFix_0__WellFounded_opaqueFix_u2082___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_splitNewlines_spec__1(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* l___private_Init_WFExtrinsicFix_0__WellFounded_opaqueFix_u2082___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_splitNewlines_spec__1___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_codeBlockLines(lean_object*);
LEAN_EXPORT lean_object* l_String_Slice_Pos_skipWhile___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_trimLeft_go_spec__0(lean_object*, lean_object*);
LEAN_EXPORT lean_object* l_String_Slice_Pos_skipWhile___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_trimLeft_go_spec__0___boxed(lean_object*, lean_object*);
static lean_once_cell_t l___private_Lean_DocString_Markdown_0__Lean_Doc_trimLeft_go___redArg___closed__0_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_trimLeft_go___redArg___closed__0;
static lean_once_cell_t l___private_Lean_DocString_Markdown_0__Lean_Doc_trimLeft_go___redArg___closed__1_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_trimLeft_go___redArg___closed__1;
LEAN_EXPORT lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_trimLeft_go___redArg(lean_object*);
LEAN_EXPORT lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_trimLeft_go(lean_object*, lean_object*);
LEAN_EXPORT lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_trimLeft___redArg(lean_object*);
LEAN_EXPORT lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_trimLeft(lean_object*, lean_object*);
LEAN_EXPORT lean_object* l_String_Slice_Pos_revSkipWhile___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_trimRight_go_spec__0(lean_object*, lean_object*);
LEAN_EXPORT lean_object* l_String_Slice_Pos_revSkipWhile___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_trimRight_go_spec__0___boxed(lean_object*, lean_object*);
static lean_once_cell_t l___private_Lean_DocString_Markdown_0__Lean_Doc_trimRight_go___redArg___closed__0_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_trimRight_go___redArg___closed__0;
LEAN_EXPORT lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_trimRight_go___redArg(lean_object*);
LEAN_EXPORT lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_trimRight_go(lean_object*, lean_object*);
LEAN_EXPORT lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_trimRight___redArg(lean_object*);
LEAN_EXPORT lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_trimRight(lean_object*, lean_object*);
LEAN_EXPORT lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_trim___redArg(lean_object*);
LEAN_EXPORT lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_trim(lean_object*, lean_object*);
static const lean_closure_object l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)l_Id_instMonad___lam__0, .m_arity = 4, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__0 = (const lean_object*)&l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__0_value;
static const lean_closure_object l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__1_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)l_Id_instMonad___lam__1___boxed, .m_arity = 4, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__1 = (const lean_object*)&l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__1_value;
static const lean_closure_object l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__2_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)l_Id_instMonad___lam__2___boxed, .m_arity = 2, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__2 = (const lean_object*)&l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__2_value;
static const lean_closure_object l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__3_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)l_Id_instMonad___lam__3, .m_arity = 4, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__3 = (const lean_object*)&l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__3_value;
static const lean_closure_object l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__4_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)l_Id_instMonad___lam__4___boxed, .m_arity = 4, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__4 = (const lean_object*)&l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__4_value;
static const lean_closure_object l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__5_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)l_Id_instMonad___lam__5___boxed, .m_arity = 4, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__5 = (const lean_object*)&l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__5_value;
static const lean_closure_object l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__6_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)l_Id_instMonad___lam__6, .m_arity = 4, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__6 = (const lean_object*)&l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__6_value;
static const lean_ctor_object l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__7_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 0, .m_other = 2, .m_tag = 0}, .m_objs = {((lean_object*)&l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__0_value),((lean_object*)&l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__1_value)}};
static const lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__7 = (const lean_object*)&l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__7_value;
static const lean_ctor_object l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__8_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*5 + 0, .m_other = 5, .m_tag = 0}, .m_objs = {((lean_object*)&l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__7_value),((lean_object*)&l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__2_value),((lean_object*)&l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__3_value),((lean_object*)&l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__4_value),((lean_object*)&l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__5_value)}};
static const lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__8 = (const lean_object*)&l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__8_value;
static const lean_ctor_object l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__9_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 0, .m_other = 2, .m_tag = 0}, .m_objs = {((lean_object*)&l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__8_value),((lean_object*)&l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__6_value)}};
static const lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__9 = (const lean_object*)&l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__9_value;
static const lean_closure_object l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__10_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*1, .m_other = 0, .m_tag = 245}, .m_fun = (void*)l_StateT_instMonad___redArg___lam__1, .m_arity = 6, .m_num_fixed = 1, .m_objs = {((lean_object*)&l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__9_value)} };
static const lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__10 = (const lean_object*)&l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__10_value;
static const lean_closure_object l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__11_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*1, .m_other = 0, .m_tag = 245}, .m_fun = (void*)l_StateT_instMonad___redArg___lam__4, .m_arity = 6, .m_num_fixed = 1, .m_objs = {((lean_object*)&l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__9_value)} };
static const lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__11 = (const lean_object*)&l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__11_value;
static const lean_closure_object l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__12_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*1, .m_other = 0, .m_tag = 245}, .m_fun = (void*)l_StateT_instMonad___redArg___lam__7, .m_arity = 6, .m_num_fixed = 1, .m_objs = {((lean_object*)&l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__9_value)} };
static const lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__12 = (const lean_object*)&l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__12_value;
static const lean_closure_object l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__13_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*1, .m_other = 0, .m_tag = 245}, .m_fun = (void*)l_StateT_instMonad___redArg___lam__9, .m_arity = 6, .m_num_fixed = 1, .m_objs = {((lean_object*)&l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__9_value)} };
static const lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__13 = (const lean_object*)&l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__13_value;
static const lean_closure_object l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__14_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*3, .m_other = 0, .m_tag = 245}, .m_fun = (void*)l_StateT_map, .m_arity = 8, .m_num_fixed = 3, .m_objs = {((lean_object*)(((size_t)(0) << 1) | 1)),((lean_object*)(((size_t)(0) << 1) | 1)),((lean_object*)&l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__9_value)} };
static const lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__14 = (const lean_object*)&l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__14_value;
static const lean_ctor_object l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__15_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 0, .m_other = 2, .m_tag = 0}, .m_objs = {((lean_object*)&l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__14_value),((lean_object*)&l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__10_value)}};
static const lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__15 = (const lean_object*)&l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__15_value;
static const lean_closure_object l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__16_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*3, .m_other = 0, .m_tag = 245}, .m_fun = (void*)l_StateT_pure, .m_arity = 6, .m_num_fixed = 3, .m_objs = {((lean_object*)(((size_t)(0) << 1) | 1)),((lean_object*)(((size_t)(0) << 1) | 1)),((lean_object*)&l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__9_value)} };
static const lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__16 = (const lean_object*)&l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__16_value;
static const lean_ctor_object l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__17_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*5 + 0, .m_other = 5, .m_tag = 0}, .m_objs = {((lean_object*)&l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__15_value),((lean_object*)&l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__16_value),((lean_object*)&l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__11_value),((lean_object*)&l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__12_value),((lean_object*)&l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__13_value)}};
static const lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__17 = (const lean_object*)&l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__17_value;
static const lean_closure_object l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__18_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*3, .m_other = 0, .m_tag = 245}, .m_fun = (void*)l_StateT_bind, .m_arity = 8, .m_num_fixed = 3, .m_objs = {((lean_object*)(((size_t)(0) << 1) | 1)),((lean_object*)(((size_t)(0) << 1) | 1)),((lean_object*)&l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__9_value)} };
static const lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__18 = (const lean_object*)&l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__18_value;
static const lean_ctor_object l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__19_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 0, .m_other = 2, .m_tag = 0}, .m_objs = {((lean_object*)&l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__17_value),((lean_object*)&l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__18_value)}};
static const lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__19 = (const lean_object*)&l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__19_value;
static const lean_string_object l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__20_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 2, .m_capacity = 2, .m_length = 1, .m_data = "*"};
static const lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__20 = (const lean_object*)&l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__20_value;
static const lean_array_object l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__21_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_array_object) + sizeof(void*)*1, .m_other = 0, .m_tag = 246}, .m_size = 1, .m_capacity = 1, .m_data = {((lean_object*)&l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__20_value)}};
static const lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__21 = (const lean_object*)&l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__21_value;
static const lean_array_object l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__22_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_array_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 246}, .m_size = 0, .m_capacity = 0, .m_data = {}};
static const lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__22 = (const lean_object*)&l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__22_value;
static const lean_string_object l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__23_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 3, .m_capacity = 3, .m_length = 2, .m_data = "**"};
static const lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__23 = (const lean_object*)&l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__23_value;
static const lean_array_object l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__24_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_array_object) + sizeof(void*)*1, .m_other = 0, .m_tag = 246}, .m_size = 1, .m_capacity = 1, .m_data = {((lean_object*)&l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__23_value)}};
static const lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__24 = (const lean_object*)&l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__24_value;
static const lean_string_object l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__25_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 2, .m_capacity = 2, .m_length = 1, .m_data = "$"};
static const lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__25 = (const lean_object*)&l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__25_value;
static const lean_string_object l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__26_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 3, .m_capacity = 3, .m_length = 2, .m_data = "$$"};
static const lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__26 = (const lean_object*)&l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__26_value;
static const lean_array_object l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__27_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_array_object) + sizeof(void*)*2, .m_other = 0, .m_tag = 246}, .m_size = 2, .m_capacity = 2, .m_data = {((lean_object*)&l___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Lean_Doc_joinBlocks_spec__0___closed__0_value),((lean_object*)&l___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Lean_Doc_joinBlocks_spec__0___closed__0_value)}};
static const lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__27 = (const lean_object*)&l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__27_value;
static const lean_string_object l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__28_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 2, .m_capacity = 2, .m_length = 1, .m_data = "["};
static const lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__28 = (const lean_object*)&l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__28_value;
static const lean_array_object l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__29_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_array_object) + sizeof(void*)*1, .m_other = 0, .m_tag = 246}, .m_size = 1, .m_capacity = 1, .m_data = {((lean_object*)&l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__28_value)}};
static const lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__29 = (const lean_object*)&l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__29_value;
static const lean_string_object l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__30_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 3, .m_capacity = 3, .m_length = 2, .m_data = "]("};
static const lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__30 = (const lean_object*)&l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__30_value;
static const lean_string_object l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__31_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 2, .m_capacity = 2, .m_length = 1, .m_data = ")"};
static const lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__31 = (const lean_object*)&l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__31_value;
static lean_once_cell_t l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__32_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__32;
static const lean_string_object l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__33_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 2, .m_capacity = 2, .m_length = 1, .m_data = "]"};
static const lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__33 = (const lean_object*)&l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__33_value;
static const lean_string_object l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__34_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 3, .m_capacity = 3, .m_length = 2, .m_data = "!["};
static const lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__34 = (const lean_object*)&l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__34_value;
LEAN_EXPORT lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* l_Lean_Doc_instToMarkdownInlineOfMarkdownInline___private__1___redArg(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* l_Lean_Doc_instToMarkdownInlineOfMarkdownInline___private__1(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* l_Lean_Doc_instToMarkdownInlineOfMarkdownInline___redArg(lean_object*);
LEAN_EXPORT lean_object* l_Lean_Doc_instToMarkdownInlineOfMarkdownInline(lean_object*, lean_object*);
LEAN_EXPORT lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_blockMarkdown___redArg___lam__1(uint32_t, lean_object*);
LEAN_EXPORT lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_blockMarkdown___redArg___lam__1___boxed(lean_object*, lean_object*);
static const lean_string_object l___private_Lean_DocString_Markdown_0__Lean_Doc_blockMarkdown___redArg___lam__0___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 3, .m_capacity = 3, .m_length = 2, .m_data = "* "};
static const lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_blockMarkdown___redArg___lam__0___closed__0 = (const lean_object*)&l___private_Lean_DocString_Markdown_0__Lean_Doc_blockMarkdown___redArg___lam__0___closed__0_value;
static const lean_string_object l___private_Lean_DocString_Markdown_0__Lean_Doc_blockMarkdown___redArg___lam__0___closed__1_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 3, .m_capacity = 3, .m_length = 2, .m_data = "  "};
static const lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_blockMarkdown___redArg___lam__0___closed__1 = (const lean_object*)&l___private_Lean_DocString_Markdown_0__Lean_Doc_blockMarkdown___redArg___lam__0___closed__1_value;
static const lean_string_object l___private_Lean_DocString_Markdown_0__Lean_Doc_blockMarkdown___redArg___lam__2___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 3, .m_capacity = 3, .m_length = 2, .m_data = ". "};
static const lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_blockMarkdown___redArg___lam__2___closed__0 = (const lean_object*)&l___private_Lean_DocString_Markdown_0__Lean_Doc_blockMarkdown___redArg___lam__2___closed__0_value;
static lean_once_cell_t l___private_Lean_DocString_Markdown_0__Lean_Doc_blockMarkdown___redArg___lam__2___closed__1_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_blockMarkdown___redArg___lam__2___closed__1;
LEAN_EXPORT lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_blockMarkdown___redArg___lam__2(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_blockMarkdown___redArg___lam__2___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
static const lean_string_object l___private_Lean_DocString_Markdown_0__Lean_Doc_blockMarkdown___redArg___lam__3___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 2, .m_capacity = 2, .m_length = 1, .m_data = ":"};
static const lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_blockMarkdown___redArg___lam__3___closed__0 = (const lean_object*)&l___private_Lean_DocString_Markdown_0__Lean_Doc_blockMarkdown___redArg___lam__3___closed__0_value;
static const lean_array_object l___private_Lean_DocString_Markdown_0__Lean_Doc_blockMarkdown___redArg___lam__3___closed__1_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_array_object) + sizeof(void*)*1, .m_other = 0, .m_tag = 246}, .m_size = 1, .m_capacity = 1, .m_data = {((lean_object*)&l___private_Lean_DocString_Markdown_0__Lean_Doc_blockMarkdown___redArg___lam__3___closed__0_value)}};
static const lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_blockMarkdown___redArg___lam__3___closed__1 = (const lean_object*)&l___private_Lean_DocString_Markdown_0__Lean_Doc_blockMarkdown___redArg___lam__3___closed__1_value;
LEAN_EXPORT lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_blockMarkdown___redArg___lam__3(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
static const lean_string_object l___private_Lean_DocString_Markdown_0__Lean_Doc_blockMarkdown___redArg___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = 0, .m_other = 0, .m_tag = 249}, .m_size = 3, .m_capacity = 3, .m_length = 2, .m_data = "> "};
static const lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_blockMarkdown___redArg___closed__0 = (const lean_object*)&l___private_Lean_DocString_Markdown_0__Lean_Doc_blockMarkdown___redArg___closed__0_value;
LEAN_EXPORT lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_blockMarkdown___redArg(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_blockMarkdown___redArg___lam__0(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_blockMarkdown(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* l_Lean_Doc_instToMarkdownBlockOfMarkdownInlineOfMarkdownBlock___private__1___redArg(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* l_Lean_Doc_instToMarkdownBlockOfMarkdownInlineOfMarkdownBlock___private__1(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* l_Lean_Doc_instToMarkdownBlockOfMarkdownInlineOfMarkdownBlock___redArg(lean_object*, lean_object*);
LEAN_EXPORT lean_object* l_Lean_Doc_instToMarkdownBlockOfMarkdownInlineOfMarkdownBlock(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* l_Lean_Doc_partMarkdown___redArg___closed__0___boxed__const__1;
static lean_once_cell_t l_Lean_Doc_partMarkdown___redArg___closed__0_once = LEAN_ONCE_CELL_INITIALIZER;
static lean_object* l_Lean_Doc_partMarkdown___redArg___closed__0;
LEAN_EXPORT lean_object* l_Lean_Doc_partMarkdown___redArg___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* l_Lean_Doc_partMarkdown___redArg(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* l_Lean_Doc_partMarkdown(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* l_Lean_Doc_partMarkdown___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* l_Lean_Doc_instToMarkdownPartOfMarkdownInlineOfMarkdownBlock___redArg___lam__0(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* l_Lean_Doc_instToMarkdownPartOfMarkdownInlineOfMarkdownBlock___redArg(lean_object*, lean_object*);
LEAN_EXPORT lean_object* l_Lean_Doc_instToMarkdownPartOfMarkdownInlineOfMarkdownBlock(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* l_List_mapTR_loop___at___00Lean_Doc_MarkdownM_run_x27_spec__0(lean_object* v_a_7_, lean_object* v_a_8_){
_start:
{
if (lean_obj_tag(v_a_7_) == 0)
{
lean_object* v___x_9_; 
v___x_9_ = l_List_reverse___redArg(v_a_8_);
return v___x_9_;
}
else
{
lean_object* v_head_10_; lean_object* v_tail_11_; lean_object* v___x_13_; uint8_t v_isShared_14_; uint8_t v_isSharedCheck_26_; 
v_head_10_ = lean_ctor_get(v_a_7_, 0);
v_tail_11_ = lean_ctor_get(v_a_7_, 1);
v_isSharedCheck_26_ = !lean_is_exclusive(v_a_7_);
if (v_isSharedCheck_26_ == 0)
{
v___x_13_ = v_a_7_;
v_isShared_14_ = v_isSharedCheck_26_;
goto v_resetjp_12_;
}
else
{
lean_inc(v_tail_11_);
lean_inc(v_head_10_);
lean_dec(v_a_7_);
v___x_13_ = lean_box(0);
v_isShared_14_ = v_isSharedCheck_26_;
goto v_resetjp_12_;
}
v_resetjp_12_:
{
lean_object* v_fst_15_; lean_object* v_snd_16_; lean_object* v___x_17_; lean_object* v___x_18_; lean_object* v___x_19_; lean_object* v___x_20_; lean_object* v___x_21_; lean_object* v___x_23_; 
v_fst_15_ = lean_ctor_get(v_head_10_, 0);
lean_inc(v_fst_15_);
v_snd_16_ = lean_ctor_get(v_head_10_, 1);
lean_inc(v_snd_16_);
lean_dec(v_head_10_);
v___x_17_ = ((lean_object*)(l_List_mapTR_loop___at___00Lean_Doc_MarkdownM_run_x27_spec__0___closed__0));
v___x_18_ = lean_string_append(v___x_17_, v_fst_15_);
lean_dec(v_fst_15_);
v___x_19_ = ((lean_object*)(l_List_mapTR_loop___at___00Lean_Doc_MarkdownM_run_x27_spec__0___closed__1));
v___x_20_ = lean_string_append(v___x_18_, v___x_19_);
v___x_21_ = lean_string_append(v___x_20_, v_snd_16_);
lean_dec(v_snd_16_);
if (v_isShared_14_ == 0)
{
lean_ctor_set(v___x_13_, 1, v_a_8_);
lean_ctor_set(v___x_13_, 0, v___x_21_);
v___x_23_ = v___x_13_;
goto v_reusejp_22_;
}
else
{
lean_object* v_reuseFailAlloc_25_; 
v_reuseFailAlloc_25_ = lean_alloc_ctor(1, 2, 0);
lean_ctor_set(v_reuseFailAlloc_25_, 0, v___x_21_);
lean_ctor_set(v_reuseFailAlloc_25_, 1, v_a_8_);
v___x_23_ = v_reuseFailAlloc_25_;
goto v_reusejp_22_;
}
v_reusejp_22_:
{
v_a_7_ = v_tail_11_;
v_a_8_ = v___x_23_;
goto _start;
}
}
}
}
}
LEAN_EXPORT lean_object* l_Lean_Doc_MarkdownM_run_x27(lean_object* v_act_31_){
_start:
{
lean_object* v___x_32_; lean_object* v___x_33_; lean_object* v___x_34_; lean_object* v_fst_35_; lean_object* v_snd_36_; lean_object* v___x_37_; lean_object* v___x_38_; lean_object* v_main_39_; lean_object* v___x_40_; uint8_t v___x_41_; 
v___x_32_ = lean_unsigned_to_nat(0u);
v___x_33_ = ((lean_object*)(l_Lean_Doc_MarkdownM_run_x27___closed__0));
v___x_34_ = lean_apply_1(v_act_31_, v___x_33_);
v_fst_35_ = lean_ctor_get(v___x_34_, 0);
lean_inc(v_fst_35_);
v_snd_36_ = lean_ctor_get(v___x_34_, 1);
lean_inc(v_snd_36_);
lean_dec_ref(v___x_34_);
v___x_37_ = ((lean_object*)(l_Lean_Doc_MarkdownM_run_x27___closed__1));
v___x_38_ = lean_array_to_list(v_fst_35_);
v_main_39_ = l_String_intercalate(v___x_37_, v___x_38_);
v___x_40_ = lean_array_get_size(v_snd_36_);
v___x_41_ = lean_nat_dec_eq(v___x_40_, v___x_32_);
if (v___x_41_ == 0)
{
lean_object* v___x_42_; lean_object* v___x_43_; lean_object* v_foots_44_; lean_object* v___x_45_; lean_object* v___x_46_; lean_object* v___x_47_; lean_object* v___x_48_; 
v___x_42_ = lean_array_to_list(v_snd_36_);
v___x_43_ = lean_box(0);
v_foots_44_ = l_List_mapTR_loop___at___00Lean_Doc_MarkdownM_run_x27_spec__0(v___x_42_, v___x_43_);
v___x_45_ = ((lean_object*)(l_Lean_Doc_MarkdownM_run_x27___closed__2));
v___x_46_ = lean_string_append(v_main_39_, v___x_45_);
v___x_47_ = l_String_intercalate(v___x_45_, v_foots_44_);
v___x_48_ = lean_string_append(v___x_46_, v___x_47_);
lean_dec_ref(v___x_47_);
return v___x_48_;
}
else
{
lean_dec(v_snd_36_);
return v_main_39_;
}
}
}
LEAN_EXPORT lean_object* l_String_Slice_Pos_revSkipWhile___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_trimEndSpaces_spec__0(lean_object* v_s_49_, lean_object* v_pos_50_){
_start:
{
lean_object* v_str_51_; lean_object* v_startInclusive_52_; lean_object* v___x_53_; lean_object* v___x_54_; lean_object* v___x_55_; uint8_t v___x_56_; 
v_str_51_ = lean_ctor_get(v_s_49_, 0);
v_startInclusive_52_ = lean_ctor_get(v_s_49_, 1);
v___x_53_ = lean_nat_add(v_startInclusive_52_, v_pos_50_);
v___x_54_ = lean_nat_sub(v___x_53_, v_startInclusive_52_);
v___x_55_ = lean_unsigned_to_nat(0u);
v___x_56_ = lean_nat_dec_eq(v___x_54_, v___x_55_);
if (v___x_56_ == 0)
{
uint32_t v___x_57_; lean_object* v___x_58_; lean_object* v___x_59_; lean_object* v___x_60_; lean_object* v___x_61_; lean_object* v___x_62_; uint32_t v___x_63_; uint8_t v___x_64_; 
v___x_57_ = 32;
lean_inc(v_startInclusive_52_);
lean_inc_ref(v_str_51_);
v___x_58_ = lean_alloc_ctor(0, 3, 0);
lean_ctor_set(v___x_58_, 0, v_str_51_);
lean_ctor_set(v___x_58_, 1, v_startInclusive_52_);
lean_ctor_set(v___x_58_, 2, v___x_53_);
v___x_59_ = lean_unsigned_to_nat(1u);
v___x_60_ = lean_nat_sub(v___x_54_, v___x_59_);
lean_dec(v___x_54_);
v___x_61_ = l_String_Slice_posLE(v___x_58_, v___x_60_);
lean_dec_ref(v___x_58_);
v___x_62_ = lean_nat_add(v_startInclusive_52_, v___x_61_);
v___x_63_ = lean_string_utf8_get_fast(v_str_51_, v___x_62_);
lean_dec(v___x_62_);
v___x_64_ = lean_uint32_dec_eq(v___x_63_, v___x_57_);
if (v___x_64_ == 0)
{
lean_dec(v___x_61_);
return v_pos_50_;
}
else
{
uint8_t v___x_65_; 
v___x_65_ = lean_nat_dec_lt(v___x_61_, v_pos_50_);
if (v___x_65_ == 0)
{
lean_dec(v___x_61_);
return v_pos_50_;
}
else
{
lean_dec(v_pos_50_);
v_pos_50_ = v___x_61_;
goto _start;
}
}
}
else
{
lean_dec(v___x_54_);
lean_dec(v___x_53_);
return v_pos_50_;
}
}
}
LEAN_EXPORT lean_object* l_String_Slice_Pos_revSkipWhile___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_trimEndSpaces_spec__0___boxed(lean_object* v_s_67_, lean_object* v_pos_68_){
_start:
{
lean_object* v_res_69_; 
v_res_69_ = l_String_Slice_Pos_revSkipWhile___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_trimEndSpaces_spec__0(v_s_67_, v_pos_68_);
lean_dec_ref(v_s_67_);
return v_res_69_;
}
}
LEAN_EXPORT lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_trimEndSpaces(lean_object* v_s_70_){
_start:
{
lean_object* v___x_71_; lean_object* v___x_72_; lean_object* v___x_73_; lean_object* v___x_74_; lean_object* v___x_75_; 
v___x_71_ = lean_unsigned_to_nat(0u);
v___x_72_ = lean_string_utf8_byte_size(v_s_70_);
lean_inc_ref(v_s_70_);
v___x_73_ = lean_alloc_ctor(0, 3, 0);
lean_ctor_set(v___x_73_, 0, v_s_70_);
lean_ctor_set(v___x_73_, 1, v___x_71_);
lean_ctor_set(v___x_73_, 2, v___x_72_);
v___x_74_ = l_String_Slice_Pos_revSkipWhile___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_trimEndSpaces_spec__0(v___x_73_, v___x_72_);
lean_dec_ref(v___x_73_);
v___x_75_ = lean_string_utf8_extract(v_s_70_, v___x_71_, v___x_74_);
lean_dec(v___x_74_);
lean_dec_ref(v_s_70_);
return v___x_75_;
}
}
LEAN_EXPORT lean_object* l___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Lean_Doc_prefixLines_spec__0(lean_object* v_p_76_, lean_object* v_pTrim_77_, size_t v_sz_78_, size_t v_i_79_, lean_object* v_bs_80_){
_start:
{
uint8_t v___x_81_; 
v___x_81_ = lean_usize_dec_lt(v_i_79_, v_sz_78_);
if (v___x_81_ == 0)
{
lean_dec_ref(v_pTrim_77_);
lean_dec_ref(v_p_76_);
return v_bs_80_;
}
else
{
lean_object* v_v_82_; lean_object* v___x_83_; lean_object* v_bs_x27_84_; lean_object* v___y_86_; lean_object* v___x_91_; uint8_t v___x_92_; 
v_v_82_ = lean_array_uget(v_bs_80_, v_i_79_);
v___x_83_ = lean_unsigned_to_nat(0u);
v_bs_x27_84_ = lean_array_uset(v_bs_80_, v_i_79_, v___x_83_);
v___x_91_ = lean_string_utf8_byte_size(v_v_82_);
v___x_92_ = lean_nat_dec_eq(v___x_91_, v___x_83_);
if (v___x_92_ == 0)
{
lean_object* v___x_93_; 
lean_inc_ref(v_p_76_);
v___x_93_ = lean_string_append(v_p_76_, v_v_82_);
lean_dec(v_v_82_);
v___y_86_ = v___x_93_;
goto v___jp_85_;
}
else
{
lean_dec(v_v_82_);
lean_inc_ref(v_pTrim_77_);
v___y_86_ = v_pTrim_77_;
goto v___jp_85_;
}
v___jp_85_:
{
size_t v___x_87_; size_t v___x_88_; lean_object* v___x_89_; 
v___x_87_ = ((size_t)1ULL);
v___x_88_ = lean_usize_add(v_i_79_, v___x_87_);
v___x_89_ = lean_array_uset(v_bs_x27_84_, v_i_79_, v___y_86_);
v_i_79_ = v___x_88_;
v_bs_80_ = v___x_89_;
goto _start;
}
}
}
}
LEAN_EXPORT lean_object* l___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Lean_Doc_prefixLines_spec__0___boxed(lean_object* v_p_94_, lean_object* v_pTrim_95_, lean_object* v_sz_96_, lean_object* v_i_97_, lean_object* v_bs_98_){
_start:
{
size_t v_sz_boxed_99_; size_t v_i_boxed_100_; lean_object* v_res_101_; 
v_sz_boxed_99_ = lean_unbox_usize(v_sz_96_);
lean_dec(v_sz_96_);
v_i_boxed_100_ = lean_unbox_usize(v_i_97_);
lean_dec(v_i_97_);
v_res_101_ = l___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Lean_Doc_prefixLines_spec__0(v_p_94_, v_pTrim_95_, v_sz_boxed_99_, v_i_boxed_100_, v_bs_98_);
return v_res_101_;
}
}
LEAN_EXPORT lean_object* l_Lean_Doc_prefixLines(lean_object* v_p_102_, lean_object* v_lines_103_){
_start:
{
lean_object* v_pTrim_104_; size_t v_sz_105_; size_t v___x_106_; lean_object* v___x_107_; 
lean_inc_ref(v_p_102_);
v_pTrim_104_ = l___private_Lean_DocString_Markdown_0__Lean_Doc_trimEndSpaces(v_p_102_);
v_sz_105_ = lean_array_size(v_lines_103_);
v___x_106_ = ((size_t)0ULL);
v___x_107_ = l___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map___at___00Lean_Doc_prefixLines_spec__0(v_p_102_, v_pTrim_104_, v_sz_105_, v___x_106_, v_lines_103_);
return v___x_107_;
}
}
LEAN_EXPORT lean_object* l_Array_mapFinIdxM_map___at___00Lean_Doc_prefixListLines_spec__0___redArg(lean_object* v_rest_108_, lean_object* v_restTrim_109_, lean_object* v_head_110_, lean_object* v_headTrim_111_, lean_object* v_as_112_, lean_object* v_i_113_, lean_object* v_j_114_, lean_object* v_bs_115_){
_start:
{
lean_object* v_zero_116_; uint8_t v_isZero_117_; 
v_zero_116_ = lean_unsigned_to_nat(0u);
v_isZero_117_ = lean_nat_dec_eq(v_i_113_, v_zero_116_);
if (v_isZero_117_ == 1)
{
lean_dec(v_j_114_);
lean_dec(v_i_113_);
lean_dec_ref(v_headTrim_111_);
lean_dec_ref(v_head_110_);
lean_dec_ref(v_restTrim_109_);
lean_dec_ref(v_rest_108_);
return v_bs_115_;
}
else
{
lean_object* v_one_118_; lean_object* v_n_119_; lean_object* v___y_121_; lean_object* v___x_125_; lean_object* v_fst_127_; lean_object* v_snd_128_; uint8_t v___x_132_; 
v_one_118_ = lean_unsigned_to_nat(1u);
v_n_119_ = lean_nat_sub(v_i_113_, v_one_118_);
lean_dec(v_i_113_);
v___x_125_ = lean_array_fget_borrowed(v_as_112_, v_j_114_);
v___x_132_ = lean_nat_dec_eq(v_j_114_, v_zero_116_);
if (v___x_132_ == 0)
{
lean_inc_ref(v_restTrim_109_);
lean_inc_ref(v_rest_108_);
v_fst_127_ = v_rest_108_;
v_snd_128_ = v_restTrim_109_;
goto v___jp_126_;
}
else
{
lean_inc_ref(v_headTrim_111_);
lean_inc_ref(v_head_110_);
v_fst_127_ = v_head_110_;
v_snd_128_ = v_headTrim_111_;
goto v___jp_126_;
}
v___jp_120_:
{
lean_object* v___x_122_; lean_object* v___x_123_; 
v___x_122_ = lean_nat_add(v_j_114_, v_one_118_);
lean_dec(v_j_114_);
v___x_123_ = lean_array_push(v_bs_115_, v___y_121_);
v_i_113_ = v_n_119_;
v_j_114_ = v___x_122_;
v_bs_115_ = v___x_123_;
goto _start;
}
v___jp_126_:
{
lean_object* v___x_129_; uint8_t v___x_130_; 
v___x_129_ = lean_string_utf8_byte_size(v___x_125_);
v___x_130_ = lean_nat_dec_eq(v___x_129_, v_zero_116_);
if (v___x_130_ == 0)
{
lean_object* v___x_131_; 
lean_dec_ref(v_snd_128_);
v___x_131_ = lean_string_append(v_fst_127_, v___x_125_);
v___y_121_ = v___x_131_;
goto v___jp_120_;
}
else
{
lean_dec_ref(v_fst_127_);
v___y_121_ = v_snd_128_;
goto v___jp_120_;
}
}
}
}
}
LEAN_EXPORT lean_object* l_Array_mapFinIdxM_map___at___00Lean_Doc_prefixListLines_spec__0___redArg___boxed(lean_object* v_rest_133_, lean_object* v_restTrim_134_, lean_object* v_head_135_, lean_object* v_headTrim_136_, lean_object* v_as_137_, lean_object* v_i_138_, lean_object* v_j_139_, lean_object* v_bs_140_){
_start:
{
lean_object* v_res_141_; 
v_res_141_ = l_Array_mapFinIdxM_map___at___00Lean_Doc_prefixListLines_spec__0___redArg(v_rest_133_, v_restTrim_134_, v_head_135_, v_headTrim_136_, v_as_137_, v_i_138_, v_j_139_, v_bs_140_);
lean_dec_ref(v_as_137_);
return v_res_141_;
}
}
LEAN_EXPORT lean_object* l_Lean_Doc_prefixListLines(lean_object* v_head_142_, lean_object* v_rest_143_, lean_object* v_lines_144_){
_start:
{
lean_object* v_headTrim_145_; lean_object* v_restTrim_146_; lean_object* v___x_147_; lean_object* v___x_148_; lean_object* v___x_149_; lean_object* v___x_150_; 
lean_inc_ref(v_head_142_);
v_headTrim_145_ = l___private_Lean_DocString_Markdown_0__Lean_Doc_trimEndSpaces(v_head_142_);
lean_inc_ref(v_rest_143_);
v_restTrim_146_ = l___private_Lean_DocString_Markdown_0__Lean_Doc_trimEndSpaces(v_rest_143_);
v___x_147_ = lean_array_get_size(v_lines_144_);
v___x_148_ = lean_unsigned_to_nat(0u);
v___x_149_ = lean_mk_empty_array_with_capacity(v___x_147_);
v___x_150_ = l_Array_mapFinIdxM_map___at___00Lean_Doc_prefixListLines_spec__0___redArg(v_rest_143_, v_restTrim_146_, v_head_142_, v_headTrim_145_, v_lines_144_, v___x_147_, v___x_148_, v___x_149_);
return v___x_150_;
}
}
LEAN_EXPORT lean_object* l_Lean_Doc_prefixListLines___boxed(lean_object* v_head_151_, lean_object* v_rest_152_, lean_object* v_lines_153_){
_start:
{
lean_object* v_res_154_; 
v_res_154_ = l_Lean_Doc_prefixListLines(v_head_151_, v_rest_152_, v_lines_153_);
lean_dec_ref(v_lines_153_);
return v_res_154_;
}
}
LEAN_EXPORT lean_object* l_Array_mapFinIdxM_map___at___00Lean_Doc_prefixListLines_spec__0(lean_object* v_rest_155_, lean_object* v_restTrim_156_, lean_object* v_head_157_, lean_object* v_headTrim_158_, lean_object* v_as_159_, lean_object* v_i_160_, lean_object* v_j_161_, lean_object* v_inv_162_, lean_object* v_bs_163_){
_start:
{
lean_object* v___x_164_; 
v___x_164_ = l_Array_mapFinIdxM_map___at___00Lean_Doc_prefixListLines_spec__0___redArg(v_rest_155_, v_restTrim_156_, v_head_157_, v_headTrim_158_, v_as_159_, v_i_160_, v_j_161_, v_bs_163_);
return v___x_164_;
}
}
LEAN_EXPORT lean_object* l_Array_mapFinIdxM_map___at___00Lean_Doc_prefixListLines_spec__0___boxed(lean_object* v_rest_165_, lean_object* v_restTrim_166_, lean_object* v_head_167_, lean_object* v_headTrim_168_, lean_object* v_as_169_, lean_object* v_i_170_, lean_object* v_j_171_, lean_object* v_inv_172_, lean_object* v_bs_173_){
_start:
{
lean_object* v_res_174_; 
v_res_174_ = l_Array_mapFinIdxM_map___at___00Lean_Doc_prefixListLines_spec__0(v_rest_165_, v_restTrim_166_, v_head_167_, v_headTrim_168_, v_as_169_, v_i_170_, v_j_171_, v_inv_172_, v_bs_173_);
lean_dec_ref(v_as_169_);
return v_res_174_;
}
}
LEAN_EXPORT lean_object* l___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Lean_Doc_joinBlocks_spec__0(lean_object* v_as_176_, size_t v_i_177_, size_t v_stop_178_, lean_object* v_b_179_){
_start:
{
lean_object* v___y_181_; uint8_t v___x_185_; 
v___x_185_ = lean_usize_dec_eq(v_i_177_, v_stop_178_);
if (v___x_185_ == 0)
{
lean_object* v___x_186_; lean_object* v___x_187_; lean_object* v___x_188_; uint8_t v___x_189_; 
v___x_186_ = lean_array_uget_borrowed(v_as_176_, v_i_177_);
v___x_187_ = lean_array_get_size(v___x_186_);
v___x_188_ = lean_unsigned_to_nat(0u);
v___x_189_ = lean_nat_dec_eq(v___x_187_, v___x_188_);
if (v___x_189_ == 0)
{
lean_object* v___x_190_; uint8_t v___x_191_; 
v___x_190_ = lean_array_get_size(v_b_179_);
v___x_191_ = lean_nat_dec_eq(v___x_190_, v___x_188_);
if (v___x_191_ == 0)
{
lean_object* v___x_192_; lean_object* v___x_193_; lean_object* v___x_194_; 
v___x_192_ = ((lean_object*)(l___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Lean_Doc_joinBlocks_spec__0___closed__0));
v___x_193_ = lean_array_push(v_b_179_, v___x_192_);
v___x_194_ = l_Array_append___redArg(v___x_193_, v___x_186_);
v___y_181_ = v___x_194_;
goto v___jp_180_;
}
else
{
lean_dec_ref(v_b_179_);
lean_inc(v___x_186_);
v___y_181_ = v___x_186_;
goto v___jp_180_;
}
}
else
{
v___y_181_ = v_b_179_;
goto v___jp_180_;
}
}
else
{
return v_b_179_;
}
v___jp_180_:
{
size_t v___x_182_; size_t v___x_183_; 
v___x_182_ = ((size_t)1ULL);
v___x_183_ = lean_usize_add(v_i_177_, v___x_182_);
v_i_177_ = v___x_183_;
v_b_179_ = v___y_181_;
goto _start;
}
}
}
LEAN_EXPORT lean_object* l___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Lean_Doc_joinBlocks_spec__0___boxed(lean_object* v_as_195_, lean_object* v_i_196_, lean_object* v_stop_197_, lean_object* v_b_198_){
_start:
{
size_t v_i_boxed_199_; size_t v_stop_boxed_200_; lean_object* v_res_201_; 
v_i_boxed_199_ = lean_unbox_usize(v_i_196_);
lean_dec(v_i_196_);
v_stop_boxed_200_ = lean_unbox_usize(v_stop_197_);
lean_dec(v_stop_197_);
v_res_201_ = l___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Lean_Doc_joinBlocks_spec__0(v_as_195_, v_i_boxed_199_, v_stop_boxed_200_, v_b_198_);
lean_dec_ref(v_as_195_);
return v_res_201_;
}
}
LEAN_EXPORT lean_object* l_Lean_Doc_joinBlocks(lean_object* v_blocks_204_){
_start:
{
lean_object* v___x_205_; lean_object* v___x_206_; lean_object* v___x_207_; uint8_t v___x_208_; 
v___x_205_ = lean_unsigned_to_nat(0u);
v___x_206_ = ((lean_object*)(l_Lean_Doc_joinBlocks___closed__0));
v___x_207_ = lean_array_get_size(v_blocks_204_);
v___x_208_ = lean_nat_dec_lt(v___x_205_, v___x_207_);
if (v___x_208_ == 0)
{
return v___x_206_;
}
else
{
uint8_t v___x_209_; 
v___x_209_ = lean_nat_dec_le(v___x_207_, v___x_207_);
if (v___x_209_ == 0)
{
if (v___x_208_ == 0)
{
return v___x_206_;
}
else
{
size_t v___x_210_; size_t v___x_211_; lean_object* v___x_212_; 
v___x_210_ = ((size_t)0ULL);
v___x_211_ = lean_usize_of_nat(v___x_207_);
v___x_212_ = l___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Lean_Doc_joinBlocks_spec__0(v_blocks_204_, v___x_210_, v___x_211_, v___x_206_);
return v___x_212_;
}
}
else
{
size_t v___x_213_; size_t v___x_214_; lean_object* v___x_215_; 
v___x_213_ = ((size_t)0ULL);
v___x_214_ = lean_usize_of_nat(v___x_207_);
v___x_215_ = l___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Lean_Doc_joinBlocks_spec__0(v_blocks_204_, v___x_213_, v___x_214_, v___x_206_);
return v___x_215_;
}
}
}
}
LEAN_EXPORT lean_object* l_Lean_Doc_joinBlocks___boxed(lean_object* v_blocks_216_){
_start:
{
lean_object* v_res_217_; 
v_res_217_ = l_Lean_Doc_joinBlocks(v_blocks_216_);
lean_dec_ref(v_blocks_216_);
return v_res_217_;
}
}
static lean_object* _init_l___private_Lean_DocString_Markdown_0__Lean_Doc_glueInlineBoundary___closed__1(void){
_start:
{
lean_object* v___x_219_; lean_object* v___x_220_; 
v___x_219_ = ((lean_object*)(l___private_Lean_DocString_Markdown_0__Lean_Doc_glueInlineBoundary___closed__0));
v___x_220_ = lean_string_utf8_byte_size(v___x_219_);
return v___x_220_;
}
}
LEAN_EXPORT lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_glueInlineBoundary(lean_object* v_l_222_, lean_object* v_r_223_){
_start:
{
lean_object* v___x_224_; lean_object* v___x_225_; lean_object* v___x_226_; uint8_t v___x_227_; 
v___x_224_ = ((lean_object*)(l___private_Lean_DocString_Markdown_0__Lean_Doc_glueInlineBoundary___closed__0));
v___x_225_ = lean_string_utf8_byte_size(v_l_222_);
v___x_226_ = lean_obj_once(&l___private_Lean_DocString_Markdown_0__Lean_Doc_glueInlineBoundary___closed__1, &l___private_Lean_DocString_Markdown_0__Lean_Doc_glueInlineBoundary___closed__1_once, _init_l___private_Lean_DocString_Markdown_0__Lean_Doc_glueInlineBoundary___closed__1);
v___x_227_ = lean_nat_dec_le(v___x_226_, v___x_225_);
if (v___x_227_ == 0)
{
lean_object* v___x_228_; 
v___x_228_ = lean_string_append(v_l_222_, v_r_223_);
return v___x_228_;
}
else
{
lean_object* v___x_229_; lean_object* v___x_230_; uint8_t v___x_231_; 
v___x_229_ = lean_unsigned_to_nat(0u);
v___x_230_ = lean_nat_sub(v___x_225_, v___x_226_);
v___x_231_ = lean_string_memcmp(v_l_222_, v___x_224_, v___x_230_, v___x_229_, v___x_226_);
lean_dec(v___x_230_);
if (v___x_231_ == 0)
{
lean_object* v___x_232_; 
v___x_232_ = lean_string_append(v_l_222_, v_r_223_);
return v___x_232_;
}
else
{
lean_object* v___x_233_; uint8_t v___x_234_; 
v___x_233_ = lean_string_utf8_byte_size(v_r_223_);
v___x_234_ = lean_nat_dec_le(v___x_226_, v___x_233_);
if (v___x_234_ == 0)
{
lean_object* v___x_235_; 
v___x_235_ = lean_string_append(v_l_222_, v_r_223_);
return v___x_235_;
}
else
{
uint8_t v___x_236_; 
v___x_236_ = lean_string_memcmp(v_r_223_, v___x_224_, v___x_229_, v___x_229_, v___x_226_);
if (v___x_236_ == 0)
{
lean_object* v___x_237_; 
v___x_237_ = lean_string_append(v_l_222_, v_r_223_);
return v___x_237_;
}
else
{
lean_object* v___x_238_; lean_object* v___x_239_; lean_object* v___x_240_; 
v___x_238_ = ((lean_object*)(l___private_Lean_DocString_Markdown_0__Lean_Doc_glueInlineBoundary___closed__2));
v___x_239_ = lean_string_append(v_l_222_, v___x_238_);
v___x_240_ = lean_string_append(v___x_239_, v_r_223_);
return v___x_240_;
}
}
}
}
}
}
LEAN_EXPORT lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_glueInlineBoundary___boxed(lean_object* v_l_241_, lean_object* v_r_242_){
_start:
{
lean_object* v_res_243_; 
v_res_243_ = l___private_Lean_DocString_Markdown_0__Lean_Doc_glueInlineBoundary(v_l_241_, v_r_242_);
lean_dec_ref(v_r_242_);
return v_res_243_;
}
}
LEAN_EXPORT lean_object* l___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Lean_Doc_joinInlines_spec__0(lean_object* v_as_244_, size_t v_i_245_, size_t v_stop_246_, lean_object* v_b_247_){
_start:
{
lean_object* v___y_249_; uint8_t v___x_253_; 
v___x_253_ = lean_usize_dec_eq(v_i_245_, v_stop_246_);
if (v___x_253_ == 0)
{
lean_object* v___x_254_; lean_object* v___x_255_; lean_object* v___x_256_; uint8_t v___x_257_; 
v___x_254_ = lean_array_uget_borrowed(v_as_244_, v_i_245_);
v___x_255_ = lean_array_get_size(v___x_254_);
v___x_256_ = lean_unsigned_to_nat(0u);
v___x_257_ = lean_nat_dec_eq(v___x_255_, v___x_256_);
if (v___x_257_ == 0)
{
lean_object* v___x_258_; uint8_t v___x_259_; 
v___x_258_ = lean_array_get_size(v_b_247_);
v___x_259_ = lean_nat_dec_eq(v___x_258_, v___x_256_);
if (v___x_259_ == 0)
{
lean_object* v___x_260_; lean_object* v_lastIdx_261_; lean_object* v___x_262_; lean_object* v___x_263_; lean_object* v_glued_264_; lean_object* v___x_265_; lean_object* v___x_266_; lean_object* v___x_267_; 
v___x_260_ = lean_unsigned_to_nat(1u);
v_lastIdx_261_ = lean_nat_sub(v___x_258_, v___x_260_);
v___x_262_ = lean_array_fget_borrowed(v_b_247_, v_lastIdx_261_);
v___x_263_ = lean_array_fget_borrowed(v___x_254_, v___x_256_);
lean_inc(v___x_262_);
v_glued_264_ = l___private_Lean_DocString_Markdown_0__Lean_Doc_glueInlineBoundary(v___x_262_, v___x_263_);
v___x_265_ = lean_array_fset(v_b_247_, v_lastIdx_261_, v_glued_264_);
lean_dec(v_lastIdx_261_);
v___x_266_ = l_Array_extract___redArg(v___x_254_, v___x_260_, v___x_255_);
v___x_267_ = l_Array_append___redArg(v___x_265_, v___x_266_);
lean_dec_ref(v___x_266_);
v___y_249_ = v___x_267_;
goto v___jp_248_;
}
else
{
lean_dec_ref(v_b_247_);
lean_inc(v___x_254_);
v___y_249_ = v___x_254_;
goto v___jp_248_;
}
}
else
{
v___y_249_ = v_b_247_;
goto v___jp_248_;
}
}
else
{
return v_b_247_;
}
v___jp_248_:
{
size_t v___x_250_; size_t v___x_251_; 
v___x_250_ = ((size_t)1ULL);
v___x_251_ = lean_usize_add(v_i_245_, v___x_250_);
v_i_245_ = v___x_251_;
v_b_247_ = v___y_249_;
goto _start;
}
}
}
LEAN_EXPORT lean_object* l___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Lean_Doc_joinInlines_spec__0___boxed(lean_object* v_as_268_, lean_object* v_i_269_, lean_object* v_stop_270_, lean_object* v_b_271_){
_start:
{
size_t v_i_boxed_272_; size_t v_stop_boxed_273_; lean_object* v_res_274_; 
v_i_boxed_272_ = lean_unbox_usize(v_i_269_);
lean_dec(v_i_269_);
v_stop_boxed_273_ = lean_unbox_usize(v_stop_270_);
lean_dec(v_stop_270_);
v_res_274_ = l___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Lean_Doc_joinInlines_spec__0(v_as_268_, v_i_boxed_272_, v_stop_boxed_273_, v_b_271_);
lean_dec_ref(v_as_268_);
return v_res_274_;
}
}
LEAN_EXPORT lean_object* l_Lean_Doc_joinInlines(lean_object* v_parts_275_){
_start:
{
lean_object* v___x_276_; lean_object* v___x_277_; lean_object* v___x_278_; uint8_t v___x_279_; 
v___x_276_ = lean_unsigned_to_nat(0u);
v___x_277_ = ((lean_object*)(l_Lean_Doc_joinBlocks___closed__0));
v___x_278_ = lean_array_get_size(v_parts_275_);
v___x_279_ = lean_nat_dec_lt(v___x_276_, v___x_278_);
if (v___x_279_ == 0)
{
return v___x_277_;
}
else
{
uint8_t v___x_280_; 
v___x_280_ = lean_nat_dec_le(v___x_278_, v___x_278_);
if (v___x_280_ == 0)
{
if (v___x_279_ == 0)
{
return v___x_277_;
}
else
{
size_t v___x_281_; size_t v___x_282_; lean_object* v___x_283_; 
v___x_281_ = ((size_t)0ULL);
v___x_282_ = lean_usize_of_nat(v___x_278_);
v___x_283_ = l___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Lean_Doc_joinInlines_spec__0(v_parts_275_, v___x_281_, v___x_282_, v___x_277_);
return v___x_283_;
}
}
else
{
size_t v___x_284_; size_t v___x_285_; lean_object* v___x_286_; 
v___x_284_ = ((size_t)0ULL);
v___x_285_ = lean_usize_of_nat(v___x_278_);
v___x_286_ = l___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Lean_Doc_joinInlines_spec__0(v_parts_275_, v___x_284_, v___x_285_, v___x_277_);
return v___x_286_;
}
}
}
}
LEAN_EXPORT lean_object* l_Lean_Doc_joinInlines___boxed(lean_object* v_parts_287_){
_start:
{
lean_object* v_res_288_; 
v_res_288_ = l_Lean_Doc_joinInlines(v_parts_287_);
lean_dec_ref(v_parts_287_);
return v_res_288_;
}
}
LEAN_EXPORT lean_object* l_Lean_Doc_instMarkdownInlineEmpty___lam__0(lean_object* v_a_289_, uint8_t v_a_290_, lean_object* v_a_291_, lean_object* v_a_292_){
_start:
{
lean_internal_panic_unreachable();
}
}
LEAN_EXPORT lean_object* l_Lean_Doc_instMarkdownInlineEmpty___lam__0___boxed(lean_object* v_a_293_, lean_object* v_a_294_, lean_object* v_a_295_, lean_object* v_a_296_){
_start:
{
uint8_t v_a_13__boxed_297_; lean_object* v_res_298_; 
v_a_13__boxed_297_ = lean_unbox(v_a_294_);
v_res_298_ = l_Lean_Doc_instMarkdownInlineEmpty___lam__0(v_a_293_, v_a_13__boxed_297_, v_a_295_, v_a_296_);
lean_dec_ref(v_a_296_);
lean_dec_ref(v_a_295_);
lean_dec_ref(v_a_293_);
return v_res_298_;
}
}
LEAN_EXPORT lean_object* l_Lean_Doc_instMarkdownBlockEmpty___lam__0(lean_object* v_a_301_, lean_object* v_a_302_, uint8_t v_a_303_, lean_object* v_a_304_, lean_object* v_a_305_){
_start:
{
lean_internal_panic_unreachable();
}
}
LEAN_EXPORT lean_object* l_Lean_Doc_instMarkdownBlockEmpty___lam__0___boxed(lean_object* v_a_306_, lean_object* v_a_307_, lean_object* v_a_308_, lean_object* v_a_309_, lean_object* v_a_310_){
_start:
{
uint8_t v_a_17__boxed_311_; lean_object* v_res_312_; 
v_a_17__boxed_311_ = lean_unbox(v_a_308_);
v_res_312_ = l_Lean_Doc_instMarkdownBlockEmpty___lam__0(v_a_306_, v_a_307_, v_a_17__boxed_311_, v_a_309_, v_a_310_);
lean_dec_ref(v_a_310_);
lean_dec_ref(v_a_309_);
lean_dec_ref(v_a_307_);
lean_dec_ref(v_a_306_);
return v_res_312_;
}
}
LEAN_EXPORT lean_object* l_Lean_Doc_instMarkdownBlockEmpty(lean_object* v_i_314_){
_start:
{
lean_object* v___f_315_; 
v___f_315_ = ((lean_object*)(l_Lean_Doc_instMarkdownBlockEmpty___closed__0));
return v___f_315_;
}
}
LEAN_EXPORT uint8_t l_Option_instBEq_beq___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_midLineSpecial_spec__1(lean_object* v_x_316_, lean_object* v_x_317_){
_start:
{
if (lean_obj_tag(v_x_316_) == 0)
{
if (lean_obj_tag(v_x_317_) == 0)
{
uint8_t v___x_318_; 
v___x_318_ = 1;
return v___x_318_;
}
else
{
uint8_t v___x_319_; 
v___x_319_ = 0;
return v___x_319_;
}
}
else
{
if (lean_obj_tag(v_x_317_) == 0)
{
uint8_t v___x_320_; 
v___x_320_ = 0;
return v___x_320_;
}
else
{
lean_object* v_val_321_; lean_object* v_val_322_; uint32_t v___x_323_; uint32_t v___x_324_; uint8_t v___x_325_; 
v_val_321_ = lean_ctor_get(v_x_316_, 0);
v_val_322_ = lean_ctor_get(v_x_317_, 0);
v___x_323_ = lean_unbox_uint32(v_val_321_);
v___x_324_ = lean_unbox_uint32(v_val_322_);
v___x_325_ = lean_uint32_dec_eq(v___x_323_, v___x_324_);
return v___x_325_;
}
}
}
}
LEAN_EXPORT lean_object* l_Option_instBEq_beq___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_midLineSpecial_spec__1___boxed(lean_object* v_x_326_, lean_object* v_x_327_){
_start:
{
uint8_t v_res_328_; lean_object* v_r_329_; 
v_res_328_ = l_Option_instBEq_beq___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_midLineSpecial_spec__1(v_x_326_, v_x_327_);
lean_dec(v_x_327_);
lean_dec(v_x_326_);
v_r_329_ = lean_box(v_res_328_);
return v_r_329_;
}
}
LEAN_EXPORT uint8_t l_WellFounded_opaqueFix_u2083___at___00String_Slice_contains___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_midLineSpecial_spec__0_spec__0___redArg(lean_object* v_s_330_, uint32_t v_c_331_, lean_object* v_a_332_, uint8_t v_b_333_){
_start:
{
lean_object* v_str_334_; lean_object* v_startInclusive_335_; lean_object* v_endExclusive_336_; lean_object* v___x_337_; uint8_t v___x_338_; 
v_str_334_ = lean_ctor_get(v_s_330_, 0);
v_startInclusive_335_ = lean_ctor_get(v_s_330_, 1);
v_endExclusive_336_ = lean_ctor_get(v_s_330_, 2);
v___x_337_ = lean_nat_sub(v_endExclusive_336_, v_startInclusive_335_);
v___x_338_ = lean_nat_dec_eq(v_a_332_, v___x_337_);
lean_dec(v___x_337_);
if (v___x_338_ == 0)
{
lean_object* v___x_339_; uint32_t v___x_340_; uint8_t v___x_341_; 
v___x_339_ = lean_nat_add(v_startInclusive_335_, v_a_332_);
lean_dec(v_a_332_);
v___x_340_ = lean_string_utf8_get_fast(v_str_334_, v___x_339_);
v___x_341_ = lean_uint32_dec_eq(v___x_340_, v_c_331_);
if (v___x_341_ == 0)
{
lean_object* v___x_342_; lean_object* v___x_343_; 
v___x_342_ = lean_string_utf8_next_fast(v_str_334_, v___x_339_);
lean_dec(v___x_339_);
v___x_343_ = lean_nat_sub(v___x_342_, v_startInclusive_335_);
v_a_332_ = v___x_343_;
v_b_333_ = v___x_341_;
goto _start;
}
else
{
lean_dec(v___x_339_);
return v___x_341_;
}
}
else
{
lean_dec(v_a_332_);
return v_b_333_;
}
}
}
LEAN_EXPORT lean_object* l_WellFounded_opaqueFix_u2083___at___00String_Slice_contains___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_midLineSpecial_spec__0_spec__0___redArg___boxed(lean_object* v_s_345_, lean_object* v_c_346_, lean_object* v_a_347_, lean_object* v_b_348_){
_start:
{
uint32_t v_c_boxed_349_; uint8_t v_b_boxed_350_; uint8_t v_res_351_; lean_object* v_r_352_; 
v_c_boxed_349_ = lean_unbox_uint32(v_c_346_);
lean_dec(v_c_346_);
v_b_boxed_350_ = lean_unbox(v_b_348_);
v_res_351_ = l_WellFounded_opaqueFix_u2083___at___00String_Slice_contains___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_midLineSpecial_spec__0_spec__0___redArg(v_s_345_, v_c_boxed_349_, v_a_347_, v_b_boxed_350_);
lean_dec_ref(v_s_345_);
v_r_352_ = lean_box(v_res_351_);
return v_r_352_;
}
}
LEAN_EXPORT uint8_t l_String_Slice_contains___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_midLineSpecial_spec__0(uint32_t v_c_353_, lean_object* v_s_354_){
_start:
{
lean_object* v_searcher_355_; uint8_t v___x_356_; uint8_t v___x_357_; 
v_searcher_355_ = lean_unsigned_to_nat(0u);
v___x_356_ = 0;
v___x_357_ = l_WellFounded_opaqueFix_u2083___at___00String_Slice_contains___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_midLineSpecial_spec__0_spec__0___redArg(v_s_354_, v_c_353_, v_searcher_355_, v___x_356_);
return v___x_357_;
}
}
LEAN_EXPORT lean_object* l_String_Slice_contains___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_midLineSpecial_spec__0___boxed(lean_object* v_c_358_, lean_object* v_s_359_){
_start:
{
uint32_t v_c_boxed_360_; uint8_t v_res_361_; lean_object* v_r_362_; 
v_c_boxed_360_ = lean_unbox_uint32(v_c_358_);
lean_dec(v_c_358_);
v_res_361_ = l_String_Slice_contains___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_midLineSpecial_spec__0(v_c_boxed_360_, v_s_359_);
lean_dec_ref(v_s_359_);
v_r_362_ = lean_box(v_res_361_);
return v_r_362_;
}
}
static lean_object* _init_l___private_Lean_DocString_Markdown_0__Lean_Doc_midLineSpecial___closed__1(void){
_start:
{
lean_object* v___x_364_; lean_object* v___x_365_; 
v___x_364_ = ((lean_object*)(l___private_Lean_DocString_Markdown_0__Lean_Doc_midLineSpecial___closed__0));
v___x_365_ = lean_string_utf8_byte_size(v___x_364_);
return v___x_365_;
}
}
static lean_object* _init_l___private_Lean_DocString_Markdown_0__Lean_Doc_midLineSpecial___closed__2(void){
_start:
{
lean_object* v___x_366_; lean_object* v___x_367_; lean_object* v___x_368_; lean_object* v___x_369_; 
v___x_366_ = lean_obj_once(&l___private_Lean_DocString_Markdown_0__Lean_Doc_midLineSpecial___closed__1, &l___private_Lean_DocString_Markdown_0__Lean_Doc_midLineSpecial___closed__1_once, _init_l___private_Lean_DocString_Markdown_0__Lean_Doc_midLineSpecial___closed__1);
v___x_367_ = lean_unsigned_to_nat(0u);
v___x_368_ = ((lean_object*)(l___private_Lean_DocString_Markdown_0__Lean_Doc_midLineSpecial___closed__0));
v___x_369_ = lean_alloc_ctor(0, 3, 0);
lean_ctor_set(v___x_369_, 0, v___x_368_);
lean_ctor_set(v___x_369_, 1, v___x_367_);
lean_ctor_set(v___x_369_, 2, v___x_366_);
return v___x_369_;
}
}
static lean_object* _init_l___private_Lean_DocString_Markdown_0__Lean_Doc_midLineSpecial___closed__3___boxed__const__1(void){
_start:
{
uint32_t v___x_370_; lean_object* v___x_371_; 
v___x_370_ = 91;
v___x_371_ = lean_box_uint32(v___x_370_);
return v___x_371_;
}
}
static lean_object* _init_l___private_Lean_DocString_Markdown_0__Lean_Doc_midLineSpecial___closed__3(void){
_start:
{
lean_object* v___x_372_; lean_object* v___x_373_; 
v___x_372_ = l___private_Lean_DocString_Markdown_0__Lean_Doc_midLineSpecial___closed__3___boxed__const__1;
v___x_373_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v___x_373_, 0, v___x_372_);
return v___x_373_;
}
}
LEAN_EXPORT uint8_t l___private_Lean_DocString_Markdown_0__Lean_Doc_midLineSpecial(uint32_t v_c_374_, lean_object* v_next_x3f_375_){
_start:
{
uint32_t v___x_376_; uint8_t v___x_377_; 
v___x_376_ = 33;
v___x_377_ = lean_uint32_dec_eq(v_c_374_, v___x_376_);
if (v___x_377_ == 0)
{
lean_object* v___x_378_; uint8_t v___x_379_; 
v___x_378_ = lean_obj_once(&l___private_Lean_DocString_Markdown_0__Lean_Doc_midLineSpecial___closed__2, &l___private_Lean_DocString_Markdown_0__Lean_Doc_midLineSpecial___closed__2_once, _init_l___private_Lean_DocString_Markdown_0__Lean_Doc_midLineSpecial___closed__2);
v___x_379_ = l_String_Slice_contains___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_midLineSpecial_spec__0(v_c_374_, v___x_378_);
return v___x_379_;
}
else
{
lean_object* v___x_380_; uint8_t v___x_381_; 
v___x_380_ = lean_obj_once(&l___private_Lean_DocString_Markdown_0__Lean_Doc_midLineSpecial___closed__3, &l___private_Lean_DocString_Markdown_0__Lean_Doc_midLineSpecial___closed__3_once, _init_l___private_Lean_DocString_Markdown_0__Lean_Doc_midLineSpecial___closed__3);
v___x_381_ = l_Option_instBEq_beq___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_midLineSpecial_spec__1(v_next_x3f_375_, v___x_380_);
return v___x_381_;
}
}
}
LEAN_EXPORT lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_midLineSpecial___boxed(lean_object* v_c_382_, lean_object* v_next_x3f_383_){
_start:
{
uint32_t v_c_boxed_384_; uint8_t v_res_385_; lean_object* v_r_386_; 
v_c_boxed_384_ = lean_unbox_uint32(v_c_382_);
lean_dec(v_c_382_);
v_res_385_ = l___private_Lean_DocString_Markdown_0__Lean_Doc_midLineSpecial(v_c_boxed_384_, v_next_x3f_383_);
lean_dec(v_next_x3f_383_);
v_r_386_ = lean_box(v_res_385_);
return v_r_386_;
}
}
LEAN_EXPORT uint8_t l_WellFounded_opaqueFix_u2083___at___00String_Slice_contains___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_midLineSpecial_spec__0_spec__0(lean_object* v_s_387_, uint32_t v_c_388_, lean_object* v_inst_389_, lean_object* v_R_390_, lean_object* v_a_391_, uint8_t v_b_392_, lean_object* v_c_393_){
_start:
{
uint8_t v___x_394_; 
v___x_394_ = l_WellFounded_opaqueFix_u2083___at___00String_Slice_contains___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_midLineSpecial_spec__0_spec__0___redArg(v_s_387_, v_c_388_, v_a_391_, v_b_392_);
return v___x_394_;
}
}
LEAN_EXPORT lean_object* l_WellFounded_opaqueFix_u2083___at___00String_Slice_contains___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_midLineSpecial_spec__0_spec__0___boxed(lean_object* v_s_395_, lean_object* v_c_396_, lean_object* v_inst_397_, lean_object* v_R_398_, lean_object* v_a_399_, lean_object* v_b_400_, lean_object* v_c_401_){
_start:
{
uint32_t v_c_boxed_402_; uint8_t v_b_boxed_403_; uint8_t v_res_404_; lean_object* v_r_405_; 
v_c_boxed_402_ = lean_unbox_uint32(v_c_396_);
lean_dec(v_c_396_);
v_b_boxed_403_ = lean_unbox(v_b_400_);
v_res_404_ = l_WellFounded_opaqueFix_u2083___at___00String_Slice_contains___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_midLineSpecial_spec__0_spec__0(v_s_395_, v_c_boxed_402_, v_inst_397_, v_R_398_, v_a_399_, v_b_boxed_403_, v_c_401_);
lean_dec_ref(v_s_395_);
v_r_405_ = lean_box(v_res_404_);
return v_r_405_;
}
}
static lean_object* _init_l___private_Lean_DocString_Markdown_0__Lean_Doc_markerPrefixSpecial___closed__0___boxed__const__1(void){
_start:
{
uint32_t v___x_406_; lean_object* v___x_407_; 
v___x_406_ = 32;
v___x_407_ = lean_box_uint32(v___x_406_);
return v___x_407_;
}
}
static lean_object* _init_l___private_Lean_DocString_Markdown_0__Lean_Doc_markerPrefixSpecial___closed__0(void){
_start:
{
lean_object* v___x_408_; lean_object* v___x_409_; 
v___x_408_ = l___private_Lean_DocString_Markdown_0__Lean_Doc_markerPrefixSpecial___closed__0___boxed__const__1;
v___x_409_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v___x_409_, 0, v___x_408_);
return v___x_409_;
}
}
LEAN_EXPORT uint8_t l___private_Lean_DocString_Markdown_0__Lean_Doc_markerPrefixSpecial(lean_object* v_prev_x3f_410_, uint32_t v_c_411_, lean_object* v_next_x3f_412_){
_start:
{
uint8_t v___y_414_; lean_object* v___x_431_; uint8_t v___x_432_; 
v___x_431_ = lean_obj_once(&l___private_Lean_DocString_Markdown_0__Lean_Doc_markerPrefixSpecial___closed__0, &l___private_Lean_DocString_Markdown_0__Lean_Doc_markerPrefixSpecial___closed__0_once, _init_l___private_Lean_DocString_Markdown_0__Lean_Doc_markerPrefixSpecial___closed__0);
v___x_432_ = l_Option_instBEq_beq___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_midLineSpecial_spec__1(v_next_x3f_412_, v___x_431_);
if (v___x_432_ == 0)
{
if (lean_obj_tag(v_next_x3f_412_) == 0)
{
uint8_t v___x_433_; 
v___x_433_ = 1;
v___y_414_ = v___x_433_;
goto v___jp_413_;
}
else
{
v___y_414_ = v___x_432_;
goto v___jp_413_;
}
}
else
{
v___y_414_ = v___x_432_;
goto v___jp_413_;
}
v___jp_413_:
{
uint32_t v___x_415_; uint8_t v___x_416_; 
v___x_415_ = 62;
v___x_416_ = lean_uint32_dec_eq(v_c_411_, v___x_415_);
if (v___x_416_ == 0)
{
uint32_t v___x_417_; uint8_t v___x_418_; 
v___x_417_ = 45;
v___x_418_ = lean_uint32_dec_eq(v_c_411_, v___x_417_);
if (v___x_418_ == 0)
{
uint32_t v___x_419_; uint8_t v___x_420_; 
v___x_419_ = 43;
v___x_420_ = lean_uint32_dec_eq(v_c_411_, v___x_419_);
if (v___x_420_ == 0)
{
uint32_t v___x_421_; uint8_t v___x_422_; 
v___x_421_ = 46;
v___x_422_ = lean_uint32_dec_eq(v_c_411_, v___x_421_);
if (v___x_422_ == 0)
{
uint8_t v___x_423_; 
v___x_423_ = l___private_Lean_DocString_Markdown_0__Lean_Doc_midLineSpecial(v_c_411_, v_next_x3f_412_);
return v___x_423_;
}
else
{
if (lean_obj_tag(v_prev_x3f_410_) == 0)
{
return v___x_420_;
}
else
{
lean_object* v_val_424_; uint32_t v___x_425_; uint32_t v___x_426_; uint8_t v___x_427_; 
v_val_424_ = lean_ctor_get(v_prev_x3f_410_, 0);
v___x_425_ = 48;
v___x_426_ = lean_unbox_uint32(v_val_424_);
v___x_427_ = lean_uint32_dec_le(v___x_425_, v___x_426_);
if (v___x_427_ == 0)
{
if (v___x_427_ == 0)
{
return v___x_427_;
}
else
{
return v___y_414_;
}
}
else
{
uint32_t v___x_428_; uint32_t v___x_429_; uint8_t v___x_430_; 
v___x_428_ = 57;
v___x_429_ = lean_unbox_uint32(v_val_424_);
v___x_430_ = lean_uint32_dec_le(v___x_429_, v___x_428_);
if (v___x_430_ == 0)
{
return v___x_430_;
}
else
{
return v___y_414_;
}
}
}
}
}
else
{
return v___y_414_;
}
}
else
{
return v___y_414_;
}
}
else
{
return v___x_416_;
}
}
}
}
LEAN_EXPORT lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_markerPrefixSpecial___boxed(lean_object* v_prev_x3f_434_, lean_object* v_c_435_, lean_object* v_next_x3f_436_){
_start:
{
uint32_t v_c_boxed_437_; uint8_t v_res_438_; lean_object* v_r_439_; 
v_c_boxed_437_ = lean_unbox_uint32(v_c_435_);
lean_dec(v_c_435_);
v_res_438_ = l___private_Lean_DocString_Markdown_0__Lean_Doc_markerPrefixSpecial(v_prev_x3f_434_, v_c_boxed_437_, v_next_x3f_436_);
lean_dec(v_next_x3f_436_);
lean_dec(v_prev_x3f_434_);
v_r_439_ = lean_box(v_res_438_);
return v_r_439_;
}
}
LEAN_EXPORT lean_object* l___private_Init_While_0__Lean_Loop_forIn_loop___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_escape_spec__1(lean_object* v_s_440_, lean_object* v_b_441_){
_start:
{
lean_object* v_fst_442_; lean_object* v_snd_443_; lean_object* v___x_445_; uint8_t v_isShared_446_; uint8_t v_isSharedCheck_471_; 
v_fst_442_ = lean_ctor_get(v_b_441_, 0);
v_snd_443_ = lean_ctor_get(v_b_441_, 1);
v_isSharedCheck_471_ = !lean_is_exclusive(v_b_441_);
if (v_isSharedCheck_471_ == 0)
{
v___x_445_ = v_b_441_;
v_isShared_446_ = v_isSharedCheck_471_;
goto v_resetjp_444_;
}
else
{
lean_inc(v_snd_443_);
lean_inc(v_fst_442_);
lean_dec(v_b_441_);
v___x_445_ = lean_box(0);
v_isShared_446_ = v_isSharedCheck_471_;
goto v_resetjp_444_;
}
v_resetjp_444_:
{
lean_object* v___x_447_; uint8_t v___x_448_; 
v___x_447_ = lean_string_utf8_byte_size(v_s_440_);
v___x_448_ = lean_nat_dec_eq(v_snd_443_, v___x_447_);
if (v___x_448_ == 0)
{
uint32_t v___x_449_; lean_object* v___x_450_; lean_object* v_s_x27_452_; lean_object* v___y_459_; uint8_t v___x_463_; 
v___x_449_ = lean_string_utf8_get_fast(v_s_440_, v_snd_443_);
v___x_450_ = lean_string_utf8_next_fast(v_s_440_, v_snd_443_);
lean_dec(v_snd_443_);
v___x_463_ = lean_nat_dec_eq(v___x_450_, v___x_447_);
if (v___x_463_ == 0)
{
uint32_t v___x_464_; lean_object* v___x_465_; lean_object* v___x_466_; 
v___x_464_ = lean_string_utf8_get_fast(v_s_440_, v___x_450_);
v___x_465_ = lean_box_uint32(v___x_464_);
v___x_466_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v___x_466_, 0, v___x_465_);
v___y_459_ = v___x_466_;
goto v___jp_458_;
}
else
{
lean_object* v_prev_x3f_467_; 
v_prev_x3f_467_ = lean_box(0);
v___y_459_ = v_prev_x3f_467_;
goto v___jp_458_;
}
v___jp_451_:
{
lean_object* v___x_453_; lean_object* v___x_455_; 
v___x_453_ = lean_string_push(v_s_x27_452_, v___x_449_);
if (v_isShared_446_ == 0)
{
lean_ctor_set(v___x_445_, 1, v___x_450_);
lean_ctor_set(v___x_445_, 0, v___x_453_);
v___x_455_ = v___x_445_;
goto v_reusejp_454_;
}
else
{
lean_object* v_reuseFailAlloc_457_; 
v_reuseFailAlloc_457_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v_reuseFailAlloc_457_, 0, v___x_453_);
lean_ctor_set(v_reuseFailAlloc_457_, 1, v___x_450_);
v___x_455_ = v_reuseFailAlloc_457_;
goto v_reusejp_454_;
}
v_reusejp_454_:
{
v_b_441_ = v___x_455_;
goto _start;
}
}
v___jp_458_:
{
uint8_t v___x_460_; 
v___x_460_ = l___private_Lean_DocString_Markdown_0__Lean_Doc_midLineSpecial(v___x_449_, v___y_459_);
lean_dec(v___y_459_);
if (v___x_460_ == 0)
{
v_s_x27_452_ = v_fst_442_;
goto v___jp_451_;
}
else
{
uint32_t v___x_461_; lean_object* v___x_462_; 
v___x_461_ = 92;
v___x_462_ = lean_string_push(v_fst_442_, v___x_461_);
v_s_x27_452_ = v___x_462_;
goto v___jp_451_;
}
}
}
else
{
lean_object* v___x_469_; 
if (v_isShared_446_ == 0)
{
v___x_469_ = v___x_445_;
goto v_reusejp_468_;
}
else
{
lean_object* v_reuseFailAlloc_470_; 
v_reuseFailAlloc_470_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v_reuseFailAlloc_470_, 0, v_fst_442_);
lean_ctor_set(v_reuseFailAlloc_470_, 1, v_snd_443_);
v___x_469_ = v_reuseFailAlloc_470_;
goto v_reusejp_468_;
}
v_reusejp_468_:
{
return v___x_469_;
}
}
}
}
}
LEAN_EXPORT lean_object* l___private_Init_While_0__Lean_Loop_forIn_loop___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_escape_spec__1___boxed(lean_object* v_s_472_, lean_object* v_b_473_){
_start:
{
lean_object* v_res_474_; 
v_res_474_ = l___private_Init_While_0__Lean_Loop_forIn_loop___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_escape_spec__1(v_s_472_, v_b_473_);
lean_dec_ref(v_s_472_);
return v_res_474_;
}
}
static lean_object* _init_l___private_Init_While_0__Lean_Loop_forIn_loop___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_escape_spec__0___closed__1(void){
_start:
{
lean_object* v___x_476_; lean_object* v___x_477_; 
v___x_476_ = ((lean_object*)(l___private_Init_While_0__Lean_Loop_forIn_loop___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_escape_spec__0___closed__0));
v___x_477_ = lean_string_utf8_byte_size(v___x_476_);
return v___x_477_;
}
}
static lean_object* _init_l___private_Init_While_0__Lean_Loop_forIn_loop___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_escape_spec__0___closed__2(void){
_start:
{
lean_object* v___x_478_; lean_object* v___x_479_; lean_object* v___x_480_; lean_object* v___x_481_; 
v___x_478_ = lean_obj_once(&l___private_Init_While_0__Lean_Loop_forIn_loop___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_escape_spec__0___closed__1, &l___private_Init_While_0__Lean_Loop_forIn_loop___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_escape_spec__0___closed__1_once, _init_l___private_Init_While_0__Lean_Loop_forIn_loop___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_escape_spec__0___closed__1);
v___x_479_ = lean_unsigned_to_nat(0u);
v___x_480_ = ((lean_object*)(l___private_Init_While_0__Lean_Loop_forIn_loop___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_escape_spec__0___closed__0));
v___x_481_ = lean_alloc_ctor(0, 3, 0);
lean_ctor_set(v___x_481_, 0, v___x_480_);
lean_ctor_set(v___x_481_, 1, v___x_479_);
lean_ctor_set(v___x_481_, 2, v___x_478_);
return v___x_481_;
}
}
LEAN_EXPORT lean_object* l___private_Init_While_0__Lean_Loop_forIn_loop___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_escape_spec__0(lean_object* v_s_482_, lean_object* v_b_483_){
_start:
{
lean_object* v_snd_484_; lean_object* v_fst_485_; lean_object* v___x_487_; uint8_t v_isShared_488_; uint8_t v_isSharedCheck_542_; 
v_snd_484_ = lean_ctor_get(v_b_483_, 1);
v_fst_485_ = lean_ctor_get(v_b_483_, 0);
v_isSharedCheck_542_ = !lean_is_exclusive(v_b_483_);
if (v_isSharedCheck_542_ == 0)
{
v___x_487_ = v_b_483_;
v_isShared_488_ = v_isSharedCheck_542_;
goto v_resetjp_486_;
}
else
{
lean_inc(v_snd_484_);
lean_inc(v_fst_485_);
lean_dec(v_b_483_);
v___x_487_ = lean_box(0);
v_isShared_488_ = v_isSharedCheck_542_;
goto v_resetjp_486_;
}
v_resetjp_486_:
{
lean_object* v_fst_489_; lean_object* v_snd_490_; lean_object* v___x_492_; uint8_t v_isShared_493_; uint8_t v_isSharedCheck_541_; 
v_fst_489_ = lean_ctor_get(v_snd_484_, 0);
v_snd_490_ = lean_ctor_get(v_snd_484_, 1);
v_isSharedCheck_541_ = !lean_is_exclusive(v_snd_484_);
if (v_isSharedCheck_541_ == 0)
{
v___x_492_ = v_snd_484_;
v_isShared_493_ = v_isSharedCheck_541_;
goto v_resetjp_491_;
}
else
{
lean_inc(v_snd_490_);
lean_inc(v_fst_489_);
lean_dec(v_snd_484_);
v___x_492_ = lean_box(0);
v_isShared_493_ = v_isSharedCheck_541_;
goto v_resetjp_491_;
}
v_resetjp_491_:
{
lean_object* v___x_494_; uint8_t v___x_495_; 
v___x_494_ = lean_string_utf8_byte_size(v_s_482_);
v___x_495_ = lean_nat_dec_eq(v_fst_489_, v___x_494_);
if (v___x_495_ == 0)
{
uint32_t v_c_496_; lean_object* v_iter_497_; lean_object* v___y_499_; lean_object* v___y_500_; lean_object* v___y_509_; lean_object* v___y_510_; uint8_t v___y_511_; lean_object* v_s_x27_517_; lean_object* v___y_526_; uint8_t v___x_530_; 
v_c_496_ = lean_string_utf8_get_fast(v_s_482_, v_fst_489_);
v_iter_497_ = lean_string_utf8_next_fast(v_s_482_, v_fst_489_);
lean_dec(v_fst_489_);
v___x_530_ = lean_nat_dec_eq(v_iter_497_, v___x_494_);
if (v___x_530_ == 0)
{
uint32_t v___x_531_; lean_object* v___x_532_; lean_object* v___x_533_; 
v___x_531_ = lean_string_utf8_get_fast(v_s_482_, v_iter_497_);
v___x_532_ = lean_box_uint32(v___x_531_);
v___x_533_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v___x_533_, 0, v___x_532_);
v___y_526_ = v___x_533_;
goto v___jp_525_;
}
else
{
lean_object* v_prev_x3f_534_; 
v_prev_x3f_534_ = lean_box(0);
v___y_526_ = v_prev_x3f_534_;
goto v___jp_525_;
}
v___jp_498_:
{
lean_object* v___x_502_; 
if (v_isShared_493_ == 0)
{
lean_ctor_set(v___x_492_, 1, v___y_499_);
lean_ctor_set(v___x_492_, 0, v_iter_497_);
v___x_502_ = v___x_492_;
goto v_reusejp_501_;
}
else
{
lean_object* v_reuseFailAlloc_507_; 
v_reuseFailAlloc_507_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v_reuseFailAlloc_507_, 0, v_iter_497_);
lean_ctor_set(v_reuseFailAlloc_507_, 1, v___y_499_);
v___x_502_ = v_reuseFailAlloc_507_;
goto v_reusejp_501_;
}
v_reusejp_501_:
{
lean_object* v___x_504_; 
if (v_isShared_488_ == 0)
{
lean_ctor_set(v___x_487_, 1, v___x_502_);
lean_ctor_set(v___x_487_, 0, v___y_500_);
v___x_504_ = v___x_487_;
goto v_reusejp_503_;
}
else
{
lean_object* v_reuseFailAlloc_506_; 
v_reuseFailAlloc_506_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v_reuseFailAlloc_506_, 0, v___y_500_);
lean_ctor_set(v_reuseFailAlloc_506_, 1, v___x_502_);
v___x_504_ = v_reuseFailAlloc_506_;
goto v_reusejp_503_;
}
v_reusejp_503_:
{
v_b_483_ = v___x_504_;
goto _start;
}
}
}
v___jp_508_:
{
if (v___y_511_ == 0)
{
lean_object* v___x_512_; uint8_t v___x_513_; 
v___x_512_ = lean_obj_once(&l___private_Init_While_0__Lean_Loop_forIn_loop___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_escape_spec__0___closed__2, &l___private_Init_While_0__Lean_Loop_forIn_loop___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_escape_spec__0___closed__2_once, _init_l___private_Init_While_0__Lean_Loop_forIn_loop___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_escape_spec__0___closed__2);
v___x_513_ = l_String_Slice_contains___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_midLineSpecial_spec__0(v_c_496_, v___x_512_);
if (v___x_513_ == 0)
{
lean_object* v___x_514_; lean_object* v___x_515_; 
lean_del_object(v___x_492_);
lean_del_object(v___x_487_);
v___x_514_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v___x_514_, 0, v_iter_497_);
lean_ctor_set(v___x_514_, 1, v___y_509_);
v___x_515_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v___x_515_, 0, v___y_510_);
lean_ctor_set(v___x_515_, 1, v___x_514_);
return v___x_515_;
}
else
{
v___y_499_ = v___y_509_;
v___y_500_ = v___y_510_;
goto v___jp_498_;
}
}
else
{
v___y_499_ = v___y_509_;
v___y_500_ = v___y_510_;
goto v___jp_498_;
}
}
v___jp_516_:
{
lean_object* v_s_x27_518_; lean_object* v___x_519_; lean_object* v_prev_x3f_520_; uint32_t v___x_521_; uint8_t v___x_522_; 
v_s_x27_518_ = lean_string_push(v_s_x27_517_, v_c_496_);
v___x_519_ = lean_box_uint32(v_c_496_);
v_prev_x3f_520_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_prev_x3f_520_, 0, v___x_519_);
v___x_521_ = 48;
v___x_522_ = lean_uint32_dec_le(v___x_521_, v_c_496_);
if (v___x_522_ == 0)
{
v___y_509_ = v_prev_x3f_520_;
v___y_510_ = v_s_x27_518_;
v___y_511_ = v___x_522_;
goto v___jp_508_;
}
else
{
uint32_t v___x_523_; uint8_t v___x_524_; 
v___x_523_ = 57;
v___x_524_ = lean_uint32_dec_le(v_c_496_, v___x_523_);
v___y_509_ = v_prev_x3f_520_;
v___y_510_ = v_s_x27_518_;
v___y_511_ = v___x_524_;
goto v___jp_508_;
}
}
v___jp_525_:
{
uint8_t v___x_527_; 
v___x_527_ = l___private_Lean_DocString_Markdown_0__Lean_Doc_markerPrefixSpecial(v_snd_490_, v_c_496_, v___y_526_);
lean_dec(v___y_526_);
lean_dec(v_snd_490_);
if (v___x_527_ == 0)
{
v_s_x27_517_ = v_fst_485_;
goto v___jp_516_;
}
else
{
uint32_t v___x_528_; lean_object* v_s_x27_529_; 
v___x_528_ = 92;
v_s_x27_529_ = lean_string_push(v_fst_485_, v___x_528_);
v_s_x27_517_ = v_s_x27_529_;
goto v___jp_516_;
}
}
}
else
{
lean_object* v___x_536_; 
if (v_isShared_493_ == 0)
{
v___x_536_ = v___x_492_;
goto v_reusejp_535_;
}
else
{
lean_object* v_reuseFailAlloc_540_; 
v_reuseFailAlloc_540_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v_reuseFailAlloc_540_, 0, v_fst_489_);
lean_ctor_set(v_reuseFailAlloc_540_, 1, v_snd_490_);
v___x_536_ = v_reuseFailAlloc_540_;
goto v_reusejp_535_;
}
v_reusejp_535_:
{
lean_object* v___x_538_; 
if (v_isShared_488_ == 0)
{
lean_ctor_set(v___x_487_, 1, v___x_536_);
v___x_538_ = v___x_487_;
goto v_reusejp_537_;
}
else
{
lean_object* v_reuseFailAlloc_539_; 
v_reuseFailAlloc_539_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v_reuseFailAlloc_539_, 0, v_fst_485_);
lean_ctor_set(v_reuseFailAlloc_539_, 1, v___x_536_);
v___x_538_ = v_reuseFailAlloc_539_;
goto v_reusejp_537_;
}
v_reusejp_537_:
{
return v___x_538_;
}
}
}
}
}
}
}
LEAN_EXPORT lean_object* l___private_Init_While_0__Lean_Loop_forIn_loop___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_escape_spec__0___boxed(lean_object* v_s_543_, lean_object* v_b_544_){
_start:
{
lean_object* v_res_545_; 
v_res_545_ = l___private_Init_While_0__Lean_Loop_forIn_loop___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_escape_spec__0(v_s_543_, v_b_544_);
lean_dec_ref(v_s_543_);
return v_res_545_;
}
}
LEAN_EXPORT lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_escape(lean_object* v_s_552_){
_start:
{
lean_object* v___x_553_; lean_object* v___x_554_; lean_object* v_snd_555_; lean_object* v_fst_556_; lean_object* v_fst_557_; lean_object* v___x_559_; uint8_t v_isShared_560_; uint8_t v_isSharedCheck_566_; 
v___x_553_ = ((lean_object*)(l___private_Lean_DocString_Markdown_0__Lean_Doc_escape___closed__1));
v___x_554_ = l___private_Init_While_0__Lean_Loop_forIn_loop___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_escape_spec__0(v_s_552_, v___x_553_);
v_snd_555_ = lean_ctor_get(v___x_554_, 1);
lean_inc(v_snd_555_);
v_fst_556_ = lean_ctor_get(v___x_554_, 0);
lean_inc(v_fst_556_);
lean_dec_ref(v___x_554_);
v_fst_557_ = lean_ctor_get(v_snd_555_, 0);
v_isSharedCheck_566_ = !lean_is_exclusive(v_snd_555_);
if (v_isSharedCheck_566_ == 0)
{
lean_object* v_unused_567_; 
v_unused_567_ = lean_ctor_get(v_snd_555_, 1);
lean_dec(v_unused_567_);
v___x_559_ = v_snd_555_;
v_isShared_560_ = v_isSharedCheck_566_;
goto v_resetjp_558_;
}
else
{
lean_inc(v_fst_557_);
lean_dec(v_snd_555_);
v___x_559_ = lean_box(0);
v_isShared_560_ = v_isSharedCheck_566_;
goto v_resetjp_558_;
}
v_resetjp_558_:
{
lean_object* v___x_562_; 
if (v_isShared_560_ == 0)
{
lean_ctor_set(v___x_559_, 1, v_fst_557_);
lean_ctor_set(v___x_559_, 0, v_fst_556_);
v___x_562_ = v___x_559_;
goto v_reusejp_561_;
}
else
{
lean_object* v_reuseFailAlloc_565_; 
v_reuseFailAlloc_565_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v_reuseFailAlloc_565_, 0, v_fst_556_);
lean_ctor_set(v_reuseFailAlloc_565_, 1, v_fst_557_);
v___x_562_ = v_reuseFailAlloc_565_;
goto v_reusejp_561_;
}
v_reusejp_561_:
{
lean_object* v___x_563_; lean_object* v_fst_564_; 
v___x_563_ = l___private_Init_While_0__Lean_Loop_forIn_loop___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_escape_spec__1(v_s_552_, v___x_562_);
v_fst_564_ = lean_ctor_get(v___x_563_, 0);
lean_inc(v_fst_564_);
lean_dec_ref(v___x_563_);
return v_fst_564_;
}
}
}
}
LEAN_EXPORT lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_escape___boxed(lean_object* v_s_568_){
_start:
{
lean_object* v_res_569_; 
v_res_569_ = l___private_Lean_DocString_Markdown_0__Lean_Doc_escape(v_s_568_);
lean_dec_ref(v_s_568_);
return v_res_569_;
}
}
LEAN_EXPORT lean_object* l___private_Init_While_0__Lean_Loop_forIn_loop___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_longestBacktickRun_spec__0(lean_object* v_str_570_, lean_object* v_b_571_){
_start:
{
lean_object* v_snd_572_; lean_object* v_fst_573_; lean_object* v___x_575_; uint8_t v_isShared_576_; uint8_t v_isSharedCheck_615_; 
v_snd_572_ = lean_ctor_get(v_b_571_, 1);
v_fst_573_ = lean_ctor_get(v_b_571_, 0);
v_isSharedCheck_615_ = !lean_is_exclusive(v_b_571_);
if (v_isSharedCheck_615_ == 0)
{
v___x_575_ = v_b_571_;
v_isShared_576_ = v_isSharedCheck_615_;
goto v_resetjp_574_;
}
else
{
lean_inc(v_snd_572_);
lean_inc(v_fst_573_);
lean_dec(v_b_571_);
v___x_575_ = lean_box(0);
v_isShared_576_ = v_isSharedCheck_615_;
goto v_resetjp_574_;
}
v_resetjp_574_:
{
lean_object* v_fst_577_; lean_object* v_snd_578_; lean_object* v___x_580_; uint8_t v_isShared_581_; uint8_t v_isSharedCheck_614_; 
v_fst_577_ = lean_ctor_get(v_snd_572_, 0);
v_snd_578_ = lean_ctor_get(v_snd_572_, 1);
v_isSharedCheck_614_ = !lean_is_exclusive(v_snd_572_);
if (v_isSharedCheck_614_ == 0)
{
v___x_580_ = v_snd_572_;
v_isShared_581_ = v_isSharedCheck_614_;
goto v_resetjp_579_;
}
else
{
lean_inc(v_snd_578_);
lean_inc(v_fst_577_);
lean_dec(v_snd_572_);
v___x_580_ = lean_box(0);
v_isShared_581_ = v_isSharedCheck_614_;
goto v_resetjp_579_;
}
v_resetjp_579_:
{
lean_object* v___x_582_; uint8_t v___x_583_; 
v___x_582_ = lean_string_utf8_byte_size(v_str_570_);
v___x_583_ = lean_nat_dec_eq(v_snd_578_, v___x_582_);
if (v___x_583_ == 0)
{
uint32_t v_c_584_; lean_object* v_iter_585_; uint32_t v___x_586_; uint8_t v___x_587_; 
v_c_584_ = lean_string_utf8_get_fast(v_str_570_, v_snd_578_);
v_iter_585_ = lean_string_utf8_next_fast(v_str_570_, v_snd_578_);
lean_dec(v_snd_578_);
v___x_586_ = 96;
v___x_587_ = lean_uint32_dec_eq(v_c_584_, v___x_586_);
if (v___x_587_ == 0)
{
lean_object* v_longest_588_; lean_object* v___y_590_; uint8_t v___x_598_; 
v_longest_588_ = lean_unsigned_to_nat(0u);
v___x_598_ = lean_nat_dec_le(v_fst_573_, v_fst_577_);
if (v___x_598_ == 0)
{
lean_dec(v_fst_577_);
v___y_590_ = v_fst_573_;
goto v___jp_589_;
}
else
{
lean_dec(v_fst_573_);
v___y_590_ = v_fst_577_;
goto v___jp_589_;
}
v___jp_589_:
{
lean_object* v___x_592_; 
if (v_isShared_581_ == 0)
{
lean_ctor_set(v___x_580_, 1, v_iter_585_);
lean_ctor_set(v___x_580_, 0, v_longest_588_);
v___x_592_ = v___x_580_;
goto v_reusejp_591_;
}
else
{
lean_object* v_reuseFailAlloc_597_; 
v_reuseFailAlloc_597_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v_reuseFailAlloc_597_, 0, v_longest_588_);
lean_ctor_set(v_reuseFailAlloc_597_, 1, v_iter_585_);
v___x_592_ = v_reuseFailAlloc_597_;
goto v_reusejp_591_;
}
v_reusejp_591_:
{
lean_object* v___x_594_; 
if (v_isShared_576_ == 0)
{
lean_ctor_set(v___x_575_, 1, v___x_592_);
lean_ctor_set(v___x_575_, 0, v___y_590_);
v___x_594_ = v___x_575_;
goto v_reusejp_593_;
}
else
{
lean_object* v_reuseFailAlloc_596_; 
v_reuseFailAlloc_596_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v_reuseFailAlloc_596_, 0, v___y_590_);
lean_ctor_set(v_reuseFailAlloc_596_, 1, v___x_592_);
v___x_594_ = v_reuseFailAlloc_596_;
goto v_reusejp_593_;
}
v_reusejp_593_:
{
v_b_571_ = v___x_594_;
goto _start;
}
}
}
}
else
{
lean_object* v___x_599_; lean_object* v_current_600_; lean_object* v___x_602_; 
v___x_599_ = lean_unsigned_to_nat(1u);
v_current_600_ = lean_nat_add(v_fst_577_, v___x_599_);
lean_dec(v_fst_577_);
if (v_isShared_581_ == 0)
{
lean_ctor_set(v___x_580_, 1, v_iter_585_);
lean_ctor_set(v___x_580_, 0, v_current_600_);
v___x_602_ = v___x_580_;
goto v_reusejp_601_;
}
else
{
lean_object* v_reuseFailAlloc_607_; 
v_reuseFailAlloc_607_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v_reuseFailAlloc_607_, 0, v_current_600_);
lean_ctor_set(v_reuseFailAlloc_607_, 1, v_iter_585_);
v___x_602_ = v_reuseFailAlloc_607_;
goto v_reusejp_601_;
}
v_reusejp_601_:
{
lean_object* v___x_604_; 
if (v_isShared_576_ == 0)
{
lean_ctor_set(v___x_575_, 1, v___x_602_);
v___x_604_ = v___x_575_;
goto v_reusejp_603_;
}
else
{
lean_object* v_reuseFailAlloc_606_; 
v_reuseFailAlloc_606_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v_reuseFailAlloc_606_, 0, v_fst_573_);
lean_ctor_set(v_reuseFailAlloc_606_, 1, v___x_602_);
v___x_604_ = v_reuseFailAlloc_606_;
goto v_reusejp_603_;
}
v_reusejp_603_:
{
v_b_571_ = v___x_604_;
goto _start;
}
}
}
}
else
{
lean_object* v___x_609_; 
if (v_isShared_581_ == 0)
{
v___x_609_ = v___x_580_;
goto v_reusejp_608_;
}
else
{
lean_object* v_reuseFailAlloc_613_; 
v_reuseFailAlloc_613_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v_reuseFailAlloc_613_, 0, v_fst_577_);
lean_ctor_set(v_reuseFailAlloc_613_, 1, v_snd_578_);
v___x_609_ = v_reuseFailAlloc_613_;
goto v_reusejp_608_;
}
v_reusejp_608_:
{
lean_object* v___x_611_; 
if (v_isShared_576_ == 0)
{
lean_ctor_set(v___x_575_, 1, v___x_609_);
v___x_611_ = v___x_575_;
goto v_reusejp_610_;
}
else
{
lean_object* v_reuseFailAlloc_612_; 
v_reuseFailAlloc_612_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v_reuseFailAlloc_612_, 0, v_fst_573_);
lean_ctor_set(v_reuseFailAlloc_612_, 1, v___x_609_);
v___x_611_ = v_reuseFailAlloc_612_;
goto v_reusejp_610_;
}
v_reusejp_610_:
{
return v___x_611_;
}
}
}
}
}
}
}
LEAN_EXPORT lean_object* l___private_Init_While_0__Lean_Loop_forIn_loop___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_longestBacktickRun_spec__0___boxed(lean_object* v_str_616_, lean_object* v_b_617_){
_start:
{
lean_object* v_res_618_; 
v_res_618_ = l___private_Init_While_0__Lean_Loop_forIn_loop___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_longestBacktickRun_spec__0(v_str_616_, v_b_617_);
lean_dec_ref(v_str_616_);
return v_res_618_;
}
}
LEAN_EXPORT lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_longestBacktickRun(lean_object* v_str_624_){
_start:
{
lean_object* v___x_625_; lean_object* v___x_626_; lean_object* v_snd_627_; lean_object* v_fst_628_; lean_object* v_fst_629_; uint8_t v___x_630_; 
v___x_625_ = ((lean_object*)(l___private_Lean_DocString_Markdown_0__Lean_Doc_longestBacktickRun___closed__1));
v___x_626_ = l___private_Init_While_0__Lean_Loop_forIn_loop___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_longestBacktickRun_spec__0(v_str_624_, v___x_625_);
v_snd_627_ = lean_ctor_get(v___x_626_, 1);
lean_inc(v_snd_627_);
v_fst_628_ = lean_ctor_get(v___x_626_, 0);
lean_inc(v_fst_628_);
lean_dec_ref(v___x_626_);
v_fst_629_ = lean_ctor_get(v_snd_627_, 0);
lean_inc(v_fst_629_);
lean_dec(v_snd_627_);
v___x_630_ = lean_nat_dec_le(v_fst_628_, v_fst_629_);
if (v___x_630_ == 0)
{
lean_dec(v_fst_629_);
return v_fst_628_;
}
else
{
lean_dec(v_fst_628_);
return v_fst_629_;
}
}
}
LEAN_EXPORT lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_longestBacktickRun___boxed(lean_object* v_str_631_){
_start:
{
lean_object* v_res_632_; 
v_res_632_ = l___private_Lean_DocString_Markdown_0__Lean_Doc_longestBacktickRun(v_str_631_);
lean_dec_ref(v_str_631_);
return v_res_632_;
}
}
LEAN_EXPORT lean_object* l___private_Init_Data_Nat_Basic_0__Nat_repeatTR_loop___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_fenceFor_spec__0(lean_object* v_x_633_, lean_object* v_x_634_){
_start:
{
lean_object* v_zero_635_; uint8_t v_isZero_636_; 
v_zero_635_ = lean_unsigned_to_nat(0u);
v_isZero_636_ = lean_nat_dec_eq(v_x_633_, v_zero_635_);
if (v_isZero_636_ == 1)
{
lean_dec(v_x_633_);
return v_x_634_;
}
else
{
uint32_t v___x_637_; lean_object* v_one_638_; lean_object* v_n_639_; lean_object* v___x_640_; 
v___x_637_ = 96;
v_one_638_ = lean_unsigned_to_nat(1u);
v_n_639_ = lean_nat_sub(v_x_633_, v_one_638_);
lean_dec(v_x_633_);
v___x_640_ = lean_string_push(v_x_634_, v___x_637_);
v_x_633_ = v_n_639_;
v_x_634_ = v___x_640_;
goto _start;
}
}
}
LEAN_EXPORT lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_fenceFor(lean_object* v_atLeast_642_, lean_object* v_str_643_){
_start:
{
lean_object* v___x_644_; lean_object* v___y_646_; lean_object* v___x_650_; uint8_t v___x_651_; 
v___x_644_ = ((lean_object*)(l___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Lean_Doc_joinBlocks_spec__0___closed__0));
v___x_650_ = l___private_Lean_DocString_Markdown_0__Lean_Doc_longestBacktickRun(v_str_643_);
v___x_651_ = lean_nat_dec_le(v_atLeast_642_, v___x_650_);
if (v___x_651_ == 0)
{
lean_dec(v___x_650_);
v___y_646_ = v_atLeast_642_;
goto v___jp_645_;
}
else
{
lean_dec(v_atLeast_642_);
v___y_646_ = v___x_650_;
goto v___jp_645_;
}
v___jp_645_:
{
lean_object* v___x_647_; lean_object* v___x_648_; lean_object* v___x_649_; 
v___x_647_ = lean_unsigned_to_nat(1u);
v___x_648_ = lean_nat_add(v___y_646_, v___x_647_);
lean_dec(v___y_646_);
v___x_649_ = l___private_Init_Data_Nat_Basic_0__Nat_repeatTR_loop___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_fenceFor_spec__0(v___x_648_, v___x_644_);
return v___x_649_;
}
}
}
LEAN_EXPORT lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_fenceFor___boxed(lean_object* v_atLeast_652_, lean_object* v_str_653_){
_start:
{
lean_object* v_res_654_; 
v_res_654_ = l___private_Lean_DocString_Markdown_0__Lean_Doc_fenceFor(v_atLeast_652_, v_str_653_);
lean_dec_ref(v_str_653_);
return v_res_654_;
}
}
LEAN_EXPORT lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_quoteCode(lean_object* v_str_656_){
_start:
{
lean_object* v___x_657_; lean_object* v_backticks_658_; lean_object* v___y_660_; lean_object* v___x_674_; lean_object* v___x_675_; lean_object* v___x_676_; uint8_t v___x_677_; 
v___x_657_ = lean_unsigned_to_nat(0u);
v_backticks_658_ = l___private_Lean_DocString_Markdown_0__Lean_Doc_fenceFor(v___x_657_, v_str_656_);
v___x_674_ = ((lean_object*)(l___private_Lean_DocString_Markdown_0__Lean_Doc_glueInlineBoundary___closed__0));
v___x_675_ = lean_string_utf8_byte_size(v_str_656_);
v___x_676_ = lean_obj_once(&l___private_Lean_DocString_Markdown_0__Lean_Doc_glueInlineBoundary___closed__1, &l___private_Lean_DocString_Markdown_0__Lean_Doc_glueInlineBoundary___closed__1_once, _init_l___private_Lean_DocString_Markdown_0__Lean_Doc_glueInlineBoundary___closed__1);
v___x_677_ = lean_nat_dec_le(v___x_676_, v___x_675_);
if (v___x_677_ == 0)
{
goto v___jp_667_;
}
else
{
uint8_t v___x_678_; 
v___x_678_ = lean_string_memcmp(v_str_656_, v___x_674_, v___x_657_, v___x_657_, v___x_676_);
if (v___x_678_ == 0)
{
goto v___jp_667_;
}
else
{
goto v___jp_663_;
}
}
v___jp_659_:
{
lean_object* v___x_661_; lean_object* v___x_662_; 
lean_inc_ref(v_backticks_658_);
v___x_661_ = lean_string_append(v_backticks_658_, v___y_660_);
lean_dec_ref(v___y_660_);
v___x_662_ = lean_string_append(v___x_661_, v_backticks_658_);
lean_dec_ref(v_backticks_658_);
return v___x_662_;
}
v___jp_663_:
{
lean_object* v___x_664_; lean_object* v___x_665_; lean_object* v___x_666_; 
v___x_664_ = ((lean_object*)(l___private_Lean_DocString_Markdown_0__Lean_Doc_quoteCode___closed__0));
v___x_665_ = lean_string_append(v___x_664_, v_str_656_);
lean_dec_ref(v_str_656_);
v___x_666_ = lean_string_append(v___x_665_, v___x_664_);
v___y_660_ = v___x_666_;
goto v___jp_659_;
}
v___jp_667_:
{
lean_object* v___x_668_; lean_object* v___x_669_; lean_object* v___x_670_; uint8_t v___x_671_; 
v___x_668_ = ((lean_object*)(l___private_Lean_DocString_Markdown_0__Lean_Doc_glueInlineBoundary___closed__0));
v___x_669_ = lean_string_utf8_byte_size(v_str_656_);
v___x_670_ = lean_obj_once(&l___private_Lean_DocString_Markdown_0__Lean_Doc_glueInlineBoundary___closed__1, &l___private_Lean_DocString_Markdown_0__Lean_Doc_glueInlineBoundary___closed__1_once, _init_l___private_Lean_DocString_Markdown_0__Lean_Doc_glueInlineBoundary___closed__1);
v___x_671_ = lean_nat_dec_le(v___x_670_, v___x_669_);
if (v___x_671_ == 0)
{
v___y_660_ = v_str_656_;
goto v___jp_659_;
}
else
{
lean_object* v___x_672_; uint8_t v___x_673_; 
v___x_672_ = lean_nat_sub(v___x_669_, v___x_670_);
v___x_673_ = lean_string_memcmp(v_str_656_, v___x_668_, v___x_672_, v___x_657_, v___x_670_);
lean_dec(v___x_672_);
if (v___x_673_ == 0)
{
v___y_660_ = v_str_656_;
goto v___jp_659_;
}
else
{
goto v___jp_663_;
}
}
}
}
}
LEAN_EXPORT lean_object* l_String_Slice_splitToSubslice___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_splitNewlines_spec__0(lean_object* v_s_681_){
_start:
{
lean_object* v___x_682_; 
v___x_682_ = ((lean_object*)(l_String_Slice_splitToSubslice___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_splitNewlines_spec__0___closed__0));
return v___x_682_;
}
}
LEAN_EXPORT lean_object* l_String_Slice_splitToSubslice___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_splitNewlines_spec__0___boxed(lean_object* v_s_683_){
_start:
{
lean_object* v_res_684_; 
v_res_684_ = l_String_Slice_splitToSubslice___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_splitNewlines_spec__0(v_s_683_);
lean_dec_ref(v_s_683_);
return v_res_684_;
}
}
LEAN_EXPORT lean_object* l___private_Init_WFExtrinsicFix_0__WellFounded_opaqueFix_u2082___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_splitNewlines_spec__1___redArg(lean_object* v_str_685_, lean_object* v___x_686_, lean_object* v___x_687_, lean_object* v_a_688_, lean_object* v_b_689_){
_start:
{
lean_object* v_it_691_; lean_object* v_startInclusive_692_; lean_object* v_endExclusive_693_; 
if (lean_obj_tag(v_a_688_) == 0)
{
lean_object* v_currPos_697_; lean_object* v_searcher_698_; lean_object* v___x_700_; uint8_t v_isShared_701_; uint8_t v_isSharedCheck_724_; 
v_currPos_697_ = lean_ctor_get(v_a_688_, 0);
v_searcher_698_ = lean_ctor_get(v_a_688_, 1);
v_isSharedCheck_724_ = !lean_is_exclusive(v_a_688_);
if (v_isSharedCheck_724_ == 0)
{
v___x_700_ = v_a_688_;
v_isShared_701_ = v_isSharedCheck_724_;
goto v_resetjp_699_;
}
else
{
lean_inc(v_searcher_698_);
lean_inc(v_currPos_697_);
lean_dec(v_a_688_);
v___x_700_ = lean_box(0);
v_isShared_701_ = v_isSharedCheck_724_;
goto v_resetjp_699_;
}
v_resetjp_699_:
{
lean_object* v_startInclusive_702_; lean_object* v_endExclusive_703_; lean_object* v___x_704_; uint8_t v___x_705_; 
v_startInclusive_702_ = lean_ctor_get(v___x_686_, 1);
v_endExclusive_703_ = lean_ctor_get(v___x_686_, 2);
v___x_704_ = lean_nat_sub(v_endExclusive_703_, v_startInclusive_702_);
v___x_705_ = lean_nat_dec_eq(v_searcher_698_, v___x_704_);
lean_dec(v___x_704_);
if (v___x_705_ == 0)
{
uint32_t v___x_706_; uint32_t v___x_707_; uint8_t v___x_708_; 
v___x_706_ = 10;
v___x_707_ = lean_string_utf8_get_fast(v_str_685_, v_searcher_698_);
v___x_708_ = lean_uint32_dec_eq(v___x_707_, v___x_706_);
if (v___x_708_ == 0)
{
lean_object* v___x_709_; lean_object* v___x_711_; 
v___x_709_ = lean_string_utf8_next_fast(v_str_685_, v_searcher_698_);
lean_dec(v_searcher_698_);
if (v_isShared_701_ == 0)
{
lean_ctor_set(v___x_700_, 1, v___x_709_);
v___x_711_ = v___x_700_;
goto v_reusejp_710_;
}
else
{
lean_object* v_reuseFailAlloc_713_; 
v_reuseFailAlloc_713_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v_reuseFailAlloc_713_, 0, v_currPos_697_);
lean_ctor_set(v_reuseFailAlloc_713_, 1, v___x_709_);
v___x_711_ = v_reuseFailAlloc_713_;
goto v_reusejp_710_;
}
v_reusejp_710_:
{
v_a_688_ = v___x_711_;
goto _start;
}
}
else
{
lean_object* v___x_714_; lean_object* v___x_715_; lean_object* v___x_716_; lean_object* v_slice_717_; lean_object* v_nextIt_719_; 
v___x_714_ = lean_string_utf8_next_fast(v_str_685_, v_searcher_698_);
v___x_715_ = lean_nat_sub(v___x_714_, v_searcher_698_);
v___x_716_ = lean_nat_add(v_searcher_698_, v___x_715_);
lean_dec(v___x_715_);
v_slice_717_ = l_String_Slice_subslice_x21(v___x_686_, v_currPos_697_, v_searcher_698_);
lean_inc(v___x_716_);
if (v_isShared_701_ == 0)
{
lean_ctor_set(v___x_700_, 1, v___x_716_);
lean_ctor_set(v___x_700_, 0, v___x_716_);
v_nextIt_719_ = v___x_700_;
goto v_reusejp_718_;
}
else
{
lean_object* v_reuseFailAlloc_722_; 
v_reuseFailAlloc_722_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v_reuseFailAlloc_722_, 0, v___x_716_);
lean_ctor_set(v_reuseFailAlloc_722_, 1, v___x_716_);
v_nextIt_719_ = v_reuseFailAlloc_722_;
goto v_reusejp_718_;
}
v_reusejp_718_:
{
lean_object* v_startInclusive_720_; lean_object* v_endExclusive_721_; 
v_startInclusive_720_ = lean_ctor_get(v_slice_717_, 0);
lean_inc(v_startInclusive_720_);
v_endExclusive_721_ = lean_ctor_get(v_slice_717_, 1);
lean_inc(v_endExclusive_721_);
lean_dec_ref(v_slice_717_);
v_it_691_ = v_nextIt_719_;
v_startInclusive_692_ = v_startInclusive_720_;
v_endExclusive_693_ = v_endExclusive_721_;
goto v___jp_690_;
}
}
}
else
{
lean_object* v___x_723_; 
lean_del_object(v___x_700_);
lean_dec(v_searcher_698_);
v___x_723_ = lean_box(1);
lean_inc(v___x_687_);
v_it_691_ = v___x_723_;
v_startInclusive_692_ = v_currPos_697_;
v_endExclusive_693_ = v___x_687_;
goto v___jp_690_;
}
}
}
else
{
lean_dec(v___x_687_);
return v_b_689_;
}
v___jp_690_:
{
lean_object* v___x_694_; lean_object* v___x_695_; 
v___x_694_ = lean_string_utf8_extract(v_str_685_, v_startInclusive_692_, v_endExclusive_693_);
lean_dec(v_endExclusive_693_);
lean_dec(v_startInclusive_692_);
v___x_695_ = lean_array_push(v_b_689_, v___x_694_);
v_a_688_ = v_it_691_;
v_b_689_ = v___x_695_;
goto _start;
}
}
}
LEAN_EXPORT lean_object* l___private_Init_WFExtrinsicFix_0__WellFounded_opaqueFix_u2082___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_splitNewlines_spec__1___redArg___boxed(lean_object* v_str_725_, lean_object* v___x_726_, lean_object* v___x_727_, lean_object* v_a_728_, lean_object* v_b_729_){
_start:
{
lean_object* v_res_730_; 
v_res_730_ = l___private_Init_WFExtrinsicFix_0__WellFounded_opaqueFix_u2082___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_splitNewlines_spec__1___redArg(v_str_725_, v___x_726_, v___x_727_, v_a_728_, v_b_729_);
lean_dec_ref(v___x_726_);
lean_dec_ref(v_str_725_);
return v_res_730_;
}
}
LEAN_EXPORT lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_splitNewlines(lean_object* v_str_731_){
_start:
{
lean_object* v___x_732_; lean_object* v___x_733_; lean_object* v___x_734_; lean_object* v___x_735_; lean_object* v___x_736_; lean_object* v___x_737_; 
v___x_732_ = lean_unsigned_to_nat(0u);
v___x_733_ = lean_string_utf8_byte_size(v_str_731_);
lean_inc_ref(v_str_731_);
v___x_734_ = lean_alloc_ctor(0, 3, 0);
lean_ctor_set(v___x_734_, 0, v_str_731_);
lean_ctor_set(v___x_734_, 1, v___x_732_);
lean_ctor_set(v___x_734_, 2, v___x_733_);
v___x_735_ = l_String_Slice_splitToSubslice___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_splitNewlines_spec__0(v___x_734_);
v___x_736_ = ((lean_object*)(l_Lean_Doc_joinBlocks___closed__0));
v___x_737_ = l___private_Init_WFExtrinsicFix_0__WellFounded_opaqueFix_u2082___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_splitNewlines_spec__1___redArg(v_str_731_, v___x_734_, v___x_733_, v___x_735_, v___x_736_);
lean_dec_ref(v___x_734_);
lean_dec_ref(v_str_731_);
return v___x_737_;
}
}
LEAN_EXPORT lean_object* l___private_Init_WFExtrinsicFix_0__WellFounded_opaqueFix_u2082___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_splitNewlines_spec__1(lean_object* v_str_738_, lean_object* v___x_739_, lean_object* v___x_740_, lean_object* v_inst_741_, lean_object* v_R_742_, lean_object* v_a_743_, lean_object* v_b_744_){
_start:
{
lean_object* v___x_745_; 
v___x_745_ = l___private_Init_WFExtrinsicFix_0__WellFounded_opaqueFix_u2082___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_splitNewlines_spec__1___redArg(v_str_738_, v___x_739_, v___x_740_, v_a_743_, v_b_744_);
return v___x_745_;
}
}
LEAN_EXPORT lean_object* l___private_Init_WFExtrinsicFix_0__WellFounded_opaqueFix_u2082___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_splitNewlines_spec__1___boxed(lean_object* v_str_746_, lean_object* v___x_747_, lean_object* v___x_748_, lean_object* v_inst_749_, lean_object* v_R_750_, lean_object* v_a_751_, lean_object* v_b_752_){
_start:
{
lean_object* v_res_753_; 
v_res_753_ = l___private_Init_WFExtrinsicFix_0__WellFounded_opaqueFix_u2082___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_splitNewlines_spec__1(v_str_746_, v___x_747_, v___x_748_, v_inst_749_, v_R_750_, v_a_751_, v_b_752_);
lean_dec_ref(v___x_747_);
lean_dec_ref(v_str_746_);
return v_res_753_;
}
}
LEAN_EXPORT lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_codeBlockLines(lean_object* v_str_754_){
_start:
{
lean_object* v___x_755_; lean_object* v_fence_756_; lean_object* v___y_758_; lean_object* v_body_764_; uint8_t v___y_766_; lean_object* v___x_768_; lean_object* v___x_769_; uint8_t v___x_770_; 
v___x_755_ = lean_unsigned_to_nat(2u);
v_fence_756_ = l___private_Lean_DocString_Markdown_0__Lean_Doc_fenceFor(v___x_755_, v_str_754_);
v_body_764_ = l___private_Lean_DocString_Markdown_0__Lean_Doc_splitNewlines(v_str_754_);
v___x_768_ = lean_unsigned_to_nat(0u);
v___x_769_ = lean_array_get_size(v_body_764_);
v___x_770_ = lean_nat_dec_lt(v___x_768_, v___x_769_);
if (v___x_770_ == 0)
{
v___y_766_ = v___x_770_;
goto v___jp_765_;
}
else
{
lean_object* v___x_771_; lean_object* v___x_772_; lean_object* v___x_773_; lean_object* v___x_774_; lean_object* v___x_775_; uint8_t v___x_776_; 
v___x_771_ = ((lean_object*)(l___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Lean_Doc_joinBlocks_spec__0___closed__0));
v___x_772_ = lean_unsigned_to_nat(1u);
v___x_773_ = lean_nat_sub(v___x_769_, v___x_772_);
v___x_774_ = lean_array_get(v___x_771_, v_body_764_, v___x_773_);
lean_dec(v___x_773_);
v___x_775_ = lean_string_utf8_byte_size(v___x_774_);
lean_dec(v___x_774_);
v___x_776_ = lean_nat_dec_eq(v___x_775_, v___x_768_);
v___y_766_ = v___x_776_;
goto v___jp_765_;
}
v___jp_757_:
{
lean_object* v___x_759_; lean_object* v___x_760_; lean_object* v___x_761_; lean_object* v___x_762_; lean_object* v___x_763_; 
v___x_759_ = lean_unsigned_to_nat(1u);
v___x_760_ = lean_mk_empty_array_with_capacity(v___x_759_);
v___x_761_ = lean_array_push(v___x_760_, v_fence_756_);
lean_inc_ref(v___x_761_);
v___x_762_ = l_Array_append___redArg(v___x_761_, v___y_758_);
lean_dec_ref(v___y_758_);
v___x_763_ = l_Array_append___redArg(v___x_762_, v___x_761_);
lean_dec_ref(v___x_761_);
return v___x_763_;
}
v___jp_765_:
{
if (v___y_766_ == 0)
{
v___y_758_ = v_body_764_;
goto v___jp_757_;
}
else
{
lean_object* v___x_767_; 
v___x_767_ = lean_array_pop(v_body_764_);
v___y_758_ = v___x_767_;
goto v___jp_757_;
}
}
}
}
LEAN_EXPORT lean_object* l_String_Slice_Pos_skipWhile___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_trimLeft_go_spec__0(lean_object* v_s_777_, lean_object* v_pos_778_){
_start:
{
lean_object* v_str_779_; lean_object* v_startInclusive_780_; lean_object* v_endExclusive_781_; lean_object* v___x_782_; uint8_t v___y_790_; lean_object* v___x_791_; lean_object* v___x_792_; uint8_t v___x_793_; 
v_str_779_ = lean_ctor_get(v_s_777_, 0);
v_startInclusive_780_ = lean_ctor_get(v_s_777_, 1);
v_endExclusive_781_ = lean_ctor_get(v_s_777_, 2);
v___x_782_ = lean_nat_add(v_startInclusive_780_, v_pos_778_);
v___x_791_ = lean_unsigned_to_nat(0u);
v___x_792_ = lean_nat_sub(v_endExclusive_781_, v___x_782_);
v___x_793_ = lean_nat_dec_eq(v___x_791_, v___x_792_);
lean_dec(v___x_792_);
if (v___x_793_ == 0)
{
uint32_t v___x_794_; uint8_t v___y_796_; uint32_t v___x_801_; uint8_t v___x_802_; 
v___x_794_ = lean_string_utf8_get_fast(v_str_779_, v___x_782_);
v___x_801_ = 32;
v___x_802_ = lean_uint32_dec_eq(v___x_794_, v___x_801_);
if (v___x_802_ == 0)
{
uint32_t v___x_803_; uint8_t v___x_804_; 
v___x_803_ = 9;
v___x_804_ = lean_uint32_dec_eq(v___x_794_, v___x_803_);
v___y_796_ = v___x_804_;
goto v___jp_795_;
}
else
{
v___y_796_ = v___x_802_;
goto v___jp_795_;
}
v___jp_795_:
{
if (v___y_796_ == 0)
{
uint32_t v___x_797_; uint8_t v___x_798_; 
v___x_797_ = 13;
v___x_798_ = lean_uint32_dec_eq(v___x_794_, v___x_797_);
if (v___x_798_ == 0)
{
uint32_t v___x_799_; uint8_t v___x_800_; 
v___x_799_ = 10;
v___x_800_ = lean_uint32_dec_eq(v___x_794_, v___x_799_);
v___y_790_ = v___x_800_;
goto v___jp_789_;
}
else
{
v___y_790_ = v___x_798_;
goto v___jp_789_;
}
}
else
{
goto v___jp_783_;
}
}
}
else
{
lean_dec(v___x_782_);
return v_pos_778_;
}
v___jp_783_:
{
lean_object* v___x_784_; lean_object* v___x_785_; lean_object* v___x_786_; uint8_t v___x_787_; 
v___x_784_ = lean_string_utf8_next_fast(v_str_779_, v___x_782_);
v___x_785_ = lean_nat_sub(v___x_784_, v___x_782_);
lean_dec(v___x_782_);
v___x_786_ = lean_nat_add(v_pos_778_, v___x_785_);
lean_dec(v___x_785_);
v___x_787_ = lean_nat_dec_lt(v_pos_778_, v___x_786_);
if (v___x_787_ == 0)
{
lean_dec(v___x_786_);
return v_pos_778_;
}
else
{
lean_dec(v_pos_778_);
v_pos_778_ = v___x_786_;
goto _start;
}
}
v___jp_789_:
{
if (v___y_790_ == 0)
{
lean_dec(v___x_782_);
return v_pos_778_;
}
else
{
goto v___jp_783_;
}
}
}
}
LEAN_EXPORT lean_object* l_String_Slice_Pos_skipWhile___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_trimLeft_go_spec__0___boxed(lean_object* v_s_805_, lean_object* v_pos_806_){
_start:
{
lean_object* v_res_807_; 
v_res_807_ = l_String_Slice_Pos_skipWhile___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_trimLeft_go_spec__0(v_s_805_, v_pos_806_);
lean_dec_ref(v_s_805_);
return v_res_807_;
}
}
static lean_object* _init_l___private_Lean_DocString_Markdown_0__Lean_Doc_trimLeft_go___redArg___closed__0(void){
_start:
{
lean_object* v___x_808_; 
v___x_808_ = l_Lean_Doc_Inline_empty(lean_box(0));
return v___x_808_;
}
}
static lean_object* _init_l___private_Lean_DocString_Markdown_0__Lean_Doc_trimLeft_go___redArg___closed__1(void){
_start:
{
lean_object* v___x_809_; lean_object* v___x_810_; lean_object* v___x_811_; 
v___x_809_ = lean_obj_once(&l___private_Lean_DocString_Markdown_0__Lean_Doc_trimLeft_go___redArg___closed__0, &l___private_Lean_DocString_Markdown_0__Lean_Doc_trimLeft_go___redArg___closed__0_once, _init_l___private_Lean_DocString_Markdown_0__Lean_Doc_trimLeft_go___redArg___closed__0);
v___x_810_ = ((lean_object*)(l___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Lean_Doc_joinBlocks_spec__0___closed__0));
v___x_811_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v___x_811_, 0, v___x_810_);
lean_ctor_set(v___x_811_, 1, v___x_809_);
return v___x_811_;
}
}
LEAN_EXPORT lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_trimLeft_go___redArg(lean_object* v_a_812_){
_start:
{
if (lean_obj_tag(v_a_812_) == 0)
{
lean_object* v___x_813_; 
v___x_813_ = lean_obj_once(&l___private_Lean_DocString_Markdown_0__Lean_Doc_trimLeft_go___redArg___closed__1, &l___private_Lean_DocString_Markdown_0__Lean_Doc_trimLeft_go___redArg___closed__1_once, _init_l___private_Lean_DocString_Markdown_0__Lean_Doc_trimLeft_go___redArg___closed__1);
return v___x_813_;
}
else
{
lean_object* v_head_814_; 
v_head_814_ = lean_ctor_get(v_a_812_, 0);
lean_inc(v_head_814_);
switch(lean_obj_tag(v_head_814_))
{
case 0:
{
lean_object* v_tail_815_; lean_object* v___x_817_; uint8_t v_isShared_818_; uint8_t v_isSharedCheck_861_; 
v_tail_815_ = lean_ctor_get(v_a_812_, 1);
v_isSharedCheck_861_ = !lean_is_exclusive(v_a_812_);
if (v_isSharedCheck_861_ == 0)
{
lean_object* v_unused_862_; 
v_unused_862_ = lean_ctor_get(v_a_812_, 0);
lean_dec(v_unused_862_);
v___x_817_ = v_a_812_;
v_isShared_818_ = v_isSharedCheck_861_;
goto v_resetjp_816_;
}
else
{
lean_inc(v_tail_815_);
lean_dec(v_a_812_);
v___x_817_ = lean_box(0);
v_isShared_818_ = v_isSharedCheck_861_;
goto v_resetjp_816_;
}
v_resetjp_816_:
{
lean_object* v_string_819_; lean_object* v___x_821_; uint8_t v_isShared_822_; uint8_t v_isSharedCheck_860_; 
v_string_819_ = lean_ctor_get(v_head_814_, 0);
v_isSharedCheck_860_ = !lean_is_exclusive(v_head_814_);
if (v_isSharedCheck_860_ == 0)
{
v___x_821_ = v_head_814_;
v_isShared_822_ = v_isSharedCheck_860_;
goto v_resetjp_820_;
}
else
{
lean_inc(v_string_819_);
lean_dec(v_head_814_);
v___x_821_ = lean_box(0);
v_isShared_822_ = v_isSharedCheck_860_;
goto v_resetjp_820_;
}
v_resetjp_820_:
{
lean_object* v___x_823_; lean_object* v___x_824_; lean_object* v___x_825_; lean_object* v___x_826_; uint8_t v___x_827_; 
v___x_823_ = lean_unsigned_to_nat(0u);
v___x_824_ = lean_string_utf8_byte_size(v_string_819_);
lean_inc_ref(v_string_819_);
v___x_825_ = lean_alloc_ctor(0, 3, 0);
lean_ctor_set(v___x_825_, 0, v_string_819_);
lean_ctor_set(v___x_825_, 1, v___x_823_);
lean_ctor_set(v___x_825_, 2, v___x_824_);
v___x_826_ = l_String_Slice_Pos_skipWhile___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_trimLeft_go_spec__0(v___x_825_, v___x_823_);
v___x_827_ = lean_nat_dec_eq(v___x_826_, v___x_824_);
if (v___x_827_ == 0)
{
lean_object* v_s1_828_; lean_object* v___x_829_; lean_object* v___x_830_; lean_object* v_s2_831_; lean_object* v___x_833_; 
v_s1_828_ = lean_string_utf8_extract(v_string_819_, v___x_823_, v___x_826_);
lean_dec(v___x_826_);
v___x_829_ = lean_string_length(v_s1_828_);
v___x_830_ = l_String_Slice_Pos_nextn(v___x_825_, v___x_823_, v___x_829_);
lean_dec_ref(v___x_825_);
v_s2_831_ = lean_string_utf8_extract(v_string_819_, v___x_830_, v___x_824_);
lean_dec(v___x_830_);
lean_dec_ref(v_string_819_);
if (v_isShared_822_ == 0)
{
lean_ctor_set(v___x_821_, 0, v_s2_831_);
v___x_833_ = v___x_821_;
goto v_reusejp_832_;
}
else
{
lean_object* v_reuseFailAlloc_848_; 
v_reuseFailAlloc_848_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_848_, 0, v_s2_831_);
v___x_833_ = v_reuseFailAlloc_848_;
goto v_reusejp_832_;
}
v_reusejp_832_:
{
lean_object* v___x_834_; lean_object* v___x_835_; uint8_t v___x_836_; 
v___x_834_ = lean_array_mk(v_tail_815_);
v___x_835_ = lean_array_get_size(v___x_834_);
v___x_836_ = lean_nat_dec_eq(v___x_835_, v___x_823_);
if (v___x_836_ == 0)
{
lean_object* v___x_837_; lean_object* v___x_838_; lean_object* v___x_839_; lean_object* v___x_840_; lean_object* v___x_841_; lean_object* v___x_843_; 
v___x_837_ = lean_unsigned_to_nat(1u);
v___x_838_ = lean_mk_empty_array_with_capacity(v___x_837_);
v___x_839_ = lean_array_push(v___x_838_, v___x_833_);
v___x_840_ = l_Array_append___redArg(v___x_839_, v___x_834_);
lean_dec_ref(v___x_834_);
v___x_841_ = lean_alloc_ctor(9, 1, 0);
lean_ctor_set(v___x_841_, 0, v___x_840_);
if (v_isShared_818_ == 0)
{
lean_ctor_set_tag(v___x_817_, 0);
lean_ctor_set(v___x_817_, 1, v___x_841_);
lean_ctor_set(v___x_817_, 0, v_s1_828_);
v___x_843_ = v___x_817_;
goto v_reusejp_842_;
}
else
{
lean_object* v_reuseFailAlloc_844_; 
v_reuseFailAlloc_844_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v_reuseFailAlloc_844_, 0, v_s1_828_);
lean_ctor_set(v_reuseFailAlloc_844_, 1, v___x_841_);
v___x_843_ = v_reuseFailAlloc_844_;
goto v_reusejp_842_;
}
v_reusejp_842_:
{
return v___x_843_;
}
}
else
{
lean_object* v___x_846_; 
lean_dec_ref(v___x_834_);
if (v_isShared_818_ == 0)
{
lean_ctor_set_tag(v___x_817_, 0);
lean_ctor_set(v___x_817_, 1, v___x_833_);
lean_ctor_set(v___x_817_, 0, v_s1_828_);
v___x_846_ = v___x_817_;
goto v_reusejp_845_;
}
else
{
lean_object* v_reuseFailAlloc_847_; 
v_reuseFailAlloc_847_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v_reuseFailAlloc_847_, 0, v_s1_828_);
lean_ctor_set(v_reuseFailAlloc_847_, 1, v___x_833_);
v___x_846_ = v_reuseFailAlloc_847_;
goto v_reusejp_845_;
}
v_reusejp_845_:
{
return v___x_846_;
}
}
}
}
else
{
lean_object* v___x_849_; lean_object* v_fst_850_; lean_object* v_snd_851_; lean_object* v___x_853_; uint8_t v_isShared_854_; uint8_t v_isSharedCheck_859_; 
lean_dec(v___x_826_);
lean_dec_ref(v___x_825_);
lean_del_object(v___x_821_);
lean_del_object(v___x_817_);
v___x_849_ = l___private_Lean_DocString_Markdown_0__Lean_Doc_trimLeft_go___redArg(v_tail_815_);
v_fst_850_ = lean_ctor_get(v___x_849_, 0);
v_snd_851_ = lean_ctor_get(v___x_849_, 1);
v_isSharedCheck_859_ = !lean_is_exclusive(v___x_849_);
if (v_isSharedCheck_859_ == 0)
{
v___x_853_ = v___x_849_;
v_isShared_854_ = v_isSharedCheck_859_;
goto v_resetjp_852_;
}
else
{
lean_inc(v_snd_851_);
lean_inc(v_fst_850_);
lean_dec(v___x_849_);
v___x_853_ = lean_box(0);
v_isShared_854_ = v_isSharedCheck_859_;
goto v_resetjp_852_;
}
v_resetjp_852_:
{
lean_object* v___x_855_; lean_object* v___x_857_; 
v___x_855_ = lean_string_append(v_string_819_, v_fst_850_);
lean_dec(v_fst_850_);
if (v_isShared_854_ == 0)
{
lean_ctor_set(v___x_853_, 0, v___x_855_);
v___x_857_ = v___x_853_;
goto v_reusejp_856_;
}
else
{
lean_object* v_reuseFailAlloc_858_; 
v_reuseFailAlloc_858_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v_reuseFailAlloc_858_, 0, v___x_855_);
lean_ctor_set(v_reuseFailAlloc_858_, 1, v_snd_851_);
v___x_857_ = v_reuseFailAlloc_858_;
goto v_reusejp_856_;
}
v_reusejp_856_:
{
return v___x_857_;
}
}
}
}
}
}
case 9:
{
lean_object* v_tail_863_; lean_object* v_content_864_; lean_object* v___x_865_; lean_object* v___x_866_; 
v_tail_863_ = lean_ctor_get(v_a_812_, 1);
lean_inc(v_tail_863_);
lean_dec_ref(v_a_812_);
v_content_864_ = lean_ctor_get(v_head_814_, 0);
lean_inc_ref(v_content_864_);
lean_dec_ref(v_head_814_);
v___x_865_ = lean_array_to_list(v_content_864_);
v___x_866_ = l_List_appendTR___redArg(v___x_865_, v_tail_863_);
v_a_812_ = v___x_866_;
goto _start;
}
default: 
{
lean_object* v_tail_868_; lean_object* v___x_870_; uint8_t v_isShared_871_; uint8_t v_isSharedCheck_906_; 
v_tail_868_ = lean_ctor_get(v_a_812_, 1);
v_isSharedCheck_906_ = !lean_is_exclusive(v_a_812_);
if (v_isSharedCheck_906_ == 0)
{
lean_object* v_unused_907_; 
v_unused_907_ = lean_ctor_get(v_a_812_, 0);
lean_dec(v_unused_907_);
v___x_870_ = v_a_812_;
v_isShared_871_ = v_isSharedCheck_906_;
goto v_resetjp_869_;
}
else
{
lean_inc(v_tail_868_);
lean_dec(v_a_812_);
v___x_870_ = lean_box(0);
v_isShared_871_ = v_isSharedCheck_906_;
goto v_resetjp_869_;
}
v_resetjp_869_:
{
lean_object* v___x_872_; lean_object* v___x_873_; 
v___x_872_ = ((lean_object*)(l___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Lean_Doc_joinBlocks_spec__0___closed__0));
v___x_873_ = lean_array_mk(v_tail_868_);
if (lean_obj_tag(v_head_814_) == 9)
{
lean_object* v_content_874_; lean_object* v___x_875_; lean_object* v___x_876_; uint8_t v___x_877_; 
v_content_874_ = lean_ctor_get(v_head_814_, 0);
v___x_875_ = lean_array_get_size(v_content_874_);
v___x_876_ = lean_unsigned_to_nat(0u);
v___x_877_ = lean_nat_dec_eq(v___x_875_, v___x_876_);
if (v___x_877_ == 0)
{
lean_object* v___x_878_; uint8_t v___x_879_; 
v___x_878_ = lean_array_get_size(v___x_873_);
v___x_879_ = lean_nat_dec_eq(v___x_878_, v___x_876_);
if (v___x_879_ == 0)
{
lean_object* v___x_880_; lean_object* v___x_881_; lean_object* v___x_883_; 
lean_inc_ref(v_content_874_);
lean_dec_ref(v_head_814_);
v___x_880_ = l_Array_append___redArg(v_content_874_, v___x_873_);
lean_dec_ref(v___x_873_);
v___x_881_ = lean_alloc_ctor(9, 1, 0);
lean_ctor_set(v___x_881_, 0, v___x_880_);
if (v_isShared_871_ == 0)
{
lean_ctor_set_tag(v___x_870_, 0);
lean_ctor_set(v___x_870_, 1, v___x_881_);
lean_ctor_set(v___x_870_, 0, v___x_872_);
v___x_883_ = v___x_870_;
goto v_reusejp_882_;
}
else
{
lean_object* v_reuseFailAlloc_884_; 
v_reuseFailAlloc_884_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v_reuseFailAlloc_884_, 0, v___x_872_);
lean_ctor_set(v_reuseFailAlloc_884_, 1, v___x_881_);
v___x_883_ = v_reuseFailAlloc_884_;
goto v_reusejp_882_;
}
v_reusejp_882_:
{
return v___x_883_;
}
}
else
{
lean_object* v___x_886_; 
lean_dec_ref(v___x_873_);
if (v_isShared_871_ == 0)
{
lean_ctor_set_tag(v___x_870_, 0);
lean_ctor_set(v___x_870_, 1, v_head_814_);
lean_ctor_set(v___x_870_, 0, v___x_872_);
v___x_886_ = v___x_870_;
goto v_reusejp_885_;
}
else
{
lean_object* v_reuseFailAlloc_887_; 
v_reuseFailAlloc_887_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v_reuseFailAlloc_887_, 0, v___x_872_);
lean_ctor_set(v_reuseFailAlloc_887_, 1, v_head_814_);
v___x_886_ = v_reuseFailAlloc_887_;
goto v_reusejp_885_;
}
v_reusejp_885_:
{
return v___x_886_;
}
}
}
else
{
lean_object* v___x_888_; lean_object* v___x_890_; 
lean_dec_ref(v_head_814_);
v___x_888_ = lean_alloc_ctor(9, 1, 0);
lean_ctor_set(v___x_888_, 0, v___x_873_);
if (v_isShared_871_ == 0)
{
lean_ctor_set_tag(v___x_870_, 0);
lean_ctor_set(v___x_870_, 1, v___x_888_);
lean_ctor_set(v___x_870_, 0, v___x_872_);
v___x_890_ = v___x_870_;
goto v_reusejp_889_;
}
else
{
lean_object* v_reuseFailAlloc_891_; 
v_reuseFailAlloc_891_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v_reuseFailAlloc_891_, 0, v___x_872_);
lean_ctor_set(v_reuseFailAlloc_891_, 1, v___x_888_);
v___x_890_ = v_reuseFailAlloc_891_;
goto v_reusejp_889_;
}
v_reusejp_889_:
{
return v___x_890_;
}
}
}
else
{
lean_object* v___x_892_; lean_object* v___x_893_; uint8_t v___x_894_; 
v___x_892_ = lean_array_get_size(v___x_873_);
v___x_893_ = lean_unsigned_to_nat(0u);
v___x_894_ = lean_nat_dec_eq(v___x_892_, v___x_893_);
if (v___x_894_ == 0)
{
lean_object* v___x_895_; lean_object* v___x_896_; lean_object* v___x_897_; lean_object* v___x_898_; lean_object* v___x_899_; lean_object* v___x_901_; 
v___x_895_ = lean_unsigned_to_nat(1u);
v___x_896_ = lean_mk_empty_array_with_capacity(v___x_895_);
v___x_897_ = lean_array_push(v___x_896_, v_head_814_);
v___x_898_ = l_Array_append___redArg(v___x_897_, v___x_873_);
lean_dec_ref(v___x_873_);
v___x_899_ = lean_alloc_ctor(9, 1, 0);
lean_ctor_set(v___x_899_, 0, v___x_898_);
if (v_isShared_871_ == 0)
{
lean_ctor_set_tag(v___x_870_, 0);
lean_ctor_set(v___x_870_, 1, v___x_899_);
lean_ctor_set(v___x_870_, 0, v___x_872_);
v___x_901_ = v___x_870_;
goto v_reusejp_900_;
}
else
{
lean_object* v_reuseFailAlloc_902_; 
v_reuseFailAlloc_902_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v_reuseFailAlloc_902_, 0, v___x_872_);
lean_ctor_set(v_reuseFailAlloc_902_, 1, v___x_899_);
v___x_901_ = v_reuseFailAlloc_902_;
goto v_reusejp_900_;
}
v_reusejp_900_:
{
return v___x_901_;
}
}
else
{
lean_object* v___x_904_; 
lean_dec_ref(v___x_873_);
if (v_isShared_871_ == 0)
{
lean_ctor_set_tag(v___x_870_, 0);
lean_ctor_set(v___x_870_, 1, v_head_814_);
lean_ctor_set(v___x_870_, 0, v___x_872_);
v___x_904_ = v___x_870_;
goto v_reusejp_903_;
}
else
{
lean_object* v_reuseFailAlloc_905_; 
v_reuseFailAlloc_905_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v_reuseFailAlloc_905_, 0, v___x_872_);
lean_ctor_set(v_reuseFailAlloc_905_, 1, v_head_814_);
v___x_904_ = v_reuseFailAlloc_905_;
goto v_reusejp_903_;
}
v_reusejp_903_:
{
return v___x_904_;
}
}
}
}
}
}
}
}
}
LEAN_EXPORT lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_trimLeft_go(lean_object* v_i_908_, lean_object* v_a_909_){
_start:
{
lean_object* v___x_910_; 
v___x_910_ = l___private_Lean_DocString_Markdown_0__Lean_Doc_trimLeft_go___redArg(v_a_909_);
return v___x_910_;
}
}
LEAN_EXPORT lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_trimLeft___redArg(lean_object* v_inline_911_){
_start:
{
lean_object* v___x_912_; lean_object* v___x_913_; lean_object* v___x_914_; 
v___x_912_ = lean_box(0);
v___x_913_ = lean_alloc_ctor(1, 2, 0);
lean_ctor_set(v___x_913_, 0, v_inline_911_);
lean_ctor_set(v___x_913_, 1, v___x_912_);
v___x_914_ = l___private_Lean_DocString_Markdown_0__Lean_Doc_trimLeft_go___redArg(v___x_913_);
return v___x_914_;
}
}
LEAN_EXPORT lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_trimLeft(lean_object* v_i_915_, lean_object* v_inline_916_){
_start:
{
lean_object* v___x_917_; 
v___x_917_ = l___private_Lean_DocString_Markdown_0__Lean_Doc_trimLeft___redArg(v_inline_916_);
return v___x_917_;
}
}
LEAN_EXPORT lean_object* l_String_Slice_Pos_revSkipWhile___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_trimRight_go_spec__0(lean_object* v_s_918_, lean_object* v_pos_919_){
_start:
{
lean_object* v_str_920_; lean_object* v_startInclusive_921_; lean_object* v___x_922_; lean_object* v___x_923_; lean_object* v___x_924_; uint8_t v___x_925_; 
v_str_920_ = lean_ctor_get(v_s_918_, 0);
v_startInclusive_921_ = lean_ctor_get(v_s_918_, 1);
v___x_922_ = lean_nat_add(v_startInclusive_921_, v_pos_919_);
v___x_923_ = lean_nat_sub(v___x_922_, v_startInclusive_921_);
v___x_924_ = lean_unsigned_to_nat(0u);
v___x_925_ = lean_nat_dec_eq(v___x_923_, v___x_924_);
if (v___x_925_ == 0)
{
lean_object* v___x_926_; lean_object* v___x_927_; lean_object* v___x_928_; lean_object* v___x_929_; uint8_t v___y_934_; lean_object* v___x_935_; uint32_t v___x_936_; uint8_t v___y_938_; uint32_t v___x_943_; uint8_t v___x_944_; 
lean_inc(v_startInclusive_921_);
lean_inc_ref(v_str_920_);
v___x_926_ = lean_alloc_ctor(0, 3, 0);
lean_ctor_set(v___x_926_, 0, v_str_920_);
lean_ctor_set(v___x_926_, 1, v_startInclusive_921_);
lean_ctor_set(v___x_926_, 2, v___x_922_);
v___x_927_ = lean_unsigned_to_nat(1u);
v___x_928_ = lean_nat_sub(v___x_923_, v___x_927_);
lean_dec(v___x_923_);
v___x_929_ = l_String_Slice_posLE(v___x_926_, v___x_928_);
lean_dec_ref(v___x_926_);
v___x_935_ = lean_nat_add(v_startInclusive_921_, v___x_929_);
v___x_936_ = lean_string_utf8_get_fast(v_str_920_, v___x_935_);
lean_dec(v___x_935_);
v___x_943_ = 32;
v___x_944_ = lean_uint32_dec_eq(v___x_936_, v___x_943_);
if (v___x_944_ == 0)
{
uint32_t v___x_945_; uint8_t v___x_946_; 
v___x_945_ = 9;
v___x_946_ = lean_uint32_dec_eq(v___x_936_, v___x_945_);
v___y_938_ = v___x_946_;
goto v___jp_937_;
}
else
{
v___y_938_ = v___x_944_;
goto v___jp_937_;
}
v___jp_930_:
{
uint8_t v___x_931_; 
v___x_931_ = lean_nat_dec_lt(v___x_929_, v_pos_919_);
if (v___x_931_ == 0)
{
lean_dec(v___x_929_);
return v_pos_919_;
}
else
{
lean_dec(v_pos_919_);
v_pos_919_ = v___x_929_;
goto _start;
}
}
v___jp_933_:
{
if (v___y_934_ == 0)
{
lean_dec(v___x_929_);
return v_pos_919_;
}
else
{
goto v___jp_930_;
}
}
v___jp_937_:
{
if (v___y_938_ == 0)
{
uint32_t v___x_939_; uint8_t v___x_940_; 
v___x_939_ = 13;
v___x_940_ = lean_uint32_dec_eq(v___x_936_, v___x_939_);
if (v___x_940_ == 0)
{
uint32_t v___x_941_; uint8_t v___x_942_; 
v___x_941_ = 10;
v___x_942_ = lean_uint32_dec_eq(v___x_936_, v___x_941_);
v___y_934_ = v___x_942_;
goto v___jp_933_;
}
else
{
v___y_934_ = v___x_940_;
goto v___jp_933_;
}
}
else
{
goto v___jp_930_;
}
}
}
else
{
lean_dec(v___x_923_);
lean_dec(v___x_922_);
return v_pos_919_;
}
}
}
LEAN_EXPORT lean_object* l_String_Slice_Pos_revSkipWhile___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_trimRight_go_spec__0___boxed(lean_object* v_s_947_, lean_object* v_pos_948_){
_start:
{
lean_object* v_res_949_; 
v_res_949_ = l_String_Slice_Pos_revSkipWhile___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_trimRight_go_spec__0(v_s_947_, v_pos_948_);
lean_dec_ref(v_s_947_);
return v_res_949_;
}
}
static lean_object* _init_l___private_Lean_DocString_Markdown_0__Lean_Doc_trimRight_go___redArg___closed__0(void){
_start:
{
lean_object* v___x_950_; lean_object* v___x_951_; lean_object* v___x_952_; 
v___x_950_ = ((lean_object*)(l___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Lean_Doc_joinBlocks_spec__0___closed__0));
v___x_951_ = lean_obj_once(&l___private_Lean_DocString_Markdown_0__Lean_Doc_trimLeft_go___redArg___closed__0, &l___private_Lean_DocString_Markdown_0__Lean_Doc_trimLeft_go___redArg___closed__0_once, _init_l___private_Lean_DocString_Markdown_0__Lean_Doc_trimLeft_go___redArg___closed__0);
v___x_952_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v___x_952_, 0, v___x_951_);
lean_ctor_set(v___x_952_, 1, v___x_950_);
return v___x_952_;
}
}
LEAN_EXPORT lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_trimRight_go___redArg(lean_object* v_xs_953_){
_start:
{
lean_object* v___x_954_; lean_object* v___x_955_; uint8_t v___x_956_; 
v___x_954_ = lean_array_get_size(v_xs_953_);
v___x_955_ = lean_unsigned_to_nat(0u);
v___x_956_ = lean_nat_dec_eq(v___x_954_, v___x_955_);
if (v___x_956_ == 0)
{
lean_object* v___x_957_; lean_object* v___x_958_; lean_object* v___x_959_; 
v___x_957_ = lean_unsigned_to_nat(1u);
v___x_958_ = lean_nat_sub(v___x_954_, v___x_957_);
v___x_959_ = lean_array_fget(v_xs_953_, v___x_958_);
lean_dec(v___x_958_);
switch(lean_obj_tag(v___x_959_))
{
case 0:
{
lean_object* v_string_960_; lean_object* v___x_962_; uint8_t v_isShared_963_; uint8_t v_isSharedCheck_990_; 
v_string_960_ = lean_ctor_get(v___x_959_, 0);
v_isSharedCheck_990_ = !lean_is_exclusive(v___x_959_);
if (v_isSharedCheck_990_ == 0)
{
v___x_962_ = v___x_959_;
v_isShared_963_ = v_isSharedCheck_990_;
goto v_resetjp_961_;
}
else
{
lean_inc(v_string_960_);
lean_dec(v___x_959_);
v___x_962_ = lean_box(0);
v_isShared_963_ = v_isSharedCheck_990_;
goto v_resetjp_961_;
}
v_resetjp_961_:
{
lean_object* v___x_964_; lean_object* v___x_965_; lean_object* v___x_966_; uint8_t v___x_967_; 
v___x_964_ = lean_string_utf8_byte_size(v_string_960_);
lean_inc_ref(v_string_960_);
v___x_965_ = lean_alloc_ctor(0, 3, 0);
lean_ctor_set(v___x_965_, 0, v_string_960_);
lean_ctor_set(v___x_965_, 1, v___x_955_);
lean_ctor_set(v___x_965_, 2, v___x_964_);
v___x_966_ = l_String_Slice_Pos_skipWhile___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_trimLeft_go_spec__0(v___x_965_, v___x_955_);
v___x_967_ = lean_nat_dec_eq(v___x_966_, v___x_964_);
lean_dec(v___x_966_);
if (v___x_967_ == 0)
{
lean_object* v___x_968_; lean_object* v___x_969_; lean_object* v___x_970_; lean_object* v___x_972_; 
v___x_968_ = l_String_Slice_Pos_revSkipWhile___at___00__private_Lean_DocString_Markdown_0__Lean_Doc_trimRight_go_spec__0(v___x_965_, v___x_964_);
lean_dec_ref(v___x_965_);
v___x_969_ = lean_array_pop(v_xs_953_);
v___x_970_ = lean_string_utf8_extract(v_string_960_, v___x_955_, v___x_968_);
if (v_isShared_963_ == 0)
{
lean_ctor_set(v___x_962_, 0, v___x_970_);
v___x_972_ = v___x_962_;
goto v_reusejp_971_;
}
else
{
lean_object* v_reuseFailAlloc_977_; 
v_reuseFailAlloc_977_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v_reuseFailAlloc_977_, 0, v___x_970_);
v___x_972_ = v_reuseFailAlloc_977_;
goto v_reusejp_971_;
}
v_reusejp_971_:
{
lean_object* v___x_973_; lean_object* v___x_974_; lean_object* v___x_975_; lean_object* v___x_976_; 
v___x_973_ = lean_array_push(v___x_969_, v___x_972_);
v___x_974_ = lean_alloc_ctor(9, 1, 0);
lean_ctor_set(v___x_974_, 0, v___x_973_);
v___x_975_ = lean_string_utf8_extract(v_string_960_, v___x_968_, v___x_964_);
lean_dec(v___x_968_);
lean_dec_ref(v_string_960_);
v___x_976_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v___x_976_, 0, v___x_974_);
lean_ctor_set(v___x_976_, 1, v___x_975_);
return v___x_976_;
}
}
else
{
lean_object* v___x_978_; lean_object* v___x_979_; lean_object* v_fst_980_; lean_object* v_snd_981_; lean_object* v___x_983_; uint8_t v_isShared_984_; uint8_t v_isSharedCheck_989_; 
lean_dec_ref(v___x_965_);
lean_del_object(v___x_962_);
v___x_978_ = lean_array_pop(v_xs_953_);
v___x_979_ = l___private_Lean_DocString_Markdown_0__Lean_Doc_trimRight_go___redArg(v___x_978_);
v_fst_980_ = lean_ctor_get(v___x_979_, 0);
v_snd_981_ = lean_ctor_get(v___x_979_, 1);
v_isSharedCheck_989_ = !lean_is_exclusive(v___x_979_);
if (v_isSharedCheck_989_ == 0)
{
v___x_983_ = v___x_979_;
v_isShared_984_ = v_isSharedCheck_989_;
goto v_resetjp_982_;
}
else
{
lean_inc(v_snd_981_);
lean_inc(v_fst_980_);
lean_dec(v___x_979_);
v___x_983_ = lean_box(0);
v_isShared_984_ = v_isSharedCheck_989_;
goto v_resetjp_982_;
}
v_resetjp_982_:
{
lean_object* v___x_985_; lean_object* v___x_987_; 
v___x_985_ = lean_string_append(v_snd_981_, v_string_960_);
lean_dec_ref(v_string_960_);
if (v_isShared_984_ == 0)
{
lean_ctor_set(v___x_983_, 1, v___x_985_);
v___x_987_ = v___x_983_;
goto v_reusejp_986_;
}
else
{
lean_object* v_reuseFailAlloc_988_; 
v_reuseFailAlloc_988_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v_reuseFailAlloc_988_, 0, v_fst_980_);
lean_ctor_set(v_reuseFailAlloc_988_, 1, v___x_985_);
v___x_987_ = v_reuseFailAlloc_988_;
goto v_reusejp_986_;
}
v_reusejp_986_:
{
return v___x_987_;
}
}
}
}
}
case 9:
{
lean_object* v_content_991_; lean_object* v___x_992_; lean_object* v___x_993_; 
v_content_991_ = lean_ctor_get(v___x_959_, 0);
lean_inc_ref(v_content_991_);
lean_dec_ref(v___x_959_);
v___x_992_ = lean_array_pop(v_xs_953_);
v___x_993_ = l_Array_append___redArg(v___x_992_, v_content_991_);
lean_dec_ref(v_content_991_);
v_xs_953_ = v___x_993_;
goto _start;
}
default: 
{
lean_object* v___x_995_; lean_object* v___x_996_; lean_object* v___x_997_; 
lean_dec(v___x_959_);
v___x_995_ = lean_alloc_ctor(9, 1, 0);
lean_ctor_set(v___x_995_, 0, v_xs_953_);
v___x_996_ = ((lean_object*)(l___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Lean_Doc_joinBlocks_spec__0___closed__0));
v___x_997_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v___x_997_, 0, v___x_995_);
lean_ctor_set(v___x_997_, 1, v___x_996_);
return v___x_997_;
}
}
}
else
{
lean_object* v___x_998_; 
lean_dec_ref(v_xs_953_);
v___x_998_ = lean_obj_once(&l___private_Lean_DocString_Markdown_0__Lean_Doc_trimRight_go___redArg___closed__0, &l___private_Lean_DocString_Markdown_0__Lean_Doc_trimRight_go___redArg___closed__0_once, _init_l___private_Lean_DocString_Markdown_0__Lean_Doc_trimRight_go___redArg___closed__0);
return v___x_998_;
}
}
}
LEAN_EXPORT lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_trimRight_go(lean_object* v_i_999_, lean_object* v_xs_1000_){
_start:
{
lean_object* v___x_1001_; 
v___x_1001_ = l___private_Lean_DocString_Markdown_0__Lean_Doc_trimRight_go___redArg(v_xs_1000_);
return v___x_1001_;
}
}
LEAN_EXPORT lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_trimRight___redArg(lean_object* v_inline_1002_){
_start:
{
lean_object* v___x_1003_; lean_object* v___x_1004_; lean_object* v___x_1005_; lean_object* v___x_1006_; 
v___x_1003_ = lean_unsigned_to_nat(1u);
v___x_1004_ = lean_mk_empty_array_with_capacity(v___x_1003_);
v___x_1005_ = lean_array_push(v___x_1004_, v_inline_1002_);
v___x_1006_ = l___private_Lean_DocString_Markdown_0__Lean_Doc_trimRight_go___redArg(v___x_1005_);
return v___x_1006_;
}
}
LEAN_EXPORT lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_trimRight(lean_object* v_i_1007_, lean_object* v_inline_1008_){
_start:
{
lean_object* v___x_1009_; 
v___x_1009_ = l___private_Lean_DocString_Markdown_0__Lean_Doc_trimRight___redArg(v_inline_1008_);
return v___x_1009_;
}
}
LEAN_EXPORT lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_trim___redArg(lean_object* v_inline_1010_){
_start:
{
lean_object* v___x_1011_; lean_object* v_fst_1012_; lean_object* v_snd_1013_; lean_object* v___x_1015_; uint8_t v_isShared_1016_; uint8_t v_isSharedCheck_1021_; 
v___x_1011_ = l___private_Lean_DocString_Markdown_0__Lean_Doc_trimLeft___redArg(v_inline_1010_);
v_fst_1012_ = lean_ctor_get(v___x_1011_, 0);
v_snd_1013_ = lean_ctor_get(v___x_1011_, 1);
v_isSharedCheck_1021_ = !lean_is_exclusive(v___x_1011_);
if (v_isSharedCheck_1021_ == 0)
{
v___x_1015_ = v___x_1011_;
v_isShared_1016_ = v_isSharedCheck_1021_;
goto v_resetjp_1014_;
}
else
{
lean_inc(v_snd_1013_);
lean_inc(v_fst_1012_);
lean_dec(v___x_1011_);
v___x_1015_ = lean_box(0);
v_isShared_1016_ = v_isSharedCheck_1021_;
goto v_resetjp_1014_;
}
v_resetjp_1014_:
{
lean_object* v___x_1017_; lean_object* v___x_1019_; 
v___x_1017_ = l___private_Lean_DocString_Markdown_0__Lean_Doc_trimRight___redArg(v_snd_1013_);
if (v_isShared_1016_ == 0)
{
lean_ctor_set(v___x_1015_, 1, v___x_1017_);
v___x_1019_ = v___x_1015_;
goto v_reusejp_1018_;
}
else
{
lean_object* v_reuseFailAlloc_1020_; 
v_reuseFailAlloc_1020_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v_reuseFailAlloc_1020_, 0, v_fst_1012_);
lean_ctor_set(v_reuseFailAlloc_1020_, 1, v___x_1017_);
v___x_1019_ = v_reuseFailAlloc_1020_;
goto v_reusejp_1018_;
}
v_reusejp_1018_:
{
return v___x_1019_;
}
}
}
}
LEAN_EXPORT lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_trim(lean_object* v_i_1022_, lean_object* v_inline_1023_){
_start:
{
lean_object* v___x_1024_; 
v___x_1024_ = l___private_Lean_DocString_Markdown_0__Lean_Doc_trim___redArg(v_inline_1023_);
return v___x_1024_;
}
}
static lean_object* _init_l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__32(void){
_start:
{
lean_object* v___x_1096_; lean_object* v___x_1097_; lean_object* v___x_1098_; lean_object* v___x_1099_; 
v___x_1096_ = ((lean_object*)(l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__29));
v___x_1097_ = lean_unsigned_to_nat(3u);
v___x_1098_ = lean_mk_empty_array_with_capacity(v___x_1097_);
v___x_1099_ = lean_array_push(v___x_1098_, v___x_1096_);
return v___x_1099_;
}
}
LEAN_EXPORT lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg(lean_object* v_inst_1102_, lean_object* v_x_1103_, lean_object* v_x_1104_, lean_object* v_a_1105_){
_start:
{
lean_object* v_pieces_1107_; lean_object* v___y_1108_; lean_object* v_pieces_1112_; lean_object* v___y_1113_; lean_object* v___x_1116_; 
v___x_1116_ = ((lean_object*)(l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__19));
switch(lean_obj_tag(v_x_1104_))
{
case 0:
{
lean_object* v_string_1117_; lean_object* v___x_1118_; lean_object* v___x_1119_; lean_object* v___x_1120_; lean_object* v___x_1121_; lean_object* v___x_1122_; 
lean_dec_ref(v_x_1103_);
lean_dec_ref(v_inst_1102_);
v_string_1117_ = lean_ctor_get(v_x_1104_, 0);
lean_inc_ref(v_string_1117_);
lean_dec_ref(v_x_1104_);
v___x_1118_ = l___private_Lean_DocString_Markdown_0__Lean_Doc_escape(v_string_1117_);
lean_dec_ref(v_string_1117_);
v___x_1119_ = lean_unsigned_to_nat(1u);
v___x_1120_ = lean_mk_empty_array_with_capacity(v___x_1119_);
v___x_1121_ = lean_array_push(v___x_1120_, v___x_1118_);
v___x_1122_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v___x_1122_, 0, v___x_1121_);
lean_ctor_set(v___x_1122_, 1, v_a_1105_);
return v___x_1122_;
}
case 1:
{
lean_object* v_content_1123_; lean_object* v___x_1125_; uint8_t v_isShared_1126_; uint8_t v_isSharedCheck_1177_; 
v_content_1123_ = lean_ctor_get(v_x_1104_, 0);
v_isSharedCheck_1177_ = !lean_is_exclusive(v_x_1104_);
if (v_isSharedCheck_1177_ == 0)
{
v___x_1125_ = v_x_1104_;
v_isShared_1126_ = v_isSharedCheck_1177_;
goto v_resetjp_1124_;
}
else
{
lean_inc(v_content_1123_);
lean_dec(v_x_1104_);
v___x_1125_ = lean_box(0);
v_isShared_1126_ = v_isSharedCheck_1177_;
goto v_resetjp_1124_;
}
v_resetjp_1124_:
{
lean_object* v___x_1128_; 
if (v_isShared_1126_ == 0)
{
lean_ctor_set_tag(v___x_1125_, 9);
v___x_1128_ = v___x_1125_;
goto v_reusejp_1127_;
}
else
{
lean_object* v_reuseFailAlloc_1176_; 
v_reuseFailAlloc_1176_ = lean_alloc_ctor(9, 1, 0);
lean_ctor_set(v_reuseFailAlloc_1176_, 0, v_content_1123_);
v___x_1128_ = v_reuseFailAlloc_1176_;
goto v_reusejp_1127_;
}
v_reusejp_1127_:
{
lean_object* v___x_1129_; lean_object* v_snd_1130_; lean_object* v_fst_1131_; lean_object* v_fst_1132_; lean_object* v_snd_1133_; lean_object* v_pieces_1135_; lean_object* v___y_1136_; uint8_t v_inEmph_1144_; uint8_t v_inBold_1145_; uint8_t v_inLink_1146_; lean_object* v___x_1148_; uint8_t v_isShared_1149_; uint8_t v_isSharedCheck_1175_; 
v___x_1129_ = l___private_Lean_DocString_Markdown_0__Lean_Doc_trim___redArg(v___x_1128_);
v_snd_1130_ = lean_ctor_get(v___x_1129_, 1);
lean_inc(v_snd_1130_);
v_fst_1131_ = lean_ctor_get(v___x_1129_, 0);
lean_inc(v_fst_1131_);
lean_dec_ref(v___x_1129_);
v_fst_1132_ = lean_ctor_get(v_snd_1130_, 0);
lean_inc(v_fst_1132_);
v_snd_1133_ = lean_ctor_get(v_snd_1130_, 1);
lean_inc(v_snd_1133_);
lean_dec(v_snd_1130_);
v_inEmph_1144_ = lean_ctor_get_uint8(v_x_1103_, 0);
v_inBold_1145_ = lean_ctor_get_uint8(v_x_1103_, 1);
v_inLink_1146_ = lean_ctor_get_uint8(v_x_1103_, 2);
v_isSharedCheck_1175_ = !lean_is_exclusive(v_x_1103_);
if (v_isSharedCheck_1175_ == 0)
{
v___x_1148_ = v_x_1103_;
v_isShared_1149_ = v_isSharedCheck_1175_;
goto v_resetjp_1147_;
}
else
{
lean_dec(v_x_1103_);
v___x_1148_ = lean_box(0);
v_isShared_1149_ = v_isSharedCheck_1175_;
goto v_resetjp_1147_;
}
v___jp_1134_:
{
lean_object* v___x_1137_; lean_object* v___x_1138_; uint8_t v___x_1139_; 
v___x_1137_ = lean_string_utf8_byte_size(v_snd_1133_);
v___x_1138_ = lean_unsigned_to_nat(0u);
v___x_1139_ = lean_nat_dec_eq(v___x_1137_, v___x_1138_);
if (v___x_1139_ == 0)
{
lean_object* v___x_1140_; lean_object* v___x_1141_; lean_object* v___x_1142_; lean_object* v___x_1143_; 
v___x_1140_ = lean_unsigned_to_nat(1u);
v___x_1141_ = lean_mk_empty_array_with_capacity(v___x_1140_);
v___x_1142_ = lean_array_push(v___x_1141_, v_snd_1133_);
v___x_1143_ = lean_array_push(v_pieces_1135_, v___x_1142_);
v_pieces_1112_ = v___x_1143_;
v___y_1113_ = v___y_1136_;
goto v___jp_1111_;
}
else
{
lean_dec(v_snd_1133_);
v_pieces_1112_ = v_pieces_1135_;
v___y_1113_ = v___y_1136_;
goto v___jp_1111_;
}
}
v_resetjp_1147_:
{
uint8_t v___x_1150_; lean_object* v___x_1152_; 
v___x_1150_ = 1;
if (v_isShared_1149_ == 0)
{
v___x_1152_ = v___x_1148_;
goto v_reusejp_1151_;
}
else
{
lean_object* v_reuseFailAlloc_1174_; 
v_reuseFailAlloc_1174_ = lean_alloc_ctor(0, 0, 3);
lean_ctor_set_uint8(v_reuseFailAlloc_1174_, 1, v_inBold_1145_);
lean_ctor_set_uint8(v_reuseFailAlloc_1174_, 2, v_inLink_1146_);
v___x_1152_ = v_reuseFailAlloc_1174_;
goto v_reusejp_1151_;
}
v_reusejp_1151_:
{
lean_object* v___x_1153_; lean_object* v_fst_1154_; lean_object* v_snd_1155_; lean_object* v_pieces_1157_; lean_object* v___y_1158_; lean_object* v_pieces_1163_; lean_object* v___x_1166_; lean_object* v___x_1167_; lean_object* v___x_1168_; uint8_t v___x_1169_; 
lean_ctor_set_uint8(v___x_1152_, 0, v___x_1150_);
v___x_1153_ = l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg(v_inst_1102_, v___x_1152_, v_fst_1132_, v_a_1105_);
v_fst_1154_ = lean_ctor_get(v___x_1153_, 0);
lean_inc(v_fst_1154_);
v_snd_1155_ = lean_ctor_get(v___x_1153_, 1);
lean_inc(v_snd_1155_);
lean_dec_ref(v___x_1153_);
v___x_1166_ = lean_unsigned_to_nat(0u);
v___x_1167_ = ((lean_object*)(l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__22));
v___x_1168_ = lean_string_utf8_byte_size(v_fst_1131_);
v___x_1169_ = lean_nat_dec_eq(v___x_1168_, v___x_1166_);
if (v___x_1169_ == 0)
{
lean_object* v___x_1170_; lean_object* v___x_1171_; lean_object* v___x_1172_; lean_object* v___x_1173_; 
v___x_1170_ = lean_unsigned_to_nat(1u);
v___x_1171_ = lean_mk_empty_array_with_capacity(v___x_1170_);
v___x_1172_ = lean_array_push(v___x_1171_, v_fst_1131_);
v___x_1173_ = lean_array_push(v___x_1167_, v___x_1172_);
v_pieces_1163_ = v___x_1173_;
goto v___jp_1162_;
}
else
{
lean_dec(v_fst_1131_);
v_pieces_1163_ = v___x_1167_;
goto v___jp_1162_;
}
v___jp_1156_:
{
lean_object* v___x_1159_; 
v___x_1159_ = lean_array_push(v_pieces_1157_, v_fst_1154_);
if (v_inEmph_1144_ == 0)
{
lean_object* v___x_1160_; lean_object* v___x_1161_; 
v___x_1160_ = ((lean_object*)(l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__21));
v___x_1161_ = lean_array_push(v___x_1159_, v___x_1160_);
v_pieces_1135_ = v___x_1161_;
v___y_1136_ = v___y_1158_;
goto v___jp_1134_;
}
else
{
v_pieces_1135_ = v___x_1159_;
v___y_1136_ = v___y_1158_;
goto v___jp_1134_;
}
}
v___jp_1162_:
{
if (v_inEmph_1144_ == 0)
{
lean_object* v___x_1164_; lean_object* v___x_1165_; 
v___x_1164_ = ((lean_object*)(l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__21));
v___x_1165_ = lean_array_push(v_pieces_1163_, v___x_1164_);
v_pieces_1157_ = v___x_1165_;
v___y_1158_ = v_snd_1155_;
goto v___jp_1156_;
}
else
{
v_pieces_1157_ = v_pieces_1163_;
v___y_1158_ = v_snd_1155_;
goto v___jp_1156_;
}
}
}
}
}
}
}
case 2:
{
lean_object* v_content_1178_; lean_object* v___x_1180_; uint8_t v_isShared_1181_; uint8_t v_isSharedCheck_1232_; 
v_content_1178_ = lean_ctor_get(v_x_1104_, 0);
v_isSharedCheck_1232_ = !lean_is_exclusive(v_x_1104_);
if (v_isSharedCheck_1232_ == 0)
{
v___x_1180_ = v_x_1104_;
v_isShared_1181_ = v_isSharedCheck_1232_;
goto v_resetjp_1179_;
}
else
{
lean_inc(v_content_1178_);
lean_dec(v_x_1104_);
v___x_1180_ = lean_box(0);
v_isShared_1181_ = v_isSharedCheck_1232_;
goto v_resetjp_1179_;
}
v_resetjp_1179_:
{
lean_object* v___x_1183_; 
if (v_isShared_1181_ == 0)
{
lean_ctor_set_tag(v___x_1180_, 9);
v___x_1183_ = v___x_1180_;
goto v_reusejp_1182_;
}
else
{
lean_object* v_reuseFailAlloc_1231_; 
v_reuseFailAlloc_1231_ = lean_alloc_ctor(9, 1, 0);
lean_ctor_set(v_reuseFailAlloc_1231_, 0, v_content_1178_);
v___x_1183_ = v_reuseFailAlloc_1231_;
goto v_reusejp_1182_;
}
v_reusejp_1182_:
{
lean_object* v___x_1184_; lean_object* v_snd_1185_; lean_object* v_fst_1186_; lean_object* v_fst_1187_; lean_object* v_snd_1188_; lean_object* v_pieces_1190_; lean_object* v___y_1191_; uint8_t v_inEmph_1199_; uint8_t v_inBold_1200_; uint8_t v_inLink_1201_; lean_object* v___x_1203_; uint8_t v_isShared_1204_; uint8_t v_isSharedCheck_1230_; 
v___x_1184_ = l___private_Lean_DocString_Markdown_0__Lean_Doc_trim___redArg(v___x_1183_);
v_snd_1185_ = lean_ctor_get(v___x_1184_, 1);
lean_inc(v_snd_1185_);
v_fst_1186_ = lean_ctor_get(v___x_1184_, 0);
lean_inc(v_fst_1186_);
lean_dec_ref(v___x_1184_);
v_fst_1187_ = lean_ctor_get(v_snd_1185_, 0);
lean_inc(v_fst_1187_);
v_snd_1188_ = lean_ctor_get(v_snd_1185_, 1);
lean_inc(v_snd_1188_);
lean_dec(v_snd_1185_);
v_inEmph_1199_ = lean_ctor_get_uint8(v_x_1103_, 0);
v_inBold_1200_ = lean_ctor_get_uint8(v_x_1103_, 1);
v_inLink_1201_ = lean_ctor_get_uint8(v_x_1103_, 2);
v_isSharedCheck_1230_ = !lean_is_exclusive(v_x_1103_);
if (v_isSharedCheck_1230_ == 0)
{
v___x_1203_ = v_x_1103_;
v_isShared_1204_ = v_isSharedCheck_1230_;
goto v_resetjp_1202_;
}
else
{
lean_dec(v_x_1103_);
v___x_1203_ = lean_box(0);
v_isShared_1204_ = v_isSharedCheck_1230_;
goto v_resetjp_1202_;
}
v___jp_1189_:
{
lean_object* v___x_1192_; lean_object* v___x_1193_; uint8_t v___x_1194_; 
v___x_1192_ = lean_string_utf8_byte_size(v_snd_1188_);
v___x_1193_ = lean_unsigned_to_nat(0u);
v___x_1194_ = lean_nat_dec_eq(v___x_1192_, v___x_1193_);
if (v___x_1194_ == 0)
{
lean_object* v___x_1195_; lean_object* v___x_1196_; lean_object* v___x_1197_; lean_object* v___x_1198_; 
v___x_1195_ = lean_unsigned_to_nat(1u);
v___x_1196_ = lean_mk_empty_array_with_capacity(v___x_1195_);
v___x_1197_ = lean_array_push(v___x_1196_, v_snd_1188_);
v___x_1198_ = lean_array_push(v_pieces_1190_, v___x_1197_);
v_pieces_1107_ = v___x_1198_;
v___y_1108_ = v___y_1191_;
goto v___jp_1106_;
}
else
{
lean_dec(v_snd_1188_);
v_pieces_1107_ = v_pieces_1190_;
v___y_1108_ = v___y_1191_;
goto v___jp_1106_;
}
}
v_resetjp_1202_:
{
uint8_t v___x_1205_; lean_object* v___x_1207_; 
v___x_1205_ = 1;
if (v_isShared_1204_ == 0)
{
v___x_1207_ = v___x_1203_;
goto v_reusejp_1206_;
}
else
{
lean_object* v_reuseFailAlloc_1229_; 
v_reuseFailAlloc_1229_ = lean_alloc_ctor(0, 0, 3);
lean_ctor_set_uint8(v_reuseFailAlloc_1229_, 0, v_inEmph_1199_);
lean_ctor_set_uint8(v_reuseFailAlloc_1229_, 2, v_inLink_1201_);
v___x_1207_ = v_reuseFailAlloc_1229_;
goto v_reusejp_1206_;
}
v_reusejp_1206_:
{
lean_object* v___x_1208_; lean_object* v_fst_1209_; lean_object* v_snd_1210_; lean_object* v_pieces_1212_; lean_object* v___y_1213_; lean_object* v_pieces_1218_; lean_object* v___x_1221_; lean_object* v___x_1222_; lean_object* v___x_1223_; uint8_t v___x_1224_; 
lean_ctor_set_uint8(v___x_1207_, 1, v___x_1205_);
v___x_1208_ = l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg(v_inst_1102_, v___x_1207_, v_fst_1187_, v_a_1105_);
v_fst_1209_ = lean_ctor_get(v___x_1208_, 0);
lean_inc(v_fst_1209_);
v_snd_1210_ = lean_ctor_get(v___x_1208_, 1);
lean_inc(v_snd_1210_);
lean_dec_ref(v___x_1208_);
v___x_1221_ = lean_unsigned_to_nat(0u);
v___x_1222_ = ((lean_object*)(l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__22));
v___x_1223_ = lean_string_utf8_byte_size(v_fst_1186_);
v___x_1224_ = lean_nat_dec_eq(v___x_1223_, v___x_1221_);
if (v___x_1224_ == 0)
{
lean_object* v___x_1225_; lean_object* v___x_1226_; lean_object* v___x_1227_; lean_object* v___x_1228_; 
v___x_1225_ = lean_unsigned_to_nat(1u);
v___x_1226_ = lean_mk_empty_array_with_capacity(v___x_1225_);
v___x_1227_ = lean_array_push(v___x_1226_, v_fst_1186_);
v___x_1228_ = lean_array_push(v___x_1222_, v___x_1227_);
v_pieces_1218_ = v___x_1228_;
goto v___jp_1217_;
}
else
{
lean_dec(v_fst_1186_);
v_pieces_1218_ = v___x_1222_;
goto v___jp_1217_;
}
v___jp_1211_:
{
lean_object* v___x_1214_; 
v___x_1214_ = lean_array_push(v_pieces_1212_, v_fst_1209_);
if (v_inBold_1200_ == 0)
{
lean_object* v___x_1215_; lean_object* v___x_1216_; 
v___x_1215_ = ((lean_object*)(l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__24));
v___x_1216_ = lean_array_push(v___x_1214_, v___x_1215_);
v_pieces_1190_ = v___x_1216_;
v___y_1191_ = v___y_1213_;
goto v___jp_1189_;
}
else
{
v_pieces_1190_ = v___x_1214_;
v___y_1191_ = v___y_1213_;
goto v___jp_1189_;
}
}
v___jp_1217_:
{
if (v_inBold_1200_ == 0)
{
lean_object* v___x_1219_; lean_object* v___x_1220_; 
v___x_1219_ = ((lean_object*)(l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__24));
v___x_1220_ = lean_array_push(v_pieces_1218_, v___x_1219_);
v_pieces_1212_ = v___x_1220_;
v___y_1213_ = v_snd_1210_;
goto v___jp_1211_;
}
else
{
v_pieces_1212_ = v_pieces_1218_;
v___y_1213_ = v_snd_1210_;
goto v___jp_1211_;
}
}
}
}
}
}
}
case 3:
{
lean_object* v_string_1233_; lean_object* v___x_1234_; lean_object* v___x_1235_; lean_object* v___x_1236_; lean_object* v___x_1237_; lean_object* v___x_1238_; 
lean_dec_ref(v_x_1103_);
lean_dec_ref(v_inst_1102_);
v_string_1233_ = lean_ctor_get(v_x_1104_, 0);
lean_inc_ref(v_string_1233_);
lean_dec_ref(v_x_1104_);
v___x_1234_ = l___private_Lean_DocString_Markdown_0__Lean_Doc_quoteCode(v_string_1233_);
v___x_1235_ = lean_unsigned_to_nat(1u);
v___x_1236_ = lean_mk_empty_array_with_capacity(v___x_1235_);
v___x_1237_ = lean_array_push(v___x_1236_, v___x_1234_);
v___x_1238_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v___x_1238_, 0, v___x_1237_);
lean_ctor_set(v___x_1238_, 1, v_a_1105_);
return v___x_1238_;
}
case 4:
{
uint8_t v_mode_1239_; 
lean_dec_ref(v_x_1103_);
lean_dec_ref(v_inst_1102_);
v_mode_1239_ = lean_ctor_get_uint8(v_x_1104_, sizeof(void*)*1);
if (v_mode_1239_ == 0)
{
lean_object* v_string_1240_; lean_object* v___x_1241_; lean_object* v___x_1242_; lean_object* v___x_1243_; lean_object* v___x_1244_; lean_object* v___x_1245_; lean_object* v___x_1246_; lean_object* v___x_1247_; 
v_string_1240_ = lean_ctor_get(v_x_1104_, 0);
lean_inc_ref(v_string_1240_);
lean_dec_ref(v_x_1104_);
v___x_1241_ = ((lean_object*)(l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__25));
v___x_1242_ = lean_string_append(v___x_1241_, v_string_1240_);
lean_dec_ref(v_string_1240_);
v___x_1243_ = lean_string_append(v___x_1242_, v___x_1241_);
v___x_1244_ = lean_unsigned_to_nat(1u);
v___x_1245_ = lean_mk_empty_array_with_capacity(v___x_1244_);
v___x_1246_ = lean_array_push(v___x_1245_, v___x_1243_);
v___x_1247_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v___x_1247_, 0, v___x_1246_);
lean_ctor_set(v___x_1247_, 1, v_a_1105_);
return v___x_1247_;
}
else
{
lean_object* v_string_1248_; lean_object* v___x_1249_; lean_object* v___x_1250_; lean_object* v___x_1251_; lean_object* v___x_1252_; lean_object* v___x_1253_; lean_object* v___x_1254_; lean_object* v___x_1255_; 
v_string_1248_ = lean_ctor_get(v_x_1104_, 0);
lean_inc_ref(v_string_1248_);
lean_dec_ref(v_x_1104_);
v___x_1249_ = ((lean_object*)(l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__26));
v___x_1250_ = lean_string_append(v___x_1249_, v_string_1248_);
lean_dec_ref(v_string_1248_);
v___x_1251_ = lean_string_append(v___x_1250_, v___x_1249_);
v___x_1252_ = lean_unsigned_to_nat(1u);
v___x_1253_ = lean_mk_empty_array_with_capacity(v___x_1252_);
v___x_1254_ = lean_array_push(v___x_1253_, v___x_1251_);
v___x_1255_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v___x_1255_, 0, v___x_1254_);
lean_ctor_set(v___x_1255_, 1, v_a_1105_);
return v___x_1255_;
}
}
case 5:
{
lean_object* v___x_1256_; lean_object* v___x_1257_; 
lean_dec_ref(v_x_1104_);
lean_dec_ref(v_x_1103_);
lean_dec_ref(v_inst_1102_);
v___x_1256_ = ((lean_object*)(l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__27));
v___x_1257_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v___x_1257_, 0, v___x_1256_);
lean_ctor_set(v___x_1257_, 1, v_a_1105_);
return v___x_1257_;
}
case 6:
{
uint8_t v_inLink_1258_; 
v_inLink_1258_ = lean_ctor_get_uint8(v_x_1103_, 2);
if (v_inLink_1258_ == 0)
{
lean_object* v_content_1259_; lean_object* v_url_1260_; uint8_t v_inEmph_1261_; uint8_t v_inBold_1262_; lean_object* v___x_1264_; uint8_t v_isShared_1265_; uint8_t v_isSharedCheck_1292_; 
v_content_1259_ = lean_ctor_get(v_x_1104_, 0);
lean_inc_ref(v_content_1259_);
v_url_1260_ = lean_ctor_get(v_x_1104_, 1);
lean_inc_ref(v_url_1260_);
lean_dec_ref(v_x_1104_);
v_inEmph_1261_ = lean_ctor_get_uint8(v_x_1103_, 0);
v_inBold_1262_ = lean_ctor_get_uint8(v_x_1103_, 1);
v_isSharedCheck_1292_ = !lean_is_exclusive(v_x_1103_);
if (v_isSharedCheck_1292_ == 0)
{
v___x_1264_ = v_x_1103_;
v_isShared_1265_ = v_isSharedCheck_1292_;
goto v_resetjp_1263_;
}
else
{
lean_dec(v_x_1103_);
v___x_1264_ = lean_box(0);
v_isShared_1265_ = v_isSharedCheck_1292_;
goto v_resetjp_1263_;
}
v_resetjp_1263_:
{
uint8_t v___x_1266_; lean_object* v___x_1268_; 
v___x_1266_ = 1;
if (v_isShared_1265_ == 0)
{
v___x_1268_ = v___x_1264_;
goto v_reusejp_1267_;
}
else
{
lean_object* v_reuseFailAlloc_1291_; 
v_reuseFailAlloc_1291_ = lean_alloc_ctor(0, 0, 3);
lean_ctor_set_uint8(v_reuseFailAlloc_1291_, 0, v_inEmph_1261_);
lean_ctor_set_uint8(v_reuseFailAlloc_1291_, 1, v_inBold_1262_);
v___x_1268_ = v_reuseFailAlloc_1291_;
goto v_reusejp_1267_;
}
v_reusejp_1267_:
{
lean_object* v___x_1269_; lean_object* v___x_1270_; lean_object* v_fst_1271_; lean_object* v_snd_1272_; lean_object* v___x_1274_; uint8_t v_isShared_1275_; uint8_t v_isSharedCheck_1290_; 
lean_ctor_set_uint8(v___x_1268_, 2, v___x_1266_);
v___x_1269_ = lean_alloc_ctor(9, 1, 0);
lean_ctor_set(v___x_1269_, 0, v_content_1259_);
v___x_1270_ = l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg(v_inst_1102_, v___x_1268_, v___x_1269_, v_a_1105_);
v_fst_1271_ = lean_ctor_get(v___x_1270_, 0);
v_snd_1272_ = lean_ctor_get(v___x_1270_, 1);
v_isSharedCheck_1290_ = !lean_is_exclusive(v___x_1270_);
if (v_isSharedCheck_1290_ == 0)
{
v___x_1274_ = v___x_1270_;
v_isShared_1275_ = v_isSharedCheck_1290_;
goto v_resetjp_1273_;
}
else
{
lean_inc(v_snd_1272_);
lean_inc(v_fst_1271_);
lean_dec(v___x_1270_);
v___x_1274_ = lean_box(0);
v_isShared_1275_ = v_isSharedCheck_1290_;
goto v_resetjp_1273_;
}
v_resetjp_1273_:
{
lean_object* v___x_1276_; lean_object* v___x_1277_; lean_object* v___x_1278_; lean_object* v___x_1279_; lean_object* v___x_1280_; lean_object* v___x_1281_; lean_object* v___x_1282_; lean_object* v___x_1283_; lean_object* v___x_1284_; lean_object* v___x_1285_; lean_object* v___x_1286_; lean_object* v___x_1288_; 
v___x_1276_ = lean_unsigned_to_nat(1u);
v___x_1277_ = lean_mk_empty_array_with_capacity(v___x_1276_);
v___x_1278_ = ((lean_object*)(l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__30));
v___x_1279_ = lean_string_append(v___x_1278_, v_url_1260_);
lean_dec_ref(v_url_1260_);
v___x_1280_ = ((lean_object*)(l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__31));
v___x_1281_ = lean_string_append(v___x_1279_, v___x_1280_);
v___x_1282_ = lean_array_push(v___x_1277_, v___x_1281_);
v___x_1283_ = lean_obj_once(&l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__32, &l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__32_once, _init_l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__32);
v___x_1284_ = lean_array_push(v___x_1283_, v_fst_1271_);
v___x_1285_ = lean_array_push(v___x_1284_, v___x_1282_);
v___x_1286_ = l_Lean_Doc_joinInlines(v___x_1285_);
lean_dec_ref(v___x_1285_);
if (v_isShared_1275_ == 0)
{
lean_ctor_set(v___x_1274_, 0, v___x_1286_);
v___x_1288_ = v___x_1274_;
goto v_reusejp_1287_;
}
else
{
lean_object* v_reuseFailAlloc_1289_; 
v_reuseFailAlloc_1289_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v_reuseFailAlloc_1289_, 0, v___x_1286_);
lean_ctor_set(v_reuseFailAlloc_1289_, 1, v_snd_1272_);
v___x_1288_ = v_reuseFailAlloc_1289_;
goto v_reusejp_1287_;
}
v_reusejp_1287_:
{
return v___x_1288_;
}
}
}
}
}
else
{
lean_object* v_content_1293_; lean_object* v___x_1294_; size_t v_sz_1295_; size_t v___x_1296_; lean_object* v___x_5248__overap_1297_; lean_object* v___x_1298_; lean_object* v_fst_1299_; lean_object* v_snd_1300_; lean_object* v___x_1302_; uint8_t v_isShared_1303_; uint8_t v_isSharedCheck_1308_; 
v_content_1293_ = lean_ctor_get(v_x_1104_, 0);
lean_inc_ref(v_content_1293_);
lean_dec_ref(v_x_1104_);
v___x_1294_ = lean_alloc_closure((void*)(l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg), 4, 2);
lean_closure_set(v___x_1294_, 0, v_inst_1102_);
lean_closure_set(v___x_1294_, 1, v_x_1103_);
v_sz_1295_ = lean_array_size(v_content_1293_);
v___x_1296_ = ((size_t)0ULL);
v___x_5248__overap_1297_ = l___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map(lean_box(0), lean_box(0), lean_box(0), v___x_1116_, v___x_1294_, v_sz_1295_, v___x_1296_, v_content_1293_);
v___x_1298_ = lean_apply_1(v___x_5248__overap_1297_, v_a_1105_);
v_fst_1299_ = lean_ctor_get(v___x_1298_, 0);
v_snd_1300_ = lean_ctor_get(v___x_1298_, 1);
v_isSharedCheck_1308_ = !lean_is_exclusive(v___x_1298_);
if (v_isSharedCheck_1308_ == 0)
{
v___x_1302_ = v___x_1298_;
v_isShared_1303_ = v_isSharedCheck_1308_;
goto v_resetjp_1301_;
}
else
{
lean_inc(v_snd_1300_);
lean_inc(v_fst_1299_);
lean_dec(v___x_1298_);
v___x_1302_ = lean_box(0);
v_isShared_1303_ = v_isSharedCheck_1308_;
goto v_resetjp_1301_;
}
v_resetjp_1301_:
{
lean_object* v___x_1304_; lean_object* v___x_1306_; 
v___x_1304_ = l_Lean_Doc_joinInlines(v_fst_1299_);
lean_dec(v_fst_1299_);
if (v_isShared_1303_ == 0)
{
lean_ctor_set(v___x_1302_, 0, v___x_1304_);
v___x_1306_ = v___x_1302_;
goto v_reusejp_1305_;
}
else
{
lean_object* v_reuseFailAlloc_1307_; 
v_reuseFailAlloc_1307_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v_reuseFailAlloc_1307_, 0, v___x_1304_);
lean_ctor_set(v_reuseFailAlloc_1307_, 1, v_snd_1300_);
v___x_1306_ = v_reuseFailAlloc_1307_;
goto v_reusejp_1305_;
}
v_reusejp_1305_:
{
return v___x_1306_;
}
}
}
}
case 7:
{
lean_object* v_name_1309_; lean_object* v_content_1310_; lean_object* v___x_1311_; size_t v_sz_1312_; size_t v___x_1313_; lean_object* v___x_5251__overap_1314_; lean_object* v___x_1315_; lean_object* v_fst_1316_; lean_object* v_snd_1317_; lean_object* v___x_1319_; uint8_t v_isShared_1320_; uint8_t v_isSharedCheck_1337_; 
v_name_1309_ = lean_ctor_get(v_x_1104_, 0);
lean_inc_ref(v_name_1309_);
v_content_1310_ = lean_ctor_get(v_x_1104_, 1);
lean_inc_ref(v_content_1310_);
lean_dec_ref(v_x_1104_);
v___x_1311_ = lean_alloc_closure((void*)(l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg), 4, 2);
lean_closure_set(v___x_1311_, 0, v_inst_1102_);
lean_closure_set(v___x_1311_, 1, v_x_1103_);
v_sz_1312_ = lean_array_size(v_content_1310_);
v___x_1313_ = ((size_t)0ULL);
v___x_5251__overap_1314_ = l___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map(lean_box(0), lean_box(0), lean_box(0), v___x_1116_, v___x_1311_, v_sz_1312_, v___x_1313_, v_content_1310_);
v___x_1315_ = lean_apply_1(v___x_5251__overap_1314_, v_a_1105_);
v_fst_1316_ = lean_ctor_get(v___x_1315_, 0);
v_snd_1317_ = lean_ctor_get(v___x_1315_, 1);
v_isSharedCheck_1337_ = !lean_is_exclusive(v___x_1315_);
if (v_isSharedCheck_1337_ == 0)
{
v___x_1319_ = v___x_1315_;
v_isShared_1320_ = v_isSharedCheck_1337_;
goto v_resetjp_1318_;
}
else
{
lean_inc(v_snd_1317_);
lean_inc(v_fst_1316_);
lean_dec(v___x_1315_);
v___x_1319_ = lean_box(0);
v_isShared_1320_ = v_isSharedCheck_1337_;
goto v_resetjp_1318_;
}
v_resetjp_1318_:
{
lean_object* v___x_1321_; lean_object* v___x_1322_; lean_object* v___x_1323_; lean_object* v___x_1324_; lean_object* v___x_1326_; 
v___x_1321_ = ((lean_object*)(l_Lean_Doc_MarkdownM_run_x27___closed__1));
v___x_1322_ = l_Lean_Doc_joinInlines(v_fst_1316_);
lean_dec(v_fst_1316_);
v___x_1323_ = lean_array_to_list(v___x_1322_);
v___x_1324_ = l_String_intercalate(v___x_1321_, v___x_1323_);
lean_inc_ref(v_name_1309_);
if (v_isShared_1320_ == 0)
{
lean_ctor_set(v___x_1319_, 1, v___x_1324_);
lean_ctor_set(v___x_1319_, 0, v_name_1309_);
v___x_1326_ = v___x_1319_;
goto v_reusejp_1325_;
}
else
{
lean_object* v_reuseFailAlloc_1336_; 
v_reuseFailAlloc_1336_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v_reuseFailAlloc_1336_, 0, v_name_1309_);
lean_ctor_set(v_reuseFailAlloc_1336_, 1, v___x_1324_);
v___x_1326_ = v_reuseFailAlloc_1336_;
goto v_reusejp_1325_;
}
v_reusejp_1325_:
{
lean_object* v___x_1327_; lean_object* v___x_1328_; lean_object* v___x_1329_; lean_object* v___x_1330_; lean_object* v___x_1331_; lean_object* v___x_1332_; lean_object* v___x_1333_; lean_object* v___x_1334_; lean_object* v___x_1335_; 
v___x_1327_ = lean_array_push(v_snd_1317_, v___x_1326_);
v___x_1328_ = ((lean_object*)(l_List_mapTR_loop___at___00Lean_Doc_MarkdownM_run_x27_spec__0___closed__0));
v___x_1329_ = lean_string_append(v___x_1328_, v_name_1309_);
lean_dec_ref(v_name_1309_);
v___x_1330_ = ((lean_object*)(l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__33));
v___x_1331_ = lean_string_append(v___x_1329_, v___x_1330_);
v___x_1332_ = lean_unsigned_to_nat(1u);
v___x_1333_ = lean_mk_empty_array_with_capacity(v___x_1332_);
v___x_1334_ = lean_array_push(v___x_1333_, v___x_1331_);
v___x_1335_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v___x_1335_, 0, v___x_1334_);
lean_ctor_set(v___x_1335_, 1, v___x_1327_);
return v___x_1335_;
}
}
}
case 8:
{
lean_object* v_alt_1338_; lean_object* v_url_1339_; lean_object* v___x_1340_; lean_object* v___x_1341_; lean_object* v___x_1342_; lean_object* v___x_1343_; lean_object* v___x_1344_; lean_object* v___x_1345_; lean_object* v___x_1346_; lean_object* v___x_1347_; lean_object* v___x_1348_; lean_object* v___x_1349_; lean_object* v___x_1350_; lean_object* v___x_1351_; 
lean_dec_ref(v_x_1103_);
lean_dec_ref(v_inst_1102_);
v_alt_1338_ = lean_ctor_get(v_x_1104_, 0);
lean_inc_ref(v_alt_1338_);
v_url_1339_ = lean_ctor_get(v_x_1104_, 1);
lean_inc_ref(v_url_1339_);
lean_dec_ref(v_x_1104_);
v___x_1340_ = ((lean_object*)(l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__34));
v___x_1341_ = l___private_Lean_DocString_Markdown_0__Lean_Doc_escape(v_alt_1338_);
lean_dec_ref(v_alt_1338_);
v___x_1342_ = lean_string_append(v___x_1340_, v___x_1341_);
lean_dec_ref(v___x_1341_);
v___x_1343_ = ((lean_object*)(l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__30));
v___x_1344_ = lean_string_append(v___x_1342_, v___x_1343_);
v___x_1345_ = lean_string_append(v___x_1344_, v_url_1339_);
lean_dec_ref(v_url_1339_);
v___x_1346_ = ((lean_object*)(l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__31));
v___x_1347_ = lean_string_append(v___x_1345_, v___x_1346_);
v___x_1348_ = lean_unsigned_to_nat(1u);
v___x_1349_ = lean_mk_empty_array_with_capacity(v___x_1348_);
v___x_1350_ = lean_array_push(v___x_1349_, v___x_1347_);
v___x_1351_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v___x_1351_, 0, v___x_1350_);
lean_ctor_set(v___x_1351_, 1, v_a_1105_);
return v___x_1351_;
}
case 9:
{
lean_object* v_content_1352_; lean_object* v___x_1353_; size_t v_sz_1354_; size_t v___x_1355_; lean_object* v___x_5254__overap_1356_; lean_object* v___x_1357_; lean_object* v_fst_1358_; lean_object* v_snd_1359_; lean_object* v___x_1361_; uint8_t v_isShared_1362_; uint8_t v_isSharedCheck_1367_; 
v_content_1352_ = lean_ctor_get(v_x_1104_, 0);
lean_inc_ref(v_content_1352_);
lean_dec_ref(v_x_1104_);
v___x_1353_ = lean_alloc_closure((void*)(l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg), 4, 2);
lean_closure_set(v___x_1353_, 0, v_inst_1102_);
lean_closure_set(v___x_1353_, 1, v_x_1103_);
v_sz_1354_ = lean_array_size(v_content_1352_);
v___x_1355_ = ((size_t)0ULL);
v___x_5254__overap_1356_ = l___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map(lean_box(0), lean_box(0), lean_box(0), v___x_1116_, v___x_1353_, v_sz_1354_, v___x_1355_, v_content_1352_);
v___x_1357_ = lean_apply_1(v___x_5254__overap_1356_, v_a_1105_);
v_fst_1358_ = lean_ctor_get(v___x_1357_, 0);
v_snd_1359_ = lean_ctor_get(v___x_1357_, 1);
v_isSharedCheck_1367_ = !lean_is_exclusive(v___x_1357_);
if (v_isSharedCheck_1367_ == 0)
{
v___x_1361_ = v___x_1357_;
v_isShared_1362_ = v_isSharedCheck_1367_;
goto v_resetjp_1360_;
}
else
{
lean_inc(v_snd_1359_);
lean_inc(v_fst_1358_);
lean_dec(v___x_1357_);
v___x_1361_ = lean_box(0);
v_isShared_1362_ = v_isSharedCheck_1367_;
goto v_resetjp_1360_;
}
v_resetjp_1360_:
{
lean_object* v___x_1363_; lean_object* v___x_1365_; 
v___x_1363_ = l_Lean_Doc_joinInlines(v_fst_1358_);
lean_dec(v_fst_1358_);
if (v_isShared_1362_ == 0)
{
lean_ctor_set(v___x_1361_, 0, v___x_1363_);
v___x_1365_ = v___x_1361_;
goto v_reusejp_1364_;
}
else
{
lean_object* v_reuseFailAlloc_1366_; 
v_reuseFailAlloc_1366_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v_reuseFailAlloc_1366_, 0, v___x_1363_);
lean_ctor_set(v_reuseFailAlloc_1366_, 1, v_snd_1359_);
v___x_1365_ = v_reuseFailAlloc_1366_;
goto v_reusejp_1364_;
}
v_reusejp_1364_:
{
return v___x_1365_;
}
}
}
default: 
{
lean_object* v_container_1368_; lean_object* v_content_1369_; lean_object* v___x_1370_; lean_object* v___x_1371_; 
v_container_1368_ = lean_ctor_get(v_x_1104_, 0);
lean_inc(v_container_1368_);
v_content_1369_ = lean_ctor_get(v_x_1104_, 1);
lean_inc_ref(v_content_1369_);
lean_dec_ref(v_x_1104_);
lean_inc_ref(v_inst_1102_);
v___x_1370_ = lean_alloc_closure((void*)(l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg), 4, 2);
lean_closure_set(v___x_1370_, 0, v_inst_1102_);
lean_closure_set(v___x_1370_, 1, v_x_1103_);
v___x_1371_ = lean_apply_4(v_inst_1102_, v___x_1370_, v_container_1368_, v_content_1369_, v_a_1105_);
return v___x_1371_;
}
}
v___jp_1106_:
{
lean_object* v___x_1109_; lean_object* v___x_1110_; 
v___x_1109_ = l_Lean_Doc_joinInlines(v_pieces_1107_);
lean_dec_ref(v_pieces_1107_);
v___x_1110_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v___x_1110_, 0, v___x_1109_);
lean_ctor_set(v___x_1110_, 1, v___y_1108_);
return v___x_1110_;
}
v___jp_1111_:
{
lean_object* v___x_1114_; lean_object* v___x_1115_; 
v___x_1114_ = l_Lean_Doc_joinInlines(v_pieces_1112_);
lean_dec_ref(v_pieces_1112_);
v___x_1115_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v___x_1115_, 0, v___x_1114_);
lean_ctor_set(v___x_1115_, 1, v___y_1113_);
return v___x_1115_;
}
}
}
LEAN_EXPORT lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown(lean_object* v_i_1372_, lean_object* v_inst_1373_, lean_object* v_x_1374_, lean_object* v_x_1375_, lean_object* v_a_1376_){
_start:
{
lean_object* v___x_1377_; 
v___x_1377_ = l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg(v_inst_1373_, v_x_1374_, v_x_1375_, v_a_1376_);
return v___x_1377_;
}
}
LEAN_EXPORT lean_object* l_Lean_Doc_instToMarkdownInlineOfMarkdownInline___private__1___redArg(lean_object* v_inst_1378_, lean_object* v_a_1379_, lean_object* v_a_1380_){
_start:
{
lean_object* v___x_1381_; lean_object* v___x_1382_; 
v___x_1381_ = ((lean_object*)(l_Lean_Doc_MarkdownM_instInhabitedInlineCtx_default___closed__0));
v___x_1382_ = l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg(v_inst_1378_, v___x_1381_, v_a_1379_, v_a_1380_);
return v___x_1382_;
}
}
LEAN_EXPORT lean_object* l_Lean_Doc_instToMarkdownInlineOfMarkdownInline___private__1(lean_object* v_i_1383_, lean_object* v_inst_1384_, lean_object* v_a_1385_, lean_object* v_a_1386_){
_start:
{
lean_object* v___x_1387_; lean_object* v___x_1388_; 
v___x_1387_ = ((lean_object*)(l_Lean_Doc_MarkdownM_instInhabitedInlineCtx_default___closed__0));
v___x_1388_ = l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg(v_inst_1384_, v___x_1387_, v_a_1385_, v_a_1386_);
return v___x_1388_;
}
}
LEAN_EXPORT lean_object* l_Lean_Doc_instToMarkdownInlineOfMarkdownInline___redArg(lean_object* v_inst_1389_){
_start:
{
lean_object* v___x_1390_; 
v___x_1390_ = lean_alloc_closure((void*)(l_Lean_Doc_instToMarkdownInlineOfMarkdownInline___private__1), 4, 2);
lean_closure_set(v___x_1390_, 0, lean_box(0));
lean_closure_set(v___x_1390_, 1, v_inst_1389_);
return v___x_1390_;
}
}
LEAN_EXPORT lean_object* l_Lean_Doc_instToMarkdownInlineOfMarkdownInline(lean_object* v_i_1391_, lean_object* v_inst_1392_){
_start:
{
lean_object* v___x_1393_; 
v___x_1393_ = lean_alloc_closure((void*)(l_Lean_Doc_instToMarkdownInlineOfMarkdownInline___private__1), 4, 2);
lean_closure_set(v___x_1393_, 0, lean_box(0));
lean_closure_set(v___x_1393_, 1, v_inst_1392_);
return v___x_1393_;
}
}
LEAN_EXPORT lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_blockMarkdown___redArg___lam__1(uint32_t v___x_1394_, lean_object* v_s_1395_){
_start:
{
lean_object* v___x_1396_; 
v___x_1396_ = lean_string_push(v_s_1395_, v___x_1394_);
return v___x_1396_;
}
}
LEAN_EXPORT lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_blockMarkdown___redArg___lam__1___boxed(lean_object* v___x_1397_, lean_object* v_s_1398_){
_start:
{
uint32_t v___x_3198__boxed_1399_; lean_object* v_res_1400_; 
v___x_3198__boxed_1399_ = lean_unbox_uint32(v___x_1397_);
lean_dec(v___x_1397_);
v_res_1400_ = l___private_Lean_DocString_Markdown_0__Lean_Doc_blockMarkdown___redArg___lam__1(v___x_3198__boxed_1399_, v_s_1398_);
return v_res_1400_;
}
}
static lean_object* _init_l___private_Lean_DocString_Markdown_0__Lean_Doc_blockMarkdown___redArg___lam__2___closed__1(void){
_start:
{
lean_object* v___x_1404_; lean_object* v___f_1405_; 
v___x_1404_ = l___private_Lean_DocString_Markdown_0__Lean_Doc_markerPrefixSpecial___closed__0___boxed__const__1;
v___f_1405_ = lean_alloc_closure((void*)(l___private_Lean_DocString_Markdown_0__Lean_Doc_blockMarkdown___redArg___lam__1___boxed), 2, 1);
lean_closure_set(v___f_1405_, 0, v___x_1404_);
return v___f_1405_;
}
}
LEAN_EXPORT lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_blockMarkdown___redArg___lam__2(lean_object* v_inst_1406_, lean_object* v_inst_1407_, lean_object* v___x_1408_, lean_object* v___x_1409_, lean_object* v_a_1410_, lean_object* v_x_1411_, lean_object* v___y_1412_, lean_object* v___y_1413_){
_start:
{
lean_object* v___x_1414_; size_t v_sz_1415_; size_t v___x_1416_; lean_object* v___x_3142__overap_1417_; lean_object* v___x_1418_; lean_object* v_fst_1419_; lean_object* v_snd_1420_; lean_object* v___x_1422_; uint8_t v_isShared_1423_; uint8_t v_isSharedCheck_1448_; 
v___x_1414_ = lean_alloc_closure((void*)(l___private_Lean_DocString_Markdown_0__Lean_Doc_blockMarkdown___redArg), 4, 2);
lean_closure_set(v___x_1414_, 0, v_inst_1406_);
lean_closure_set(v___x_1414_, 1, v_inst_1407_);
v_sz_1415_ = lean_array_size(v_a_1410_);
v___x_1416_ = ((size_t)0ULL);
v___x_3142__overap_1417_ = l___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map(lean_box(0), lean_box(0), lean_box(0), v___x_1408_, v___x_1414_, v_sz_1415_, v___x_1416_, v_a_1410_);
v___x_1418_ = lean_apply_1(v___x_3142__overap_1417_, v___y_1413_);
v_fst_1419_ = lean_ctor_get(v___x_1418_, 0);
v_snd_1420_ = lean_ctor_get(v___x_1418_, 1);
v_isSharedCheck_1448_ = !lean_is_exclusive(v___x_1418_);
if (v_isSharedCheck_1448_ == 0)
{
v___x_1422_ = v___x_1418_;
v_isShared_1423_ = v_isSharedCheck_1448_;
goto v_resetjp_1421_;
}
else
{
lean_inc(v_snd_1420_);
lean_inc(v_fst_1419_);
lean_dec(v___x_1418_);
v___x_1422_ = lean_box(0);
v_isShared_1423_ = v_isSharedCheck_1448_;
goto v_resetjp_1421_;
}
v_resetjp_1421_:
{
lean_object* v_fst_1424_; lean_object* v_snd_1425_; lean_object* v___x_1427_; uint8_t v_isShared_1428_; uint8_t v_isSharedCheck_1447_; 
v_fst_1424_ = lean_ctor_get(v___y_1412_, 0);
v_snd_1425_ = lean_ctor_get(v___y_1412_, 1);
v_isSharedCheck_1447_ = !lean_is_exclusive(v___y_1412_);
if (v_isSharedCheck_1447_ == 0)
{
v___x_1427_ = v___y_1412_;
v_isShared_1428_ = v_isSharedCheck_1447_;
goto v_resetjp_1426_;
}
else
{
lean_inc(v_snd_1425_);
lean_inc(v_fst_1424_);
lean_dec(v___y_1412_);
v___x_1427_ = lean_box(0);
v_isShared_1428_ = v_isSharedCheck_1447_;
goto v_resetjp_1426_;
}
v_resetjp_1426_:
{
lean_object* v___x_1429_; lean_object* v___x_1430_; lean_object* v___x_1431_; lean_object* v___x_1432_; lean_object* v___f_1433_; lean_object* v___x_1434_; lean_object* v___x_1435_; lean_object* v___x_1436_; lean_object* v___x_1437_; lean_object* v___x_1438_; lean_object* v___x_1439_; lean_object* v___x_1441_; 
lean_inc(v_snd_1425_);
v___x_1429_ = l_Nat_reprFast(v_snd_1425_);
v___x_1430_ = ((lean_object*)(l___private_Lean_DocString_Markdown_0__Lean_Doc_blockMarkdown___redArg___lam__2___closed__0));
v___x_1431_ = lean_string_append(v___x_1429_, v___x_1430_);
v___x_1432_ = ((lean_object*)(l___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Lean_Doc_joinBlocks_spec__0___closed__0));
v___f_1433_ = lean_obj_once(&l___private_Lean_DocString_Markdown_0__Lean_Doc_blockMarkdown___redArg___lam__2___closed__1, &l___private_Lean_DocString_Markdown_0__Lean_Doc_blockMarkdown___redArg___lam__2___closed__1_once, _init_l___private_Lean_DocString_Markdown_0__Lean_Doc_blockMarkdown___redArg___lam__2___closed__1);
v___x_1434_ = lean_string_length(v___x_1431_);
v___x_1435_ = l___private_Init_Data_Nat_Basic_0__Nat_repeatTR_loop(lean_box(0), v___f_1433_, v___x_1434_, v___x_1432_);
v___x_1436_ = l_Lean_Doc_joinBlocks(v_fst_1419_);
lean_dec(v_fst_1419_);
v___x_1437_ = l_Lean_Doc_prefixListLines(v___x_1431_, v___x_1435_, v___x_1436_);
lean_dec_ref(v___x_1436_);
v___x_1438_ = lean_array_push(v_fst_1424_, v___x_1437_);
v___x_1439_ = lean_nat_add(v_snd_1425_, v___x_1409_);
lean_dec(v_snd_1425_);
if (v_isShared_1428_ == 0)
{
lean_ctor_set(v___x_1427_, 1, v___x_1439_);
lean_ctor_set(v___x_1427_, 0, v___x_1438_);
v___x_1441_ = v___x_1427_;
goto v_reusejp_1440_;
}
else
{
lean_object* v_reuseFailAlloc_1446_; 
v_reuseFailAlloc_1446_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v_reuseFailAlloc_1446_, 0, v___x_1438_);
lean_ctor_set(v_reuseFailAlloc_1446_, 1, v___x_1439_);
v___x_1441_ = v_reuseFailAlloc_1446_;
goto v_reusejp_1440_;
}
v_reusejp_1440_:
{
lean_object* v___x_1442_; lean_object* v___x_1444_; 
v___x_1442_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v___x_1442_, 0, v___x_1441_);
if (v_isShared_1423_ == 0)
{
lean_ctor_set(v___x_1422_, 0, v___x_1442_);
v___x_1444_ = v___x_1422_;
goto v_reusejp_1443_;
}
else
{
lean_object* v_reuseFailAlloc_1445_; 
v_reuseFailAlloc_1445_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v_reuseFailAlloc_1445_, 0, v___x_1442_);
lean_ctor_set(v_reuseFailAlloc_1445_, 1, v_snd_1420_);
v___x_1444_ = v_reuseFailAlloc_1445_;
goto v_reusejp_1443_;
}
v_reusejp_1443_:
{
return v___x_1444_;
}
}
}
}
}
}
LEAN_EXPORT lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_blockMarkdown___redArg___lam__2___boxed(lean_object* v_inst_1449_, lean_object* v_inst_1450_, lean_object* v___x_1451_, lean_object* v___x_1452_, lean_object* v_a_1453_, lean_object* v_x_1454_, lean_object* v___y_1455_, lean_object* v___y_1456_){
_start:
{
lean_object* v_res_1457_; 
v_res_1457_ = l___private_Lean_DocString_Markdown_0__Lean_Doc_blockMarkdown___redArg___lam__2(v_inst_1449_, v_inst_1450_, v___x_1451_, v___x_1452_, v_a_1453_, v_x_1454_, v___y_1455_, v___y_1456_);
lean_dec(v___x_1452_);
return v_res_1457_;
}
}
LEAN_EXPORT lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_blockMarkdown___redArg___lam__3(lean_object* v_inst_1463_, lean_object* v_inst_1464_, lean_object* v___x_1465_, lean_object* v_item_1466_, lean_object* v___y_1467_){
_start:
{
lean_object* v___x_1468_; lean_object* v_term_1469_; lean_object* v_desc_1470_; lean_object* v___x_1471_; lean_object* v___x_1472_; lean_object* v_fst_1473_; lean_object* v_snd_1474_; lean_object* v___x_1475_; size_t v_sz_1476_; size_t v___x_1477_; lean_object* v___x_3172__overap_1478_; lean_object* v___x_1479_; lean_object* v_fst_1480_; lean_object* v_snd_1481_; lean_object* v___x_1483_; uint8_t v_isShared_1484_; uint8_t v_isSharedCheck_1508_; 
v___x_1468_ = ((lean_object*)(l_Lean_Doc_MarkdownM_instInhabitedInlineCtx_default___closed__0));
v_term_1469_ = lean_ctor_get(v_item_1466_, 0);
lean_inc_ref(v_term_1469_);
v_desc_1470_ = lean_ctor_get(v_item_1466_, 1);
lean_inc_ref_n(v_desc_1470_, 2);
lean_dec_ref(v_item_1466_);
v___x_1471_ = lean_alloc_ctor(2, 1, 0);
lean_ctor_set(v___x_1471_, 0, v_term_1469_);
lean_inc_ref(v_inst_1463_);
v___x_1472_ = l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg(v_inst_1463_, v___x_1468_, v___x_1471_, v___y_1467_);
v_fst_1473_ = lean_ctor_get(v___x_1472_, 0);
lean_inc(v_fst_1473_);
v_snd_1474_ = lean_ctor_get(v___x_1472_, 1);
lean_inc(v_snd_1474_);
lean_dec_ref(v___x_1472_);
v___x_1475_ = lean_alloc_closure((void*)(l___private_Lean_DocString_Markdown_0__Lean_Doc_blockMarkdown___redArg), 4, 2);
lean_closure_set(v___x_1475_, 0, v_inst_1463_);
lean_closure_set(v___x_1475_, 1, v_inst_1464_);
v_sz_1476_ = lean_array_size(v_desc_1470_);
v___x_1477_ = ((size_t)0ULL);
v___x_3172__overap_1478_ = l___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map(lean_box(0), lean_box(0), lean_box(0), v___x_1465_, v___x_1475_, v_sz_1476_, v___x_1477_, v_desc_1470_);
v___x_1479_ = lean_apply_1(v___x_3172__overap_1478_, v_snd_1474_);
v_fst_1480_ = lean_ctor_get(v___x_1479_, 0);
v_snd_1481_ = lean_ctor_get(v___x_1479_, 1);
v_isSharedCheck_1508_ = !lean_is_exclusive(v___x_1479_);
if (v_isSharedCheck_1508_ == 0)
{
v___x_1483_ = v___x_1479_;
v_isShared_1484_ = v_isSharedCheck_1508_;
goto v_resetjp_1482_;
}
else
{
lean_inc(v_snd_1481_);
lean_inc(v_fst_1480_);
lean_dec(v___x_1479_);
v___x_1483_ = lean_box(0);
v_isShared_1484_ = v_isSharedCheck_1508_;
goto v_resetjp_1482_;
}
v_resetjp_1482_:
{
lean_object* v___y_1486_; lean_object* v___x_1493_; lean_object* v___x_1494_; lean_object* v___x_1495_; lean_object* v___x_1496_; lean_object* v___x_1497_; lean_object* v___x_1498_; lean_object* v___x_1499_; lean_object* v___x_1500_; lean_object* v___x_1501_; uint8_t v___x_1502_; 
v___x_1493_ = lean_unsigned_to_nat(1u);
v___x_1494_ = lean_mk_empty_array_with_capacity(v___x_1493_);
v___x_1495_ = ((lean_object*)(l___private_Lean_DocString_Markdown_0__Lean_Doc_blockMarkdown___redArg___lam__3___closed__1));
v___x_1496_ = lean_unsigned_to_nat(2u);
v___x_1497_ = lean_mk_empty_array_with_capacity(v___x_1496_);
v___x_1498_ = lean_array_push(v___x_1497_, v_fst_1473_);
v___x_1499_ = lean_array_push(v___x_1498_, v___x_1495_);
v___x_1500_ = l_Lean_Doc_joinInlines(v___x_1499_);
lean_dec_ref(v___x_1499_);
v___x_1501_ = lean_array_get_size(v_desc_1470_);
lean_dec_ref(v_desc_1470_);
v___x_1502_ = lean_nat_dec_le(v___x_1501_, v___x_1493_);
if (v___x_1502_ == 0)
{
lean_object* v___x_1503_; lean_object* v___x_1504_; lean_object* v___x_1505_; 
v___x_1503_ = lean_array_push(v___x_1494_, v___x_1500_);
v___x_1504_ = l_Array_append___redArg(v___x_1503_, v_fst_1480_);
lean_dec(v_fst_1480_);
v___x_1505_ = l_Lean_Doc_joinBlocks(v___x_1504_);
lean_dec_ref(v___x_1504_);
v___y_1486_ = v___x_1505_;
goto v___jp_1485_;
}
else
{
lean_object* v___x_1506_; lean_object* v___x_1507_; 
lean_dec_ref(v___x_1494_);
v___x_1506_ = l_Lean_Doc_joinBlocks(v_fst_1480_);
lean_dec(v_fst_1480_);
v___x_1507_ = l_Array_append___redArg(v___x_1500_, v___x_1506_);
lean_dec_ref(v___x_1506_);
v___y_1486_ = v___x_1507_;
goto v___jp_1485_;
}
v___jp_1485_:
{
lean_object* v___x_1487_; lean_object* v___x_1488_; lean_object* v___x_1489_; lean_object* v___x_1491_; 
v___x_1487_ = ((lean_object*)(l___private_Lean_DocString_Markdown_0__Lean_Doc_blockMarkdown___redArg___lam__0___closed__0));
v___x_1488_ = ((lean_object*)(l___private_Lean_DocString_Markdown_0__Lean_Doc_blockMarkdown___redArg___lam__0___closed__1));
v___x_1489_ = l_Lean_Doc_prefixListLines(v___x_1487_, v___x_1488_, v___y_1486_);
lean_dec_ref(v___y_1486_);
if (v_isShared_1484_ == 0)
{
lean_ctor_set(v___x_1483_, 0, v___x_1489_);
v___x_1491_ = v___x_1483_;
goto v_reusejp_1490_;
}
else
{
lean_object* v_reuseFailAlloc_1492_; 
v_reuseFailAlloc_1492_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v_reuseFailAlloc_1492_, 0, v___x_1489_);
lean_ctor_set(v_reuseFailAlloc_1492_, 1, v_snd_1481_);
v___x_1491_ = v_reuseFailAlloc_1492_;
goto v_reusejp_1490_;
}
v_reusejp_1490_:
{
return v___x_1491_;
}
}
}
}
}
LEAN_EXPORT lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_blockMarkdown___redArg(lean_object* v_inst_1510_, lean_object* v_inst_1511_, lean_object* v_x_1512_, lean_object* v_a_1513_){
_start:
{
lean_object* v___x_1514_; 
v___x_1514_ = ((lean_object*)(l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__19));
switch(lean_obj_tag(v_x_1512_))
{
case 0:
{
lean_object* v_contents_1515_; lean_object* v___x_1517_; uint8_t v_isShared_1518_; uint8_t v_isSharedCheck_1524_; 
lean_dec_ref(v_inst_1511_);
v_contents_1515_ = lean_ctor_get(v_x_1512_, 0);
v_isSharedCheck_1524_ = !lean_is_exclusive(v_x_1512_);
if (v_isSharedCheck_1524_ == 0)
{
v___x_1517_ = v_x_1512_;
v_isShared_1518_ = v_isSharedCheck_1524_;
goto v_resetjp_1516_;
}
else
{
lean_inc(v_contents_1515_);
lean_dec(v_x_1512_);
v___x_1517_ = lean_box(0);
v_isShared_1518_ = v_isSharedCheck_1524_;
goto v_resetjp_1516_;
}
v_resetjp_1516_:
{
lean_object* v___x_1519_; lean_object* v___x_1521_; 
v___x_1519_ = ((lean_object*)(l_Lean_Doc_MarkdownM_instInhabitedInlineCtx_default___closed__0));
if (v_isShared_1518_ == 0)
{
lean_ctor_set_tag(v___x_1517_, 9);
v___x_1521_ = v___x_1517_;
goto v_reusejp_1520_;
}
else
{
lean_object* v_reuseFailAlloc_1523_; 
v_reuseFailAlloc_1523_ = lean_alloc_ctor(9, 1, 0);
lean_ctor_set(v_reuseFailAlloc_1523_, 0, v_contents_1515_);
v___x_1521_ = v_reuseFailAlloc_1523_;
goto v_reusejp_1520_;
}
v_reusejp_1520_:
{
lean_object* v___x_1522_; 
v___x_1522_ = l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg(v_inst_1510_, v___x_1519_, v___x_1521_, v_a_1513_);
return v___x_1522_;
}
}
}
case 1:
{
lean_object* v_content_1525_; lean_object* v___x_1526_; lean_object* v___x_1527_; 
lean_dec_ref(v_inst_1511_);
lean_dec_ref(v_inst_1510_);
v_content_1525_ = lean_ctor_get(v_x_1512_, 0);
lean_inc_ref(v_content_1525_);
lean_dec_ref(v_x_1512_);
v___x_1526_ = l___private_Lean_DocString_Markdown_0__Lean_Doc_codeBlockLines(v_content_1525_);
v___x_1527_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v___x_1527_, 0, v___x_1526_);
lean_ctor_set(v___x_1527_, 1, v_a_1513_);
return v___x_1527_;
}
case 2:
{
lean_object* v_items_1528_; lean_object* v___f_1529_; size_t v_sz_1530_; size_t v___x_1531_; lean_object* v___x_3079__overap_1532_; lean_object* v___x_1533_; lean_object* v_fst_1534_; lean_object* v_snd_1535_; lean_object* v___x_1537_; uint8_t v_isShared_1538_; uint8_t v_isSharedCheck_1543_; 
v_items_1528_ = lean_ctor_get(v_x_1512_, 0);
lean_inc_ref(v_items_1528_);
lean_dec_ref(v_x_1512_);
v___f_1529_ = lean_alloc_closure((void*)(l___private_Lean_DocString_Markdown_0__Lean_Doc_blockMarkdown___redArg___lam__0), 5, 3);
lean_closure_set(v___f_1529_, 0, v_inst_1510_);
lean_closure_set(v___f_1529_, 1, v_inst_1511_);
lean_closure_set(v___f_1529_, 2, v___x_1514_);
v_sz_1530_ = lean_array_size(v_items_1528_);
v___x_1531_ = ((size_t)0ULL);
v___x_3079__overap_1532_ = l___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map(lean_box(0), lean_box(0), lean_box(0), v___x_1514_, v___f_1529_, v_sz_1530_, v___x_1531_, v_items_1528_);
v___x_1533_ = lean_apply_1(v___x_3079__overap_1532_, v_a_1513_);
v_fst_1534_ = lean_ctor_get(v___x_1533_, 0);
v_snd_1535_ = lean_ctor_get(v___x_1533_, 1);
v_isSharedCheck_1543_ = !lean_is_exclusive(v___x_1533_);
if (v_isSharedCheck_1543_ == 0)
{
v___x_1537_ = v___x_1533_;
v_isShared_1538_ = v_isSharedCheck_1543_;
goto v_resetjp_1536_;
}
else
{
lean_inc(v_snd_1535_);
lean_inc(v_fst_1534_);
lean_dec(v___x_1533_);
v___x_1537_ = lean_box(0);
v_isShared_1538_ = v_isSharedCheck_1543_;
goto v_resetjp_1536_;
}
v_resetjp_1536_:
{
lean_object* v___x_1539_; lean_object* v___x_1541_; 
v___x_1539_ = l_Lean_Doc_joinBlocks(v_fst_1534_);
lean_dec(v_fst_1534_);
if (v_isShared_1538_ == 0)
{
lean_ctor_set(v___x_1537_, 0, v___x_1539_);
v___x_1541_ = v___x_1537_;
goto v_reusejp_1540_;
}
else
{
lean_object* v_reuseFailAlloc_1542_; 
v_reuseFailAlloc_1542_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v_reuseFailAlloc_1542_, 0, v___x_1539_);
lean_ctor_set(v_reuseFailAlloc_1542_, 1, v_snd_1535_);
v___x_1541_ = v_reuseFailAlloc_1542_;
goto v_reusejp_1540_;
}
v_reusejp_1540_:
{
return v___x_1541_;
}
}
}
case 3:
{
lean_object* v_start_1544_; lean_object* v_items_1545_; lean_object* v___x_1547_; uint8_t v_isShared_1548_; uint8_t v_isSharedCheck_1575_; 
v_start_1544_ = lean_ctor_get(v_x_1512_, 0);
v_items_1545_ = lean_ctor_get(v_x_1512_, 1);
v_isSharedCheck_1575_ = !lean_is_exclusive(v_x_1512_);
if (v_isSharedCheck_1575_ == 0)
{
v___x_1547_ = v_x_1512_;
v_isShared_1548_ = v_isSharedCheck_1575_;
goto v_resetjp_1546_;
}
else
{
lean_inc(v_items_1545_);
lean_inc(v_start_1544_);
lean_dec(v_x_1512_);
v___x_1547_ = lean_box(0);
v_isShared_1548_ = v_isSharedCheck_1575_;
goto v_resetjp_1546_;
}
v_resetjp_1546_:
{
lean_object* v_out_1549_; lean_object* v___x_1550_; lean_object* v___f_1551_; lean_object* v___y_1553_; lean_object* v___x_1573_; uint8_t v___x_1574_; 
v_out_1549_ = ((lean_object*)(l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__22));
v___x_1550_ = lean_unsigned_to_nat(1u);
v___f_1551_ = lean_alloc_closure((void*)(l___private_Lean_DocString_Markdown_0__Lean_Doc_blockMarkdown___redArg___lam__2___boxed), 8, 4);
lean_closure_set(v___f_1551_, 0, v_inst_1510_);
lean_closure_set(v___f_1551_, 1, v_inst_1511_);
lean_closure_set(v___f_1551_, 2, v___x_1514_);
lean_closure_set(v___f_1551_, 3, v___x_1550_);
v___x_1573_ = l_Int_toNat(v_start_1544_);
lean_dec(v_start_1544_);
v___x_1574_ = lean_nat_dec_le(v___x_1550_, v___x_1573_);
if (v___x_1574_ == 0)
{
lean_dec(v___x_1573_);
v___y_1553_ = v___x_1550_;
goto v___jp_1552_;
}
else
{
v___y_1553_ = v___x_1573_;
goto v___jp_1552_;
}
v___jp_1552_:
{
lean_object* v___x_1555_; 
if (v_isShared_1548_ == 0)
{
lean_ctor_set_tag(v___x_1547_, 0);
lean_ctor_set(v___x_1547_, 1, v___y_1553_);
lean_ctor_set(v___x_1547_, 0, v_out_1549_);
v___x_1555_ = v___x_1547_;
goto v_reusejp_1554_;
}
else
{
lean_object* v_reuseFailAlloc_1572_; 
v_reuseFailAlloc_1572_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v_reuseFailAlloc_1572_, 0, v_out_1549_);
lean_ctor_set(v_reuseFailAlloc_1572_, 1, v___y_1553_);
v___x_1555_ = v_reuseFailAlloc_1572_;
goto v_reusejp_1554_;
}
v_reusejp_1554_:
{
size_t v_sz_1556_; size_t v___x_1557_; lean_object* v___x_2973__overap_1558_; lean_object* v___x_1559_; lean_object* v_fst_1560_; lean_object* v_snd_1561_; lean_object* v_fst_1562_; lean_object* v___x_1564_; uint8_t v_isShared_1565_; uint8_t v_isSharedCheck_1570_; 
v_sz_1556_ = lean_array_size(v_items_1545_);
v___x_1557_ = ((size_t)0ULL);
v___x_2973__overap_1558_ = l___private_Init_Data_Array_Basic_0__Array_forIn_x27Unsafe_loop(lean_box(0), lean_box(0), lean_box(0), v___x_1514_, v_items_1545_, v___f_1551_, v_sz_1556_, v___x_1557_, v___x_1555_);
v___x_1559_ = lean_apply_1(v___x_2973__overap_1558_, v_a_1513_);
v_fst_1560_ = lean_ctor_get(v___x_1559_, 0);
lean_inc(v_fst_1560_);
v_snd_1561_ = lean_ctor_get(v___x_1559_, 1);
lean_inc(v_snd_1561_);
lean_dec_ref(v___x_1559_);
v_fst_1562_ = lean_ctor_get(v_fst_1560_, 0);
v_isSharedCheck_1570_ = !lean_is_exclusive(v_fst_1560_);
if (v_isSharedCheck_1570_ == 0)
{
lean_object* v_unused_1571_; 
v_unused_1571_ = lean_ctor_get(v_fst_1560_, 1);
lean_dec(v_unused_1571_);
v___x_1564_ = v_fst_1560_;
v_isShared_1565_ = v_isSharedCheck_1570_;
goto v_resetjp_1563_;
}
else
{
lean_inc(v_fst_1562_);
lean_dec(v_fst_1560_);
v___x_1564_ = lean_box(0);
v_isShared_1565_ = v_isSharedCheck_1570_;
goto v_resetjp_1563_;
}
v_resetjp_1563_:
{
lean_object* v___x_1566_; lean_object* v___x_1568_; 
v___x_1566_ = l_Lean_Doc_joinBlocks(v_fst_1562_);
lean_dec(v_fst_1562_);
if (v_isShared_1565_ == 0)
{
lean_ctor_set(v___x_1564_, 1, v_snd_1561_);
lean_ctor_set(v___x_1564_, 0, v___x_1566_);
v___x_1568_ = v___x_1564_;
goto v_reusejp_1567_;
}
else
{
lean_object* v_reuseFailAlloc_1569_; 
v_reuseFailAlloc_1569_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v_reuseFailAlloc_1569_, 0, v___x_1566_);
lean_ctor_set(v_reuseFailAlloc_1569_, 1, v_snd_1561_);
v___x_1568_ = v_reuseFailAlloc_1569_;
goto v_reusejp_1567_;
}
v_reusejp_1567_:
{
return v___x_1568_;
}
}
}
}
}
}
case 4:
{
lean_object* v_items_1576_; lean_object* v___f_1577_; size_t v_sz_1578_; size_t v___x_1579_; lean_object* v___x_3085__overap_1580_; lean_object* v___x_1581_; lean_object* v_fst_1582_; lean_object* v_snd_1583_; lean_object* v___x_1585_; uint8_t v_isShared_1586_; uint8_t v_isSharedCheck_1591_; 
v_items_1576_ = lean_ctor_get(v_x_1512_, 0);
lean_inc_ref(v_items_1576_);
lean_dec_ref(v_x_1512_);
v___f_1577_ = lean_alloc_closure((void*)(l___private_Lean_DocString_Markdown_0__Lean_Doc_blockMarkdown___redArg___lam__3), 5, 3);
lean_closure_set(v___f_1577_, 0, v_inst_1510_);
lean_closure_set(v___f_1577_, 1, v_inst_1511_);
lean_closure_set(v___f_1577_, 2, v___x_1514_);
v_sz_1578_ = lean_array_size(v_items_1576_);
v___x_1579_ = ((size_t)0ULL);
v___x_3085__overap_1580_ = l___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map(lean_box(0), lean_box(0), lean_box(0), v___x_1514_, v___f_1577_, v_sz_1578_, v___x_1579_, v_items_1576_);
v___x_1581_ = lean_apply_1(v___x_3085__overap_1580_, v_a_1513_);
v_fst_1582_ = lean_ctor_get(v___x_1581_, 0);
v_snd_1583_ = lean_ctor_get(v___x_1581_, 1);
v_isSharedCheck_1591_ = !lean_is_exclusive(v___x_1581_);
if (v_isSharedCheck_1591_ == 0)
{
v___x_1585_ = v___x_1581_;
v_isShared_1586_ = v_isSharedCheck_1591_;
goto v_resetjp_1584_;
}
else
{
lean_inc(v_snd_1583_);
lean_inc(v_fst_1582_);
lean_dec(v___x_1581_);
v___x_1585_ = lean_box(0);
v_isShared_1586_ = v_isSharedCheck_1591_;
goto v_resetjp_1584_;
}
v_resetjp_1584_:
{
lean_object* v___x_1587_; lean_object* v___x_1589_; 
v___x_1587_ = l_Lean_Doc_joinBlocks(v_fst_1582_);
lean_dec(v_fst_1582_);
if (v_isShared_1586_ == 0)
{
lean_ctor_set(v___x_1585_, 0, v___x_1587_);
v___x_1589_ = v___x_1585_;
goto v_reusejp_1588_;
}
else
{
lean_object* v_reuseFailAlloc_1590_; 
v_reuseFailAlloc_1590_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v_reuseFailAlloc_1590_, 0, v___x_1587_);
lean_ctor_set(v_reuseFailAlloc_1590_, 1, v_snd_1583_);
v___x_1589_ = v_reuseFailAlloc_1590_;
goto v_reusejp_1588_;
}
v_reusejp_1588_:
{
return v___x_1589_;
}
}
}
case 5:
{
lean_object* v_items_1592_; lean_object* v___x_1593_; size_t v_sz_1594_; size_t v___x_1595_; lean_object* v___x_3088__overap_1596_; lean_object* v___x_1597_; lean_object* v_fst_1598_; lean_object* v_snd_1599_; lean_object* v___x_1601_; uint8_t v_isShared_1602_; uint8_t v_isSharedCheck_1609_; 
v_items_1592_ = lean_ctor_get(v_x_1512_, 0);
lean_inc_ref(v_items_1592_);
lean_dec_ref(v_x_1512_);
v___x_1593_ = lean_alloc_closure((void*)(l___private_Lean_DocString_Markdown_0__Lean_Doc_blockMarkdown___redArg), 4, 2);
lean_closure_set(v___x_1593_, 0, v_inst_1510_);
lean_closure_set(v___x_1593_, 1, v_inst_1511_);
v_sz_1594_ = lean_array_size(v_items_1592_);
v___x_1595_ = ((size_t)0ULL);
v___x_3088__overap_1596_ = l___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map(lean_box(0), lean_box(0), lean_box(0), v___x_1514_, v___x_1593_, v_sz_1594_, v___x_1595_, v_items_1592_);
v___x_1597_ = lean_apply_1(v___x_3088__overap_1596_, v_a_1513_);
v_fst_1598_ = lean_ctor_get(v___x_1597_, 0);
v_snd_1599_ = lean_ctor_get(v___x_1597_, 1);
v_isSharedCheck_1609_ = !lean_is_exclusive(v___x_1597_);
if (v_isSharedCheck_1609_ == 0)
{
v___x_1601_ = v___x_1597_;
v_isShared_1602_ = v_isSharedCheck_1609_;
goto v_resetjp_1600_;
}
else
{
lean_inc(v_snd_1599_);
lean_inc(v_fst_1598_);
lean_dec(v___x_1597_);
v___x_1601_ = lean_box(0);
v_isShared_1602_ = v_isSharedCheck_1609_;
goto v_resetjp_1600_;
}
v_resetjp_1600_:
{
lean_object* v___x_1603_; lean_object* v___x_1604_; lean_object* v___x_1605_; lean_object* v___x_1607_; 
v___x_1603_ = ((lean_object*)(l___private_Lean_DocString_Markdown_0__Lean_Doc_blockMarkdown___redArg___closed__0));
v___x_1604_ = l_Lean_Doc_joinBlocks(v_fst_1598_);
lean_dec(v_fst_1598_);
v___x_1605_ = l_Lean_Doc_prefixLines(v___x_1603_, v___x_1604_);
if (v_isShared_1602_ == 0)
{
lean_ctor_set(v___x_1601_, 0, v___x_1605_);
v___x_1607_ = v___x_1601_;
goto v_reusejp_1606_;
}
else
{
lean_object* v_reuseFailAlloc_1608_; 
v_reuseFailAlloc_1608_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v_reuseFailAlloc_1608_, 0, v___x_1605_);
lean_ctor_set(v_reuseFailAlloc_1608_, 1, v_snd_1599_);
v___x_1607_ = v_reuseFailAlloc_1608_;
goto v_reusejp_1606_;
}
v_reusejp_1606_:
{
return v___x_1607_;
}
}
}
case 6:
{
lean_object* v_content_1610_; lean_object* v___x_1611_; size_t v_sz_1612_; size_t v___x_1613_; lean_object* v___x_3091__overap_1614_; lean_object* v___x_1615_; lean_object* v_fst_1616_; lean_object* v_snd_1617_; lean_object* v___x_1619_; uint8_t v_isShared_1620_; uint8_t v_isSharedCheck_1625_; 
v_content_1610_ = lean_ctor_get(v_x_1512_, 0);
lean_inc_ref(v_content_1610_);
lean_dec_ref(v_x_1512_);
v___x_1611_ = lean_alloc_closure((void*)(l___private_Lean_DocString_Markdown_0__Lean_Doc_blockMarkdown___redArg), 4, 2);
lean_closure_set(v___x_1611_, 0, v_inst_1510_);
lean_closure_set(v___x_1611_, 1, v_inst_1511_);
v_sz_1612_ = lean_array_size(v_content_1610_);
v___x_1613_ = ((size_t)0ULL);
v___x_3091__overap_1614_ = l___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map(lean_box(0), lean_box(0), lean_box(0), v___x_1514_, v___x_1611_, v_sz_1612_, v___x_1613_, v_content_1610_);
v___x_1615_ = lean_apply_1(v___x_3091__overap_1614_, v_a_1513_);
v_fst_1616_ = lean_ctor_get(v___x_1615_, 0);
v_snd_1617_ = lean_ctor_get(v___x_1615_, 1);
v_isSharedCheck_1625_ = !lean_is_exclusive(v___x_1615_);
if (v_isSharedCheck_1625_ == 0)
{
v___x_1619_ = v___x_1615_;
v_isShared_1620_ = v_isSharedCheck_1625_;
goto v_resetjp_1618_;
}
else
{
lean_inc(v_snd_1617_);
lean_inc(v_fst_1616_);
lean_dec(v___x_1615_);
v___x_1619_ = lean_box(0);
v_isShared_1620_ = v_isSharedCheck_1625_;
goto v_resetjp_1618_;
}
v_resetjp_1618_:
{
lean_object* v___x_1621_; lean_object* v___x_1623_; 
v___x_1621_ = l_Lean_Doc_joinBlocks(v_fst_1616_);
lean_dec(v_fst_1616_);
if (v_isShared_1620_ == 0)
{
lean_ctor_set(v___x_1619_, 0, v___x_1621_);
v___x_1623_ = v___x_1619_;
goto v_reusejp_1622_;
}
else
{
lean_object* v_reuseFailAlloc_1624_; 
v_reuseFailAlloc_1624_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v_reuseFailAlloc_1624_, 0, v___x_1621_);
lean_ctor_set(v_reuseFailAlloc_1624_, 1, v_snd_1617_);
v___x_1623_ = v_reuseFailAlloc_1624_;
goto v_reusejp_1622_;
}
v_reusejp_1622_:
{
return v___x_1623_;
}
}
}
default: 
{
lean_object* v_container_1626_; lean_object* v_content_1627_; lean_object* v___x_1628_; lean_object* v___x_1629_; lean_object* v___x_1630_; lean_object* v___x_1631_; 
v_container_1626_ = lean_ctor_get(v_x_1512_, 0);
lean_inc(v_container_1626_);
v_content_1627_ = lean_ctor_get(v_x_1512_, 1);
lean_inc_ref(v_content_1627_);
lean_dec_ref(v_x_1512_);
v___x_1628_ = ((lean_object*)(l_Lean_Doc_MarkdownM_instInhabitedInlineCtx_default___closed__0));
lean_inc_ref(v_inst_1510_);
v___x_1629_ = lean_alloc_closure((void*)(l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown), 5, 3);
lean_closure_set(v___x_1629_, 0, lean_box(0));
lean_closure_set(v___x_1629_, 1, v_inst_1510_);
lean_closure_set(v___x_1629_, 2, v___x_1628_);
lean_inc_ref(v_inst_1511_);
v___x_1630_ = lean_alloc_closure((void*)(l___private_Lean_DocString_Markdown_0__Lean_Doc_blockMarkdown___redArg), 4, 2);
lean_closure_set(v___x_1630_, 0, v_inst_1510_);
lean_closure_set(v___x_1630_, 1, v_inst_1511_);
v___x_1631_ = lean_apply_5(v_inst_1511_, v___x_1629_, v___x_1630_, v_container_1626_, v_content_1627_, v_a_1513_);
return v___x_1631_;
}
}
}
}
LEAN_EXPORT lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_blockMarkdown___redArg___lam__0(lean_object* v_inst_1632_, lean_object* v_inst_1633_, lean_object* v___x_1634_, lean_object* v_item_1635_, lean_object* v___y_1636_){
_start:
{
lean_object* v___x_1637_; size_t v_sz_1638_; size_t v___x_1639_; lean_object* v___x_3123__overap_1640_; lean_object* v___x_1641_; lean_object* v_fst_1642_; lean_object* v_snd_1643_; lean_object* v___x_1645_; uint8_t v_isShared_1646_; uint8_t v_isSharedCheck_1654_; 
v___x_1637_ = lean_alloc_closure((void*)(l___private_Lean_DocString_Markdown_0__Lean_Doc_blockMarkdown___redArg), 4, 2);
lean_closure_set(v___x_1637_, 0, v_inst_1632_);
lean_closure_set(v___x_1637_, 1, v_inst_1633_);
v_sz_1638_ = lean_array_size(v_item_1635_);
v___x_1639_ = ((size_t)0ULL);
v___x_3123__overap_1640_ = l___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map(lean_box(0), lean_box(0), lean_box(0), v___x_1634_, v___x_1637_, v_sz_1638_, v___x_1639_, v_item_1635_);
v___x_1641_ = lean_apply_1(v___x_3123__overap_1640_, v___y_1636_);
v_fst_1642_ = lean_ctor_get(v___x_1641_, 0);
v_snd_1643_ = lean_ctor_get(v___x_1641_, 1);
v_isSharedCheck_1654_ = !lean_is_exclusive(v___x_1641_);
if (v_isSharedCheck_1654_ == 0)
{
v___x_1645_ = v___x_1641_;
v_isShared_1646_ = v_isSharedCheck_1654_;
goto v_resetjp_1644_;
}
else
{
lean_inc(v_snd_1643_);
lean_inc(v_fst_1642_);
lean_dec(v___x_1641_);
v___x_1645_ = lean_box(0);
v_isShared_1646_ = v_isSharedCheck_1654_;
goto v_resetjp_1644_;
}
v_resetjp_1644_:
{
lean_object* v___x_1647_; lean_object* v___x_1648_; lean_object* v___x_1649_; lean_object* v___x_1650_; lean_object* v___x_1652_; 
v___x_1647_ = ((lean_object*)(l___private_Lean_DocString_Markdown_0__Lean_Doc_blockMarkdown___redArg___lam__0___closed__0));
v___x_1648_ = ((lean_object*)(l___private_Lean_DocString_Markdown_0__Lean_Doc_blockMarkdown___redArg___lam__0___closed__1));
v___x_1649_ = l_Lean_Doc_joinBlocks(v_fst_1642_);
lean_dec(v_fst_1642_);
v___x_1650_ = l_Lean_Doc_prefixListLines(v___x_1647_, v___x_1648_, v___x_1649_);
lean_dec_ref(v___x_1649_);
if (v_isShared_1646_ == 0)
{
lean_ctor_set(v___x_1645_, 0, v___x_1650_);
v___x_1652_ = v___x_1645_;
goto v_reusejp_1651_;
}
else
{
lean_object* v_reuseFailAlloc_1653_; 
v_reuseFailAlloc_1653_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v_reuseFailAlloc_1653_, 0, v___x_1650_);
lean_ctor_set(v_reuseFailAlloc_1653_, 1, v_snd_1643_);
v___x_1652_ = v_reuseFailAlloc_1653_;
goto v_reusejp_1651_;
}
v_reusejp_1651_:
{
return v___x_1652_;
}
}
}
}
LEAN_EXPORT lean_object* l___private_Lean_DocString_Markdown_0__Lean_Doc_blockMarkdown(lean_object* v_i_1655_, lean_object* v_b_1656_, lean_object* v_inst_1657_, lean_object* v_inst_1658_, lean_object* v_x_1659_, lean_object* v_a_1660_){
_start:
{
lean_object* v___x_1661_; 
v___x_1661_ = l___private_Lean_DocString_Markdown_0__Lean_Doc_blockMarkdown___redArg(v_inst_1657_, v_inst_1658_, v_x_1659_, v_a_1660_);
return v___x_1661_;
}
}
LEAN_EXPORT lean_object* l_Lean_Doc_instToMarkdownBlockOfMarkdownInlineOfMarkdownBlock___private__1___redArg(lean_object* v_inst_1662_, lean_object* v_inst_1663_, lean_object* v_a_1664_, lean_object* v_a_1665_){
_start:
{
lean_object* v___x_1666_; 
v___x_1666_ = l___private_Lean_DocString_Markdown_0__Lean_Doc_blockMarkdown___redArg(v_inst_1662_, v_inst_1663_, v_a_1664_, v_a_1665_);
return v___x_1666_;
}
}
LEAN_EXPORT lean_object* l_Lean_Doc_instToMarkdownBlockOfMarkdownInlineOfMarkdownBlock___private__1(lean_object* v_i_1667_, lean_object* v_b_1668_, lean_object* v_inst_1669_, lean_object* v_inst_1670_, lean_object* v_a_1671_, lean_object* v_a_1672_){
_start:
{
lean_object* v___x_1673_; 
v___x_1673_ = l___private_Lean_DocString_Markdown_0__Lean_Doc_blockMarkdown___redArg(v_inst_1669_, v_inst_1670_, v_a_1671_, v_a_1672_);
return v___x_1673_;
}
}
LEAN_EXPORT lean_object* l_Lean_Doc_instToMarkdownBlockOfMarkdownInlineOfMarkdownBlock___redArg(lean_object* v_inst_1674_, lean_object* v_inst_1675_){
_start:
{
lean_object* v___x_1676_; 
v___x_1676_ = lean_alloc_closure((void*)(l_Lean_Doc_instToMarkdownBlockOfMarkdownInlineOfMarkdownBlock___private__1), 6, 4);
lean_closure_set(v___x_1676_, 0, lean_box(0));
lean_closure_set(v___x_1676_, 1, lean_box(0));
lean_closure_set(v___x_1676_, 2, v_inst_1674_);
lean_closure_set(v___x_1676_, 3, v_inst_1675_);
return v___x_1676_;
}
}
LEAN_EXPORT lean_object* l_Lean_Doc_instToMarkdownBlockOfMarkdownInlineOfMarkdownBlock(lean_object* v_i_1677_, lean_object* v_b_1678_, lean_object* v_inst_1679_, lean_object* v_inst_1680_){
_start:
{
lean_object* v___x_1681_; 
v___x_1681_ = lean_alloc_closure((void*)(l_Lean_Doc_instToMarkdownBlockOfMarkdownInlineOfMarkdownBlock___private__1), 6, 4);
lean_closure_set(v___x_1681_, 0, lean_box(0));
lean_closure_set(v___x_1681_, 1, lean_box(0));
lean_closure_set(v___x_1681_, 2, v_inst_1679_);
lean_closure_set(v___x_1681_, 3, v_inst_1680_);
return v___x_1681_;
}
}
static lean_object* _init_l_Lean_Doc_partMarkdown___redArg___closed__0___boxed__const__1(void){
_start:
{
uint32_t v___x_1682_; lean_object* v___x_1683_; 
v___x_1682_ = 35;
v___x_1683_ = lean_box_uint32(v___x_1682_);
return v___x_1683_;
}
}
static lean_object* _init_l_Lean_Doc_partMarkdown___redArg___closed__0(void){
_start:
{
lean_object* v___x_1684_; lean_object* v___f_1685_; 
v___x_1684_ = l_Lean_Doc_partMarkdown___redArg___closed__0___boxed__const__1;
v___f_1685_ = lean_alloc_closure((void*)(l___private_Lean_DocString_Markdown_0__Lean_Doc_blockMarkdown___redArg___lam__1___boxed), 2, 1);
lean_closure_set(v___f_1685_, 0, v___x_1684_);
return v___f_1685_;
}
}
LEAN_EXPORT lean_object* l_Lean_Doc_partMarkdown___redArg___boxed(lean_object* v_inst_1686_, lean_object* v_inst_1687_, lean_object* v_level_1688_, lean_object* v_part_1689_, lean_object* v_a_1690_){
_start:
{
lean_object* v_res_1691_; 
v_res_1691_ = l_Lean_Doc_partMarkdown___redArg(v_inst_1686_, v_inst_1687_, v_level_1688_, v_part_1689_, v_a_1690_);
lean_dec(v_level_1688_);
return v_res_1691_;
}
}
LEAN_EXPORT lean_object* l_Lean_Doc_partMarkdown___redArg(lean_object* v_inst_1692_, lean_object* v_inst_1693_, lean_object* v_level_1694_, lean_object* v_part_1695_, lean_object* v_a_1696_){
_start:
{
lean_object* v___x_1697_; lean_object* v_title_1698_; lean_object* v_content_1699_; lean_object* v_subParts_1700_; lean_object* v___x_1701_; size_t v_sz_1702_; size_t v___x_1703_; lean_object* v___x_613__overap_1704_; lean_object* v___x_1705_; lean_object* v_fst_1706_; lean_object* v_snd_1707_; lean_object* v___x_1708_; size_t v_sz_1709_; lean_object* v___x_616__overap_1710_; lean_object* v___x_1711_; lean_object* v_fst_1712_; lean_object* v_snd_1713_; lean_object* v___x_1714_; lean_object* v___f_1715_; lean_object* v___x_1716_; lean_object* v___x_1717_; lean_object* v___x_1718_; lean_object* v___x_1719_; size_t v_sz_1720_; lean_object* v___x_619__overap_1721_; lean_object* v___x_1722_; lean_object* v_fst_1723_; lean_object* v_snd_1724_; lean_object* v___x_1726_; uint8_t v_isShared_1727_; uint8_t v_isSharedCheck_1742_; 
v___x_1697_ = ((lean_object*)(l___private_Lean_DocString_Markdown_0__Lean_Doc_inlineMarkdown___redArg___closed__19));
v_title_1698_ = lean_ctor_get(v_part_1695_, 0);
lean_inc_ref(v_title_1698_);
v_content_1699_ = lean_ctor_get(v_part_1695_, 3);
lean_inc_ref(v_content_1699_);
v_subParts_1700_ = lean_ctor_get(v_part_1695_, 4);
lean_inc_ref(v_subParts_1700_);
lean_dec_ref(v_part_1695_);
lean_inc_ref_n(v_inst_1692_, 2);
v___x_1701_ = lean_alloc_closure((void*)(l_Lean_Doc_instToMarkdownInlineOfMarkdownInline___private__1), 4, 2);
lean_closure_set(v___x_1701_, 0, lean_box(0));
lean_closure_set(v___x_1701_, 1, v_inst_1692_);
v_sz_1702_ = lean_array_size(v_title_1698_);
v___x_1703_ = ((size_t)0ULL);
v___x_613__overap_1704_ = l___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map(lean_box(0), lean_box(0), lean_box(0), v___x_1697_, v___x_1701_, v_sz_1702_, v___x_1703_, v_title_1698_);
v___x_1705_ = lean_apply_1(v___x_613__overap_1704_, v_a_1696_);
v_fst_1706_ = lean_ctor_get(v___x_1705_, 0);
lean_inc(v_fst_1706_);
v_snd_1707_ = lean_ctor_get(v___x_1705_, 1);
lean_inc(v_snd_1707_);
lean_dec_ref(v___x_1705_);
lean_inc_ref(v_inst_1693_);
v___x_1708_ = lean_alloc_closure((void*)(l_Lean_Doc_instToMarkdownBlockOfMarkdownInlineOfMarkdownBlock___private__1), 6, 4);
lean_closure_set(v___x_1708_, 0, lean_box(0));
lean_closure_set(v___x_1708_, 1, lean_box(0));
lean_closure_set(v___x_1708_, 2, v_inst_1692_);
lean_closure_set(v___x_1708_, 3, v_inst_1693_);
v_sz_1709_ = lean_array_size(v_content_1699_);
v___x_616__overap_1710_ = l___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map(lean_box(0), lean_box(0), lean_box(0), v___x_1697_, v___x_1708_, v_sz_1709_, v___x_1703_, v_content_1699_);
v___x_1711_ = lean_apply_1(v___x_616__overap_1710_, v_snd_1707_);
v_fst_1712_ = lean_ctor_get(v___x_1711_, 0);
lean_inc(v_fst_1712_);
v_snd_1713_ = lean_ctor_get(v___x_1711_, 1);
lean_inc(v_snd_1713_);
lean_dec_ref(v___x_1711_);
v___x_1714_ = ((lean_object*)(l___private_Init_Data_Array_Basic_0__Array_foldlMUnsafe_fold___at___00Lean_Doc_joinBlocks_spec__0___closed__0));
v___f_1715_ = lean_obj_once(&l_Lean_Doc_partMarkdown___redArg___closed__0, &l_Lean_Doc_partMarkdown___redArg___closed__0_once, _init_l_Lean_Doc_partMarkdown___redArg___closed__0);
v___x_1716_ = lean_unsigned_to_nat(1u);
v___x_1717_ = lean_nat_add(v_level_1694_, v___x_1716_);
lean_inc(v___x_1717_);
v___x_1718_ = l___private_Init_Data_Nat_Basic_0__Nat_repeatTR_loop(lean_box(0), v___f_1715_, v___x_1717_, v___x_1714_);
v___x_1719_ = lean_alloc_closure((void*)(l_Lean_Doc_partMarkdown___redArg___boxed), 5, 3);
lean_closure_set(v___x_1719_, 0, v_inst_1692_);
lean_closure_set(v___x_1719_, 1, v_inst_1693_);
lean_closure_set(v___x_1719_, 2, v___x_1717_);
v_sz_1720_ = lean_array_size(v_subParts_1700_);
v___x_619__overap_1721_ = l___private_Init_Data_Array_Basic_0__Array_mapMUnsafe_map(lean_box(0), lean_box(0), lean_box(0), v___x_1697_, v___x_1719_, v_sz_1720_, v___x_1703_, v_subParts_1700_);
v___x_1722_ = lean_apply_1(v___x_619__overap_1721_, v_snd_1713_);
v_fst_1723_ = lean_ctor_get(v___x_1722_, 0);
v_snd_1724_ = lean_ctor_get(v___x_1722_, 1);
v_isSharedCheck_1742_ = !lean_is_exclusive(v___x_1722_);
if (v_isSharedCheck_1742_ == 0)
{
v___x_1726_ = v___x_1722_;
v_isShared_1727_ = v_isSharedCheck_1742_;
goto v_resetjp_1725_;
}
else
{
lean_inc(v_snd_1724_);
lean_inc(v_fst_1723_);
lean_dec(v___x_1722_);
v___x_1726_ = lean_box(0);
v_isShared_1727_ = v_isSharedCheck_1742_;
goto v_resetjp_1725_;
}
v_resetjp_1725_:
{
lean_object* v___x_1728_; lean_object* v___x_1729_; lean_object* v___x_1730_; lean_object* v___x_1731_; lean_object* v___x_1732_; lean_object* v___x_1733_; lean_object* v___x_1734_; lean_object* v___x_1735_; lean_object* v___x_1736_; lean_object* v___x_1737_; lean_object* v___x_1738_; lean_object* v___x_1740_; 
v___x_1728_ = ((lean_object*)(l___private_Lean_DocString_Markdown_0__Lean_Doc_quoteCode___closed__0));
v___x_1729_ = lean_string_append(v___x_1718_, v___x_1728_);
v___x_1730_ = lean_mk_empty_array_with_capacity(v___x_1716_);
lean_inc_ref_n(v___x_1730_, 2);
v___x_1731_ = lean_array_push(v___x_1730_, v___x_1729_);
v___x_1732_ = lean_array_push(v___x_1730_, v___x_1731_);
v___x_1733_ = l_Array_append___redArg(v___x_1732_, v_fst_1706_);
lean_dec(v_fst_1706_);
v___x_1734_ = l_Lean_Doc_joinInlines(v___x_1733_);
lean_dec_ref(v___x_1733_);
v___x_1735_ = lean_array_push(v___x_1730_, v___x_1734_);
v___x_1736_ = l_Array_append___redArg(v___x_1735_, v_fst_1712_);
lean_dec(v_fst_1712_);
v___x_1737_ = l_Array_append___redArg(v___x_1736_, v_fst_1723_);
lean_dec(v_fst_1723_);
v___x_1738_ = l_Lean_Doc_joinBlocks(v___x_1737_);
lean_dec_ref(v___x_1737_);
if (v_isShared_1727_ == 0)
{
lean_ctor_set(v___x_1726_, 0, v___x_1738_);
v___x_1740_ = v___x_1726_;
goto v_reusejp_1739_;
}
else
{
lean_object* v_reuseFailAlloc_1741_; 
v_reuseFailAlloc_1741_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v_reuseFailAlloc_1741_, 0, v___x_1738_);
lean_ctor_set(v_reuseFailAlloc_1741_, 1, v_snd_1724_);
v___x_1740_ = v_reuseFailAlloc_1741_;
goto v_reusejp_1739_;
}
v_reusejp_1739_:
{
return v___x_1740_;
}
}
}
}
LEAN_EXPORT lean_object* l_Lean_Doc_partMarkdown(lean_object* v_i_1743_, lean_object* v_b_1744_, lean_object* v_p_1745_, lean_object* v_inst_1746_, lean_object* v_inst_1747_, lean_object* v_level_1748_, lean_object* v_part_1749_, lean_object* v_a_1750_){
_start:
{
lean_object* v___x_1751_; 
v___x_1751_ = l_Lean_Doc_partMarkdown___redArg(v_inst_1746_, v_inst_1747_, v_level_1748_, v_part_1749_, v_a_1750_);
return v___x_1751_;
}
}
LEAN_EXPORT lean_object* l_Lean_Doc_partMarkdown___boxed(lean_object* v_i_1752_, lean_object* v_b_1753_, lean_object* v_p_1754_, lean_object* v_inst_1755_, lean_object* v_inst_1756_, lean_object* v_level_1757_, lean_object* v_part_1758_, lean_object* v_a_1759_){
_start:
{
lean_object* v_res_1760_; 
v_res_1760_ = l_Lean_Doc_partMarkdown(v_i_1752_, v_b_1753_, v_p_1754_, v_inst_1755_, v_inst_1756_, v_level_1757_, v_part_1758_, v_a_1759_);
lean_dec(v_level_1757_);
return v_res_1760_;
}
}
LEAN_EXPORT lean_object* l_Lean_Doc_instToMarkdownPartOfMarkdownInlineOfMarkdownBlock___redArg___lam__0(lean_object* v_inst_1761_, lean_object* v_inst_1762_, lean_object* v_part_1763_, lean_object* v___y_1764_){
_start:
{
lean_object* v___x_1765_; lean_object* v___x_1766_; 
v___x_1765_ = lean_unsigned_to_nat(0u);
v___x_1766_ = l_Lean_Doc_partMarkdown___redArg(v_inst_1761_, v_inst_1762_, v___x_1765_, v_part_1763_, v___y_1764_);
return v___x_1766_;
}
}
LEAN_EXPORT lean_object* l_Lean_Doc_instToMarkdownPartOfMarkdownInlineOfMarkdownBlock___redArg(lean_object* v_inst_1767_, lean_object* v_inst_1768_){
_start:
{
lean_object* v___f_1769_; 
v___f_1769_ = lean_alloc_closure((void*)(l_Lean_Doc_instToMarkdownPartOfMarkdownInlineOfMarkdownBlock___redArg___lam__0), 4, 2);
lean_closure_set(v___f_1769_, 0, v_inst_1767_);
lean_closure_set(v___f_1769_, 1, v_inst_1768_);
return v___f_1769_;
}
}
LEAN_EXPORT lean_object* l_Lean_Doc_instToMarkdownPartOfMarkdownInlineOfMarkdownBlock(lean_object* v_i_1770_, lean_object* v_b_1771_, lean_object* v_p_1772_, lean_object* v_inst_1773_, lean_object* v_inst_1774_){
_start:
{
lean_object* v___f_1775_; 
v___f_1775_ = lean_alloc_closure((void*)(l_Lean_Doc_instToMarkdownPartOfMarkdownInlineOfMarkdownBlock___redArg___lam__0), 4, 2);
lean_closure_set(v___f_1775_, 0, v_inst_1773_);
lean_closure_set(v___f_1775_, 1, v_inst_1774_);
return v___f_1775_;
}
}
lean_object* runtime_initialize_Lean_DocString_Types(uint8_t builtin);
lean_object* runtime_initialize_Init_Data_String_TakeDrop(uint8_t builtin);
lean_object* runtime_initialize_Init_Data_String_Search(uint8_t builtin);
lean_object* runtime_initialize_Init_Data_ToString_Macro(uint8_t builtin);
lean_object* runtime_initialize_Init_While(uint8_t builtin);
static bool _G_runtime_initialized = false;
LEAN_EXPORT lean_object* runtime_initialize_Lean_DocString_Markdown(uint8_t builtin) {
lean_object * res;
if (_G_runtime_initialized) return lean_io_result_mk_ok(lean_box(0));
_G_runtime_initialized = true;
res = runtime_initialize_Lean_DocString_Types(builtin);
if (lean_io_result_is_error(res)) return res;
lean_dec_ref(res);
res = runtime_initialize_Init_Data_String_TakeDrop(builtin);
if (lean_io_result_is_error(res)) return res;
lean_dec_ref(res);
res = runtime_initialize_Init_Data_String_Search(builtin);
if (lean_io_result_is_error(res)) return res;
lean_dec_ref(res);
res = runtime_initialize_Init_Data_ToString_Macro(builtin);
if (lean_io_result_is_error(res)) return res;
lean_dec_ref(res);
res = runtime_initialize_Init_While(builtin);
if (lean_io_result_is_error(res)) return res;
lean_dec_ref(res);
l___private_Lean_DocString_Markdown_0__Lean_Doc_midLineSpecial___closed__3___boxed__const__1 = _init_l___private_Lean_DocString_Markdown_0__Lean_Doc_midLineSpecial___closed__3___boxed__const__1();
lean_mark_persistent(l___private_Lean_DocString_Markdown_0__Lean_Doc_midLineSpecial___closed__3___boxed__const__1);
l___private_Lean_DocString_Markdown_0__Lean_Doc_markerPrefixSpecial___closed__0___boxed__const__1 = _init_l___private_Lean_DocString_Markdown_0__Lean_Doc_markerPrefixSpecial___closed__0___boxed__const__1();
lean_mark_persistent(l___private_Lean_DocString_Markdown_0__Lean_Doc_markerPrefixSpecial___closed__0___boxed__const__1);
l_Lean_Doc_partMarkdown___redArg___closed__0___boxed__const__1 = _init_l_Lean_Doc_partMarkdown___redArg___closed__0___boxed__const__1();
lean_mark_persistent(l_Lean_Doc_partMarkdown___redArg___closed__0___boxed__const__1);
return lean_io_result_mk_ok(lean_box(0));
}
static bool _G_meta_initialized = false;
LEAN_EXPORT lean_object* meta_initialize_Lean_DocString_Markdown(uint8_t builtin) {
lean_object * res;
if (_G_meta_initialized) return lean_io_result_mk_ok(lean_box(0));
_G_meta_initialized = true;
return lean_io_result_mk_ok(lean_box(0));
}
lean_object* initialize_Lean_DocString_Types(uint8_t builtin);
lean_object* initialize_Init_Data_String_TakeDrop(uint8_t builtin);
lean_object* initialize_Init_Data_String_Search(uint8_t builtin);
lean_object* initialize_Init_Data_ToString_Macro(uint8_t builtin);
lean_object* initialize_Init_While(uint8_t builtin);
static bool _G_initialized = false;
LEAN_EXPORT lean_object* initialize_Lean_DocString_Markdown(uint8_t builtin) {
lean_object * res;
if (_G_initialized) return lean_io_result_mk_ok(lean_box(0));
_G_initialized = true;
res = initialize_Lean_DocString_Types(builtin);
if (lean_io_result_is_error(res)) return res;
lean_dec_ref(res);
res = initialize_Init_Data_String_TakeDrop(builtin);
if (lean_io_result_is_error(res)) return res;
lean_dec_ref(res);
res = initialize_Init_Data_String_Search(builtin);
if (lean_io_result_is_error(res)) return res;
lean_dec_ref(res);
res = initialize_Init_Data_ToString_Macro(builtin);
if (lean_io_result_is_error(res)) return res;
lean_dec_ref(res);
res = initialize_Init_While(builtin);
if (lean_io_result_is_error(res)) return res;
lean_dec_ref(res);
res = runtime_initialize_Lean_DocString_Markdown(builtin);
if (lean_io_result_is_error(res)) return res;
lean_dec_ref(res);
res = meta_initialize_Lean_DocString_Markdown(builtin);
if (lean_io_result_is_error(res)) return res;
lean_dec_ref(res);
return initialize_Lean_DocString_Markdown(builtin);
}
#ifdef __cplusplus
}
#endif
