open UTF8

val s = "Привет"
val ux = strlen s
val bx = Basis.strlen s

fun main {} : transaction page =
  return
  <xml>
    <head/>
    <body>
      UTF8: {[ux]}
      <br/>
      Basis: {[bx]}
      <br/>
      At0: {[str (toLower (at s 0))]}
      At2: {[str (toUpper (at s 2))]}
      <br/>
      Substr: {[substr s 0 99]} {[substr s 1 3]} {[substr s 0 6]}
      <br/>
      Tail: {[tail s]}
    </body>
  </xml>

