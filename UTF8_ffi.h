#include <types_cpp.h>
#include <urweb_cpp.h>
#include <inttypes.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int32_t uw_UTF8_ffi_uchar;

uw_Basis_int uw_UTF8_ffi_strlen(struct uw_context *ctx, uw_Basis_string str);

uw_UTF8_ffi_uchar uw_UTF8_ffi_at(struct uw_context *ctx, uw_Basis_string str, int idx);

uw_Basis_string uw_UTF8_ffi_str(struct uw_context *ctx, uw_UTF8_ffi_uchar uc);

uw_UTF8_ffi_uchar uw_UTF8_ffi_toUpper(struct uw_context *ctx, uw_UTF8_ffi_uchar uc);
uw_UTF8_ffi_uchar uw_UTF8_ffi_toLower(struct uw_context *ctx, uw_UTF8_ffi_uchar uc);

uw_Basis_string uw_UTF8_ffi_substr(struct uw_context *ctx, uw_Basis_string str, uw_Basis_int start, uw_Basis_int len);

uw_Basis_string uw_UTF8_ffi_tail(struct uw_context *ctx, uw_Basis_string str);

#ifdef __cplusplus
} // extern "C"
#endif
