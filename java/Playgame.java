package cabbageroll.tetrjar;

public class Playgame {
    public static void playgame() {
        if(Cmain.counter == 100)
        {
            if(!Position.isCollide(Position.x, Position.y + 1, Position.block_size))
            {
                Moveblock.moveBlock(Position.x, Position.y + 1);
            }
            else
            {
                Cmain.placeBlock();
                Cmain.checkPlaced();
                Cmain.makenextblock();
            }
            Cmain.counter=0;
        }
    }
}
