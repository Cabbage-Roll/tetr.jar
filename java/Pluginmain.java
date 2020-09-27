package cabbageroll.tetrjar;

import org.bukkit.plugin.java.JavaPlugin;
import org.bukkit.scheduler.BukkitScheduler;
import org.bukkit.event.Listener;
import org.bukkit.event.player.PlayerJoinEvent;
import org.bukkit.event.EventHandler;
import org.bukkit.Bukkit;
import org.bukkit.entity.Player;


public class Pluginmain extends JavaPlugin implements Listener{
    @Override
    public void onEnable() {
        System.out.println("Plugin started");
        getServer().getPluginManager().registerEvents(this, this);
        this.getCommand("startgame").setExecutor(new Startgame());
        this.getCommand("sendinput").setExecutor(new Commandinput());
        
            Bukkit.getScheduler().scheduleSyncRepeatingTask(this, new Runnable() {
                @Override
                public void run() {
                    if(Cmain.counter == 100)
                    {
                        if(!Position.isCollide(Position.x, Position.y + 1, Position.block_size))
                        {
                            Moveblock.moveBlock(Position.x, Position.y + 1);
                        }else{
                            Cmain.placeBlock();
                            Cmain.checkPlaced();
                            Cmain.makenextblock();
                        }
                            Cmain.counter=0;
                    }
                    Cmain.counter+=10;
                }
            }, 0L, 20L); //0 Tick initial delay, 20 Tick (1 Second) between repeats

    }
    
    @EventHandler
    public void onPlayerJoin(PlayerJoinEvent event)
    {
        event.setJoinMessage("" + event.getPlayer().getName() + "!");
        Player player=event.getPlayer();
        Cmain.world=player.getWorld();
    }
}