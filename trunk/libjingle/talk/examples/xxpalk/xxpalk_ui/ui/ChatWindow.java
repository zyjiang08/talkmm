package xxpalk_ui.ui;

import javax.swing.JDialog;
import java.awt.FileDialog;
import javax.swing.JPanel;
import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.Color;
import javax.swing.WindowConstants;
import java.awt.Font;
import javax.swing.JButton;
import java.awt.Rectangle;
import java.awt.GridBagLayout;
import javax.swing.JTextField;
import javax.swing.JTextArea;
import javax.swing.JProgressBar;
import java.awt.Toolkit;
import javax.swing.JScrollPane;
import java.awt.GridLayout;

public class ChatWindow {

	private JDialog jDialog_ChatWindow = null;  //  @jve:decl-index=0:visual-constraint="55,23"
	private JPanel jContentPane = null;
	private JPanel jPanel = null;
	private JButton jButton_Call = null;
	private JButton jButton_SendFile = null;
	private JTextField jTextField_InputMessage = null;
	private JButton jButton_Send = null;
	private JButton jButton_Hangup = null;
	private JButton jButton_Cancel = null;
	private JButton jButton_Mute = null;
	private JButton jButton_Unmute = null;
	private JButton jButton_Close = null;
	private JProgressBar jProgressBarFileSendingProgress = null;
	/**
	 * This method initializes jDialog_ChatWindow	
	 * 	
	 * @return javax.swing.JDialog	
	 */
	private JDialog getJDialog_ChatWindow() {
		if (jDialog_ChatWindow == null) {
			jDialog_ChatWindow = new JDialog();
			jDialog_ChatWindow.setSize(new Dimension(400, 333));
			jDialog_ChatWindow.setResizable(false);
			jDialog_ChatWindow.setBackground(Color.darkGray);
			jDialog_ChatWindow.setDefaultCloseOperation(WindowConstants.DISPOSE_ON_CLOSE);
			jDialog_ChatWindow.setFont(new Font("Lucida Grande", Font.BOLD, 12));
			jDialog_ChatWindow.setName("dialog_ChatWindow");
			jDialog_ChatWindow.setTitle("Chating With ");
			jDialog_ChatWindow.setVisible(true);
			jDialog_ChatWindow.setContentPane(getJContentPane());
			
			final NodeInfo nodeInfo = this.nodeInfo;
			final JButton button_call = this.getJButton_Call();
			jDialog_ChatWindow.addWindowListener(new java.awt.event.WindowAdapter() {
				public void windowClosing(java.awt.event.WindowEvent e) {
//					System.out.println("windowClosing()"); // TODO Auto-generated Event stub windowClosing()
					nodeInfo.chatWindowClosed();
					if(!button_call.getText().contains("Call")){
						if(button_call.getText().contains("Accept"))
							mainFrame.onCallReject();
						else
							mainFrame.onCallHangup();
					}//if
				}
			});
			jDialog_ChatWindow.setIconImage(Toolkit.getDefaultToolkit().getImage(
					getClass().getResource("/xxpalk_ui/share/images/xxpalk.png")));
		}
		return jDialog_ChatWindow;
	}

	/**
	 * This method initializes jContentPane	
	 * 	
	 * @return javax.swing.JPanel	
	 */
	private JPanel getJContentPane() {
		if (jContentPane == null) {
			jContentPane = new JPanel();
			jContentPane.setLayout(null);
			jContentPane.setBackground(Color.darkGray);
			jContentPane.add(getJPanel(), null);
			jContentPane.add(getJTextField_InputMessage(), null);
			jContentPane.add(getJButton_Send(), null);
			jContentPane.add(getJProgressBarFileSendingProgress(), null);
			jContentPane.add(getJScrollPane(), null);
		}
		return jContentPane;
	}

	/**
	 * This method initializes jPanel	
	 * 	
	 * @return javax.swing.JPanel	
	 */
	private JPanel getJPanel() {
		if (jPanel == null) {
			jPanel = new JPanel();
			jPanel.setLayout(null);
			jPanel.setBounds(new Rectangle(5, 0, 381, 82));
			jPanel.setBackground(Color.black);
			jPanel.add(getJButton_Call(), null);
			jPanel.add(getJButton_SendFile(), null);
			jPanel.add(getJButton_Hangup(), null);
			jPanel.add(getJButton_Cancel(), null);
			jPanel.add(getJButton_Mute(), null);
			jPanel.add(getJButton_Unmute(), null);
		}
		return jPanel;
	}

