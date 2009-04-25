package xxpalk_ui.ui;

import javax.swing.JFrame;
import javax.swing.JPanel;
import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.ComponentOrientation;
import java.awt.Color;
import java.awt.Toolkit;
import java.awt.Rectangle;
import java.awt.GridBagLayout;
import java.awt.event.*;
import java.io.PrintWriter;
import java.util.*;
import java.io.*;
import sun.audio.*;

import javax.swing.JLabel;
import javax.swing.ImageIcon;
import javax.swing.JComboBox;
import javax.swing.JList;
import javax.swing.JTextField;
import javax.swing.JPasswordField;
import javax.swing.JButton;
import javax.swing.JTree;
import javax.swing.tree.*;
import javax.swing.Icon;
import javax.swing.event.*;


public class XXPalkMainFrame {

	private JFrame jFrame = null; // @jve:decl-index=0:visual-constraint="89,2"

	private JPanel jContentPane = null;

	private JLabel jLabel_UserIcon = null;

	private JLabel jLabel_UserID = null;

	private JComboBox jComboBox_UserStatu = null;

	private JTextField jTextField_Event = null;

	private JPanel jPanel_Login = null;

	private JTextField jTextField_UserId = null;

	private JLabel jLabel_User = null;

	private JPasswordField jPasswordField = null;

	private JLabel jLabel2 = null;

	private JButton jButton_Connect = null;

	private JButton jButton_About = null;

	static public Process process = null;
	
	static public int port = 5000;

	public XXPalkMainFrame() {
		
		this.vec_NodeInfo = new Vector<NodeInfo>();
		try {
			port = new java.util.Random().nextInt()%1000 + 4000;

		} catch (Exception e) {
			System.out.println(e);
		}// try catch
		st = null;
		this.getJFrame();
		
	}

	public void show() {
		this.jFrame.show(true);
	}

	/**
	 * This method initializes jFrame
	 * 
	 * @return javax.swing.JFrame
	 */
	private JFrame getJFrame() {
		if (jFrame == null) {
			jFrame = new JFrame();
			jFrame.setSize(new Dimension(271, 536));
			jFrame.setFont(new Font("Lucida Grande", Font.BOLD, 14));
			jFrame.setComponentOrientation(ComponentOrientation.LEFT_TO_RIGHT);
			jFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
			jFrame.setTitle("XXPalk");
			jFrame.setPreferredSize(new Dimension(230, 400));
			jFrame.setVisible(true);
			jFrame.setBackground(Color.darkGray);
			jFrame.setMaximumSize(new Dimension(250, 500));
			jFrame.setMinimumSize(new Dimension(200, 400));
			jFrame.setIconImage(Toolkit.getDefaultToolkit().getImage(
					getClass().getResource("/xxpalk_ui/share/images/xxpalk.png")));
			jFrame.setContentPane(getJContentPane());
			jFrame.addWindowListener(new java.awt.event.WindowAdapter() {
				public void windowClosing(java.awt.event.WindowEvent e) {
					System.out.println("windowClosing()"); // TODO Auto-generated Event stub windowClosing()
					if(process != null)
						process.destroy();
				}
			});
		}
		return jFrame;
	}

	/**
	 * This method initializes jContentPane
	 * 
	 * @return javax.swing.JPanel
	 */
	private JPanel getJContentPane() {
		if (jContentPane == null) {
			jLabel_UserID = new JLabel();
			jLabel_UserID.setBounds(new Rectangle(119, 21, 134, 23));
			jLabel_UserID.setFont(new Font("Lucida Sans", Font.BOLD, 12));
			jLabel_UserID.setForeground(Color.green);
			jLabel_UserID.setText("user@gmail.com");
			jLabel_UserIcon = new JLabel();
			jLabel_UserIcon.setBounds(new Rectangle(3, 4, 111, 100));
			jLabel_UserIcon.setIcon(new ImageIcon(getClass().getResource(
					"/xxpalk_ui/share/images/xxpalk.png")));
			jLabel_UserIcon.setBackground(Color.darkGray);
			jLabel_UserIcon.setText("");
			jContentPane = new JPanel();
			jContentPane.setLayout(null);
			jContentPane.setBackground(Color.darkGray);
			jContentPane.add(jLabel_UserIcon, null);
			jContentPane.add(jLabel_UserID, null);
			jContentPane.add(getJComboBox_UserStatu(), null);
			jContentPane.add(getJTextField_Event(), null);
			jContentPane.add(getJPanel_Login(), null);
			jContentPane.add(getJButton_About(), null);
			jContentPane.add(getJTree_Rosters(), null);
		}
		return jContentPane;
	}

