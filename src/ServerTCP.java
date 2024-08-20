import java.awt.Button;
import java.awt.FlowLayout;
import java.awt.GridLayout;
import java.awt.Label;
import java.awt.Panel;
import java.awt.TextField;
import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;

import javax.swing.JButton;
import javax.swing.JFrame;


public class ServerTCP extends JFrame{

    public Label lable;
    public Panel panel;
    public Button button;
    public TextField tex;
    
    public String Infor;

    public ServerTCP(){

        lable = new Label();
        button = new Button();
        tex = new TextField("Hello", 10);
        tex.setText("Hello server");
        panel = new Panel(new FlowLayout());
        panel.add(lable);
        panel.add(button);
        panel.add(tex);
        this.add(panel);

        setSize(400, 300);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setVisible(true);

        InfoServer();
    }

    public void InfoServer(){
        

        int port = 5000; // Port mà server sẽ lắng nghe
        
        Thread thread = new Thread(new Runnable() {

            public void run()
            {
                
                try (ServerSocket serverSocket = new ServerSocket(port)) {
                    System.out.println("Server đang lắng nghe tại port " + port);

                    // Chấp nhận kết nối từ client
                    try (Socket clientSocket = serverSocket.accept()) {
                        System.out.println("Client kết nối thành công!");

                        // Tạo các stream để đọc và ghi dữ liệu
                        BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
                        PrintWriter out = new PrintWriter(clientSocket.getOutputStream(), true);

                        String receivedMessage;
                        // Đọc dữ liệu từ client và gửi phản hồi
                        while ((receivedMessage = in.readLine()) != null) {
                            System.out.println("Nhận từ client: " + receivedMessage);
                            Infor = receivedMessage;
                            //out.println("Đã nhận: " + receivedMessage); // Gửi phản hồi đến client
                        }
                    }
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }

        });
        
        thread.start();
        int count = 0;
        while(count++ < 100)
        {
            try {
                
                System.out.println("ui: " + Infor);
                tex.setText(Infor);
                Thread.sleep(1000);
            } catch (Exception e) {
                //TODO: handle exception
            }
        }

        tex.setText("Ket thuc");
    }

    public static void main(String[] args) {

        new ServerTCP();
    }
}


