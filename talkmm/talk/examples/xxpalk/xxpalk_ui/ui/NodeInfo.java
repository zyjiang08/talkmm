package xxpalk_ui.ui;

public class NodeInfo {
	String str_NodeName = null;
	String str_Statu = null;
	boolean hasChatWindow = false;
	ChatWindow chatWindow = null;
	
	public void setChatWindow(ChatWindow cw)	{
		chatWindow = cw;
		hasChatWindow = true;
	}
	
	public ChatWindow getChatWindow(){
		return chatWindow;
	}
	
	public void chatWindowClosed(){
		hasChatWindow = false;
		chatWindow = null;
	}
	
	public void chatWindowCreated(){
		hasChatWindow = true;
	}
	
	public String getName(){
		return str_NodeName;
	}
	
	public String getStatu(){
		return str_Statu;
	}
	
	public void setStatu(String statu){
		str_Statu = statu;
	}
	
	public boolean hasChatWindow(){
		return hasChatWindow;
	}
	
	public boolean isRoster(){
		return (str_Statu != null);
	}
	
	public boolean isOnlineRoster(){
		
		return isRoster() && str_Statu.contains("online");
	}
	
	public boolean isOnline(){
		return (!isRoster()) && str_NodeName.contains("Online");
	}
	
	public NodeInfo(String name, String statu){
		str_NodeName = name;
		str_Statu = statu;
		hasChatWindow = false;
	}
	
	public String toString(){
		return str_NodeName;
	}
}