	/**
	 * This method initializes jComboBox_UserStatu
	 * 
	 * @return javax.swing.JComboBox
	 */
	private JComboBox getJComboBox_UserStatu() {
		if (jComboBox_UserStatu == null) {
			jComboBox_UserStatu = new JComboBox();
			jComboBox_UserStatu.setBounds(new Rectangle(121, 61, 86, 19));
			jComboBox_UserStatu.setForeground(Color.pink);
			jComboBox_UserStatu.setBackground(Color.darkGray);
		}
		return jComboBox_UserStatu;
	}

	/**
	 * This method initializes jTextField_Event
	 * 
	 * @return javax.swing.JTextField
	 */
	private JTextField getJTextField_Event() {
		if (jTextField_Event == null) {
			jTextField_Event = new JTextField();
			jTextField_Event.setBounds(new Rectangle(5, 474, 249, 19));
			jTextField_Event.setBackground(Color.darkGray);
			jTextField_Event.setFont(new Font("Lucida Sans", Font.PLAIN, 12));
			jTextField_Event.setForeground(Color.green);
			jTextField_Event.setText("last event");
		}
		return jTextField_Event;
	}

	/**
	 * This method initializes jPanel_Login
	 * 
	 * @return javax.swing.JPanel
	 */
	private JPanel getJPanel_Login() {
		if (jPanel_Login == null) {
			jLabel_LoginInfo = new JLabel();
			jLabel_LoginInfo.setBounds(new Rectangle(27, 158, 170, 21));
			jLabel_LoginInfo.setBackground(Color.darkGray);
			jLabel_LoginInfo.setForeground(Color.red);
			jLabel_LoginInfo.setText("wrong user id or password");
			jLabel_LoginInfo.setVisible(false);
			jLabel2 = new JLabel();
			jLabel2.setBounds(new Rectangle(1, 74, 72, 20));
			jLabel2.setForeground(Color.green);
			jLabel2.setText("Password: ");
			jLabel_User = new JLabel();
			jLabel_User.setBounds(new Rectangle(1, 28, 60, 21));
			jLabel_User.setForeground(Color.green);
			jLabel_User.setText("User: ");
			jPanel_Login = new JPanel();
			jPanel_Login.setLayout(null);
			jPanel_Login.setBounds(new Rectangle(21, 197, 216, 184));
			jPanel_Login.setBackground(Color.darkGray);
			jPanel_Login.add(getJTextField_UserId(), null);
			jPanel_Login.add(jLabel_User, null);
			jPanel_Login.add(getJPasswordField(), null);
			jPanel_Login.add(jLabel2, null);
			jPanel_Login.add(getJButton_Connect(), null);
			jPanel_Login.add(jLabel_LoginInfo, null);
		}
		return jPanel_Login;
	}

	/**
	 * This method initializes jTextField_UserId
	 * 
	 * @return javax.swing.JTextField
	 */
	private JTextField getJTextField_UserId() {
		if (jTextField_UserId == null) {
			jTextField_UserId = new JTextField();
			jTextField_UserId.setBounds(new Rectangle(75, 29, 138, 20));
			jTextField_UserId.setText("user@gmail.com");
		}
		return jTextField_UserId;
	}

