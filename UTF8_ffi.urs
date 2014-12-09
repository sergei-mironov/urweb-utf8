
type uchar

val at : string -> int -> uchar

val strlen : string -> int

val str : uchar -> string

val toUpper : uchar -> uchar
val toLower : uchar -> uchar

(* O(n) complexity *)
val substr : string -> int -> int -> string

(* O(1) complexity *)
val tail : string -> string