	/**
	 * This method initializes jButton_Call	
	 * 	
	 * @return javax.swing.JButton	
	 */
	private JButton getJButton_Call() {
		if (jButton_Call == null) {
			jButton_Call = new JButton();
			jButton_Call.setBounds(new Rectangle(5, 16, 91, 17));
			jButton_Call.setText("Call");
			jButton_Call.setForeground(Color.pink);
			jButton_Call.setBackground(Color.darkGray);
			final NodeInfo nodeInfo = this.nodeInfo;
			final JButton button_call = this.getJButton_Call();
			final JButton button_hangup = this.getJButton_Hangup();
			final JTextArea textArea = this.getJTextArea();
			final JButton button_mute = this.getJButton_Mute();
			final JButton button_unmute = this.getJButton_Unmute();
			button_hangup.addActionListener(new java.awt.event.ActionListener() {
				public void actionPerformed(java.awt.event.ActionEvent e) {
//					System.out.println("actionPerformed()"); // TODO Auto-generated Event stub actionPerformed()
					if(button_hangup.getText().contains("Hangup")){
						button_hangup.setVisible(false);
						button_call.setText("Call");
						button_call.setEnabled(true);
						mainFrame.onCallHangup();
					}//if
					if(button_hangup.getText().contains("Reject")){
						button_hangup.setText("Call");
						button_hangup.setVisible(false);
						button_call.setText("Call");
						button_call.setEnabled(true);
						mainFrame.onCallReject();
					}//if
					
				}
			});
			jButton_Call.addActionListener(new java.awt.event.ActionListener() {
				public void actionPerformed(java.awt.event.ActionEvent e) {
//					System.out.println("actionPerformed()"); // TODO Auto-generated Event stub actionPerformed()
					if(button_call.getText().contains("Call")){
						
						String history = textArea.getText();
						history += "\n";
						history += "Making call to ";
						history += nodeInfo.getName();
						textArea.setText(history);
						
						button_call.setText("Calling...");
						button_call.setEnabled(false);
						button_hangup.setText("Hangup");
						button_hangup.setVisible(true);
						mainFrame.onCall(nodeInfo.getName());
					}//if
					else if(button_call.getText().contains("Accept")){
						
						
						String history = textArea.getText();
						history += "\n";
						history += "Accpeted call from ";
						history += nodeInfo.getName();
						textArea.setText(history);
						
						button_mute.setVisible(true);
						button_mute.setEnabled(true);
						button_unmute.setVisible(true);
						button_unmute.setEnabled(false);
						button_call.setText("Connected");
						button_call.setEnabled(false);
						button_hangup.setVisible(true);
						button_hangup.setText("Hangup");
						mainFrame.onCallAccept();
					}//else if
				}
			});
		}
		return jButton_Call;
	}

	/**
	 * This method initializes jButton_SendFile	
	 * 	
	 * @return javax.swing.JButton	
	 */
	private JButton getJButton_SendFile() {
		if (jButton_SendFile == null) {
			jButton_SendFile = new JButton();
			jButton_SendFile.setBounds(new Rectangle(127, 16, 97, 17));
			jButton_SendFile.setForeground(Color.pink);
			jButton_SendFile.setText("Send File");
			jButton_SendFile.setBackground(Color.darkGray);
			final JProgressBar jProgressBar_FileSendingProgress = this.getJProgressBarFileSendingProgress();
			final JTextArea textArea = this.getJTextArea();
			final JButton button_sendfile = this.getJButton_SendFile();
			final JButton button_cancel = this.getJButton_Cancel();
			final JDialog dialog = this.getJDialog_ChatWindow();
			jButton_SendFile.addActionListener(new java.awt.event.ActionListener() {
				public void actionPerformed(java.awt.event.ActionEvent e) {
					System.out.println("actionPerformed()"); // TODO Auto-generated Event stub actionPerformed()
					
					if(button_sendfile.getText().contains("Send")){
						FileDialog fileDialog = new FileDialog(dialog);
						fileDialog.setVisible(true);
						String file = fileDialog.getFile();
						
						String history = textArea.getText();
						history += "\n";
						history += "Send file to ";
						history += nodeInfo.getName();
						history += ". Waiting to receive...";
						textArea.setText(history);
						
						button_sendfile.setText("Waiting...");
						button_sendfile.setEnabled(false);
						button_cancel.setText("Cancel");
						button_cancel.setEnabled(true);
						button_cancel.setVisible(true);
						
						mainFrame.onFileSend(nodeInfo.getName(), file);
										
					}//if
					else if(button_sendfile.getText().contains("Receive")){
						button_sendfile.setText("Waiting...");
						button_sendfile.setEnabled(false);
						button_cancel.setText("Cancel");
						button_cancel.setEnabled(true);
						
						mainFrame.onFileReceive();
					}//else if
					
				}
			});
			
			button_cancel.addActionListener(new java.awt.event.ActionListener() {
				public void actionPerformed(java.awt.event.ActionEvent e) {
					button_sendfile.setText("Send");
					button_sendfile.setEnabled(true);
					button_cancel.setText("Cancel");
					button_cancel.setEnabled(true);
					button_cancel.setVisible(false);
					jProgressBar_FileSendingProgress.setVisible(false);
					String history = textArea.getText();
					history += "\n";
					history += "File transfer canceled... ";
					textArea.setText(history);
					
					mainFrame.onFileCancel();
				}
			});
		}
		return jButton_SendFile;
	}