	/**
	 * This method initializes jPasswordField
	 * 
	 * @return javax.swing.JPasswordField
	 */
	private JPasswordField getJPasswordField() {
		if (jPasswordField == null) {
			jPasswordField = new JPasswordField();
			jPasswordField.setBounds(new Rectangle(75, 74, 137, 19));
			jPasswordField.setText("xxxxxxxxxx");
		}
		return jPasswordField;
	}

	/**
	 * This method initializes jButton_Connect
	 * 
	 * @return javax.swing.JButton
	 */
	private JButton getJButton_Connect() {
		if (jButton_Connect == null) {
			jButton_Connect = new JButton();
			jButton_Connect.setBounds(new Rectangle(43, 106, 136, 48));
			jButton_Connect.setForeground(Color.green);
			jButton_Connect.setText("Connect");
			jButton_Connect.setBackground(Color.black);
			
			jButton_Connect.setMnemonic(java.awt.event.KeyEvent.VK_ENTER);
	
			final JTextField jTextField_UserID = this.getJTextField_UserId();
			final JPasswordField jPasswordField = this.getJPasswordField();
			final JButton jButonConnect =  this.jButton_Connect;
			final JLabel jLabel_LoginInfo = this.jLabel_LoginInfo;
			jButton_Connect.addActionListener(new java.awt.event.ActionListener() {
				public void actionPerformed(java.awt.event.ActionEvent e) {
// System.out.println("actionPerformed()"); // TODO Auto-generated Event stub
// actionPerformed()
			
					if(jButonConnect.getText().contains("Connect")){
						String str_UserID = jTextField_UserID.getText();
						String str_Password = jPasswordField.getText();
						if(st != null){
							st.close();
							st = null;
						}//if
						if(st == null){
							try {
								port ++;
	//							port = 5005;
								if(process != null)
									process.destroy();
								process = Runtime.getRuntime().exec(new String[]{"xxpalk_ui/xxpalk", String.valueOf(port)});
								Thread.sleep(1000);
								XXPalkMainFrame.st = new SocketThread(self, port);
								st.start();
								
							} catch (Exception ee) {
								System.out.println(ee);
							}// try catch
						}//if
						st.send(str_UserID);
						try{
							Thread.sleep(1000);
						}catch(Exception eeee){
							System.out.println(eeee);
						}
						st.send(str_Password);
				
						self.userID = str_UserID;
						jButonConnect.setText("Cancel");
						jTextField_UserID.setEditable(false);
						jPasswordField.setEditable(false);
						
						jLabel_LoginInfo.setText("Connecting...");
						jLabel_LoginInfo.setVisible(true);
					}//if
					
					else{
						process.destroy();
						
						jButonConnect.setText("Connect");
						jLabel_LoginInfo.setVisible(true);
						jLabel_LoginInfo.setText("wrong user id or password");
						jButonConnect.setEnabled(true);
						jPasswordField.setEditable(true);
						jTextField_UserID.setEditable(true);
					}
					
				}	
			});
		
		}
		return jButton_Connect;
	}

	/**
	 * This method initializes jButton_About
	 * 
	 * @return javax.swing.JButton
	 */
	private JButton getJButton_About() {
		if (jButton_About == null) {
			jButton_About = new JButton();
			jButton_About.setBounds(new Rectangle(163, 450, 85, 16));
			jButton_About.setForeground(Color.green);
			jButton_About.setText("About");
			jButton_About.setBackground(Color.black);
		}
		return jButton_About;
	}

	public JLabel getJLabel_Info_() {
		return this.jLabel_LoginInfo;
	}

	public JTextField getJTextField_UserID_() {
		return this.getJTextField_UserId();
	}

	public JPasswordField getJPasswordField_() {
		return this.getJPasswordField();
	}

	public JButton getJButon_Connect_() {
		return this.getJButton_Connect();
	}

	public JPanel getJPanel_Login_() {
		return this.getJPanel_Login();
	}

	public JTree getJTree_Rosters_() {
		return this.getJTree_Rosters();
	}
	
