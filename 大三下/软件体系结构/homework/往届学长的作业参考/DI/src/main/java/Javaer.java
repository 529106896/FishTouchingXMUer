/**
 * @author fairy
 */
public class Javaer implements Coder {
    private String name;
    public Javaer(String name){
        this.name=name;
    }
    @Override
    public void writeCode(){
        System.out.println(this.name + " is writing Java code");
    }
}
