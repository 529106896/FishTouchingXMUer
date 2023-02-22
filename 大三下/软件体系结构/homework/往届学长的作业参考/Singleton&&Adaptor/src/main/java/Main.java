/**
 * @author fairy
 */
public class Main {
    public static void main(String[] args) {
        //把狗适配成猫
        Icat fakercat=new Adapter(new IdogImpl());
        fakercat.catLooks();
        fakercat.CatchMouse();
        //把猫适配成狗
        Idog fakerdog=new Adapter(new IcatImpl());
        fakerdog.dogLooks();
        fakerdog.Cry();
    }
}