	public void onLoggedIn(){
		this.getJLabel_Info_().setVisible(true);
		this.getJLabel_Info_().setText("logged in, bingo!!!");
		this.jLabel_UserID.setText(this.userID);
		this.getJButon_Connect_().setEnabled(false);
		try{
			Thread.sleep(1000);
		}catch(Exception e){
			System.out.println(e);
		}

		this.getJPanel_Login_().setVisible(false);
		this.getJTree_Rosters_().setVisible(true);
	}
	
	public void onLoggingIn(){
		this.getJLabel_Info_().setVisible(true);
		this.getJLabel_Info_().setText("logging in ...");
		
	}
	
	public void onLoggedOut(){
		this.st = null;
		this.getJLabel_Info_().setVisible(true);
		this.getJLabel_Info_().setText("wrong user id or password");
		this.getJButon_Connect_().setEnabled(true);
		this.getJPasswordField_().setEditable(true);
		this.getJTextField_UserID_().setEditable(true);
		this.jLabel_UserID.setText("user@gmail.com");
		try{
			Thread.sleep(100);
		}catch(Exception e){
			System.out.println(e);
		}
	}
	
	public void onConnecting(){
		this.getJLabel_Info_().setVisible(true);
		this.getJLabel_Info_().setText("Connecting...");
	}

	public void onUpdateStatu(String user, String statue){
		boolean row0_isExpanded;
		boolean row1_isExpanded;
		row0_isExpanded = jTree_Rosters.isExpanded(0);
		row1_isExpanded = jTree_Rosters.isExpanded(1);
		
		node_Online.removeAllChildren();
		node_Offline.removeAllChildren();
		
		int index = 0;
		for(index=0; index<vec_NodeInfo.size(); index++){
			if(vec_NodeInfo.elementAt(index).getName().contains(user)){
				vec_NodeInfo.elementAt(index).setStatu(statue);
				break;
			}//if
		}//for
		if(index >= vec_NodeInfo.size())
			vec_NodeInfo.add(new NodeInfo(user, statue));
		
		for(int i=0; i<vec_NodeInfo.size(); i++){
			if(vec_NodeInfo.elementAt(i).getStatu().contains("online")){
				node_Online.add(new DefaultMutableTreeNode(vec_NodeInfo.elementAt(i)));
			}
			else 
				node_Offline.add(new DefaultMutableTreeNode(vec_NodeInfo.elementAt(i)));
		}//for
		
//		jTree_Rosters.updateUI();
		
		if(!node_Offline.isLeaf() && row1_isExpanded)
			jTree_Rosters.expandRow(1);
		if(!node_Online.isLeaf() && row0_isExpanded)
			jTree_Rosters.expandRow(0);
		jTree_Rosters.updateUI();
	}
	/**
	 * This method initializes jTree_Rosters	
	 * 	
	 * @return javax.swing.JTree	
	 */
	private JTree getJTree_Rosters() {
		if (jTree_Rosters == null) {
			DefaultMutableTreeNode top =
		        new DefaultMutableTreeNode(new NodeInfo("Rosters", null));
			node_Online =
		        new DefaultMutableTreeNode(new NodeInfo("Online", null));
			node_Offline =
		        new DefaultMutableTreeNode(new NodeInfo("Offline", null));
		    top.add(node_Online);
		    top.add(node_Offline);
		    
		    jTree_Rosters = new JTree(top);
			jTree_Rosters.setBounds(new Rectangle(3, 110, 251, 335));
			jTree_Rosters.setForeground(Color.pink);
			jTree_Rosters.setRootVisible(false);
			jTree_Rosters.setBackground(Color.black);
			jTree_Rosters.setToggleClickCount(1);
			jTree_Rosters.setVisible(false);
			jTree_Rosters.getSelectionModel().setSelectionMode(
					TreeSelectionModel.SINGLE_TREE_SELECTION);
			
			final JTree tree = jTree_Rosters;
			
			ImageIcon icon_OnlineIcon = new ImageIcon(getClass().getResource(	"/xxpalk_ui/share/images/Online.png"));
			ImageIcon icon_OfflineIcon = new ImageIcon(getClass().getResource(
			"/xxpalk_ui/share/images/Offline.png"));
			ImageIcon icon_onlineIcon = new ImageIcon(getClass().getResource(
			"/xxpalk_ui/share/images/online.png"));
			ImageIcon icon_offlineIcon = new ImageIcon(getClass().getResource(
			"/xxpalk_ui/share/images/offline.png"));
			
			MyRenderer renderer = new MyRenderer(icon_OnlineIcon, icon_OfflineIcon,
														icon_onlineIcon, icon_offlineIcon);
//			renderer.setBackgroundColor(Color.DARK_GRAY);
			renderer.setBackgroundNonSelectionColor(Color.BLACK);
//			renderer.setForeground(Color.GREEN);
			renderer.setTextNonSelectionColor(Color.GREEN);
			renderer.setTextSelectionColor(Color.PINK);
			renderer.setBackgroundSelectionColor(Color.GRAY);
			
			jTree_Rosters.setCellRenderer(renderer);
//			jTree_Rosters.setExpandsSelectedPaths(true);
			
			jTree_Rosters.addTreeSelectionListener(new TreeSelectionListener(){
				public void valueChanged(TreeSelectionEvent e){
					
					DefaultMutableTreeNode node = (DefaultMutableTreeNode)
                                                    tree.getLastSelectedPathComponent();
					NodeInfo nodeInfo = (NodeInfo)(node.getUserObject());
					
					if(nodeInfo.isRoster()){
						XXPalkMainFrame.openChatWindow(nodeInfo);
					}//if
					
				}
			});
		}
		return jTree_Rosters;
	}

	
	public static void openChatWindow(NodeInfo nodeInfo){
		if(!nodeInfo.hasChatWindow()){
			ChatWindow cw = new ChatWindow(self, nodeInfo);
		}//if
	}
	
