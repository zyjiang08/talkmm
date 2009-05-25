package xxpalk_ui.ui;

import java.io.*;
import java.net.Socket;

public class SocketThread extends Thread {

	public SocketThread(XXPalkMainFrame mainFrame, int port){
		super();
		this.mainframe = mainFrame;
		final int PORT = port;
		try{
			connexion = new Socket("localhost", PORT);
			sortie = new PrintWriter( connexion.getOutputStream(), true); 
			entree = new BufferedReader( new InputStreamReader(connexion.getInputStream()));
		}catch(Exception e){
			System.out.println(e);
		}//try catch
		
	}
	
	public void close(){
		try{
			this.connexion.close();
//			this.stop();
		}catch(Exception e){
			System.out.println(e);
		}//catch
	}
	
	public void send(String str){
		try{
//			sortie = new PrintWriter( connexion.getOutputStream(), true); 
			sortie.println(str);
		}catch(Exception e){
			System.out.println(e);
		}
	}
	
	public void sendln(){
		sortie.println("");
	}
	
	public void run(){
		while(continu) {
			try{
//				System.out.println("readline");
				String ligne = entree.readLine();
//				System.out.println("after readline");
				if(ligne != null){ 
					System.out.println("Received " + ligne);
					this.parseLine(ligne);
				}//if
//				if(ligne=="quite") continu=false;
//				else System.out.println(ligne);
			}catch(Exception e){
				System.out.println(e);
			}//try catch
		}//while
	}
	
	private void parseLine(String ligne){
		
		if(ligne.contains("incomingfile###")){
			String[] strs = ligne.split("###");
			System.out.println(strs.length);
			if(strs[0].contains("incomingfile") && strs.length >= 2){
				String temp = strs[1];
				int i=temp.indexOf("@");
				String name= temp.substring(0, i);
				name += "@gmail.com";
				mainframe.onIcomingFile(name, strs[2]);
			}//if
		}		
		else if(ligne.contains("filetransferstarted###")){
			mainframe.onFileBegin();
		}
		else if(ligne.contains("filetransfercanceled###")){
			mainframe.onFileCanceled();
		}
		else if(ligne.contains("filetransfercompleted###")){
			mainframe.onFileFished();
		}
		else if(ligne.contains("filetransferfailed")){
			mainframe.onFileCanceled();
		}
		else if(ligne.contains("progress###")){
			String[] strs = ligne.split("###");
			if(strs[0].contains("progress") && strs[0].length() <= 8){
				int value = Integer.parseInt(strs[1]);
				mainframe.onFileProgress(value);
			}
		}
		else if(ligne.contains("incomingcall###")){
			String[] strs = ligne.split("###");
			if(strs[0].contains("incomingcall")){
				String temp = strs[1];
				int i=temp.indexOf("@");
				String name= temp.substring(0, i);
				name += "@gmail.com";
				mainframe.onCallInComing(name);
			}//if
		}//if		
		else if(ligne.contains("otherhangup###") ){
			mainframe.onCallEnd();
		}		
		else if(ligne.contains("callanswered###")){
			mainframe.onCallAnswered();
		}
		else if(ligne.contains("callnotanswered###")){
			mainframe.onCallEnd();
		}
		else if(ligne.contains("callinprogress###")){
			mainframe.onCallAnswered();
		}
		else if(ligne.contains("message")){
			String[] strs = ligne.split("###");
			if(strs[0].contains("message")){
				System.out.println(strs[1]);
				String message = strs[2];
				String temp = strs[1];
				int i = temp.indexOf("@");
				String name= temp.substring(0, i);
				name += "@gmail.com";
				mainframe.onChatReceive(name, message);
			}//if
		}//if
		else if(ligne.contains("@gmail.com")){
			String roster = null;
			String statue = null;
			String[] strs = ligne.split("<");
			if(strs.length >=2){
				roster = strs[0];
				statue = strs[1];
				mainframe.onUpdateStatu(roster, statue);
			}//if
//			System.out.println("user = " + roster + "; statue = " + statue);
		}//if
		else if(ligne.contains("connecting")){
			mainframe.onConnecting();

		}
		else if(ligne.contains("loggingin")){
			mainframe.onLoggingIn();

		}
		else if(ligne.contains("loggedin")){
//			this.send("loggedin");
			mainframe.onLoggedIn();
		}//if
		else if(ligne.contains("quite"))
			this.send("quite");
		else if(ligne.contains("loggedout")){
//			System.out.println("byebye");
			mainframe.onLoggedOut();
//			this.close();
//			continu = false;
			
			continu = false;
		}//else if
	}
	
	public PrintWriter getSortie(){
		return sortie;
	}
	private Socket connexion;
	private PrintWriter sortie;
	private BufferedReader entree;
	private boolean continu = true;
	
	private XXPalkMainFrame mainframe;
}
