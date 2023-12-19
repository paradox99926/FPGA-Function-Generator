`timescale 1ns / 1ns
//////////////////////////////////////////////////////////////////////////////////
// Company:
// Engineer:
//
// Create Date: 21.11.2023 10:38:46
// Design Name:
// Module Name: UART_Byte_Tx
// Project Name:
// Target Devices:
// Tool Versions:
// Description:
//
// Dependencies:
//
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
//
//////////////////////////////////////////////////////////////////////////////////


module UART_Byte_Tx(Clk,
                    Rst_n,       //模块复位
                    Data_Byte,   //待传8bit数据
                    send_en,     //发�?�使�???????
                    Baud_Set,    //波特率设�???????
                    Rs232_Tx,    //Rs232输出信号
                    Tx_Done,     //�??????? 次发送数据完成标�???????
                    uart_state); //发�?�数据状�???????
    
    input Clk;
    input Rst_n;
    input [7:0]Data_Byte;
    input send_en;
    input [2:0]Baud_Set;
    
    output reg Rs232_Tx;
    output reg Tx_Done;
    output reg uart_state;
    
    reg bps_clk;	//波特率时�???????
    
    reg [15:0]div_cnt;//分频计数�???????
    
    reg [15:0]bps_DR;//分频计数�??????? 大�??
    
    reg [3:0]bps_cnt;//波特率时钟计数器
    
    reg [7:0]r_data_byte;
    
    localparam START_BIT = 1'b0;
    localparam STOP_BIT  = 1'b1;
    
    always@(posedge Clk or negedge Rst_n)
        if (!Rst_n)
            uart_state <= 1'b0;
        else if (send_en)
            uart_state <= 1'b1;
        else if (bps_cnt == 4'd11)
            uart_state <= 1'b0;
        else
            uart_state <= uart_state;
    
    always@(posedge Clk or negedge Rst_n)
        if (!Rst_n)
            r_data_byte <= 8'd0;
        else if (send_en)
            r_data_byte <= Data_Byte;
        else
            r_data_byte <= r_data_byte;
    
    always@(posedge Clk or negedge Rst_n)
        if (!Rst_n)
            bps_DR <= 16'd5207;
        else begin
            case(Baud_Set)
                0:bps_DR       <= 16'd5207;//104167/System_clk_period-1,baud-rate:9600
                1:bps_DR       <= 16'd2603;//52083/System_clk_period-1,baud-rate:19200
                2:bps_DR       <= 16'd1301;//26041/System_clk_period-1,baud-rate:38400
                3:bps_DR       <= 16'd867;//17361/System_clk_period-1,baud-rate:57600
                4:bps_DR       <= 16'd433;//8680/System_clk_period-1,baud-rate:115200
                default:bps_DR <= 16'd5207;//104167/System_clk_period-1,baud-rate:9600
            endcase
        end
    
    //counter
    always@(posedge Clk or negedge Rst_n)
        if (!Rst_n)
            div_cnt <= 16'd0;
        else if (uart_state)begin
            if (div_cnt == bps_DR)
                div_cnt <= 16'd0;
            else
                div_cnt <= div_cnt + 1'b1;
        end
        else
            div_cnt <= 16'd0;
    
    // bps_clk gen
    always@(posedge Clk or negedge Rst_n)
        if (!Rst_n)
            bps_clk <= 1'b0;
        else if (div_cnt == 16'd1)
            bps_clk <= 1'b1;
        else
            bps_clk <= 1'b0;
    
    //bps counter
    always@(posedge Clk or negedge Rst_n)
        if (!Rst_n)
            bps_cnt <= 4'd0;
        else if (bps_cnt == 4'd11)
            bps_cnt <= 4'd0;
        else if (bps_clk)
            bps_cnt <= bps_cnt + 1'b1;
        else
            bps_cnt <= bps_cnt;
    
    always@(posedge Clk or negedge Rst_n)
        if (!Rst_n)
            Tx_Done <= 1'b0;
        else if (bps_cnt == 4'd11)
            Tx_Done <= 1'b1;
        else
            Tx_Done <= 1'b0;
    
    always@(posedge Clk or negedge Rst_n)
        if (!Rst_n)
            Rs232_Tx <= 1'b1;
        else begin
            case(bps_cnt)
                0:Rs232_Tx       <= 1'b1;
                1:Rs232_Tx       <= START_BIT;
                2:Rs232_Tx       <= r_data_byte[0];
                3:Rs232_Tx       <= r_data_byte[1];
                4:Rs232_Tx       <= r_data_byte[2];
                5:Rs232_Tx       <= r_data_byte[3];
                6:Rs232_Tx       <= r_data_byte[4];
                7:Rs232_Tx       <= r_data_byte[5];
                8:Rs232_Tx       <= r_data_byte[6];
                9:Rs232_Tx       <= r_data_byte[7];
                10:Rs232_Tx      <= STOP_BIT;
                default:Rs232_Tx <= 1'b1;
            endcase
        end
    
endmodule
    