	public void onChat(String name, String str){
		st.send("chat " + name + " " + str);
	}
	
	public void onChatReceive(String name, String message){
		for(int i=0; i<vec_NodeInfo.size(); i++){
			if(vec_NodeInfo.elementAt(i).getName().contains(name)){
				if(vec_NodeInfo.elementAt(i).hasChatWindow())
					vec_NodeInfo.elementAt(i).getChatWindow().onChatReceive(message);
				else{
					ChatWindow cw = new ChatWindow(self, vec_NodeInfo.elementAt(i));
/*		the sounds can be added here			
					try{  
						FileInputStream   fileau=new    
					   
						FileInputStream("type.wave");  
						AudioStream   as=new   AudioStream(fileau);  
						AudioPlayer.player.start(as); AudioPlayer.yield();  
					 }catch(Exception e){
						 System.out.println(e);
					 }  
	*/				     
					
					cw.onChatReceive(message);
				}//else
				break;
			}//if
		}//for
	}
	
	public void onCallHangup(){
		st.send("hangup");
	}
	
	public void onCallReject(){
		st.send("reject");
	}
	
	public void onCallInComing(String name){
		for(int i=0; i<vec_NodeInfo.size(); i++){
			if(vec_NodeInfo.elementAt(i).getName().contains(name)){
				if(vec_NodeInfo.elementAt(i).hasChatWindow())
					vec_NodeInfo.elementAt(i).getChatWindow().onCallIncoming();
				else{
					ChatWindow cw = new ChatWindow(self, vec_NodeInfo.elementAt(i));
					cw.onCallIncoming();
				}//else
				break;
			}//if
		}//for
	}
	
	public void onCallEnd(){
		for(int i=0; i<vec_NodeInfo.size(); i++){
			if(vec_NodeInfo.elementAt(i).hasChatWindow()){
				System.out.println("hasChatWindow");
				if(vec_NodeInfo.elementAt(i).getChatWindow().isInCall()){
					System.out.println("isInCall");
					vec_NodeInfo.elementAt(i).getChatWindow().onCallEnd();
					break;
				}//if
			}//if
		}//for
	}
	
