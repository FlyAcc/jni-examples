class Child extends Parent{
    private native void nativeMethod();

    public static void main(String[] args) {
        Child c = new Child();
        c.nativeMethod();  
    }

    @Override
    public void callback(){
        System.out.println("call from child");
    }

    static{
        System.loadLibrary("Child");
    }
}