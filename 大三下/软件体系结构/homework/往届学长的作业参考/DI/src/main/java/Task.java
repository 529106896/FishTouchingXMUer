/**
 * @author fairy
 */
public class Task {
    private String name;
    private Coder owner;
    public Task(String name){
        this.name=name;
    }
    public void setOwner(Coder owner){
        this.owner=owner;
    }
    public void start(){
        System.out.println(this.name+ " started");
        this.owner.writeCode();
    }
}
