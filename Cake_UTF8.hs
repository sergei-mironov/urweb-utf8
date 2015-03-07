module Cake_UTF8 where

import Development.Cake3
import Development.Cake3.Ext.UrWeb
import Cake_UTF8_P

lib = do
  uwlib (file "lib.urp") $ do
    ffi (file "UTF8_ffi.urs")
    include (file "UTF8_ffi.h")
    src (file "UTF8_ffi.cpp","-std=c++11","-lstdc++ -lutf8proc")
    ur (sys "list")
    static "/UTF8_js/content" (file "UTF8.js")
    script "/UTF8_js/content"
    jsFunc "UTF8_ffi" "strlen" "utf8_strlen"
    ur (file "UTF8.ur")

mktest f bdy = do
  uwapp "-dbms sqlite" (f .= ".urp") $ do
    database ("dbname="++(takeBaseName f))
    sql (f.="sql")
    library lib
    ur (sys "list")
    ur (sys "char")
    ur (sys "string")
    bdy
    ur f

main = do
  writeDefaultMakefiles $ do
    rule $ do
      phony "lib"
      depend lib

    rule $ do
      phony "all"
      depend (mktest (file "test/UTF8_test1.ur") (return  ()))


