open UTF8

val s = "Привет"
val ux = strlen s
val bx = Basis.strlen s

fun main {} : transaction page =
  return
  <xml>
    <head/>
    <body>
      s => {[s]}
      <br/>
      strlen s => {[ux]}
      <br/>
      Basis.strlen => {[bx]}
      <br/>
      str (toLower (at s 0)) => {[str (toLower (at s 0))]}
      <br/>
      str (toUpper (at s 2)) => {[str (toUpper (at s 2))]}
      <br/>
      substr s 0 99 => {[substr s 0 99]}
      <br/>
      substr s 1 3 => {[substr s 1 3]}
      <br/>
      substr s 0 6 => {[substr s 0 6]}
      <br/>
      tail s => {[tail s]}
      <br/>
      mp toUpper s => {[mp toUpper s]}
      <br/>
      <button value="Test client side" onclick={fn _ =>
        alert ("len = " ^ (show (UTF8.strlen "12345")))
      }/>
    </body>
  </xml>

