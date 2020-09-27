package cabbageroll.tetrjar;

import org.bukkit.DyeColor;
import org.bukkit.Material;
import org.bukkit.block.Block;

public class Printing {

    public static void colprintxy(int x,int y, int z, int color) {
        Block b = Cmain.world.getBlockAt(x,y,z);
        b.setType(Material.CONCRETE);
        if(color==0)
            b.setData(DyeColor.BLACK.getWoolData());
        else if(color==4)
            b.setData(DyeColor.RED.getWoolData());
        else if(color==6)
            b.setData(DyeColor.ORANGE.getWoolData());
        else if(color==14)
            b.setData(DyeColor.YELLOW.getWoolData());
        else if(color==10)
            b.setData(DyeColor.GREEN.getWoolData());
        else if(color==3)
            b.setData(DyeColor.BLUE.getWoolData());
        else if(color==1)
            b.setData(DyeColor.CYAN.getWoolData());
        else if(color==13)
            b.setData(DyeColor.MAGENTA.getWoolData());
        else if(color==15)
            b.setData(DyeColor.WHITE.getWoolData());
    }
    
}