	/**
	 * This method initializes jTextField_InputMessage	
	 * 	
	 * @return javax.swing.JTextField	
	 */
	private JTextField getJTextField_InputMessage() {
		if (jTextField_InputMessage == null) {
			jTextField_InputMessage = new JTextField();
			jTextField_InputMessage.setBounds(new Rectangle(6, 232, 283, 25));
			jTextField_InputMessage.setText("");
		}
		return jTextField_InputMessage;
	}

	/**
	 * This method initializes jButton_Send	
	 * 	
	 * @return javax.swing.JButton	
	 */
	private JButton getJButton_Send() {
		if (jButton_Send == null) {
			jButton_Send = new JButton();
			jButton_Send.setBounds(new Rectangle(308, 234, 76, 19));
			jButton_Send.setFont(new Font("Lucida Grande", Font.BOLD, 12));
			jButton_Send.setText("Send");
			jButton_Send.setForeground(Color.green);
			jButton_Send.setBackground(Color.black);
			final NodeInfo nodeInfo = this.nodeInfo;
			final JTextField textField = this.jTextField_InputMessage;
			final JTextArea textArea = this.getJTextArea();
			jButton_Send.addActionListener(new java.awt.event.ActionListener() {
				public void actionPerformed(java.awt.event.ActionEvent e) {
					System.out.println("actionPerformed()"); // TODO Auto-generated Event stub actionPerformed()
					String message = textField.getText();
					if(message.length() != 0){
						mainFrame.onChat(nodeInfo.getName(), message);
						String[] strs = mainFrame.getUserID().split("@");
						String str = "\n" + strs[0] + " said: " + message;
						
						if(textArea != null){
							String history = textArea.getText();
							history += str;
						
							textArea.setText(history);
							
							textField.setText(null);
						}//if
					
	//					
					}//if
					textField.requestFocus();
				}
			});
		}
		return jButton_Send;
	}

	/**
	 * This method initializes jButton_Hangup	
	 * 	
	 * @return javax.swing.JButton	
	 */
	private JButton getJButton_Hangup() {
		if (jButton_Hangup == null) {
			jButton_Hangup = new JButton();
			jButton_Hangup.setBounds(new Rectangle(6, 46, 89, 16));
			jButton_Hangup.setBackground(Color.darkGray);
			jButton_Hangup.setForeground(Color.red);
			jButton_Hangup.setText("Hangup");
			jButton_Hangup.setVisible(false);
		}
		return jButton_Hangup;
	}

	/**
	 * This method initializes jButton_Cancel	
	 * 	
	 * @return javax.swing.JButton	
	 */
	private JButton getJButton_Cancel() {
		if (jButton_Cancel == null) {
			jButton_Cancel = new JButton();
			jButton_Cancel.setBounds(new Rectangle(127, 46, 98, 17));
			jButton_Cancel.setBackground(Color.darkGray);
			jButton_Cancel.setForeground(Color.red);
			jButton_Cancel.setText("Cancel");
			jButton_Cancel.setVisible(false);
		}
		return jButton_Cancel;
	}