	public void onCallAnswered(){
		for(int i=0; i<vec_NodeInfo.size(); i++){
			if(vec_NodeInfo.elementAt(i).hasChatWindow()){
				if(vec_NodeInfo.elementAt(i).getChatWindow().isInCall()){
					vec_NodeInfo.elementAt(i).getChatWindow().onCallAnswered();
					break;
				}//if
			}//if
		}//for
	}
	
	public void onCallAccept(){
		st.send("accept");
	}
	
	
	public void onCall(String name){
		st.send("call " + name);
	}
	
	public void onMute(){
		st.send("mute");
	}
	
	public void onUnmute(){
		st.send("unmute");
	}
	
	public void onFileSend(String name, String file){
		st.send("send " + name + " " + file);
	}
		
	
	public void onFileCancel(){
		st.send("cancel");
	}
	
	public void onFileReceive(){
		st.send("receive");
	}
	
	public void onFileProgress(int value){
		for(int i=0; i<vec_NodeInfo.size(); i++){
			if(vec_NodeInfo.elementAt(i).hasChatWindow()){
				if(vec_NodeInfo.elementAt(i).getChatWindow().hasFileTransfer()){
					vec_NodeInfo.elementAt(i).getChatWindow().onFileProgress(value);
					break;
				}//if
			}//if
		}//for
	}
	
	public void onFileFished()
	{
		for(int i=0; i<vec_NodeInfo.size(); i++){
			if(vec_NodeInfo.elementAt(i).hasChatWindow()){
				if(vec_NodeInfo.elementAt(i).getChatWindow().hasFileTransfer()){
					vec_NodeInfo.elementAt(i).getChatWindow().onFileFished();
					break;
				}//if
			}//if
		}//for
	}
	
	public void onIcomingFile(String name, String file){
		for(int i=0; i<vec_NodeInfo.size(); i++){
			if(vec_NodeInfo.elementAt(i).getName().contains(name)){
				if(vec_NodeInfo.elementAt(i).hasChatWindow())
					vec_NodeInfo.elementAt(i).getChatWindow().onIcomingFile(name, file);
				else{
					ChatWindow cw = new ChatWindow(self, vec_NodeInfo.elementAt(i));
					cw.onIcomingFile(name, file);
				}//else
				break;
			}//if
		}//for
	}
	
	public void onFileCanceled(){
		System.out.println("onFileCanceled");
		for(int i=0; i<vec_NodeInfo.size(); i++){
			if(vec_NodeInfo.elementAt(i).hasChatWindow()){
				System.out.println("onFileCanceled1");
				if(vec_NodeInfo.elementAt(i).getChatWindow().hasFileTransfer()){
					System.out.println("onFileCanceled2");
					vec_NodeInfo.elementAt(i).getChatWindow().onFileCanceled();
					break;
				}//if
			}//if
		}//for
	}
	
	public void onFileBegin(){
		for(int i=0; i<vec_NodeInfo.size(); i++){
			if(vec_NodeInfo.elementAt(i).hasChatWindow()){
				if(vec_NodeInfo.elementAt(i).getChatWindow().hasFileTransfer()){
					vec_NodeInfo.elementAt(i).getChatWindow().onFileBegin();
					break;
				}//if
			}//if
		}//for
	}
	
	public String getUserID(){
		return this.userID;
	}
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		XXPalkMainFrame mainFrame = new XXPalkMainFrame();
		self = mainFrame;
		mainFrame.show();

//		st.send("jtalk.xiong@gmail.com");
//		st.send("xiongqin1");
//		st.sendln();
	}

	static public SocketThread st = null;  //  @jve:decl-index=0:
//	static public PrintWriter sortie;
	static public XXPalkMainFrame self = null;
	private JLabel jLabel_LoginInfo = null;
	
	boolean b_first_time = true;

	private JTree jTree_Rosters = null;
	private DefaultMutableTreeNode node_Online;  //  @jve:decl-index=0:
	private DefaultMutableTreeNode node_Offline;  //  @jve:decl-index=0:
	private String userID = null;
	
	Vector<NodeInfo> vec_NodeInfo;
	
}
