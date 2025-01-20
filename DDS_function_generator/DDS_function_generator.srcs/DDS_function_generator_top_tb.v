`timescale 1ns / 1ns
//////////////////////////////////////////////////////////////////////////////////
// Company:
// Engineer:
//
// Create Date: 29.11.2023 14:37:35
// Design Name:
// Module Name: DDS_function_generator_top_tb
// Project Name:
// Target Devices:
// Tool Versions:clk_period
// Description:
//
// Dependencies:
//
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
//
//////////////////////////////////////////////////////////////////////////////////
//Fword = (2**32)*Fout/Fclk;
//Pword = degree/360*4096;
`define clk_period 20 //50MHz
module DDS_function_generator_top_tb();
    reg Clk;
    reg Rst_n;
    reg [7:0]Data_Byte_t;
    reg send_en;
    wire Rs232_Rx;
    wire [9:0]DA_out;
    wire [9:0]DB_out;
    wire DA1_Clk;
    wire Tx_Done;
    
    
    DDS_function_generator_top DDS_function_generator_top(
    .Clk(Clk),
    .Rs232_Rx(Rs232_Rx),
    .Rst_n(Rst_n),
    .DA_out(DA_out),
    .DB_out(DB_out),
    .DA1_Clk(DA1_Clk)
    );
    
    UART_Byte_Tx UART_Byte_Tx(
    .Clk(Clk),
    .Rst_n(Rst_n),
    .Data_Byte(Data_Byte_t),
    .send_en(send_en),
    .Baud_Set(3'd0),
    .Rs232_Tx(Rs232_Rx),
    .Tx_Done(Tx_Done),
    .uart_state()
    );
    //50MHz
    initial Clk               = 1;
    always#(`clk_period/2)Clk = ~Clk;
    
    initial begin
        
        Rst_n       = 1'b0;
        Data_Byte_t = 8'd0;
        send_en     = 1'd0;
        #(`clk_period*2000 + 1);
        
        Rst_n = 1'b1;
        #(`clk_period*50);
        //Send Freq�????????????????????????????????????????????????????????125MHz
        //编码方式：将发�?�数据转为二进制，除了�?�道选择高低位对调发�??????????????????????????????????????????????????????
        //AA030036B0000088,CHANNEL0:100HZ;
        //AA03020020000088,CHANNEL0:90DEGREE;
        //AA03011C61000088,CHANNEL1:1000HZ;
        //AA03030010000088,CHANNEL1:180DEGREE;
        //AA03045830000088,3098/4096*5V;
        //AA0305FFF0000088,4095/4096*5V;
        //AA03080004000088,1X:0,1Y:8192;
        //AA03092c1034c088,2X:812,2Y:2100;
        //AA030a134c1a6088,3X:1624,3Y:13000;
        //AA030bdb38001088,4X:2048,4Y:7387;
        //AA030c017c2c5088,5X:2612,5Y:16000;
        //AA030db52067d088,6X:3046,6Y:1197;
        //AA030e9920817088,7X:3713,7Y:1177;
        //AA030fd864000888,8X:4096,8Y:9755;
        
        //AA03064400000088,DDS_A:Cus; DDS_B:TRI;
        //AA0307fffe000088,RENWE;
        
        
        
        /* --------------------- AA030036B0000088,CHANNEL0:100HZ -------------------- */
        //send one byte
        Data_Byte_t = 8'haa;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h03;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h00;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h36;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'hb0;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h00;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h00;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h88;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        
        /* ------------------------------------ - ----------------------------------- */
        #(`clk_period*200000);
        /* --------------------- AA03020020000088,CHANNEL0:90DEGREE -------------------- */
        //send one byte
        Data_Byte_t = 8'haa;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h03;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h02;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h00;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h20;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h00;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h00;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h88;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        
        /* ------------------------------------ - ----------------------------------- */
        #(`clk_period*200000);
        /* --------------------- AA03011C61000088,CHANNEL1:1000HZ -------------------- */
        //send one byte
        Data_Byte_t = 8'haa;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h03;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h01;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h1c;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h61;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h00;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h00;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h88;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        
        /* ------------------------------------ - ----------------------------------- */
        #(`clk_period*200000);
        /* --------------------- AA03030010000088,CHANNEL1:180DEGREE -------------------- */
        //send one byte
        Data_Byte_t = 8'haa;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h03;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h03;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h00;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h10;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h00;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h00;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h88;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        
        /* ------------------------------------ - ----------------------------------- */
        #(`clk_period*200000);
        /* --------------------- //AA03045830000088,3098/4096*5V -------------------- */
        //send one byte
        Data_Byte_t = 8'haa;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h03;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h04;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h58;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h30;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h00;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h00;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h88;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        
        /* ------------------------------------ - ----------------------------------- */
        #(`clk_period*200000);
        /* --------------------- AA0305FFF0000088,4095/4096*5V -------------------- */
        //send one byte
        Data_Byte_t = 8'haa;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h03;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h05;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'hFF;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'hF0;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h00;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h00;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h88;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        
        /* ------------------------------------ - ----------------------------------- */
        #(`clk_period*200000);
        /* ---------------------  AA03080004000088,1X:0,1Y:8192 -------------------- */
        //send one byte
        Data_Byte_t = 8'haa;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h03;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h08;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h00;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h04;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h00;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h00;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h88;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        
        /* ------------------------------------ - ----------------------------------- */
        #(`clk_period*200000);
        /* ---------------------AA03092c1034c088,2X:812,2Y:2100 -------------------- */
        //send one byte
        Data_Byte_t = 8'haa;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h03;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h09;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h2c;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h10;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h34;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'hc0;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h88;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        
        /* ------------------------------------ - ----------------------------------- */
        #(`clk_period*200000);
        
        /* ---------------------AA030a134c1a6088,3X:1624,3Y:13000 -------------------- */
        //send one byte
        Data_Byte_t = 8'haa;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h03;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h0a;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h13;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h4c;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h1a;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h60;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h88;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        
        /* ------------------------------------ - ----------------------------------- */
        #(`clk_period*200000);
        
        /* --------------------- AA030bdb38001088,4X:2048,4Y:7387 -------------------- */
        //send one byte
        Data_Byte_t = 8'haa;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h03;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h0b;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'hdb;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h38;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h00;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h10;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h88;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        
        /* ------------------------------------ - ----------------------------------- */
        #(`clk_period*200000);
        
        /* --------------------- AA030c017c2c5088,5X:2612,5Y:16000 -------------------- */
        //send one byte
        Data_Byte_t = 8'haa;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h03;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h0c;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h01;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h7c;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h2c;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h50;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h88;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        
        /* ------------------------------------ - ----------------------------------- */
        #(`clk_period*200000);
        
        
        /* --------------------- AA030db52067d088,6X:3046,6Y:1197 -------------------- */
        //send one byte
        Data_Byte_t = 8'haa;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h03;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h0d;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'hb5;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h20;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h67;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'hd0;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h88;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        
        /* ------------------------------------ - ----------------------------------- */
        #(`clk_period*200000);
        
        /* --------------------- AA030e9920817088,7X:3713,7Y:1177 -------------------- */
        //send one byte
        Data_Byte_t = 8'haa;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h03;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h0e;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h99;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h20;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h81;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h70;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h88;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        
        /* ------------------------------------ - ----------------------------------- */
        #(`clk_period*200000);
        
        /* --------------------- AA030fd864000888,8X:4096,8Y:9755 -------------------- */
        //send one byte
        Data_Byte_t = 8'haa;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h03;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h0f;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'hd8;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h64;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h00;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h08;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h88;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        
        /* ------------------------------------ - ----------------------------------- */
        #(`clk_period*200000);
        
        /* --------------------- AA03064400000088,DDS_A:Cus; DDS_B:TRI -------------------- */
        //send one byte
        Data_Byte_t = 8'haa;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h03;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h06;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h44;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h00;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h00;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h00;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h88;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        
        /* ------------------------------------ - ----------------------------------- */
        #(`clk_period*200000);
        /* --------------------- AA0307fffe000088,RENWE -------------------- */
        //send one byte
        Data_Byte_t = 8'haa;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h03;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h07;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'hff;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'hfe;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h00;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h00;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        #(`clk_period*1);
        //send one byte
        Data_Byte_t = 8'h88;
        send_en     = 1'd1;
        #`clk_period;
        send_en = 1'd0;
        @(posedge Tx_Done)
        
        /* ------------------------------------ - ----------------------------------- */
        #(`clk_period*20000000);
        $stop;
    end
endmodule
