/**
 * @author fairy
 */
public class Phper implements Coder {
    private String name;
    public Phper(String name){
        this.name=name;
    }
    @Override
    public void writeCode(){
        System.out.println(this.name + " is writing Php code");
    }
}