	/**
	 * This method initializes jButton_Mute	
	 * 	
	 * @return javax.swing.JButton	
	 */
	private JButton getJButton_Mute() {
		if (jButton_Mute == null) {
			jButton_Mute = new JButton();
			jButton_Mute.setBounds(new Rectangle(284, 16, 84, 19));
			jButton_Mute.setForeground(Color.pink);
			jButton_Mute.setText("Mute");
			jButton_Mute.setBackground(Color.darkGray);
			jButton_Mute.setVisible(false);
			jButton_Mute.setEnabled(true);
			final JButton button_mute = this.getJButton_Mute();
			final JButton button_unmute = this.getJButton_Unmute();
			jButton_Mute.addActionListener(new java.awt.event.ActionListener() {
				public void actionPerformed(java.awt.event.ActionEvent e) {
					button_mute.setEnabled(false);
					button_unmute.setEnabled(true);
					
					mainFrame.onMute();
				}
			});
			
		}
		return jButton_Mute;
	}

	/**
	 * This method initializes jButton_Unmute	
	 * 	
	 * @return javax.swing.JButton	
	 */
	private JButton getJButton_Unmute() {
		if (jButton_Unmute == null) {
			jButton_Unmute = new JButton();
			jButton_Unmute.setBounds(new Rectangle(284, 47, 84, 18));
			jButton_Unmute.setForeground(Color.pink);
			jButton_Unmute.setBackground(Color.darkGray);
			jButton_Unmute.setText("Unmute");
			jButton_Unmute.setEnabled(false);
			jButton_Unmute.setVisible(false);
			final JButton button_mute = this.getJButton_Mute();
			final JButton button_unmute = this.getJButton_Unmute();
			jButton_Unmute.addActionListener(new java.awt.event.ActionListener() {
				public void actionPerformed(java.awt.event.ActionEvent e) {
					button_mute.setEnabled(false);
					button_unmute.setEnabled(true);
					mainFrame.onUnmute();
				}
			});
		}
		return jButton_Unmute;
	}

	/**
	 * This method initializes jProgressBarFileSendingProgress	
	 * 	
	 * @return javax.swing.JProgressBar	
	 */
	private JProgressBar getJProgressBarFileSendingProgress() {
		if (jProgressBarFileSendingProgress == null) {
			jProgressBarFileSendingProgress = new JProgressBar();
			jProgressBarFileSendingProgress.setBounds(new Rectangle(3, 266, 378, 21));
			jProgressBarFileSendingProgress.setForeground(Color.green);
			jProgressBarFileSendingProgress.setBackground(Color.black);
			this.getJProgressBarFileSendingProgress().setVisible(false);
		}
		return jProgressBarFileSendingProgress;
	}

	public ChatWindow(XXPalkMainFrame mainFrame, NodeInfo nodeInfo){
		this.nodeInfo = nodeInfo;
		JDialog dialog = this.getJDialog_ChatWindow();
		dialog.setVisible(true);
		this.nodeInfo.chatWindowCreated();
		this.nodeInfo.setChatWindow(this);
		this.mainFrame = mainFrame;
		this.getJButton_Send().setMnemonic(java.awt.event.KeyEvent.VK_ENTER);
		this.jButton_Close = new JButton();
		jButton_Close.setVisible(false);
		final JDialog chatWindow = this.getJDialog_ChatWindow();
		jButton_Close.setMnemonic(java.awt.event.KeyEvent.VK_ESCAPE);
				
		String title = dialog.getTitle();
		title += nodeInfo.getName();
		dialog.setTitle(title);
	}
	
	private NodeInfo nodeInfo;
	private String str_History;
	static private XXPalkMainFrame mainFrame;
	private JScrollPane jScrollPane = null;
	private JTextArea jTextArea = null;
	
	
	public boolean isInCall(){
		return this.getJButton_Call().getText().contains("Calling")
						|| !this.getJButton_Call().getText().contains("Call");
	}
	
