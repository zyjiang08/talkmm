package xxpalk_ui.ui;

import java.awt.*;
import javax.swing.Icon;
import javax.swing.tree.*;
import javax.swing.*;

class MyRenderer extends DefaultTreeCellRenderer {
	Icon icon_OnlineIcon;
	Icon icon_OfflineIcon;
	Icon icon_onlineIcon;
	Icon icon_offlineIcon;

    public MyRenderer(Icon OnlineIcon, Icon OfflineIcon, Icon onlineIcon, Icon offlineIcon) {
    	icon_OnlineIcon = OnlineIcon;
       icon_OfflineIcon = OfflineIcon;
       icon_onlineIcon = onlineIcon;
       icon_offlineIcon = offlineIcon;
    }

    public Component getTreeCellRendererComponent(
                        JTree tree,
                        Object value,
                        boolean sel,
                        boolean expanded,
                        boolean leaf,
                        int row,
                        boolean hasFocus) {

        super.getTreeCellRendererComponent(
                        tree, value, sel,
                        expanded, leaf, row,
                        hasFocus);
        if (isRoster(value)) {
          if(isOnlineRoster(value)){
            setIcon(icon_onlineIcon);
          	}//if
          else
        	  setIcon(icon_offlineIcon);
            
        } else {
            	if(isOnlineNode(value))
            		setIcon(icon_OnlineIcon);
            	else
            		setIcon(icon_OfflineIcon);
        	}//else 

        return this;
    }

    protected boolean isRoster(Object value){
    	DefaultMutableTreeNode node =
    		(DefaultMutableTreeNode)value;
    	NodeInfo nodeInfo = (NodeInfo)(node.getUserObject());
    	return (nodeInfo.isRoster());
    }
    
    protected boolean isOnlineNode(Object value){
    	DefaultMutableTreeNode node =
            (DefaultMutableTreeNode)value;
    	NodeInfo nodeInfo = (NodeInfo)node.getUserObject();
    	
    	return nodeInfo.isOnline();
    }
    
    protected boolean isOnlineRoster(Object value) {
    	DefaultMutableTreeNode node =
            (DefaultMutableTreeNode)value;
    	NodeInfo nodeInfo = (NodeInfo)node.getUserObject();
    	if(nodeInfo.isRoster())
    		if(nodeInfo.isOnlineRoster())
    			return true;
        return false;
    }
}

