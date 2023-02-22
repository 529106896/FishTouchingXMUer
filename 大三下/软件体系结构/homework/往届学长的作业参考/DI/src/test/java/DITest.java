public class DITest {
    public static void main(String[] args) {
        Task t = new Task("Task #1");
        // Phper, Javaer 都是Coder,可以赋值
        Coder owner = new Phper("lee4");
        //Coder owner = new Javaer("Wang5");
        t.setOwner(owner);
        t.start();
    }
}