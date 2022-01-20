class ConstructorCall {

  private native String newString(String s, int length);

  public static void main(String[] args) {
    ConstructorCall c = new ConstructorCall();
    System.out.println(c.newString("aaabbb", 3));
  }

  static {
    System.loadLibrary("ConstructorCall");
  }
}
