
open UTF8_ffi

fun mp (f : uchar -> uchar) (s:string) : string =
  if strlenGe s 1 then
    (str (f (at s 0))) ^ (mp f (tail s))
  else
    ""
