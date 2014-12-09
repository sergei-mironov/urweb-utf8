
extern "C" {
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <utf8proc.h>

#include <urweb_cpp.h>
#include "UTF8_ffi.h"
}

#include <functional>

using namespace std;

ssize_t for_each_uchar(const char* str_, ssize_t maxlen,
      function<ssize_t(const char* b, const char *e, int32_t uc)> f) {
  int32_t uc;
  const uint8_t *str  = (const uint8_t*)str_;

  while(*str != 0) {
    ssize_t ret = utf8proc_iterate(str, maxlen, &uc);
    if(ret > 0) {
      if(maxlen > 0) maxlen -= ret;
      ssize_t ret2 = f((const char*)str, (const char*)str+ret, uc);
      if(ret2 != 0)
        return ret2;
      str += ret;
    }
    else {
      return ret;
    }
  }
  return 0;
}

uw_Basis_int uw_UTF8_ffi_strlen(struct uw_context *ctx, uw_Basis_string str)
{
  uw_Basis_int len = 0;
  if(0 != for_each_uchar(str, -1, [&](const char* b, const char* e, int32_t uc){ len++; return 0; }))
    uw_error(ctx, FATAL, "UTF8::%s failed to iterate through string", __func__);
  return len;
}

uw_UTF8_ffi_uchar uw_UTF8_ffi_at(struct uw_context *ctx, uw_Basis_string str, int idx)
{
  int32_t uc = -1;
  uw_Basis_int idx_ = 0;
  for_each_uchar(str, -1, [&](const char* b, const char* e, int32_t uc_) {
    if(idx == idx_++) {
      uc = uc_;
      return -1;
    }
    else {
      return 0;
    }
  });

  if(uc == -1)
    uw_error(ctx, FATAL, "UTF8::%s no such index", __func__);

  return (int)uc;
}

uw_Basis_string uw_UTF8_ffi_str(struct uw_context *ctx, uw_UTF8_ffi_uchar c)
{
  uint8_t *str = (uint8_t*)uw_malloc(ctx, 5);
  ssize_t ret = utf8proc_encode_char((int32_t)c, str);
  if(ret <= 0)
    uw_error(ctx, FATAL, "UTF8::%s can't encode %d", __func__, c);
  str[ret] = 0;
  return (char*)str;
}

uw_UTF8_ffi_uchar uw_UTF8_ffi_toUpper(struct uw_context *ctx, uw_UTF8_ffi_uchar uc)
{
  if(uc == -1)
    uw_error(ctx, FATAL, "UTF8::%s invalid character", __func__);
  const utf8proc_property_t *p = utf8proc_get_property(uc);
  uw_UTF8_ffi_uchar uc2 = p->uppercase_mapping;
  if(uc2 == -1)
    return uc;
  return uc2;
}

uw_UTF8_ffi_uchar uw_UTF8_ffi_toLower(struct uw_context *ctx, uw_UTF8_ffi_uchar uc)
{
  if(uc == -1)
    uw_error(ctx, FATAL, "UTF8::%s invalid character", __func__);
  const utf8proc_property_t *p = utf8proc_get_property(uc);
  uw_UTF8_ffi_uchar uc2 = p->lowercase_mapping;
  if(uc2 == -1)
    return uc;
  return uc2;
}

uw_Basis_string uw_UTF8_ffi_substr(struct uw_context *ctx, uw_Basis_string str, uw_Basis_int start, uw_Basis_int len)
{
  const char* b = NULL;
  const char* e = NULL;
  const char* last = NULL;
  uw_Basis_int idx = 0;
  for_each_uchar(str, -1, [&](const char* b1, const char* e1, int32_t uc_) {
    last = e1;
    if(idx == start) {
      b = b1;
      if(len == 0)
        e = b1;
    }
    if(idx == start + len - 1) {
      e = e1;
    }
    idx++;
    if(e && b)
      return -1;
    else
      return 0;
  });

  if(b) {
    if(!e) {
      e = last;
    }

    size_t len = e - b;
    char* str = (char*)uw_malloc(ctx, len + 1);
    memcpy(str, b, len);
    str[len] = 0;
    return str;
  }
  else {
    return (char*)"";
  }
}

uw_Basis_string uw_UTF8_ffi_tail(struct uw_context *ctx, uw_Basis_string str)
{
  const char *e = NULL;
  for_each_uchar(str, -1, [&](const char* b1, const char* e1, int32_t uc_) {
      e = e1; return -1;
  });
  if(!e)
    uw_error(ctx, FATAL, "UTF8::%s empty string", __func__);
  return str + (e - str);
}