	public void onCallEnd(){
		this.getJButton_Call().setText("Call");
		this.getJButton_Call().setEnabled(true);
		this.getJButton_Hangup().setText("Hangup");
		this.getJButton_Hangup().setVisible(false);
		this.getJButton_Mute().setVisible(false);
		this.getJButton_Unmute().setVisible(false);
		this.getJButton_Mute().setEnabled(true);
		this.getJButton_Unmute().setEnabled(false);
		
		String history = this.getJTextArea().getText();
		history += "\n";
		history += "Call end with ";
		history += nodeInfo.getName();
		this.getJTextArea().setText(history);
	}
	
	
	/**
	 * This method initializes jScrollPane	
	 * 	
	 * @return javax.swing.JScrollPane	
	 */
	private JScrollPane getJScrollPane() {
		if (jScrollPane == null) {
			jScrollPane = new JScrollPane();
			jScrollPane.setBounds(new Rectangle(6, 84, 379, 138));
			jScrollPane.setViewportView(getJTextArea());
			jScrollPane.setBackground(Color.darkGray);
		}
		return jScrollPane;
	}

	/**
	 * This method initializes jTextArea	
	 * 	
	 * @return javax.swing.JTextArea	
	 */
	private JTextArea getJTextArea() {
		if (jTextArea == null) {
			jTextArea = new JTextArea();
			jTextArea.setEditable(false);
		}
		return jTextArea;
	}
	
	public void onChatReceive(String message){
		String history = this.getJTextArea().getText();
		history += "\n";
		String[] strs = this.nodeInfo.getName().split("@");
		history += strs[0];
		history += " said: ";
		history += message;
		this.getJTextArea().setText(history);
	}
	
	public void onCallIncoming(){
		this.getJButton_Call().setText("Accept");
		this.getJButton_Hangup().setText("Reject");
		this.getJButton_Hangup().setVisible(true);
		
		String history = this.getJTextArea().getText();
		history += "\n";
		history += "Incoming call form ";
		history += nodeInfo.getName();
		this.getJTextArea().setText(history);
	}
	
	public void onCallAnswered(){
		this.getJButton_Mute().setVisible(true);
		this.getJButton_Unmute().setVisible(true);
		this.getJButton_Call().setText("Connected");
		this.getJButton_Call().setEnabled(false);
		this.getJButton_Hangup().setText("Hangup");
		this.getJButton_Hangup().setVisible(true);
		
		String history = this.getJTextArea().getText();
		history += "\n";
		history += "Connected, calling with ";
		history += nodeInfo.getName();
		this.getJTextArea().setText(history);
	}
	
	public void onFileProgress(int value){
		this.jProgressBarFileSendingProgress.setValue(value);
	}
	
	public void onFileFished()
	{
		this.getJButton_SendFile().setText("Send");
		this.getJButton_Cancel().setText("Cancel");
		this.getJButton_SendFile().setEnabled(true);
		this.getJButton_Cancel().setEnabled(true);
		this.getJButton_Cancel().setVisible(false);
		this.getJProgressBarFileSendingProgress().setVisible(false);
		
		String history = this.getJTextArea().getText();
		history += "\n";
		history += "File transfer completed.";
		this.getJTextArea().setText(history);
	}
	
	public void onIcomingFile(String name, String file){
		this.getJButton_SendFile().setText("Receive");
		this.getJButton_Cancel().setText("Cancel");
		this.getJButton_SendFile().setEnabled(true);
		this.getJButton_Cancel().setEnabled(true);
		this.getJButton_SendFile().setVisible(true);
		this.getJButton_Cancel().setVisible(true);
		
		
		String history = this.getJTextArea().getText();
		history += "\n";
		history += name;
		history += " want to send file ";
		history += file;
		history += "to you.";
		this.getJTextArea().setText(history);
	}
	
	public void onFileCanceled(){
		this.getJButton_SendFile().setText("Send");
		this.getJButton_Cancel().setText("Cancel");
		this.getJButton_SendFile().setEnabled(true);
		this.getJButton_Cancel().setEnabled(true);
		this.getJButton_Cancel().setVisible(false);
		this.getJProgressBarFileSendingProgress().setVisible(false);
		
		String history = this.getJTextArea().getText();
		history += "\n";
		history += "File transfer canceled.";
		this.getJTextArea().setText(history);
	}
	
	public void onFileBegin(){
		this.getJButton_SendFile().setText("Started");
		this.getJButton_SendFile().setEnabled(false);
		this.getJProgressBarFileSendingProgress().setVisible(true);
		this.getJProgressBarFileSendingProgress().setValue(0);
	}
	
	public boolean hasFileTransfer(){
		if(this.jButton_SendFile.getText().contains("Send"))
			return false;
		else
			return true;
	}
}
