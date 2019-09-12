int x;
static int b = 4;

main() {
  int y;
  static int z;

  y = b;
  z = foo(y);
}

foo( int p ) {
  int a;
  a = p + 2;
  return(a);
}
